
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/endpoint.h"

#include <grpc/support/port_platform.h>

void grpc_endpoint_read(grpc_endpoint* ep, grpc_slice_buffer* slices,
                        grpc_closure* cb, bool urgent, int min_progress_size) {
  ep->vtable->read(ep, slices, cb, urgent, min_progress_size);
}

void grpc_endpoint_write(
    grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
    grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args) {
  ep->vtable->write(ep, slices, cb, std::move(args));
}

void grpc_endpoint_add_to_pollset(grpc_endpoint* ep, grpc_pollset* pollset) {
  ep->vtable->add_to_pollset(ep, pollset);
}

void grpc_endpoint_add_to_pollset_set(grpc_endpoint* ep,
                                      grpc_pollset_set* pollset_set) {
  ep->vtable->add_to_pollset_set(ep, pollset_set);
}

void grpc_endpoint_delete_from_pollset_set(grpc_endpoint* ep,
                                           grpc_pollset_set* pollset_set) {
  ep->vtable->delete_from_pollset_set(ep, pollset_set);
}

void grpc_endpoint_destroy(grpc_endpoint* ep) { ep->vtable->destroy(ep); }

absl::string_view grpc_endpoint_get_peer(grpc_endpoint* ep) {
  return ep->vtable->get_peer(ep);
}

absl::string_view grpc_endpoint_get_local_address(grpc_endpoint* ep) {
  return ep->vtable->get_local_address(ep);
}

int grpc_endpoint_get_fd(grpc_endpoint* ep) { return ep->vtable->get_fd(ep); }

bool grpc_endpoint_can_track_err(grpc_endpoint* ep) {
  return ep->vtable->can_track_err(ep);
}
