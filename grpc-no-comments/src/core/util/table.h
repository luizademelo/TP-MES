// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_TABLE_H
#define GRPC_SRC_CORE_UTIL_TABLE_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <initializer_list>
#include <new>
#include <type_traits>
#include <utility>

#include "absl/meta/type_traits.h"
#include "absl/utility/utility.h"
#include "src/core/util/bitset.h"

namespace grpc_core {

namespace table_detail {

template <typename, typename... Ts>
struct Elements;

template <typename T, typename... Ts>
struct Elements<absl::enable_if_t<!std::is_empty<T>::value>, T, Ts...>
    : Elements<void, Ts...> {
  struct alignas(T) Data {
    unsigned char bytes[sizeof(T)];
  };
  Data x;
  Elements() {}
  T* ptr() { return reinterpret_cast<T*>(x.bytes); }
  const T* ptr() const { return reinterpret_cast<const T*>(x.bytes); }
};
template <typename T, typename... Ts>
struct Elements<absl::enable_if_t<std::is_empty<T>::value>, T, Ts...>
    : Elements<void, Ts...> {
  T* ptr() { return reinterpret_cast<T*>(this); }
  const T* ptr() const { return reinterpret_cast<const T*>(this); }
};
template <>
struct Elements<void> {};

template <size_t I, typename... Ts>
struct GetElem;

template <typename T, typename... Ts>
struct GetElem<0, T, Ts...> {
  static T* f(Elements<void, T, Ts...>* e) { return e->ptr(); }
  static const T* f(const Elements<void, T, Ts...>* e) { return e->ptr(); }
};

template <size_t I, typename T, typename... Ts>
struct GetElem<I, T, Ts...> {
  static auto f(Elements<void, T, Ts...>* e)
      -> decltype(GetElem<I - 1, Ts...>::f(e)) {
    return GetElem<I - 1, Ts...>::f(e);
  }
  static auto f(const Elements<void, T, Ts...>* e)
      -> decltype(GetElem<I - 1, Ts...>::f(e)) {
    return GetElem<I - 1, Ts...>::f(e);
  }
};

template <typename Needle, typename... Haystack>
struct CountIncludedStruct;

template <typename Needle, typename Straw, typename... RestOfHaystack>
struct CountIncludedStruct<Needle, Straw, RestOfHaystack...> {
  static constexpr size_t N =
      static_cast<size_t>(std::is_same<Needle, Straw>::value) +
      CountIncludedStruct<Needle, RestOfHaystack...>::N;
};
template <typename Needle>
struct CountIncludedStruct<Needle> {
  static constexpr size_t N = 0;
};

template <typename Needle, typename... Haystack>
constexpr size_t CountIncluded() {
  return CountIncludedStruct<Needle, Haystack...>::N;
}

template <typename Ignored, typename Needle, typename... Haystack>
struct IndexOfStruct;

template <typename Needle, typename Straw, typename... RestOfHaystack>
struct IndexOfStruct<absl::enable_if_t<std::is_same<Needle, Straw>::value>,
                     Needle, Straw, RestOfHaystack...> {

  static constexpr size_t N = 0;
};
template <typename Needle, typename Straw, typename... RestOfHaystack>
struct IndexOfStruct<absl::enable_if_t<!std::is_same<Needle, Straw>::value>,
                     Needle, Straw, RestOfHaystack...> {

  static constexpr size_t N =
      1 + IndexOfStruct<void, Needle, RestOfHaystack...>::N;
};

template <typename Needle, typename... Haystack>
constexpr absl::enable_if_t<CountIncluded<Needle, Haystack...>() == 1, size_t>
IndexOf() {
  return IndexOfStruct<void, Needle, Haystack...>::N;
}

template <size_t I, typename... Ts>
struct TypeIndexStruct;

template <typename T, typename... Ts>
struct TypeIndexStruct<0, T, Ts...> {
  using Type = T;
};
template <size_t I, typename T, typename... Ts>
struct TypeIndexStruct<I, T, Ts...> : TypeIndexStruct<I - 1, Ts...> {};

template <size_t I, typename... Ts>
using TypeIndex = typename TypeIndexStruct<I, Ts...>::Type;

template <typename T>
void DestructIfNotNull(T* p) {
  if (p) p->~T();
}

}

template <typename... Ts>
class Table {

  template <size_t I>
  using TypeIndex = table_detail::TypeIndex<I, Ts...>;

 public:

  Table() = default;

  ~Table() { Destruct(absl::make_index_sequence<sizeof...(Ts)>()); }

  Table(const Table& rhs) {

    Copy<false>(absl::make_index_sequence<sizeof...(Ts)>(), rhs);
  }

  Table& operator=(const Table& rhs) {

    Copy<true>(absl::make_index_sequence<sizeof...(Ts)>(), rhs);
    return *this;
  }

  Table(Table&& rhs) noexcept {

    Move<false>(absl::make_index_sequence<sizeof...(Ts)>(),
                std::forward<Table>(rhs));
  }

  Table& operator=(Table&& rhs) noexcept {

    Move<true>(absl::make_index_sequence<sizeof...(Ts)>(),
               std::forward<Table>(rhs));
    return *this;
  }

  template <typename T>
  bool has() const {
    return has<index_of<T>()>();
  }

  template <size_t I>
  absl::enable_if_t<(I < sizeof...(Ts)), bool> has() const {
    return present_bits_.is_set(I);
  }

