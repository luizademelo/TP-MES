// Copyright 2022 gRPC authors.

#include <cstdint>
#include <vector>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/ext/transport/chaotic_good/tcp_frame_transport.h"

namespace grpc_core {
namespace chaotic_good {
namespace {

std::vector<uint8_t> Serialize(TcpFrameHeader h) {
  uint8_t buffer[TcpFrameHeader::kFrameHeaderSize];
  h.Serialize(buffer);
  return std::vector<uint8_t>(buffer,
                              buffer + TcpFrameHeader::kFrameHeaderSize);
}

absl::StatusOr<TcpFrameHeader> Deserialize(std::vector<uint8_t> data) {
  if (data.size() != TcpFrameHeader::kFrameHeaderSize) {
    return absl::InvalidArgumentError("bad length");
  }
  return TcpFrameHeader::Parse(data.data());
}

TEST(TcpFrameHeader, SimpleSerialize) {
  EXPECT_EQ(Serialize(TcpFrameHeader{
                {FrameType::kCancel, 0x01020304, 0x05060708}, 1}),
            std::vector<uint8_t>({
                0xff, 0x01,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x04, 0x03, 0x02, 0x01,
                0x08, 0x07, 0x06, 0x05,
            }));
}

TEST(TcpFrameHeader, SimpleDeserialize) {
  EXPECT_EQ(Deserialize(std::vector<uint8_t>({
                0xff, 0x01,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x04, 0x03, 0x02, 0x01,
                0x08, 0x07, 0x06, 0x05,
            })),
            absl::StatusOr<TcpFrameHeader>(TcpFrameHeader{
                {FrameType::kCancel, 0x01020304, 0x05060708}, 1}));
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
