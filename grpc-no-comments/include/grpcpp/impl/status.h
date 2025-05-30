
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_STATUS_H
#define GRPCPP_IMPL_STATUS_H

#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status_code_enum.h>

namespace grpc {

class GRPC_MUST_USE_RESULT_WHEN_USE_STRICT_WARNING GRPCXX_DLL Status {
 public:

  Status() : code_(StatusCode::OK) {

    static_assert(StatusCode::OK == static_cast<StatusCode>(GRPC_STATUS_OK),
                  "Mismatched status code");
    static_assert(
        StatusCode::CANCELLED == static_cast<StatusCode>(GRPC_STATUS_CANCELLED),
        "Mismatched status code");
    static_assert(
        StatusCode::UNKNOWN == static_cast<StatusCode>(GRPC_STATUS_UNKNOWN),
        "Mismatched status code");
    static_assert(StatusCode::INVALID_ARGUMENT ==
                      static_cast<StatusCode>(GRPC_STATUS_INVALID_ARGUMENT),
                  "Mismatched status code");
    static_assert(StatusCode::DEADLINE_EXCEEDED ==
                      static_cast<StatusCode>(GRPC_STATUS_DEADLINE_EXCEEDED),
                  "Mismatched status code");
    static_assert(
        StatusCode::NOT_FOUND == static_cast<StatusCode>(GRPC_STATUS_NOT_FOUND),
        "Mismatched status code");
    static_assert(StatusCode::ALREADY_EXISTS ==
                      static_cast<StatusCode>(GRPC_STATUS_ALREADY_EXISTS),
                  "Mismatched status code");
    static_assert(StatusCode::PERMISSION_DENIED ==
                      static_cast<StatusCode>(GRPC_STATUS_PERMISSION_DENIED),
                  "Mismatched status code");
    static_assert(StatusCode::UNAUTHENTICATED ==
                      static_cast<StatusCode>(GRPC_STATUS_UNAUTHENTICATED),
                  "Mismatched status code");
    static_assert(StatusCode::RESOURCE_EXHAUSTED ==
                      static_cast<StatusCode>(GRPC_STATUS_RESOURCE_EXHAUSTED),
                  "Mismatched status code");
    static_assert(StatusCode::FAILED_PRECONDITION ==
                      static_cast<StatusCode>(GRPC_STATUS_FAILED_PRECONDITION),
                  "Mismatched status code");
    static_assert(
        StatusCode::ABORTED == static_cast<StatusCode>(GRPC_STATUS_ABORTED),
        "Mismatched status code");
    static_assert(StatusCode::OUT_OF_RANGE ==
                      static_cast<StatusCode>(GRPC_STATUS_OUT_OF_RANGE),
                  "Mismatched status code");
    static_assert(StatusCode::UNIMPLEMENTED ==
                      static_cast<StatusCode>(GRPC_STATUS_UNIMPLEMENTED),
                  "Mismatched status code");
    static_assert(
        StatusCode::INTERNAL == static_cast<StatusCode>(GRPC_STATUS_INTERNAL),
        "Mismatched status code");
    static_assert(StatusCode::UNAVAILABLE ==
                      static_cast<StatusCode>(GRPC_STATUS_UNAVAILABLE),
                  "Mismatched status code");
    static_assert(
        StatusCode::DATA_LOSS == static_cast<StatusCode>(GRPC_STATUS_DATA_LOSS),
        "Mismatched status code");
  }

  Status(StatusCode code, const std::string& error_message)
      : code_(code), error_message_(error_message) {}

  Status(StatusCode code, const std::string& error_message,
         const std::string& error_details)
      : code_(code),
        error_message_(error_message),
        binary_error_details_(error_details) {}

  static const Status& OK;

  static const Status& CANCELLED;

  StatusCode error_code() const { return code_; }

  std::string error_message() const { return error_message_; }

  std::string error_details() const { return binary_error_details_; }

  bool ok() const { return code_ == StatusCode::OK; }

  void IgnoreError() const {}

 private:
  StatusCode code_;
  std::string error_message_;
  std::string binary_error_details_;
};

}

#endif
