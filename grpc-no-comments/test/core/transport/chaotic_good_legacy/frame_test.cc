// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good_legacy/frame.h"

#include <cstdint>

#include "absl/log/check.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"

namespace grpc_core {
namespace chaotic_good_legacy {
namespace {

template <typename T>
void AssertRoundTrips(const T& input, FrameType expected_frame_type) {
  const auto hdr = input.MakeHeader();
  EXPECT_EQ(hdr.type, expected_frame_type);

  EXPECT_EQ(hdr.payload_connection_id, 0);
  SliceBuffer output_buffer;
  input.SerializePayload(output_buffer);
  EXPECT_EQ(hdr.payload_length, output_buffer.Length());
  T output;
  auto deser = output.Deserialize(hdr, std::move(output_buffer));
  CHECK_OK(deser);
  CHECK_EQ(output.ToString(), input.ToString());
}

TEST(FrameTest, SettingsFrameRoundTrips) {
  AssertRoundTrips(SettingsFrame{}, FrameType::kSettings);
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int r = RUN_ALL_TESTS();
  return r;
}
