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

#include "src/compiler/python_generator.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>

#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"
#include "src/compiler/protobuf_plugin.h"
#include "src/compiler/python_generator_helpers.h"
#include "src/compiler/python_private_generator.h"

using grpc::protobuf::FileDescriptor;
using grpc::protobuf::compiler::GeneratorContext;
using grpc::protobuf::io::CodedOutputStream;
using grpc::protobuf::io::ZeroCopyOutputStream;
using std::map;
using std::pair;
using std::replace;
using std::set;
using std::tuple;
using std::vector;

namespace grpc_python_generator {

// Global variable storing the name of the proto file being processed
std::string generator_file_name;

namespace {

// Type aliases for better readability
typedef map<std::string, std::string> StringMap;
typedef vector<std::string> StringVector;
typedef tuple<std::string, std::string> StringPair;
typedef set<StringPair> StringPairSet;

// RAII class for managing indentation in generated Python code
class IndentScope {
 public:
  explicit IndentScope(grpc_generator::Printer* printer) : printer_(printer) {
    // Increase indentation by two levels when entering scope
    printer_->Indent();
    printer_->Indent();
  }

  ~IndentScope() {
    // Decrease indentation by two levels when leaving scope
    printer_->Outdent();
    printer_->Outdent();
  }

 private:
  grpc_generator::Printer* printer_;  // Printer object for code generation
};

// Private generator class that handles the actual code generation
PrivateGenerator::PrivateGenerator(const GeneratorConfiguration& config,
                                   const grpc_generator::File* file)
    : config(config), file(file) {}

// Prints all comments for a proto element, with a default message if none exist
void PrivateGenerator::PrintAllComments(StringVector comments,
                                        grpc_generator::Printer* out) {
  if (comments.empty()) {
    // Print default comment if no comments are provided
    out->Print(
        "\"\"\"Missing associated documentation comment in .proto "
        "file.\"\"\"\n");
    return;
  }
  out->Print("\"\"\"");
  for (StringVector::iterator it = comments.begin(); it != comments.end();
       ++it) {
    // Trim leading spaces from each comment line
    size_t start_pos = it->find_first_not_of(' ');
    if (start_pos != std::string::npos) {
      out->PrintRaw(it->c_str() + start_pos);
    }
    out->Print("\n");
  }
  out->Print("\"\"\"\n");
}

// Generates the Beta API servicer class for a service
bool PrivateGenerator::PrintBetaServicer(const grpc_generator::Service* service,
                                         grpc_generator::Printer* out) {
  StringMap service_dict;
  service_dict["Service"] = service->name();
  out->Print("\n\n");
  out->Print(service_dict, "class Beta$Service$Servicer(object):\n");
  {
    IndentScope raii_class_indent(out);
    // Deprecation warning for Beta API
    out->Print(
        "\"\"\"The Beta API is deprecated for 0.15.0 and later.\n"
        "\nIt is recommended to use the GA API (classes and functions in this\n"
        "file not marked beta) for all further purposes. This class was "
        "generated\n"
        "only to ease transition from grpcio<0.15.0 to "
        "grpcio>=0.15.0.\"\"\"\n");
    // Print service comments
    StringVector service_comments = service->GetAllComments();
    PrintAllComments(service_comments, out);
    
    // Generate method stubs for each service method
    for (int i = 0; i < service->method_count(); ++i) {
      auto method = service->method(i);
      std::string arg_name =
          method->ClientStreaming() ? "request_iterator" : "request";
      StringMap method_dict;
      method_dict["Method"] = method->name();
      method_dict["ArgName"] = arg_name;
      out->Print(method_dict, "def $Method$(self, $ArgName$, context):\n");
      {
        IndentScope raii_method_indent(out);
        // Print method comments
        StringVector method_comments = method->GetAllComments();
        PrintAllComments(method_comments, out);
        // Default implementation returns UNIMPLEMENTED status
        out->Print("context.code(beta_interfaces.StatusCode.UNIMPLEMENTED)\n");
      }
    }
  }
  return true;
}

// Generates the Beta API stub class for a service
bool PrivateGenerator::PrintBetaStub(const grpc_generator::Service* service,
                                     grpc_generator::Printer* out) {
  StringMap service_dict;
  service_dict["Service"] = service->name();
  out->Print("\n\n");
  out->Print(service_dict, "class Beta$Service$Stub(object):\n");
  {
    IndentScope raii_class_indent(out);
    // Deprecation warning for Beta API
    out->Print(
        "\"\"\"The Beta API is deprecated for 0.15.0 and later.\n"
        "\nIt is recommended to use the GA API (classes and functions in this\n"
        "file not marked beta) for all further purposes. This class was "
        "generated\n"
        "only to ease transition from grpcio<0.15.0 to "
        "grpcio>=0.15.0.\"\"\"\n");
    // Print service comments
    StringVector service_comments = service->GetAllComments();
    PrintAllComments(service_comments, out);
    
    // Generate method stubs for each service method
    for (int i = 0; i < service->method_count(); ++i) {
      auto method = service->method(i);
      std::string arg_name =
          method->ClientStreaming() ? "request_iterator" : "request";
      StringMap method_dict;
      method_dict["Method"] = method->name();
      method_dict["ArgName"] = arg_name;
      out->Print(method_dict,
                 "def $Method$(self, $ArgName$, timeout, metadata=None, "
                 "with_call=False, protocol_options=None):\n");
      {
        IndentScope raii_method_indent(out);
        // Print method comments
        StringVector method_comments = method->GetAllComments();
        PrintAllComments(method_comments, out);
        // Default implementation raises NotImplementedError
        out->Print("raise NotImplementedError()\n");
      }
      // For non-server-streaming methods, add future attribute
      if (!method->ServerStreaming()) {
        out->Print(method_dict, "$Method$.future = None\n");
      }
    }
  }
  return true;
}

// Generates the Beta API server factory function for a service
bool PrivateGenerator::PrintBetaServerFactory(
    const std::string& package_qualified_service_name,
    const grpc_generator::Service* service, grpc_generator::Printer* out) {
  StringMap service_dict;
  service_dict["Service"] = service->name();
  out->Print("\n\n");
  out->Print(service_dict,
             "def beta_create_$Service$_server(servicer, pool=None, "
             "pool_size=None, default_timeout=None, maximum_timeout=None):\n");
  {
    IndentScope raii_create_server_indent(out);
    // Deprecation warning for Beta API
    out->Print(
        "\"\"\"The Beta API is deprecated for 0.15.0 and later.\n"
        "\nIt is recommended to use the GA API (classes and functions in this\n"
        "file not marked beta) for all further purposes. This function was\n"
        "generated only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0"
        "\"\"\"\n");
    
    // Prepare data structures for method implementations
    StringMap method_implementation_constructors;
    StringMap input_message_modules_and_classes;
    StringMap output_message_modules_and_classes;
    
    // Process each service method
    for (int i = 0; i < service->method_count(); ++i) {
      auto method = service->method(i);
      // Determine method implementation type based on streaming characteristics
      const std::string method_implementation_constructor =
          std::string(method->ClientStreaming() ? "stream_" : "unary_") +
          std::string(method->ServerStreaming() ? "stream_" : "unary_") +
          "inline";
      
      // Get input and output message types
      std::string input_message_module_and_class;
      if (!method->get_module_and_message_path_input(
              &input_message_module_and_class, generator_file_name,
              generate_in_pb2_grpc, config.import_prefix,
              config.prefixes_to_filter)) {
        return false;
      }
      std::string output_message_module_and_class;
      if (!method->get_module_and_message_path_output(
              &output_message_module_and_class, generator_file_name,
              generate_in_pb2_grpc, config.import_prefix,
              config.prefixes_to_filter)) {
        return false;
      }
      
      // Store method information
      method_implementation_constructors.insert(
          pair(method->name(), method_implementation_constructor));
      input_message_modules_and_classes.insert(
          pair(method->name(), input_message_module_and_class));
      output_message_modules_and_classes.insert(
          pair(method->name(), output_message_module_and_class));
    }
    
    // Generate request deserializers dictionary
    StringMap method_dict;
    method_dict["PackageQualifiedServiceName"] = package_qualified_service_name;
    out->Print("request_deserializers = {\n");
    for (StringMap::iterator name_and_input_module_class_pair =
             input_message_modules_and_classes.begin();
         name_and_input_module_class_pair !=
         input_message_modules_and_classes.end();
         name_and_input_module_class_pair++) {
      method_dict["MethodName"] = name_and_input_module_class_pair->first;
      method_dict["InputTypeModuleAndClass"] =
          name_and_input_module_class_pair->second;
      IndentScope raii_indent(out);
      out->Print(method_dict,
                 "(\'$PackageQualifiedServiceName$\', \'$MethodName$\'): "
                 "$InputTypeModuleAndClass$.FromString,\n");
    }
    out->Print("}\n");
    
    // Generate response serializers dictionary
    out->Print("response_serializers = {\n");
    for (StringMap::iterator name_and_output_module_class_pair =
             output_message_modules_and_classes.begin();
         name_and_output_module_class_pair !=
         output_message_modules_and_classes.end();
         name_and_output_module_class_pair++) {
      method_dict["MethodName"] = name_and_output_module_class_pair->first;
      method_dict["OutputTypeModuleAndClass"] =
          name_and_output_module_class_pair->second;
      IndentScope raii_indent(out);
      out->Print(method_dict,
                 "(\'$PackageQualifiedServiceName$\', \'$MethodName$\'): "
                 "$OutputTypeModuleAndClass$.SerializeToString,\n");
    }
    out->Print("}\n");
    
    // Generate method implementations dictionary
    out->Print("method_implementations = {\n");
    for (StringMap::iterator name_and_implementation_constructor =
             method_implementation_constructors.begin();
         name_and_implementation_constructor !=
         method_implementation_constructors.end();
         name_and_implementation_constructor++) {
      method_dict["Method"] = name_and_implementation_constructor->first;
      method_dict["Constructor"] = name_and_implementation_constructor->second;
      IndentScope raii_descriptions_indent(out);
      const std::string method_name =
          name_and_implementation_constructor->first;
      out->Print(method_dict,
                 "(\'$PackageQualifiedServiceName$\', \'$Method$\'): "
                 "face_utilities.$Constructor$(servicer.$Method$),\n");
    }
    out->Print("}\n");
    
    // Generate server options and return statement
    out->Print(
        "server_options = beta_implementations.server_options("
        "request_deserializers=request_deserializers, "
        "response_serializers=response_serializers, "
        "thread_pool=pool, thread_pool_size=pool_size, "
        "default_timeout=default_timeout, "
        "maximum_timeout=maximum_timeout)\n");
    out->Print(
        "return beta_implementations.server(method_implementations, "
        "options=server_options)\n");
  }
  return true;
}

// Generates the Beta API stub factory function for a service
bool PrivateGenerator::PrintBetaStubFactory(
    const std::string& package_qualified_service_name,
    const grpc_generator::Service* service, grpc_generator::Printer* out) {
  StringMap dict;
  dict["Service"] = service->name();
  out->Print("\n\n");
  out->Print(dict,
             "def beta_create_$Service$_stub(channel, host=None,"
             " metadata_transformer=None, pool=None, pool_size=None):\n");
  {
    IndentScope raii_create_server_indent(out);
    // Deprecation warning for Beta API
    out->Print(
        "\"\"\"The Beta API is deprecated for 0.15.0 and later.\n"
        "\nIt is recommended to use the GA API (classes and functions in this\n"
        "file not marked beta) for all further purposes. This function was\n"
        "generated only to ease transition from grpcio<0.15.0 to grpcio>=0.15.0"
        "\"\"\"\n");
    
    // Prepare data structures for method information
    StringMap method_cardinalities;
    StringMap input_message_modules_and_classes;
    StringMap output_message_modules_and_classes;
    
    // Process each service method
    for (int i = 0; i < service->method_count(); ++i) {
      auto method = service->method(i);
      // Determine method cardinality based on streaming characteristics
      const std::string method_cardinality =
          std::string(method->ClientStreaming() ? "STREAM" : "UNARY") + "_" +
          std::string(method->ServerStreaming() ? "STREAM" : "UNARY");
      
      // Get input and output message types
      std::string input_message_module_and_class;
      if (!method->get_module_and_message_path_input(
              &input_message_module_and_class, generator_file_name,
              generate_in_pb2_grpc, config.import_prefix,
              config.prefixes_to_filter)) {
        return false;
      }
      std::string output_message_module_and_class;
      if (!method->get_module_and_message_path_output(
              &output_message_module_and_class, generator_file_name,
              generate_in_pb2_grpc, config.import_prefix,
              config.prefixes_to_filter)) {
        return false;
      }
      
      // Store method information
      method_cardinalities.insert(pair(method->name(), method_cardinality));
      input_message_modules_and_classes.insert(
          pair(method->name(), input_message_module_and_class));
      output_message_modules_and_classes.insert(
          pair(method->name(), output_message_module_and_class));
    }
    
    // Generate request serializers dictionary
    StringMap method_dict;
    method_dict["PackageQualifiedServiceName"] = package_qualified_service_name;
    out->Print("request_serializers = {\n");
    for (StringMap::iterator name_and_input_module_class_pair =
             input_message_modules_and_classes.begin();
         name_and_input_module_class_pair !=
         input_message_modules_and_classes.end();
         name_and_input_module_class_pair++) {
      method_dict["MethodName"] = name_and_input_module_class_pair->first;
      method_dict["InputTypeModuleAndClass"] =
          name_and_input_module_class_pair->second;
      IndentScope raii_indent(out);
      out->Print(method_dict,
                 "(\'$PackageQualifiedServiceName$\', \'$MethodName$\'): "
                 "$InputTypeModuleAndClass$.SerializeToString,\n");
    }
    out->Print("}\n");
    
    // Generate response deserializers dictionary
    out->Print("response_deserializers = {\n");
    for (StringMap::iterator name_and_output_module_class_pair =
             output_message_modules_and_classes.begin();
         name_and_output_module_class_pair !=
         output_message_modules_and_classes.end();
         name_and_output_module_class_pair++) {
      method_dict["MethodName"] = name_and_output_module_class_pair->first;
      method_dict["OutputTypeModuleAndClass"] =
          name_and_output_module_class_pair->second;
      IndentScope raii_indent(out);
      out->Print(method_dict,
                 "(\'$PackageQualifiedServiceName$\', \'$MethodName$\'): "
                 "$OutputTypeModuleAndClass$.FromString,\n");
    }
    out->Print("}\n");
    
    // Generate cardinalities dictionary
    out->Print("cardinalities = {\n");
    for (StringMap::iterator name_and_cardinality =
             method_cardinalities.begin();
         name_and_cardinality != method_cardinalities.end();
         name_and_cardinality++) {
      method_dict["Method"] = name_and_cardinality->first;
      method_dict["Cardinality"] = name_and_cardinality->second;
      IndentScope raii_descriptions_indent(out