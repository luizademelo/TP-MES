Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_ENGINE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_ENGINE_H

// Include platform-specific support macros and types
#include <grpc/support/port_platform.h>

// Include standard string library
#include <string>

// Include necessary project headers
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {

// Abstract base class for authorization engines that provides core authorization functionality.
// Inherits from RefCounted for reference counting support.
class AuthorizationEngine : public RefCounted<AuthorizationEngine> {
 public:
  // Structure representing an authorization decision
  struct Decision {
    // Enumeration of possible decision types
    enum class Type {
      kAllow,  // Represents an allow decision
      kDeny,   // Represents a deny decision
    };
    Type type;  // The type of decision (allow/deny)
    std::string matching_policy_name;  // Name of the policy that matched, if any
  };

  // Pure virtual function to evaluate authorization against provided arguments.
  // Must be implemented by derived classes.
  // args: Evaluation arguments containing context for authorization decision
  // Returns: Decision object containing the authorization result
  virtual Decision Evaluate(const EvaluateArgs& args) const = 0;
};

}  // namespace grpc_core

// End of header guard
#endif  // GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_AUTHORIZATION_ENGINE_H
```

The comments explain:
1. The purpose of each section and include
2. The overall class purpose and inheritance
3. The Decision struct and its components
4. The pure virtual Evaluate method and its parameters
5. Header guard purpose
6. Namespace scope

The comments are designed to help future developers understand:
- The abstract nature of this class
- How authorization decisions are represented
- The interface that concrete authorization engines must implement
- The reference counting capability inherited from RefCounted