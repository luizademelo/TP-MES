// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_OVERLOAD_H
#define GRPC_SRC_CORE_UTIL_OVERLOAD_H

#include <grpc/support/port_platform.h>

#include <utility>

namespace grpc_core {

template <typename... Cases>
struct OverloadType;

template <typename Case, typename... Cases>
struct OverloadType<Case, Cases...> : public Case,
                                      public OverloadType<Cases...> {
  explicit OverloadType(Case&& c, Cases&&... cases)
      : Case(std::forward<Case>(c)),
        OverloadType<Cases...>(std::forward<Cases>(cases)...) {}
  using Case::operator();
  using OverloadType<Cases...>::operator();
};

template <typename Case>
struct OverloadType<Case> : public Case {
  explicit OverloadType(Case&& c) : Case(std::forward<Case>(c)) {}
  using Case::operator();
};

template <typename... Cases>
OverloadType<Cases...> Overload(Cases... cases) {
  return OverloadType<Cases...>(std::move(cases)...);
}

}

#endif
