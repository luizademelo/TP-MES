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

#ifndef GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_H
#define GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_H

// Include configuration settings for the compiler
#include "src/compiler/config.h"

// Namespace for Objective-C code generation utilities in gRPC
namespace grpc_objective_c_generator {

// Parameters structure to configure code generation behavior
struct Parameters {
  // Flag to indicate whether to generate code with V1 API compatibility
  bool no_v1_compatibility;
};

// Import commonly used protobuf types into current namespace
using ::grpc::protobuf::FileDescriptor;
using ::grpc::protobuf::ServiceDescriptor;

// Generates and returns all message classes for a given protobuf file
// @param file The protobuf file descriptor containing message definitions
// @return String containing all generated message classes
std::string GetAllMessageClasses(const FileDescriptor* file);

// Generates and returns the protocol for a given service
// @param service The service descriptor to generate protocol for
// @param generator_params Configuration parameters for code generation
// @return String containing the generated protocol
std::string GetProtocol(const ServiceDescriptor* service,
                        const Parameters& generator_params);

// Generates and returns the V2 protocol for a given service
// @param service The service descriptor to generate protocol for
// @return String containing the generated V2 protocol
std::string GetV2Protocol(const ServiceDescriptor* service);

// Generates and returns the interface for a given service
// @param service The service descriptor to generate interface for
// @param generator_params Configuration parameters for code generation
// @return String containing the generated interface
std::string GetInterface(const ServiceDescriptor* service,
                         const Parameters& generator_params);

// Generates and returns the implementation source for a given service
// @param service The service descriptor to generate source for
// @param generator_params Configuration parameters for code generation
// @return String containing the generated source code
std::string GetSource(const ServiceDescriptor* service,
                      const Parameters& generator_params);

}  // namespace grpc_objective_c_generator

#endif  // GRPC_INTERNAL_COMPILER_OBJECTIVE_C_GENERATOR_H
```

Key improvements made:
1. Added detailed comments for each function explaining their purpose and parameters
2. Added comments for the Parameters struct and its field
3. Added namespace documentation
4. Added comments for the include statement
5. Added clear indication of the namespace closure
6. Added comment for the header guard closure
7. Maintained all existing copyright and license information

The comments follow a consistent style and provide clear explanations of the code's functionality while being concise enough to not overwhelm the reader.