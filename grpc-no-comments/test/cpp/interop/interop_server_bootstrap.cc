
// Copyright 2016 gRPC authors.

#include <signal.h>

#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/server_helper.h"
#include "test/cpp/util/test_config.h"

gpr_atm grpc::testing::interop::g_got_sigint;

static void sigint_handler(int ) {
  gpr_atm_no_barrier_store(&grpc::testing::interop::g_got_sigint, true);
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);
  signal(SIGINT, sigint_handler);

  grpc::testing::interop::RunServer(
      grpc::testing::CreateInteropServerCredentials());

  return 0;
}
