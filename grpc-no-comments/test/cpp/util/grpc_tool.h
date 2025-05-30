
// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_GRPC_TOOL_H
#define GRPC_TEST_CPP_UTIL_GRPC_TOOL_H

#include <grpcpp/support/config.h>

#include <functional>

#include "test/cpp/util/cli_credentials.h"

namespace grpc {
namespace testing {

typedef std::function<bool(const std::string&)> GrpcToolOutputCallback;

int GrpcToolMainLib(int argc, const char** argv, const CliCredentials& cred,
                    const GrpcToolOutputCallback& callback);

}
}

#endif
