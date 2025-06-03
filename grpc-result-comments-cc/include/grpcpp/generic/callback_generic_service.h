Here's the commented version of the code:

```c++
// Copyright 2024 gRPC authors.

#ifndef GRPCPP_GENERIC_CALLBACK_GENERIC_SERVICE_H
#define GRPCPP_GENERIC_CALLBACK_GENERIC_SERVICE_H

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/server_callback.h>

struct grpc_server;

namespace grpc {

// Alias for a bidirectional streaming reactor that handles ByteBuffer messages
using ServerGenericBidiReactor = ServerBidiReactor<ByteBuffer, ByteBuffer>;

// Context class for generic callback-based RPCs, extending CallbackServerContext
class GenericCallbackServerContext final : public grpc::CallbackServerContext {
 public:
  // Returns the method name for the RPC
  const std::string& method() const { return method_; }
  
  // Returns the host name for the RPC
  const std::string& host() const { return host_; }

 private:
  friend class grpc::Server;  // Allow Server class to access private members

  std::string method_;  // Stores the RPC method name
  std::string host_;    // Stores the host name
};

// Base class for implementing generic callback-based services
class CallbackGenericService {
 public:
  CallbackGenericService() {}  // Default constructor
  virtual ~CallbackGenericService() {}  // Virtual destructor for proper cleanup

  // Creates a reactor for handling bidirectional streaming RPCs
  // Default implementation returns a reactor that immediately finishes with UNIMPLEMENTED status
  virtual ServerGenericBidiReactor* CreateReactor(
      GenericCallbackServerContext* ) {
    class Reactor : public ServerGenericBidiReactor {
     public:
      Reactor() {
        // Immediately finish the RPC with UNIMPLEMENTED status
        this->Finish(Status(StatusCode::UNIMPLEMENTED, ""));
      }
      
      // Called when the RPC is done - performs cleanup by deleting the reactor
      void OnDone() override { delete this; }
    };
    return new Reactor;
  }

 private:
  friend class grpc::Server;  // Allow Server class to access private members

  // Creates a handler for bidirectional streaming RPCs
  // The handler uses this service's CreateReactor method to create reactors for new RPCs
  internal::CallbackBidiHandler<ByteBuffer, ByteBuffer>* Handler() {
    return new internal::CallbackBidiHandler<ByteBuffer, ByteBuffer>(
        [this](grpc::CallbackServerContext* ctx) {
          return CreateReactor(static_cast<GenericCallbackServerContext*>(ctx));
        });
  }

  grpc::Server* server_{nullptr};  // Pointer to the owning server instance
};

}  // namespace grpc

#endif  // GRPCPP_GENERIC_CALLBACK_GENERIC_SERVICE_H
```

Key points covered in the comments:
1. File header and include guard explanation
2. Purpose of the ServerGenericBidiReactor alias
3. Functionality of GenericCallbackServerContext and its methods
4. Base service class (CallbackGenericService) and its virtual methods
5. Default reactor implementation behavior
6. Private handler creation mechanism
7. Relationship with the Server class through friend declarations
8. Important implementation details like memory management in OnDone()

The comments aim to provide both high-level understanding of the components and specific details about important implementation choices.