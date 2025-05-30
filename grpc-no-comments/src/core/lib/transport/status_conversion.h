
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_STATUS_CONVERSION_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_STATUS_CONVERSION_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/util/time.h"

grpc_core::http2::Http2ErrorCode grpc_status_to_http2_error(
    grpc_status_code status);
grpc_status_code grpc_http2_error_to_grpc_status(
    grpc_core::http2::Http2ErrorCode error, grpc_core::Timestamp deadline);

grpc_status_code grpc_http2_status_to_grpc_status(int status);
int grpc_status_to_http2_status(grpc_status_code status);

#endif
