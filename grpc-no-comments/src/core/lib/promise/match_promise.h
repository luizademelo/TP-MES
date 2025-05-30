// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_MATCH_PROMISE_H
#define GRPC_SRC_CORE_LIB_PROMISE_MATCH_PROMISE_H

#include <variant>

#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/promise/detail/promise_variant.h"
#include "src/core/util/overload.h"

namespace grpc_core {

namespace promise_detail {

template <typename Constructor, typename... Ts>
struct ConstructPromiseVariantVisitor {

  Constructor constructor;

  template <typename T>
  auto CallConstructorThenFactory(T x) {
    OncePromiseFactory<T, Constructor> factory(std::move(constructor));
    return factory.Make(std::move(x));
  }

  template <typename T>
  auto operator()(T x) -> std::variant<promise_detail::PromiseLike<
      decltype(CallConstructorThenFactory(std::declval<Ts>()))>...> {
    return CallConstructorThenFactory(std::move(x));
  }
};

}

template <typename... Fs, typename... Ts>
auto MatchPromise(std::variant<Ts...> value, Fs... fs) {

  auto body = std::visit(
      promise_detail::ConstructPromiseVariantVisitor<OverloadType<Fs...>,
                                                     Ts...>{
          OverloadType<Fs...>(std::move(fs)...)},
      std::move(value));

  return promise_detail::PromiseVariant<decltype(body)>(std::move(body));
}

}

#endif
