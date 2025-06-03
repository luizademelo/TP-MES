Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_STACK_TYPE_H
#define GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_STACK_TYPE_H

// Includes platform-specific support macros and types
#include <grpc/support/port_platform.h>

// Enum defining different types of channel stacks in gRPC
typedef enum {
  // Standard client channel type for making RPC calls
  GRPC_CLIENT_CHANNEL,
  
  // Subchannel type representing a connection to a single backend
  GRPC_CLIENT_SUBCHANNEL,
  
  // Dynamic channel type that can be reconfigured
  GRPC_CLIENT_DYNAMIC,
  
  // "Lame" channel type that will fail all operations (used for error cases)
  GRPC_CLIENT_LAME_CHANNEL,
  
  // Direct channel type that bypasses load balancing
  GRPC_CLIENT_DIRECT_CHANNEL,
  
  // Server channel type for handling incoming RPC calls
  GRPC_SERVER_CHANNEL,
  
  // Sentinel value representing the total number of channel stack types
  GRPC_NUM_CHANNEL_STACK_TYPES
} grpc_channel_stack_type;

// Function to check if a channel stack type is a client type
// @param type The channel stack type to check
// @return true if the type is a client type, false otherwise
bool grpc_channel_stack_type_is_client(grpc_channel_stack_type type);

// Function to get a string representation of a channel stack type
// @param type The channel stack type to convert to string
// @return const char* pointing to the string representation
const char* grpc_channel_stack_type_string(grpc_channel_stack_type type);

#endif  // GRPC_SRC_CORE_LIB_SURFACE_CHANNEL_STACK_TYPE_H
```

The comments explain:
1. The purpose of the header guard
2. The platform support include
3. Each enum value's specific purpose
4. The purpose and parameters of each function
5. The return values of the functions

The comments are concise yet provide enough information for a developer to understand the purpose and usage of each component without needing to dive into implementation details.