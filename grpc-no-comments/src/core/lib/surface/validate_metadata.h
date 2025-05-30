
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_VALIDATE_METADATA_H
#define GRPC_SRC_CORE_LIB_SURFACE_VALIDATE_METADATA_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <cstring>

#include "absl/log/check.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/error.h"

namespace grpc_core {

enum class ValidateMetadataResult : uint8_t {
  kOk,
  kCannotBeZeroLength,
  kTooLong,
  kIllegalHeaderKey,
  kIllegalHeaderValue
};

const char* ValidateMetadataResultToString(ValidateMetadataResult result);

ValidateMetadataResult ValidateHeaderKeyIsLegal(absl::string_view key);

}

grpc_error_handle grpc_validate_header_key_is_legal(const grpc_slice& slice);
grpc_error_handle grpc_validate_header_nonbin_value_is_legal(
    const grpc_slice& slice);

int grpc_is_binary_header_internal(const grpc_slice& slice);
inline int grpc_key_is_binary_header(const uint8_t* buf, size_t length) {
  if (length < 5) return 0;
  return 0 == memcmp(buf + length - 4, "-bin", 4);
}
inline int grpc_is_refcounted_slice_binary_header(const grpc_slice& slice) {
  DCHECK_NE(slice.refcount, nullptr);
  return grpc_key_is_binary_header(slice.data.refcounted.bytes,
                                   slice.data.refcounted.length);
}

#endif
