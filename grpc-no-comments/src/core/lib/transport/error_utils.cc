
// Copyright 2016 gRPC authors.

#include "src/core/lib/transport/error_utils.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <stdint.h>

#include <vector>

#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/transport/status_conversion.h"
#include "src/core/util/status_helper.h"

using grpc_core::http2::Http2ErrorCode;

static grpc_error_handle recursively_find_error_with_field(
    grpc_error_handle error, grpc_core::StatusIntProperty which) {
  intptr_t unused;

  if (grpc_error_get_int(error, which, &unused)) {
    return error;
  }
  std::vector<absl::Status> children = grpc_core::StatusGetChildren(error);
  for (const absl::Status& child : children) {
    grpc_error_handle result = recursively_find_error_with_field(child, which);
    if (!result.ok()) return result;
  }
  return absl::OkStatus();
}

namespace {

std::optional<Http2ErrorCode> GetHttp2Error(const absl::Status& status) {
  auto http_error_code = grpc_core::StatusGetInt(
      status, grpc_core::StatusIntProperty::kHttp2Error);
  if (http_error_code.has_value()) {
    return static_cast<Http2ErrorCode>(*http_error_code);
  }
  return std::nullopt;
}

}

void grpc_error_get_status(grpc_error_handle error,
                           grpc_core::Timestamp deadline,
                           grpc_status_code* code, std::string* message,
                           Http2ErrorCode* http_error,
                           const char** error_string) {
  if (grpc_core::IsErrorFlattenEnabled()) {
    auto http_error_code = GetHttp2Error(error);
    if (code != nullptr) {

      if (error.code() == absl::StatusCode::kUnknown &&
          http_error_code.has_value()) {
        *code = grpc_http2_error_to_grpc_status(*http_error_code, deadline);
      } else {
        *code = static_cast<grpc_status_code>(error.code());
      }
    }
    if (message != nullptr) *message = std::string(error.message());
    if (error_string != nullptr && !error.ok()) {
      *error_string = gpr_strdup(grpc_core::StatusToString(error).c_str());
    }
    if (http_error != nullptr) {

      if (http_error_code.has_value()) {
        *http_error = *http_error_code;
      } else if (error.code() != absl::StatusCode::kUnknown) {
        *http_error = grpc_status_to_http2_error(
            static_cast<grpc_status_code>(error.code()));
      } else {
        *http_error = error.ok() ? Http2ErrorCode::kNoError
                                 : Http2ErrorCode::kInternalError;
      }
    }
    return;
  }

  if (GPR_LIKELY(error.ok())) {
    if (code != nullptr) *code = GRPC_STATUS_OK;
    if (message != nullptr) {

      *message = "";
    }
    if (http_error != nullptr) {
      *http_error = Http2ErrorCode::kNoError;
    }
    return;
  }

  grpc_error_handle found_error = recursively_find_error_with_field(
      error, grpc_core::StatusIntProperty::kRpcStatus);
  if (found_error.ok()) {

    found_error = recursively_find_error_with_field(
        error, grpc_core::StatusIntProperty::kHttp2Error);
  }

  if (found_error.ok()) found_error = error;

  grpc_status_code status = GRPC_STATUS_UNKNOWN;
  intptr_t integer;
  if (grpc_error_get_int(found_error, grpc_core::StatusIntProperty::kRpcStatus,
                         &integer)) {
    status = static_cast<grpc_status_code>(integer);
  } else if (grpc_error_get_int(found_error,
                                grpc_core::StatusIntProperty::kHttp2Error,
                                &integer)) {
    status = grpc_http2_error_to_grpc_status(
        static_cast<Http2ErrorCode>(integer), deadline);
  } else {
    status = static_cast<grpc_status_code>(found_error.code());
  }
  if (code != nullptr) *code = status;

  if (error_string != nullptr && status != GRPC_STATUS_OK) {
    *error_string = gpr_strdup(grpc_core::StatusToString(error).c_str());
  }

  if (http_error != nullptr) {
    if (grpc_error_get_int(
            found_error, grpc_core::StatusIntProperty::kHttp2Error, &integer)) {
      *http_error = static_cast<Http2ErrorCode>(integer);
    } else if (grpc_error_get_int(found_error,
                                  grpc_core::StatusIntProperty::kRpcStatus,
                                  &integer)) {
      *http_error =
          grpc_status_to_http2_error(static_cast<grpc_status_code>(integer));
    } else {
      *http_error = found_error.ok() ? Http2ErrorCode::kNoError
                                     : Http2ErrorCode::kInternalError;
    }
  }

  if (message != nullptr) {
    if (!grpc_error_get_str(
            found_error, grpc_core::StatusStrProperty::kGrpcMessage, message)) {
      *message = found_error.message().empty()
                     ? grpc_core::StatusToString(error)
                     : std::string(found_error.message());
    }
  }
}

absl::Status grpc_error_to_absl_status(grpc_error_handle error) {
  if (grpc_core::IsErrorFlattenEnabled()) return error;
  grpc_status_code status;

  std::string message;
  grpc_error_get_status(error, grpc_core::Timestamp::InfFuture(), &status,
                        &message, nullptr ,
                        nullptr );
  return absl::Status(static_cast<absl::StatusCode>(status), message);
}

grpc_error_handle absl_status_to_grpc_error(absl::Status status) {
  if (grpc_core::IsErrorFlattenEnabled()) return status;

  if (status.ok()) {
    return absl::OkStatus();
  }
  return grpc_error_set_int(GRPC_ERROR_CREATE(status.message()),
                            grpc_core::StatusIntProperty::kRpcStatus,
                            static_cast<grpc_status_code>(status.code()));
}

bool grpc_error_has_clear_grpc_status(grpc_error_handle error) {
  if (grpc_core::IsErrorFlattenEnabled()) {
    return error.code() != absl::StatusCode::kUnknown;
  }
  intptr_t unused;
  if (grpc_error_get_int(error, grpc_core::StatusIntProperty::kRpcStatus,
                         &unused)) {
    return true;
  }
  std::vector<absl::Status> children = grpc_core::StatusGetChildren(error);
  for (const absl::Status& child : children) {
    if (grpc_error_has_clear_grpc_status(child)) {
      return true;
    }
  }
  return false;
}