  template <typename T>
  T* get() {
    return get<index_of<T>()>();
  }

  template <typename T>
  const T* get() const {
    return get<index_of<T>()>();
  }

  template <size_t I>
  TypeIndex<I>* get() {
    if (has<I>()) return element_ptr<I>();
    return nullptr;
  }

  template <size_t I>
  const TypeIndex<I>* get() const {
    if (has<I>()) return element_ptr<I>();
    return nullptr;
  }

  template <typename T>
  T* get_or_create() {
    return get_or_create<index_of<T>()>();
  }

  template <size_t I>
  TypeIndex<I>* get_or_create() {
    auto* p = element_ptr<I>();
    if (!set_present<I>(true)) {
      new (p) TypeIndex<I>();
    }
    return element_ptr<I>();
  }

  template <typename T, typename... Args>
  T* set(Args&&... args) {
    return set<index_of<T>()>(std::forward<Args>(args)...);
  }

  template <size_t I, typename... Args>
  TypeIndex<I>* set(Args&&... args) {
    auto* p = element_ptr<I>();
    if (set_present<I>(true)) {
      TypeIndex<I> replacement(std::forward<Args>(args)...);
      *p = std::move(replacement);
    } else {
      new (p) TypeIndex<I>(std::forward<Args>(args)...);
    }
    return p;
  }

  template <size_t I>
  TypeIndex<I>* set(TypeIndex<I>&& value) {
    auto* p = element_ptr<I>();
    if (set_present<I>(true)) {
      *p = std::forward<TypeIndex<I>>(value);
    } else {
      new (p) TypeIndex<I>(std::forward<TypeIndex<I>>(value));
    }
    return p;
  }

  template <typename T>
  void clear() {
    clear<index_of<T>()>();
  }

  template <size_t I>
  void clear() {
    if (set_present<I>(false)) {
      using T = TypeIndex<I>;
      element_ptr<I>()->~T();
    }
  }

  template <typename F>
  void ForEach(F f) const {
    ForEachImpl(std::move(f), absl::make_index_sequence<sizeof...(Ts)>());
  }

  template <typename F, typename... Vs>
  void ForEachIn(F f) const {
    ForEachImpl(std::move(f),
                absl::index_sequence<table_detail::IndexOf<Vs, Ts...>()...>());
  }

  template <typename F, typename... Vs>
  void FilterIn(F f) {
    FilterInImpl(std::move(f),
                 absl::index_sequence<table_detail::IndexOf<Vs, Ts...>()...>());
  }

  size_t count() const { return present_bits_.count(); }

  bool empty() const { return present_bits_.none(); }

  void ClearAll() { ClearAllImpl(absl::make_index_sequence<sizeof...(Ts)>()); }

 private:

  using PresentBits = BitSet<sizeof...(Ts)>;

  using Elements = table_detail::Elements<void, Ts...>;

  template <size_t I>
  using GetElem = table_detail::GetElem<I, Ts...>;

  template <typename T>
  static constexpr size_t index_of() {
    return table_detail::IndexOf<T, Ts...>();
  }

  template <size_t I>
  TypeIndex<I>* element_ptr() {
    return GetElem<I>::f(&elements_);
  }

  template <size_t I>
  const TypeIndex<I>* element_ptr() const {
    return GetElem<I>::f(&elements_);
  }

  template <size_t I>
  bool set_present(bool value) {
    bool out = present_bits_.is_set(I);
    present_bits_.set(I, value);
    return out;
  }

  template <bool or_clear, size_t I>
  void CopyIf(const Table& rhs) {
    if (auto* p = rhs.get<I>()) {
      set<I>(*p);
    } else if (or_clear) {
      clear<I>();
    }
  }

  template <bool or_clear, size_t I>
  void MoveIf(Table&& rhs) {
    if (auto* p = rhs.get<I>()) {
      set<I>(std::move(*p));
    } else if (or_clear) {
      clear<I>();
    }
  }

  template <size_t I, typename F>
  void CallIf(F* f) const {
    if (auto* p = get<I>()) {
      (*f)(*p);
    }
  }

  template <size_t I, typename F>
  void FilterIf(F* f) {
    if (auto* p = get<I>()) {
      if (!(*f)(*p)) {
        clear<I>();
      }
    }
  }

  template <size_t... I>
  void Destruct(absl::index_sequence<I...>) {
    (table_detail::DestructIfNotNull(get<I>()), ...);
  }

  template <bool or_clear, size_t... I>
  void Copy(absl::index_sequence<I...>, const Table& rhs) {
    (CopyIf<or_clear, I>(rhs), ...);
  }

  template <bool or_clear, size_t... I>
  void Move(absl::index_sequence<I...>, Table&& rhs) {
    (MoveIf<or_clear, I>(std::forward<Table>(rhs)), ...);
  }

  template <typename F, size_t... I>
  void ForEachImpl(F f, absl::index_sequence<I...>) const {
    (CallIf<I>(&f), ...);
  }

  template <typename F, size_t... I>
  void FilterInImpl(F f, absl::index_sequence<I...>) {
    (FilterIf<I>(&f), ...);
  }

  template <size_t... I>
  void ClearAllImpl(absl::index_sequence<I...>) {
    (clear<I>(), ...);
  }

  PresentBits present_bits_;

  Elements elements_;
};

}

#endif
