Here's the commented version of the code snippet:

```c++
// Copyright 2025 gRPC authors.

// Include necessary headers
#include "src/core/lib/promise/wait_set.h"  // Main header for WaitSet class
#include "absl/strings/str_join.h"         // For string joining functionality

namespace grpc_core {

// Returns a string representation of the WaitSet
// This is primarily used for debugging purposes to inspect the contents of the WaitSet
// The string will contain comma-separated debug strings of all pending wakers
std::string WaitSet::ToString() {
  // Use absl::StrJoin to concatenate all pending wakers' debug strings:
  // 1. Iterates through the 'pending_' container (which holds Waker objects)
  // 2. For each Waker, calls its DebugString() method
  // 3. Joins all results with ", " as separator
  return absl::StrJoin(pending_, ", ",
                       [](std::string* out, const Waker& waker) {
                         absl::StrAppend(out, waker.DebugString());
                       });
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of the ToString() method
2. Its usage for debugging
3. The string format it produces
4. How absl::StrJoin is used to concatenate the waker debug strings
5. The lambda function's role in processing each Waker object
6. The namespace closure for better readability