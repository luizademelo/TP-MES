Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Platform-specific header for portability
#include <grpc/support/port_platform.h>

// Only compile this code for Windows environments
#ifdef GPR_WINDOWS_ENV

#include <windows.h>
#include <memory>

// Project-specific headers for environment variable utilities
#include "src/core/util/env.h"
#include "src/core/util/tchar.h"

namespace grpc_core {

// Function to get an environment variable value
// Parameters:
//   name - The name of the environment variable to retrieve
// Returns:
//   std::optional<std::string> - The value if variable exists, std::nullopt otherwise
std::optional<std::string> GetEnv(const char* name) {
  // Convert the variable name to Windows TCHAR format
  auto tname = CharToTchar(name);
  
  // First call to GetEnvironmentVariable gets the required buffer size
  DWORD ret = GetEnvironmentVariable(tname.c_str(), NULL, 0);
  if (ret == 0) return std::nullopt;  // Variable doesn't exist
  
  // Allocate buffer for the environment variable value
  std::unique_ptr<TCHAR[]> tresult(new TCHAR[ret]);
  
  // Second call actually retrieves the value
  ret = GetEnvironmentVariable(tname.c_str(), tresult.get(), ret * sizeof(TCHAR));
  if (ret == 0) return std::nullopt;  // Failed to retrieve value
  
  // Convert the result from TCHAR to regular char and return
  return TcharToChar(tresult.get());
}

// Function to set an environment variable
// Parameters:
//   name - The name of the environment variable to set
//   value - The value to set for the environment variable
// Throws:
//   Aborts the program if the operation fails
void SetEnv(const char* name, const char* value) {
  // Convert both name and value to Windows TCHAR format
  BOOL res = SetEnvironmentVariable(CharToTchar(name).c_str(),
                                    CharToTchar(value).c_str());
  if (!res) abort();  // Abort if setting the variable fails
}

// Function to unset/delete an environment variable
// Parameters:
//   name - The name of the environment variable to remove
// Throws:
//   Aborts the program if the operation fails
void UnsetEnv(const char* name) {
  // Convert name to Windows TCHAR format and set to NULL to delete
  BOOL res = SetEnvironmentVariable(CharToTchar(name).c_str(), NULL);
  if (!res) abort();  // Abort if unsetting the variable fails
}

}  // namespace grpc_core

#endif  // GPR_WINDOWS_ENV
```

The comments explain:
1. The purpose of each function
2. The parameters and return values
3. The key steps in each function's logic
4. Error handling behavior
5. Platform-specific considerations (Windows TCHAR conversions)
6. The scope of the code (Windows-only compilation)

The comments are designed to help future maintainers understand:
- What the code does
- Why certain implementation choices were made
- How to use the functions correctly
- What to expect in terms of behavior and error handling