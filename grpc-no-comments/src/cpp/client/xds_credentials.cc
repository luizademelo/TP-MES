
// Copyright 2020 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/credentials.h>

#include <memory>

#include "absl/log/check.h"

namespace grpc {
class XdsChannelCredentialsImpl final : public ChannelCredentials {
 public:
  explicit XdsChannelCredentialsImpl(
      const std::shared_ptr<ChannelCredentials>& fallback_creds)
      : ChannelCredentials(
            grpc_xds_credentials_create(fallback_creds->c_creds_)) {
    CHECK_NE(fallback_creds->c_creds_, nullptr);
  }
};

std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds) {
  CHECK_NE(fallback_creds, nullptr);
  return std::make_shared<XdsChannelCredentialsImpl>(fallback_creds);
}

namespace experimental {

std::shared_ptr<ChannelCredentials> XdsCredentials(
    const std::shared_ptr<ChannelCredentials>& fallback_creds) {
  return grpc::XdsCredentials(fallback_creds);
}

}
}
