Here's the commented version of the code:

```c++
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

// Base class for authorization policy providers in gRPC.
// This class is dual reference-counted and provides interfaces for:
// 1. Managing authorization policies (allow/deny engines)
// 2. Channel argument handling for gRPC
struct grpc_authorization_policy_provider
    : public grpc_core::DualRefCounted<grpc_authorization_policy_provider> {
 public:
  // Returns the channel argument name for authorization policy provider.
  // This is used when adding the provider to channel arguments.
  static absl::string_view ChannelArgName() {
    return GRPC_ARG_AUTHORIZATION_POLICY_PROVIDER;
  }

  // Comparison function for channel arguments.
  // Uses QsortCompare for pointer comparison of policy providers.
  static int ChannelArgsCompare(const grpc_authorization_policy_provider* a,
                                const grpc_authorization_policy_provider* b) {
    return QsortCompare(a, b);
  }

  // Container for holding both allow and deny authorization engines.
  // These engines are used to evaluate authorization policies.
  struct AuthorizationEngines {
    // Engine for evaluating allow policies
    grpc_core::RefCountedPtr<grpc_core::AuthorizationEngine> allow_engine;
    // Engine for evaluating deny policies
    grpc_core::RefCountedPtr<grpc_core::AuthorizationEngine> deny_engine;
  };

  // Pure virtual function to be implemented by derived classes.
  // Returns the current set of authorization engines (both allow and deny).
  virtual AuthorizationEngines engines() = 0;
};

#endif
```

The comments explain:
1. The overall purpose of the class as a base for authorization policy providers
2. The dual reference-counting nature of the class
3. The purpose of each method and structure
4. The role of the AuthorizationEngines struct and its components
5. The virtual nature of the engines() method that must be implemented by derived classes

The comments are placed to be immediately visible to developers working with the code while maintaining good readability.