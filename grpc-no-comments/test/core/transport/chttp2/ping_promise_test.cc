
// Copyright 2025 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/ping_promise.h"

#include "absl/log/log.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/promise/sleep.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "test/core/call/yodel/yodel_test.h"

namespace grpc_core {

using ::grpc_core::http2::PingInterface;
using ::grpc_core::http2::PingManager;
using ::testing::MockFunction;
using ::testing::StrictMock;
using ::testing::WithArgs;

class MockPingInterface : public PingInterface {
 public:
  MOCK_METHOD(Promise<absl::Status>, SendPing, (SendPingArgs args), (override));
  MOCK_METHOD(Promise<absl::Status>, TriggerWrite, (), (override));
  MOCK_METHOD(Promise<absl::Status>, PingTimeout, (), (override));

  void ExpectSendPing(SendPingArgs expected_args) {
    EXPECT_CALL(*this, SendPing)
        .WillOnce(WithArgs<0>([expected_args](SendPingArgs args) {
          EXPECT_EQ(expected_args.ack, args.ack);
          LOG(INFO) << "MockPingInterface SendPing Polled (ack: " << args.ack
                    << " opaque_data: " << args.opaque_data << ")."
                    << "Expected (ack: " << expected_args.ack << ")";
          return Immediate(absl::OkStatus());
        }));
  }
  void ExpectPingTimeout() {
    EXPECT_CALL(*this, PingTimeout).WillOnce(([]() {
      LOG(INFO) << "MockPingInterface PingTimeout Polled";
      return Immediate(absl::OkStatus());
    }));
  }
  void ExpectTriggerWrite() {
    EXPECT_CALL(*this, TriggerWrite).WillOnce(([]() {
      return Immediate(absl::OkStatus());
    }));
  }
  auto ExpectSendPingReturnArgs(SendPingArgs expected_args) {
    struct SendPingReturn {
      SendPingArgs args;
      Notification ready;
    };
    std::shared_ptr<SendPingReturn> send_ping_return =
        std::make_shared<SendPingReturn>();

    EXPECT_CALL(*this, SendPing)
        .WillOnce(WithArgs<0>([send_ping_return,
                               expected_args](SendPingArgs args) {
          LOG(INFO) << "MockPingInterface SendPing Polled (ack: " << args.ack
                    << " opaque_data: " << args.opaque_data << ")."
                    << "Expected (ack: " << expected_args.ack << ")";
          EXPECT_EQ(expected_args.ack, args.ack);
          send_ping_return->args = args;
          send_ping_return->ready.Notify();
          return Immediate(absl::OkStatus());
        }));
    return [send_ping_return] {
      send_ping_return->ready.WaitForNotification();
      return send_ping_return->args;
    };
  }
};

class PingManagerTest : public YodelTest {
 protected:
  using SendPingArgs = PingInterface::SendPingArgs;
  using YodelTest::YodelTest;

  Party* GetParty() { return party_.get(); }
  void InitParty() {
    auto general_party_arena = SimpleArenaAllocator(0)->MakeArena();
    general_party_arena
        ->SetContext<grpc_event_engine::experimental::EventEngine>(
            event_engine().get());
    party_ = Party::Make(std::move(general_party_arena));
  }

  ChannelArgs GetChannelArgs() {
    return CoreConfiguration::Get()
        .channel_args_preconditioning()
        .PreconditionChannelArgs(nullptr);
  }

 private:
  void InitCoreConfiguration() override {}
  void Shutdown() override { party_.reset(); }

  RefCountedPtr<Party> party_;
};
#define PING_SYSTEM_TEST(name) YODEL_TEST(PingManagerTest, name)

PING_SYSTEM_TEST(NoOp) {}

PING_SYSTEM_TEST(TestPingRequest) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  std::string execution_order;
  StrictMock<MockFunction<void(absl::Status)>> on_done;

  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  auto party = GetParty();
  EXPECT_EQ(ping_system.CountPingInflight(), 0);
  EXPECT_FALSE(ping_system.PingRequested());

  party->Spawn("PingRequest", ping_system.RequestPing([&execution_order]() {
    LOG(INFO) << "Ping requested. Waiting for ack.";
    execution_order.append("2");
  }),
               [&on_done](auto) {
                 LOG(INFO) << "Got a Ping Ack";
                 on_done.Call(absl::OkStatus());
               });

  EXPECT_TRUE(ping_system.PingRequested());
  execution_order.append("1");
  uint64_t id = ping_system.StartPing();
  EXPECT_EQ(ping_system.CountPingInflight(), 1);
  EXPECT_FALSE(ping_system.PingRequested());
  execution_order.append("3");

