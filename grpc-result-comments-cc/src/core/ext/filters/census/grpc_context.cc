Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Include necessary gRPC headers
#include <grpc/census.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

// Include internal gRPC headers for tracing and call handling
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/surface/call.h"

/**
 * Associates a census context with a gRPC call.
 * This function stores the provided census context in the call's arena.
 * If the context is null, no operation is performed.
 * 
 * @param call The gRPC call to associate the context with
 * @param context The census context to associate (may be null)
 */
void grpc_census_call_set_context(grpc_call* call, census_context* context) {
  // Log the function call with parameters for debugging purposes
  GRPC_TRACE_LOG(api, INFO) << "grpc_census_call_set_context(call=" << call
                            << ", census_context=" << context << ")";
  if (context != nullptr) {
    // Store the census context in the call's arena
    grpc_call_get_arena(call)->SetContext<census_context>(context);
  }
}

/**
 * Retrieves the census context associated with a gRPC call.
 * This function fetches the census context stored in the call's arena.
 * 
 * @param call The gRPC call from which to retrieve the context
 * @return The associated census context, or null if none exists
 */
census_context* grpc_census_call_get_context(grpc_call* call) {
  // Log the function call with parameters for debugging purposes
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_census_call_get_context(call=" << call << ")";
  // Retrieve and return the census context from the call's arena
  return grpc_call_get_arena(call)->GetContext<census_context>();
}
```

Key improvements made:
1. Added file-level comments explaining the included headers
2. Added detailed function-level documentation using Doxygen-style comments
3. Included parameter and return value descriptions
4. Added explanations of the null check in set_context
5. Maintained all existing debug logging
6. Kept the original copyright notice
7. Added explanations of what each function actually does in terms of behavior