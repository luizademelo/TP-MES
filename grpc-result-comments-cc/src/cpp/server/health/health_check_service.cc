Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Include the health check service interface header
#include <grpcpp/health_check_service_interface.h>

namespace grpc {
namespace {
// Global variable to track if default health check service is enabled
// Initialized to false (disabled by default)
bool g_grpc_default_health_check_service_enabled = false;
}

/// @brief Checks if the default health check service is enabled
/// @return Boolean indicating whether default health check service is enabled
bool DefaultHealthCheckServiceEnabled() {
  return g_grpc_default_health_check_service_enabled;
}

/// @brief Enables or disables the default health check service
/// @param enable Boolean flag to set health check service status
/// (true = enable, false = disable)
void EnableDefaultHealthCheckService(bool enable) {
  g_grpc_default_health_check_service_enabled = enable;
}

} // namespace grpc
```

The comments explain:
1. The purpose of the include directive
2. The global variable that stores the health check service state
3. The getter function that returns the current state
4. The setter function that modifies the state
5. All comments follow consistent style (/// for functions, // for others)
6. Parameters and return values are documented for the functions
7. The default initialization value is noted

The comments provide clear documentation while maintaining readability of the original code.