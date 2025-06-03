Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#include "src/cpp/server/external_connection_acceptor_impl.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc {
namespace internal {
namespace {

// Wrapper class that implements the ExternalConnectionAcceptor interface
// and forwards connection handling to ExternalConnectionAcceptorImpl
class AcceptorWrapper : public experimental::ExternalConnectionAcceptor {
 public:
  // Constructs the wrapper with a shared pointer to the implementation
  explicit AcceptorWrapper(std::shared_ptr<ExternalConnectionAcceptorImpl> impl)
      : impl_(std::move(impl)) {}
  
  // Handles new connection by delegating to the implementation
  void HandleNewConnection(NewConnectionParameters* p) override {
    impl_->HandleNewConnection(p);
  }

 private:
  std::shared_ptr<ExternalConnectionAcceptorImpl> impl_;
};
}

// Constructor for ExternalConnectionAcceptorImpl
// name: identifier for this acceptor
// type: type of external connection (must be FROM_FD)
// creds: server credentials for the connection
ExternalConnectionAcceptorImpl::ExternalConnectionAcceptorImpl(
    const std::string& name,
    ServerBuilder::experimental_type::ExternalConnectionType type,
    std::shared_ptr<ServerCredentials> creds)
    : name_(name), creds_(std::move(creds)) {
  // Verify that the connection type is FROM_FD (file descriptor)
  CHECK(type ==
        ServerBuilder::experimental_type::ExternalConnectionType::FROM_FD);
}

// Creates and returns a new acceptor wrapper instance
// Ensures only one acceptor can be created per instance
std::unique_ptr<experimental::ExternalConnectionAcceptor>
ExternalConnectionAcceptorImpl::GetAcceptor() {
  grpc_core::MutexLock lock(&mu_);  // Thread-safe operation
  CHECK(!has_acceptor_);  // Verify no acceptor exists yet
  has_acceptor_ = true;
  return std::unique_ptr<experimental::ExternalConnectionAcceptor>(
      new AcceptorWrapper(shared_from_this()));
}

// Handles a new incoming connection
// p: parameters containing connection details (file descriptors and buffer)
void ExternalConnectionAcceptorImpl::HandleNewConnection(
    experimental::ExternalConnectionAcceptor::NewConnectionParameters* p) {
  grpc_core::MutexLock lock(&mu_);  // Thread-safe operation
  
  // Reject connection if shutdown or not started
  if (shutdown_ || !started_) {
    LOG(ERROR) << "NOT handling external connection with fd " << p->fd
               << ", started " << started_ << ", shutdown " << shutdown_;
    return;
  }
  
  // Forward connection to handler if available
  if (handler_) {
    handler_->Handle(p->listener_fd, p->fd, p->read_buffer.c_buffer());
  }
}

// Shuts down the acceptor, preventing new connections from being handled
void ExternalConnectionAcceptorImpl::Shutdown() {
  grpc_core::MutexLock lock(&mu_);  // Thread-safe operation
  shutdown_ = true;
}

// Starts the acceptor, allowing it to handle new connections
// Must be called after GetAcceptor() and before Shutdown()
void ExternalConnectionAcceptorImpl::Start() {
  grpc_core::MutexLock lock(&mu_);  // Thread-safe operation
  CHECK(!started_);    // Verify not already started
  CHECK(has_acceptor_);  // Verify acceptor exists
  CHECK(!shutdown_);   // Verify not shutdown
  started_ = true;
}

// Sets the acceptor handler in the channel arguments
// args: ChannelArguments to modify
void ExternalConnectionAcceptorImpl::SetToChannelArgs(ChannelArguments* args) {
  args->SetPointer(name_, &handler_);
}

}
}
```