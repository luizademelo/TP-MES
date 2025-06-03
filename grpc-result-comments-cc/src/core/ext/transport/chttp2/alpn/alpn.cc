Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/alpn/alpn.h"
#include <grpc/support/port_platform.h>
#include "absl/log/check.h"
#include "src/core/util/useful.h"

// Array of supported ALPN (Application-Layer Protocol Negotiation) versions
// Currently only supports HTTP/2 ("h2")
static const char* const supported_versions[] = {"h2"};

/// Checks if the given protocol version is supported by comparing it against
/// the list of supported ALPN versions.
/// @param version The protocol version string to check
/// @param size Length of the version string
/// @return 1 if the version is supported, 0 otherwise
int grpc_chttp2_is_alpn_version_supported(const char* version, size_t size) {
  size_t i;
  // Iterate through all supported versions
  for (i = 0; i < GPR_ARRAY_SIZE(supported_versions); i++) {
    // Check if string length matches and content is identical
    if (size == strlen(supported_versions[i]) &&
        !strncmp(version, supported_versions[i], size)) {
      return 1;
    }
  }
  return 0;
}

/// Returns the number of supported ALPN versions
/// @return Count of supported ALPN versions
size_t grpc_chttp2_num_alpn_versions(void) {
  return GPR_ARRAY_SIZE(supported_versions);
}

/// Gets the ALPN version string at the specified index
/// @param i Index of the version to retrieve
/// @return The version string at the given index
/// @note Performs bounds checking and will abort if index is out of bounds
const char* grpc_chttp2_get_alpn_version_index(size_t i) {
  CHECK_LT(i, GPR_ARRAY_SIZE(supported_versions));
  return supported_versions[i];
}
```

Key improvements made:
1. Added documentation for the supported_versions array
2. Added detailed function documentation using /// comments
3. Added parameter and return value documentation
4. Added inline comments to explain the logic within functions
5. Noted the bounds checking behavior in get_alpn_version_index
6. Maintained consistent comment style throughout

The comments now clearly explain:
- What each function does
- What parameters they take
- What they return
- Any important implementation details
- The purpose of the supported_versions array