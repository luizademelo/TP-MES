
// Copyright 2018 gRPC authors.

#include <fcntl.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <grpc/support/time.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_builder.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <functional>
#include <set>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "gmock/gmock.h"
#include "src/core/credentials/transport/alts/alts_credentials.h"
#include "src/core/credentials/transport/alts/alts_security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/slice/slice_string_helpers.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "src/core/util/thd.h"
#include "src/core/util/useful.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/build.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/core/tsi/alts/fake_handshaker/fake_handshaker_server.h"

namespace {

void drain_cq(grpc_completion_queue* cq) {
  grpc_event ev;
  do {
    ev = grpc_completion_queue_next(
        cq, grpc_timeout_milliseconds_to_deadline(5000), nullptr);
  } while (ev.type != GRPC_QUEUE_SHUTDOWN);
}

grpc_channel* create_secure_channel_for_test(
    const char* server_addr, const char* fake_handshake_server_addr,
    int reconnect_backoff_ms) {
  grpc_alts_credentials_options* alts_options =
      grpc_alts_credentials_client_options_create();
  grpc_channel_credentials* channel_creds =
      grpc_alts_credentials_create_customized(alts_options,
                                              fake_handshake_server_addr,
                                              true );
  grpc_alts_credentials_options_destroy(alts_options);

  std::vector<grpc_arg> new_args;
  new_args.push_back(grpc_channel_arg_integer_create(
      const_cast<char*>(GRPC_ARG_USE_LOCAL_SUBCHANNEL_POOL), true));
  if (reconnect_backoff_ms != 0) {
    new_args.push_back(grpc_channel_arg_integer_create(
        const_cast<char*>("grpc.testing.fixed_reconnect_backoff_ms"),
        reconnect_backoff_ms));
  }
  grpc_channel_args* channel_args =
      grpc_channel_args_copy_and_add(nullptr, new_args.data(), new_args.size());
  grpc_channel* channel =
      grpc_channel_create(server_addr, channel_creds, channel_args);
  grpc_channel_args_destroy(channel_args);
  grpc_channel_credentials_release(channel_creds);
  return channel;
}

class FakeHandshakeServer {
 public:
  FakeHandshakeServer() {
    int port = grpc_pick_unused_port_or_die();
    address_ = grpc_core::JoinHostPort("localhost", port);
    service_ = grpc::gcp::CreateFakeHandshakerService("peer_identity");
    grpc::ServerBuilder builder;
    builder.AddListeningPort(address_, grpc::InsecureServerCredentials());
    builder.RegisterService(service_.get());

    server_ = builder.BuildAndStart();
    LOG(INFO) << "Fake handshaker server listening on " << address_;
  }

  ~FakeHandshakeServer() {
    server_->Shutdown(grpc_timeout_milliseconds_to_deadline(0));
  }

  const char* address() { return address_.c_str(); }

 private:
  std::string address_;
  std::unique_ptr<grpc::Service> service_;
  std::unique_ptr<grpc::Server> server_;
};

class TestServer {
 public:
  TestServer() {
    grpc_alts_credentials_options* alts_options =
        grpc_alts_credentials_server_options_create();
    grpc_server_credentials* server_creds =
        grpc_alts_server_credentials_create_customized(
            alts_options, fake_handshake_server_.address(),
            true );
    grpc_alts_credentials_options_destroy(alts_options);
    server_ = grpc_server_create(nullptr, nullptr);
    server_cq_ = grpc_completion_queue_create_for_next(nullptr);
    grpc_server_register_completion_queue(server_, server_cq_, nullptr);
    int port = grpc_pick_unused_port_or_die();
    server_addr_ = grpc_core::JoinHostPort("localhost", port);
    CHECK(grpc_server_add_http2_port(server_, server_addr_.c_str(),
                                     server_creds));
    grpc_server_credentials_release(server_creds);
    grpc_server_start(server_);
    VLOG(2) << "Start TestServer " << this << ". listen on " << server_addr_;
    server_thd_ = std::make_unique<std::thread>(PollUntilShutdown, this);
  }

  ~TestServer() {
    VLOG(2) << "Begin dtor of TestServer " << this;
    grpc_server_shutdown_and_notify(server_, server_cq_, this);
    server_thd_->join();
    grpc_server_destroy(server_);
    grpc_completion_queue_shutdown(server_cq_);
    drain_cq(server_cq_);
    grpc_completion_queue_destroy(server_cq_);
  }

