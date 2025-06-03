Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Header file for flow control implementation in HTTP/2 transport
#include "src/core/ext/transport/chttp2/transport/flow_control.h"

// Platform-specific support macros
#include <grpc/support/port_platform.h>
#include <inttypes.h>

// Standard library includes
#include <algorithm>
#include <cmath>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

// Abseil logging and string utilities
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"

// HTTP/2 settings and core utilities
#include "src/core/ext/transport/chttp2/transport/http2_settings.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace chttp2 {

// Global variable for testing purposes to mock transport target window estimates
TestOnlyTransportTargetWindowEstimatesMocker*
    g_test_only_transport_target_window_estimates_mocker;

namespace {
// Maximum size for window updates (2^31 - 1 as per HTTP/2 spec)
constexpr const int64_t kMaxWindowUpdateSize = (1u << 31) - 1;
}

// Returns string representation of flow control urgency
const char* FlowControlAction::UrgencyString(Urgency u) {
  switch (u) {
    case Urgency::NO_ACTION_NEEDED:
      return "no-action";
    case Urgency::UPDATE_IMMEDIATELY:
      return "now";
    case Urgency::QUEUE_UPDATE:
      return "queue";
    default:
      GPR_UNREACHABLE_CODE(return "unknown");
  }
  GPR_UNREACHABLE_CODE(return "unknown");
}

// Output operator for flow control urgency
std::ostream& operator<<(std::ostream& out, FlowControlAction::Urgency u) {
  return out << FlowControlAction::UrgencyString(u);
}

// Returns debug string describing the flow control action
std::string FlowControlAction::DebugString() const {
  std::vector<std::string> segments;
  if (send_transport_update_ != Urgency::NO_ACTION_NEEDED) {
    segments.push_back(
        absl::StrCat("t:", UrgencyString(send_transport_update_)));
  }
  if (send_stream_update_ != Urgency::NO_ACTION_NEEDED) {
    segments.push_back(absl::StrCat("s:", UrgencyString(send_stream_update_)));
  }
  if (send_initial_window_update_ != Urgency::NO_ACTION_NEEDED) {
    segments.push_back(
        absl::StrCat("iw=", initial_window_size_, ":",
                     UrgencyString(send_initial_window_update_)));
  }
  if (send_max_frame_size_update_ != Urgency::NO_ACTION_NEEDED) {
    segments.push_back(
        absl::StrCat("mf=", max_frame_size_, ":",
                     UrgencyString(send_max_frame_size_update_)));
  }
  if (segments.empty()) return "no action";
  return absl::StrJoin(segments, ",");
}

// Output operator for flow control action
std::ostream& operator<<(std::ostream& out, const FlowControlAction& action) {
  return out << action.DebugString();
}

// Constructor for transport-level flow control
TransportFlowControl::TransportFlowControl(absl::string_view name,
                                           bool enable_bdp_probe,
                                           MemoryOwner* memory_owner)
    : memory_owner_(memory_owner),
      enable_bdp_probe_(enable_bdp_probe),
      bdp_estimator_(name) {}

// Calculates desired window update size for transport
uint32_t TransportFlowControl::DesiredAnnounceSize(bool writing_anyway) const {
  const uint32_t target_announced_window =
      static_cast<uint32_t>(target_window());
  if ((writing_anyway || announced_window_ <= target_announced_window / 2) &&
      announced_window_ != target_announced_window) {
    return Clamp(target_announced_window - announced_window_, int64_t{0},
                 kMaxWindowUpdateSize);
  }
  return 0;
}

// Updates announced window after sending window update
void TransportFlowControl::SentUpdate(uint32_t announce) {
  announced_window_ += announce;
}

// Constructor for stream-level flow control
StreamFlowControl::StreamFlowControl(TransportFlowControl* tfc) : tfc_(tfc) {}

// Handles incoming data frame at stream level
absl::Status StreamFlowControl::IncomingUpdateContext::RecvData(
    int64_t incoming_frame_size) {
  return tfc_upd_.RecvData(incoming_frame_size, [this, incoming_frame_size]() {
    int64_t acked_stream_window =
        sfc_->announced_window_delta_ + sfc_->tfc_->acked_init_window();
    if (incoming_frame_size > acked_stream_window) {
      return absl::InternalError(absl::StrFormat(
          "frame of size %" PRId64 " overflows local window of %" PRId64,
          incoming_frame_size, acked_stream_window));
    }

    tfc_upd_.UpdateAnnouncedWindowDelta(&sfc_->announced_window_delta_,
                                        -incoming_frame_size);
    sfc_->min_progress_size_ -=
        std::min(sfc_->min_progress_size_, incoming_frame_size);
    return absl::OkStatus();
  });
}

