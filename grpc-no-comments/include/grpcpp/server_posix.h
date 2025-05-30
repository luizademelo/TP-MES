
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_SERVER_POSIX_H
#define GRPCPP_SERVER_POSIX_H

#include <grpc/support/port_platform.h>
#include <grpcpp/server.h>

#include <memory>

namespace grpc {

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

void AddInsecureChannelFromFd(Server* server, int fd);

#endif

}

#endif
