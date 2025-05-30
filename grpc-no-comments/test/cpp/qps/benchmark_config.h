
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_BENCHMARK_CONFIG_H
#define GRPC_TEST_CPP_QPS_BENCHMARK_CONFIG_H

#include <memory>

#include "test/cpp/qps/report.h"

namespace grpc {
namespace testing {

std::shared_ptr<Reporter> GetReporter();

}
}

#endif