// Handles incoming data frame at transport level
absl::Status TransportFlowControl::IncomingUpdateContext::RecvData(
    int64_t incoming_frame_size, absl::FunctionRef<absl::Status()> stream) {
  if (incoming_frame_size > tfc_->announced_window_) {
    return absl::InternalError(absl::StrFormat(
        "frame of size %" PRId64 " overflows local window of %" PRId64,
        incoming_frame_size, tfc_->announced_window_));
  }
  absl::Status error = stream();
  if (!error.ok()) return error;
  tfc_->announced_window_ -= incoming_frame_size;
  return absl::OkStatus();
}

// Calculates target window size for transport flow control
int64_t TransportFlowControl::target_window() const {
  return static_cast<uint32_t>(
      std::min(static_cast<int64_t>((1u << 31) - 1),
               announced_stream_total_over_incoming_window_ +
                   std::max<int64_t>(1, target_initial_window_size_)));
}

// Determines if flow control action is needed for transport
FlowControlAction TransportFlowControl::UpdateAction(FlowControlAction action) {
  const int64_t target = target_window();

  const int64_t send_threshold = (target + 1) / 2;
  if (announced_window_ < send_threshold) {
    action.set_send_transport_update(
        FlowControlAction::Urgency::UPDATE_IMMEDIATELY);
  }
  return action;
}

// Calculates initial window size based on memory pressure and BDP
double
TransportFlowControl::TargetInitialWindowSizeBasedOnMemoryPressureAndBdp()
    const {
  const double bdp = bdp_estimator_.EstimateBdp() * 2.0;
  const double memory_pressure =
      memory_owner_->GetPressureInfo().pressure_control_value;

  // Linear interpolation helper function
  auto lerp = [](double t, double t_min, double t_max, double a, double b) {
    return a + ((b - a) * (t - t_min) / (t_max - t_min));
  };

  // Constants for memory pressure thresholds and window sizes
  const double kAnythingGoesPressure = 0.2;
  const double kAdjustedToBdpPressure = 0.5;
  const double kOneMegabyte = 1024.0 * 1024.0;
  const double kAnythingGoesWindow = std::max(4.0 * kOneMegabyte, bdp);
  
  // Determine window size based on memory pressure
  if (memory_pressure < kAnythingGoesPressure) {
    return kAnythingGoesWindow;
  } else if (memory_pressure < kAdjustedToBdpPressure) {
    return lerp(memory_pressure, kAnythingGoesPressure, kAdjustedToBdpPressure,
                kAnythingGoesWindow, bdp);
  } else if (memory_pressure < 1.0) {
    return lerp(memory_pressure, kAdjustedToBdpPressure, 1.0, bdp, 0);
  } else {
    return 0;
  }
}

// Updates flow control setting and generates appropriate action
void TransportFlowControl::UpdateSetting(
    absl::string_view name, int64_t* desired_value, uint32_t new_desired_value,
    FlowControlAction* action,
    FlowControlAction& (FlowControlAction::*set)(FlowControlAction::Urgency,
                                                 uint32_t)) {
  if (new_desired_value != *desired_value) {
    GRPC_TRACE_LOG(flowctl, INFO)
        << "[flowctl] UPDATE SETTING " << name << " from " << *desired_value
        << " to " << new_desired_value;

    FlowControlAction::Urgency urgency =
        FlowControlAction::Urgency::QUEUE_UPDATE;
    if (*desired_value == 0 || new_desired_value == 0) {
      urgency = FlowControlAction::Urgency::UPDATE_IMMEDIATELY;
    }
    *desired_value = new_desired_value;
    (action->*set)(urgency, *desired_value);
  }
}

// Sets acknowledged initial window size and returns appropriate action
FlowControlAction TransportFlowControl::SetAckedInitialWindow(uint32_t value) {
  acked_init_window_ = value;
  FlowControlAction action;
  if (acked_init_window_ != target_initial_window_size_) {
    FlowControlAction::Urgency urgency =
        FlowControlAction::Urgency::QUEUE_UPDATE;
    if (acked_init_window_ == 0 || target_initial_window_size_ == 0) {
      urgency = FlowControlAction::Urgency::UPDATE_IMMEDIATELY;
    }
    action.set_send_initial_window_update(urgency, target_initial_window_size_);
  }
  return action;
}

