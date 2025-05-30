
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_VARINT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_TRANSPORT_VARINT_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include "absl/log/check.h"

namespace grpc_core {

constexpr uint32_t MaxInVarintPrefix(uint8_t prefix_bits) {
  return (1 << (8 - prefix_bits)) - 1;
}

size_t VarintLength(size_t tail_value);
void VarintWriteTail(size_t tail_value, uint8_t* target, size_t tail_length);

template <uint8_t kPrefixBits>
class VarintWriter {
 public:
  static constexpr uint32_t kMaxInPrefix = MaxInVarintPrefix(kPrefixBits);

  explicit VarintWriter(size_t value)
      : value_(value),
        length_(value < kMaxInPrefix ? 1 : VarintLength(value - kMaxInPrefix)) {
    CHECK(value <= UINT32_MAX);
  }

  size_t value() const { return value_; }
  size_t length() const { return length_; }

  void Write(uint8_t prefix, uint8_t* target) const {
    if (length_ == 1) {
      target[0] = prefix | value_;
    } else {
      target[0] = prefix | kMaxInPrefix;
      VarintWriteTail(value_ - kMaxInPrefix, target + 1, length_ - 1);
    }
  }

 private:
  const size_t value_;

  const size_t length_;
};

}

#endif
