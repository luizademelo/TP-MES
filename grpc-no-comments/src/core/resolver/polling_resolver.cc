
// Copyright 2015 gRPC authors.

#include "src/core/resolver/polling_resolver.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/strip.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/service_config/service_config.h"
#include "src/core/util/backoff.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

using ::grpc_event_engine::experimental::EventEngine;

PollingResolver::PollingResolver(ResolverArgs args,
                                 Duration min_time_between_resolutions,
                                 BackOff::Options backoff_options,
                                 TraceFlag* tracer)
    : authority_(args.uri.authority()),
      name_to_resolve_(absl::StripPrefix(args.uri.path(), "/")),
      channel_args_(std::move(args.args)),
      work_serializer_(std::move(args.work_serializer)),
      result_handler_(std::move(args.result_handler)),
      tracer_(tracer),
      interested_parties_(args.pollset_set),
      min_time_between_resolutions_(min_time_between_resolutions),
      backoff_(backoff_options) {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this << "] created";
  }
}

PollingResolver::~PollingResolver() {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this << "] destroying";
  }
}

void PollingResolver::StartLocked() { MaybeStartResolvingLocked(); }

void PollingResolver::RequestReresolutionLocked() {
  if (request_ == nullptr) {

    if (result_status_state_ ==
        ResultStatusState::kResultHealthCallbackPending) {
      result_status_state_ =
          ResultStatusState::kReresolutionRequestedWhileCallbackWasPending;
    } else {
      MaybeStartResolvingLocked();
    }
  }
}

void PollingResolver::ResetBackoffLocked() {
  backoff_.Reset();
  if (next_resolution_timer_handle_.has_value()) {
    MaybeCancelNextResolutionTimer();
    StartResolvingLocked();
  }
}

void PollingResolver::ShutdownLocked() {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this << "] shutting down";
  }
  shutdown_ = true;
  MaybeCancelNextResolutionTimer();
  request_.reset();
}

void PollingResolver::ScheduleNextResolutionTimer(Duration delay) {
  next_resolution_timer_handle_ =
      channel_args_.GetObject<EventEngine>()->RunAfter(
          delay, [self = RefAsSubclass<PollingResolver>()]() mutable {
            ExecCtx exec_ctx;
            auto* self_ptr = self.get();
            self_ptr->work_serializer_->Run(
                [self = std::move(self)]() { self->OnNextResolutionLocked(); });
          });
}

void PollingResolver::OnNextResolutionLocked() {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this
              << "] re-resolution timer fired: shutdown_=" << shutdown_;
  }

  if (next_resolution_timer_handle_.has_value() && !shutdown_) {
    next_resolution_timer_handle_.reset();
    StartResolvingLocked();
  }
}

void PollingResolver::MaybeCancelNextResolutionTimer() {
  if (next_resolution_timer_handle_.has_value()) {
    if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
      LOG(INFO) << "[polling resolver " << this
                << "] cancel re-resolution timer";
    }
    channel_args_.GetObject<EventEngine>()->Cancel(
        *next_resolution_timer_handle_);
    next_resolution_timer_handle_.reset();
  }
}

void PollingResolver::OnRequestComplete(Result result) {
  Ref(DEBUG_LOCATION, "OnRequestComplete").release();
  work_serializer_->Run(
      [this, result]() mutable { OnRequestCompleteLocked(std::move(result)); });
}

void PollingResolver::OnRequestCompleteLocked(Result result) {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this << "] request complete";
  }
  request_.reset();
  if (!shutdown_) {
    if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
      LOG(INFO)
          << "[polling resolver " << this << "] returning result: addresses="
          << (result.addresses.ok()
                  ? absl::StrCat("<", result.addresses->size(), " addresses>")
                  : result.addresses.status().ToString())
          << ", service_config="
          << (result.service_config.ok()
                  ? (*result.service_config == nullptr
                         ? "<null>"
                         : std::string((*result.service_config)->json_string())
                               .c_str())
                  : result.service_config.status().ToString())
          << ", resolution_note=" << result.resolution_note;
    }
    CHECK(result.result_health_callback == nullptr);
    result.result_health_callback =
        [self = RefAsSubclass<PollingResolver>(
             DEBUG_LOCATION, "result_health_callback")](absl::Status status) {
          self->GetResultStatus(std::move(status));
        };
    result_status_state_ = ResultStatusState::kResultHealthCallbackPending;
    result_handler_->ReportResult(std::move(result));
  }
  Unref(DEBUG_LOCATION, "OnRequestComplete");
}

void PollingResolver::GetResultStatus(absl::Status status) {
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    LOG(INFO) << "[polling resolver " << this
              << "] result status from channel: " << status;
  }
  if (status.ok()) {

    backoff_.Reset();

    if (std::exchange(result_status_state_, ResultStatusState::kNone) ==
        ResultStatusState::kReresolutionRequestedWhileCallbackWasPending) {
      MaybeStartResolvingLocked();
    }
  } else {

    const Duration delay = backoff_.NextAttemptDelay();
    CHECK(!next_resolution_timer_handle_.has_value());
    if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
      LOG(INFO) << "[polling resolver " << this << "] retrying in "
                << delay.millis() << " ms";
    }
    ScheduleNextResolutionTimer(delay);

    result_status_state_ = ResultStatusState::kNone;
  }
}

void PollingResolver::MaybeStartResolvingLocked() {

  if (next_resolution_timer_handle_.has_value()) return;
  if (last_resolution_timestamp_.has_value()) {

    ExecCtx::Get()->InvalidateNow();
    const Timestamp earliest_next_resolution =
        *last_resolution_timestamp_ + min_time_between_resolutions_;
    const Duration time_until_next_resolution =
        earliest_next_resolution - Timestamp::Now();
    if (time_until_next_resolution > Duration::Zero()) {
      if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
        const Duration last_resolution_ago =
            Timestamp::Now() - *last_resolution_timestamp_;
        LOG(INFO) << "[polling resolver " << this
                  << "] in cooldown from last resolution (from "
                  << last_resolution_ago.millis()
                  << " ms ago); will resolve again in "
                  << time_until_next_resolution.millis() << " ms";
      }
      ScheduleNextResolutionTimer(time_until_next_resolution);
      return;
    }
  }
  StartResolvingLocked();
}

void PollingResolver::StartResolvingLocked() {
  request_ = StartRequest();
  last_resolution_timestamp_ = Timestamp::Now();
  if (GPR_UNLIKELY(tracer_ != nullptr && tracer_->enabled())) {
    if (request_ != nullptr) {
      LOG(INFO) << "[polling resolver " << this
                << "] starting resolution, request_=" << request_.get();
    } else {
      LOG(INFO) << "[polling resolver " << this << "] StartRequest failed";
    }
  }
}

}
