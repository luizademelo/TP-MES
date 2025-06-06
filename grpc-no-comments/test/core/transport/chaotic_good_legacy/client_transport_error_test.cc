// Copyright 2023 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <grpc/event_engine/memory_allocator.h>
#include <grpc/event_engine/slice.h>
#include <grpc/event_engine/slice_buffer.h>
#include <grpc/grpc.h>
#include <grpc/status.h>
#include <stddef.h>

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/chaotic_good_legacy/client_transport.h"
#include "src/core/lib/event_engine/event_engine_context.h"
#include "src/core/lib/iomgr/timer_manager.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/event_engine_wakeup_scheduler.h"
#include "src/core/lib/promise/if.h"
#include "src/core/lib/promise/join.h"
#include "src/core/lib/promise/loop.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/resource_quota/memory_quota.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.h"
#include "test/core/event_engine/fuzzing_event_engine/fuzzing_event_engine.pb.h"

using testing::AtMost;
using testing::MockFunction;
using testing::Return;
using testing::StrictMock;
using testing::WithArgs;

namespace grpc_core {
namespace chaotic_good_legacy {
namespace testing {

class MockEndpoint
    : public grpc_event_engine::experimental::EventEngine::Endpoint {
 public:
  MOCK_METHOD(
      bool, Read,
      (absl::AnyInvocable<void(absl::Status)> on_read,
       grpc_event_engine::experimental::SliceBuffer* buffer,
       grpc_event_engine::experimental::EventEngine::Endpoint::ReadArgs args),
      (override));

  MOCK_METHOD(
      bool, Write,
      (absl::AnyInvocable<void(absl::Status)> on_writable,
       grpc_event_engine::experimental::SliceBuffer* data,
       grpc_event_engine::experimental::EventEngine::Endpoint::WriteArgs args),
      (override));

  MOCK_METHOD(
      const grpc_event_engine::experimental::EventEngine::ResolvedAddress&,
      GetPeerAddress, (), (const, override));
  MOCK_METHOD(
      const grpc_event_engine::experimental::EventEngine::ResolvedAddress&,
      GetLocalAddress, (), (const, override));

  MOCK_METHOD(std::vector<size_t>, AllWriteMetrics, (), (override));
  MOCK_METHOD(std::optional<absl::string_view>, GetMetricName, (size_t key),
              (override));
  MOCK_METHOD(std::optional<size_t>, GetMetricKey, (absl::string_view name),
              (override));
};

class MockClientConnectionFactory : public ClientConnectionFactory {
 public:
  MOCK_METHOD(PendingConnection, Connect, (absl::string_view), (override));
  void Orphaned() final {}
};

struct MockPromiseEndpoint {
  StrictMock<MockEndpoint>* endpoint = new StrictMock<MockEndpoint>();
  PromiseEndpoint promise_endpoint{
      std::unique_ptr<StrictMock<MockEndpoint>>(endpoint), SliceBuffer()};
};

auto SendClientToServerMessages(CallInitiator initiator, int num_messages) {
  return Loop([initiator, num_messages]() mutable {
    bool has_message = (num_messages > 0);
    return If(
        has_message,
        [initiator, &num_messages]() mutable {
          return Seq(initiator.PushMessage(Arena::MakePooled<Message>()),
                     [&num_messages]() -> LoopCtl<absl::Status> {
                       --num_messages;
                       return Continue();
                     });
        },
        [initiator]() mutable -> LoopCtl<absl::Status> {
          initiator.FinishSends();
          return absl::OkStatus();
        });
  });
}

ClientMetadataHandle TestInitialMetadata() {
  auto md = Arena::MakePooledForOverwrite<ClientMetadata>();
  md->Set(HttpPathMetadata(), Slice::FromStaticString("/test"));
  return md;
}

class ClientTransportTest : public ::testing::Test {
 protected:
  const std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>&
  event_engine() {
    return event_engine_;
  }

  ChannelArgs MakeChannelArgs() {
    return CoreConfiguration::Get()
        .channel_args_preconditioning()
        .PreconditionChannelArgs(nullptr);
  }

  template <typename... PromiseEndpoints>
  Config MakeConfig(PromiseEndpoints... promise_endpoints) {
    Config config(MakeChannelArgs());
    auto name_endpoint = [i = 0]() mutable { return absl::StrCat(++i); };
    std::vector<int> this_is_only_here_to_unpack_the_following_statement{
        (config.ServerAddPendingDataEndpoint(ImmediateConnection(
             name_endpoint(), std::move(promise_endpoints))),
         0)...};
    return config;
  }

