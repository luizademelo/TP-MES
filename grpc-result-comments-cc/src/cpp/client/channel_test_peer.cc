Here's the commented version of the code snippet:

```c++
// Copyright 2020 gRPC authors.

// Include necessary headers
#include <grpcpp/channel.h>             // For gRPC channel functionality
#include <grpcpp/test/channel_test_peer.h>  // For ChannelTestPeer class

#include "src/core/lib/surface/channel.h"  // For core channel implementation

namespace grpc {
namespace testing {

// Returns the number of currently registered calls on this channel
// This is a test-only method used for verifying channel behavior
// 
// Returns:
//   int - The count of currently registered calls on the channel
int ChannelTestPeer::registered_calls() const {
  // Access the core channel implementation from the C-style channel
  // and call its test-only method to get registered calls count
  return grpc_core::Channel::FromC(channel_->c_channel_)
      ->TestOnlyRegisteredCalls();
}

}  // namespace testing
}  // namespace grpc
```

Key comments added:
1. Explained the purpose of each include header
2. Added documentation for the `registered_calls()` method including:
   - What it does
   - That it's test-only functionality
   - Return value description
3. Explained the implementation logic within the method
4. Added namespace closing comments for better readability
5. Maintained the original copyright notice

The comments provide context about the method's purpose and implementation while making it clear this is test functionality not meant for production use.