Here's the commented version of the code:

```c++
// Copyright 2021 The gRPC Authors

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_EVENT_ENGINE_ENDPOINT_CONFIG_H
#define GRPC_EVENT_ENGINE_ENDPOINT_CONFIG_H

// Includes platform-specific support macros and types
#include <grpc/support/port_platform.h>

// Standard library includes
#include <optional>  // For std::optional
#include <string>    // For std::string

// ABSL (Abseil) library for string view functionality
#include "absl/strings/string_view.h"

// Namespace for gRPC Event Engine components
namespace grpc_event_engine {
namespace experimental {

// Abstract base class representing endpoint configuration options.
// This provides an interface to access various types of configuration parameters
// that might be associated with a network endpoint.
class EndpointConfig {
 public:
  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~EndpointConfig() = default;

  // Gets an integer configuration value associated with the given key.
  // Returns std::nullopt if the key is not found or value isn't an integer.
  // @param key The configuration key to look up
  // @return Optional containing the integer value if found
  virtual std::optional<int> GetInt(absl::string_view key) const = 0;

  // Gets a string configuration value associated with the given key.
  // Returns std::nullopt if the key is not found or value isn't a string.
  // @param key The configuration key to look up
  // @return Optional containing the string_view to the value if found
  virtual std::optional<absl::string_view> GetString(
      absl::string_view key) const = 0;

  // Gets a void pointer configuration value associated with the given key.
  // Returns nullptr if the key is not found.
  // @param key The configuration key to look up
  // @return Raw pointer to the configuration value if found
  virtual void* GetVoidPointer(absl::string_view key) const = 0;
};

}  // namespace experimental
}  // namespace grpc_event_engine

#endif  // GRPC_EVENT_ENGINE_ENDPOINT_CONFIG_H
```

The comments explain:
1. The purpose of each include directive
2. The namespace structure
3. The overall purpose of the EndpointConfig class
4. Each virtual method's purpose, parameters, and return values
5. The behavior when keys aren't found
6. The use of std::optional for type-safe optional returns

The comments are written in a way that would help future developers understand:
- How to use this interface
- What to expect from each method
- The design decisions behind the interface
- Where this fits in the larger architecture (as an abstract base class)