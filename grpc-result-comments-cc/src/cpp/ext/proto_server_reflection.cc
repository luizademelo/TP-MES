Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/cpp/ext/proto_server_reflection.h"

#include <grpcpp/grpcpp.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/sync_stream.h>

#include <unordered_set>
#include <vector>

namespace grpc {

// Handles bidirectional streaming RPC for server reflection requests
// Reads requests from the stream and processes them based on the request type
// Writes appropriate responses back to the stream
template <typename Request, typename Response>
Status ProtoServerReflectionBackend::ServerReflectionInfo(
    ServerReaderWriter<Response, Request>* stream) const {
  Request request;
  Response response;
  Status status;
  
  // Process each incoming request from the stream
  while (stream->Read(&request)) {
    // Handle different types of reflection requests
    switch (request.message_request_case()) {
      case Request::MessageRequestCase::kFileByFilename:
        // Get file descriptor by filename
        status = GetFileByName(request.file_by_filename(), &response);
        break;
      case Request::MessageRequestCase::kFileContainingSymbol:
        // Get file descriptor containing the specified symbol
        status = GetFileContainingSymbol(request.file_containing_symbol(),
                                         &response);
        break;
      case Request::MessageRequestCase::kFileContainingExtension:
        // Get file descriptor containing the specified extension
        status = GetFileContainingExtension(
            &request.file_containing_extension(), &response);
        break;
      case Request::MessageRequestCase::kAllExtensionNumbersOfType:
        // Get all extension numbers for the specified type
        status = GetAllExtensionNumbers(
            request.all_extension_numbers_of_type(),
            response.mutable_all_extension_numbers_response());
        break;
      case Request::MessageRequestCase::kListServices:
        // List all services
        status = ListService(response.mutable_list_services_response());
        break;
      default:
        // Handle unknown request types
        status = Status(StatusCode::UNIMPLEMENTED, "");
    }

    // If there was an error, fill the error response
    if (!status.ok()) {
      FillErrorResponse(status, response.mutable_error_response());
    }
    // Set response metadata
    response.set_valid_host(request.host());
    response.set_allocated_original_request(new Request(request));
    // Write the response back to the stream
    stream->Write(response);
  }
  return Status::OK;
}

// Fills error response with status code and message
template <typename Response>
void ProtoServerReflectionBackend::FillErrorResponse(
    const Status& status, Response* error_response) const {
  error_response->set_error_code(status.error_code());
  error_response->set_error_message(status.error_message());
}

// Lists all available services
template <typename Response>
Status ProtoServerReflectionBackend::ListService(Response* response) const {
  if (services_ == nullptr) {
    return Status(StatusCode::NOT_FOUND, "Services not found.");
  }
  // Add each service name to the response
  for (const auto& value : *services_) {
    auto* service_response = response->add_service();
    service_response->set_name(value);
  }
  return Status::OK;
}

// Gets file descriptor by filename
template <typename Response>
Status ProtoServerReflectionBackend::GetFileByName(const std::string& file_name,
                                                   Response* response) const {
  if (descriptor_pool_ == nullptr) {
    return Status::CANCELLED;
  }

  // Find file descriptor in the pool
  const protobuf::FileDescriptor* file_desc =
      descriptor_pool_->FindFileByName(file_name);
  if (file_desc == nullptr) {
    return Status(StatusCode::NOT_FOUND, "File not found.");
  }
  // Fill response with file descriptor and its dependencies
  std::unordered_set<std::string> seen_files;
  FillFileDescriptorResponse(file_desc, response, &seen_files);
  return Status::OK;
}

// Gets file descriptor containing the specified symbol
template <typename Response>
Status ProtoServerReflectionBackend::GetFileContainingSymbol(
    const std::string& symbol, Response* response) const {
  if (descriptor_pool_ == nullptr) {
    return Status::CANCELLED;
  }

  // Find file descriptor containing the symbol
  const protobuf::FileDescriptor* file_desc =
      descriptor_pool_->FindFileContainingSymbol(symbol);
  if (file_desc == nullptr) {
    return Status(StatusCode::NOT_FOUND, "Symbol not found.");
  }
  // Fill response with file descriptor and its dependencies
  std::unordered_set<std::string> seen_files;
  FillFileDescriptorResponse(file_desc, response, &seen_files);
  return Status::OK;
}

// Gets file descriptor containing the specified extension
template <typename Request, typename Response>
Status ProtoServerReflectionBackend::GetFileContainingExtension(
    const Request* request, Response* response) const {
  if (descriptor_pool_ == nullptr) {
    return Status::CANCELLED;
  }

  // Find descriptor for the containing type
  const protobuf::Descriptor* desc =
      descriptor_pool_->FindMessageTypeByName(request->containing_type());
  if (desc == nullptr) {
    return Status(StatusCode::NOT_FOUND, "Type not found.");
  }

  // Find field descriptor for the extension
  const protobuf::FieldDescriptor* field_desc =
      descriptor_pool_->FindExtensionByNumber(desc,
                                              request->extension_number());
  if (field_desc == nullptr) {
    return Status(StatusCode::NOT_FOUND, "Extension not found.");
  }
  // Fill response with file descriptor and its dependencies
  std::unordered_set<std::string> seen_files;
  FillFileDescriptorResponse(field_desc->file(), response, &seen_files);
  return Status::OK;
}

// Gets all extension numbers for the specified type
template <typename Response>
Status ProtoServerReflectionBackend::GetAllExtensionNumbers(
    const std::string& type, Response* response) const {
  if (descriptor_pool_ == nullptr) {
    return Status::CANCELLED;
  }

  // Find descriptor for the base type
  const protobuf::Descriptor* desc =
      descriptor_pool_->FindMessageTypeByName(type);
  if (desc == nullptr) {
    return Status(StatusCode::NOT_FOUND, "Type not found.");
  }

  // Find all extensions for the type
  std::vector<const protobuf::FieldDescriptor*> extensions;
  descriptor_pool_->FindAllExtensions(desc, &extensions);
  // Add each extension number to the response
  for (const auto& value : extensions) {
    response->add_extension_number(value->number());
  }
  response->set_base_type_name(type);
  return Status::OK;
}

// Recursively fills file descriptor response with descriptor and its dependencies
// Uses seen_files to avoid duplicate entries
template <typename Response>
void ProtoServerReflectionBackend::FillFileDescriptorResponse(
    const protobuf::FileDescriptor* file_desc, Response* response,
    std::unordered_set<std::string>* seen_files) const {
  // Check if we've already processed this file
  bool inserted = seen_files->emplace(file_desc->name()).second;
  if (!inserted) {
    return;
  }

  // Serialize file descriptor to protobuf
  protobuf::FileDescriptorProto file_desc_proto;
  std::string data;
  file_desc->CopyTo(&file_desc_proto);
  file_desc_proto.SerializeToString(&data);
  response->mutable_file_descriptor_response()->add_file_descriptor_proto(data);

  // Recursively process all dependencies
  for (int i = 0; i < file_desc->dependency_count(); ++i) {
    FillFileDescriptorResponse(file_desc->dependency(i), response, seen_files);
  }
}

// Implementation of ServerReflectionInfo for v1alpha API
Status ProtoServerReflection::ServerReflectionInfo(
    ServerContext* ,
    ServerReaderWriter<reflection::v1alpha::ServerReflectionResponse,
                       reflection::v1alpha::ServerReflectionRequest>* stream) {
  return backend_->ServerReflectionInfo(stream);
}

// Implementation of ServerReflectionInfo for v1 API
Status ProtoServerReflectionV1::ServerReflectionInfo(
    ServerContext* ,
    ServerReaderWriter<reflection::v1::ServerReflectionResponse,
                       reflection::v1::ServerReflectionRequest>* stream) {
  return backend_->ServerReflectionInfo(stream);
}

}
```