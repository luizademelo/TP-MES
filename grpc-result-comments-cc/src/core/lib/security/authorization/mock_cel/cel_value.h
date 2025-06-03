Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_VALUE_H
#define GRPC_SRC_CORE_LIB_SECURITY_AUTHORIZATION_MOCK_CEL_CEL_VALUE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"

namespace grpc_core {
namespace mock_cel {

// CelMap is a mock implementation of a map container for CEL (Common Expression Language).
// Currently empty, would typically provide methods for key-value storage and retrieval.
class CelMap {
 public:
  CelMap() = default;
};

// CelValue represents a value in CEL expressions. It can hold different types of values
// including null, integers, strings, and maps. This is a mock implementation.
class CelValue {
 public:
  // Default constructor creates a null value
  CelValue() : CelValue(nullptr) {}

  // Creates a null CelValue
  static CelValue CreateNull() { return CelValue(nullptr); }

  // Creates a CelValue from a 64-bit signed integer (mock implementation returns null)
  static CelValue CreateInt64(int64_t ) { return CreateNull(); }

  // Creates a CelValue from a 64-bit unsigned integer (mock implementation returns null)
  static CelValue CreateUint64(uint64_t ) { return CreateNull(); }

  // Creates a CelValue from a string view (mock implementation returns null)
  static CelValue CreateStringView(absl::string_view ) {
    return CreateNull();
  }

  // Creates a CelValue from a string pointer (mock implementation returns null)
  static CelValue CreateString(const std::string* ) {
    return CreateNull();
  }

  // Creates a CelValue from a CelMap pointer (mock implementation returns null)
  static CelValue CreateMap(const CelMap* ) { return CreateNull(); }

 private:
  // Private constructor that can create a CelValue from any type T
  // (mock implementation does nothing with the input)
  template <class T>
  explicit CelValue(T ) {}
};

// ContainerBackedMapImpl is a concrete implementation of CelMap that would typically
// be backed by a container. Currently mock implementation with no actual functionality.
class ContainerBackedMapImpl : public CelMap {
 public:
  ContainerBackedMapImpl() = default;

  // Factory method to create a ContainerBackedMapImpl from a span of CelValue pairs
  // (mock implementation always returns an empty map)
  static std::unique_ptr<CelMap> Create(
      absl::Span<std::pair<CelValue, CelValue>> ) {
    return std::make_unique<ContainerBackedMapImpl>();
  }
};

}  // namespace mock_cel
}  // namespace grpc_core

#endif
```

The comments explain:
1. The purpose of each class and its role in the mock CEL implementation
2. What each method is supposed to do (with notes about the current mock implementation)
3. The expected behavior vs actual mock behavior
4. The relationships between classes
5. The purpose of template methods and factory methods

The comments are kept concise while providing enough information for future maintainers to understand both the intended functionality and the current mock implementation state.