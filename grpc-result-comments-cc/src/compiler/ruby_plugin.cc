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

#include <memory>

#include "src/compiler/config.h"
#include "src/compiler/ruby_generator.h"
#include "src/compiler/ruby_generator_helpers-inl.h"

// RubyGrpcGenerator is a CodeGenerator implementation that generates Ruby code
// for gRPC services defined in .proto files.
class RubyGrpcGenerator : public grpc::protobuf::compiler::CodeGenerator {
 public:
  RubyGrpcGenerator() {}
  ~RubyGrpcGenerator() {}

  // Returns the set of supported features for this generator.
  // Currently supports PROTO3_OPTIONAL and optionally editions support.
  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
           | FEATURE_SUPPORTS_EDITIONS
#endif
        ;
  }

#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
  // Returns the minimum protobuf edition supported by this generator
  grpc::protobuf::Edition GetMinimumEdition() const override {
    return grpc::protobuf::Edition::EDITION_PROTO2;
  }
  
  // Returns the maximum protobuf edition supported by this generator
  grpc::protobuf::Edition GetMaximumEdition() const override {
    return grpc::protobuf::Edition::EDITION_2023;
  }
#endif

  // Generates Ruby code for the services defined in the given .proto file.
  // Parameters:
  //   file: The FileDescriptor of the .proto file being processed
  //   parameter: Unused parameter (kept for interface compatibility)
  //   context: GeneratorContext for file operations
  //   error: Unused error string (kept for interface compatibility)
  // Returns:
  //   true on success, false on failure
  bool Generate(const grpc::protobuf::FileDescriptor* file,
                const std::string& ,
                grpc::protobuf::compiler::GeneratorContext* context,
                std::string* ) const override {
    // Generate Ruby service code from the proto file
    std::string code = grpc_ruby_generator::GetServices(file);
    
    // Return successfully if there are no services to generate
    if (code.size() == 0) {
      return true;
    }

    // Determine the output filename based on the proto file
    std::string file_name;
    if (!grpc_ruby_generator::ServicesFilename(file, &file_name)) {
      return false;
    }
    
    // Create output stream and write the generated code
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> output(
        context->Open(file_name));
    grpc::protobuf::io::CodedOutputStream coded_out(output.get());
    coded_out.WriteRaw(code.data(), code.size());
    return true;
  }
};

// Main entry point for the protoc plugin
// Parameters:
//   argc: Argument count
//   argv: Argument vector
// Returns:
//   Exit status (0 for success)
int main(int argc, char* argv[]) {
  RubyGrpcGenerator generator;
  // Run the generator as a protoc plugin
  return grpc::protobuf::compiler::PluginMain(argc, argv, &generator);
}
```

Key improvements in the comments:
1. Added class-level documentation explaining the purpose of RubyGrpcGenerator
2. Documented each method's purpose, parameters, and return values
3. Added comments explaining conditional compilation blocks
4. Clarified the main function's role as a protoc plugin entry point
5. Added comments for important code blocks and logic flow
6. Explained the significance of empty checks and file operations

The comments are concise yet informative, helping future maintainers understand both the high-level purpose and implementation details of the code.