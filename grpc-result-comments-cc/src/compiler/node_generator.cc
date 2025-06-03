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

#include "src/compiler/node_generator.h"

#include <map>

#include "src/compiler/config.h"
#include "src/compiler/generator_helpers.h"
#include "src/compiler/node_generator_helpers.h"

using grpc::protobuf::Descriptor;
using grpc::protobuf::FileDescriptor;
using grpc::protobuf::MethodDescriptor;
using grpc::protobuf::ServiceDescriptor;
using grpc::protobuf::io::Printer;
using grpc::protobuf::io::StringOutputStream;
using std::map;

namespace grpc_node_generator {
namespace {

// Generates a module alias from a proto filename by:
// 1. Stripping the .proto extension
// 2. Replacing special characters (-, /, .) with JS-friendly alternatives
std::string ModuleAlias(const std::string filename) {
  std::string basename = grpc_generator::StripProto(filename);
  basename = grpc_generator::StringReplace(basename, "-", "$");
  basename = grpc_generator::StringReplace(basename, "/", "_");
  basename = grpc_generator::StringReplace(basename, ".", "_");
  return basename + "_pb";
}

// Generates the JS filename for message definitions by replacing .proto with _pb.js
std::string GetJSMessageFilename(const std::string& filename) {
  std::string name = filename;
  return grpc_generator::StripProto(name) + "_pb.js";
}

// Calculates the root path between two files, with special handling for google/protobuf files
std::string GetRootPath(const std::string& from_filename,
                        const std::string& to_filename) {
  // Special case for protobuf core messages
  if (to_filename.find("google/protobuf") == 0) {
    return "google-protobuf/";
  }
  // Count directory levels in source file to create proper relative path
  size_t slashes = std::count(from_filename.begin(), from_filename.end(), '/');
  if (slashes == 0) {
    return "./";
  }
  std::string result = "";
  for (size_t i = 0; i < slashes; i++) {
    result += "../";
  }
  return result;
}

// Generates a relative path from one file to another
std::string GetRelativePath(const std::string& from_file,
                            const std::string& to_file) {
  return GetRootPath(from_file, to_file) + to_file;
}

// Collects all message types used in the file's service methods
map<std::string, const Descriptor*> GetAllMessages(const FileDescriptor* file) {
  map<std::string, const Descriptor*> message_types;
  for (int service_num = 0; service_num < file->service_count();
       service_num++) {
    const ServiceDescriptor* service = file->service(service_num);
    for (int method_num = 0; method_num < service->method_count();
         method_num++) {
      const MethodDescriptor* method = service->method(method_num);
      const Descriptor* input_type = method->input_type();
      const Descriptor* output_type = method->output_type();
      message_types[std::string(input_type->full_name())] = input_type;
      message_types[std::string(output_type->full_name())] = output_type;
    }
  }
  return message_types;
}

// Converts a fully qualified message name to a JS-friendly identifier
std::string MessageIdentifierName(const std::string& name) {
  return grpc_generator::StringReplace(name, ".", "_");
}

// Generates the full object path for a message in the generated JS code
std::string NodeObjectPath(const Descriptor* descriptor) {
  std::string module_alias =
      ModuleAlias(std::string(descriptor->file()->name()));
  std::string name(descriptor->full_name());
  grpc_generator::StripPrefix(&name,
                              std::string(descriptor->file()->package()) + ".");
  return module_alias + "." + name;
}

// Generates serialization/deserialization functions for a message type
void PrintMessageTransformer(const Descriptor* descriptor, Printer* out,
                             const Parameters& params) {
  map<std::string, std::string> template_vars;
  std::string full_name(descriptor->full_name());
  template_vars["identifier_name"] = MessageIdentifierName(full_name);
  template_vars["name"] = full_name;
  template_vars["node_name"] = NodeObjectPath(descriptor);

  // Generate serialize function
  out->Print(template_vars, "function serialize_$identifier_name$(arg) {\n");
  out->Indent();
  out->Print(template_vars, "if (!(arg instanceof $node_name$)) {\n");
  out->Indent();
  out->Print(template_vars,
             "throw new Error('Expected argument of type $name$');\n");
  out->Outdent();
  out->Print("}\n");
  // Handle different Buffer creation syntax for Node versions
  if (params.minimum_node_version > 5) {
    out->Print("return Buffer.from(arg.serializeBinary());\n");
  } else {
    out->Print("return new Buffer(arg.serializeBinary());\n");
  }
  out->Outdent();
  out->Print("}\n\n");

  // Generate deserialize function
  out->Print(template_vars,
             "function deserialize_$identifier_name$(buffer_arg) {\n");
  out->Indent();
  out->Print(
      template_vars,
      "return $node_name$.deserializeBinary(new Uint8Array(buffer_arg));\n");
  out->Outdent();
  out->Print("}\n\n");
}

// Generates the method descriptor object for a gRPC method
void PrintMethod(const MethodDescriptor* method, Printer* out) {
  const Descriptor* input_type = method->input_type();
  const Descriptor* output_type = method->output_type();
  map<std::string, std::string> vars;
  vars["service_name"] = method->service()->full_name();
  vars["name"] = method->name();
  vars["input_type"] = NodeObjectPath(input_type);
  vars["input_type_id"] =
      MessageIdentifierName(std::string(input_type->full_name()));
  vars["output_type"] = NodeObjectPath(output_type);
  vars["output_type_id"] =
      MessageIdentifierName(std::string(output_type->full_name()));
  vars["client_stream"] = method->client_streaming() ? "true" : "false";
  vars["server_stream"] = method->server_streaming() ? "true" : "false";
  out->Print("{\n");
  out->Indent();
  // Print method descriptor properties
  out->Print(vars, "path: '/$service_name$/$name$',\n");
  out->Print(vars, "requestStream: $client_stream$,\n");
  out->Print(vars, "responseStream: $server_stream$,\n");
  out->Print(vars, "requestType: $input_type$,\n");
  out->Print(vars, "responseType: $output_type$,\n");
  out->Print(vars, "requestSerialize: serialize_$input_type_id$,\n");
  out->Print(vars, "requestDeserialize: deserialize_$input_type_id$,\n");
  out->Print(vars, "responseSerialize: serialize_$output_type_id$,\n");
  out->Print(vars, "responseDeserialize: deserialize_$output_type_id$,\n");
  out->Outdent();
  out->Print("}");
}

// Generates the service descriptor and client constructor for a gRPC service
void PrintService(const ServiceDescriptor* service, Printer* out) {
  map<std::string, std::string> template_vars;
  out->Print(GetNodeComments(service, true).c_str());
  template_vars["name"] = service->name();
  out->Print(template_vars, "var $name$Service = exports.$name$Service = {\n");
  out->Indent();
  // Generate all methods for the service
  for (int i = 0; i < service->method_count(); i++) {
    std::string method_name = grpc_generator::LowercaseFirstLetter(
        std::string(service->method(i)->name()));
    out->Print(GetNodeComments(service->method(i), true).c_str());
    out->Print("$method_name$: ", "method_name", method_name);
    PrintMethod(service->method(i), out);
    out->Print(",\n");
    out->Print(GetNodeComments(service->method(i), false).c_str());
  }
  out->Outdent();
  out->Print("};\n\n");
  // Generate client constructor
  out->Print(template_vars,
             "exports.$name$Client = "
             "grpc.makeGenericClientConstructor($name$Service);\n");
  out->Print(GetNodeComments(service, false).c_str());
}

// Generates require statements for all dependencies
void PrintImports(const FileDescriptor* file, Printer* out) {
  out->Print("var grpc = require('grpc');\n");
  // Import message definitions from this file if needed
  if (file->message_type_count() > 0) {
    std::string file_path =
        GetRelativePath(std::string(file->name()),
                        GetJSMessageFilename(std::string(file->name())));
    out->Print("var $module_alias$ = require('$file_path$');\n", "module_alias",
               ModuleAlias(std::string(file->name())), "file_path", file_path);
  }

  // Import message definitions from dependencies
  for (int i = 0; i < file->dependency_count(); i++) {
    std::string file_path = GetRelativePath(
        std::string(file->name()),
        GetJSMessageFilename(std::string(file->dependency(i)->name())));
    out->Print("var $module_alias$ = require('$file_path$');\n", "module_alias",
               ModuleAlias(std::string(file->dependency(i)->name())),
               "file_path", file_path);
  }
  out->Print("\n");
}

// Generates all serialization/deserialization functions needed by the services
void PrintTransformers(const FileDescriptor* file, Printer* out,
                       const Parameters& params) {
  map<std::string, const Descriptor*> messages = GetAllMessages(file);
  for (std::map<std::string, const Descriptor*>::iterator it = messages.begin();
       it != messages.end(); it++) {
    PrintMessageTransformer(it->second, out, params);
  }
  out->Print("\n");
}

// Generates all services defined in the proto file
void PrintServices(const FileDescriptor* file, Printer* out) {
  for (int i = 0; i < file->service_count(); i++) {
    PrintService(file->service(i), out);
  }
}
}

// Main generation function that produces the Node.js gRPC service file
std::string GenerateFile(const FileDescriptor* file, const Parameters& params) {
  std::string output;
  {
    StringOutputStream output_stream(&output);
    Printer out(&output_stream, '$');

    // Skip generation if no services are defined
    if (file->service_count() == 0) {
      return output;
    }
    out.Print("// GENERATED CODE -- DO NOT EDIT!\n\n");

    // Print original file comments if present
    std::string leading_comments = GetNodeComments(file, true);
    if (!leading_comments.empty()) {
      out.Print("// Original file comments:\n");
      out.PrintRaw(leading_comments.c_str());
    }

    out.Print("'use strict';\n");

    PrintImports(file, &out);

    PrintTransformers(file, &out, params);

    PrintServices(file, &out);

    out.Print(GetNodeComments(file, false).c_str());
  }
  return output;
}

}
```