Here's the commented version of the code snippet:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_SECURITY_AUTH_CONTEXT_H
#define GRPCPP_IMPL_CODEGEN_SECURITY_AUTH_CONTEXT_H

// Includes the main auth_context.h header file from gRPC's security module
// This provides the authentication context functionality for gRPC
#include <grpcpp/security/auth_context.h>

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard (standard C++ practice to prevent multiple inclusions)
2. The significance of including the main auth_context.h file
3. The closing of the header guard

The file appears to be a forwarding header that simply includes the main authentication context header from gRPC's security module, with appropriate header guards to prevent multiple inclusions.