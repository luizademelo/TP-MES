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

#ifndef GRPC_INTERNAL_COMPILER_PROTOBUF_PLUGIN_H
#define GRPC_INTERNAL_COMPILER_PROTOBUF_PLUGIN_H

#include <vector>

#include "src/compiler/config.h"
#include "src/compiler/cpp_generator_helpers.h"
#include "src/compiler/python_generator_helpers.h"
#include "src/compiler/python_private_generator.h"
#include "src/compiler/schema_interface.h"

// Helper function to get comments from protobuf descriptors
// Parameters:
//   desc: The descriptor to get comments from
//   leading: Whether to get leading comments (true) or trailing comments (false)
//   prefix: String prefix to add to each comment line
template <typename DescriptorType>
inline std::string GetCommentsHelper(const DescriptorType* desc, bool leading,
                                     const std::string& prefix) {
  return grpc_generator::GetPrefixedComments(desc, leading, prefix);
}

// Wrapper class for protobuf method descriptors that implements the
// grpc_generator::Method interface
class ProtoBufMethod : public grpc_generator::Method {
 public:
  explicit ProtoBufMethod(const grpc::protobuf::MethodDescriptor* method)
      : method_(method) {}

  // Returns the name of the method
  std::string name() const { return std::string(method_->name()); }

  // Returns the fully qualified name of the input type
  std::string input_type_name() const {
    return grpc_cpp_generator::ClassName(method_->input_type(), true);
  }
  
  // Returns the fully qualified name of the output type
  std::string output_type_name() const {
    return grpc_cpp_generator::ClassName(method_->output_type(), true);
  }

  // Returns the file name where the input type is defined
  std::string get_input_type_name() const {
    return std::string(method_->input_type()->file()->name());
  }
  
  // Returns the file name where the output type is defined
  std::string get_output_type_name() const {
    return std::string(method_->output_type()->file()->name());
  }

  // Gets the module and message path for the input type (Python-specific)
  bool get_module_and_message_path_input(
      std::string* str, std::string generator_file_name,
      bool generate_in_pb2_grpc, std::string import_prefix,
      const std::vector<std::string>& prefixes_to_filter) const final {
    return grpc_python_generator::GetModuleAndMessagePath(
        method_->input_type(), str, generator_file_name, generate_in_pb2_grpc,
        import_prefix, prefixes_to_filter);
  }

  // Gets the module and message path for the output type (Python-specific)
  bool get_module_and_message_path_output(
      std::string* str, std::string generator_file_name,
      bool generate_in_pb2_grpc, std::string import_prefix,
      const std::vector<std::string>& prefixes_to_filter) const final {
    return grpc_python_generator::GetModuleAndMessagePath(
        method_->output_type(), str, generator_file_name, generate_in_pb2_grpc,
        import_prefix, prefixes_to_filter);
  }

  // Returns true if this is a unary RPC (no streaming)
  bool NoStreaming() const {
    return !method_->client_streaming() && !method_->server_streaming();
  }

  // Returns true if this is a client streaming RPC
  bool ClientStreaming() const { return method_->client_streaming(); }

  // Returns true if this is a server streaming RPC
  bool ServerStreaming() const { return method_->server_streaming(); }

  // Returns true if this is a bidirectional streaming RPC
  bool BidiStreaming() const {
    return method_->client_streaming() && method_->server_streaming();
  }

  // Returns the leading comments for this method
  std::string GetLeadingComments(const std::string prefix) const {
    return GetCommentsHelper(method_, true, prefix);
  }

  // Returns the trailing comments for this method
  std::string GetTrailingComments(const std::string prefix) const {
    return GetCommentsHelper(method_, false, prefix);
  }

  // Returns all comments for this method (Python-specific)
  vector<std::string> GetAllComments() const {
    return grpc_python_generator::get_all_comments(method_);
  }

 private:
  const grpc::protobuf::MethodDescriptor* method_;  // Underlying protobuf descriptor
};

// Wrapper class for protobuf service descriptors that implements the
// grpc_generator::Service interface
class ProtoBufService : public grpc_generator::Service {
 public:
  explicit ProtoBufService(const grpc::protobuf::ServiceDescriptor* service)
      : service_(service) {}

  // Returns the name of the service
  std::string name() const { return std::string(service_->name()); }
  
  // Returns true if the service is marked as deprecated
  bool is_deprecated() const { return service_->options().deprecated(); }

  // Returns the number of methods in this service
  int method_count() const { return service_->method_count(); }
  
