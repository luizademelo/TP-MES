// Copyright 2022 gRPC authors.

#include "src/core/ext/transport/chaotic_good/frame.h"

#include <cstdint>

#include "absl/log/check.h"
#include "absl/random/random.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "test/core/transport/chaotic_good/test_frame.h"

namespace grpc_core {
namespace chaotic_good {
namespace {

void AssertRoundTrips(const Frame& input) {
  const auto& input_interface =
      absl::ConvertVariantTo<const FrameInterface&>(input);
  const auto hdr = input_interface.MakeHeader();

  SliceBuffer output_buffer;
  input_interface.SerializePayload(output_buffer);
  EXPECT_EQ(hdr.payload_length, output_buffer.Length());
  absl::StatusOr<Frame> output = ParseFrame(hdr, std::move(output_buffer));
  CHECK_OK(output);
  CHECK_EQ(absl::ConvertVariantTo<const FrameInterface&>(*output).ToString(),
           input_interface.ToString());
}
FUZZ_TEST(FrameTest, AssertRoundTrips).WithDomains(AnyFrame());

TEST(FrameTest, SettingsFrameRoundTrips) { AssertRoundTrips(SettingsFrame{}); }

}
}
}
