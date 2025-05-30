// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TYPE_LIST_H
#define GRPC_SRC_CORE_UTIL_TYPE_LIST_H

namespace grpc_core {

template <typename... A>
struct Typelist {
  template <template <typename...> class T>
  using Instantiate = T<A...>;

  template <typename C>
  using PushFront = Typelist<C, A...>;

  template <typename C>
  using PushBack = Typelist<A..., C>;
};

namespace typelist_detail {
template <typename T>
struct ReverseTpl;

template <typename A>
struct ReverseTpl<Typelist<A>> {
  using Result = Typelist<A>;
};

template <typename A, typename... Rest>
struct ReverseTpl<Typelist<A, Rest...>> {
  using Result =
      typename ReverseTpl<Typelist<Rest...>>::Result::template PushBack<A>;
};
}

template <typename... A>
using Reverse = typename typelist_detail::ReverseTpl<Typelist<A...>>::Result;

template <auto... A>
struct Valuelist {
  template <template <auto...> class T>
  using Instantiate = T<A...>;

  template <auto C>
  using PushFront = Valuelist<C, A...>;

  template <auto C>
  using PushBack = Valuelist<A..., C>;
};

namespace valuelist_detail {
template <typename T>
struct ReverseTpl;

template <auto A>
struct ReverseTpl<Valuelist<A>> {
  using Result = Valuelist<A>;
};

template <auto A, auto... Rest>
struct ReverseTpl<Valuelist<A, Rest...>> {
  using Result =
      typename ReverseTpl<Valuelist<Rest...>>::Result::template PushBack<A>;
};

}

template <auto... A>
using ReverseValues =
    typename valuelist_detail::ReverseTpl<Valuelist<A...>>::Result;

}

#endif
