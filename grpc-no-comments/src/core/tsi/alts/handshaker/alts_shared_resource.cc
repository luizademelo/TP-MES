
// Copyright 2018 gRPC authors.

#include "src/core/tsi/alts/handshaker/alts_shared_resource.h"

#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"
#include "src/core/util/crash.h"

static alts_shared_resource_dedicated g_alts_resource_dedicated;

alts_shared_resource_dedicated* grpc_alts_get_shared_resource_dedicated(void) {
  return &g_alts_resource_dedicated;
}

static void thread_worker(void* ) {
  while (true) {
    grpc_event event =
        grpc_completion_queue_next(g_alts_resource_dedicated.cq,
                                   gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
    CHECK(event.type != GRPC_QUEUE_TIMEOUT);
    if (event.type == GRPC_QUEUE_SHUTDOWN) {
      break;
    }
    CHECK(event.type == GRPC_OP_COMPLETE);
    alts_handshaker_client* client =
        static_cast<alts_handshaker_client*>(event.tag);
    alts_handshaker_client_handle_response(client, event.success);
  }
}

void grpc_alts_shared_resource_dedicated_init() {
  g_alts_resource_dedicated.cq = nullptr;
  gpr_mu_init(&g_alts_resource_dedicated.mu);
}

void grpc_alts_shared_resource_dedicated_start(
    const char* handshaker_service_url) {
  gpr_mu_lock(&g_alts_resource_dedicated.mu);
  if (g_alts_resource_dedicated.cq == nullptr) {
    grpc_channel_credentials* creds = grpc_insecure_credentials_create();

    grpc_arg disable_retries_arg = grpc_channel_arg_integer_create(
        const_cast<char*>(GRPC_ARG_ENABLE_RETRIES), 0);
    grpc_channel_args args = {1, &disable_retries_arg};
    g_alts_resource_dedicated.channel =
        grpc_channel_create(handshaker_service_url, creds, &args);
    grpc_channel_credentials_release(creds);
    g_alts_resource_dedicated.cq =
        grpc_completion_queue_create_for_next(nullptr);
    g_alts_resource_dedicated.thread =
        grpc_core::Thread("alts_tsi_handshaker", &thread_worker, nullptr);
    g_alts_resource_dedicated.interested_parties = grpc_pollset_set_create();
    grpc_pollset_set_add_pollset(g_alts_resource_dedicated.interested_parties,
                                 grpc_cq_pollset(g_alts_resource_dedicated.cq));
    g_alts_resource_dedicated.thread.Start();
  }
  gpr_mu_unlock(&g_alts_resource_dedicated.mu);
}

void grpc_alts_shared_resource_dedicated_shutdown() {
  if (g_alts_resource_dedicated.cq != nullptr) {
    grpc_pollset_set_del_pollset(g_alts_resource_dedicated.interested_parties,
                                 grpc_cq_pollset(g_alts_resource_dedicated.cq));
    grpc_completion_queue_shutdown(g_alts_resource_dedicated.cq);
    g_alts_resource_dedicated.thread.Join();
    grpc_pollset_set_destroy(g_alts_resource_dedicated.interested_parties);
    grpc_completion_queue_destroy(g_alts_resource_dedicated.cq);
    grpc_channel_destroy(g_alts_resource_dedicated.channel);
  }
  gpr_mu_destroy(&g_alts_resource_dedicated.mu);
}
