// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_USEFUL_H
#define GRPC_SRC_CORE_UTIL_USEFUL_H

#include <grpc/support/port_platform.h>

#include <cstddef>
#include <limits>
#include <variant>

#include "absl/log/check.h"
#include "absl/numeric/bits.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

template <typename T>
T Clamp(T val, T min, T max) {
  if (val < min) return min;
  if (max < val) return max;
  return val;
}

template <typename T>
T SetBit(T* i, size_t n) {
  return *i |= (T(1) << n);
}

template <typename T>
T ClearBit(T* i, size_t n) {
  return *i &= ~(T(1) << n);
}

template <typename T>
bool GetBit(T i, size_t n) {
  return (i & (T(1) << n)) != 0;
}

template <typename T>
int QsortCompare(const T& a, const T& b) {
  if (a < b) return -1;
  if (b < a) return 1;
  return 0;
}

template <typename... X>
int QsortCompare(const std::variant<X...>& a, const std::variant<X...>& b) {
  const int index = QsortCompare(a.index(), b.index());
  if (index != 0) return index;
  return std::visit(
      [&](const auto& x) {
        return QsortCompare(x, std::get<absl::remove_cvref_t<decltype(x)>>(b));
      },
      a);
}

inline int QsortCompare(absl::string_view a, absl::string_view b) {
  return a.compare(b);
}

inline int QsortCompare(const std::string& a, const std::string& b) {
  return a.compare(b);
}

template <typename A, typename B>
int QsortCompare(const std::pair<A, B>& a, const std::pair<A, B>& b) {
  const int first = QsortCompare(a.first, b.first);
  if (first != 0) return first;
  return QsortCompare(a.second, b.second);
}

template <typename T>
constexpr size_t HashPointer(T* p, size_t range) {
  return (((reinterpret_cast<size_t>(p)) >> 4) ^
          ((reinterpret_cast<size_t>(p)) >> 9) ^
          ((reinterpret_cast<size_t>(p)) >> 14)) %
         range;
}

template <typename T>
inline T SaturatingAdd(T a, T b) {
  if (a > 0) {
    if (b > std::numeric_limits<T>::max() - a) {
      return std::numeric_limits<T>::max();
    }
  } else if (b < std::numeric_limits<T>::min() - a) {
    return std::numeric_limits<T>::min();
  }
  return a + b;
}

inline uint32_t MixHash32(uint32_t a, uint32_t b) {
  return absl::rotl(a, 2u) ^ b;
}

inline uint32_t RoundUpToPowerOf2(uint32_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline uint8_t LowestOneBit(uint8_t x) {
  return x & -x;
}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline uint16_t LowestOneBit(uint16_t x) {
  return x & -x;
}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline uint32_t LowestOneBit(uint32_t x) {
  return x & -x;
}

GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline uint64_t LowestOneBit(uint64_t x) {
  return x & -x;
}

}

#define GPR_ARRAY_SIZE(array) (sizeof(array) / sizeof(*(array)))

#endif
