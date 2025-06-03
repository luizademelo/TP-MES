Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this file
#ifndef GRPCXX_IMPL_CODEGEN_RPC_METHOD_H
#define GRPCXX_IMPL_CODEGEN_RPC_METHOD_H

// Includes the main implementation file for RPC method functionality
// This is a common pattern where the public header just includes
// the actual implementation from another location
#include <grpcpp/impl/codegen/rpc_method.h>

// End of header guard
#endif
```

The comments explain:
1. The copyright notice
2. The purpose of the header guard
3. The inclusion pattern being used (where this header just includes the actual implementation)
4. The closing of the header guard

This is a typical structure for a public-facing header file that serves as an indirection to the actual implementation.