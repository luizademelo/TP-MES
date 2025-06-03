Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_SURFACE_VALIDATE_METADATA_H
#define GRPC_SRC_CORE_LIB_SURFACE_VALIDATE_METADATA_H

#include <grpc/slice.h>                // For grpc_slice type
#include <grpc/support/port_platform.h> // Platform-specific configurations
#include <stdint.h>                    // For uint8_t

#include <cstring>                     // For memcmp

#include "absl/log/check.h"            // For DCHECK macro
#include "absl/strings/string_view.h"  // For absl::string_view
#include "src/core/lib/iomgr/error.h"  // For grpc_error_handle

namespace grpc_core {

// Enumeration of possible metadata validation results
enum class ValidateMetadataResult : uint8_t {
  kOk,                    // Validation succeeded
  kCannotBeZeroLength,    // Metadata cannot be empty
  kTooLong,               // Metadata exceeds maximum allowed length
  kIllegalHeaderKey,      // Header key contains illegal characters
  kIllegalHeaderValue    // Header value contains illegal characters
};

// Converts a ValidateMetadataResult enum value to its string representation
const char* ValidateMetadataResultToString(ValidateMetadataResult result);

// Validates if a header key is legal according to HTTP/2 specifications
ValidateMetadataResult ValidateHeaderKeyIsLegal(absl::string_view key);

} // namespace grpc_core

// Validates if a header key (in grpc_slice format) is legal
// Returns a grpc_error_handle indicating validation result
grpc_error_handle grpc_validate_header_key_is_legal(const grpc_slice& slice);

// Validates if a non-binary header value (in grpc_slice format) is legal
// Returns a grpc_error_handle indicating validation result
grpc_error_handle grpc_validate_header_nonbin_value_is_legal(
    const grpc_slice& slice);

// Checks if the given slice represents a binary header
int grpc_is_binary_header_internal(const grpc_slice& slice);

// Checks if a buffer represents a binary header by looking for "-bin" suffix
// buf: pointer to the header key bytes
// length: length of the header key
// Returns 1 if binary header, 0 otherwise
inline int grpc_key_is_binary_header(const uint8_t* buf, size_t length) {
  if (length < 5) return 0;  // Cannot be binary if shorter than 5 chars
  return 0 == memcmp(buf + length - 4, "-bin", 4);  // Check for "-bin" suffix
}

// Checks if a refcounted slice represents a binary header
// slice: the grpc_slice to check (must be refcounted)
// Returns 1 if binary header, 0 otherwise
inline int grpc_is_refcounted_slice_binary_header(const grpc_slice& slice) {
  DCHECK_NE(slice.refcount, nullptr);  // Ensure slice is refcounted
  return grpc_key_is_binary_header(slice.data.refcounted.bytes,
                                   slice.data.refcounted.length);
}

#endif // GRPC_SRC_CORE_LIB_SURFACE_VALIDATE_METADATA_H
```

The comments explain:
1. The purpose of each include directive
2. The meaning of each enum value in ValidateMetadataResult
3. The functionality of each function/method
4. Parameters and return values for each function
5. Important implementation details
6. The header guard purpose

The comments are concise yet informative, helping future developers understand the code's purpose and functionality without being overly verbose.