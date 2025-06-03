Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Platform-specific header for gRPC
#include <grpc/support/port_platform.h>

// This implementation is only compiled for platforms that are NOT Linux or Windows
#if !defined(GPR_LINUX) && !defined(GPR_WINDOWS)

// Includes for logging and GCP environment checking functionality
#include "absl/log/log.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/util/crash.h"

/**
 * Checks if the code is running on Google Cloud Platform (GCP) environment.
 * 
 * Note: This implementation is for non-Linux and non-Windows platforms.
 * Since ALTS is currently only supported on Linux and Windows,
 * this function always returns false and logs a warning.
 * 
 * @return bool Always returns false indicating not running on GCP for unsupported platforms
 */
bool grpc_alts_is_running_on_gcp() {
  // Log a verbose message indicating ALTS is not supported on this platform
  VLOG(2) << "ALTS: Platforms other than Linux and Windows are not supported";
  return false;
}

#endif  // !defined(GPR_LINUX) && !defined(GPR_WINDOWS)
```

The comments explain:
1. The platform-specific nature of the code (only for non-Linux/Windows)
2. The purpose of the included headers
3. The function's behavior and its always-false return value
4. The logging of unsupported platform message
5. The conditional compilation directive's purpose

The comments are structured to help maintainers understand:
- Why this implementation exists
- What it does (and doesn't do)
- The context around its limitations
- The expected behavior