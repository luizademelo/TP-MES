Here's the commented version of the code snippet:

```c++
// Copyright 2021 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_EXT_ADMIN_SERVICES_H
#define GRPCPP_EXT_ADMIN_SERVICES_H

// Include necessary header for ServerBuilder class
#include <grpcpp/server_builder.h>

// Main gRPC namespace
namespace grpc {

// Function declaration for adding admin services to a gRPC server
// @param builder Pointer to ServerBuilder instance which will be configured
//                with admin services. The ServerBuilder is used to create
//                and configure gRPC server instances.
void AddAdminServices(grpc::ServerBuilder* builder);

}  // namespace grpc

// End of header guard
#endif  // GRPCPP_EXT_ADMIN_SERVICES_H
```

The comments explain:
1. The purpose of the header guard
2. The included header file and its relevance
3. The namespace declaration
4. The function declaration, including its purpose and parameter explanation
5. The closing of the namespace and header guard

The comments follow a clear and consistent style while providing useful information about each component of the header file.