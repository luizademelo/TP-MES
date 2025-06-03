Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_STATUS_CONVERSION_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_STATUS_CONVERSION_H

// Include necessary headers
#include <grpc/status.h>                  // For grpc_status_code
#include <grpc/support/port_platform.h>   // For platform-specific definitions

// Project-specific headers
#include "src/core/ext/transport/chttp2/transport/http2_status.h"  // For Http2ErrorCode
#include "src/core/util/time.h"           // For Timestamp

// Converts a gRPC status code to an HTTP/2 error code
// @param status The gRPC status code to convert
// @return Corresponding HTTP/2 error code
grpc_core::http2::Http2ErrorCode grpc_status_to_http2_error(
    grpc_status_code status);

// Converts an HTTP/2 error code to a gRPC status code
// @param error The HTTP/2 error code to convert
// @param deadline The deadline timestamp for context
// @return Corresponding gRPC status code
grpc_status_code grpc_http2_error_to_grpc_status(
    grpc_core::http2::Http2ErrorCode error, grpc_core::Timestamp deadline);

// Converts an HTTP/2 status code to a gRPC status code
// @param status The HTTP/2 status code to convert
// @return Corresponding gRPC status code
grpc_status_code grpc_http2_status_to_grpc_status(int status);

// Converts a gRPC status code to an HTTP/2 status code
// @param status The gRPC status code to convert
// @return Corresponding HTTP/2 status code
int grpc_status_to_http2_status(grpc_status_code status);

#endif  // GRPC_SRC_CORE_LIB_TRANSPORT_STATUS_CONVERSION_H
```

The comments explain:
1. The purpose of the header guard
2. The included headers and their purposes
3. Each function's purpose, parameters, and return values
4. The closing of the header guard

The comments follow a consistent style and provide clear documentation about the conversion utilities between gRPC and HTTP/2 status codes.