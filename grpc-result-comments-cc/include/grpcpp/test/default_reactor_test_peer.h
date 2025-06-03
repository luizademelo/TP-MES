Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_TEST_DEFAULT_REACTOR_TEST_PEER_H
#define GRPCPP_TEST_DEFAULT_REACTOR_TEST_PEER_H

#include <grpcpp/server_context.h>
#include <grpcpp/support/server_callback.h>

namespace grpc {
namespace testing {

// DefaultReactorTestPeer is a testing utility class that provides access to
// the default reactor in a CallbackServerContext for testing purposes.
// It allows inspecting and manipulating the reactor during unit tests.
class DefaultReactorTestPeer {
 public:
  // Constructor that takes a CallbackServerContext and uses a no-op finish function
  // Args:
  //   ctx - The CallbackServerContext containing the reactor to test
  explicit DefaultReactorTestPeer(CallbackServerContext* ctx)
      : DefaultReactorTestPeer(ctx, [](Status) {}) {}

  // Constructor that takes a CallbackServerContext and a custom finish function
  // Args:
  //   ctx - The CallbackServerContext containing the reactor to test
  //   finish_func - A function to be called when the reactor finishes
  DefaultReactorTestPeer(CallbackServerContext* ctx,
                         std::function<void(Status)> finish_func)
      : ctx_(ctx) {
    // Set up the test default reactor with the provided finish function
    ctx->SetupTestDefaultReactor(std::move(finish_func));
  }

  // Gets the underlying ServerUnaryReactor from the context
  // Returns:
  //   Pointer to the ServerUnaryReactor being tested
  ServerUnaryReactor* reactor() const {
    return reinterpret_cast<ServerUnaryReactor*>(&ctx_->default_reactor_);
  }

  // Checks if a test status has been set on the context
  // Returns:
  //   true if a test status has been set, false otherwise
  bool test_status_set() const { return ctx_->test_status_set(); }

  // Gets the test status from the context
  // Returns:
  //   The Status object containing test status information
  Status test_status() const { return ctx_->test_status(); }

 private:
  // The CallbackServerContext being tested, stored as a const pointer
  CallbackServerContext* const ctx_;
};

}  // namespace testing
}  // namespace grpc

#endif  // GRPCPP_TEST_DEFAULT_REACTOR_TEST_PEER_H
```

The comments explain:
1. The overall purpose of the DefaultReactorTestPeer class
2. Each constructor's purpose and parameters
3. Each method's purpose, parameters, and return values
4. The private member variable's purpose
5. The namespace and include guard details

The comments follow a consistent style and provide enough information for a developer to understand how to use and maintain this testing utility class.