Here's the commented version of the code:

```c++
/*
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
 */

#include <memory>

#include "src/compiler/config.h"
#include "src/compiler/csharp_generator.h"
#include "src/compiler/csharp_generator_helpers.h"

// CSharpGrpcGenerator is a CodeGenerator implementation that generates C# gRPC service
// code from Protocol Buffer definitions.
class CSharpGrpcGenerator : public grpc::protobuf::compiler::CodeGenerator {
 public:
  CSharpGrpcGenerator() {}
  ~CSharpGrpcGenerator() {}

  // Returns the supported features of this generator, including PROTO3_OPTIONAL
  // and optionally edition support if GRPC_PROTOBUF_EDITION_SUPPORT is defined.
  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
           | FEATURE_SUPPORTS_EDITIONS
#endif
        ;
  }

#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
  // Returns the minimum Protocol Buffer edition supported by this generator
  grpc::protobuf::Edition GetMinimumEdition() const override {
    return grpc::protobuf::Edition::EDITION_PROTO2;
  }
  
  // Returns the maximum Protocol Buffer edition supported by this generator
  grpc::protobuf::Edition GetMaximumEdition() const override {
    return grpc::protobuf::Edition::EDITION_2023;
  }
#endif

  // Main generation method that creates C# gRPC service code for the given proto file
  bool Generate(const grpc::protobuf::FileDescriptor* file,
                const std::string& parameter,
                grpc::protobuf::compiler::GeneratorContext* context,
                std::string* error) const override {
    // Parse generator parameters/options
    std::vector<std::pair<std::string, std::string> > options;
    grpc::protobuf::compiler::ParseGeneratorParameter(parameter, &options);

    // Default generation options
    bool generate_client = true;      // Generate client code by default
    bool generate_server = true;      // Generate server code by default
    bool internal_access = false;     // Default access level
    std::string base_namespace = "";  // Default base namespace
    bool base_namespace_present = false;
    std::string file_suffix = "Grpc.cs";  // Default output file suffix

    // Process each generator option
    for (size_t i = 0; i < options.size(); i++) {
      if (options[i].first == "no_client") {
        generate_client = false;
      } else if (options[i].first == "no_server") {
        generate_server = false;
      } else if (options[i].first == "internal_access") {
        internal_access = true;
      } else if (options[i].first == "file_suffix") {
        file_suffix = options[i].second;
      } else if (options[i].first == "base_namespace") {
        base_namespace = options[i].second;
        base_namespace_present = true;
      } else {
        *error = "Unknown generator option: " + options[i].first;
        return false;
      }
    }

    // Generate the C# service code
    std::string code = grpc_csharp_generator::GetServices(
        file, generate_client, generate_server, internal_access);
    
    // Return successfully if there are no services to generate
    if (code.size() == 0) {
      return true;
    }

    // Determine the output file name based on options
    std::string file_name;
    if (!grpc_csharp_generator::ServicesFilename(
            file, file_suffix, base_namespace_present, base_namespace,
            file_name, error)) {
      return false;
    }

    // Write the generated code to the output file
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> output(
        context->Open(file_name));
    grpc::protobuf::io::CodedOutputStream coded_out(output.get());
    coded_out.WriteRaw(code.data(), code.size());
    return true;
  }
};

// Main entry point for the protoc plugin
int main(int argc, char* argv[]) {
  CSharpGrpcGenerator generator;
  return grpc::protobuf::compiler::PluginMain(argc, argv, &generator);
}
```

Key aspects covered in the comments:
1. Class overview explaining the purpose of CSharpGrpcGenerator
2. Feature support details including conditional compilation
3. Generation options and their defaults
4. Parameter processing logic
5. File naming and output generation
6. Main function's role as a protoc plugin entry point

The comments aim to provide both high-level understanding of the component's purpose and detailed explanations of the implementation choices and logic flow.