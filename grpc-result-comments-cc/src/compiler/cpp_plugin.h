Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2019 gRPC authors.
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

#ifndef GRPC_INTERNAL_COMPILER_CPP_PLUGIN_H
#define GRPC_INTERNAL_COMPILER_CPP_PLUGIN_H

#include <memory>
#include <sstream>

#include "src/compiler/config.h"
#include "src/compiler/cpp_generator.h"
#include "src/compiler/generator_helpers.h"
#include "src/compiler/protobuf_plugin.h"

// Main generator class for C++ gRPC code generation
class CppGrpcGenerator : public grpc::protobuf::compiler::CodeGenerator {
 public:
  CppGrpcGenerator() {}
  virtual ~CppGrpcGenerator() {}

  // Returns the supported features of this generator
  uint64_t GetSupportedFeatures() const override {
    return FEATURE_PROTO3_OPTIONAL
#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
           | FEATURE_SUPPORTS_EDITIONS
#endif
        ;
  }

#ifdef GRPC_PROTOBUF_EDITION_SUPPORT
  // Returns the minimum supported protobuf edition
  grpc::protobuf::Edition GetMinimumEdition() const override {
    return grpc::protobuf::Edition::EDITION_PROTO2;
  }
  
  // Returns the maximum supported protobuf edition
  grpc::protobuf::Edition GetMaximumEdition() const override {
    return grpc::protobuf::Edition::EDITION_2023;
  }
#endif

  // Main generation function that produces gRPC C++ code
  virtual bool Generate(const grpc::protobuf::FileDescriptor* file,
                        const std::string& parameter,
                        grpc::protobuf::compiler::GeneratorContext* context,
                        std::string* error) const override {
    // Check if generic services are enabled (not supported)
    if (file->options().cc_generic_services()) {
      *error =
          "cpp grpc proto compiler plugin does not work with generic "
          "services. To generate cpp grpc APIs, please set \""
          "cc_generic_service = false\".";
      return false;
    }

    // Initialize generator parameters with default values
    grpc_cpp_generator::Parameters generator_parameters;
    generator_parameters.use_system_headers = true;
    generator_parameters.generate_mock_code = false;
    generator_parameters.include_import_headers = false;
    generator_parameters.allow_sync_server_api = true;
    generator_parameters.allow_cq_api = true;
    generator_parameters.allow_deprecated = false;

    ProtoBufFile pbfile(file);

    // Process any provided parameters
    if (!parameter.empty()) {
      std::vector<std::string> parameters_list =
          grpc_generator::tokenize(parameter, ",");
      for (auto parameter_string = parameters_list.begin();
           parameter_string != parameters_list.end(); parameter_string++) {
        std::vector<std::string> param =
            grpc_generator::tokenize(*parameter_string, "=");
            
        // Handle different parameter types
        if (param[0] == "services_namespace") {
          generator_parameters.services_namespace = param[1];
        } else if (param[0] == "use_system_headers") {
          if (param[1] == "true") {
            generator_parameters.use_system_headers = true;
          } else if (param[1] == "false") {
            generator_parameters.use_system_headers = false;
          } else {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else if (param[0] == "grpc_search_path") {
          generator_parameters.grpc_search_path = param[1];
        } else if (param[0] == "generate_mock_code") {
          if (param[1] == "true") {
            generator_parameters.generate_mock_code = true;
          } else if (param[1] != "false") {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else if (param[0] == "allow_sync_server_api") {
          if (param[1] == "true") {
            generator_parameters.allow_sync_server_api = true;
          } else if (param[1] == "false") {
            generator_parameters.allow_sync_server_api = false;
          } else {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else if (param[0] == "allow_cq_api") {
          if (param[1] == "true") {
            generator_parameters.allow_cq_api = true;
          } else if (param[1] == "false") {
            generator_parameters.allow_cq_api = false;
          } else {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else if (param[0] == "gmock_search_path") {
          generator_parameters.gmock_search_path = param[1];
        } else if (param[0] == "additional_header_includes") {
          generator_parameters.additional_header_includes =
              grpc_generator::tokenize(param[1], ":");
        } else if (param[0] == "message_header_extension") {
          generator_parameters.message_header_extension = param[1];
        } else if (param[0] == "include_import_headers") {
          if (param[1] == "true") {
            generator_parameters.include_import_headers = true;
          } else if (param[1] != "false") {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else if (param[0] == "allow_deprecated") {
          if (param[1] == "true") {
            generator_parameters.allow_deprecated = true;
          } else if (param[1] == "false") {
            generator_parameters.allow_deprecated = false;
          } else {
            *error = std::string("Invalid parameter: ") + *parameter_string;
            return false;
          }
        } else {
          *error = std::string("Unknown parameter: ") + *parameter_string;
          return false;
        }
      }
    }

    // Generate the base file name by stripping the .proto extension
    std::string file_name =
        grpc_generator::StripProto(std::string(file->name()));

    // Generate and write header file
    std::string header_code =
        grpc_cpp_generator::GetHeaderPrologue(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetHeaderIncludes(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetHeaderServices(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetHeaderEpilogue(&pbfile, generator_parameters);
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> header_output(
        context->Open(file_name + ".grpc.pb.h"));
    grpc::protobuf::io::CodedOutputStream header_coded_out(header_output.get());
    header_coded_out.WriteRaw(header_code.data(), header_code.size());

    // Generate and write source file
    std::string source_code =
        grpc_cpp_generator::GetSourcePrologue(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetSourceIncludes(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetSourceServices(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetSourceEpilogue(&pbfile, generator_parameters);
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> source_output(
        context->Open(file_name + ".grpc.pb.cc"));
    grpc::protobuf::io::CodedOutputStream source_coded_out(source_output.get());
    source_coded_out.WriteRaw(source_code.data(), source_code.size());

    // Generate mock code if requested
    if (!generator_parameters.generate_mock_code) {
      return true;
    }
    std::string mock_code =
        grpc_cpp_generator::GetMockPrologue(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetMockIncludes(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetMockServices(&pbfile, generator_parameters) +
        grpc_cpp_generator::GetMockEpilogue(&pbfile, generator_parameters);
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> mock_output(
        context->Open(file_name + "_mock.grpc.pb.h"));
    grpc::protobuf::io::CodedOutputStream mock_coded_out(mock_output.get());
    mock_coded_out.WriteRaw(mock_code.data(), mock_code.size());

    return true;
  }

 private:
  // Helper function to insert code at a specific point in an existing file
  void Insert(grpc::protobuf::compiler::GeneratorContext* context,
              const std::string& filename, const std::string& insertion_point,
              const std::string& code) const {
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> output(
        context->OpenForInsert(filename, insertion_point));
    grpc::protobuf::io::CodedOutputStream coded_out(output.get());
    coded_out.WriteRaw(code.data(), code.size());
  }
};

#endif
```

The comments added explain:
1. The overall purpose of the class (C++ gRPC code generator)
2. Key methods and their functionality
3. The parameter processing logic
4. The code generation process for different file types (header, source, mock)
5. Important implementation details
6. The helper method's purpose

The comments are designed to help future developers understand:
- What the code does at a high level
- How the different components work together
- The purpose of complex logic sections
- Important implementation decisions