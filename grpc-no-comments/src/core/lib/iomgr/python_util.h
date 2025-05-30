
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_PYTHON_UTIL_H
#define GRPC_SRC_CORE_LIB_IOMGR_PYTHON_UTIL_H

#include <grpc/slice.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/error.h"

inline grpc_error_handle grpc_socket_error(char* error) {
  return grpc_error_set_int(GRPC_ERROR_CREATE(error),
                            grpc_core::StatusIntProperty::kRpcStatus,
                            GRPC_STATUS_UNAVAILABLE);
}

inline char* grpc_slice_buffer_start(grpc_slice_buffer* buffer, int i) {
  return reinterpret_cast<char*>(GRPC_SLICE_START_PTR(buffer->slices[i]));
}

inline int grpc_slice_buffer_length(grpc_slice_buffer* buffer, int i) {
  return GRPC_SLICE_LENGTH(buffer->slices[i]);
}

#endif
