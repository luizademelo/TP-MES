Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.
// This file is part of the gRPC C++ library interface.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCXX_SERVER_BUILDER_H
#define GRPCXX_SERVER_BUILDER_H

// Includes the main server builder implementation from the gRPP C++ library
// This provides the ServerBuilder class which is used to configure and create
// gRPC server instances.
#include <grpcpp/server_builder.h>

// End of header guard
#endif
```

The comments explain:
1. The copyright notice
2. The purpose of the header guard
3. What the included file provides
4. The closing of the header guard

The file appears to be a wrapper header that mainly serves to include the actual implementation from the gRPC C++ library while providing proper header guards. This is a common pattern in library design to provide a clean include path while keeping the actual implementation separate.