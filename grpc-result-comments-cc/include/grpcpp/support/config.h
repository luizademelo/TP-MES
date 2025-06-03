Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this file
#ifndef GRPCPP_SUPPORT_CONFIG_H
#define GRPCPP_SUPPORT_CONFIG_H

// Include standard string library
#include <string>

// Macro definitions for C++11 override and final specifiers
// These provide consistent naming across different platforms/compilers
#define GRPC_OVERRIDE override
#define GRPC_FINAL final

// Deprecation warning for obsolete configuration option
// GRPC_CUSTOM_STRING is no longer supported in favor of standard std::string
#ifdef GRPC_CUSTOM_STRING
#warning GRPC_CUSTOM_STRING is no longer supported. Please use std::string.
#endif

// gRPC namespace definition
namespace grpc {

// Bring std::string and std::to_string into the grpc namespace for convenience
using std::string;
using std::to_string;

}  // namespace grpc

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. Included standard library headers
3. Macro definitions and their purpose
4. Deprecation warning for obsolete configuration
5. Namespace usage and convenience type aliases
6. The closing of the header guard

The comments are concise but provide enough context for future maintainers to understand the purpose and functionality of each part of the header file.