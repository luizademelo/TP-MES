
// Copyright 2019 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/time.h>

#include <vector>

#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iocp_windows.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_windows.h"
#include "src/core/lib/surface/init.h"
#include "src/core/util/thd.h"
#include "test/core/test_util/test_config.h"

#if defined(GRPC_WINSOCK_SOCKET)

const size_t THREADS = 3;

struct ThreadParams {
  gpr_cv cv;
  gpr_mu mu;
  int complete;
  int queuing;
  gpr_mu* pollset_mu[THREADS];
};

int main(int argc, char** argv) {
  grpc_init();

  ThreadParams params = {};
  gpr_cv_init(&params.cv);
  gpr_mu_init(&params.mu);
  std::vector<grpc_core::Thread> threads;
  for (int i = 0; i < THREADS; i++) {
    grpc_core::Thread thd(
        "Poller",
        [](void* params) {
          ThreadParams* tparams = static_cast<ThreadParams*>(params);
          grpc_core::ExecCtx exec_ctx;

          gpr_mu* mu;
          grpc_pollset pollset = {};
          grpc_pollset_init(&pollset, &mu);

          gpr_mu_lock(mu);

          gpr_mu_lock(&tparams->mu);
          tparams->pollset_mu[tparams->queuing] = mu;
          tparams->queuing++;
          gpr_cv_signal(&tparams->cv);
          gpr_mu_unlock(&tparams->mu);

          grpc_error_handle error;
          error = grpc_pollset_work(&pollset, NULL,
                                    grpc_core::Timestamp::InfFuture());
          error = grpc_pollset_kick(&pollset, NULL);

          gpr_mu_unlock(mu);

          gpr_mu_lock(&tparams->mu);
          tparams->complete++;
          gpr_cv_signal(&tparams->cv);
          gpr_mu_unlock(&tparams->mu);
        },
        &params);
    thd.Start();
    threads.push_back(std::move(thd));
  }

  gpr_mu_lock(&params.mu);
  while (
      params.queuing != THREADS &&
      !gpr_cv_wait(&params.cv, &params.mu, gpr_inf_future(GPR_CLOCK_REALTIME)));
  gpr_mu_unlock(&params.mu);

  for (int i = 0; i < THREADS; i++) {
    gpr_mu_lock(params.pollset_mu[i]);
    gpr_mu_unlock(params.pollset_mu[i]);
  }

  grpc_iocp_kick();

  gpr_mu_lock(&params.mu);
  while (
      params.complete != THREADS &&
      !gpr_cv_wait(&params.cv, &params.mu, gpr_inf_future(GPR_CLOCK_REALTIME)));
  gpr_mu_unlock(&params.mu);

  for (auto& t : threads) t.Join();
  return EXIT_SUCCESS;
}
#else
int main(int , char** ) { return 0; }
#endif
