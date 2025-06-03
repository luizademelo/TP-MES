Here's the commented version of the code snippet:

```c++
// Copyright 2019 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_ASYNC_STREAM_H
#define GRPCPP_IMPL_CODEGEN_ASYNC_STREAM_H

// Include the actual implementation of async stream support
// This is a common pattern where a codegen header includes the real implementation
#include <grpcpp/support/async_stream.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard (a standard C++ practice to prevent multiple inclusions)
2. The nature of this being a forwarding header that includes the actual implementation
3. The standard pattern used in gRPC's code organization

The code itself is a simple header file that:
- Has copyright information
- Uses standard include guards
- Forwards to the actual implementation file
This is a common pattern in large codebases to separate interface from implementation.