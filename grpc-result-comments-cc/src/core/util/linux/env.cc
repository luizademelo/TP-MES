Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Ensure GNU extensions are available (for secure_getenv on Linux)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <grpc/support/port_platform.h>  // Platform-specific configuration

#include <optional>  // For std::optional
#include <string>    // For std::string

// Only compile this block for Linux environments
#ifdef GPR_LINUX_ENV

#include <features.h>  // For __GLIBC__ version macros
#include <stdlib.h>    // For environment variable functions

#include "src/core/util/env.h"  // Header for these implementations

namespace grpc_core {

// Gets an environment variable value safely
// Returns std::nullopt if variable is not set, or its value otherwise
std::optional<std::string> GetEnv(const char* name) {
  char* result = nullptr;
  // Use secure_getenv if available (glibc >= 2.17) and not forced to use getenv
  // secure_getenv is more secure as it's not affected by LD_PRELOAD
#if (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 17)) && \
    !defined(GRPC_FORCE_UNSECURE_GETENV)
  result = secure_getenv(name);
#else
  // Fall back to standard getenv if secure_getenv isn't available
  result = getenv(name);
#endif
  if (result == nullptr) return std::nullopt;
  return result;
}

// Sets an environment variable
// Aborts the program if the operation fails
void SetEnv(const char* name, const char* value) {
  // setenv with overwrite flag (1) to replace existing value
  int res = setenv(name, value, 1);
  if (res != 0) abort();  // Terminate on failure
}

// Unsets/removes an environment variable
// Aborts the program if the operation fails
void UnsetEnv(const char* name) {
  int res = unsetenv(name);
  if (res != 0) abort();  // Terminate on failure
}

}  // namespace grpc_core

#endif  // GPR_LINUX_ENV
```

The comments explain:
1. The purpose of each section and important macros
2. The security considerations around environment variable access
3. The behavior of each function including error handling
4. The version-specific logic for choosing between secure_getenv and getenv
5. The abort behavior on failure for SetEnv/UnsetEnv operations
6. The return value semantics for GetEnv

The comments are designed to help maintainers understand both the what and the why behind the implementation choices.