
// Copyright 2015 gRPC authors.

#include "src/core/lib/transport/status_conversion.h"

#include <grpc/support/port_platform.h>

using grpc_core::http2::AbslStatusCodeToErrorCode;
using grpc_core::http2::Http2ErrorCode;

Http2ErrorCode grpc_status_to_http2_error(grpc_status_code status) {
  return AbslStatusCodeToErrorCode(static_cast<absl::StatusCode>(status));
}

grpc_status_code grpc_http2_error_to_grpc_status(
    Http2ErrorCode error, grpc_core::Timestamp deadline) {
  if (error == Http2ErrorCode::kNoError) {

    return GRPC_STATUS_INTERNAL;
  }
  return static_cast<grpc_status_code>(
      ErrorCodeToAbslStatusCode(error, deadline));
}

grpc_status_code grpc_http2_status_to_grpc_status(int status) {
  switch (status) {

    case 200:
      return GRPC_STATUS_OK;
    case 400:
      return GRPC_STATUS_INTERNAL;
    case 401:
      return GRPC_STATUS_UNAUTHENTICATED;
    case 403:
      return GRPC_STATUS_PERMISSION_DENIED;
    case 404:
      return GRPC_STATUS_UNIMPLEMENTED;
    case 429:
      return GRPC_STATUS_UNAVAILABLE;
    case 502:
      return GRPC_STATUS_UNAVAILABLE;
    case 503:
      return GRPC_STATUS_UNAVAILABLE;
    case 504:
      return GRPC_STATUS_UNAVAILABLE;

    default:
      return GRPC_STATUS_UNKNOWN;
  }
}

int grpc_status_to_http2_status(grpc_status_code ) { return 200; }
