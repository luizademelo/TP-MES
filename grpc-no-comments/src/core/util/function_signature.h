// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_FUNCTION_SIGNATURE_H
#define GRPC_SRC_CORE_UTIL_FUNCTION_SIGNATURE_H

#include "absl/strings/string_view.h"

#if defined(_MSC_VER)
#define GRPC_FUNCTION_SIGNATURE __FUNCSIG__
#elif defined(__GNUC__)
#define GRPC_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#else
#define GRPC_FUNCTION_SIGNATURE "???()"
#endif

namespace grpc_core {

template <typename T>
static constexpr inline absl::string_view TypeName() {
#if ABSL_USES_STD_STRING_VIEW

#if defined(__clang__)
  constexpr absl::string_view kPrefix{"[T = "};
  constexpr absl::string_view kSuffix{"]"};
#elif defined(__GNUC__)
#if __GNUC__ < 9
#define GRPC_FUNCTION_SIGNATURE_TYPE_NAME_USE_FALLBACK
#endif
  constexpr absl::string_view kPrefix{"[with T = "};
  constexpr absl::string_view kSuffix{";"};
#elif defined(_MSC_VER)
  constexpr absl::string_view kPrefix{"TypeName<"};
  constexpr absl::string_view kSuffix{">(void)"};
#else
#define GRPC_FUNCTION_SIGNATURE_TYPE_NAME_USE_FALLBACK
#endif
#else
#define GRPC_FUNCTION_SIGNATURE_TYPE_NAME_USE_FALLBACK
#endif

#ifdef GRPC_FUNCTION_SIGNATURE_TYPE_NAME_USE_FALLBACK
  return "unknown";
#else
  constexpr absl::string_view kFunction{GRPC_FUNCTION_SIGNATURE};
  constexpr size_t kStart = kFunction.find(kPrefix) + kPrefix.size();
  constexpr size_t kEnd = kFunction.rfind(kSuffix);
  static_assert(kStart < kEnd);
  return kFunction.substr(kStart, (kEnd - kStart));
#endif
}

}

#endif
