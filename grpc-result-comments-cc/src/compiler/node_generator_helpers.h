Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2016 gRPC authors.
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

#ifndef GRPC_INTERNAL_COMPILER_NODE_GENERATOR_HELPERS_H
#define GRPC_INTERNAL_COMPILER_NODE_GENERATOR_HELPERS_H

#include <algorithm>

#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"

// Namespace for Node.js gRPC code generation utilities
namespace grpc_node_generator {

/**
 * Generates the filename for the JavaScript service file by appending
 * '_grpc_pb.js' to the base filename (with .proto extension removed).
 * 
 * @param filename The original .proto filename
 * @return The generated JavaScript service filename
 */
inline std::string GetJSServiceFilename(const std::string& filename) {
  return grpc_generator::StripProto(filename) + "_grpc_pb.js";
}

/**
 * Retrieves comments from a descriptor and formats them as JavaScript comments.
 * 
 * @tparam DescriptorType The type of descriptor (e.g., ServiceDescriptor)
 * @param desc Pointer to the descriptor containing comments
 * @param leading Whether to get leading comments (true) or trailing comments (false)
 * @return Formatted comments with '//' prefix for each line
 */
template <typename DescriptorType>
inline std::string GetNodeComments(const DescriptorType* desc, bool leading) {
  return grpc_generator::GetPrefixedComments(desc, leading, "//");
}

}  // namespace grpc_node_generator

#endif  // GRPC_INTERNAL_COMPILER_NODE_GENERATOR_HELPERS_H
```

Key improvements made:
1. Added namespace documentation explaining its purpose
2. Added detailed function documentation for both functions including:
   - Purpose of each function
   - Parameter descriptions
   - Return value description
3. Added template parameter documentation for GetNodeComments
4. Added clear closing comment for the namespace
5. Added clear closing comment for the header guard
6. Maintained all existing copyright and license information

The comments now provide clear context about what each component does, making it easier for future developers to understand and maintain the code.