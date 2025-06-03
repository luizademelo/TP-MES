Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#include <grpcpp/impl/channel_argument_option.h>
#include <grpcpp/impl/server_builder_option.h>
#include <grpcpp/impl/server_builder_plugin.h>
#include <grpcpp/support/channel_arguments.h>

#include <memory>
#include <string>
#include <vector>

namespace grpc {

/// @brief Creates a ServerBuilderOption for setting a string channel argument
/// @param name The name of the channel argument to set
/// @param value The string value to set for the channel argument
/// @return A unique_ptr to a ServerBuilderOption that will set the string argument
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, const std::string& value) {
  // Implementation of ServerBuilderOption for string values
  class StringOption final : public ServerBuilderOption {
   public:
    StringOption(const std::string& name, const std::string& value)
        : name_(name), value_(value) {}

    /// @brief Sets the string channel argument when called
    /// @param args The ChannelArguments object to modify
    void UpdateArguments(ChannelArguments* args) override {
      args->SetString(name_, value_);
    }

    /// @brief No plugin updates needed for this option
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;    // Name of the channel argument
    const std::string value_;   // String value to set
  };
  return std::unique_ptr<ServerBuilderOption>(new StringOption(name, value));
}

/// @brief Creates a ServerBuilderOption for setting an integer channel argument
/// @param name The name of the channel argument to set
/// @param value The integer value to set for the channel argument
/// @return A unique_ptr to a ServerBuilderOption that will set the integer argument
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, int value) {
  // Implementation of ServerBuilderOption for integer values
  class IntOption final : public ServerBuilderOption {
   public:
    IntOption(const std::string& name, int value)
        : name_(name), value_(value) {}

    /// @brief Sets the integer channel argument when called
    /// @param args The ChannelArguments object to modify
    void UpdateArguments(ChannelArguments* args) override {
      args->SetInt(name_, value_);
    }

    /// @brief No plugin updates needed for this option
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;    // Name of the channel argument
    const int value_;           // Integer value to set
  };
  return std::unique_ptr<ServerBuilderOption>(new IntOption(name, value));
}

/// @brief Creates a ServerBuilderOption for setting a pointer channel argument
/// @param name The name of the channel argument to set
/// @param value The pointer value to set for the channel argument
/// @return A unique_ptr to a ServerBuilderOption that will set the pointer argument
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, void* value) {
  // Implementation of ServerBuilderOption for pointer values
  class PointerOption final : public ServerBuilderOption {
   public:
    PointerOption(const std::string& name, void* value)
        : name_(name), value_(value) {}

    /// @brief Sets the pointer channel argument when called
    /// @param args The ChannelArguments object to modify
    void UpdateArguments(ChannelArguments* args) override {
      args->SetPointer(name_, value_);
    }

    /// @brief No plugin updates needed for this option
    void UpdatePlugins(
        std::vector<std::unique_ptr<ServerBuilderPlugin>>* )
        override {}

   private:
    const std::string name_;    // Name of the channel argument
    void* value_;               // Pointer value to set
  };
  return std::unique_ptr<ServerBuilderOption>(new PointerOption(name, value));
}

}  // namespace grpc
```

Key improvements made:
1. Added detailed function-level documentation for each factory function
2. Added class-level comments explaining the purpose of each Option implementation
3. Documented each override method's purpose
4. Added comments for private member variables
5. Added namespace closing comment
6. Used consistent comment style (/// for documentation comments)
7. Explained the no-op behavior of UpdatePlugins methods
8. Added parameter and return value documentation

The comments now provide clear understanding of:
- What each function does
- What each class is for
- How the options will be applied
- The purpose of each method
- The meaning of member variables