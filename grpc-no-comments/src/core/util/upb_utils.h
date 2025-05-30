
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_UPB_UTILS_H
#define GRPC_SRC_CORE_UTIL_UPB_UTILS_H

#include <string>

#include "absl/strings/string_view.h"
#include "upb/base/string_view.h"

namespace grpc_core {

template <typename T>
inline upb_StringView StdStringToUpbString(const T& str) {
  return upb_StringView_FromDataAndSize(str.data(), str.size());
}

inline absl::string_view UpbStringToAbsl(const upb_StringView& str) {
  return absl::string_view(str.data, str.size);
}

inline std::string UpbStringToStdString(const upb_StringView& str) {
  return std::string(str.data, str.size);
}

}

#endif
