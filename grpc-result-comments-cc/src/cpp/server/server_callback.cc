Here's the commented version of the code:

```c++

// Copyright 2019 gRPC authors.

#include <grpcpp/support/server_callback.h>

namespace grpc {
namespace internal {

// Schedules the OnDone callback for the server call
// Parameters:
//   inline_ondone - if true, executes the callback immediately in the current thread;
//                   if false, schedules the callback to run asynchronously
void ServerCallbackCall::ScheduleOnDone(bool inline_ondone) {
  if (inline_ondone) {
    // Execute OnDone callback immediately
    CallOnDone();
    return;
  }
  // Schedule OnDone callback to run asynchronously
  RunAsync([this]() { CallOnDone(); });
}

// Handles cancellation of the server call by invoking the reactor's OnCancel callback
// Parameters:
//   reactor - the ServerReactor instance handling the call
void ServerCallbackCall::CallOnCancel(ServerReactor* reactor) {
  // Check if the reactor can handle the callback inline
  if (reactor->InternalInlineable()) {
    // Execute OnCancel immediately
    reactor->OnCancel();
    return;
  }
  // Increase reference count to maintain object lifetime during async operation
  Ref();
  // Schedule OnCancel to run asynchronously
  RunAsync([this, reactor]() {
    // Execute the OnCancel callback
    reactor->OnCancel();
    // Decrease reference count and potentially clean up if this was last reference
    MaybeDone();
  });
}

}  // namespace internal
}  // namespace grpc
```

Key improvements in the comments:
1. Added function-level comments explaining the purpose and behavior of each method
2. Added parameter descriptions
3. Added inline comments explaining key operations and decisions
4. Clarified the reference counting mechanism in CallOnCancel
5. Added namespace closing comments for better readability
6. Explained both the synchronous and asynchronous execution paths
7. Noted the object lifetime management in the async case

The comments now provide a clear understanding of:
- When callbacks execute immediately vs asynchronously
- How cancellation is handled
- The role of reference counting
- The overall flow of control in both methods