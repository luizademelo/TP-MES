// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_RATE_POLICY_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_PING_RATE_POLICY_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <iosfwd>
#include <string>
#include <variant>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"

namespace grpc_core {

#define GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS "grpc.http2.max_inflight_pings"

class Chttp2PingRatePolicy {
 public:
  explicit Chttp2PingRatePolicy(const ChannelArgs& args, bool is_client);

  static void SetDefaults(const ChannelArgs& args);

  struct SendGranted {
    bool operator==(const SendGranted&) const { return true; }
  };
  struct TooManyRecentPings {
    bool operator==(const TooManyRecentPings&) const { return true; }
  };
  struct TooSoon {
    Duration next_allowed_ping_interval;
    Timestamp last_ping;
    Duration wait;
    bool operator==(const TooSoon& other) const {
      return next_allowed_ping_interval == other.next_allowed_ping_interval &&
             last_ping == other.last_ping && wait == other.wait;
    }
  };
  using RequestSendPingResult =
      std::variant<SendGranted, TooManyRecentPings, TooSoon>;

  RequestSendPingResult RequestSendPing(Duration next_allowed_ping_interval,
                                        size_t inflight_pings) const;

  void SentPing();

  void ResetPingsBeforeDataRequired();

  void ReceivedDataFrame();
  std::string GetDebugString() const;

  int TestOnlyMaxPingsWithoutData() const {
    return max_pings_without_data_sent_;
  }

 private:
  const int max_pings_without_data_sent_;
  const int max_inflight_pings_;
  int pings_before_data_sending_required_ = 0;
  Timestamp last_ping_sent_time_ = Timestamp::InfPast();
};

std::ostream& operator<<(std::ostream& out,
                         const Chttp2PingRatePolicy::RequestSendPingResult& r);

}

#endif
