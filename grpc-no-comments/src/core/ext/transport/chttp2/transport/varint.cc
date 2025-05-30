
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/varint.h"

#include <grpc/support/port_platform.h>

#include "absl/base/attributes.h"

namespace grpc_core {

size_t VarintLength(size_t tail_value) {
  if (tail_value < (1 << 7)) {
    return 2;
  } else if (tail_value < (1 << 14)) {
    return 3;
  } else if (tail_value < (1 << 21)) {
    return 4;
  } else if (tail_value < (1 << 28)) {
    return 5;
  } else {
    return 6;
  }
}

void VarintWriteTail(size_t tail_value, uint8_t* target, size_t tail_length) {
  switch (tail_length) {
    case 5:
      target[4] = static_cast<uint8_t>((tail_value >> 28) | 0x80);
      [[fallthrough]];
    case 4:
      target[3] = static_cast<uint8_t>((tail_value >> 21) | 0x80);
      [[fallthrough]];
    case 3:
      target[2] = static_cast<uint8_t>((tail_value >> 14) | 0x80);
      [[fallthrough]];
    case 2:
      target[1] = static_cast<uint8_t>((tail_value >> 7) | 0x80);
      [[fallthrough]];
    case 1:
      target[0] = static_cast<uint8_t>((tail_value) | 0x80);
  }
  target[tail_length - 1] &= 0x7f;
}

}
