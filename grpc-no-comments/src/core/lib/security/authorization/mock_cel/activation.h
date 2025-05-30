// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_ACTIVATION_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_ACTIVATION_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/security/authorization/mock_cel/cel_value.h"

namespace grpc_core {
namespace mock_cel {

class BaseActivation {
 public:
  BaseActivation() = default;

  BaseActivation(const BaseActivation&) = delete;
  BaseActivation& operator=(const BaseActivation&) = delete;
};

class Activation : public BaseActivation {
 public:
  Activation() = default;

  Activation(const Activation&) = delete;
  Activation& operator=(const Activation&) = delete;

  void InsertValue(absl::string_view , const CelValue& ) {}
};

}
}

#endif
