// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_CALLBACKS_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_CALLBACKS_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <algorithm>
#include <optional>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "absl/hash/hash.h"
#include "absl/random/bit_gen_ref.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/time.h"

namespace grpc_core {

class Chttp2PingCallbacks {
 public:

  using Callback = absl::AnyInvocable<void()>;

  void RequestPing() { ping_requested_ = true; }

  void OnPing(Callback on_start, Callback on_ack);

  void OnPingAck(Callback on_ack);

  GRPC_MUST_USE_RESULT uint64_t StartPing(absl::BitGenRef bitgen);
  bool AckPing(uint64_t id,
               grpc_event_engine::experimental::EventEngine* event_engine);

  void CancelAll(grpc_event_engine::experimental::EventEngine* event_engine);

  bool ping_requested() const { return ping_requested_; }

  size_t pings_inflight() const { return inflight_.size(); }

  bool started_new_ping_without_setting_timeout() const {
    return started_new_ping_without_setting_timeout_;
  }

  std::optional<uint64_t> OnPingTimeout(
      Duration ping_timeout,
      grpc_event_engine::experimental::EventEngine* event_engine,
      Callback callback);

 private:
  using CallbackVec = std::vector<Callback>;
  struct InflightPing {
    grpc_event_engine::experimental::EventEngine::TaskHandle on_timeout =
        grpc_event_engine::experimental::EventEngine::TaskHandle::kInvalid;
    CallbackVec on_ack;
  };
  absl::flat_hash_map<uint64_t, InflightPing> inflight_;
  uint64_t most_recent_inflight_ = 0;
  bool ping_requested_ = false;
  bool started_new_ping_without_setting_timeout_ = false;
  CallbackVec on_start_;
  CallbackVec on_ack_;
};

}

#endif
