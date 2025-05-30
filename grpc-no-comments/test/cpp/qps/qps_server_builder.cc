
// Copyright 2016 gRPC authors.

#include "test/cpp/qps/qps_server_builder.h"

#include "absl/memory/memory.h"

using grpc::ServerBuilder;

namespace grpc {
namespace testing {

namespace {
std::unique_ptr<ServerBuilder> DefaultCreateQpsServerBuilder() {
  return std::make_unique<ServerBuilder>();
}

std::function<std::unique_ptr<ServerBuilder>()> g_create_qps_server_builder =
    DefaultCreateQpsServerBuilder;
}

std::unique_ptr<ServerBuilder> CreateQpsServerBuilder() {
  return g_create_qps_server_builder();
}

void SetCreateQpsServerBuilderFunc(
    std::function<std::unique_ptr<ServerBuilder>()> create_qps_server_builder) {
  g_create_qps_server_builder = std::move(create_qps_server_builder);
}

}
}
