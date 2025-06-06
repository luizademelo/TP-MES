// Copyright 2024 gRPC authors.

#include "test/core/transport/chaotic_good/mock_frame_transport.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/race.h"
#include "src/core/lib/promise/try_seq.h"
#include "test/core/promise/poll_matcher.h"

namespace grpc_core {
namespace chaotic_good {
namespace testing {

MockFrameTransport::~MockFrameTransport() {
  while (!expected_writes_.empty()) {
    auto& w = expected_writes_.front();
    ADD_FAILURE_AT(w.whence.file(), w.whence.line())
        << "Expected write of "
        << absl::ConvertVariantTo<FrameInterface&>(w.frame).ToString();
    expected_writes_.pop();
  }
  if (sink_ != nullptr) {
    sink_->OnFrameTransportClosed(absl::OkStatus());
  }
}

void MockFrameTransport::Start(Party* party,
                               MpscReceiver<OutgoingFrame> outgoing_frames,
                               RefCountedPtr<FrameTransportSink> sink) {
  CHECK(sink_ == nullptr);
  sink_ = sink;
  party->Spawn(
      "MockFrameTransport_Writer",
      [self = RefAsSubclass<MockFrameTransport>(),
       outgoing_frames = std::move(outgoing_frames)]() mutable {
        return Race(
            Map(self->closed_.Wait(),
                [self](auto) {
                  return absl::UnavailableError("transport closed");
                }),
            Loop([self,
                  outgoing_frames = std::move(outgoing_frames)]() mutable {
              return TrySeq(
                  outgoing_frames.Next(),
                  [self](OutgoingFrame frame) -> LoopCtl<absl::Status> {
                    if (self->expected_writes_.empty()) {
                      ADD_FAILURE() << "Unexpected write of "
                                    << absl::ConvertVariantTo<FrameInterface&>(
                                           frame.payload)
                                           .ToString();
                      return Continue{};
                    }
                    auto expected = std::move(self->expected_writes_.front());
                    self->expected_writes_.pop();
                    EXPECT_EQ(expected.frame, frame.payload)
                        << " from " << expected.whence.file() << ":"
                        << expected.whence.line();
                    return Continue{};
                  });
            }));
      },
      [sink](absl::Status status) { sink->OnFrameTransportClosed(status); });
}

void MockFrameTransport::Read(Frame frame) {
  SliceBuffer buffer;
  auto& frame_interface = absl::ConvertVariantTo<FrameInterface&>(frame);
  LOG(INFO) << "Read " << frame_interface.ToString();
  auto header = frame_interface.MakeHeader();
  frame_interface.SerializePayload(buffer);
  sink_->OnIncomingFrame(IncomingFrame(header, std::move(buffer)));
}

}
}
}
