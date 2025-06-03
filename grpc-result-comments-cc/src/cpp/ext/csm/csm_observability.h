Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CPP_EXT_CSM_CSM_OBSERVABILITY_H
#define GRPC_SRC_CPP_EXT_CSM_CSM_OBSERVABILITY_H

// Include platform-specific support macros and types
#include <grpc/support/port_platform.h>

// Include string view utility from Abseil library
#include "absl/strings/string_view.h"
// Include channel arguments utilities
#include "src/core/lib/channel/channel_args.h"

// Begin grpc namespace
namespace grpc {
// Begin internal namespace (for implementation details)
namespace internal {

// Function to determine if a given target is a CSM (Cloud Service Mesh) channel
// Parameters:
//   target - The target string to evaluate (as a string view for efficiency)
// Returns:
//   bool - true if the target is identified as a CSM channel, false otherwise
bool CsmChannelTargetSelector(absl::string_view target);

// Function to determine if a server should enable CSM observability based on channel args
// Parameters:
//   args - The channel arguments containing server configuration
// Returns:
//   bool - true if the server should enable CSM observability, false otherwise
bool CsmServerSelector(const grpc_core::ChannelArgs& args);

}  // namespace internal
}  // namespace grpc

// End of header guard
#endif  // GRPC_SRC_CPP_EXT_CSM_CSM_OBSERVABILITY_H
```

The comments provide:
1. Explanation of the header guard purpose
2. Description of each included header's purpose
3. Documentation of namespaces
4. Detailed documentation for each function including:
   - Purpose of the function
   - Parameters with their types and purposes
   - Return value explanation
5. Clear indication of namespace endings
6. Proper closing of header guard with comment