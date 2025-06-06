
// Copyright 2016 gRPC authors.

#include <grpcpp/ext/gcp_observability.h>
#include <signal.h>

#include "absl/flags/flag.h"
#include "absl/log/log.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/server_helper.h"
#include "test/cpp/util/test_config.h"

gpr_atm grpc::testing::interop::g_got_sigint;

ABSL_FLAG(bool, enable_observability, false,
          "Whether to enable GCP Observability");

static void sigint_handler(int ) {
  gpr_atm_no_barrier_store(&grpc::testing::interop::g_got_sigint, true);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  signal(SIGINT, sigint_handler);

  if (absl::GetFlag(FLAGS_enable_observability)) {

    auto status = grpc::experimental::GcpObservabilityInit();
    VLOG(2) << "GcpObservabilityInit() status_code: " << status.code();
    if (!status.ok()) {
      return 1;
    }
  }

  grpc::testing::interop::RunServer(
      grpc::testing::CreateInteropServerCredentials());

  return 0;
}
