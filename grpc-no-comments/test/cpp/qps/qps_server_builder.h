
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_QPS_SERVER_BUILDER_H
#define GRPC_TEST_CPP_QPS_QPS_SERVER_BUILDER_H

#include <grpcpp/server_builder.h>

#include <functional>
#include <memory>

namespace grpc {
namespace testing {

std::unique_ptr<ServerBuilder> CreateQpsServerBuilder();

void SetCreateQpsServerBuilderFunc(
    std::function<std::unique_ptr<ServerBuilder>()>);

}
}

#endif
