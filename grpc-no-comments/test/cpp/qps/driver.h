
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_DRIVER_H
#define GRPC_TEST_CPP_QPS_DRIVER_H

#include <memory>

#include "src/proto/grpc/testing/control.pb.h"
#include "test/cpp/qps/histogram.h"

namespace grpc {
namespace testing {

std::unique_ptr<ScenarioResult> RunScenario(
    const grpc::testing::ClientConfig& client_config, size_t num_clients,
    const grpc::testing::ServerConfig& server_config, size_t num_servers,
    int warmup_seconds, int benchmark_seconds, int spawn_local_worker_count,
    const std::string& qps_server_target_override,
    const std::string& credential_type,
    const std::map<std::string, std::string>& per_worker_credential_types,
    bool run_inproc, int32_t median_latency_collection_interval_millis);

bool RunQuit(
    const std::string& credential_type,
    const std::map<std::string, std::string>& per_worker_credential_types);
}
}

#endif
