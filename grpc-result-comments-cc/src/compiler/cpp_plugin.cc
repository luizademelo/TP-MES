Here's the commented version of the code snippet:

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

// Include the header file for the C++ plugin generator
#include "src/compiler/cpp_plugin.h"

/**
 * @brief Main entry point for the gRPC C++ protobuf compiler plugin
 * 
 * This function creates a C++ generator instance and passes it to the protobuf
 * compiler's PluginMain function to generate gRPC service code from .proto files.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return int Returns the exit status from the protobuf compiler plugin
 */
int main(int argc, char* argv[]) {
  // Create an instance of the C++ gRPC code generator
  CppGrpcGenerator generator;
  
  // Invoke the protobuf compiler's plugin main function with our generator
  // This will handle the code generation process for gRPC services
  return grpc::protobuf::compiler::PluginMain(argc, argv, &generator);
}
```

The comments added explain:
1. The purpose of the included header file
2. The overall function of the main program
3. The role of each parameter in the main function
4. What the CppGrpcGenerator instance represents
5. What the PluginMain function does and how it uses the generator

The comments are designed to help future developers understand:
- The plugin's entry point
- How the code generation process is initiated
- The relationship between this code and the protobuf compiler infrastructure
- The flow of control in the program