Here's the commented version of the code:

```c++
/*
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
 */

#include <memory>

#include "src/compiler/config.h"
#include "src/compiler/php_generator.h"
#include "src/compiler/php_generator_helpers.h"

using google::protobuf::compiler::ParseGeneratorParameter;
using grpc_php_generator::GenerateFile;
using grpc_php_generator::GetPHPServiceFilename;

/**
 * PHPGrpcGenerator is a CodeGenerator implementation that generates PHP client
 * and server code for gRPC services defined in .proto files.
 */
class PHPGrpcGenerator : public grpc::protobuf::compiler::CodeGenerator {
 public:
  PHPGrpcGenerator() {}
  ~PHPGrpcGenerator() {}

  /**
   * Returns the supported features of this generator.
   * Currently supports PROTO3_OPTIONAL and optionally EDITION features.
   */
  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
           | FEATURE_SUPPORTS_EDITIONS
#endif
        ;
  }

#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
  /**
   * Returns the minimum supported protobuf edition (PROTO2).
   */
  grpc::protobuf::Edition GetMinimumEdition() const override {
    return grpc::protobuf::Edition::EDITION_PROTO2;
  }

  /**
   * Returns the maximum supported protobuf edition (2023).
   */
  grpc::protobuf::Edition GetMaximumEdition() const override {
    return grpc::protobuf::Edition::EDITION_2023;
  }
#endif

  /**
   * Generates PHP code for gRPC services defined in the given file descriptor.
   * 
   * @param file The FileDescriptor containing the service definitions
   * @param parameter Generator parameters (e.g., "class_suffix=Foo,generate_server")
   * @param context Generator context for file operations
   * @param error Output parameter for error messages
   * @return true on success, false on failure
   */
  bool Generate(const grpc::protobuf::FileDescriptor* file,
                const std::string& parameter,
                grpc::protobuf::compiler::GeneratorContext* context,
                std::string* error) const override {
    // Skip files with no services
    if (file->service_count() == 0) {
      return true;
    }

    // Parse generator parameters
    std::vector<std::pair<std::string, std::string> > options;
    ParseGeneratorParameter(parameter, &options);

    bool generate_server = false;
    std::string class_suffix;
    
    // Process generator options
    for (size_t i = 0; i < options.size(); ++i) {
      if (options[i].first == "class_suffix") {
        class_suffix = options[i].second;
      } else if (options[i].first == "generate_server") {
        generate_server = true;
      } else {
        *error = "unsupported options: " + options[i].first;
        return false;
      }
    }

    // Generate code for each service in the file
    for (int i = 0; i < file->service_count(); i++) {
      // Generate client code
      GenerateService(file, file->service(i), class_suffix, false, context);
      
      // Generate server code if requested
      if (generate_server) {
        GenerateService(file, file->service(i), class_suffix, true, context);
      }
    }

    return true;
  }

 private:
  /**
   * Generates the PHP service code and writes it to a file.
   * 
   * @param file FileDescriptor containing the service
   * @param service ServiceDescriptor to generate code for
   * @param class_suffix Optional suffix for generated class names
   * @param is_server Whether to generate server (true) or client (false) code
   * @param context Generator context for file operations
   */
  void GenerateService(
      const grpc::protobuf::FileDescriptor* file,
      const grpc::protobuf::ServiceDescriptor* service,
      const std::string& class_suffix, bool is_server,
      grpc::protobuf::compiler::GeneratorContext* context) const {
    // Generate the PHP code
    std::string code = GenerateFile(file, service, class_suffix, is_server);

    // Determine the output filename
    std::string file_name =
        GetPHPServiceFilename(file, service, class_suffix, is_server);

    // Write the generated code to file
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> output(
        context->Open(file_name));
    grpc::protobuf::io::CodedOutputStream coded_out(output.get());
    coded_out.WriteRaw(code.data(), code.size());
  }
};

/**
 * Main entry point for the PHP gRPC protobuf plugin.
 * Creates a PHPGrpcGenerator instance and runs the plugin main function.
 */
int main(int argc, char* argv[]) {
  PHPGrpcGenerator generator;
  return grpc::protobuf::compiler::PluginMain(argc, argv, &generator);
}
```

Key improvements in the comments:
1. Added class-level documentation explaining the purpose of PHPGrpcGenerator
2. Documented all public methods including parameters and return values
3. Added detailed comments explaining the logic flow in the Generate method
4. Documented the private GenerateService helper method
5. Added explanation for the main() function's purpose
6. Maintained all existing copyright and license information
7. Added comments explaining the feature flags and edition support

The comments follow a consistent style and provide clear explanations of both what the code does and why it does it, which will help future maintainers understand and modify the code.