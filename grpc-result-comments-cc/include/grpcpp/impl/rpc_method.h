Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_RPC_METHOD_H
#define GRPCPP_IMPL_RPC_METHOD_H

#include <grpcpp/impl/codegen/channel_interface.h>
#include <memory>

namespace grpc {
namespace internal {

// Represents an RPC method and its characteristics
class RpcMethod {
 public:
  // Enum defining different types of RPC methods
  enum RpcType {
    NORMAL_RPC = 0,        // Unary RPC: single request, single response
    CLIENT_STREAMING,      // Client streams multiple requests, single response
    SERVER_STREAMING,      // Single request, server streams multiple responses
    BIDI_STREAMING         // Both client and server stream messages
  };

  // Constructor for basic RPC method without stats suffix or channel
  // @param name: The name of the RPC method
  // @param type: The type of RPC (from RpcType enum)
  RpcMethod(const char* name, RpcType type)
      : name_(name),
        suffix_for_stats_(nullptr),
        method_type_(type),
        channel_tag_(nullptr) {}

  // Constructor for RPC method with stats suffix but no channel
  // @param name: The name of the RPC method
  // @param suffix_for_stats: Suffix used for statistics collection
  // @param type: The type of RPC (from RpcType enum)
  RpcMethod(const char* name, const char* suffix_for_stats, RpcType type)
      : name_(name),
        suffix_for_stats_(suffix_for_stats),
        method_type_(type),
        channel_tag_(nullptr) {}

  // Constructor for RPC method with channel but no stats suffix
  // @param name: The name of the RPC method
  // @param type: The type of RPC (from RpcType enum)
  // @param channel: Channel interface to register the method with
  RpcMethod(const char* name, RpcType type,
            const std::shared_ptr<ChannelInterface>& channel)
      : name_(name),
        suffix_for_stats_(nullptr),
        method_type_(type),
        channel_tag_(channel->RegisterMethod(name)) {}

  // Constructor for RPC method with both stats suffix and channel
  // @param name: The name of the RPC method
  // @param suffix_for_stats: Suffix used for statistics collection
  // @param type: The type of RPC (from RpcType enum)
  // @param channel: Channel interface to register the method with
  RpcMethod(const char* name, const char* suffix_for_stats, RpcType type,
            const std::shared_ptr<ChannelInterface>& channel)
      : name_(name),
        suffix_for_stats_(suffix_for_stats),
        method_type_(type),
        channel_tag_(channel->RegisterMethod(name)) {}

  // Getter for method name
  const char* name() const { return name_; }
  
  // Getter for stats suffix
  const char* suffix_for_stats() const { return suffix_for_stats_; }
  
  // Getter for RPC type
  RpcType method_type() const { return method_type_; }
  
  // Setter for RPC type
  void SetMethodType(RpcType type) { method_type_ = type; }
  
  // Getter for channel tag (used for registration)
  void* channel_tag() const { return channel_tag_; }

 private:
  const char* const name_;            // The name of the RPC method
  const char* const suffix_for_stats_; // Optional suffix for statistics
  RpcType method_type_;               // Type of RPC method
  void* const channel_tag_;           // Tag used for channel registration
};

}  // namespace internal
}  // namespace grpc

#endif  // GRPCPP_IMPL_RPC_METHOD_H
```

Key improvements made:
1. Added detailed class description
2. Documented the RpcType enum values
3. Added detailed parameter descriptions for all constructors
4. Documented all getter/setter methods
5. Added comments for private member variables
6. Improved namespace closing comments
7. Added comment for the header guard closing
8. Organized comments consistently with proper spacing

The comments now provide clear documentation about:
- The purpose of the class
- What each RPC type represents
- What each constructor variant is for
- The purpose of each member variable
- The functionality of each method