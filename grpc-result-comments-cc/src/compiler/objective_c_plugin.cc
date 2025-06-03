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

#include <google/protobuf/compiler/objectivec/names.h>

#include <memory>

#include "src/compiler/config.h"
#include "src/compiler/objective_c_generator.h"
#include "src/compiler/objective_c_generator_helpers.h"

// Using declarations for protobuf and gRPC Objective-C generator utilities
using ::google::protobuf::compiler::objectivec::
    IsProtobufLibraryBundledProtoFile;
using ::google::protobuf::compiler::objectivec::ProtobufLibraryFrameworkName;
#ifdef SUPPORT_OBJC_PREFIX_VALIDATION
using ::google::protobuf::compiler::objectivec::ValidateObjCClassPrefixes;
#endif
using ::grpc_objective_c_generator::FrameworkImport;
using ::grpc_objective_c_generator::LocalImport;
using ::grpc_objective_c_generator::PreprocIfElse;
using ::grpc_objective_c_generator::PreprocIfNot;
using ::grpc_objective_c_generator::SystemImport;

namespace {

/**
 * Generates the appropriate import statement for proto headers based on:
 * - Whether the proto is bundled with protobuf library
 * - Framework settings
 * - Runtime import prefix
 * 
 * @param dep The file descriptor for the dependency
 * @param indent String to prepend for indentation
 * @param framework The framework name if using framework imports
 * @param pb_runtime_import_prefix Prefix for runtime imports
 * @return The generated import statement as a string
 */
inline ::std::string ImportProtoHeaders(
    const grpc::protobuf::FileDescriptor* dep, const char* indent,
    const ::std::string& framework,
    const ::std::string& pb_runtime_import_prefix) {
  ::std::string header = grpc_objective_c_generator::MessageHeaderName(dep);

  // Handle non-bundled proto files
  if (!IsProtobufLibraryBundledProtoFile(dep)) {
    if (framework.empty()) {
      return indent + LocalImport(header);  // Local import if no framework
    } else {
      return indent + FrameworkImport(header, framework);  // Framework import
    }
  }

  // Handle bundled protobuf library files
  ::std::string base_name = header;
  grpc_generator::StripPrefix(&base_name, "google/protobuf/");
  ::std::string file_name = "GPB" + base_name;

  ::std::string framework_header =
      ::std::string(ProtobufLibraryFrameworkName) + "/" + file_name;
  ::std::string local_header = file_name;
  if (!pb_runtime_import_prefix.empty()) {
    local_header = pb_runtime_import_prefix + "/" + file_name;
  }

  // Choose between framework or local imports based on preprocessor condition
  static const ::std::string kFrameworkImportsCondition =
      "GPB_USE_PROTOBUF_FRAMEWORK_IMPORTS";
  return PreprocIfElse(kFrameworkImportsCondition,
                       indent + SystemImport(framework_header),
                       indent + LocalImport(local_header));
}

}  // namespace

/**
 * Objective-C gRPC code generator implementation.
 * Generates client-side Objective-C interfaces for gRPC services.
 */
class ObjectiveCGrpcGenerator : public grpc::protobuf::compiler::CodeGenerator {
 public:
  ObjectiveCGrpcGenerator() {}
  virtual ~ObjectiveCGrpcGenerator() {}

 public:
  /**
   * Returns the supported features of this generator.
   * @return Bitmask of supported features
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
   * @return Minimum supported protobuf edition
   */
  grpc::protobuf::Edition GetMinimumEdition() const override {
    return grpc::protobuf::Edition::EDITION_PROTO2;
  }
  
  /**
   * @return Maximum supported protobuf edition
   */
  grpc::protobuf::Edition GetMaximumEdition() const override {
    return grpc::protobuf::Edition::EDITION_2023;
  }
#endif