  auto MakeCall(ClientMetadataHandle client_initial_metadata) {
    auto arena = call_arena_allocator_->MakeArena();
    arena->SetContext<grpc_event_engine::experimental::EventEngine>(
        event_engine_.get());
    return MakeCallPair(std::move(client_initial_metadata), std::move(arena));
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::FuzzingEventEngine>
      event_engine_{
          std::make_shared<grpc_event_engine::experimental::FuzzingEventEngine>(
              []() {
                grpc_timer_manager_set_threading(false);
                grpc_event_engine::experimental::FuzzingEventEngine::Options
                    options;
                return options;
              }(),
              fuzzing_event_engine::Actions())};
  RefCountedPtr<CallArenaAllocator> call_arena_allocator_{
      MakeRefCounted<CallArenaAllocator>(
          MakeResourceQuota("test-quota")
              ->memory_quota()
              ->CreateMemoryAllocator("test-allocator"),
          1024)};
};

TEST_F(ClientTransportTest, AddOneStreamWithWriteFailed) {
  MockPromiseEndpoint control_endpoint;
  MockPromiseEndpoint data_endpoint;
  auto client_connection_factory =
      MakeRefCounted<StrictMock<MockClientConnectionFactory>>();

  EXPECT_CALL(*control_endpoint.endpoint, Write)
      .Times(AtMost(1))
      .WillOnce(
          WithArgs<0>([](absl::AnyInvocable<void(absl::Status)> on_write) {
            on_write(absl::InternalError("control endpoint write failed."));
            return false;
          }));
  EXPECT_CALL(*data_endpoint.endpoint, Write)
      .Times(AtMost(1))
      .WillOnce(
          WithArgs<0>([](absl::AnyInvocable<void(absl::Status)> on_write) {
            on_write(absl::InternalError("data endpoint write failed."));
            return false;
          }));
  EXPECT_CALL(*control_endpoint.endpoint, Read).WillOnce(Return(false));
  auto transport = MakeOrphanable<ChaoticGoodClientTransport>(
      MakeChannelArgs(), std::move(control_endpoint.promise_endpoint),
      MakeConfig(std::move(data_endpoint.promise_endpoint)),
      client_connection_factory);
  auto call = MakeCall(TestInitialMetadata());
  transport->StartCall(call.handler.StartCall());
  call.initiator.SpawnGuarded("test-send",
                              [initiator = call.initiator]() mutable {
                                return SendClientToServerMessages(initiator, 1);
                              });
  StrictMock<MockFunction<void()>> on_done;
  EXPECT_CALL(on_done, Call());
  call.initiator.SpawnInfallible(
      "test-read", [&on_done, initiator = call.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done.Call();
            });
      });

  event_engine()->TickUntilIdle();
  transport.reset();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(ClientTransportTest, AddOneStreamWithReadFailed) {
  MockPromiseEndpoint control_endpoint;
  MockPromiseEndpoint data_endpoint;
  auto client_connection_factory =
      MakeRefCounted<StrictMock<MockClientConnectionFactory>>();

  EXPECT_CALL(*control_endpoint.endpoint, Read)
      .WillOnce(WithArgs<0>(
          [](absl::AnyInvocable<void(absl::Status)> on_read) mutable {
            on_read(absl::InternalError("control endpoint read failed."));

            return false;
          }));
  auto transport = MakeOrphanable<ChaoticGoodClientTransport>(
      MakeChannelArgs(), std::move(control_endpoint.promise_endpoint),
      MakeConfig(std::move(data_endpoint.promise_endpoint)),
      client_connection_factory);
  auto call = MakeCall(TestInitialMetadata());
  transport->StartCall(call.handler.StartCall());
  call.initiator.SpawnGuarded("test-send",
                              [initiator = call.initiator]() mutable {
                                return SendClientToServerMessages(initiator, 1);
                              });
  StrictMock<MockFunction<void()>> on_done;
  EXPECT_CALL(on_done, Call());
  call.initiator.SpawnInfallible(
      "test-read", [&on_done, initiator = call.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done.Call();
            });
      });

