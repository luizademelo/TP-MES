
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_MANUAL_CONSTRUCTOR_H
#define GRPC_SRC_CORE_UTIL_MANUAL_CONSTRUCTOR_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <utility>

#include "src/core/util/construct_destruct.h"

namespace grpc_core {

namespace manual_ctor_impl {

template <class Member, class... List>
class is_one_of;

template <class Member, class... List>
class is_one_of<Member, Member, List...> {
 public:
  static constexpr const bool value = true;
};

template <class Member, class A, class... List>
class is_one_of<Member, A, List...> {
 public:
  static constexpr const bool value = is_one_of<Member, List...>::value;
};

template <class Member>
class is_one_of<Member> {
 public:
  static constexpr const bool value = false;
};

template <class... Types>
class max_size_of;

template <class A>
class max_size_of<A> {
 public:
  static constexpr const size_t value = sizeof(A);
};

template <class A, class... B>
class max_size_of<A, B...> {
 public:
  static constexpr const size_t value = sizeof(A) > max_size_of<B...>::value
                                            ? sizeof(A)
                                            : max_size_of<B...>::value;
};

template <class... Types>
class max_align_of;

template <class A>
class max_align_of<A> {
 public:
  static constexpr const size_t value = alignof(A);
};

template <class A, class... B>
class max_align_of<A, B...> {
 public:
  static constexpr const size_t value = alignof(A) > max_align_of<B...>::value
                                            ? alignof(A)
                                            : max_align_of<B...>::value;
};

}

template <typename Type>
class ManualConstructor {
 public:

  Type* get() { return reinterpret_cast<Type*>(&space_); }
  const Type* get() const { return reinterpret_cast<const Type*>(&space_); }

  Type* operator->() { return get(); }
  const Type* operator->() const { return get(); }

  Type& operator*() { return *get(); }
  const Type& operator*() const { return *get(); }

  void Init() { Construct(get()); }

  template <typename... Ts>
  void Init(Ts&&... args) {
    Construct(get(), std::forward<Ts>(args)...);
  }

  void Init(const Type& x) { Construct(get(), x); }
  void Init(Type&& x) { Construct(get(), std::forward<Type>(x)); }

  void Destroy() { Destruct(get()); }

 private:
  alignas(Type) char space_[sizeof(Type)];
};

}

#endif
