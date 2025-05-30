
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_COMMON_SECURE_AUTH_CONTEXT_H
#define GRPC_SRC_CPP_COMMON_SECURE_AUTH_CONTEXT_H

#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_context.h>
#include <grpcpp/support/string_ref.h>

#include <string>
#include <vector>

#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc {

class SecureAuthContext final : public AuthContext {
 public:
  explicit SecureAuthContext(grpc_auth_context* ctx)
      : ctx_(ctx != nullptr ? ctx->Ref() : nullptr) {}

  ~SecureAuthContext() override = default;

  bool IsPeerAuthenticated() const override;

  std::vector<grpc::string_ref> GetPeerIdentity() const override;

  std::string GetPeerIdentityPropertyName() const override;

  std::vector<grpc::string_ref> FindPropertyValues(
      const std::string& name) const override;

  AuthPropertyIterator begin() const override;

  AuthPropertyIterator end() const override;

  void AddProperty(const std::string& key,
                   const grpc::string_ref& value) override;

  bool SetPeerIdentityPropertyName(const std::string& name) override;

 private:
  grpc_core::RefCountedPtr<grpc_auth_context> ctx_;
};

}

#endif
