
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_CHANNEL_TRACE_PROTO_HELPER_H
#define GRPC_TEST_CPP_UTIL_CHANNEL_TRACE_PROTO_HELPER_H

#include "absl/strings/string_view.h"

namespace grpc {
namespace testing {

void ValidateChannelTraceProtoJsonTranslation(absl::string_view json_string);
void ValidateChannelProtoJsonTranslation(absl::string_view json_string);
void ValidateGetTopChannelsResponseProtoJsonTranslation(
    absl::string_view json_string);
void ValidateGetChannelResponseProtoJsonTranslation(
    absl::string_view json_string);
void ValidateGetServerResponseProtoJsonTranslation(
    absl::string_view json_string);
void ValidateSubchannelProtoJsonTranslation(absl::string_view json_string);
void ValidateServerProtoJsonTranslation(absl::string_view json_string);
void ValidateGetServersResponseProtoJsonTranslation(
    absl::string_view json_string);

}
}

#endif
