// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_STATUS_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_STATUS_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc_core {
namespace promise_detail {

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::Status IntoStatus(
    absl::StatusOr<T>* status) {
  return std::move(status->status());
}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline absl::Status IntoStatus(
    absl::Status* status) {
  return std::move(*status);
}

}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool IsStatusOk(
    const absl::Status& status) {
  return status.ok();
}

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool IsStatusOk(
    const absl::StatusOr<T>& status) {
  return status.ok();
}

template <typename To, typename From, typename SfinaeVoid = void>
struct StatusCastImpl;

template <typename To>
struct StatusCastImpl<To, To> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static To Cast(To&& t) {
    return std::move(t);
  }
};

template <typename To>
struct StatusCastImpl<To, const To&> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static To Cast(const To& t) { return t; }
};

template <typename T>
struct StatusCastImpl<absl::Status, absl::StatusOr<T>> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static absl::Status Cast(
      absl::StatusOr<T>&& t) {
    return std::move(t.status());
  }
};

template <typename T>
struct StatusCastImpl<absl::Status, absl::StatusOr<T>&> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static absl::Status Cast(
      const absl::StatusOr<T>& t) {
    return t.status();
  }
};

template <typename T>
struct StatusCastImpl<absl::Status, const absl::StatusOr<T>&> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static absl::Status Cast(
      const absl::StatusOr<T>& t) {
    return t.status();
  }
};

template <typename To, typename From>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline To StatusCast(From&& from) {
  return StatusCastImpl<To, From>::Cast(std::forward<From>(from));
}

template <typename To, typename From, typename SfinaeVoid = void>
struct FailureStatusCastImpl : public StatusCastImpl<To, From> {};

template <typename T>
struct FailureStatusCastImpl<absl::StatusOr<T>, absl::Status> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static absl::StatusOr<T> Cast(
      absl::Status&& t) {
    return std::move(t);
  }
};

template <typename T>
struct FailureStatusCastImpl<absl::StatusOr<T>, const absl::Status&> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static absl::StatusOr<T> Cast(
      const absl::Status& t) {
    return t;
  }
};

template <typename To, typename From>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline To FailureStatusCast(From&& from) {
  DCHECK(!IsStatusOk(from));
  return FailureStatusCastImpl<To, From>::Cast(std::forward<From>(from));
}

}

#endif
