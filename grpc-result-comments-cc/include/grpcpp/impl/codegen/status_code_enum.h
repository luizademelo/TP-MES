Here's the commented version of the code snippet:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_STATUS_CODE_ENUM_H
#define GRPCPP_IMPL_CODEGEN_STATUS_CODE_ENUM_H

// Includes the actual implementation of status code enumeration
// This is a forwarding header that points to the public-facing header
#include <grpcpp/support/status_code_enum.h>

#endif  // End of header guard
```

The comments explain:
1. The copyright notice
2. The purpose of the header guard
3. The nature of this file as a forwarding header
4. The closing of the header guard

This is a typical C++ header file structure where:
- The header guard prevents multiple inclusion issues
- The file serves as an internal forwarding header to the public header
- The actual implementation is in the included file