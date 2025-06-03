Here's the commented version of the code snippet:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this file
#ifndef GRPCPP_IMPL_CODEGEN_CLIENT_UNARY_CALL_H
#define GRPCPP_IMPL_CODEGEN_CLIENT_UNARY_CALL_H

// Includes the main implementation file for client unary calls in gRPC
// This is a forwarding header that points to the actual implementation
#include <grpcpp/impl/client_unary_call.h>

#endif  // GRPCPP_IMPL_CODEGEN_CLIENT_UNARY_CALL_H
```

The comments explain:
1. The purpose of the header guard (standard C++ practice to prevent multiple inclusions)
2. The nature of this file as a forwarding header that includes the actual implementation
3. The closing of the header guard with a descriptive comment

The additional comments help future maintainers understand:
- That this is essentially a wrapper/forwarding header
- Where the actual implementation resides
- The standard C++ header guard pattern being used