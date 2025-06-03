Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/surface/channel_stack_type.h"
#include <grpc/support/port_platform.h>

/// Determines whether the given channel stack type is a client type.
/// 
/// @param type The channel stack type to check
/// @return true if the type represents a client channel, false if it represents
///         a server channel. For GRPC_NUM_CHANNEL_STACK_TYPES, this function
///         will trigger an assertion failure (GPR_UNREACHABLE_CODE).
bool grpc_channel_stack_type_is_client(grpc_channel_stack_type type) {
  switch (type) {
    case GRPC_CLIENT_CHANNEL:
      return true;
    case GRPC_CLIENT_SUBCHANNEL:
      return true;
    case GRPC_CLIENT_LAME_CHANNEL:
      return true;
    case GRPC_CLIENT_DIRECT_CHANNEL:
      return true;
    case GRPC_CLIENT_DYNAMIC:
      return true;
    case GRPC_SERVER_CHANNEL:
      return false;
    case GRPC_NUM_CHANNEL_STACK_TYPES:
      break;  // This case should never be reached in normal operation
  }
  // This macro handles unexpected cases (should never be reached)
  GPR_UNREACHABLE_CODE(return true;);
}

/// Returns a string representation of the given channel stack type.
/// 
/// @param type The channel stack type to convert to string
/// @return A const char* containing the string representation of the type.
///         For GRPC_NUM_CHANNEL_STACK_TYPES, this function will trigger an
///         assertion failure (GPR_UNREACHABLE_CODE) and return "UNKNOWN".
const char* grpc_channel_stack_type_string(grpc_channel_stack_type type) {
  switch (type) {
    case GRPC_CLIENT_CHANNEL:
      return "CLIENT_CHANNEL";
    case GRPC_CLIENT_SUBCHANNEL:
      return "CLIENT_SUBCHANNEL";
    case GRPC_SERVER_CHANNEL:
      return "SERVER_CHANNEL";
    case GRPC_CLIENT_LAME_CHANNEL:
      return "CLIENT_LAME_CHANNEL";
    case GRPC_CLIENT_DIRECT_CHANNEL:
      return "CLIENT_DIRECT_CHANNEL";
    case GRPC_CLIENT_DYNAMIC:
      return "CLIENT_DYNAMIC_CHANNEL";
    case GRPC_NUM_CHANNEL_STACK_TYPES:
      break;  // This case should never be reached in normal operation
  }
  // This macro handles unexpected cases (should never be reached)
  GPR_UNREACHABLE_CODE(return "UNKNOWN");
}
```

Key improvements in the comments:
1. Added detailed function-level documentation explaining purpose, parameters, and return values
2. Added comments explaining the special handling of GRPC_NUM_CHANNEL_STACK_TYPES
3. Explained the GPR_UNREACHABLE_CODE macro usage
4. Maintained consistent comment style (/// for documentation comments)
5. Clarified behavior for edge cases
6. Kept the original copyright notice intact

The comments now provide clear guidance for future developers about:
- What each function does
- The meaning of parameters and return values
- Special cases and edge conditions
- The purpose of the unreachable code macro