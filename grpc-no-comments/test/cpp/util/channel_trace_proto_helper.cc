
// Copyright 2018 gRPC authors.

#include "test/cpp/util/channel_trace_proto_helper.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/support/config.h>

#include "gtest/gtest.h"
#include "src/core/channelz/channelz_registry.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/crash.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "src/proto/grpc/channelz/channelz.pb.h"

namespace grpc {

namespace {

template <typename Message>
void ValidateProtoJsonTranslation(absl::string_view json_str) {
  Message msg;
  grpc::protobuf::json::JsonParseOptions parse_options;
  auto stripped = grpc_core::channelz::StripAdditionalInfoFromJson(json_str);

  grpc::protobuf::util::Status s =
      grpc::protobuf::json::JsonStringToMessage(stripped, &msg, parse_options);
  EXPECT_TRUE(s.ok()) << s;
  std::string proto_json_str;
  grpc::protobuf::json::JsonPrintOptions print_options;

  s = grpc::protobuf::json::MessageToJsonString(msg, &proto_json_str,
                                                print_options);
  EXPECT_TRUE(s.ok());

  auto parsed_json = grpc_core::JsonParse(proto_json_str.c_str());
  ASSERT_TRUE(parsed_json.ok()) << parsed_json.status();
  ASSERT_EQ(parsed_json->type(), grpc_core::Json::Type::kObject);
  proto_json_str = grpc_core::JsonDump(*parsed_json);
  EXPECT_EQ(stripped, proto_json_str);
}

}

namespace testing {

void ValidateChannelTraceProtoJsonTranslation(absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::ChannelTrace>(json_string);
}

void ValidateChannelProtoJsonTranslation(absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::Channel>(json_string);
}

void ValidateGetTopChannelsResponseProtoJsonTranslation(
    absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::GetTopChannelsResponse>(
      json_string);
}

void ValidateGetChannelResponseProtoJsonTranslation(
    absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::GetChannelResponse>(
      json_string);
}

void ValidateGetServerResponseProtoJsonTranslation(
    absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::GetServerResponse>(
      json_string);
}

void ValidateSubchannelProtoJsonTranslation(absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::Subchannel>(json_string);
}

void ValidateServerProtoJsonTranslation(absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::Server>(json_string);
}

void ValidateGetServersResponseProtoJsonTranslation(
    absl::string_view json_string) {
  ValidateProtoJsonTranslation<grpc::channelz::v1::GetServersResponse>(
      json_string);
}

}
}
