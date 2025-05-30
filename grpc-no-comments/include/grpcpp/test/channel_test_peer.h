
// Copyright 2020 gRPC authors.

#ifndef GRPCPP_TEST_CHANNEL_TEST_PEER_H
#define GRPCPP_TEST_CHANNEL_TEST_PEER_H

#include <grpcpp/channel.h>

namespace grpc {
namespace testing {

class ChannelTestPeer {
 public:
  explicit ChannelTestPeer(Channel* channel) : channel_(channel) {}

  grpc_channel* channel() const { return channel_->c_channel_; }
  int registered_calls() const;

 private:
  Channel* channel_;
};

}
}

#endif
