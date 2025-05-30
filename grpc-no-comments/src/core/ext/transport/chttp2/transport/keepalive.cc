
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
KeepaliveManager::KeepaliveManager(
    std::unique_ptr<KeepAliveInterface> keep_alive_interface,
    Duration keepalive_timeout, const Duration keepalive_time)
    : keep_alive_interface_(std::move(keep_alive_interface)),
      keepalive_timeout_(keepalive_timeout),
      keepalive_time_(keepalive_time) {}

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
auto KeepaliveManager::TimeoutAndSendPing() {
  DCHECK(!data_received_in_last_cycle_);
  DCHECK(keepalive_timeout_ != Duration::Infinity());

  return AllOk<absl::Status>(Race(WaitForData(), WaitForKeepAliveTimeout()),
                             SendPingAndWaitForAck());
}
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

void KeepaliveManager::Spawn(Party* party) {
  if (!IsKeepAliveNeeded()) {
    KEEPALIVE_LOG << "Not spawning keepalive loop.";
    return;
  }
  keep_alive_spawned_ = true;

  party->Spawn("KeepAliveLoop", Loop([this]() {
                 return TrySeq(
                     Sleep(keepalive_time_),
                     [this]() { return MaybeSendKeepAlivePing(); },
                     []() -> LoopCtl<absl::Status> { return Continue(); });
               }),
               [](auto status) {
                 KEEPALIVE_LOG << "KeepAlive end with status: " << status;
               });
}
}
}
