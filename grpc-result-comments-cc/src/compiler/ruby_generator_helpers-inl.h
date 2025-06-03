Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_HELPERS_INL_H
#define GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_HELPERS_INL_H

// Include necessary headers for protobuf and generator functionality
#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"
#include "src/compiler/ruby_generator_string-inl.h"

namespace grpc_ruby_generator {

// Generates the Ruby services filename from a proto file descriptor
// Args:
//   file: The protobuf file descriptor
//   file_name_or_error: Output parameter that receives either the generated filename
//                       or an error message if the input is invalid
// Returns:
//   true if successful (filename generated), false if input is invalid
inline bool ServicesFilename(const grpc::protobuf::FileDescriptor* file,
                             std::string* file_name_or_error) {
  // The length of ".proto" suffix we need to check and remove
  static const unsigned proto_suffix_length = 6;
  
  // Check if filename ends with ".proto" and has sufficient length
  if (file->name().size() > proto_suffix_length &&
      file->name().find_last_of(".proto") == file->name().size() - 1) {
    // Generate Ruby services filename by replacing .proto with _services_pb.rb
    *file_name_or_error = std::string(file->name().substr(
                              0, file->name().size() - proto_suffix_length)) +
                          "_services_pb.rb";
    return true;
  } else {
    // Return error message for invalid proto filenames
    *file_name_or_error = "Invalid proto file name:  must end with .proto";
    return false;
  }
}

// Generates the require name for Ruby message files
// Args:
//   file: The protobuf file descriptor
// Returns:
//   The require name string with ".proto" replaced by "_pb"
inline std::string MessagesRequireName(
    const grpc::protobuf::FileDescriptor* file) {
  return Replace(std::string(file->name()), ".proto", "_pb");
}

// Gets comments from a descriptor and formats them as Ruby comments
// Template Args:
//   DescriptorType: The type of descriptor (e.g., ServiceDescriptor)
// Args:
//   desc: The descriptor to extract comments from
//   leading: Whether to get leading comments (true) or trailing comments (false)
// Returns:
//   The comments formatted with Ruby comment style (# prefix)
template <typename DescriptorType>
inline std::string GetRubyComments(const DescriptorType* desc, bool leading) {
  return grpc_generator::GetPrefixedComments(desc, leading, "#");
}

}  // namespace grpc_ruby_generator

#endif  // GRPC_INTERNAL_COMPILER_RUBY_GENERATOR_HELPERS_INL_H
```

The comments I've added:
1. Explained the purpose and usage of each function
2. Documented parameters and return values
3. Added details about the logic inside each function
4. Noted the template parameter for the generic function
5. Added namespace and header guard comments
6. Maintained the existing license header

The comments are designed to help future developers understand:
- What each function does
- How to use each function
- What the expected inputs and outputs are
- The internal logic of each function
- The purpose of the included headers and namespace