
// Copyright 2016 gRPC authors.

#include "test/cpp/qps/parse_json.h"

#include <string>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/util/crash.h"

namespace grpc {
namespace testing {

void ParseJson(const std::string& json, const std::string& type,
               GRPC_CUSTOM_MESSAGE* msg) {
  std::unique_ptr<protobuf::json::TypeResolver> type_resolver(
      protobuf::json::NewTypeResolverForDescriptorPool(
          "type.googleapis.com", protobuf::DescriptorPool::generated_pool()));
  std::string binary;
  auto status = JsonToBinaryString(
      type_resolver.get(), "type.googleapis.com/" + type, json, &binary);
  if (!status.ok()) {
    std::string errmsg(status.message());
    LOG(ERROR) << "Failed to convert json to binary: errcode=" << status.code()
               << " msg=" << errmsg;
    grpc_core::Crash(absl::StrFormat("JSON: %s", json.c_str()));
  }
  CHECK(msg->ParseFromString(binary));
}

std::string SerializeJson(const GRPC_CUSTOM_MESSAGE& msg,
                          const std::string& type) {
  std::unique_ptr<protobuf::json::TypeResolver> type_resolver(
      protobuf::json::NewTypeResolverForDescriptorPool(
          "type.googleapis.com", protobuf::DescriptorPool::generated_pool()));
  std::string binary;
  std::string json_string;
  msg.SerializeToString(&binary);
  auto status =
      BinaryToJsonString(type_resolver.get(), type, binary, &json_string);
  CHECK_OK(status);
  return json_string;
}

}
}
