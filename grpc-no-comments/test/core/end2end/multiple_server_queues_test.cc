
// Copyright 2015 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/time.h>

#include "test/core/test_util/test_config.h"

int main(int argc, char** argv) {
  grpc_completion_queue* cq1;
  grpc_completion_queue* cq2;
  grpc_completion_queue* cq3;
  grpc_completion_queue_attributes attr;

  grpc_server* server;

  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();

  attr.version = 1;
  attr.cq_completion_type = GRPC_CQ_NEXT;
  attr.cq_polling_type = GRPC_CQ_DEFAULT_POLLING;
  attr.cq_shutdown_cb = nullptr;
  cq1 = grpc_completion_queue_create(
      grpc_completion_queue_factory_lookup(&attr), &attr, nullptr);

  attr.cq_polling_type = GRPC_CQ_NON_LISTENING;
  cq2 = grpc_completion_queue_create(
      grpc_completion_queue_factory_lookup(&attr), &attr, nullptr);

  attr.cq_polling_type = GRPC_CQ_NON_POLLING;
  cq3 = grpc_completion_queue_create(
      grpc_completion_queue_factory_lookup(&attr), &attr, nullptr);

  server = grpc_server_create(nullptr, nullptr);
  grpc_server_register_completion_queue(server, cq1, nullptr);
  grpc_server_credentials* server_creds =
      grpc_insecure_server_credentials_create();
  grpc_server_add_http2_port(server, "[::]:0", server_creds);
  grpc_server_credentials_release(server_creds);
  grpc_server_register_completion_queue(server, cq2, nullptr);
  grpc_server_register_completion_queue(server, cq3, nullptr);

  grpc_server_start(server);
  grpc_server_shutdown_and_notify(server, cq2, nullptr);
  grpc_completion_queue_next(cq2, gpr_inf_future(GPR_CLOCK_REALTIME),
                             nullptr);
  grpc_completion_queue_shutdown(cq1);
  grpc_completion_queue_shutdown(cq2);
  grpc_completion_queue_shutdown(cq3);

  grpc_completion_queue_next(cq1, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  grpc_completion_queue_next(cq2, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
  grpc_completion_queue_next(cq3, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);

  grpc_server_destroy(server);
  grpc_completion_queue_destroy(cq1);
  grpc_completion_queue_destroy(cq2);
  grpc_completion_queue_destroy(cq3);
  grpc_shutdown();
  return 0;
}
