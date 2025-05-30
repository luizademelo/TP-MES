
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_H
#define GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"

typedef struct grpc_endpoint grpc_endpoint;
typedef struct grpc_endpoint_vtable grpc_endpoint_vtable;

struct grpc_endpoint_vtable {
  void (*read)(grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
               bool urgent, int min_progress_size);
  void (*write)(
      grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
      grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args);
  void (*add_to_pollset)(grpc_endpoint* ep, grpc_pollset* pollset);
  void (*add_to_pollset_set)(grpc_endpoint* ep, grpc_pollset_set* pollset);
  void (*delete_from_pollset_set)(grpc_endpoint* ep, grpc_pollset_set* pollset);
  void (*destroy)(grpc_endpoint* ep);
  absl::string_view (*get_peer)(grpc_endpoint* ep);
  absl::string_view (*get_local_address)(grpc_endpoint* ep);
  int (*get_fd)(grpc_endpoint* ep);
  bool (*can_track_err)(grpc_endpoint* ep);
};

void grpc_endpoint_read(grpc_endpoint* ep, grpc_slice_buffer* slices,
                        grpc_closure* cb, bool urgent, int min_progress_size);

absl::string_view grpc_endpoint_get_peer(grpc_endpoint* ep);

absl::string_view grpc_endpoint_get_local_address(grpc_endpoint* ep);

int grpc_endpoint_get_fd(grpc_endpoint* ep);

void grpc_endpoint_write(
    grpc_endpoint* ep, grpc_slice_buffer* slices, grpc_closure* cb,
    grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs arg);

void grpc_endpoint_destroy(grpc_endpoint* ep);

void grpc_endpoint_add_to_pollset(grpc_endpoint* ep, grpc_pollset* pollset);
void grpc_endpoint_add_to_pollset_set(grpc_endpoint* ep,
                                      grpc_pollset_set* pollset_set);

void grpc_endpoint_delete_from_pollset_set(grpc_endpoint* ep,
                                           grpc_pollset_set* pollset_set);

bool grpc_endpoint_can_track_err(grpc_endpoint* ep);

struct grpc_endpoint {
  const grpc_endpoint_vtable* vtable;

  void Orphan() { grpc_endpoint_destroy(this); }
};

#endif
