
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_GRPCPP_H
#define GRPCPP_GRPCPP_H

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/create_channel_posix.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/server_posix.h>
#include <grpcpp/version_info.h>

namespace grpc {

std::string Version();
}

#endif
