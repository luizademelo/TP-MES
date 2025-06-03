Here's the commented code:

```c++
// Copyright 2021 gRPC authors.

// Header file for fault injection filter implementation
#include "src/core/ext/filters/fault_injection/fault_injection_filter.h"

// Standard includes
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

// Abseil includes
#include "absl/log/log.h"
#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

// gRPC core includes
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

// Global counter for active faults across all channels
std::atomic<uint32_t> g_active_faults{0};
// Ensure atomic counter has trivial destructor for safe global destruction
static_assert(
    std::is_trivially_destructible<std::atomic<uint32_t>>::value,
    "the active fault counter needs to have a trivially destructible type");

// Utility function to convert string view to integer of type T
template <typename T>
auto AsInt(absl::string_view s) -> std::optional<T> {
  T x;
  if (absl::SimpleAtoi(s, &x)) return x;
  return std::nullopt;
}

// Determines if a random fraction is under given numerator/denominator ratio
inline bool UnderFraction(absl::InsecureBitGen* rand_generator,
                          const uint32_t numerator,
                          const uint32_t denominator) {
  if (numerator <= 0) return false;
  if (numerator >= denominator) return true;

  // Generate random number and compare against threshold
  const uint32_t random_number =
      absl::Uniform(absl::IntervalClosedOpen, *rand_generator, 0u, denominator);
  return random_number < numerator;
}

// RAII class to track active faults in global counter
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

}  // namespace

// Implementation of FaultInjectionFilter's injection decision logic
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

  uint32_t max_faults_;  // Maximum allowed concurrent faults
  Duration delay_time_;  // Duration to delay the request
  std::optional<absl::Status> abort_request_;  // Optional abort status
  FaultHandle active_fault_{false};  // RAII handle for active fault tracking
};

// Factory method for creating FaultInjectionFilter
absl::StatusOr<std::unique_ptr<FaultInjectionFilter>>
FaultInjectionFilter::Create(const ChannelArgs&,
                             ChannelFilter::Args filter_args) {
  return std::make_unique<FaultInjectionFilter>(filter_args);
}

// Constructor for FaultInjectionFilter
FaultInjectionFilter::FaultInjectionFilter(ChannelFilter::Args filter_args)
    : index_(filter_args.instance_id()),
      service_config_parser_index_(
          FaultInjectionServiceConfigParser::ParserIndex()) {}

// Handles client initial metadata and decides on fault injection
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

// Makes injection decision based on metadata and configuration
FaultInjectionFilter::InjectionDecision
FaultInjectionFilter::MakeInjectionDecision(
    const ClientMetadata& initial_metadata) {
  // Get service config data for current call
  auto* service_config_call_data = GetContext<ServiceConfigCallData>();
  auto* method_params = static_cast<FaultInjectionMethodParsedConfig*>(
      service_config_call_data->GetMethodParsedConfig(
          service_config_parser_index_));
  const FaultInjectionMethodParsedConfig::FaultInjectionPolicy* fi_policy =
      nullptr;
  if (method_params != nullptr) {
    fi_policy = method_params->fault_injection_policy(index_);
  }

  // Return no injection if no policy configured
  if (fi_policy == nullptr) {
    return InjectionDecision(0, Duration::Zero(),
                             std::nullopt);
  }

  // Get base policy values
  grpc_status_code abort_code = fi_policy->abort_code;
  uint32_t abort_percentage_numerator = fi_policy->abort_percentage_numerator;
  uint32_t delay_percentage_numerator = fi_policy->delay_percentage_numerator;
  Duration delay = fi_policy->delay;

  // Check for header overrides of policy values
  if (!fi_policy->abort_code_header.empty() ||
      !fi_policy->abort_percentage_header.empty() ||
      !fi_policy->delay_header.empty() ||
      !fi_policy->delay_percentage_header.empty()) {
    std::string buffer;
    // Override abort code from header if present
    if (!fi_policy->abort_code_header.empty() && abort_code == GRPC_STATUS_OK) {
      auto value = initial_metadata.GetStringValue(fi_policy->abort_code_header,
                                                   &buffer);
      if (value.has_value()) {
        grpc_status_code_from_int(
            AsInt<int>(*value).value_or(GRPC_STATUS_UNKNOWN), &abort_code);
      }
    }
    // Override abort percentage from header if present
    if (!fi_policy->abort_percentage_header.empty()) {
      auto value = initial_metadata.GetStringValue(
          fi_policy->abort_percentage_header, &buffer);
      if (value.has_value()) {
        abort_percentage_numerator = std::min(
            AsInt<uint32_t>(*value).value_or(-1), abort_percentage_numerator);
      }
    }
    // Override delay from header if present
    if (!fi_policy->delay_header.empty() && delay == Duration::Zero()) {
      auto value =
          initial_metadata.GetStringValue(fi_policy->delay_header, &buffer);
      if (value.has_value()) {
        delay = Duration::Milliseconds(
            std::max(AsInt<int64_t>(*value).value_or(0), int64_t{0}));
      }
    }
    // Override delay percentage from header if present
    if (!fi_policy->delay_percentage_header.empty()) {
      auto value = initial_metadata.GetStringValue(
          fi_policy->delay_percentage_header, &buffer);
      if (value.has_value()) {
        delay_percentage_numerator = std::min(
            AsInt<uint32_t>(*value).value_or(-1), delay_percentage_numerator);
      }
    }
  }

  // Determine if we should delay or abort
  bool delay_request = delay != Duration::Zero();
  bool abort_request = abort_code != GRPC_STATUS_OK;
  if (delay_request || abort_request) {
    MutexLock lock(&mu_);
    // Apply random percentage checks
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

  // Return injection decision with configured values
  return InjectionDecision(
      fi_policy->max_faults, delay_request ? delay : Duration::Zero(),
      abort_request ? std::optional<absl::Status>(absl::Status(
                          static_cast<absl::StatusCode>(abort_code),
                          fi_policy->abort_message))
                    : std::nullopt);
}

// Checks if we have quota for more active faults
bool FaultInjectionFilter::InjectionDecision::HaveActiveFaultsQuota() const {
  return g_active_faults.load(std::memory_order_acquire) < max_faults_;
}

// Returns timestamp for when delay should end, if applicable
Timestamp FaultInjectionFilter::InjectionDecision::DelayUntil() {
  if (delay_time_ != Duration::Zero() && HaveActiveFaultsQuota()) {
    active_fault_ = FaultHandle{true};
    return Timestamp::Now() + delay_time_;
  }
  return Timestamp::InfPast();
}

// Returns abort status if request should be aborted
absl::Status FaultInjectionFilter::InjectionDecision::MaybeAbort() const {
  if (abort_request_.has_value() &&
      (delay_time_ != Duration::Zero() || HaveActiveFaultsQuota())) {
    return abort_request_.value();
  }
  return absl::OkStatus();
}

// Returns string representation of injection decision
std::string FaultInjectionFilter::InjectionDecision::ToString() const {
  return absl::StrCat("delay=", delay_time_ != Duration::Zero(),
                      " abort=", abort_request_.has_value());
}

// Static filter definition
const grpc_channel_filter FaultInjectionFilter::kFilter =
    MakePromiseBasedFilter<FaultInjectionFilter, FilterEndpoint::kClient>();

// Registration function for core configuration
void FaultInjectionFilterRegister(CoreConfiguration::Builder* builder) {
  FaultInjectionServiceConfigParser::Register(builder);
}

}  // namespace grpc_core
```