// Copyright 2022 gRPC authors.

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chaotic_good_legacy/frame_header.h"

using grpc_core::chaotic_good_legacy::FrameHeader;
using HeaderBuffer = std::array<uint8_t, FrameHeader::kFrameHeaderSize>;

void RoundTrips(HeaderBuffer buffer) {
  auto r = FrameHeader::Parse(buffer.data());
  if (!r.ok()) return;
  HeaderBuffer reserialized;
  r->Serialize(reserialized.data());
  EXPECT_EQ(buffer, reserialized);
}
FUZZ_TEST(FrameHeaderTest, RoundTrips);
