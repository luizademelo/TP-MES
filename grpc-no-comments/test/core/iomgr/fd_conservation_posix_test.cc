
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <sys/resource.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/endpoint_pair.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  int i;
  struct rlimit rlim;
  grpc_endpoint_pair p;

  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  {
    grpc_core::ExecCtx exec_ctx;

    rlim.rlim_cur = rlim.rlim_max = 1000;
    CHECK_EQ(setrlimit(RLIMIT_NOFILE, &rlim), 0);
    for (i = 0; i < 10000; i++) {
      p = grpc_iomgr_create_endpoint_pair("test", nullptr);
      grpc_endpoint_destroy(p.client);
      grpc_endpoint_destroy(p.server);
      grpc_core::ExecCtx::Get()->Flush();
    }
  }

  grpc_shutdown();
  return 0;
}
