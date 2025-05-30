// Copyright 2022 gRPC authors.

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chaotic_good/tcp_frame_transport.h"

using grpc_core::chaotic_good::TcpFrameHeader;
using HeaderBuffer = std::array<uint8_t, TcpFrameHeader::kFrameHeaderSize>;

void RoundTrips(HeaderBuffer buffer) {
  auto r = TcpFrameHeader::Parse(buffer.data());
  if (!r.ok()) return;
  HeaderBuffer reserialized;
  r->Serialize(reserialized.data());
  EXPECT_EQ(buffer, reserialized) << r->ToString();
}
FUZZ_TEST(FrameHeaderTest, RoundTrips);
