Here's the commented version of the code:

```c++
// Copyright 2017 gRPC authors.

#ifndef GRPCPP_SUPPORT_ERROR_DETAILS_H
#define GRPCPP_SUPPORT_ERROR_DETAILS_H

#include <grpcpp/support/status.h>

namespace grpc {

/// @brief Extracts error details from a gRPC Status object into a protocol buffer message.
/// @tparam T The type of the protocol buffer message to extract into.
/// @param from The source Status object containing error details.
/// @param to Pointer to the destination protocol buffer message.
/// @return Returns OK on success, or error status if:
///         - to is nullptr (FAILED_PRECONDITION)
///         - parsing fails (INVALID_ARGUMENT)
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

/// @brief Overload for nullptr case - always returns error.
/// @param from Unused Status object.
/// @return Always returns FAILED_PRECONDITION status.
inline grpc::Status ExtractErrorDetails(const grpc::Status&, std::nullptr_t) {
  return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "");
}

/// @brief Sets error details in a gRPC Status object from a protocol buffer message.
/// @tparam T The type of the protocol buffer message containing error details.
/// @param from The source protocol buffer message.
/// @param to Pointer to the destination Status object to be modified.
/// @return Returns OK on success, or FAILED_PRECONDITION if to is nullptr.
/// @note The status code will be set to UNKNOWN if the protocol buffer's code is invalid.
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
```

Key improvements in the comments:
1. Added detailed documentation for each function including:
   - Brief description of purpose
   - Template parameters
   - Function parameters
   - Return values and error conditions
   - Important notes about behavior
2. Used consistent documentation style with @brief, @tparam, @param, @return tags
3. Explained the special case handling for nullptr
4. Documented the range checking behavior for status codes in SetErrorDetails
5. Added note about default UNKNOWN status code behavior

The comments now provide comprehensive documentation that would help future developers understand and maintain this code.