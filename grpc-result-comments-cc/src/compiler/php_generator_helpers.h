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

#ifndef GRPC_INTERNAL_COMPILER_PHP_GENERATOR_HELPERS_H
#define GRPC_INTERNAL_COMPILER_PHP_GENERATOR_HELPERS_H

#include <algorithm>

#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"

namespace grpc_php_generator {

// Generates PHP service class name based on service descriptor and parameters
// Args:
//   service: Protobuf service descriptor
//   class_suffix: Optional suffix to append to class name
//   is_server: Boolean indicating if this is for server-side code
// Returns:
//   Formatted PHP class name as string
inline std::string GetPHPServiceClassname(
    const grpc::protobuf::ServiceDescriptor* service,
    const std::string& class_suffix, bool is_server) {
  return std::string(service->name()) +
         (class_suffix == "" ? (is_server ? "" : "Client") : class_suffix) +
         (is_server ? "Stub" : "");
}

// Replaces all occurrences of 'search' string with 'replace' string in 's'
// Args:
//   s: Original string to perform replacements on
//   search: Substring to search for
//   replace: Replacement substring
// Returns:
//   Modified string with all replacements made
inline std::string ReplaceAll(std::string s, const std::string& search,
                              const std::string& replace) {
  size_t pos = 0;
  while ((pos = s.find(search, pos)) != std::string::npos) {
    s.replace(pos, search.length(), replace);
    pos += replace.length();
  }
  return s;
}

// Generates PHP service filename based on file descriptor, service descriptor, and parameters
// Args:
//   file: Protobuf file descriptor
//   service: Protobuf service descriptor
//   class_suffix: Optional suffix to append to class name
//   is_server: Boolean indicating if this is for server-side code
// Returns:
//   Full PHP file path as string
inline std::string GetPHPServiceFilename(
    const grpc::protobuf::FileDescriptor* file,
    const grpc::protobuf::ServiceDescriptor* service,
    const std::string& class_suffix, bool is_server) {
  std::ostringstream oss;
  
  // Handle PHP namespace if specified in file options
  if (file->options().has_php_namespace()) {
    oss << ReplaceAll(file->options().php_namespace(), "\\", "/");
  } else {
    // Fall back to package name if no PHP namespace specified
    std::vector<std::string> tokens =
        grpc_generator::tokenize(std::string(file->package()), ".");
    for (unsigned int i = 0; i < tokens.size(); i++) {
      oss << (i == 0 ? "" : "/")
          << grpc_generator::CapitalizeFirstLetter(tokens[i]);
    }
  }
  
  // Construct full file path
  std::string path = oss.str();
  if (!path.empty()) path += "/";
  path += GetPHPServiceClassname(service, class_suffix, is_server) + ".php";
  return path;
}

// Extracts and formats comments from descriptor objects
// Template Args:
//   DescriptorType: Type of descriptor (service, method, etc.)
// Args:
//   desc: Descriptor object to extract comments from
//   prefix: String prefix to add to each comment line
// Returns:
//   Formatted comments as string with special characters escaped
template <typename DescriptorType>
inline std::string GetPHPComments(const DescriptorType* desc,
                                  std::string prefix) {
  return ReplaceAll(grpc_generator::GetPrefixedComments(desc, true, prefix),
                    "*/", "&#42;/");
}

}  // namespace grpc_php_generator

#endif  // GRPC_INTERNAL_COMPILER_PHP_GENERATOR_HELPERS_H
```

The comments added explain:
1. The purpose of each function
2. The parameters they accept
3. What they return
4. Key logic points within the functions
5. Special handling cases (like PHP namespace vs package name fallback)
6. Template parameters where applicable

The comments are formatted to be clear and helpful for future maintainers while not being overly verbose. They follow a consistent style and provide enough context to understand the code's purpose and behavior.