Here's the commented version of the code snippet:

```c++
// Copyright 2022 gRPC authors.

// Header file for internal initialization functionality
#include "src/core/lib/surface/init_internally.h"

// Platform-specific support definitions
#include <grpc/support/port_platform.h>

// Main namespace for gRPC core functionality
namespace grpc_core {

// Function pointer for internal initialization routine.
// This will be set to point to the actual initialization implementation.
void (*InitInternally)();

// Function pointer for internal shutdown routine.
// This will be set to point to the actual shutdown implementation.
void (*ShutdownInternally)();

// Function pointer to check if gRPC is initialized internally.
// This will be set to point to the actual status check implementation.
bool (*IsInitializedInternally)();

}  // namespace grpc_core
```

The comments explain:
1. The purpose of the included header file
2. The platform support include
3. The namespace declaration
4. Each function pointer declaration, noting they will be set to point to actual implementations
5. The closing namespace with a clear label

The comments are kept concise while providing clear explanations of each component's purpose and relationship to the larger system.