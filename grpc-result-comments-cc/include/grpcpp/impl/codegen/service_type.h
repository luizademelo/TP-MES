Here's the commented version of the code snippet:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_SERVICE_TYPE_H
#define GRPCPP_IMPL_CODEGEN_SERVICE_TYPE_H

// Includes the actual service type implementation from the gRPP library
// This is a forward declaration or facade header that points to the real implementation
#include <grpcpp/impl/service_type.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard (preventing multiple inclusions)
2. The nature of this being a facade/forwarding header file
3. The actual location of the implementation
4. The closing of the header guard

This follows common C++ header file conventions and helps developers understand:
- Why this header exists
- Where the actual implementation is located
- The standard header guard pattern used