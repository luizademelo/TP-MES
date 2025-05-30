// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_RBAC_TRANSLATOR_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_RBAC_TRANSLATOR_H

#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/security/authorization/rbac_policy.h"

namespace grpc_core {

struct RbacPolicies {
  std::optional<Rbac> deny_policy;
  Rbac allow_policy;
};

absl::StatusOr<RbacPolicies> GenerateRbacPolicies(
    absl::string_view authz_policy);

}

#endif
