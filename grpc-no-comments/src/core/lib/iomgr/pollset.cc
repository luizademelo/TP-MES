
// Copyright 2018 gRPC authors.

#include "src/core/lib/iomgr/pollset.h"

#include <grpc/support/port_platform.h>

grpc_pollset_vtable* grpc_pollset_impl;

void grpc_set_pollset_vtable(grpc_pollset_vtable* vtable) {
  grpc_pollset_impl = vtable;
}

void grpc_pollset_global_init() { grpc_pollset_impl->global_init(); }

void grpc_pollset_global_shutdown() { grpc_pollset_impl->global_shutdown(); }

void grpc_pollset_init(grpc_pollset* pollset, gpr_mu** mu) {
  grpc_pollset_impl->init(pollset, mu);
}

void grpc_pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  grpc_pollset_impl->shutdown(pollset, closure);
}

void grpc_pollset_destroy(grpc_pollset* pollset) {
  grpc_pollset_impl->destroy(pollset);
}

grpc_error_handle grpc_pollset_work(grpc_pollset* pollset,
                                    grpc_pollset_worker** worker,
                                    grpc_core::Timestamp deadline) {
  return grpc_pollset_impl->work(pollset, worker, deadline);
}

grpc_error_handle grpc_pollset_kick(grpc_pollset* pollset,
                                    grpc_pollset_worker* specific_worker) {
  return grpc_pollset_impl->kick(pollset, specific_worker);
}

size_t grpc_pollset_size(void) { return grpc_pollset_impl->pollset_size(); }
