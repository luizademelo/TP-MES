Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCXX_IMPL_CODEGEN_SLICE_H
#define GRPCXX_IMPL_CODEGEN_SLICE_H

// Includes the actual implementation of the Slice functionality
// from the gRPC C++ library. This is a forwarding header that
// points to the real implementation location.
#include <grpcpp/impl/codegen/slice.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. The nature of this file as a forwarding header
3. The location of the actual implementation
4. The closing of the header guard

This style of commenting makes it clear that this is a boilerplate header file whose main purpose is to include the real implementation while preventing multiple inclusions.