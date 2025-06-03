Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPCPP_IMPL_CHANNEL_ARGUMENT_OPTION_H
#define GRPCPP_IMPL_CHANNEL_ARGUMENT_OPTION_H

// Include necessary headers
#include <grpcpp/impl/server_builder_option.h>  // For ServerBuilderOption
#include <grpcpp/support/channel_arguments.h>    // For ChannelArguments functionality

// Standard library includes
#include <map>      // For std::map
#include <memory>   // For std::unique_ptr

namespace grpc {

// Creates a ServerBuilderOption for a channel argument with string value
// @param name: The name of the channel argument
// @param value: The string value to set for the argument
// @return: Unique pointer to the created ServerBuilderOption
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, const std::string& value);

// Creates a ServerBuilderOption for a channel argument with integer value
// @param name: The name of the channel argument
// @param value: The integer value to set for the argument
// @return: Unique pointer to the created ServerBuilderOption
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, int value);

// Creates a ServerBuilderOption for a channel argument with pointer value
// @param name: The name of the channel argument
// @param value: The pointer value to set for the argument
// @return: Unique pointer to the created ServerBuilderOption
std::unique_ptr<ServerBuilderOption> MakeChannelArgumentOption(
    const std::string& name, void* value);

}  // namespace grpc

#endif  // GRPCPP_IMPL_CHANNEL_ARGUMENT_OPTION_H
```

The comments explain:
1. The purpose of the header guard
2. The included headers and their purposes
3. The namespace declaration
4. Each function overload's purpose, parameters, and return value
5. The closing of the namespace and header guard

The comments are clear, concise, and provide useful information for future developers who might need to work with or modify this code.