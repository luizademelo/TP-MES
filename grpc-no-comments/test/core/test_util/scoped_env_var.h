
// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_SCOPED_ENV_VAR_H
#define GRPC_TEST_CORE_TEST_UTIL_SCOPED_ENV_VAR_H

#include <grpc/support/port_platform.h>

#include "src/core/util/env.h"

namespace grpc_core {
namespace testing {

class ScopedEnvVar {
 public:
  ScopedEnvVar(const char* env_var, const char* value) : env_var_(env_var) {
    SetEnv(env_var_, value);
  }

  virtual ~ScopedEnvVar() { UnsetEnv(env_var_); }

 private:
  const char* env_var_;
};

class ScopedExperimentalEnvVar : public ScopedEnvVar {
 public:
  explicit ScopedExperimentalEnvVar(const char* env_var)
      : ScopedEnvVar(env_var, "true") {}
};

}
}

#endif
