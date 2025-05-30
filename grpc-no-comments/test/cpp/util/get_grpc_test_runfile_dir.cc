// Copyright 2023 The gRPC Authors.

#include "test/cpp/util/get_grpc_test_runfile_dir.h"

#include "src/core/util/env.h"

namespace grpc {

std::optional<std::string> GetGrpcTestRunFileDir() {
  std::optional<std::string> test_srcdir = grpc_core::GetEnv("TEST_SRCDIR");
  if (!test_srcdir.has_value()) {
    return std::nullopt;
  }
  return *test_srcdir + "/com_github_grpc_grpc";
}

}
