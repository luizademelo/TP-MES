
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_server_transport.h"

#include <grpc/event_engine/slice.h>
#include <grpc/grpc.h>

#include <memory>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/util/orphanable.h"
#include "test/core/transport/chttp2/http2_frame_test_helper.h"
#include "test/core/transport/util/mock_promise_endpoint.h"
#include "test/core/transport/util/transport_test.h"

namespace grpc_core {
namespace http2 {
namespace testing {

using EventEngineSlice = grpc_event_engine::experimental::Slice;
using transport::testing::Http2FrameTestHelper;
using util::testing::MockPromiseEndpoint;
using util::testing::TransportTest;

class Http2ServerTransportTest : public TransportTest {
 public:
  Http2ServerTransportTest() {
    grpc_tracer_set_enabled("http2_ph2_transport", true);
  }

 protected:
  Http2FrameTestHelper helper_;
};

TEST_F(Http2ServerTransportTest, TestHttp2ServerTransportObjectCreation) {

  LOG(INFO) << "TestHttp2ServerTransportObjectCreation Begin";
  MockPromiseEndpoint mock_endpoint(1000);

  mock_endpoint.ExpectRead(
      {helper_.EventEngineSliceFromHttp2DataFrame(
           "Hello!", 9, false),
       helper_.EventEngineSliceFromHttp2DataFrame(
           "Bye!", 11, true)},
      event_engine().get());

  mock_endpoint.ExpectReadClose(absl::UnavailableError("Connection closed"),
                                event_engine().get());

  auto server_transport = MakeOrphanable<Http2ServerTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());

  EXPECT_EQ(server_transport->filter_stack_transport(), nullptr);
  EXPECT_EQ(server_transport->client_transport(), nullptr);
  EXPECT_NE(server_transport->server_transport(), nullptr);
  EXPECT_EQ(server_transport->GetTransportName(), "http2");

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
  LOG(INFO) << "TestHttp2ServerTransportObjectCreation End";
}

}
}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
