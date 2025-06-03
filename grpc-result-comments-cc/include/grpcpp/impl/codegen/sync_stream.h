Here's the commented version of the code snippet:

```c++
// Copyright 2019 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_SYNC_STREAM_H
#define GRPCPP_IMPL_CODEGEN_SYNC_STREAM_H

// Includes the actual implementation of synchronous streaming support
// This follows the Pimpl idiom where the implementation details are
// separated from the interface
#include <grpcpp/support/sync_stream.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. The include statement's role in the code organization (using Pimpl idiom)
3. The closing of the header guard

This is a typical header file structure in C++ that:
- Protects against multiple inclusions
- Provides the interface while delegating implementation to another file
- Maintains clean separation of concerns