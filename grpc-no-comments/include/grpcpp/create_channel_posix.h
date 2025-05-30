
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_CREATE_CHANNEL_POSIX_H
#define GRPCPP_CREATE_CHANNEL_POSIX_H

#include <grpc/support/port_platform.h>
#include <grpcpp/channel.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>

namespace grpc {

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

std::shared_ptr<grpc::Channel> CreateInsecureChannelFromFd(
    const std::string& target, int fd);

std::shared_ptr<grpc::Channel> CreateCustomInsecureChannelFromFd(
    const std::string& target, int fd, const grpc::ChannelArguments& args);

namespace experimental {

std::shared_ptr<grpc::Channel>
CreateCustomInsecureChannelWithInterceptorsFromFd(
    const std::string& target, int fd, const grpc::ChannelArguments& args,
    std::vector<
        std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>>
        interceptor_creators);

}

#endif

}

#endif
