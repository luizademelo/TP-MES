Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include <algorithm>
#include <optional>

#include "absl/strings/str_cat.h"

namespace grpc_core {

namespace {
// Default minimum allowed interval between receiving pings when no data is being sent
Duration g_default_min_recv_ping_interval_without_data = Duration::Minutes(5);
// Default maximum number of excessive pings (ping strikes) allowed before taking action
int g_default_max_ping_strikes = 2;
}

// Constructor for Chttp2PingAbusePolicy that initializes policy parameters from channel args
// Args:
//   args: Channel arguments containing configuration values
Chttp2PingAbusePolicy::Chttp2PingAbusePolicy(const ChannelArgs& args)
    : min_recv_ping_interval_without_data_(std::max(
          Duration::Zero(),
          args.GetDurationFromIntMillis(
                  GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS)
              .value_or(g_default_min_recv_ping_interval_without_data))),
      max_ping_strikes_(
          std::max(0, args.GetInt(GRPC_ARG_HTTP2_MAX_PING_STRIKES)
                          .value_or(g_default_max_ping_strikes))) {}

// Static method to update default policy values from channel args
// Args:
//   args: Channel arguments containing new default configuration values
void Chttp2PingAbusePolicy::SetDefaults(const ChannelArgs& args) {
  g_default_max_ping_strikes =
      std::max(0, args.GetInt(GRPC_ARG_HTTP2_MAX_PING_STRIKES)
                      .value_or(g_default_max_ping_strikes));
  g_default_min_recv_ping_interval_without_data =
      std::max(Duration::Zero(),
               args.GetDurationFromIntMillis(
                       GRPC_ARG_HTTP2_MIN_RECV_PING_INTERVAL_WITHOUT_DATA_MS)
                   .value_or(g_default_min_recv_ping_interval_without_data));
}

// Processes an incoming ping and determines if it constitutes abuse
// Args:
//   transport_idle: Whether the transport is currently idle (no data being sent)
// Returns:
//   true if the ping should be considered abusive, false otherwise
bool Chttp2PingAbusePolicy::ReceivedOnePing(bool transport_idle) {
  const Timestamp now = Timestamp::Now();
  // Calculate when the next ping would be allowed based on current state
  const Timestamp next_allowed_ping =
      last_ping_recv_time_ + RecvPingIntervalWithoutData(transport_idle);
  last_ping_recv_time_ = now;
  // If ping arrives too early, count it as a strike
  if (next_allowed_ping <= now) return false;

  ++ping_strikes_;
  // Consider it abuse if we've exceeded max strikes and strikes are being tracked
  return ping_strikes_ > max_ping_strikes_ && max_ping_strikes_ != 0;
}

// Generates a debug string showing current policy state
// Args:
//   transport_idle: Current idle state of the transport
// Returns:
//   Formatted string containing policy state information
std::string Chttp2PingAbusePolicy::GetDebugString(bool transport_idle) const {
  return absl::StrCat(
      "now=", Timestamp::Now().ToString(), " transport_idle=", transport_idle,
      " next_allowed_ping=",
      (last_ping_recv_time_ + RecvPingIntervalWithoutData(transport_idle))
          .ToString(),
      " ping_strikes=", ping_strikes_);
}

// Gets the minimum allowed interval between pings based on transport state
// Args:
//   transport_idle: Whether the transport is currently idle
// Returns:
//   Duration representing the minimum allowed interval between pings
Duration Chttp2PingAbusePolicy::RecvPingIntervalWithoutData(
    bool transport_idle) const {
  if (transport_idle) {
    // More lenient interval when transport is idle
    return Duration::Hours(2);
  }
  return min_recv_ping_interval_without_data_;
}

// Resets the ping strike counter and last received time
void Chttp2PingAbusePolicy::ResetPingStrikes() {
  last_ping_recv_time_ = Timestamp::InfPast();
  ping_strikes_ = 0;
}

}  // namespace grpc_core
```