  const char* address() { return server_addr_.c_str(); }

  static void PollUntilShutdown(const TestServer* self) {
    grpc_event ev = grpc_completion_queue_next(
        self->server_cq_, gpr_inf_future(GPR_CLOCK_REALTIME), nullptr);
    CHECK(ev.type == GRPC_OP_COMPLETE);
    CHECK(ev.tag == self);
    VLOG(2) << "TestServer " << self << " stop polling";
  }

 private:
  grpc_server* server_;
  grpc_completion_queue* server_cq_;
  std::unique_ptr<std::thread> server_thd_;
  std::string server_addr_;

  FakeHandshakeServer fake_handshake_server_;
};

class ConnectLoopRunner {
 public:
  explicit ConnectLoopRunner(
      const char* server_address, const char* fake_handshake_server_addr,
      int per_connect_deadline_seconds, size_t loops,
      grpc_connectivity_state expected_connectivity_states,
      int reconnect_backoff_ms)
      : server_address_(grpc_core::UniquePtr<char>(gpr_strdup(server_address))),
        fake_handshake_server_addr_(
            grpc_core::UniquePtr<char>(gpr_strdup(fake_handshake_server_addr))),
        per_connect_deadline_seconds_(per_connect_deadline_seconds),
        loops_(loops),
        expected_connectivity_states_(expected_connectivity_states),
        reconnect_backoff_ms_(reconnect_backoff_ms) {
    thd_ = std::make_unique<std::thread>(ConnectLoop, this);
  }

  ~ConnectLoopRunner() { thd_->join(); }

  static void ConnectLoop(const ConnectLoopRunner* self) {
    for (size_t i = 0; i < self->loops_; i++) {
      VLOG(2) << "runner:" << self << " connect_loop begin loop " << i;
      grpc_completion_queue* cq =
          grpc_completion_queue_create_for_next(nullptr);
      grpc_channel* channel = create_secure_channel_for_test(
          self->server_address_.get(), self->fake_handshake_server_addr_.get(),
          self->reconnect_backoff_ms_);

      grpc_connectivity_state state =
          grpc_channel_check_connectivity_state(channel, 1);
      ASSERT_EQ(state, GRPC_CHANNEL_IDLE);
      while (state != self->expected_connectivity_states_) {
        if (self->expected_connectivity_states_ ==
            GRPC_CHANNEL_TRANSIENT_FAILURE) {
          ASSERT_NE(state, GRPC_CHANNEL_READY);
        } else {
          ASSERT_EQ(self->expected_connectivity_states_, GRPC_CHANNEL_READY);
        }
        grpc_channel_watch_connectivity_state(
            channel, state, gpr_inf_future(GPR_CLOCK_REALTIME), cq, nullptr);
        grpc_event ev =
            grpc_completion_queue_next(cq,
                                       grpc_timeout_seconds_to_deadline(
                                           self->per_connect_deadline_seconds_),
                                       nullptr);
        ASSERT_EQ(ev.type, GRPC_OP_COMPLETE)
            << "connect_loop runner:" << std::hex << self
            << " got ev.type:" << ev.type << " i:" << i;
        ASSERT_TRUE(ev.success);
        grpc_connectivity_state prev_state = state;
        state = grpc_channel_check_connectivity_state(channel, 1);
        if (self->expected_connectivity_states_ ==
                GRPC_CHANNEL_TRANSIENT_FAILURE &&
            prev_state == GRPC_CHANNEL_CONNECTING &&
            state == GRPC_CHANNEL_CONNECTING) {

          break;
        }
      }
      grpc_channel_destroy(channel);
      grpc_completion_queue_shutdown(cq);
      drain_cq(cq);
      grpc_completion_queue_destroy(cq);
      VLOG(2) << "runner:" << self << " connect_loop finished loop " << i;
    }
  }

