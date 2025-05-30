
// Copyright 2017 gRPC authors.

#ifndef GRPCPP_IMPL_CHANNEL_ARGUMENT_OPTION_H
#define GRPCPP_IMPL_CHANNEL_ARGUMENT_OPTION_H

#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/support/channel_arguments.h>

#include <map>
#include <memory>

namespace grpc {

std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, const std::string& value);
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, int value);
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, void* value);

}

#endif