  // Returns a method wrapper for the method at index i
  std::unique_ptr<const grpc_generator::Method> method(int i) const {
    return std::unique_ptr<const grpc_generator::Method>(
        new ProtoBufMethod(service_->method(i)));
  }

  // Returns the leading comments for this service
  std::string GetLeadingComments(const std::string prefix) const {
    return GetCommentsHelper(service_, true, prefix);
  }

  // Returns the trailing comments for this service
  std::string GetTrailingComments(const std::string prefix) const {
    return GetCommentsHelper(service_, false, prefix);
  }

  // Returns all comments for this service (Python-specific)
  vector<std::string> GetAllComments() const {
    return grpc_python_generator::get_all_comments(service_);
  }

 private:
  const grpc::protobuf::ServiceDescriptor* service_;  // Underlying protobuf descriptor
};

// Printer implementation that writes to a string buffer
class ProtoBufPrinter : public grpc_generator::Printer {
 public:
  explicit ProtoBufPrinter(std::string* str)
      : output_stream_(str), printer_(&output_stream_, '$') {}

  // Prints a template string with variable substitution
  void Print(const std::map<std::string, std::string>& vars,
             const char* string_template) {
    printer_.Print(vars, string_template);
  }

  // Prints a simple string
  void Print(const char* string) { printer_.Print(string); }
  
  // Prints a string without any processing
  void PrintRaw(const char* string) { printer_.PrintRaw(string); }
  
  // Increases indentation level
  void Indent() { printer_.Indent(); }
  
  // Decreases indentation level
  void Outdent() { printer_.Outdent(); }

 private:
  grpc::protobuf::io::StringOutputStream output_stream_;  // Output buffer
  grpc::protobuf::io::Printer printer_;                  // Protobuf printer utility
};

// Wrapper class for protobuf file descriptors that implements the
// grpc_generator::File interface
class ProtoBufFile : public grpc_generator::File {
 public:
  explicit ProtoBufFile(const grpc::protobuf::FileDescriptor* file) : file_(file) {}

  // Returns the filename of the proto file
  std::string filename() const { return std::string(file_->name()); }
  
  // Returns the filename without extension
  std::string filename_without_ext() const {
    return grpc_generator::StripProto(filename());
  }

  // Returns the package name of the proto file
  std::string package() const { return std::string(file_->package()); }
  
  // Returns the package name split into parts by dots
  std::vector<std::string> package_parts() const {
    return grpc_generator::tokenize(package(), ".");
  }

  // Placeholder for additional headers (returns empty string)
  std::string additional_headers() const { return ""; }

  // Returns the number of services defined in this file
  int service_count() const { return file_->service_count(); }
  
  // Returns a service wrapper for the service at index i
  std::unique_ptr<const grpc_generator::Service> service(int i) const {
    return std::unique_ptr<const grpc_generator::Service>(
        new ProtoBufService(file_->service(i)));
  }

  // Creates a printer that writes to the given string buffer
  std::unique_ptr<grpc_generator::Printer> CreatePrinter(
      std::string* str) const {
    return std::unique_ptr<grpc_generator::Printer>(new ProtoBufPrinter(str));
  }

  // Returns the leading comments for this file
  std::string GetLeadingComments(const std::string prefix) const {
    return GetCommentsHelper(file_, true, prefix);
  }

  // Returns the trailing comments for this file
  std::string GetTrailingComments(const std::string prefix) const {
    return GetCommentsHelper(file_, false, prefix);
  }

  // Returns all comments for this file (Python-specific)
  vector<std::string> GetAllComments() const {
    return grpc_python_generator::get_all_comments(file_);
  }

  // Returns the names of all imported proto files
  vector<std::string> GetImportNames() const {
    vector<std::string> proto_names;
    for (int i = 0; i < file_->dependency_count(); ++i) {
      const auto& dep = *file_->dependency(i);
      proto_names.emplace_back(dep.name());
    }
    return proto_names;
  }

 private:
  const grpc::protobuf::FileDescriptor* file_;  // Underlying protobuf descriptor
};

#endif
```

The comments added explain:
1. The purpose of each class and its role in the gRPC code generation system
2. The functionality of each method
3. Parameters and return values
4. Implementation details where relevant
5. Relationships between classes
6. Special notes about Python-specific functionality

The comments maintain a consistent style and provide enough detail to understand the code without being overly verbose. They focus on the "why" and "what" rather than just repeating the "how" that's already evident from the code itself.