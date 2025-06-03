Here's the commented version of the code:

```c++
// Copyright 2021 The gRPC Authors

// Header file for ChannelArgsEndpointConfig implementation
#include "src/core/lib/event_engine/channel_args_endpoint_config.h"

// Required headers for EventEngine functionality and platform support
#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

// Standard library headers for optional values and strings
#include <optional>
#include <string>

// Channel args utilities from gRPC core
#include "src/core/lib/channel/channel_args.h"

namespace grpc_event_engine::experimental {

// Gets an integer value associated with the given key from channel args
// Parameters:
//   key - The string key to look up in the channel args
// Returns:
//   optional<int> - The value if found, or nullopt if not present
std::optional<int> ChannelArgsEndpointConfig::GetInt(
    absl::string_view key) const {
  return args_.GetInt(key);
}

// Gets a string value associated with the given key from channel args
// Parameters:
//   key - The string key to look up in the channel args
// Returns:
//   optional<absl::string_view> - The string value if found, or nullopt if not present
std::optional<absl::string_view> ChannelArgsEndpointConfig::GetString(
    absl::string_view key) const {
  return args_.GetString(key);
}

// Gets a void pointer associated with the given key from channel args
// Special handling for GRPC_INTERNAL_ARG_EVENT_ENGINE key which returns an EventEngine object
// Parameters:
//   key - The string key to look up in the channel args
// Returns:
//   void* - The pointer value if found, nullptr otherwise
void* ChannelArgsEndpointConfig::GetVoidPointer(absl::string_view key) const {
  // Special case for EventEngine object retrieval
  if (key == GRPC_INTERNAL_ARG_EVENT_ENGINE) {
    return args_.GetObject<EventEngine>();
  }
  // Default case for other void pointer values
  return args_.GetVoidPointer(key);
}

}  // namespace grpc_event_engine::experimental
```

The comments provide:
1. File-level documentation about the purpose of the file
2. Explanation for each included header
3. Detailed documentation for each method including:
   - Purpose of the method
   - Parameter descriptions
   - Return value descriptions
   - Special cases or behaviors
4. Namespace closing comment for clarity

The comments are kept concise while providing all necessary information for maintenance and future development.