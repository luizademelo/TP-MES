// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chaotic_good_legacy/control_endpoint.h"

#include <grpc/grpc.h>

#include "gtest/gtest.h"
#include "test/core/call/yodel/yodel_test.h"
#include "test/core/transport/util/mock_promise_endpoint.h"

namespace grpc_core {

class ControlEndpointTest : public YodelTest {
 protected:
  using YodelTest::YodelTest;
};

#define CONTROL_ENDPOINT_TEST(name) YODEL_TEST(ControlEndpointTest, name)

CONTROL_ENDPOINT_TEST(CanWrite) {
  util::testing::MockPromiseEndpoint ep(1234);
  chaotic_good_legacy::ControlEndpoint control_endpoint(
      std::move(ep.promise_endpoint), event_engine().get());
  ep.ExpectWrite(
      {grpc_event_engine::experimental::Slice::FromCopiedString("hello")},
      nullptr);
  SpawnTestSeqWithoutContext(
      "write",
      control_endpoint.Write(SliceBuffer(Slice::FromCopiedString("hello"))));
  WaitForAllPendingWork();
}

}
