Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_ACTIVATION_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_ACTIVATION_H

#include <grpc/support/port_platform.h>  // Platform-specific portability macros

#include "absl/strings/string_view.h"    // For absl::string_view
#include "src/core/lib/security/authorization/mock_cel/cel_value.h"  // For CelValue class

namespace grpc_core {
namespace mock_cel {

// Base class for CEL (Common Expression Language) activation.
// Activation in CEL context is a collection of named values that can be
// referenced in expressions.
class BaseActivation {
 public:
  BaseActivation() = default;  // Default constructor

  // Delete copy constructor and assignment operator to make this class non-copyable
  BaseActivation(const BaseActivation&) = delete;
  BaseActivation& operator=(const BaseActivation&) = delete;
};

// Derived class implementing CEL activation functionality.
// Currently provides minimal functionality for mock implementation.
class Activation : public BaseActivation {
 public:
  Activation() = default;  // Default constructor

  // Delete copy constructor and assignment operator to make this class non-copyable
  Activation(const Activation&) = delete;
  Activation& operator=(const Activation&) = delete;

  // Method to insert a named value into the activation.
  // Currently a no-op in this mock implementation.
  // Parameters:
  //   - absl::string_view: The name/key under which to store the value
  //   - const CelValue&: The CEL value to be stored
  void InsertValue(absl::string_view, const CelValue&) {}
};

}  // namespace mock_cel
}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_ACTIVATION_H
```

The comments explain:
1. The purpose of each class and its role in the CEL (Common Expression Language) context
2. The non-copyable nature of both classes (via deleted copy operations)
3. The currently minimal/mock implementation status
4. The purpose of each method and its parameters
5. Header guard and include statements
6. Namespace organization

The comments are designed to help future developers understand:
- The intended functionality of these classes
- Current implementation limitations (mock/no-op behavior)
- How these classes fit into the larger CEL authorization system
- The design decisions (like non-copyability)