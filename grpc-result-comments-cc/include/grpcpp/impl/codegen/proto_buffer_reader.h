Here's the commented version of the code snippet:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CODEGEN_PROTO_BUFFER_READER_H
#define GRPCPP_IMPL_CODEGEN_PROTO_BUFFER_READER_H

// Includes the main implementation of the ProtoBufferReader support class
// This is the public-facing header that should be included by users
#include <grpcpp/support/proto_buffer_reader.h>

#endif  // GRPCPP_IMPL_CODEGEN_PROTO_BUFFER_READER_H
```

The comments explain:
1. The copyright notice at the top
2. The purpose of the header guard (#ifndef/#define)
3. The purpose of the include statement (pointing to the public-facing header)
4. The closing of the header guard with a descriptive comment

This is a typical C++ header file structure that:
- Prevents multiple inclusions
- Serves as a forwarding header to the actual implementation
- Maintains clean separation between internal and public headers in the gRPC library