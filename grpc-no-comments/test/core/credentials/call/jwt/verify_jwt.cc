
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <stdio.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/credentials/call/jwt/jwt_verifier.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/util/crash.h"
#include "src/core/util/json/json_writer.h"
#include "test/core/test_util/cmdline.h"

typedef struct {
  grpc_pollset* pollset;
  gpr_mu* mu;
  int is_done;
  int success;
} synchronizer;

static void print_usage_and_exit(gpr_cmdline* cl, const char* argv0) {
  std::string usage = gpr_cmdline_usage_string(cl, argv0);
  fprintf(stderr, "%s", usage.c_str());
  fflush(stderr);
  gpr_cmdline_destroy(cl);
  exit(1);
}

static void on_jwt_verification_done(void* user_data,
                                     grpc_jwt_verifier_status status,
                                     grpc_jwt_claims* claims) {
  synchronizer* sync = static_cast<synchronizer*>(user_data);

  sync->success = (status == GRPC_JWT_VERIFIER_OK);
  if (sync->success) {
    CHECK_NE(claims, nullptr);
    std::string claims_str =
        grpc_core::JsonDump(*grpc_jwt_claims_json(claims), 2);
    printf("Claims: \n\n%s\n", claims_str.c_str());
    grpc_jwt_claims_destroy(claims);
  } else {
    CHECK_EQ(claims, nullptr);
    fprintf(stderr, "Verification failed with error %s\n",
            grpc_jwt_verifier_status_to_string(status));
    fflush(stderr);
  }

  gpr_mu_lock(sync->mu);
  sync->is_done = 1;
  GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(sync->pollset, nullptr));
  gpr_mu_unlock(sync->mu);
}

int main(int argc, char** argv) {
  synchronizer sync;
  grpc_jwt_verifier* verifier;
  gpr_cmdline* cl;
  const char* jwt = nullptr;
  const char* aud = nullptr;
  grpc_core::ExecCtx exec_ctx;

  grpc_init();
  cl = gpr_cmdline_create("JWT verifier tool");
  gpr_cmdline_add_string(cl, "jwt", "JSON web token to verify", &jwt);
  gpr_cmdline_add_string(cl, "aud", "Audience for the JWT", &aud);
  gpr_cmdline_parse(cl, argc, argv);
  if (jwt == nullptr || aud == nullptr) {
    print_usage_and_exit(cl, argv[0]);
  }

  verifier = grpc_jwt_verifier_create(nullptr, 0);

  grpc_init();

  sync.pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(sync.pollset, &sync.mu);
  sync.is_done = 0;

  grpc_jwt_verifier_verify(verifier, sync.pollset, jwt, aud,
                           on_jwt_verification_done, &sync);

  gpr_mu_lock(sync.mu);
  while (!sync.is_done) {
    grpc_pollset_worker* worker = nullptr;
    if (!GRPC_LOG_IF_ERROR(
            "pollset_work",
            grpc_pollset_work(sync.pollset, &worker,
                              grpc_core::Timestamp::InfFuture()))) {
      sync.is_done = true;
    }
    gpr_mu_unlock(sync.mu);
    grpc_core::ExecCtx::Get()->Flush();
    gpr_mu_lock(sync.mu);
  }
  gpr_mu_unlock(sync.mu);

  gpr_free(sync.pollset);

  grpc_jwt_verifier_destroy(verifier);

  gpr_cmdline_destroy(cl);
  grpc_shutdown();
  return !sync.success;
}
