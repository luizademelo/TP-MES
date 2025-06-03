Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#ifndef GRPCPP_XDS_SERVER_BUILDER_H
#define GRPCPP_XDS_SERVER_BUILDER_H

#include <grpc/support/port_platform.h>
#include <grpcpp/server_builder.h>

namespace grpc {

// Interface for receiving XDS server serving status updates.
// Implementations of this interface can be registered with XdsServerBuilder
// to receive notifications when the serving status changes.
class XdsServerServingStatusNotifierInterface {
 public:
  // Structure containing serving status update information
  struct ServingStatusUpdate {
    grpc::Status status;  // Status object containing code and message
  };

  virtual ~XdsServerServingStatusNotifierInterface() = default;

  // Called when the serving status for a particular URI is updated
  // @param uri: The URI whose serving status changed
  // @param update: The new serving status information
  virtual void OnServingStatusUpdate(std::string uri,
                                     ServingStatusUpdate update) = 0;
};

// XDS-enabled version of ServerBuilder that provides additional XDS-specific
// functionality for building and configuring gRPC servers.
class XdsServerBuilder : public grpc::ServerBuilder {
 public:
  // NOTE: class experimental_type is not part of the public API of this class
  //       and may change in future versions

  // Provides access to experimental features of XdsServerBuilder
  class experimental_type : public grpc::ServerBuilder::experimental_type {
   public:
    explicit experimental_type(XdsServerBuilder* builder)
        : ServerBuilder::experimental_type(builder), builder_(builder) {}

    // Sets the drain grace time in milliseconds for server shutdown
    // @param drain_grace_time_ms: Time in ms to wait for existing RPCs to complete
    //                             during server shutdown
    void set_drain_grace_time(int drain_grace_time_ms) {
      builder_->drain_grace_time_ms_ = drain_grace_time_ms;
    }

   private:
    XdsServerBuilder* builder_;  // Pointer to parent XdsServerBuilder
  };

  // Sets the status notifier that will receive serving status updates
  // @param notifier: Pointer to notifier implementation (can be nullptr)
  void set_status_notifier(XdsServerServingStatusNotifierInterface* notifier) {
    notifier_ = notifier;
  }

  /// NOTE: The function experimental() is not stable public API. It is a view
  /// to the experimental features which may change or be removed at any time
  
  // Provides access to experimental features
  // @return: experimental_type object providing access to experimental methods
  experimental_type experimental() { return experimental_type(this); }

 private:
  // Builds and returns the channel arguments with XDS-specific configurations
  ChannelArguments BuildChannelArgs() override;

  // Callback function for handling serving status updates from the core
  // @param user_data: Pointer to the status notifier instance
  // @param uri: The URI whose status changed
  // @param update: The status update from the core
  static void OnServingStatusUpdate(void* user_data, const char* uri,
                                    grpc_serving_status_update update) {
    if (user_data == nullptr) return;
    XdsServerServingStatusNotifierInterface* notifier =
        static_cast<XdsServerServingStatusNotifierInterface*>(user_data);
    notifier->OnServingStatusUpdate(
        uri, {grpc::Status(static_cast<StatusCode>(update.code),
                           update.error_message)});
  }

  XdsServerServingStatusNotifierInterface* notifier_ = nullptr;  // Status update notifier
  int drain_grace_time_ms_ = -1;  // Grace period for server shutdown (-1 means default)
};

}

#endif
```

Key improvements in the comments:
1. Added class-level documentation explaining the purpose of each class
2. Added detailed parameter descriptions for methods
3. Documented the purpose of each member variable
4. Clarified the experimental nature of certain APIs
5. Added documentation for the callback mechanism
6. Explained the significance of default values
7. Added cross-references between related components

The comments now provide a comprehensive understanding of the code's functionality while maintaining clarity and conciseness.