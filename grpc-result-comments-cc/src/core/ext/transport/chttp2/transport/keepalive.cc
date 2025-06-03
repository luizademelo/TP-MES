Here's the commented version of the code:

```c++
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/keepalive.h"

#include "src/core/lib/promise/all_ok.h"
#include "src/core/lib/promise/if.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"

namespace grpc_core {
namespace http2 {

// Constructor for KeepaliveManager
// Parameters:
//   keep_alive_interface: Interface for keepalive operations
//   keepalive_timeout: Duration after which timeout occurs if no data received
//   keepalive_time: Interval between keepalive pings
KeepaliveManager::KeepaliveManager(
    std::unique_ptr<KeepAliveInterface> keep_alive_interface,
    Duration keepalive_timeout, const Duration keepalive_time)
    : keep_alive_interface_(std::move(keep_alive_interface)),
      keepalive_timeout_(keepalive_timeout),
      keepalive_time_(keepalive_time) {}

// Waits for keepalive timeout period and checks if data was received
// Returns:
//   OkStatus if data was received during timeout period
//   CancelledError if timeout occurs without receiving data
auto KeepaliveManager::WaitForKeepAliveTimeout() {
  return AssertResultType<absl::Status>(
      TrySeq(Sleep(keepalive_timeout_), [this] {
        return If(
            data_received_in_last_cycle_,
            [] {
              KEEPALIVE_LOG << "Keepalive timeout triggered but "
                            << "received data. Resolving with ok status";
              return Immediate(absl::OkStatus());
            },
            [this] {
              KEEPALIVE_LOG << "Keepalive timeout triggered and no "
                               "data received. Triggering keepalive timeout.";

              keep_alive_timeout_triggered_ = true;
              return TrySeq(keep_alive_interface_->OnKeepAliveTimeout(), [] {
                return absl::CancelledError("keepalive timeout");
              });
            });
      }));
}

// Handles timeout scenario and sends ping
// Preconditions:
//   - No data received in last cycle
//   - keepalive_timeout_ is not infinite
// Returns:
//   Result of racing between waiting for data and timeout,
//   combined with sending ping and waiting for ack
auto KeepaliveManager::TimeoutAndSendPing() {
  DCHECK(!data_received_in_last_cycle_);
  DCHECK(keepalive_timeout_ != Duration::Infinity());

  return AllOk<absl::Status>(Race(WaitForData(), WaitForKeepAliveTimeout()),
                             SendPingAndWaitForAck());
}

// Conditionally sends keepalive ping if needed
// Returns:
//   OkStatus if no ping was needed or if ping was successful
//   Error status if ping failed
auto KeepaliveManager::MaybeSendKeepAlivePing() {
  KEEPALIVE_LOG << "KeepaliveManager::MaybeSendKeepAlivePing";
  return AssertResultType<absl::Status>(
      TrySeq(If(
                 NeedToSendKeepAlivePing(),
                 [this]() {
                   return If(
                       keepalive_timeout_ != Duration::Infinity(),
                       [this] { return TimeoutAndSendPing(); },
                       [this] { return SendPingAndWaitForAck(); });
                 },
                 []() { return Immediate(absl::OkStatus()); }),
             [this] {
               data_received_in_last_cycle_ = false;
               return Immediate(absl::OkStatus());
             }));
}

// Starts the keepalive loop if keepalive is needed
// Parameters:
//   party: The party (thread/execution context) to spawn the keepalive loop on
void KeepaliveManager::Spawn(Party* party) {
  if (!IsKeepAliveNeeded()) {
    KEEPALIVE_LOG << "Not spawning keepalive loop.";
    return;
  }
  keep_alive_spawned_ = true;

  // Spawns a loop that periodically sends keepalive pings
  party->Spawn("KeepAliveLoop", Loop([this]() {
                 return TrySeq(
                     Sleep(keepalive_time_),  // Wait for keepalive interval
                     [this]() { return MaybeSendKeepAlivePing(); },  // Send ping if needed
                     []() -> LoopCtl<absl::Status> { return Continue(); });  // Continue loop
               }),
               [](auto status) {
                 KEEPALIVE_LOG << "KeepAlive end with status: " << status;
               });
}

}  // namespace http2
}  // namespace grpc_core
```

The comments explain:
1. The overall purpose of each method
2. Key parameters and their meanings
3. Return values and their significance
4. Important preconditions (checked via DCHECK)
5. The control flow within complex promise chains
6. The logging behavior
7. The overall keepalive loop mechanism

The comments are designed to help future developers understand:
- When and why keepalive pings are sent
- How timeouts are handled
- The state machine behavior
- Error handling cases
- The overall architecture of the keepalive system