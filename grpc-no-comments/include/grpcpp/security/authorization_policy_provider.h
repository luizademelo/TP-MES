// Copyright 2021 gRPC authors.

#ifndef GRPCPP_SECURITY_AUTHORIZATION_POLICY_PROVIDER_H
#define GRPCPP_SECURITY_AUTHORIZATION_POLICY_PROVIDER_H

#include <grpc/grpc_security.h>
#include <grpc/status.h>
#include <grpcpp/support/status.h>

#include <memory>

namespace grpc {
namespace experimental {

class AuthorizationPolicyProviderInterface {
 public:
  virtual ~AuthorizationPolicyProviderInterface() = default;
  virtual grpc_authorization_policy_provider* c_provider() = 0;
};

class StaticDataAuthorizationPolicyProvider
    : public AuthorizationPolicyProviderInterface {
 public:
  static std::shared_ptr<StaticDataAuthorizationPolicyProvider> Create(
      const std::string& authz_policy, grpc::Status* status);

  explicit StaticDataAuthorizationPolicyProvider(
      grpc_authorization_policy_provider* provider)
      : c_provider_(provider) {}

  ~StaticDataAuthorizationPolicyProvider() override;

  grpc_authorization_policy_provider* c_provider() override {
    return c_provider_;
  }

 private:
  grpc_authorization_policy_provider* c_provider_ = nullptr;
};

class FileWatcherAuthorizationPolicyProvider
    : public AuthorizationPolicyProviderInterface {
 public:
  static std::shared_ptr<FileWatcherAuthorizationPolicyProvider> Create(
      const std::string& authz_policy_path, unsigned int refresh_interval_sec,
      grpc::Status* status);

  explicit FileWatcherAuthorizationPolicyProvider(
      grpc_authorization_policy_provider* provider)
      : c_provider_(provider) {}

  ~FileWatcherAuthorizationPolicyProvider() override;

  grpc_authorization_policy_provider* c_provider() override {
    return c_provider_;
  }

 private:
  grpc_authorization_policy_provider* c_provider_ = nullptr;
};

}
}

#endif
