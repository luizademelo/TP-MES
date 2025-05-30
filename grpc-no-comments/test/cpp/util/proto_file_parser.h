
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_PROTO_FILE_PARSER_H
#define GRPC_TEST_CPP_UTIL_PROTO_FILE_PARSER_H

#include <grpcpp/channel.h>

#include <memory>

#include "test/cpp/util/config_grpc_cli.h"
#include "test/cpp/util/proto_reflection_descriptor_database.h"

#if defined(_WIN32) && !defined(__CYGWIN__)
#define GRPC_CLI_PATH_SEPARATOR ";"
#else
#define GRPC_CLI_PATH_SEPARATOR ":"
#endif

namespace grpc {
namespace testing {
class ErrorPrinter;

class ProtoFileParser {
 public:

  ProtoFileParser(const std::shared_ptr<grpc::Channel>& channel,
                  const std::string& proto_path, const std::string& protofiles);

  ~ProtoFileParser();

  std::string GetFullMethodName(const std::string& method);

  std::string GetFormattedMethodName(const std::string& method);

  std::string GetSerializedProtoFromMethod(const std::string& method,
                                           const std::string& formatted_proto,
                                           bool is_request,
                                           bool is_json_format);

  std::string GetSerializedProtoFromMessageType(
      const std::string& message_type_name, const std::string& formatted_proto,
      bool is_json_format);

  std::string GetFormattedStringFromMethod(const std::string& method,
                                           const std::string& serialized_proto,
                                           bool is_request,
                                           bool is_json_format);

  std::string GetFormattedStringFromMessageType(
      const std::string& message_type_name, const std::string& serialized_proto,
      bool is_json_format);

  bool IsStreaming(const std::string& method, bool is_request);

  bool HasError() const { return has_error_; }

  void LogError(const std::string& error_msg);

 private:
  std::string GetMessageTypeFromMethod(const std::string& method,
                                       bool is_request);

  bool has_error_;
  std::string request_text_;
  protobuf::compiler::DiskSourceTree source_tree_;
  std::unique_ptr<ErrorPrinter> error_printer_;
  std::unique_ptr<protobuf::compiler::Importer> importer_;
  std::unique_ptr<grpc::ProtoReflectionDescriptorDatabase> reflection_db_;
  std::unique_ptr<protobuf::DescriptorPoolDatabase> file_db_;
  std::unique_ptr<protobuf::DescriptorDatabase> desc_db_;
  std::unique_ptr<protobuf::DescriptorPool> desc_pool_;
  std::unique_ptr<protobuf::DynamicMessageFactory> dynamic_factory_;
  std::unique_ptr<grpc::protobuf::Message> request_prototype_;
  std::unique_ptr<grpc::protobuf::Message> response_prototype_;
  std::unordered_map<std::string, std::string> known_methods_;
  std::vector<const protobuf::ServiceDescriptor*> service_desc_list_;
};

}
}

#endif
