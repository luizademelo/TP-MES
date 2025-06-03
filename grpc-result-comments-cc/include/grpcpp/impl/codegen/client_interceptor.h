Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.
// This file is part of the gRPC library and contains client interceptor related functionality.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_CLIENT_INTERCEPTOR_H
#define GRPCPP_IMPL_CODEGEN_CLIENT_INTERCEPTOR_H

// Includes the main client interceptor support header which contains
// the actual implementation of client interceptors in gRPC.
// Client interceptors allow for intercepting and modifying RPC calls
// on the client side before they are sent to the server.
#include <grpcpp/support/client_interceptor.h>

#endif  // GRPCPP_IMPL_CODEGEN_CLIENT_INTERCEPTOR_H
```

The comments explain:
1. The copyright notice and general purpose of the file
2. The purpose of the header guard
3. What the included header provides (client interceptor functionality)
4. Brief explanation of what client interceptors do in gRPC
5. The closing of the header guard with a matching comment for clarity