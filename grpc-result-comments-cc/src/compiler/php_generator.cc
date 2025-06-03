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

// Include necessary headers for Protobuf PHP compiler functionality
#include <google/protobuf/compiler/php/names.h>
#include <map>
#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"
#include "src/compiler/php_generator_helpers.h"

// Using declarations for Protobuf and gRPC types
using google::protobuf::compiler::php::GeneratedClassName;
using grpc::protobuf::Descriptor;
using grpc::protobuf::FileDescriptor;
using grpc::protobuf::MethodDescriptor;
using grpc::protobuf::ServiceDescriptor;
using grpc::protobuf::io::Printer;
using grpc::protobuf::io::StringOutputStream;
using std::map;

namespace grpc_php_generator {
namespace {

// Converts a proto package name to PHP namespace format
// Example: "example.package" becomes "Example\\Package"
std::string ConvertToPhpNamespace(const std::string& name) {
  std::vector<std::string> tokens = grpc_generator::tokenize(name, ".");
  std::ostringstream oss;
  for (unsigned int i = 0; i < tokens.size(); i++) {
    oss << (i == 0 ? "" : "\\")
        << grpc_generator::CapitalizeFirstLetter(tokens[i]);
  }
  return oss.str();
}

// Gets the PHP namespace for a file, either from explicit option or by converting proto package
std::string PackageName(const FileDescriptor* file) {
  if (file->options().has_php_namespace()) {
    return file->options().php_namespace();
  } else {
    return ConvertToPhpNamespace(std::string(file->package()));
  }
}

// Generates a fully qualified message identifier name for PHP
std::string MessageIdentifierName(const std::string& name,
                                  const FileDescriptor* file) {
  std::vector<std::string> tokens = grpc_generator::tokenize(name, ".");
  std::ostringstream oss;
  if (PackageName(file) != "") {
    oss << PackageName(file) << "\\";
  }
  oss << grpc_generator::CapitalizeFirstLetter(tokens[tokens.size() - 1]);
  return oss.str();
}

// Prints a client-side method implementation for a gRPC service
void PrintMethod(const MethodDescriptor* method, Printer* out) {
  const Descriptor* input_type = method->input_type();
  const Descriptor* output_type = method->output_type();
  map<std::string, std::string> vars;
  vars["service_name"] = method->service()->full_name();
  vars["name"] = method->name();
  vars["input_type_id"] =
      MessageIdentifierName(GeneratedClassName(input_type), input_type->file());
  vars["output_type_id"] = MessageIdentifierName(
      GeneratedClassName(output_type), output_type->file());

  // Handle different types of RPC methods (unary, client streaming, server streaming, bidirectional)
  if (method->client_streaming()) {
    out->Print("

\n"
               "public function $name$($$metadata = [], "
               "$$options = []) {\n");
    out->Indent();
    out->Indent();
    if (method->server_streaming()) {
      out->Print("return $$this->_bidiRequest(");
    } else {
      out->Print("return $$this->_clientStreamRequest(");
    }
    out->Print(vars,
               "'/$service_name$/$name$',\n"
               "['\\$output_type_id$','decode'],\n"
               "$$metadata, $$options);\n");
  } else {
    if (method->server_streaming()) {
      vars["return_type_id"] = "\\Grpc\\ServerStreamingCall";
    } else {
      vars["return_type_id"] = "\\Grpc\\UnaryCall";
    }
    out->Print(vars,
               " * @param \\$input_type_id$ $$argument input argument\n"
               " * @param array $$metadata metadata\n"
               " * @param array $$options call options\n"
               " * @return $return_type_id$\n */\n"
               "public function $name$(\\$input_type_id$ $$argument,\n"
               "  $$metadata = [], $$options = []) {\n");
    out->Indent();
    out->Indent();
    if (method->server_streaming()) {
      out->Print("return $$this->_serverStreamRequest(");
    } else {
      out->Print("return $$this->_simpleRequest(");
    }
    out->Print(vars,
               "'/$service_name$/$name$',\n"
               "$$argument,\n"
               "['\\$output_type_id$', 'decode'],\n"
               "$$metadata, $$options);\n");
  }
  out->Outdent();
  out->Outdent();
  out->Print("}\n\n");
}

// Prints a server-side method implementation for a gRPC service
void PrintServerMethod(const MethodDescriptor* method, Printer* out) {
  map<std::string, std::string> vars;
  const Descriptor* input_type = method->input_type();
  const Descriptor* output_type = method->output_type();
  vars["service_name"] = method->service()->full_name();
  vars["method_name"] = method->name();
  vars["input_type_id"] =
      MessageIdentifierName(GeneratedClassName(input_type), input_type->file());
  vars["output_type_id"] = MessageIdentifierName(
      GeneratedClassName(output_type), output_type->file());

  // Handle different types of RPC methods with appropriate method signatures
  if (method->client_streaming() && method->server_streaming()) {
    out->Print("

\n"
        "public function $method_name$(\n"
        "    \\Grpc\\ServerCallReader $$reader,\n"
        "    \\Grpc\\ServerCallWriter $$writer,\n"
        "    \\Grpc\\ServerContext $$context\n"
        "): void {\n"
        "    $$context->setStatus(\\Grpc\\Status::unimplemented());\n"
        "    $$writer->finish();\n"
        "}\n\n");
  } else if (method->client_streaming()) {
    out->Print("

\n"
        "public function $method_name$(\n"
        "    \\Grpc\\ServerCallReader $$reader,\n"
        "    \\Grpc\\ServerContext $$context\n"
        "): ?\\$output_type_id$ {\n"
        "    $$context->setStatus(\\Grpc\\Status::unimplemented());\n"
        "    return null;\n"
        "}\n\n");
  } else if (method->server_streaming()) {
    out->Print("

\n"
        "public function $method_name$(\n"
        "    \\$input_type_id$ $$request,\n"
        "    \\Grpc\\ServerCallWriter $$writer,\n"
        "    \\Grpc\\ServerContext $$context\n"
        "): void {\n"
        "    $$context->setStatus(\\Grpc\\Status::unimplemented());\n"
        "    $$writer->finish();\n"
        "}\n\n");
  } else {
    out->Print("

\n"
        "public function $method_name$(\n"
        "    \\$input_type_id$ $$request,\n"
        "    \\Grpc\\ServerContext $$context\n"
        "): ?\\$output_type_id$ {\n"
        "    $$context->setStatus(\\Grpc\\Status::unimplemented());\n"
        "    return null;\n"
        "}\n\n");
  }
}

// Prints method descriptors for server-side service implementation
void PrintServerMethodDescriptors(const ServiceDescriptor* service,
                                  Printer* out) {
  map<std::string, std::string> vars;
  vars["service_name"] = service->full_name();

  out->Print("

\n"
      "public final function getMethodDescriptors(): array\n{\n");
  out->Indent();
  out->Indent();
  out->Print("return [\n");
  out->Indent();
  out->Indent();
  for (int i = 0; i < service->method_count(); i++) {
    auto method = service->method(i);
    auto input_type = method->input_type();
    vars["method_name"] = method->name();
    vars["input_type_id"] = MessageIdentifierName(
        GeneratedClassName(input_type), input_type->file());
    // Determine call type based on streaming characteristics
    if (method->client_streaming() && method->server_streaming()) {
      vars["call_type"] = "BIDI_STREAMING_CALL";
    } else if (method->client_streaming()) {
      vars["call_type"] = "CLIENT_STREAMING_CALL";
    } else if (method->server_streaming()) {
      vars["call_type"] = "SERVER_STREAMING_CALL";
    } else {
      vars["call_type"] = "UNARY_CALL";
    }
    out->Print(
        vars,
        "'/$service_name$/$method_name$' => new \\Grpc\\MethodDescriptor(\n"
        "    $$this,\n"
        "    '$method_name$',\n"
        "    '\\$input_type_id$',\n"
        "    \\Grpc\\MethodDescriptor::$call_type$\n"
        "),\n");
  }
  out->Outdent();
  out->Outdent();
  out->Print("];\n");
  out->Outdent();
  out->Outdent();
  out->Print("}\n\n");
}

// Prints the complete service class (either client or server side)
void PrintService(const ServiceDescriptor* service,
                  const std::string& class_suffix, bool is_server,
                  Printer* out) {
  map<std::string, std::string> vars;
  out->Print("

\n");
  vars["name"] = GetPHPServiceClassname(service, class_suffix, is_server);
  vars["extends"] = is_server ? "" : "extends \\Grpc\\BaseStub ";
  out->Print(vars, "class $name$ $extends${\n\n");
  out->Indent();
  out->Indent();
  if (!is_server) {
    // Client-side constructor
    out->Print(
        "

\n"
        "public function __construct($$hostname, $$opts, "
        "$$channel = null) {\n");
    out->Indent();
    out->Indent();
    out->Print("parent::__construct($$hostname, $$opts, $$channel);\n");
    out->Outdent();
    out->Outdent();
    out->Print("}\n\n");
  }
  // Print all methods for the service
  for (int i = 0; i < service->method_count(); i++) {
    if (is_server) {
      PrintServerMethod(service->method(i), out);
    } else {
      PrintMethod(service->method(i), out);
    }
  }
  // Add method descriptors if this is a server implementation
  if (is_server) {
    PrintServerMethodDescriptors(service, out);
  }
  out->Outdent();
  out->Outdent();
  out->Print("}\n");
}
}  // namespace

// Main generation function that produces PHP service code
std::string GenerateFile(const FileDescriptor* file,
                         const ServiceDescriptor* service,
                         const std::string& class_suffix, bool is_server) {
  std::string output;
  {
    StringOutputStream output_stream(&output);
    Printer out(&output_stream, '$');

    // Generate PHP file header
    out.Print("<?php\n");
    out.Print("

    // Include original file comments if any
    std::string leading_comments = GetPHPComments(file, "//");
    if (!leading_comments.empty()) {
      out.Print("// Original file comments:\n");
      out.PrintRaw(leading_comments.c_str());
    }

    // Set up namespace
    map<std::string, std::string> vars;
    std::string php_namespace = PackageName(file);
    vars["package"] = php_namespace;
    out.Print(vars, "namespace $package$;\n\n");

    // Generate the service class
    PrintService(service, class_suffix, is_server, &out);
  }
  return output;
}

}  // namespace grpc_php_generator
```