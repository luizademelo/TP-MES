
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_CLIENT_SECURE_CREDENTIALS_H
#define GRPC_SRC_CPP_CLIENT_SECURE_CREDENTIALS_H

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpcpp/channel.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/support/client_interceptor.h>

namespace grpc {

namespace experimental {

grpc_sts_credentials_options StsCredentialsCppToCoreOptions(
    const StsCredentialsOptions& options);

}

class SecureChannelCredentials final : public grpc::ChannelCredentials {
 public:
  explicit SecureChannelCredentials(grpc_channel_credentials* c_creds)
      : ChannelCredentials(c_creds) {}
};

class SecureCallCredentials final : public grpc::CallCredentials {
 public:
  explicit SecureCallCredentials(grpc_call_credentials* c_creds)
      : CallCredentials(c_creds) {}
};

}

#endif
