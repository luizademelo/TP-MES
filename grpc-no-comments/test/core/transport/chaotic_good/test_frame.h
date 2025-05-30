// Copyright 2025 The gRPC authors.

#ifndef GRPC_TEST_CORE_TRANSPORT_CHAOTIC_GOOD_TEST_FRAME_H
#define GRPC_TEST_CORE_TRANSPORT_CHAOTIC_GOOD_TEST_FRAME_H

#include "fuzztest/fuzztest.h"
#include "src/core/ext/transport/chaotic_good/frame.h"
#include "test/core/transport/chaotic_good/test_frame.pb.h"

namespace grpc_core {
namespace chaotic_good {

Frame FrameFromTestFrame(const chaotic_good_frame::TestFrame& frame);

inline auto AnyFrame() {
  return ::fuzztest::Filter(
      [](const Frame& frame) {
        return absl::ConvertVariantTo<const FrameInterface&>(frame).IsLegal();
      },
      ::fuzztest::Map(FrameFromTestFrame,
                      ::fuzztest::Arbitrary<chaotic_good_frame::TestFrame>()));
}

}
}

#endif
