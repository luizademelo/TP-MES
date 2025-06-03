Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CPP_CLIENT_SECURE_CREDENTIALS_H
#define GRPC_SRC_CPP_CLIENT_SECURE_CREDENTIALS_H

// Include necessary gRPC headers
#include <grpc/grpc.h>                  // Core gRPC functionality
#include <grpc/grpc_security.h>         // Security-related functionality
#include <grpc/status.h>                // gRPC status codes
#include <grpcpp/channel.h>             // Channel interface
#include <grpcpp/impl/grpc_library.h>   // gRPC library initialization
#include <grpcpp/security/credentials.h> // Credentials base classes
#include <grpcpp/support/channel_arguments.h> // Channel arguments support
#include <grpcpp/support/client_interceptor.h> // Client interceptor support

namespace grpc {

namespace experimental {

// Converts C++ STS (Security Token Service) credentials options to core options
// Parameters:
//   options - const reference to StsCredentialsOptions containing C++ options
// Returns:
//   grpc_sts_credentials_options - converted core options structure
grpc_sts_credentials_options StsCredentialsCppToCoreOptions(
    const StsCredentialsOptions& options);

} // namespace experimental

// SecureChannelCredentials class provides secure channel credentials
// Inherits from grpc::ChannelCredentials to provide secure channel functionality
class SecureChannelCredentials final : public grpc::ChannelCredentials {
 public:
  // Constructor that takes ownership of core credentials
  // Parameters:
  //   c_creds - pointer to grpc_channel_credentials (core credentials)
  explicit SecureChannelCredentials(grpc_channel_credentials* c_creds)
      : ChannelCredentials(c_creds) {}
};

// SecureCallCredentials class provides secure call credentials
// Inherits from grpc::CallCredentials to provide secure call functionality
class SecureCallCredentials final : public grpc::CallCredentials {
 public:
  // Constructor that takes ownership of core credentials
  // Parameters:
  //   c_creds - pointer to grpc_call_credentials (core credentials)
  explicit SecureCallCredentials(grpc_call_credentials* c_creds)
      : CallCredentials(c_creds) {}
};

} // namespace grpc

#endif // GRPC_SRC_CPP_CLIENT_SECURE_CREDENTIALS_H
```

The comments provide:
1. Explanation of header guards and includes
2. Documentation for the namespace and conversion function
3. Class-level documentation for both credential classes
4. Constructor documentation explaining parameters and purpose
5. Clear indication of inheritance relationships
6. Notes about ownership transfer in constructors

The comments maintain a consistent style and provide enough information for future maintainers to understand the purpose and usage of each component without being overly verbose.