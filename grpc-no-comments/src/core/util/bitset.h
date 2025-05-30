// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_BITSET_H
#define GRPC_SRC_CORE_UTIL_BITSET_H

#include <grpc/support/port_platform.h>
#include <stddef.h>
#include <stdint.h>

#include <type_traits>

#include "src/core/util/useful.h"

namespace grpc_core {

template <size_t kBits>
struct UintSelector;

template <>
struct UintSelector<8> {
  typedef uint8_t Type;
};
template <>
struct UintSelector<16> {
  typedef uint16_t Type;
};
template <>
struct UintSelector<32> {
  typedef uint32_t Type;
};
template <>
struct UintSelector<64> {
  typedef uint64_t Type;
};

template <size_t kBits>
using Uint = typename UintSelector<kBits>::Type;

constexpr size_t ChooseUnitBitsForBitSet(size_t total_bits) {
  return total_bits <= 8    ? 8
         : total_bits <= 16 ? 16
         : total_bits <= 24 ? 8
         : total_bits <= 32 ? 32
         : total_bits <= 48 ? 16
         : total_bits <= 64 ? 64
         : total_bits <= 96 ? 32
                            : 64;
}

template <size_t kTotalBits,
          size_t kUnitBits = ChooseUnitBitsForBitSet(kTotalBits)>
class BitSet {
  static constexpr size_t kUnits = (kTotalBits + kUnitBits - 1) / kUnitBits;

 public:

  constexpr BitSet() : units_{} {}

  constexpr void set(int i) { units_[unit_for(i)] |= mask_for(i); }

  constexpr void set(int i, bool is_set) {
    if (is_set) {
      set(i);
    } else {
      clear(i);
    }
  }

  constexpr void clear(int i) { units_[unit_for(i)] &= ~mask_for(i); }

  constexpr bool is_set(int i) const {
    return (units_[unit_for(i)] & mask_for(i)) != 0;
  }

  bool all() const {
    if (kTotalBits % kUnitBits == 0) {

      for (size_t i = 0; i < kUnits; i++) {
        if (units_[i] != all_ones()) return false;
      }
      return true;
    } else {

      for (size_t i = 0; i < kUnits - 1; i++) {
        if (units_[i] != all_ones()) return false;
      }
      return units_[kUnits - 1] == n_ones(kTotalBits % kUnitBits);
    }
  }

  bool none() const {
    for (size_t i = 0; i < kUnits; i++) {
      if (units_[i] != 0) return false;
    }
    return true;
  }

  bool any() const { return !none(); }

  uint32_t count() const {
    uint32_t count = 0;
    for (size_t i = 0; i < kUnits; i++) {
      count += absl::popcount(units_[i]);
    }
    return count;
  }

  bool operator==(const BitSet& other) const {
    for (size_t i = 0; i < kUnits; i++) {
      if (units_[i] != other.units_[i]) return false;
    }
    return true;
  }

  template <typename Int>
  typename std::enable_if<std::is_unsigned<Int>::value &&
                              (sizeof(Int) * 8 >= kTotalBits),
                          Int>::type
  ToInt() const {
    Int result = 0;
    for (size_t i = 0; i < kTotalBits; i++) {
      if (is_set(i)) result |= (Int(1) << i);
    }
    return result;
  }

  template <typename Int>
  static BitSet<kTotalBits, kUnitBits> FromInt(Int value) {
    BitSet<kTotalBits, kUnitBits> result;
    for (size_t i = 0; i < kTotalBits; i++) {
      result.set(i, (value & (Int(1) << i)) != 0);
    }
    return result;
  }

  BitSet& Set(int i, bool value) {
    set(i, value);
    return *this;
  }

  BitSet& SetAll(bool value) {
    for (size_t i = 0; i < kTotalBits; i++) {
      set(i, value);
    }
    return *this;
  }

 private:

  static constexpr size_t unit_for(size_t bit) { return bit / kUnitBits; }

  static constexpr Uint<kUnitBits> mask_for(size_t bit) {
    return Uint<kUnitBits>{1} << (bit % kUnitBits);
  }

  static constexpr Uint<kUnitBits> all_ones() {
    return Uint<kUnitBits>(~Uint<kUnitBits>(0));
  }

  static constexpr Uint<kUnitBits> n_ones(size_t n) {
    return n == kUnitBits ? all_ones() : (Uint<kUnitBits>(1) << n) - 1;
  }

  Uint<kUnitBits> units_[kUnits];
};

template <>
class BitSet<0> {
 public:
  constexpr BitSet() {}

  bool all() const { return true; }
  bool none() const { return true; }
  uint32_t count() const { return 0; }
};

}

#endif