  /**
   * Main generation method that produces Objective-C gRPC client code.
   * 
   * @param file The proto file descriptor to generate code for
   * @param parameter Generator parameters
   * @param context Generator context for file operations
   * @param error Error output string
   * @return true if generation succeeded, false otherwise
   */
  virtual bool Generate(const grpc::protobuf::FileDescriptor* file,
                        const ::std::string& parameter,
                        grpc::protobuf::compiler::GeneratorContext* context,
                        ::std::string* error) const override {
    // Skip files with no services
    if (file->service_count() == 0) {
      return true;
    }

#ifdef SUPPORT_OBJC_PREFIX_VALIDATION
    // Validate Objective-C class prefixes if supported
    if (!ValidateObjCClassPrefixes({file}, {}, error)) {
      return false;
    }
#endif

    // Parse generator parameters
    bool grpc_local_import = false;
    ::std::string framework;
    ::std::string pb_runtime_import_prefix;
    ::std::string grpc_local_import_prefix;
    std::vector<::std::string> params_list =
        grpc_generator::tokenize(parameter, ",");
    for (auto param_str = params_list.begin(); param_str != params_list.end();
         ++param_str) {
      std::vector<::std::string> param =
          grpc_generator::tokenize(*param_str, "=");
      if (param[0] == "generate_for_named_framework") {
        // Handle framework generation parameter
        if (param.size() != 2) {
          *error =
              std::string("Format: generate_for_named_framework=<Framework>");
          return false;
        } else if (param[1].empty()) {
          *error =
              std::string("Name of framework cannot be empty for parameter: ") +
              param[0];
          return false;
        }
        framework = param[1];
      } else if (param[0] == "runtime_import_prefix") {
        // Handle runtime import prefix parameter
        if (param.size() != 2) {
          *error = grpc::string("Format: runtime_import_prefix=dir/");
          return false;
        }
        pb_runtime_import_prefix = param[1];
        grpc_generator::StripSuffix(&pb_runtime_import_prefix, "/");
      } else if (param[0] == "grpc_local_import_prefix") {
        // Handle local import prefix parameter
        grpc_local_import = true;
        if (param.size() != 2) {
          *error = grpc::string("Format: grpc_local_import_prefix=dir/");
          return false;
        }
        grpc_local_import_prefix = param[1];
      }
    }

    // Constants for generated code
    static const ::std::string kNonNullBegin = "NS_ASSUME_NONNULL_BEGIN\n";
    static const ::std::string kNonNullEnd = "NS_ASSUME_NONNULL_END\n";
    static const ::std::string kProtocolOnly = "GPB_GRPC_PROTOCOL_ONLY";
    static const ::std::string kForwardDeclare =
        "GPB_GRPC_FORWARD_DECLARE_MESSAGE_PROTO";

    // Generate file paths
    ::std::string file_name =
        google::protobuf::compiler::objectivec::FilePath(file);

    // Initialize generator parameters
    grpc_objective_c_generator::Parameters generator_params;
    generator_params.no_v1_compatibility = false;

    // Parse additional parameters
    if (!parameter.empty()) {
      std::vector<std::string> parameters_list =
          grpc_generator::tokenize(parameter, ",");
      for (auto parameter_string = parameters_list.begin();
           parameter_string != parameters_list.end(); parameter_string++) {
        std::vector<std::string> param =
            grpc_generator::tokenize(*parameter_string, "=");
        if (param[0] == "no_v1_compatibility") {
          generator_params.no_v1_compatibility = true;
        }
      }
    }

    // Generate file header comment
    ::std::string file_header =
        "// Code generated by gRPC proto compiler.  DO NOT EDIT!\n"
        "// source: " +
        ::std::string(file->name()) + "\n\n";

    // Generate header file (.pbrpc.h)
    {
      // Generate imports section
      ::std::string imports;
      if (framework.empty()) {
        imports = LocalImport(file_name + ".pbobjc.h");
      } else {
        imports = FrameworkImport(file_name + ".pbobjc.h", framework);
      }

      // Generate system imports based on parameters
      ::std::string system_imports;
      if (grpc_local_import) {
        system_imports =
            LocalImport(grpc_local_import_prefix + "ProtoRPC/ProtoService.h");
        if (generator_params.no_v1_compatibility) {
          system_imports +=
              LocalImport(grpc_local_import_prefix + "ProtoRPC/ProtoRPC.h");
        } else {
          system_imports += LocalImport(grpc_local_import_prefix +
                                        "ProtoRPC/ProtoRPCLegacy.h");
          system_imports += LocalImport(grpc_local_import_prefix +
                                        "RxLibrary/GRXWriteable.h");
          system_imports +=
              LocalImport(grpc_local_import_prefix + "RxLibrary/GRXWriter.h");
        }
      } else {
        system_imports = SystemImport("ProtoRPC/ProtoService.h");
        if (generator_params.no_v1_compatibility) {
          system_imports += SystemImport("ProtoRPC/ProtoRPC.h");
        } else {
          system_imports += SystemImport("ProtoRPC/ProtoRPCLegacy.h");
          system_imports += SystemImport("RxLibrary/GRXWriteable.h");
          system_imports += SystemImport("RxLibrary/GRXWriter.h");
        }
      }

      // Generate forward declarations
      ::std::string forward_declarations =
          "@class GRPCUnaryProtoCall;\n"
          "@class GRPCStreamingProtoCall;\n"
          "@class GRPCCallOptions;\n"
          "@protocol GRPCProtoResponseHandler;\n";
      if (!generator_params.no_v1_compatibility) {
        forward_declarations += "@class GRPCProtoCall;\n";
      }
      forward_declarations += "\n";

      // Generate class declarations and imports
      ::std::string class_declarations =
          grpc_objective_c_generator::GetAllMessageClasses(file);

      ::std::string class_imports;
      for (int i = 0; i < file->dependency_count(); i++) {
        class_imports += ImportProtoHeaders(
            file->dependency(i), "  ", framework, pb_runtime_import_prefix);
      }

      // Generate protocols for services
      ::std::string ng_protocols;
      for (int i = 0; i < file->service_count(); i++) {
        const grpc::protobuf::ServiceDescriptor* service = file->service(i);
        ng_protocols += grpc_objective_c_generator::GetV2Protocol(service);
      }

      ::std::string protocols;
      for (int i = 0; i < file->service_count(); i++) {
        const grpc::protobuf::ServiceDescriptor* service = file->service(i);
        protocols +=
            grpc_objective_c_generator::GetProtocol(service, generator_params);
      }

      // Generate service interfaces
      ::std::string interfaces;
      for (int i = 0; i < file->service_count(); i++) {
        const grpc::protobuf::ServiceDescriptor* service = file->service(i);
        interfaces +=
            grpc_objective_c_generator::GetInterface(service, generator_params);
      }

      // Write the complete header file
      Write(context, file_name + ".pbrpc.h",
            file_header + SystemImport("Foundation/Foundation.h") + "\n" +
                PreprocIfNot(kForwardDeclare, imports) + "\n" +
                PreprocIfNot(kProtocolOnly, system_imports) + "\n" +
                class_declarations + "\n" +
                PreprocIfNot(kForwardDeclare, class_imports) + "\n" +
                forward_declarations + "\n" + kNonNullBegin + "\n" +
                ng_protocols + protocols + "\n" +
                PreprocIfNot(kProtocolOnly, interfaces) + "\n" + kNonNullEnd +
                "\n");
    }

    // Generate implementation file (.pbrpc.m)
    {
      // Generate imports for implementation file
      ::std::string imports;
      if (framework.empty()) {
        imports = LocalImport(file_name + ".pbrpc.h") +
                  LocalImport(file_name + ".pbobjc.h");
      } else {
        imports = FrameworkImport(file_name + ".pbrpc.h", framework) +
                  FrameworkImport(file_name + ".pbobjc.h", framework);
      }

      // Add additional imports based on parameters
      if (grpc_local_import) {
        if (generator_params.no_v1_compatibility) {
          imports +=
              LocalImport(grpc_local_import_prefix + "ProtoRPC/ProtoRPC.h");
        } else {
          imports += LocalImport(grpc_local_import_prefix +
                                 "ProtoRPC/ProtoRPCLegacy.h");
          imports += LocalImport(grpc_local_import_prefix +
                                 "RxLibrary/GRXWriter+Immediate.h");
        }
      } else {
        if (generator_params.no_v1_compatibility) {
          imports += SystemImport("ProtoRPC/ProtoRPC.h");
        } else {
          imports += SystemImport("ProtoRPC/ProtoRPCLegacy.h");
          imports += SystemImport("RxLibrary/GRXWriter+Immediate.h");
        }
      }

      // Generate dependency imports
      ::std::string class_imports;
      for (int i = 0; i < file->dependency_count(); i++) {
        class_imports += ImportProtoHeaders(file->dependency(i), "", framework,
                                            pb_runtime_import_prefix);
      }

      // Generate service implementations
      ::std::string definitions;
      for (int i = 0; i < file->service_count(); i++) {
        const grpc::protobuf::ServiceDescriptor* service = file->service(i);
        definitions +=
            grpc_objective_c_generator::GetSource(service, generator_params);
      }

      // Write the complete implementation file
      Write(context, file_name + ".pbrpc.m",
            file_header +
                PreprocIfNot(kProtocolOnly, imports + "\n" + class_imports +
                                                "\n" + definitions));
    }

    return true;
  }

 private:
  /**
   * Helper method to write generated code to a file.
   * 
   * @param context Generator context for file operations
   * @param filename Name of the file to write
   * @param code The code content to write
   */
  void Write(grpc::protobuf::compiler::GeneratorContext* context,
             const ::std::string& filename, const ::std::string& code) const {
    std::unique_ptr<grpc::protobuf::io::ZeroCopyOutputStream> output(
        context->Open(filename));
    grpc::protobuf::io::CodedOutputStream coded_out(output.get());
    coded_out.WriteRaw(code.data(), code.size());
  }
};

/**
 * Main entry point for the protoc plugin.
 * Creates and runs the Objective-C gRPC generator.
 */
int main(int argc, char* argv[]) {
  ObjectiveCGrpcGenerator generator;
  return grpc::protobuf::compiler::PluginMain(argc, argv, &generator);
}
```

The comments added explain:
1. The overall purpose of each major component
2. The functionality of important methods
3. The logic flow in complex sections
4. The purpose of key variables and constants
5. The generation process for both header and implementation files
6. The parameter handling logic
7. The file writing mechanism

The comments are designed to help future maintainers understand:
- What the code does
- Why certain decisions were made
- How the different components interact
- Where to look for specific functionality
- The overall architecture of the generator