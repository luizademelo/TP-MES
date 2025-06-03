Here's the commented version of the code snippet:

```c++
// Copyright 2018 gRPC authors.
// This file is part of the gRPC++ library and contains the completion queue header guard.

// Header guard to prevent multiple inclusions of this file
#ifndef GRPCXX_COMPLETION_QUEUE_H
#define GRPCXX_COMPLETION_QUEUE_H

// Include the actual implementation of the completion queue functionality
// from the gRPC++ library
#include <grpcpp/completion_queue.h>

// End of header guard
#endif
```

The comments explain:
1. The copyright notice and brief file purpose
2. The purpose of the header guard (a standard C++ practice to prevent multiple inclusions)
3. What the included header provides
4. The closing of the header guard

The file appears to be a simple wrapper header that mainly serves to provide the header guard for the actual implementation in `<grpcpp/completion_queue.h>`.