
// Copyright 2015 gRPC authors.

#include "test/core/test_util/parse_hexstring.h"

#include <grpc/slice.h>
#include <stddef.h>
#include <stdint.h>

#include "absl/log/check.h"

namespace grpc_core {
Slice ParseHexstring(absl::string_view hexstring) {
  size_t nibbles = 0;
  uint8_t* out;
  uint8_t temp;
  grpc_slice slice;

  for (auto c : hexstring) {
    nibbles += (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
  }

  CHECK_EQ((nibbles & 1), 0u);

  slice = grpc_slice_malloc(nibbles / 2);
  out = GRPC_SLICE_START_PTR(slice);

  nibbles = 0;
  temp = 0;
  for (auto c : hexstring) {
    if (c >= '0' && c <= '9') {
      temp = static_cast<uint8_t>(temp << 4) | static_cast<uint8_t>(c - '0');
      nibbles++;
    } else if (c >= 'a' && c <= 'f') {
      temp =
          static_cast<uint8_t>(temp << 4) | static_cast<uint8_t>(c - 'a' + 10);
      nibbles++;
    }
    if (nibbles == 2) {
      *out++ = temp;
      nibbles = 0;
    }
  }

  return Slice(slice);
}
}
