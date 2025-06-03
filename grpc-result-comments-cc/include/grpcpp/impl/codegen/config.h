Here's the commented version of the code snippet:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_CONFIG_H
#define GRPCPP_IMPL_CODEGEN_CONFIG_H

// Includes the main gRPC C++ configuration header which contains
// platform-specific configurations and feature macros needed for gRPC
#include <grpcpp/support/config.h>

#endif  // GRPCPP_IMPL_CODEGEN_CONFIG_H
```

The comments explain:
1. The purpose of the header guard (standard practice in C/C++ headers)
2. The role of the included config.h file which contains essential gRPC configuration
3. The closing of the header guard with a descriptive comment

The file appears to be a simple configuration wrapper that ensures the main gRPC configuration header is properly included while maintaining standard header guard practices.