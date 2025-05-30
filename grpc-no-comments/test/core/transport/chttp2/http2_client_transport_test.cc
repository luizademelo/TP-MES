
// Copyright 2024 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/http2_client_transport.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/slice.h>
#include <grpc/grpc.h>

#include <memory>
#include <utility>

#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chttp2/transport/http2_status.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/util/orphanable.h"
#include "test/core/promise/poll_matcher.h"
#include "test/core/transport/chttp2/http2_frame_test_helper.h"
#include "test/core/transport/util/mock_promise_endpoint.h"
#include "test/core/transport/util/transport_test.h"

namespace grpc_core {
namespace http2 {
namespace testing {

using EventEngineSlice = grpc_event_engine::experimental::Slice;
using ::testing::MockFunction;
using ::testing::StrictMock;
using transport::testing::Http2FrameTestHelper;
using util::testing::MockPromiseEndpoint;
using util::testing::TransportTest;

static uint64_t Read8b(const uint8_t* input) {
  return static_cast<uint64_t>(input[0]) << 56 |
         static_cast<uint64_t>(input[1]) << 48 |
         static_cast<uint64_t>(input[2]) << 40 |
         static_cast<uint64_t>(input[3]) << 32 |
         static_cast<uint64_t>(input[4]) << 24 |
         static_cast<uint64_t>(input[5]) << 16 |
         static_cast<uint64_t>(input[6]) << 8 | static_cast<uint64_t>(input[7]);
}

static ClientMetadataHandle TestInitialMetadata() {
  auto md = Arena::MakePooledForOverwrite<ClientMetadata>();
  md->Set(HttpPathMetadata(), Slice::FromStaticString("/demo.Service/Step"));
  return md;
}

static const std::vector<uint8_t> kPathDemoServiceStep = {
    0x40, 0x05, 0x3a, 0x70, 0x61, 0x74, 0x68, 0x12, 0x2f,
    0x64, 0x65, 0x6d, 0x6f, 0x2e, 0x53, 0x65, 0x72, 0x76,
    0x69, 0x63, 0x65, 0x2f, 0x53, 0x74, 0x65, 0x70};

class Http2ClientTransportTest : public TransportTest {
 public:
  Http2ClientTransportTest() {
    grpc_tracer_set_enabled("http2_ph2_transport", true);
  }

 protected:
  Http2FrameTestHelper helper_;
};

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportObjectCreation) {

  LOG(INFO) << "TestHttp2ClientTransportObjectCreation Begin";
  MockPromiseEndpoint mock_endpoint(1000);

  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());

  mock_endpoint.ExpectRead(
      {helper_.EventEngineSliceFromHttp2DataFrame(
           "Hello!", 9, false),
       helper_.EventEngineSliceFromHttp2DataFrame(
           "Bye!", 11, true)},
      event_engine().get());

  mock_endpoint.ExpectReadClose(absl::UnavailableError("Connection closed"),
                                event_engine().get());

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());

