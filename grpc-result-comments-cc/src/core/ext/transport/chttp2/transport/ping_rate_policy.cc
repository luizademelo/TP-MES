Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <optional>
#include <ostream>

#include "absl/strings/str_cat.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/util/match.h"

namespace grpc_core {

namespace {
// Default maximum number of pings that can be sent without receiving any data
int g_default_max_pings_without_data_sent = 2;
// Minimum time interval between pings when no data is being received
constexpr Duration kThrottleIntervalWithoutDataSent = Duration::Minutes(1);
// Optional default maximum number of in-flight pings
std::optional<int> g_default_max_inflight_pings;
}

// Constructor for Chttp2PingRatePolicy
// args: Channel configuration arguments
// is_client: Flag indicating if this is a client-side policy
Chttp2PingRatePolicy::Chttp2PingRatePolicy(const ChannelArgs& args,
                                           bool is_client)
    : max_pings_without_data_sent_(
          // For clients, use configured value or default, but not less than 0
          is_client
              ? std::max(0,
                         args.GetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA)
                             .value_or(g_default_max_pings_without_data_sent))
              : 0),  // Servers don't send pings without data

      max_inflight_pings_(
          // Use configured value or default, but not less than 0
          std::max(0, args.GetInt(GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS)
                          .value_or(g_default_max_inflight_pings.value_or(
                              // Choose default based on whether multi-ping is enabled
                              IsMultipingEnabled() ? 100 : 1)))) {}

// Static method to set default values for ping rate policy
void Chttp2PingRatePolicy::SetDefaults(const ChannelArgs& args) {
  g_default_max_pings_without_data_sent =
      std::max(0, args.GetInt(GRPC_ARG_HTTP2_MAX_PINGS_WITHOUT_DATA)
                      .value_or(g_default_max_pings_without_data_sent));
  g_default_max_inflight_pings = args.GetInt(GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS);
}

// Checks if a new ping can be sent based on current state and limits
// next_allowed_ping_interval: Minimum required interval between pings
// inflight_pings: Current number of pings waiting for response
// Returns: Result indicating if ping can be sent or why it can't
Chttp2PingRatePolicy::RequestSendPingResult
Chttp2PingRatePolicy::RequestSendPing(Duration next_allowed_ping_interval,
                                      size_t inflight_pings) const {
  // Check inflight ping limits
  if (max_inflight_pings_ > 0) {
    if (!IsMaxInflightPingsStrictLimitEnabled()) {
      // Non-strict limit: can exceed by 1
      if (inflight_pings > static_cast<size_t>(max_inflight_pings_)) {
        return TooManyRecentPings{};
      }
    } else {
      // Strict limit: cannot reach or exceed
      if (inflight_pings >= static_cast<size_t>(max_inflight_pings_)) {
        return TooManyRecentPings{};
      }
    }
  }
  
  // Check minimum interval between pings
  const Timestamp next_allowed_ping =
      last_ping_sent_time_ + next_allowed_ping_interval;
  const Timestamp now = Timestamp::Now();
  if (next_allowed_ping > now) {
    return TooSoon{next_allowed_ping_interval, last_ping_sent_time_,
                   next_allowed_ping - now};
  }

  // Check pings-without-data limits
  if (max_pings_without_data_sent_ != 0 &&
      pings_before_data_sending_required_ == 0) {
    if (IsMaxPingsWoDataThrottleEnabled()) {
      // Throttle mode: enforce minimum interval when no data received
      const Timestamp next_allowed_ping =
          last_ping_sent_time_ + kThrottleIntervalWithoutDataSent;
      if (next_allowed_ping > now) {
        return TooSoon{kThrottleIntervalWithoutDataSent, last_ping_sent_time_,
                       next_allowed_ping - now};
      }
    } else {
      // Strict mode: no more pings allowed without data
      return TooManyRecentPings{};
    }
  }

  // All checks passed - ping can be sent
  return SendGranted{};
}

// Updates state when a ping is sent
void Chttp2PingRatePolicy::SentPing() {
  last_ping_sent_time_ = Timestamp::Now();
  if (pings_before_data_sending_required_ > 0) {
    --pings_before_data_sending_required_;
  }
}

// Updates state when data is received
void Chttp2PingRatePolicy::ReceivedDataFrame() {
  // Reset last ping time to allow immediate new pings
  last_ping_sent_time_ = Timestamp::InfPast();
}

// Resets the counter for pings before data is required
void Chttp2PingRatePolicy::ResetPingsBeforeDataRequired() {
  pings_before_data_sending_required_ = max_pings_without_data_sent_;
}

// Returns a debug string with current policy state
std::string Chttp2PingRatePolicy::GetDebugString() const {
  return absl::StrCat(
      "max_pings_without_data: ", max_pings_without_data_sent_,
      ", pings_before_data_required: ", pings_before_data_sending_required_,
      ", last_ping_sent_time_: ", last_ping_sent_time_.ToString());
}

// Output stream operator for RequestSendPingResult
std::ostream& operator<<(std::ostream& out,
                         const Chttp2PingRatePolicy::RequestSendPingResult& r) {
  Match(
      r, [&out](Chttp2PingRatePolicy::SendGranted) { out << "SendGranted"; },
      [&out](Chttp2PingRatePolicy::TooManyRecentPings) {
        out << "TooManyRecentPings";
      },
      [&out](Chttp2PingRatePolicy::TooSoon r) {
        out << "TooSoon: next_allowed="
            << r.next_allowed_ping_interval.ToString()
            << " last_ping_sent_time=" << r.last_ping.ToString()
            << " wait=" << r.wait.ToString();
      });
  return out;
}

}
```