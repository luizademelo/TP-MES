
// Copyright 2020 gRPC authors.

#include <grpcpp/channel.h>
#include <grpcpp/test/channel_test_peer.h>

#include "src/core/lib/surface/channel.h"

namespace grpc {
namespace testing {

int ChannelTestPeer::registered_calls() const {
  return grpc_core::Channel::FromC(channel_->c_channel_)
      ->TestOnlyRegisteredCalls();
}

}
}
