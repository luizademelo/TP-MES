Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCXX_IMPL_CODEGEN_METADATA_MAP_H
#define GRPCXX_IMPL_CODEGEN_METADATA_MAP_H

// Includes the main metadata map implementation from the gRPP public headers
// This is a common pattern in C++ libraries where the public header includes
// the actual implementation from another location
#include <grpcpp/impl/codegen/metadata_map.h>

#endif  // GRPCXX_IMPL_CODEGEN_METADATA_MAP_H
```

The comments explain:
1. The purpose of the header guard
2. The inclusion pattern being used (common in library development)
3. The closing of the header guard with a descriptive comment

I've maintained the original copyright notice and kept the code structure identical while adding explanatory comments that would help future developers understand:
- Why this file exists
- What it's doing
- The common library pattern being used