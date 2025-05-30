
// Copyright 2015 gRPC authors.

#include "src/cpp/client/create_channel_internal.h"

#include <grpcpp/channel.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace grpc {

std::shared_ptr<Channel> CreateChannelInternal(
    const std::string& host, grpc_channel* c_channel,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators) {
  return std::shared_ptr<Channel>(
      new Channel(host, c_channel, std::move(interceptor_creators)));
}

}
