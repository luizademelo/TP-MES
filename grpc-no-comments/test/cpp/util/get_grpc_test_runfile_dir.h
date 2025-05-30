// Copyright 2023 The gRPC Authors.

#ifndef GRPC_TEST_CPP_UTIL_GET_GRPC_TEST_RUNFILE_DIR_H
#define GRPC_TEST_CPP_UTIL_GET_GRPC_TEST_RUNFILE_DIR_H

#include <optional>
#include <string>

namespace grpc {

std::optional<std::string> GetGrpcTestRunFileDir();

}

#endif
