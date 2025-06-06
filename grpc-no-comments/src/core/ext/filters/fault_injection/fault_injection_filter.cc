
// Copyright 2021 gRPC authors.

#include "src/core/ext/filters/fault_injection/fault_injection_filter.h"

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <functional>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/log/log.h"
#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/call/status_util.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/filters/fault_injection/fault_injection_service_config_parser.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/time.h"

namespace grpc_core {

namespace {

std::atomic<uint32_t> g_active_faults{0};
static_assert(
    std::is_trivially_destructible<std::atomic<uint32_t>>::value,
    "the active fault counter needs to have a trivially destructible type");

template <typename T>
auto AsInt(absl::string_view s) -> std::optional<T> {
  T x;
  if (absl::SimpleAtoi(s, &x)) return x;
  return std::nullopt;
}

inline bool UnderFraction(absl::InsecureBitGen* rand_generator,
                          const uint32_t numerator,
                          const uint32_t denominator) {
  if (numerator <= 0) return false;
  if (numerator >= denominator) return true;

  const uint32_t random_number =
      absl::Uniform(absl::IntervalClosedOpen, *rand_generator, 0u, denominator);
  return random_number < numerator;
}

class FaultHandle {
 public:
  explicit FaultHandle(bool active) : active_(active) {
    if (active) {
      g_active_faults.fetch_add(1, std::memory_order_relaxed);
    }
  }
  ~FaultHandle() {
    if (active_) {
      g_active_faults.fetch_sub(1, std::memory_order_relaxed);
    }
  }
  FaultHandle(const FaultHandle&) = delete;
  FaultHandle& operator=(const FaultHandle&) = delete;
  FaultHandle(FaultHandle&& other) noexcept
      : active_(std::exchange(other.active_, false)) {}
  FaultHandle& operator=(FaultHandle&& other) noexcept {
    std::swap(active_, other.active_);
    return *this;
  }

 private:
  bool active_;
};

}

class FaultInjectionFilter::InjectionDecision {
 public:
  InjectionDecision(uint32_t max_faults, Duration delay_time,
                    std::optional<absl::Status> abort_request)
      : max_faults_(max_faults),
        delay_time_(delay_time),
        abort_request_(abort_request) {}

  std::string ToString() const;
  Timestamp DelayUntil();
  absl::Status MaybeAbort() const;

 private:
  bool HaveActiveFaultsQuota() const;