// Performs periodic update of flow control settings
FlowControlAction TransportFlowControl::PeriodicUpdate() {
  FlowControlAction action;
  if (enable_bdp_probe_) {
    // Calculate target window size based on memory pressure and BDP
    uint32_t target = static_cast<uint32_t>(RoundUpToPowerOf2(
        Clamp(TargetInitialWindowSizeBasedOnMemoryPressureAndBdp(), 0.0,
              static_cast<double>(kMaxInitialWindowSize))));
    if (target < kMinPositiveInitialWindowSize) target = 0;
    
    // Allow test mocker to override target if present
    if (g_test_only_transport_target_window_estimates_mocker != nullptr) {
      target = g_test_only_transport_target_window_estimates_mocker
                   ->ComputeNextTargetInitialWindowSizeFromPeriodicUpdate(
                       target_initial_window_size_ );
    }

    // Update initial window size setting
    UpdateSetting(Http2Settings::initial_window_size_name(),
                  &target_initial_window_size_,
                  std::min(target, Http2Settings::max_initial_window_size()),
                  &action, &FlowControlAction::set_send_initial_window_update);

    // Update max frame size setting
    UpdateSetting(Http2Settings::max_frame_size_name(), &target_frame_size_,
                  Clamp(target, Http2Settings::min_max_frame_size(),
                        Http2Settings::max_max_frame_size()),
                  &action, &FlowControlAction::set_send_max_frame_size_update);

    // Update preferred crypto frame size if experiment is enabled
    if (IsTcpFrameSizeTuningEnabled()) {
      UpdateSetting(
          Http2Settings::preferred_receive_crypto_message_size_name(),
          &target_preferred_rx_crypto_frame_size_,
          Clamp(static_cast<unsigned int>(target_frame_size_ * 2),
                Http2Settings::min_preferred_receive_crypto_message_size(),
                Http2Settings::max_preferred_receive_crypto_message_size()),
          &action,
          &FlowControlAction::set_preferred_rx_crypto_frame_size_update);
    }
  }
  return UpdateAction(action);
}

// Returns string representation of transport flow control stats
std::string TransportFlowControl::Stats::ToString() const {
  return absl::StrCat("target_window: ", target_window,
                      " target_frame_size: ", target_frame_size,
                      " target_preferred_rx_crypto_frame_size: ",
                      target_preferred_rx_crypto_frame_size,
                      " acked_init_window: ", acked_init_window,
                      " queued_init_window: ", queued_init_window,
                      " sent_init_window: ", sent_init_window,
                      " remote_window: ", remote_window,
                      " announced_window: ", announced_window,
                      " announced_stream_total_over_incoming_window: ",
                      announced_stream_total_over_incoming_window,
                      " bdp_accumulator: ", bdp_accumulator,
                      " bdp_estimate: ", bdp_estimate,
                      " bdp_bw_est: ", bdp_bw_est);
}

// Updates stream window after sending window update
void StreamFlowControl::SentUpdate(uint32_t announce) {
  TransportFlowControl::IncomingUpdateContext tfc_upd(tfc_);
  pending_size_ = std::nullopt;
  tfc_upd.UpdateAnnouncedWindowDelta(&announced_window_delta_, announce);
  CHECK_EQ(DesiredAnnounceSize(), 0u);
  std::ignore = tfc_upd.MakeAction();
}

// Calculates desired window update size for stream
uint32_t StreamFlowControl::DesiredAnnounceSize() const {
  int64_t desired_window_delta = [this]() {
    if (min_progress_size_ == 0) {
      if (pending_size_.has_value() &&
          announced_window_delta_ < -*pending_size_) {
        return -*pending_size_;
      } else {
        return announced_window_delta_;
      }
    } else {
      return std::min(min_progress_size_, kMaxWindowDelta);
    }
  }();
  return Clamp(desired_window_delta - announced_window_delta_, int64_t{0},
               kMaxWindowUpdateSize);
}

// Determines if flow control action is needed for stream
FlowControlAction StreamFlowControl::UpdateAction(FlowControlAction action) {
  const int64_t desired_announce_size = DesiredAnnounceSize();
  if (desired_announce_size > 0) {
    FlowControlAction::Urgency urgency =
        FlowControlAction::Urgency::QUEUE_UPDATE;

    // Determine urgency based on window size thresholds
    const int64_t hurry_up_size = std::max(
        static_cast<int64_t>(tfc_->queued_init_window()) / 2, int64_t{8192});
    if (desired_announce_size > hurry_up_size) {
      urgency = FlowControlAction::Urgency::UPDATE_IMMEDIATELY;
    }

    if (min_progress_size_ > 0) {
      if (announced_window_delta_ <=
          -static_cast<int64_t>(tfc_->sent_init_window()) / 2) {
        urgency = FlowControlAction::Urgency::UPDATE_IMMEDIATELY;
      }
    }
    action.set_send_stream_update(urgency);
  }
  return action;
}

// Sets pending size for stream flow control
void StreamFlowControl::IncomingUpdateContext::SetPendingSize(
    int64_t pending_size) {
  CHECK_GE(pending_size, 0);
  sfc_->pending_size_ = pending_size;
}

// Returns string representation of stream flow control stats
std::string StreamFlowControl::Stats::ToString() const {
  return absl::StrCat("min_progress_size: ", min_progress_size,
                      " remote_window_delta: ", remote_window_delta,
                      " announced_window_delta: ", announced_window_delta,
                      pending_size.has_value() ? *pending_size : -1);
}

}  // namespace chttp2
}  // namespace grpc_core
```