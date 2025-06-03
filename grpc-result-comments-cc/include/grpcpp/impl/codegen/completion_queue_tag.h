Here's the commented version of the code snippet:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_COMPLETION_QUEUE_TAG_H
#define GRPCPP_IMPL_CODEGEN_COMPLETION_QUEUE_TAG_H

// Includes the actual implementation of the CompletionQueueTag functionality
// This is a common pattern where a header in the 'codegen' directory includes
// the real implementation from another location
#include <grpcpp/impl/completion_queue_tag.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. The inclusion pattern being used (common in generated code)
3. The closing of the header guard

This is a typical boilerplate header file in gRPC's C++ implementation that serves as an indirection layer for the actual CompletionQueueTag implementation.