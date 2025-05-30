
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_ERROR_UTILS_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_ERROR_UTILS_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "absl/status/status.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/time.h"

void grpc_error_get_status(grpc_error_handle error,
                           grpc_core::Timestamp deadline,
                           grpc_status_code* code, std::string* message,
                           grpc_core::http2::Http2ErrorCode* http_error,
                           const char** error_string);

absl::Status grpc_error_to_absl_status(grpc_error_handle error);

grpc_error_handle absl_status_to_grpc_error(absl::Status status);

bool grpc_error_has_clear_grpc_status(grpc_error_handle error);

#endif
