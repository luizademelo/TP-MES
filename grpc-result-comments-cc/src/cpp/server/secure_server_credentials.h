Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_SECURE_SERVER_CREDENTIALS_H
#define GRPC_SRC_CPP_SERVER_SECURE_SERVER_CREDENTIALS_H

// Include necessary gRPC headers for server security functionality
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpcpp/security/auth_metadata_processor.h>
#include <grpcpp/security/server_credentials.h>

#include <memory>  // For smart pointers

#include "src/cpp/server/thread_pool_interface.h"  // For thread pool interface

namespace grpc {

// Wrapper class for asynchronous processing of authentication metadata
// This class handles the interaction between gRPC's C-based auth processing
// and C++ AuthMetadataProcessor implementations
class AuthMetadataProcessorAsyncWrapper final {
 public:
  // Static method to clean up wrapper instances
  static void Destroy(void* wrapper);

  // Static method that processes authentication metadata
  // This is the entry point called by gRPC's C core
  static void Process(void* wrapper, grpc_auth_context* context,
                      const grpc_metadata* md, size_t num_md,
                      grpc_process_auth_metadata_done_cb cb, void* user_data);

  // Constructor that takes a shared pointer to an AuthMetadataProcessor
  // If the processor is blocking, creates a default thread pool for async processing
  explicit AuthMetadataProcessorAsyncWrapper(
      const std::shared_ptr<AuthMetadataProcessor>& processor)
      : processor_(processor) {
    if (processor && processor->IsBlocking()) {
      thread_pool_.reset(CreateDefaultThreadPool());
    }
  }

 private:
  // Internal method that actually invokes the processor's logic
  void InvokeProcessor(grpc_auth_context* context, const grpc_metadata* md,
                       size_t num_md, grpc_process_auth_metadata_done_cb cb,
                       void* user_data);
  
  // Thread pool for handling blocking auth processors
  std::unique_ptr<ThreadPoolInterface> thread_pool_;
  // The actual auth metadata processor implementation
  std::shared_ptr<AuthMetadataProcessor> processor_;
};

// Implementation of ServerCredentials for secure connections
// This class wraps gRPC's C-based server credentials with C++ functionality
class SecureServerCredentials final : public ServerCredentials {
 public:
  // Constructor taking raw gRPC server credentials
  explicit SecureServerCredentials(grpc_server_credentials* creds);

  // Sets the auth metadata processor for these credentials
  // Overrides the base class method to provide specific implementation
  void SetAuthMetadataProcessor(
      const std::shared_ptr<grpc::AuthMetadataProcessor>& processor) override;

 private:
  // Wrapper instance that handles async auth metadata processing
  std::unique_ptr<grpc::AuthMetadataProcessorAsyncWrapper> processor_;
};

}  // namespace grpc

#endif  // GRPC_SRC_CPP_SERVER_SECURE_SERVER_CREDENTIALS_H
```

Key aspects covered in the comments:
1. Overall purpose of each class
2. Important methods and their roles
3. Relationships between components
4. Memory management considerations
5. Threading implications
6. Connection between C and C++ layers
7. Overridden virtual methods
8. Key member variables and their purposes

The comments aim to provide enough context for future maintainers to understand the code's structure and behavior without being overly verbose.