  party->Spawn("PingAckReceived",
               Map([&ping_system, id] { return ping_system.AckPing(id); },
                   [&execution_order, &ping_system](bool) {
                     execution_order.append("4");
                     EXPECT_EQ(ping_system.CountPingInflight(), 0);
                     return absl::OkStatus();
                   }),
               [](auto) { LOG(INFO) << "Reached PingAck end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();

  EXPECT_STREQ(execution_order.c_str(), "1234");
}

PING_SYSTEM_TEST(TestPingUnrelatedAck) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  std::string execution_order;
  StrictMock<MockFunction<void(absl::Status)>> on_done;

  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  auto party = GetParty();
  EXPECT_EQ(ping_system.CountPingInflight(), 0);
  EXPECT_FALSE(ping_system.PingRequested());

  party->Spawn("PingRequest", ping_system.RequestPing([&execution_order]() {
    LOG(INFO) << "Ping requested. Waiting for ack.";
    execution_order.append("2");
  }),
               [&on_done](auto) {
                 LOG(INFO) << "Got a Ping Ack";
                 on_done.Call(absl::OkStatus());
               });

  EXPECT_TRUE(ping_system.PingRequested());
  execution_order.append("1");
  uint64_t id = ping_system.StartPing();
  EXPECT_EQ(ping_system.CountPingInflight(), 1);
  EXPECT_FALSE(ping_system.PingRequested());
  execution_order.append("3");
  party->Spawn(
      "PingAckReceived",
      TrySeq(Map([&ping_system, id] { return ping_system.AckPing(id + 1); },
                 [&execution_order, &ping_system](bool) {
                   execution_order.append("4");
                   EXPECT_EQ(ping_system.CountPingInflight(), 1);
                   return absl::OkStatus();
                 }),
             Map([&ping_system, id] { return ping_system.AckPing(id); },
                 [&execution_order, &ping_system](bool) {
                   execution_order.append("5");
                   EXPECT_EQ(ping_system.CountPingInflight(), 0);
                   return absl::OkStatus();
                 })),
      [](auto) { LOG(INFO) << "Reached PingAck end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();

  EXPECT_STREQ(execution_order.c_str(), "12345");
}

PING_SYSTEM_TEST(TestPingWaitForAck) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  std::string execution_order;
  StrictMock<MockFunction<void(absl::Status)>> on_done;

  EXPECT_CALL(on_done, Call(absl::OkStatus()));
  auto party = GetParty();
  EXPECT_EQ(ping_system.CountPingInflight(), 0);
  EXPECT_FALSE(ping_system.PingRequested());

  party->Spawn("WaitForPingAck", ping_system.WaitForPingAck(),
               [&on_done, &execution_order](auto) {
                 LOG(INFO) << "Reached WaitForPingAck end";
                 execution_order.append("2");
                 on_done.Call(absl::OkStatus());
               });

  execution_order.append("1");
  EXPECT_TRUE(ping_system.PingRequested());
  uint64_t id = ping_system.StartPing();
  EXPECT_EQ(ping_system.CountPingInflight(), 1);
  EXPECT_FALSE(ping_system.PingRequested());
  execution_order.append("3");
  party->Spawn("PingAckReceived",
               Map([&ping_system, id] { return ping_system.AckPing(id); },
                   [&execution_order, &ping_system](bool) {
                     EXPECT_EQ(ping_system.CountPingInflight(), 0);
                     execution_order.append("4");
                     return absl::OkStatus();
                   }),
               [](auto) { LOG(INFO) << "Reached PingAckReceived end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();

  EXPECT_STREQ(execution_order.c_str(), "1342");
}

PING_SYSTEM_TEST(TestPingCancel) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());

  auto party = GetParty();
  EXPECT_EQ(ping_system.CountPingInflight(), 0);
  EXPECT_FALSE(ping_system.PingRequested());

  party->Spawn(
      "WaitForPingAck",
      TrySeq(ping_system.WaitForPingAck(), []() { Crash("Unreachable"); }),
      [](auto) { LOG(INFO) << "Reached WaitForPingAck end"; });

  EXPECT_TRUE(ping_system.PingRequested());
  ping_system.StartPing();
  EXPECT_EQ(ping_system.CountPingInflight(), 1);
  EXPECT_FALSE(ping_system.PingRequested());

  ping_system.CancelCallbacks();
  EXPECT_FALSE(ping_system.PingRequested());

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

PING_SYSTEM_TEST(TestPingManagerNoAck) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  ping_interface->ExpectSendPing(SendPingArgs{false,  1234});
  ping_interface->ExpectPingTimeout();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  auto party = GetParty();
  party->Spawn("PingRequest",
               TrySeq(ping_system.RequestPing([]() {
                 LOG(INFO) << "Ping requested. Waiting for ack.";
               }),
                      []() {
                        Crash("Unreachable");
                        return absl::OkStatus();
                      }),
               [](auto) { LOG(INFO) << "Received a Ping Ack"; });

  party->Spawn(
      "PingManager",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Seconds(100),
                                         Duration::Seconds(
                                             10));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

PING_SYSTEM_TEST(DISABLED_TestPingManagerDelayedPing) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  ping_interface->ExpectSendPing(SendPingArgs{false, 1234});
  ping_interface->ExpectPingTimeout();

  ping_interface->ExpectTriggerWrite();

  auto channel_args =
      GetChannelArgs().Set(GRPC_ARG_HTTP2_MAX_INFLIGHT_PINGS, 2);
  PingManager ping_system(channel_args, std::move(ping_interface),
                          event_engine());
  auto party = GetParty();

  party->Spawn(
      "PingRequest",
      TrySeq(ping_system.RequestPing([]() { LOG(INFO) << "Ping initiated"; }),
             []() {
               Crash("Unreachable");
               return absl::OkStatus();
             }),
      [](auto) { LOG(INFO) << "Reached PingRequest end"; });

  party->Spawn(
      "PingManager",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Hours(1),
                                         Duration::Seconds(
                                             100));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });

