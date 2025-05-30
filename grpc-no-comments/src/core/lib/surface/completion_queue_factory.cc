
// Copyright 2017 gRPC authors.

#include "src/core/lib/surface/completion_queue_factory.h"

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "absl/log/check.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/surface/completion_queue.h"

static grpc_completion_queue* default_create(
    const grpc_completion_queue_factory* ,
    const grpc_completion_queue_attributes* attr) {
  return grpc_completion_queue_create_internal(
      attr->cq_completion_type, attr->cq_polling_type, attr->cq_shutdown_cb);
}

static grpc_completion_queue_factory_vtable default_vtable = {default_create};

static const grpc_completion_queue_factory g_default_cq_factory = {
    "Default Factory", nullptr, &default_vtable};

const grpc_completion_queue_factory* grpc_completion_queue_factory_lookup(
    const grpc_completion_queue_attributes* attributes) {
  CHECK(attributes->version >= 1 &&
        attributes->version <= GRPC_CQ_CURRENT_VERSION);

  return &g_default_cq_factory;
}

grpc_completion_queue* grpc_completion_queue_create_for_next(void* reserved) {
  grpc_core::ExecCtx exec_ctx;
  CHECK(!reserved);
  grpc_completion_queue_attributes attr = {1, GRPC_CQ_NEXT,
                                           GRPC_CQ_DEFAULT_POLLING, nullptr};
  return g_default_cq_factory.vtable->create(&g_default_cq_factory, &attr);
}

grpc_completion_queue* grpc_completion_queue_create_for_pluck(void* reserved) {
  grpc_core::ExecCtx exec_ctx;
  CHECK(!reserved);
  grpc_completion_queue_attributes attr = {1, GRPC_CQ_PLUCK,
                                           GRPC_CQ_DEFAULT_POLLING, nullptr};
  return g_default_cq_factory.vtable->create(&g_default_cq_factory, &attr);
}

grpc_completion_queue* grpc_completion_queue_create_for_callback(
    grpc_completion_queue_functor* shutdown_callback, void* reserved) {
  grpc_core::ExecCtx exec_ctx;
  CHECK(!reserved);
  grpc_completion_queue_attributes attr = {
      2, GRPC_CQ_CALLBACK, GRPC_CQ_DEFAULT_POLLING, shutdown_callback};
  return g_default_cq_factory.vtable->create(&g_default_cq_factory, &attr);
}

grpc_completion_queue* grpc_completion_queue_create(
    const grpc_completion_queue_factory* factory,
    const grpc_completion_queue_attributes* attr, void* reserved) {
  grpc_core::ExecCtx exec_ctx;
  CHECK(!reserved);
  return factory->vtable->create(factory, attr);
}
