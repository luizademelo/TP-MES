
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_PROMISE_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_PROMISE_H

#include <memory>

#include "src/core/ext/transport/chttp2/transport/ping_abuse_policy.h"
#include "src/core/ext/transport/chttp2/transport/ping_callbacks.h"
#include "src/core/ext/transport/chttp2/transport/ping_rate_policy.h"
#include "src/core/lib/promise/inter_activity_latch.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/util/shared_bit_gen.h"
#include "src/core/util/time.h"

namespace grpc_core {
namespace http2 {

class PingInterface {
 public:
  struct SendPingArgs {
    bool ack = false;

    uint64_t opaque_data = 0;
  };

  virtual Promise<absl::Status> SendPing(SendPingArgs args) = 0;

  virtual Promise<absl::Status> TriggerWrite() = 0;

  virtual Promise<absl::Status> PingTimeout() = 0;
  virtual ~PingInterface() = default;
};

class PingManager {
 public:
  PingManager(const ChannelArgs& channel_args,
              std::unique_ptr<PingInterface> ping_interface,
              std::shared_ptr<grpc_event_engine::experimental::EventEngine>
                  event_engine);

  Promise<absl::Status> MaybeSendPing(Duration next_allowed_ping_interval,
                                      Duration ping_timeout);

  void ReceivedDataFrame() { ping_rate_policy_.ReceivedDataFrame(); }

  bool NotifyPingAbusePolicy(const bool transport_idle) {
    return ping_abuse_policy_.ReceivedOnePing(transport_idle);
  }

  void ResetPingClock(bool is_client) {
    if (!is_client) {
      ping_abuse_policy_.ResetPingStrikes();
    }
    ping_rate_policy_.ResetPingsBeforeDataRequired();
  }

  auto RequestPing(absl::AnyInvocable<void()> on_initiate) {
    return ping_callbacks_.RequestPing(std::move(on_initiate));
  }

  auto WaitForPingAck() { return ping_callbacks_.WaitForPingAck(); }

  void CancelCallbacks() { ping_callbacks_.CancelCallbacks(); }

  uint64_t StartPing() { return ping_callbacks_.StartPing(); }
  bool PingRequested() { return ping_callbacks_.PingRequested(); }
  bool AckPing(uint64_t id) { return ping_callbacks_.AckPing(id); }
  size_t CountPingInflight() { return ping_callbacks_.CountPingInflight(); }

 private:
  class PingPromiseCallbacks {
   public:
    explicit PingPromiseCallbacks(
        std::shared_ptr<grpc_event_engine::experimental::EventEngine>
            event_engine)
        : event_engine_(event_engine) {}
    Promise<absl::Status> RequestPing(absl::AnyInvocable<void()> on_initiate);
    Promise<absl::Status> WaitForPingAck();
    void CancelCallbacks() { ping_callbacks_.CancelAll(event_engine_.get()); }
    uint64_t StartPing() { return ping_callbacks_.StartPing(SharedBitGen()); }
    bool PingRequested() { return ping_callbacks_.ping_requested(); }
    bool AckPing(uint64_t id) {
      return ping_callbacks_.AckPing(id, event_engine_.get());
    }
    size_t CountPingInflight() { return ping_callbacks_.pings_inflight(); }

    auto PingTimeout(Duration ping_timeout) {
      std::shared_ptr<InterActivityLatch<void>> latch =
          std::make_shared<InterActivityLatch<void>>();
      auto timeout_cb = [latch]() { latch->Set(); };
      auto id = ping_callbacks_.OnPingTimeout(ping_timeout, event_engine_.get(),
                                              std::move(timeout_cb));
      DCHECK(id.has_value());
      VLOG(2) << "Ping timeout of duration: " << ping_timeout
              << " initiated for ping id: " << *id;
      return Map(latch->Wait(), [latch](Empty) { return absl::OkStatus(); });
    }

   private:
    Chttp2PingCallbacks ping_callbacks_;
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_;
  };

  PingPromiseCallbacks ping_callbacks_;
  Chttp2PingAbusePolicy ping_abuse_policy_;
  Chttp2PingRatePolicy ping_rate_policy_;
  bool delayed_ping_spawned_ = false;
  std::unique_ptr<PingInterface> ping_interface_;

  void TriggerDelayedPing(Duration wait);
  bool NeedToPing(Duration next_allowed_ping_interval);
  void SpawnTimeout(Duration ping_timeout, uint64_t opaque_data);

  void SentPing() { ping_rate_policy_.SentPing(); }
};
}
}

#endif