  event_engine()->TickUntilIdle();
  transport.reset();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(ClientTransportTest, AddMultipleStreamWithWriteFailed) {

  MockPromiseEndpoint control_endpoint;
  MockPromiseEndpoint data_endpoint;
  auto client_connection_factory =
      MakeRefCounted<StrictMock<MockClientConnectionFactory>>();
  EXPECT_CALL(*control_endpoint.endpoint, Write)
      .Times(AtMost(1))
      .WillRepeatedly(
          WithArgs<0>([](absl::AnyInvocable<void(absl::Status)> on_write) {
            on_write(absl::InternalError("control endpoint write failed."));
            return false;
          }));
  EXPECT_CALL(*data_endpoint.endpoint, Write)
      .Times(AtMost(1))
      .WillRepeatedly(
          WithArgs<0>([](absl::AnyInvocable<void(absl::Status)> on_write) {
            on_write(absl::InternalError("data endpoint write failed."));
            return false;
          }));
  EXPECT_CALL(*control_endpoint.endpoint, Read).WillOnce(Return(false));
  auto transport = MakeOrphanable<ChaoticGoodClientTransport>(
      MakeChannelArgs(), std::move(control_endpoint.promise_endpoint),
      MakeConfig(std::move(data_endpoint.promise_endpoint)),
      client_connection_factory);
  auto call1 = MakeCall(TestInitialMetadata());
  transport->StartCall(call1.handler.StartCall());
  auto call2 = MakeCall(TestInitialMetadata());
  transport->StartCall(call2.handler.StartCall());
  call1.initiator.SpawnGuarded(
      "test-send-1", [initiator = call1.initiator]() mutable {
        return SendClientToServerMessages(initiator, 1);
      });
  call2.initiator.SpawnGuarded(
      "test-send-2", [initiator = call2.initiator]() mutable {
        return SendClientToServerMessages(initiator, 1);
      });
  StrictMock<MockFunction<void()>> on_done1;
  EXPECT_CALL(on_done1, Call());
  StrictMock<MockFunction<void()>> on_done2;
  EXPECT_CALL(on_done2, Call());
  call1.initiator.SpawnInfallible(
      "test-read-1", [&on_done1, initiator = call1.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done1](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done1.Call();
            });
      });
  call2.initiator.SpawnInfallible(
      "test-read-2", [&on_done2, initiator = call2.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done2](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done2.Call();
            });
      });

  event_engine()->TickUntilIdle();
  transport.reset();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

TEST_F(ClientTransportTest, AddMultipleStreamWithReadFailed) {
  MockPromiseEndpoint control_endpoint;
  MockPromiseEndpoint data_endpoint;
  auto client_connection_factory =
      MakeRefCounted<StrictMock<MockClientConnectionFactory>>();

  EXPECT_CALL(*control_endpoint.endpoint, Read)
      .WillOnce(WithArgs<0>(
          [](absl::AnyInvocable<void(absl::Status)> on_read) mutable {
            on_read(absl::InternalError("control endpoint read failed."));

            return false;
          }));
  auto transport = MakeOrphanable<ChaoticGoodClientTransport>(
      MakeChannelArgs(), std::move(control_endpoint.promise_endpoint),
      MakeConfig(std::move(data_endpoint.promise_endpoint)),
      client_connection_factory);
  auto call1 = MakeCall(TestInitialMetadata());
  transport->StartCall(call1.handler.StartCall());
  auto call2 = MakeCall(TestInitialMetadata());
  transport->StartCall(call2.handler.StartCall());
  call1.initiator.SpawnGuarded(
      "test-send", [initiator = call1.initiator]() mutable {
        return SendClientToServerMessages(initiator, 1);
      });
  call2.initiator.SpawnGuarded(
      "test-send", [initiator = call2.initiator]() mutable {
        return SendClientToServerMessages(initiator, 1);
      });
  StrictMock<MockFunction<void()>> on_done1;
  EXPECT_CALL(on_done1, Call());
  StrictMock<MockFunction<void()>> on_done2;
  EXPECT_CALL(on_done2, Call());
  call1.initiator.SpawnInfallible(
      "test-read", [&on_done1, initiator = call1.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done1](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done1.Call();
            });
      });
  call2.initiator.SpawnInfallible(
      "test-read", [&on_done2, initiator = call2.initiator]() mutable {
        return Seq(
            initiator.PullServerInitialMetadata(),
            [](ValueOrFailure<std::optional<ServerMetadataHandle>> md) {
              EXPECT_TRUE(md.ok());
            },
            initiator.PullServerTrailingMetadata(),
            [&on_done2](ServerMetadataHandle md) {
              EXPECT_EQ(md->get(GrpcStatusMetadata()).value(),
                        GRPC_STATUS_UNAVAILABLE);
              on_done2.Call();
            });
      });

  event_engine()->TickUntilIdle();
  transport.reset();
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
