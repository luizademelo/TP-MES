// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good_legacy/frame_header.h"

#include <cstdint>
#include <vector>

#include "absl/status/status.h"
#include "gtest/gtest.h"

namespace grpc_core {
namespace chaotic_good_legacy {
namespace {

std::vector<uint8_t> Serialize(FrameHeader h) {
  uint8_t buffer[FrameHeader::kFrameHeaderSize];
  h.Serialize(buffer);
  return std::vector<uint8_t>(buffer, buffer + FrameHeader::kFrameHeaderSize);
}

absl::StatusOr<FrameHeader> Deserialize(std::vector<uint8_t> data) {
  if (data.size() != FrameHeader::kFrameHeaderSize) {
    return absl::InvalidArgumentError("bad length");
  }
  return FrameHeader::Parse(data.data());
}

TEST(FrameHeaderTest, SimpleSerialize) {
  EXPECT_EQ(
      Serialize(FrameHeader{FrameType::kCancel, 1, 0x01020304, 0x05060708}),
      std::vector<uint8_t>({
          1, 0, 0xff, 0,
          0x04, 0x03, 0x02, 0x01,
          0x08, 0x07, 0x06, 0x05,
      }));
}

TEST(FrameHeaderTest, SimpleDeserialize) {
  EXPECT_EQ(Deserialize(std::vector<uint8_t>({
                1, 0, 0xff, 0,
                0x04, 0x03, 0x02, 0x01,
                0x08, 0x07, 0x06, 0x05,
            })),
            absl::StatusOr<FrameHeader>(
                FrameHeader{FrameType::kCancel, 1, 0x01020304, 0x05060708}));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
