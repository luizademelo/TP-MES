
// Copyright 2016 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_posix.h>
#include <grpc/grpc_security.h>
#include <grpcpp/server.h>
#include <grpcpp/server_posix.h>

namespace grpc {

#ifdef GPR_SUPPORT_CHANNELS_FROM_FD

void AddInsecureChannelFromFd(grpc::Server* server, int fd) {
  grpc_server_credentials* creds = grpc_insecure_server_credentials_create();
  grpc_server_add_channel_from_fd(server->c_server(), fd, creds);
  grpc_server_credentials_release(creds);
}

#endif

}
