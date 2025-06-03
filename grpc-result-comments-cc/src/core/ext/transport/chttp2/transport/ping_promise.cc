Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_promise.h"

#include "src/core/lib/promise/if.h"
#include "src/core/lib/promise/latch.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/util/match.h"
#include "src/core/util/time.h"

namespace grpc_core {
namespace http2 {
using SendPingArgs = ::grpc_core::http2::PingInterface::SendPingArgs;
using Callback = absl::AnyInvocable<void()>;
using grpc_event_engine::experimental::EventEngine;

// Macro for conditional logging of ping-related events
// Logs when any of the specified trace flags are enabled
#define PING_LOG                                           \
  LOG_IF(INFO, (GRPC_TRACE_FLAG_ENABLED(http) ||           \
                GRPC_TRACE_FLAG_ENABLED(bdp_estimator) ||  \
                GRPC_TRACE_FLAG_ENABLED(http_keepalive) || \
                GRPC_TRACE_FLAG_ENABLED(http2_ping)))

// Requests a ping to be sent and returns a promise that completes when the ping is acknowledged
Promise<absl::Status> PingManager::PingPromiseCallbacks::RequestPing(
    Callback on_initiate) {
  // Create a latch to track ping acknowledgment
  std::shared_ptr<Latch<void>> latch = std::make_shared<Latch<void>>();
  auto on_ack = [latch]() { latch->Set(); };
  // Register both initiation and acknowledgment callbacks
  ping_callbacks_.OnPing(std::move(on_initiate), std::move(on_ack));
  // Return a promise that waits for the latch to be set (ping acknowledged)
  return Map(latch->Wait(), [latch](Empty) { return absl::OkStatus(); });
}

// Returns a promise that completes when the next ping is acknowledged
Promise<absl::Status> PingManager::PingPromiseCallbacks::WaitForPingAck() {
  // Create a latch to track ping acknowledgment
  std::shared_ptr<Latch<void>> latch = std::make_shared<Latch<void>>();
  auto on_ack = [latch]() { latch->Set(); };
  // Register acknowledgment callback
  ping_callbacks_.OnPingAck(std::move(on_ack));
  // Return a promise that waits for the latch to be set (ping acknowledged)
  return Map(latch->Wait(), [latch](Empty) { return absl::OkStatus(); });
}

// Constructor for PingManager
PingManager::PingManager(const ChannelArgs& channel_args,
                         std::unique_ptr<PingInterface> ping_interface,
                         std::shared_ptr<EventEngine> event_engine)
    : ping_callbacks_(event_engine),  // Initialize ping callbacks with event engine
      ping_abuse_policy_(channel_args),  // Initialize ping abuse policy with channel args
      ping_rate_policy_(channel_args, true),  // Initialize ping rate policy with channel args
      ping_interface_(std::move(ping_interface)) {}  // Take ownership of ping interface

// Triggers a ping after a specified delay
void PingManager::TriggerDelayedPing(Duration wait) {
  // If there's already a delayed ping scheduled, do nothing
  if (delayed_ping_spawned_) {
    return;
  }
  delayed_ping_spawned_ = true;
  // Spawn a new asynchronous task to handle the delayed ping
  GetContext<Party>()->Spawn(
      "DelayedPing",
      [this, wait]() mutable {
        VLOG(2) << "Scheduling delayed ping after wait=" << wait;
        // Sequence: wait for the delay, then trigger a write
        return AssertResultType<absl::Status>(TrySeq(
            Sleep(wait),
            [this]() mutable { return ping_interface_->TriggerWrite(); }));
      },
      // Reset the delayed_ping_spawned_ flag when done
      [this](auto) { delayed_ping_spawned_ = false; });
}

// Determines if a ping should be sent based on ping request status and rate limiting policies
bool PingManager::NeedToPing(Duration next_allowed_ping_interval) {
  // If no ping has been requested, no need to send one
  if (!ping_callbacks_.PingRequested()) {
    return false;
  }

  // Check ping rate policy to determine if we can send a ping now
  return Match(
      ping_rate_policy_.RequestSendPing(next_allowed_ping_interval,
                                        ping_callbacks_.CountPingInflight()),
      // Case: Ping sending is granted
      [this](Chttp2PingRatePolicy::SendGranted) {
        PING_LOG << "CLIENT" << "[" << "PH2"
                 << "]: Ping sent" << ping_rate_policy_.GetDebugString();
        return true;
      },
      // Case: Too many pings recently sent
      [this](Chttp2PingRatePolicy::TooManyRecentPings) {
        PING_LOG << "CLIENT" << "[" << "PH2"
                 << "]: Ping delayed too many recent pings: "
                 << ping_rate_policy_.GetDebugString();
        return false;
      },
      // Case: Need to wait before sending next ping
      [this](Chttp2PingRatePolicy::TooSoon too_soon) mutable {
        PING_LOG << "]: Ping delayed not enough time elapsed since last "
                    "ping. Last ping:"
                 << too_soon.last_ping
                 << ", minimum wait:" << too_soon.next_allowed_ping_interval
                 << ", need to wait:" << too_soon.wait;
        // Schedule a delayed ping
        TriggerDelayedPing(too_soon.wait);
        return false;
      });
}

// Spawns a task that will trigger a timeout if the ping isn't acknowledged in time
void PingManager::SpawnTimeout(Duration ping_timeout,
                               const uint64_t opaque_data) {
  GetContext<Party>()->Spawn(
      "PingTimeout",
      [this, ping_timeout, opaque_data]() {
        // Race between waiting for timeout and waiting for acknowledgment
        return AssertResultType<absl::Status>(Race(
            // Timeout path: wait for timeout duration, then handle timeout
            TrySeq(ping_callbacks_.PingTimeout(ping_timeout),
                   [this, opaque_data]() mutable {
                     VLOG(2) << " Ping ack not received for id=" << opaque_data
                             << ". Ping timeout triggered.";
                     return ping_interface_->PingTimeout();
                   }),
            // Success path: wait for ping acknowledgment
            ping_callbacks_.WaitForPingAck()));
      },
      // Cleanup callback (does nothing in this case)
      [](auto) {});
}

// Main method for sending pings if needed
Promise<absl::Status> PingManager::MaybeSendPing(
    Duration next_allowed_ping_interval, Duration ping_timeout) {
  return If(
      // First check if we need to send a ping
      NeedToPing(next_allowed_ping_interval),
      // If we need to send a ping:
      [this, ping_timeout]() mutable {
        // Generate a unique ID for this ping
        const uint64_t opaque_data = ping_callbacks_.StartPing();
        return AssertResultType<absl::Status>(
            // Sequence: send the ping, then handle timeout and logging
            TrySeq(ping_interface_->SendPing(SendPingArgs{false, opaque_data}),
                   [this, ping_timeout, opaque_data]() {
                     VLOG(2) << "Ping Sent with id: " << opaque_data;
                     // Start timeout tracking
                     SpawnTimeout(ping_timeout, opaque_data);
                     // Update ping statistics
                     SentPing();
                     return absl::OkStatus();
                   }));
      },
      // If we don't need to send a ping, return immediately
      []() { return Immediate(absl::OkStatus()); });
}
}
}
```