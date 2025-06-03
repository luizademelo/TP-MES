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

#ifndef GRPC_INTERNAL_COMPILER_CSHARP_GENERATOR_HELPERS_H
#define GRPC_INTERNAL_COMPILER_CSHARP_GENERATOR_HELPERS_H

#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"

namespace grpc_csharp_generator {

// Generates the output filename for C# service files based on the protobuf file descriptor
// Parameters:
//   file: Protobuf file descriptor containing service definitions
//   file_suffix: Suffix to append to the generated filename
//   base_namespace_present: Flag indicating if a base namespace is specified
//   base_namespace: The base namespace for the generated code
//   out_file: Output parameter for the generated filename
//   error: Output parameter for error messages
// Returns:
//   true if filename was generated successfully, false otherwise
inline bool ServicesFilename(const grpc::protobuf::FileDescriptor* file,
                             const std::string& file_suffix,
                             const bool base_namespace_present,
                             const std::string& base_namespace,
                             std::string& out_file, std::string* error) {

  if (!base_namespace_present) {
    // If no base namespace is specified, generate filename in UpperCamelCase
    out_file = grpc_generator::FileNameInUpperCamel(file, false) + file_suffix;
  } else {
    // If base namespace is specified, use custom C# filename generation
    out_file = GRPC_CUSTOM_CSHARP_GETOUTPUTFILE(file, file_suffix, true,
                                                base_namespace, error);
    if (out_file.empty()) {
      // Return false if custom filename generation failed
      return false;
    }
  }
  return true;
}

// Generates C# style comments from protobuf descriptor comments
// Template Parameters:
//   DescriptorType: Type of descriptor (e.g., ServiceDescriptor, MethodDescriptor)
// Parameters:
//   desc: Pointer to the descriptor object
//   leading: Flag indicating whether to get leading comments (true) or trailing comments (false)
// Returns:
//   Formatted comments as a string with C# style comment markers ("//")
template <typename DescriptorType>
inline std::string GetCsharpComments(const DescriptorType* desc, bool leading) {
  return grpc_generator::GetPrefixedComments(desc, leading, "//");
}

}

#endif
```

The comments I've added:
1. Explained the purpose and functionality of the ServicesFilename function
2. Documented all parameters and return values for ServicesFilename
3. Added details about the two different filename generation paths
4. Explained the GetCsharpComments template function
5. Documented the template parameter and function parameters
6. Added information about the return value format

The comments are designed to help future developers understand:
- What each function does
- How to use each function
- The expected inputs and outputs
- The different code paths and their purposes
- The relationship between these helper functions and the larger code generation system