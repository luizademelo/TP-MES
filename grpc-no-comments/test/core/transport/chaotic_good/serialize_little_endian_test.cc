// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good/serialize_little_endian.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <cstdint>

#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"

namespace grpc_core::chaotic_good {

void RoundTrips32(uint32_t x) {
  uint8_t buffer[4];
  WriteLittleEndianUint32(x, buffer);
  uint32_t y = ReadLittleEndianUint32(buffer);
  EXPECT_EQ(x, y);
}
FUZZ_TEST(SerializeLittleEndianTest, RoundTrips32);

void RoundTrips64(uint64_t x) {
  uint8_t buffer[8];
  WriteLittleEndianUint64(x, buffer);
  uint64_t y = ReadLittleEndianUint64(buffer);
  EXPECT_EQ(x, y);
}
FUZZ_TEST(SerializeLittleEndianTest, RoundTrips64);

}
