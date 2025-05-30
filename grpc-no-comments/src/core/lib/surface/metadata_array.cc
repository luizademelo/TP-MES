
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "src/core/lib/debug/trace.h"

void grpc_metadata_array_init(grpc_metadata_array* array) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_metadata_array_init(array=" << array << ")";
  memset(array, 0, sizeof(*array));
}

void grpc_metadata_array_destroy(grpc_metadata_array* array) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_metadata_array_destroy(array=" << array << ")";
  gpr_free(array->metadata);
}
