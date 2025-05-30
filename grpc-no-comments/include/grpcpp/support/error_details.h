
// Copyright 2017 gRPC authors.

#ifndef GRPCPP_SUPPORT_ERROR_DETAILS_H
#define GRPCPP_SUPPORT_ERROR_DETAILS_H

#include <grpcpp/support/status.h>

namespace grpc {

template <typename T>
grpc::Status ExtractErrorDetails(const grpc::Status& from, T* to) {
  if (to == nullptr) {
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "");
  }
  if (!to->ParseFromString(from.error_details())) {
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "");
  }
  return grpc::Status::OK;
}
inline grpc::Status ExtractErrorDetails(const grpc::Status&, std::nullptr_t) {
  return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "");
}

template <typename T>
grpc::Status SetErrorDetails(const T& from, grpc::Status* to) {
  if (to == nullptr) {
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "");
  }
  grpc::StatusCode code = grpc::StatusCode::UNKNOWN;
  if (from.code() >= grpc::StatusCode::OK &&
      from.code() <= grpc::StatusCode::UNAUTHENTICATED) {
    code = static_cast<grpc::StatusCode>(from.code());
  }
  *to = grpc::Status(code, from.message(), from.SerializeAsString());
  return grpc::Status::OK;
}

}

#endif