  EXPECT_EQ(client_transport->filter_stack_transport(), nullptr);
  EXPECT_NE(client_transport->client_transport(), nullptr);
  EXPECT_EQ(client_transport->server_transport(), nullptr);
  EXPECT_EQ(client_transport->GetTransportName(), "http2");

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
  LOG(INFO) << "TestHttp2ClientTransportObjectCreation End";
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportWriteFromQueue) {
  MockPromiseEndpoint mock_endpoint(1000);

  auto read = mock_endpoint.ExpectDelayedReadClose(
      absl::UnavailableError("Connection closed"), event_engine().get());

  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());
  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2DataFrame(
              "Hello!", 9, false),
      },
      event_engine().get());

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());

  Http2Frame frame = Http2DataFrame{
      .stream_id = 9,
      .end_stream = false,
      .payload = SliceBuffer(Slice::FromExternalString("Hello!"))};

  auto promise =
      client_transport->TestOnlyEnqueueOutgoingFrame(std::move(frame));
  EXPECT_THAT(promise(), IsReady());
  read();

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportWriteFromCall) {
  MockPromiseEndpoint mock_endpoint(1000);
  SliceBuffer grpc_header;
  std::string data_payload = "Hello!";
  AppendGrpcHeaderToSliceBuffer(grpc_header, 0, data_payload.size());

  mock_endpoint.ExpectReadClose(absl::UnavailableError("Connection closed"),
                                event_engine().get());

  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());

  mock_endpoint.ExpectWrite(
      {helper_.EventEngineSliceFromHttp2HeaderFrame(std::string(
           kPathDemoServiceStep.begin(), kPathDemoServiceStep.end())),
       helper_.EventEngineSliceFromHttp2DataFrame(
           (grpc_header.JoinIntoString() + data_payload),
           1, false),
       helper_.EventEngineSliceFromHttp2DataFrame(
           "", 1, true)},
      event_engine().get());

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());
  auto call = MakeCall(TestInitialMetadata());
  client_transport->StartCall(call.handler.StartCall());

  StrictMock<MockFunction<void()>> on_done;
  EXPECT_CALL(on_done, Call());

  call.initiator.SpawnGuarded("test-send", [initiator =
                                                call.initiator]() mutable {
    return Seq(
        initiator.PushMessage(Arena::MakePooled<Message>(
            SliceBuffer(Slice::FromExternalString("Hello!")), 0)),
        [initiator = initiator]() mutable { return initiator.FinishSends(); },
        [initiator]() mutable {
          return initiator.Cancel(absl::CancelledError("Cancelled"));
        },
        []() { return absl::OkStatus(); });
  });
  call.initiator.SpawnInfallible(
      "test-wait", [initator = call.initiator, &on_done]() mutable {
        return Seq(initator.PullServerTrailingMetadata(),
                   [&on_done](ServerMetadataHandle metadata) {
                     on_done.Call();
                     return Empty{};
                   });
      });

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportPingRead) {

  MockPromiseEndpoint mock_endpoint(1000);

  mock_endpoint.ExpectRead(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(false,
                                                     1234),
      },
      event_engine().get());

  mock_endpoint.ExpectReadClose(absl::UnavailableError("Connection closed"),
                                event_engine().get());

  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());
  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(true,
                                                     1234),
      },
      event_engine().get());

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportPingWrite) {

  MockPromiseEndpoint mock_endpoint(1000);
  StrictMock<MockFunction<void()>> ping_ack_received;
  EXPECT_CALL(ping_ack_received, Call());

  auto read_cb = mock_endpoint.ExpectDelayedRead(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(true,
                                                     1234),
      },
      event_engine().get());
  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());
  mock_endpoint.ExpectWriteWithCallback(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(false,
                                                     0),
      },
      event_engine().get(),
      [&mock_endpoint, &read_cb, this](SliceBuffer& out, SliceBuffer& expect) {
        char out_buffer[kFrameHeaderSize + 1] = {};
        char expect_buffer[kFrameHeaderSize + 1] = {};
        out.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, out_buffer);
        expect.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, expect_buffer);
        EXPECT_STREQ(out_buffer, expect_buffer);

        auto mutable_slice = out.JoinIntoSlice().TakeMutable();
        uint8_t* opaque_id_ptr = mutable_slice.data();
        uint64_t opaque_id = Read8b(opaque_id_ptr + kFrameHeaderSize);

        read_cb();

        mock_endpoint.ExpectRead(
            {
                helper_.EventEngineSliceFromHttp2PingFrame(
                    true,
                    opaque_id),
            },
            event_engine().get());

        mock_endpoint.ExpectReadClose(
            absl::UnavailableError("Connection closed"), event_engine().get());
      });

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());
  client_transport->TestOnlySpawnPromise(
      "PingRequest", [&client_transport, &ping_ack_received] {
        return Map(TrySeq(client_transport->TestOnlyEnqueueOutgoingFrame(
                              Http2EmptyFrame{}),
                          [&client_transport] {
                            return client_transport->TestOnlySendPing([] {});
                          }),
                   [&ping_ack_received](auto) {
                     ping_ack_received.Call();
                     LOG(INFO) << "PingAck Received. Ping Test done.";
                   });
      });
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportPingTimeout) {

  MockPromiseEndpoint mock_endpoint(1000);
  StrictMock<MockFunction<void()>> ping_ack_received;

  mock_endpoint.ExpectReadClose(absl::UnavailableError("Connection closed"),
                                event_engine().get());
  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());
  mock_endpoint.ExpectWriteWithCallback(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(false,
                                                     0),
      },
      event_engine().get(), [](SliceBuffer& out, SliceBuffer& expect) {
        char out_buffer[kFrameHeaderSize];
        out.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, out_buffer);
        char expect_buffer[kFrameHeaderSize];
        expect.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, expect_buffer);

        EXPECT_STREQ(out_buffer, expect_buffer);
      });

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint), GetChannelArgs(),
      event_engine());
  client_transport->TestOnlySpawnPromise("PingRequest", [&client_transport] {
    return Map(TrySeq(client_transport->TestOnlyEnqueueOutgoingFrame(
                          Http2EmptyFrame{}),
                      [&client_transport] {
                        return client_transport->TestOnlySendPing([] {});
                      }),
               [](auto) { Crash("Unreachable"); });
  });

  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(Http2ClientTransportTest, TestHttp2ClientTransportMultiplePings) {

  MockPromiseEndpoint mock_endpoint(1000);
  StrictMock<MockFunction<void()>> ping_ack_received;
  EXPECT_CALL(ping_ack_received, Call());
  auto ping_complete = std::make_shared<Latch<void>>();

  auto read_cb = mock_endpoint.ExpectDelayedRead(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(true,
                                                     1234),
      },
      event_engine().get());

  mock_endpoint.ExpectWrite(
      {
          helper_.EventEngineSliceFromHttp2SettingsFrame({{4, 65535}}),
      },
      event_engine().get());
  mock_endpoint.ExpectWriteWithCallback(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(false,
                                                     0),
      },
      event_engine().get(),
      [&mock_endpoint, &read_cb, this](SliceBuffer& out, SliceBuffer& expect) {
        char out_buffer[kFrameHeaderSize + 1] = {};
        char expect_buffer[kFrameHeaderSize + 1] = {};
        out.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, out_buffer);
        expect.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, expect_buffer);
        EXPECT_STREQ(out_buffer, expect_buffer);

        auto mutable_slice = out.JoinIntoSlice().TakeMutable();
        auto* opaque_id_ptr = mutable_slice.data();
        uint64_t opaque_id = Read8b(opaque_id_ptr + kFrameHeaderSize);

        read_cb();
        mock_endpoint.ExpectRead(
            {
                helper_.EventEngineSliceFromHttp2PingFrame(
                    true,
                    opaque_id),
            },
            event_engine().get());

        mock_endpoint.ExpectReadClose(
            absl::UnavailableError("Connection closed"), event_engine().get());
      });

  mock_endpoint.ExpectWriteWithCallback(
      {
          helper_.EventEngineSliceFromHttp2PingFrame(false,
                                                     0),
      },
      event_engine().get(),
      [event_engine = event_engine().get()](SliceBuffer& out,
                                            SliceBuffer& expect) {
        char out_buffer[kFrameHeaderSize];
        out.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, out_buffer);
        char expect_buffer[kFrameHeaderSize];
        expect.CopyFirstNBytesIntoBuffer(kFrameHeaderSize, expect_buffer);

        EXPECT_STREQ(out_buffer, expect_buffer);
      });

  auto client_transport = MakeOrphanable<Http2ClientTransport>(
      std::move(mock_endpoint.promise_endpoint),
      GetChannelArgs().Set(GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS, 2),
      event_engine());

  client_transport->TestOnlySpawnPromise(
      "PingRequest", [&client_transport, &ping_ack_received, ping_complete] {
        return Map(TrySeq(
                       client_transport->TestOnlyEnqueueOutgoingFrame(
                           Http2EmptyFrame{}),
                       [&client_transport] {
                         return client_transport->TestOnlySendPing([] {});
                       },
                       [ping_complete]() { ping_complete->Set(); }),
                   [&ping_ack_received](auto) {
                     ping_ack_received.Call();
                     LOG(INFO) << "PingAck Received. Ping Test done.";
                   });
      });
  client_transport->TestOnlySpawnPromise(
      "PingRequest", [&client_transport, ping_complete] {
        return Map(TrySeq(
                       ping_complete->Wait(),
                       [&client_transport] {
                         return client_transport->TestOnlyEnqueueOutgoingFrame(
                             Http2EmptyFrame{});
                       },
                       [&client_transport] {
                         return client_transport->TestOnlySendPing([] {});
                       }),
                   [](auto) { Crash("Unreachable"); });
      });
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
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