  uint32_t max_faults_;
  Duration delay_time_;
  std::optional<absl::Status> abort_request_;
  FaultHandle active_fault_{false};
};

absl::StatusOr<std::unique_ptr<FaultInjectionFilter>>
FaultInjectionFilter::Create(const ChannelArgs&,
                             ChannelFilter::Args filter_args) {
  return std::make_unique<FaultInjectionFilter>(filter_args);
}

FaultInjectionFilter::FaultInjectionFilter(ChannelFilter::Args filter_args)
    : index_(filter_args.instance_id()),
      service_config_parser_index_(
          FaultInjectionServiceConfigParser::ParserIndex()) {}

ArenaPromise<absl::Status> FaultInjectionFilter::Call::OnClientInitialMetadata(
    ClientMetadata& md, FaultInjectionFilter* filter) {
  auto decision = filter->MakeInjectionDecision(md);
  GRPC_TRACE_LOG(fault_injection_filter, INFO)
      << "chand=" << this << ": Fault injection triggered "
      << decision.ToString();
  auto delay = decision.DelayUntil();
  return TrySeq(Sleep(delay), [decision = std::move(decision)]() {
    return decision.MaybeAbort();
  });
}

FaultInjectionFilter::InjectionDecision
FaultInjectionFilter::MakeInjectionDecision(
    const ClientMetadata& initial_metadata) {

  auto* service_config_call_data = GetContext<ServiceConfigCallData>();
  auto* method_params = static_cast<FaultInjectionMethodParsedConfig*>(
      service_config_call_data->GetMethodParsedConfig(
          service_config_parser_index_));
  const FaultInjectionMethodParsedConfig::FaultInjectionPolicy* fi_policy =
      nullptr;
  if (method_params != nullptr) {
    fi_policy = method_params->fault_injection_policy(index_);
  }

  if (fi_policy == nullptr) {
    return InjectionDecision(0, Duration::Zero(),
                             std::nullopt);
  }

  grpc_status_code abort_code = fi_policy->abort_code;
  uint32_t abort_percentage_numerator = fi_policy->abort_percentage_numerator;
  uint32_t delay_percentage_numerator = fi_policy->delay_percentage_numerator;
  Duration delay = fi_policy->delay;

  if (!fi_policy->abort_code_header.empty() ||
      !fi_policy->abort_percentage_header.empty() ||
      !fi_policy->delay_header.empty() ||
      !fi_policy->delay_percentage_header.empty()) {
    std::string buffer;
    if (!fi_policy->abort_code_header.empty() && abort_code == GRPC_STATUS_OK) {
      auto value = initial_metadata.GetStringValue(fi_policy->abort_code_header,
                                                   &buffer);
      if (value.has_value()) {
        grpc_status_code_from_int(
            AsInt<int>(*value).value_or(GRPC_STATUS_UNKNOWN), &abort_code);
      }
    }
    if (!fi_policy->abort_percentage_header.empty()) {
      auto value = initial_metadata.GetStringValue(
          fi_policy->abort_percentage_header, &buffer);
      if (value.has_value()) {
        abort_percentage_numerator = std::min(
            AsInt<uint32_t>(*value).value_or(-1), abort_percentage_numerator);
      }
    }
    if (!fi_policy->delay_header.empty() && delay == Duration::Zero()) {
      auto value =
          initial_metadata.GetStringValue(fi_policy->delay_header, &buffer);
      if (value.has_value()) {
        delay = Duration::Milliseconds(
            std::max(AsInt<int64_t>(*value).value_or(0), int64_t{0}));
      }
    }
    if (!fi_policy->delay_percentage_header.empty()) {
      auto value = initial_metadata.GetStringValue(
          fi_policy->delay_percentage_header, &buffer);
      if (value.has_value()) {
        delay_percentage_numerator = std::min(
            AsInt<uint32_t>(*value).value_or(-1), delay_percentage_numerator);
      }
    }
  }

  bool delay_request = delay != Duration::Zero();
  bool abort_request = abort_code != GRPC_STATUS_OK;
  if (delay_request || abort_request) {
    MutexLock lock(&mu_);
    if (delay_request) {
      delay_request =
          UnderFraction(&delay_rand_generator_, delay_percentage_numerator,
                        fi_policy->delay_percentage_denominator);
    }
    if (abort_request) {
      abort_request =
          UnderFraction(&abort_rand_generator_, abort_percentage_numerator,
                        fi_policy->abort_percentage_denominator);
    }
  }

  return InjectionDecision(
      fi_policy->max_faults, delay_request ? delay : Duration::Zero(),
      abort_request ? std::optional<absl::Status>(absl::Status(
                          static_cast<absl::StatusCode>(abort_code),
                          fi_policy->abort_message))
                    : std::nullopt);
}

bool FaultInjectionFilter::InjectionDecision::HaveActiveFaultsQuota() const {
  return g_active_faults.load(std::memory_order_acquire) < max_faults_;
}

Timestamp FaultInjectionFilter::InjectionDecision::DelayUntil() {
  if (delay_time_ != Duration::Zero() && HaveActiveFaultsQuota()) {
    active_fault_ = FaultHandle{true};
    return Timestamp::Now() + delay_time_;
  }
  return Timestamp::InfPast();
}

absl::Status FaultInjectionFilter::InjectionDecision::MaybeAbort() const {
  if (abort_request_.has_value() &&
      (delay_time_ != Duration::Zero() || HaveActiveFaultsQuota())) {
    return abort_request_.value();
  }
  return absl::OkStatus();
}

std::string FaultInjectionFilter::InjectionDecision::ToString() const {
  return absl::StrCat("delay=", delay_time_ != Duration::Zero(),
                      " abort=", abort_request_.has_value());
}

const grpc_channel_filter FaultInjectionFilter::kFilter =
    MakePromiseBasedFilter<FaultInjectionFilter, FilterEndpoint::kClient>();

void FaultInjectionFilterRegister(CoreConfiguration::Builder* builder) {
  FaultInjectionServiceConfigParser::Register(builder);
}

}
