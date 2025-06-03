Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_IMPL_SERVER_BUILDER_PLUGIN_H
#define GRPCPP_IMPL_SERVER_BUILDER_PLUGIN_H

// Include necessary headers
#include <grpcpp/support/channel_arguments.h>  // For ChannelArguments class
#include <grpcpp/support/config.h>             // For gRPC configuration
#include <memory>                              // For std::shared_ptr, etc.

namespace grpc {

// Forward declarations
class ServerBuilder;
class ServerInitializer;

/// @class ServerBuilderPlugin
/// @brief Abstract base class for plugins that can extend ServerBuilder functionality.
/// This class defines the interface for plugins that can modify server configuration
/// during different stages of server initialization.
class ServerBuilderPlugin {
 public:
  virtual ~ServerBuilderPlugin() {}  // Virtual destructor for proper cleanup

  /// @brief Returns the name of the plugin
  /// @return The plugin name as a string
  virtual std::string name() = 0;

  /// @brief Called to allow the plugin to modify the ServerBuilder
  /// @param builder Pointer to the ServerBuilder being configured
  virtual void UpdateServerBuilder(ServerBuilder* builder) {}

  /// @brief Called during server initialization
  /// @param si Pointer to the ServerInitializer
  virtual void InitServer(ServerInitializer* si) = 0;

  /// @brief Called when server initialization is complete
  /// @param si Pointer to the ServerInitializer
  virtual void Finish(ServerInitializer* si) = 0;

  /// @brief Allows the plugin to modify arguments
  /// @param name The name of the argument to change
  /// @param value Pointer to the argument value to modify
  virtual void ChangeArguments(const std::string& name, void* value) = 0;

  /// @brief Called to allow the plugin to modify channel arguments
  /// @param args Pointer to the ChannelArguments object
  virtual void UpdateChannelArguments(ChannelArguments* args) {}

  /// @brief Indicates if the plugin has synchronous methods
  /// @return true if the plugin has sync methods, false otherwise
  virtual bool has_sync_methods() const { return false; }

  /// @brief Indicates if the plugin has asynchronous methods
  /// @return true if the plugin has async methods, false otherwise
  virtual bool has_async_methods() const { return false; }
};

}  // namespace grpc

#endif  // GRPCPP_IMPL_SERVER_BUILDER_PLUGIN_H
```

The comments provide:
1. File-level documentation about the purpose of the header
2. Explanation of each include directive
3. Detailed documentation for each class and method
4. Parameter and return value descriptions
5. Notes about virtual functions and their purposes
6. Clear separation between different sections of the code

The comments follow a consistent style and provide enough information for future developers to understand how to implement and use ServerBuilderPlugin classes.