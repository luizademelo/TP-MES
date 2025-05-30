
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_PARSE_JSON_H
#define GRPC_TEST_CPP_QPS_PARSE_JSON_H

#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/support/config.h>

namespace grpc {
namespace testing {

void ParseJson(const std::string& json, const std::string& type,
               GRPC_CUSTOM_MESSAGE* msg);

std::string SerializeJson(const GRPC_CUSTOM_MESSAGE& msg,
                          const std::string& type);

}
}

#endif
