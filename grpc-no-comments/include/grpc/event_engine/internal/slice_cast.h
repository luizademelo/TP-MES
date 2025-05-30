// Copyright 2022 gRPC authors.

#ifndef GRPC_EVENT_ENGINE_INTERNAL_SLICE_CAST_H
#define GRPC_EVENT_ENGINE_INTERNAL_SLICE_CAST_H

namespace grpc_event_engine {
namespace experimental {
namespace internal {

template <typename Result, typename T>
struct SliceCastable;

template <typename A>
struct SliceCastable<A, A> {};

template <typename Result, typename T>
const Result& SliceCast(const T& value, SliceCastable<Result, T> = {}) {

  static_assert(sizeof(Result) == sizeof(T), "size mismatch");
  return reinterpret_cast<const Result&>(value);
}

template <typename Result, typename T>
Result& SliceCast(T& value, SliceCastable<Result, T> = {}) {

  static_assert(sizeof(Result) == sizeof(T), "size mismatch");
  return reinterpret_cast<Result&>(value);
}

template <typename Result, typename T>
Result&& SliceCast(T&& value, SliceCastable<Result, T> = {}) {

  static_assert(sizeof(Result) == sizeof(T), "size mismatch");
  return reinterpret_cast<Result&&>(value);
}

}
}
}

#endif
