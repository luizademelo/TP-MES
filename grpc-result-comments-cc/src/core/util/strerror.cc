Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Header file for string error utility functions
#include "src/core/util/strerror.h"

// Platform-specific support and string handling headers
#include <grpc/support/port_platform.h>
#include <string.h>

// Abseil string formatting utilities
#include "absl/strings/str_format.h"

namespace grpc_core {

// Platform-specific implementation of StrError function
#ifdef GPR_WINDOWS
// Windows implementation of StrError
// Simply wraps the standard strerror function
std::string StrError(int err) { return strerror(err); }
#else
// Portable implementation of StrError for non-Windows platforms
// Handles both GNU and XSI-compliant versions of strerror_r
std::string StrError(int err) {
  // Helper struct to handle different strerror_r implementations
  struct Finish {
    // Handles XSI-compliant version (returns int, writes to buffer)
    static std::string Run(char* buf, int err, int r) {
      // On success (r == 0), return the error message from buffer
      // On failure, return a formatted error string
      if (r == 0) return buf;
      return absl::StrFormat("strerror_r(%d) failed: %d", err, r);
    }
    // Handles GNU version (returns char* pointing to message)
    static std::string Run(char*, int, const char* r) { return r; }
  };
  
  // Buffer to hold error message
  char buf[256];
  // Call strerror_r and dispatch to appropriate Finish::Run handler
  // The template magic will select the correct overload based on strerror_r's return type
  return Finish::Run(buf, err, strerror_r(err, buf, sizeof(buf)));
}
#endif

}  // namespace grpc_core
```

Key points explained in the comments:
1. The overall purpose of the file (string error utilities)
2. Platform-specific implementations (Windows vs others)
3. The dual behavior handling of strerror_r (GNU vs XSI variants)
4. The template magic that selects the correct handler based on strerror_r's return type
5. The buffer management for error messages
6. The error handling for cases where strerror_r fails

The comments maintain a balance between explaining the high-level purpose and the technical details needed for maintenance.