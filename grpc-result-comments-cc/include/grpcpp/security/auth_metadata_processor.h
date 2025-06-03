Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_SECURITY_AUTH_METADATA_PROCESSOR_H
#define GRPCPP_SECURITY_AUTH_METADATA_PROCESSOR_H

// Include necessary headers
#include <grpcpp/security/auth_context.h>  // For AuthContext
#include <grpcpp/support/status.h>         // For Status
#include <grpcpp/support/string_ref.h>     // For string_ref

#include <map>  // For std::multimap

namespace grpc {

// Abstract base class for processing authentication metadata in gRPC.
// Implementations of this class can be used to intercept and process
// authentication metadata during RPC calls.
class AuthMetadataProcessor {
 public:
  // Type definitions for metadata containers:
  // InputMetadata: Read-only metadata received from the client (string_ref for efficiency)
  typedef std::multimap<grpc::string_ref, grpc::string_ref> InputMetadata;
  // OutputMetadata: Writable metadata (using std::string for modification)
  typedef std::multimap<std::string, std::string> OutputMetadata;

  // Virtual destructor for proper cleanup of derived classes
  virtual ~AuthMetadataProcessor() {}

  // Indicates whether the processor is blocking (synchronous) or non-blocking (asynchronous).
  // Default implementation returns true for backward compatibility.
  virtual bool IsBlocking() const { return true; }

  // Pure virtual function to process authentication metadata.
  // Parameters:
  //   auth_metadata: The authentication metadata received from the client
  //   context: The authentication context that can be modified
  //   consumed_auth_metadata: Output parameter for metadata consumed by processor
  //   response_metadata: Output parameter for metadata to send back to client
  // Returns:
  //   Status indicating success or failure of the authentication process
  virtual grpc::Status Process(const InputMetadata& auth_metadata,
                               grpc::AuthContext* context,
                               OutputMetadata* consumed_auth_metadata,
                               OutputMetadata* response_metadata) = 0;
};

}  // namespace grpc

#endif  // GRPCPP_SECURITY_AUTH_METADATA_PROCESSOR_H
```

The comments explain:
1. The purpose of the header guard
2. The role of each included header
3. The overall purpose of the AuthMetadataProcessor class
4. The typedefs for metadata containers and why different string types are used
5. The virtual destructor and its importance
6. The IsBlocking() method and its default behavior
7. The Process() method with detailed parameter explanations and return value

The comments are designed to help future developers understand:
- When they might need to implement this interface
- How to properly implement the virtual methods
- The expected behavior and contracts of each method
- The memory management implications (string_ref vs string)