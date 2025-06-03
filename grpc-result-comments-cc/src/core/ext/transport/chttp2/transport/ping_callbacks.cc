Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/meta/type_traits.h"
#include "absl/random/distributions.h"

namespace grpc_core {

// Registers callbacks to be invoked when a ping starts and when it's acknowledged.
// Sets the ping_requested_ flag to true indicating there's a pending ping request.
void Chttp2PingCallbacks::OnPing(Callback on_start, Callback on_ack) {
  on_start_.emplace_back(std::move(on_start));
  on_ack_.emplace_back(std::move(on_ack));
  ping_requested_ = true;
}

// Registers a callback to be invoked when a ping is acknowledged.
// If there's an inflight ping, adds the callback to its ack handlers.
// Otherwise, sets ping_requested_ flag and adds to general ack handlers.
void Chttp2PingCallbacks::OnPingAck(Callback on_ack) {
  auto it = inflight_.find(most_recent_inflight_);
  if (it != inflight_.end()) {
    it->second.on_ack.emplace_back(std::move(on_ack));
    return;
  }
  ping_requested_ = true;
  on_ack_.emplace_back(std::move(on_ack));
}

// Starts a new ping with a random unique ID.
// Moves all pending start callbacks to the new ping and executes them.
// Clears the pending ack callbacks and associates them with the new ping.
// Returns the generated ping ID.
uint64_t Chttp2PingCallbacks::StartPing(absl::BitGenRef bitgen) {
  uint64_t id;
  // Generate a unique ping ID that's not currently in use
  do {
    id = absl::Uniform<uint64_t>(bitgen);
  } while (inflight_.contains(id));
  
  // Move all pending start callbacks and clear the original vector
  CallbackVec cbs = std::move(on_start_);
  CallbackVec().swap(on_start_);
  
  // Create new inflight ping and move pending ack callbacks to it
  InflightPing inflight;
  inflight.on_ack.swap(on_ack_);
  
  // Mark that we've started a new ping without setting timeout yet
  started_new_ping_without_setting_timeout_ = true;
  
  // Store the new ping and update most recent ID
  inflight_.emplace(id, std::move(inflight));
  most_recent_inflight_ = id;
  ping_requested_ = false;
  
  // Execute all start callbacks
  for (auto& cb : cbs) {
    cb();
  }
  return id;
}

// Acknowledges a ping with the given ID.
// Cancels any pending timeout task for this ping.
// Executes all registered ack callbacks for this ping.
// Returns true if the ping was found and acknowledged, false otherwise.
bool Chttp2PingCallbacks::AckPing(
    uint64_t id, grpc_event_engine::experimental::EventEngine* event_engine) {
  auto ping = inflight_.extract(id);
  if (ping.empty()) return false;
  
  // Cancel timeout callback if one was set
  if (ping.mapped().on_timeout !=
      grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid) {
    event_engine->Cancel(ping.mapped().on_timeout);
  }
  
  // Execute all ack callbacks
  for (auto& cb : ping.mapped().on_ack) {
    cb();
  }
  return true;
}

// Cancels all pending ping operations.
// Clears all start and ack callbacks.
// Cancels all timeout tasks for inflight pings.
void Chttp2PingCallbacks::CancelAll(
    grpc_event_engine::experimental::EventEngine* event_engine) {
  // Clear all pending start and ack callbacks
  CallbackVec().swap(on_start_);
  CallbackVec().swap(on_ack_);
  
  // For each inflight ping, clear its callbacks and cancel timeout
  for (auto& cbs : inflight_) {
    CallbackVec().swap(cbs.second.on_ack);
    if (cbs.second.on_timeout !=
        grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid) {
      event_engine->Cancel(std::exchange(
          cbs.second.on_timeout,
          grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid));
    }
  }
  ping_requested_ = false;
}

// Sets a timeout for the most recent inflight ping.
// Schedules the provided callback to run after the specified duration.
// Returns the ping ID if successful, or nullopt if no recent ping exists.
std::optional<uint64_t> Chttp2PingCallbacks::OnPingTimeout(
    Duration ping_timeout,
    grpc_event_engine::experimental::EventEngine* event_engine,
    Callback callback) {
  // Verify we have a new ping that needs timeout setup
  CHECK(started_new_ping_without_setting_timeout_);
  started_new_ping_without_setting_timeout_ = false;
  
  // Find the most recent ping and schedule its timeout
  auto it = inflight_.find(most_recent_inflight_);
  if (it == inflight_.end()) return std::nullopt;
  
  it->second.on_timeout =
      event_engine->RunAfter(ping_timeout, std::move(callback));
  return most_recent_inflight_;
}

}
```