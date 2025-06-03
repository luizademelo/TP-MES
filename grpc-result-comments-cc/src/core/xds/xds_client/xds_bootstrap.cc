Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#include "src/core/xds/xds_client/xds_bootstrap.h"

#include <grpc/support/port_platform.h>

#include <optional>

#include "src/core/util/env.h"
#include "src/core/util/string.h"

namespace grpc_core {

// Checks if XDS federation feature is enabled by reading the environment variable.
// Returns:
//   - true if GRPC_EXPERIMENTAL_XDS_FEDERATION is not set (default enabled)
//   - true if GRPC_EXPERIMENTAL_XDS_FEDERATION is set to a truthy value ("1", "true", etc.)
//   - false if GRPC_EXPERIMENTAL_XDS_FEDERATION is set to a falsy value or cannot be parsed
bool XdsFederationEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_FEDERATION");
  if (!value.has_value()) return true;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

// Checks if XDS data error handling feature is enabled by reading the environment variable.
// Returns:
//   - false if GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING is not set (default disabled)
//   - true if GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING is set to a truthy value
//   - false if GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING is set to a falsy value or cannot be parsed
bool XdsDataErrorHandlingEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  if (!value.has_value()) return false;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each function
2. The environment variable each function checks
3. The default behavior when the variable isn't set
4. The return value logic based on the environment variable's value
5. The namespace closing comment for better readability

The comments are clear and concise while providing all the necessary information about the functions' behaviors and their interaction with environment variables.