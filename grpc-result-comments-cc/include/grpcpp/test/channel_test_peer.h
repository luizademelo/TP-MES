Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_TEST_CHANNEL_TEST_PEER_H
#define GRPCPP_TEST_CHANNEL_TEST_PEER_H

// Include the necessary gRPC channel header
#include <grpcpp/channel.h>

// gRPC namespace
namespace grpc {
// Testing utilities namespace
namespace testing {

// Class providing test access to Channel internals
// This is a test utility class that allows white-box testing of Channel functionality
class ChannelTestPeer {
 public:
  // Constructor that takes a pointer to a Channel object
  // The peer will use this channel for all operations
  explicit ChannelTestPeer(Channel* channel) : channel_(channel) {}

  // Returns the underlying C-style gRPC channel (grpc_channel) pointer
  // This provides access to the low-level implementation of the channel
  grpc_channel* channel() const { return channel_->c_channel_; }

  // Returns the number of registered calls on the channel
  // This is typically used for testing call registration/deregistration behavior
  int registered_calls() const;

 private:
  // Pointer to the Channel object being tested
  // This is the object whose internals we're providing access to for testing purposes
  Channel* channel_;
};

} // namespace testing
} // namespace grpc

// End of header guard
#endif
```

The comments explain:
1. The purpose of each section and component
2. The role of the ChannelTestPeer class as a test utility
3. The functionality of each method
4. The relationship between the class and the Channel it examines
5. The significance of the private member variable

The comments are designed to help maintainers understand:
- Why this class exists (for testing Channel internals)
- How to use it
- What each part does
- The connection between C++ and C gRPC APIs