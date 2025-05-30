
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_KEEPALIVE_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_KEEPALIVE_H

#include "absl/status/status.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/promise.h"

namespace grpc_core {
namespace http2 {

#define KEEPALIVE_LOG VLOG(2)

class KeepAliveInterface {
 public:

  virtual Promise<absl::Status> SendPingAndWaitForAck() = 0;

  virtual Promise<absl::Status> OnKeepAliveTimeout() = 0;

  virtual bool NeedToSendKeepAlivePing() = 0;
  virtual ~KeepAliveInterface() = default;
};

class KeepaliveManager {
 public:
  KeepaliveManager(std::unique_ptr<KeepAliveInterface> keep_alive_interface,
                   Duration keepalive_timeout, Duration keepalive_time);

  void Spawn(Party* party);

  void GotData() {
    if (keep_alive_timeout_triggered_) {
      KEEPALIVE_LOG
          << "KeepAlive timeout triggered. Not setting data_received_ to true";
      return;
    }
    KEEPALIVE_LOG << "Data received. Setting data_received_ to true";
    data_received_in_last_cycle_ = true;
    auto waker = std::move(waker_);

    waker.Wakeup();
  }
  void SetKeepAliveTimeout(Duration keepalive_timeout) {
    keepalive_timeout_ = keepalive_timeout;
  }

 private:

  auto WaitForKeepAliveTimeout();

  auto TimeoutAndSendPing();

  auto MaybeSendKeepAlivePing();

  auto WaitForData() {
    return [this]() -> Poll<absl::Status> {
      if (data_received_in_last_cycle_) {
        KEEPALIVE_LOG << "WaitForData: Data received. Poll resolved";
        return absl::OkStatus();
      } else {
        KEEPALIVE_LOG << "WaitForData: Data not received. Poll pending";
        waker_ = GetContext<Activity>()->MakeNonOwningWaker();
        return Pending{};
      }
    };
  }
  auto SendPingAndWaitForAck() {
    DCHECK_EQ(data_received_in_last_cycle_, false);
    return keep_alive_interface_->SendPingAndWaitForAck();
  }

  bool NeedToSendKeepAlivePing() {
    return (!data_received_in_last_cycle_) &&
           (keep_alive_interface_->NeedToSendKeepAlivePing());
  }

  bool IsKeepAliveNeeded() {
    return (keepalive_time_ != Duration::Infinity() && !keep_alive_spawned_);
  }

  std::unique_ptr<KeepAliveInterface> keep_alive_interface_;

  Duration keepalive_timeout_;
  const Duration keepalive_time_;
  bool data_received_in_last_cycle_ = false;
  bool keep_alive_timeout_triggered_ = false;
  bool keep_alive_spawned_ = false;
  Waker waker_;
};

}
}

#endif