  party->Spawn(
      "PingRequest2",
      TrySeq(ping_system.RequestPing([]() { LOG(INFO) << "Ping initiated"; }),
             []() {
               Crash("Unreachable");
               return absl::OkStatus();
             }),
      [](auto) { LOG(INFO) << "Reached PingRequest end"; });

  party->Spawn(
      "PingManager2",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Hours(1),
                                         Duration::Seconds(
                                             100));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });
  party->Spawn(
      "PingManager3",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Hours(1),
                                         Duration::Seconds(
                                             100));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

PING_SYSTEM_TEST(TestPingManagerAck) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  auto cb = ping_interface->ExpectSendPingReturnArgs(SendPingArgs{false, 1234});

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  auto party = GetParty();

  party->Spawn("PingRequest",
               TrySeq(ping_system.RequestPing([]() {
                 LOG(INFO) << "Ping requested. Waiting for ack.";
               }),
                      []() { return absl::OkStatus(); }),
               [](auto) { LOG(INFO) << "Reached PingRequest end"; });

  party->Spawn(
      "PingManager",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Seconds(100),

                                         Duration::Hours(1));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });

  party->Spawn("PingAckReceived",
               TrySeq(Sleep(Duration::Seconds(1)),
                      Map(
                          [&ping_system, &cb] {
                            auto args = cb();
                            return ping_system.AckPing(args.opaque_data);
                          },
                          [](bool) { return absl::OkStatus(); })),
               [](auto) { LOG(INFO) << "Reached PingAckReceived end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

PING_SYSTEM_TEST(TestPingManagerDelayedAck) {

  InitParty();
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  auto cb = ping_interface->ExpectSendPingReturnArgs(SendPingArgs{false, 1234});
  ping_interface->ExpectPingTimeout();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  auto party = GetParty();
  party->Spawn("PingRequest",
               TrySeq(ping_system.RequestPing([]() {
                 LOG(INFO) << "Ping requested. Waiting for ack.";
               }),
                      []() { return absl::OkStatus(); }),
               [](auto) { LOG(INFO) << "Reached PingRequest end"; });

  party->Spawn(
      "PingManager",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Seconds(100),
                                         Duration::Seconds(2));
      },
      [](auto) { LOG(INFO) << "Reached PingManager end"; });

  party->Spawn("DelayedPingAckReceived",
               TrySeq(Sleep(Duration::Hours(1)),
                      Map(
                          [&ping_system, &cb] {
                            auto args = cb();
                            return ping_system.AckPing(args.opaque_data);
                          },
                          [](bool) { return absl::OkStatus(); })),
               [](auto) { LOG(INFO) << "Reached PingAckReceived end"; });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

PING_SYSTEM_TEST(TestPingManagerNoPingRequest) {

  InitParty();
  StrictMock<MockFunction<void(absl::Status)>> on_done;
  std::unique_ptr<StrictMock<MockPingInterface>> ping_interface =
      std::make_unique<StrictMock<MockPingInterface>>();

  PingManager ping_system(GetChannelArgs(), std::move(ping_interface),
                          event_engine());
  auto party = GetParty();
  EXPECT_CALL(on_done, Call(absl::OkStatus()));

  party->Spawn(
      "PingManager",
      [&ping_system] {
        return ping_system.MaybeSendPing(
                                         Duration::Seconds(100),
                                         Duration::Seconds(2));
      },
      [&on_done](auto) {
        on_done.Call(absl::OkStatus());
        LOG(INFO) << "Reached PingManager end";
      });

  WaitForAllPendingWork();
  event_engine()->TickUntilIdle();
  event_engine()->UnsetGlobalHooks();
}

}