 private:
  grpc_core::UniquePtr<char> server_address_;
  grpc_core::UniquePtr<char> fake_handshake_server_addr_;
  int per_connect_deadline_seconds_;
  size_t loops_;
  grpc_connectivity_state expected_connectivity_states_;
  std::unique_ptr<std::thread> thd_;
  int reconnect_backoff_ms_;
};

TEST(AltsConcurrentConnectivityTest, TestBasicClientServerHandshakes) {
  FakeHandshakeServer fake_handshake_server;
  TestServer test_server;
  {
    ConnectLoopRunner runner(
        test_server.address(), fake_handshake_server.address(),
        10 * grpc_test_slowdown_factor() ,
        10 , GRPC_CHANNEL_READY ,
        0 );
  }
}

TEST(AltsConcurrentConnectivityTest, TestConcurrentClientServerHandshakes) {
  FakeHandshakeServer fake_handshake_server;

  {
    TestServer test_server;
    size_t num_concurrent_connects = 50;
    if (BuiltUnderMsan()) {
      num_concurrent_connects = 25;
    }
    std::vector<std::unique_ptr<ConnectLoopRunner>> connect_loop_runners;
    VLOG(2) << "start performing concurrent expected-to-succeed connects";
    for (size_t i = 0; i < num_concurrent_connects; i++) {
      connect_loop_runners.push_back(std::make_unique<ConnectLoopRunner>(
          test_server.address(), fake_handshake_server.address(),
          15 * grpc_test_slowdown_factor() ,
          5 , GRPC_CHANNEL_READY ,
          0 ));
    }
    connect_loop_runners.clear();
    VLOG(2) << "done performing concurrent expected-to-succeed connects";
  }
}

TEST(AltsConcurrentConnectivityTest,
     TestHandshakeFailsFastWhenPeerEndpointClosesConnectionAfterAccepting) {

  FakeHandshakeServer fake_handshake_server;

  grpc_core::testing::FakeUdpAndTcpServer fake_backend_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::
          CloseSocketUponReceivingBytesFromPeer);
  {
    std::vector<std::unique_ptr<ConnectLoopRunner>> connect_loop_runners;
    size_t num_concurrent_connects = 100;
    VLOG(2) << "start performing concurrent expected-to-fail connects";
    for (size_t i = 0; i < num_concurrent_connects; i++) {
      connect_loop_runners.push_back(std::make_unique<ConnectLoopRunner>(
          fake_backend_server.address(), fake_handshake_server.address(),
          10 * grpc_test_slowdown_factor() ,
          3 ,
          GRPC_CHANNEL_TRANSIENT_FAILURE ,
          0 ));
    }
    connect_loop_runners.clear();
    VLOG(2) << "done performing concurrent expected-to-fail connects";
  }
}

TEST(AltsConcurrentConnectivityTest,
     TestHandshakeFailsFastWhenHandshakeServerClosesConnectionAfterAccepting) {

  grpc_core::testing::FakeUdpAndTcpServer fake_handshake_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::kEagerlySendSettings,
      grpc_core::testing::FakeUdpAndTcpServer::
          CloseSocketUponReceivingBytesFromPeer);

  grpc_core::testing::FakeUdpAndTcpServer fake_backend_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  {
    std::vector<std::unique_ptr<ConnectLoopRunner>> connect_loop_runners;
    size_t num_concurrent_connects = 100;
    VLOG(2) << "start performing concurrent expected-to-fail connects";
    for (size_t i = 0; i < num_concurrent_connects; i++) {
      connect_loop_runners.push_back(std::make_unique<ConnectLoopRunner>(
          fake_backend_server.address(), fake_handshake_server.address(),
          20 * grpc_test_slowdown_factor() ,
          2 ,
          GRPC_CHANNEL_TRANSIENT_FAILURE ,
          0 ));
    }
    connect_loop_runners.clear();
    VLOG(2) << "done performing concurrent expected-to-fail connects";
  }
}

TEST(AltsConcurrentConnectivityTest,
     TestHandshakeFailsFastWhenHandshakeServerHangsAfterAccepting) {

  grpc_core::testing::FakeUdpAndTcpServer fake_handshake_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::kEagerlySendSettings,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);

  grpc_core::testing::FakeUdpAndTcpServer fake_backend_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  {
    std::vector<std::unique_ptr<ConnectLoopRunner>> connect_loop_runners;
    size_t num_concurrent_connects = 100;
    VLOG(2) << "start performing concurrent expected-to-fail connects";
    for (size_t i = 0; i < num_concurrent_connects; i++) {
      connect_loop_runners.push_back(std::make_unique<ConnectLoopRunner>(
          fake_backend_server.address(), fake_handshake_server.address(),
          10 * grpc_test_slowdown_factor() ,
          2 ,
          GRPC_CHANNEL_TRANSIENT_FAILURE ,
          100 ));
    }
    connect_loop_runners.clear();
    VLOG(2) << "done performing concurrent expected-to-fail connects";
  }
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
