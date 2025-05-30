
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_CLIENT_CREATE_CHANNEL_INTERNAL_H
#define GRPC_SRC_CPP_CLIENT_CREATE_CHANNEL_INTERNAL_H

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/support/client_interceptor.h>

#include <memory>
#include <string>
#include <vector>

namespace grpc {

std::shared_ptr<Channel> CreateChannelInternal(
    const std::string& host, grpc_channel* c_channel,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

}

#endif
