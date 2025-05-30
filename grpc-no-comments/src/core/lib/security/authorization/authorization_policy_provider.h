// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_POLICY_PROVIDER_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_POLICY_PROVIDER_H

#include <grpc/grpc_security.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/security/authorization/authorization_engine.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

struct grpc_authorization_policy_provider
    : public grpc_core::DualRefCounted<grpc_authorization_policy_provider> {
 public:
  static absl::string_view ChannelArgName() {
    return GRPC_ARG_AUTHORIZATION_POLICY_PROVIDER;
  }
  static int ChannelArgsCompare(const grpc_authorization_policy_provider* a,
                                const grpc_authorization_policy_provider* b) {
    return QsortCompare(a, b);
  }
  struct AuthorizationEngines {
    grpc_core::RefCountedPtr<grpc_core::AuthorizationEngine> allow_engine;
    grpc_core::RefCountedPtr<grpc_core::AuthorizationEngine> deny_engine;
  };
  virtual AuthorizationEngines engines() = 0;
};

#endif
