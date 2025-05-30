// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_MATCH_H
#define GRPC_SRC_CORE_UTIL_MATCH_H

#include <grpc/support/port_platform.h>

#include <utility>
#include <variant>

#include "src/core/util/overload.h"

namespace grpc_core {

namespace detail {

template <typename... Cases>
struct MatchPointerExtractor {
  OverloadType<Cases...> cases;
  template <typename T>
  auto operator()(T& value) -> decltype(cases(&value)) {
    return cases(&value);
  }
};

}

template <typename... Fs, typename T0, typename... Ts>
auto Match(const std::variant<T0, Ts...>& value, Fs... fs)
    -> decltype(std::declval<OverloadType<Fs...>>()(std::declval<T0>())) {
  return std::visit(Overload(std::move(fs)...), value);
}

template <typename... Fs, typename T0, typename... Ts>
auto MatchMutable(std::variant<T0, Ts...>* value, Fs... fs)
    -> decltype(std::declval<OverloadType<Fs...>>()(std::declval<T0*>())) {
  return std::visit(detail::MatchPointerExtractor<Fs...>{OverloadType<Fs...>(
                        std::move(fs)...)},
                    *value);
}

}

#endif
