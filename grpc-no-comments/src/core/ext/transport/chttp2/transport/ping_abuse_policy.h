// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_ABUSE_POLICY_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_ABUSE_POLICY_H

#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"

namespace grpc_core {

class Chttp2PingAbusePolicy {
 public:
  explicit Chttp2PingAbusePolicy(const ChannelArgs& args);

  static void SetDefaults(const ChannelArgs& args);

  GRPC_MUST_USE_RESULT bool ReceivedOnePing(bool transport_idle);

  void ResetPingStrikes();

  int TestOnlyMaxPingStrikes() const { return max_ping_strikes_; }
  Duration TestOnlyMinPingIntervalWithoutData() const {
    return min_recv_ping_interval_without_data_;
  }

  std::string GetDebugString(bool transport_idle) const;

 private:
  Duration RecvPingIntervalWithoutData(bool transport_idle) const;

  Timestamp last_ping_recv_time_ = Timestamp::InfPast();
  const Duration min_recv_ping_interval_without_data_;
  int ping_strikes_ = 0;
  const int max_ping_strikes_;
};

}

#endif
