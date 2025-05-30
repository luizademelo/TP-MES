// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SORTED_PACK_H
#define GRPC_SRC_CORE_UTIL_SORTED_PACK_H

#include <grpc/support/port_platform.h>

#include <type_traits>

#include "src/core/util/type_list.h"

namespace grpc_core {

namespace sorted_pack_detail {

template <template <typename, typename> class Cmp, typename Args>
struct Smallest;

template <template <typename, typename> class Cmp, typename Arg,
          typename... Args>
struct Smallest<Cmp, Typelist<Arg, Args...>> {
  using SmallestRest = Smallest<Cmp, Typelist<Args...>>;
  using PrevSmallest = typename SmallestRest::Result;
  using PrevRest = typename SmallestRest::Rest;
  static constexpr bool kCmpResult = Cmp<Arg, PrevSmallest>::kValue;
  using Result = typename std::conditional<kCmpResult, Arg, PrevSmallest>::type;
  using Prefix = typename std::conditional<kCmpResult, PrevSmallest, Arg>::type;
  using Rest = typename PrevRest::template PushFront<Prefix>;
};

template <template <typename, typename> class Cmp, typename Arg>
struct Smallest<Cmp, Typelist<Arg>> {
  using Result = Arg;
  using Rest = Typelist<>;
};

template <template <typename, typename> class Cmp, typename Args>
struct Sorted;

template <template <typename, typename> class Cmp, typename... Args>
struct Sorted<Cmp, Typelist<Args...>> {
  using SmallestResult = Smallest<Cmp, Typelist<Args...>>;
  using SmallestType = typename SmallestResult::Result;
  using RestOfTypes = typename SmallestResult::Rest;
  using SortedRestOfTypes = typename Sorted<Cmp, RestOfTypes>::Result;
  using Result = typename SortedRestOfTypes::template PushFront<SmallestType>;
};

template <template <typename, typename> class Cmp, typename Arg>
struct Sorted<Cmp, Typelist<Arg>> {
  using Result = Typelist<Arg>;
};

template <template <typename, typename> class Cmp>
struct Sorted<Cmp, Typelist<>> {
  using Result = Typelist<>;
};

}

template <template <typename...> class T,
          template <typename, typename> class Cmp, typename... Args>
struct WithSortedPack {
  using Type = typename sorted_pack_detail::Sorted<
      Cmp, Typelist<Args...>>::Result::template Instantiate<T>;
};

}

#endif
