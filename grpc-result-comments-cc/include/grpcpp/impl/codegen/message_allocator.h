Here's the commented version of the code snippet:

```c++
// Copyright 2019 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H
#define GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H

// Includes the main message allocator functionality from the public support headers
#include <grpcpp/support/message_allocator.h>

#endif  // GRPCPP_IMPL_CODEGEN_MESSAGE_ALLOCATOR_H
```

The comments explain:
1. The purpose of the header guard (a standard C++ practice to prevent duplicate inclusions)
2. The actual inclusion of the message allocator functionality from the public support headers
3. The closing of the header guard with a descriptive comment

The file appears to be a thin wrapper that simply includes the main message allocator implementation from the public headers while maintaining proper header guard protection.