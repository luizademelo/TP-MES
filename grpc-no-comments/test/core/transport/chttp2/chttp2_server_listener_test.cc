
// Copyright 2024 gRPC authors.

#include <grpc/grpc.h>

#include <thread>

#include "absl/synchronization/notification.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/insecure/insecure_credentials.h"
#include "src/core/credentials/transport/tls/grpc_tls_credentials_options.h"
#include "src/core/credentials/transport/tls/tls_credentials.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/ext/transport/chttp2/server/chttp2_server.h"
#include "src/core/server/server.h"
#include "src/core/util/host_port.h"
#include "test/core/end2end/cq_verifier.h"
#include "test/core/test_util/mock_endpoint.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/core/test_util/tls_utils.h"

using grpc_event_engine::experimental::EventEngine;

namespace grpc_core {
namespace testing {

class Chttp2ServerListenerTestPeer {
 public:
  explicit Chttp2ServerListenerTestPeer(NewChttp2ServerListener* listener)
      : listener_(listener) {}

  static OrphanablePtr<NewChttp2ServerListener> MakeListener(
      const ChannelArgs& args) {
    return MakeOrphanable<NewChttp2ServerListener>(args);
  }

  void OnAccept(grpc_endpoint* tcp, grpc_pollset* accepting_pollset,
                grpc_tcp_server_acceptor* server_acceptor) {
    NewChttp2ServerListener::OnAccept(listener_, tcp, accepting_pollset,
                                      server_acceptor);
  }

  RefCountedPtr<NewChttp2ServerListener> Ref() {
    return listener_->RefAsSubclass<NewChttp2ServerListener>();
  }

 private:
  NewChttp2ServerListener* listener_;
};

class ActiveConnectionTestPeer {
 public:
  explicit ActiveConnectionTestPeer(
      NewChttp2ServerListener::ActiveConnection* connection)
      : connection_(connection) {}

  void OnClose() {
    NewChttp2ServerListener::ActiveConnection::OnClose(connection_,
                                                       absl::OkStatus());
  }

  NewChttp2ServerListener::ActiveConnection::HandshakingState*
  handshaking_state() {
    absl::Notification notification;
    NewChttp2ServerListener::ActiveConnection::HandshakingState*
        handshaking_state = nullptr;
    connection_->work_serializer_.Run(
        [&]() {
          handshaking_state = std::get<OrphanablePtr<
              NewChttp2ServerListener::ActiveConnection::HandshakingState>>(
                                  connection_->state_)
                                  .get();
          notification.Notify();
        },
        DEBUG_LOCATION);
    notification.WaitForNotificationWithTimeout(absl::Seconds(5) *
                                                grpc_test_slowdown_factor());
    return handshaking_state;
  }

 private:
  NewChttp2ServerListener::ActiveConnection* connection_;
};

class HandshakingStateTestPeer {
 public:
  explicit HandshakingStateTestPeer(
      NewChttp2ServerListener::ActiveConnection::HandshakingState*
          handshaking_state)
      : handshaking_state_(handshaking_state) {}

  RefCountedPtr<NewChttp2ServerListener::ActiveConnection::HandshakingState>
  Ref() {
    return handshaking_state_->Ref();
  }

  bool WaitForSettingsFrame() {
    absl::Notification settings_received_notification;
    absl::Time deadline =
        absl::Now() + absl::Seconds(5) * grpc_test_slowdown_factor();

    do {
      absl::Notification callback_done;
      handshaking_state_->connection_->work_serializer_.Run(
          [&]() {
            if (!handshaking_state_->timer_handle_.has_value()) {
              settings_received_notification.Notify();
            }
            callback_done.Notify();
          },
          DEBUG_LOCATION);
      if (!callback_done.WaitForNotificationWithDeadline(deadline)) {
        break;
      }
    } while (!settings_received_notification.HasBeenNotified() &&
             absl::Now() < deadline);
    return settings_received_notification.HasBeenNotified();
  }

 private:
  NewChttp2ServerListener::ActiveConnection::HandshakingState*
      handshaking_state_;
};

class ServerTestPeer {
 public:
  explicit ServerTestPeer(Server* server) : server_(server) {}

  const std::list<RefCountedPtr<Server::ListenerState>>& listener_states()
      const {
    return server_->listener_states_;
  }

 private:
  Server* server_;
};

class ListenerStateTestPeer {
 public:
  explicit ListenerStateTestPeer(Server::ListenerState* listener_state)
      : listener_state_(listener_state) {}

  size_t ConnectionsSize() {
    MutexLock lock(&listener_state_->mu_);
    return listener_state_->connections_.size();
  }

 private:
  Server::ListenerState* listener_state_;
};

namespace {

class Chttp2ServerListenerTest : public ::testing::Test {
 protected:
  void SetUpServer(const RefCountedPtr<grpc_server_credentials>& creds =
                       MakeRefCounted<InsecureServerCredentials>()) {
    args_ = CoreConfiguration::Get()
                .channel_args_preconditioning()
                .PreconditionChannelArgs(nullptr);
    server_ = MakeOrphanable<Server>(args_);
    grpc_server_add_http2_port(
        server_->c_ptr(),
        JoinHostPort("localhost", grpc_pick_unused_port_or_die()).c_str(),
        creds.get());
    cq_ = grpc_completion_queue_create_for_next(nullptr);
    server_->RegisterCompletionQueue(cq_);
    grpc_server_start(server_->c_ptr());
    listener_state_ =
        ServerTestPeer(server_.get()).listener_states().front().get();
    listener_ = DownCast<NewChttp2ServerListener*>(listener_state_->listener());
  }

  void TearDown() override {
    CqVerifier cqv(cq_);
    grpc_server_shutdown_and_notify(server_->c_ptr(), cq_, CqVerifier::tag(-1));

    grpc_server_cancel_all_calls(server_->c_ptr());
    cqv.Expect(CqVerifier::tag(-1), true);
    cqv.Verify();
    server_.reset();
    grpc_completion_queue_destroy(cq_);
  }

  ChannelArgs args_;
  OrphanablePtr<Server> server_;
  Server::ListenerState* listener_state_;
  NewChttp2ServerListener* listener_;
  grpc_completion_queue* cq_ = nullptr;
};

TEST_F(Chttp2ServerListenerTest, Basic) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);
  auto mock_endpoint_controller =
      grpc_event_engine::experimental::MockEndpointController::Create(
          args_.GetObjectRef<EventEngine>());
  Chttp2ServerListenerTestPeer(listener_).OnAccept(
      mock_endpoint_controller->TakeCEndpoint(),
      nullptr,
      nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      1);
}

TEST_F(Chttp2ServerListenerTest, NoConnectionQuota) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(0);
  auto mock_endpoint_controller =
      grpc_event_engine::experimental::MockEndpointController::Create(
          args_.GetObjectRef<EventEngine>());
  Chttp2ServerListenerTestPeer(listener_).OnAccept(
      mock_endpoint_controller->TakeCEndpoint(),
      nullptr,
      nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      0);
}

TEST_F(Chttp2ServerListenerTest, ConnectionRefusedAfterShutdown) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);

  RefCountedPtr<NewChttp2ServerListener> listener_ref =
      Chttp2ServerListenerTestPeer(listener_).Ref();
  grpc_server_shutdown_and_notify(server_->c_ptr(), cq_, CqVerifier::tag(1));
  auto mock_endpoint_controller =
      grpc_event_engine::experimental::MockEndpointController::Create(
          args_.GetObjectRef<EventEngine>());
  Chttp2ServerListenerTestPeer(listener_).OnAccept(
      mock_endpoint_controller->TakeCEndpoint(),
      nullptr,
      nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      0);

  {

    ExecCtx exec_ctx;
    listener_ref.reset();
  }
  CqVerifier cqv(cq_);
  cqv.Expect(CqVerifier::tag(1), true);
  cqv.Verify();
}

using Chttp2ActiveConnectionTest = Chttp2ServerListenerTest;

TEST_F(Chttp2ActiveConnectionTest, CloseWithoutHandshakeStarting) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);

  ASSERT_TRUE(listener_state_->connection_quota()->AllowIncomingConnection(
      listener_state_->memory_quota(), "peer"));
  auto connection = MakeOrphanable<NewChttp2ServerListener::ActiveConnection>(
      listener_state_->Ref(), nullptr,
      nullptr,
      nullptr, args_,
      listener_state_->memory_quota()->CreateMemoryOwner(), nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      1);
  connection->RefAsSubclass<NewChttp2ServerListener::ActiveConnection>()
      .release();

  ActiveConnectionTestPeer(connection.get()).OnClose();
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      0);
}

RefCountedPtr<grpc_server_credentials> CreateSecureServerCredentials() {
  std::string ca_cert =
      testing::GetFileContents("src/core/tsi/test_creds/client.pem");
  std::string server_cert =
      testing::GetFileContents("src/core/tsi/test_creds/server1.pem");
  std::string server_key =
      testing::GetFileContents("src/core/tsi/test_creds/server1.key");
  grpc_tls_credentials_options* options = grpc_tls_credentials_options_create();

  grpc_tls_identity_pairs* server_pairs = grpc_tls_identity_pairs_create();
  grpc_tls_identity_pairs_add_pair(server_pairs, server_key.c_str(),
                                   server_cert.c_str());
  grpc_tls_certificate_provider* server_provider =
      grpc_tls_certificate_provider_static_data_create(ca_cert.c_str(),
                                                       server_pairs);
  grpc_tls_credentials_options_set_certificate_provider(options,
                                                        server_provider);
  grpc_tls_certificate_provider_release(server_provider);
  grpc_tls_credentials_options_watch_root_certs(options);
  grpc_tls_credentials_options_watch_identity_key_cert_pairs(options);

  grpc_tls_credentials_options_set_cert_request_type(
      options, GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY);
  grpc_server_credentials* creds = grpc_tls_server_credentials_create(options);
  return RefCountedPtr<grpc_server_credentials>(creds);
}

TEST_F(Chttp2ActiveConnectionTest, CloseDuringHandshake) {

  SetUpServer(CreateSecureServerCredentials());
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);

  ASSERT_TRUE(listener_state_->connection_quota()->AllowIncomingConnection(
      listener_state_->memory_quota(), "peer"));
  auto connection = MakeOrphanable<NewChttp2ServerListener::ActiveConnection>(
      listener_state_->Ref(), nullptr,
      nullptr,
      nullptr, args_,
      listener_state_->memory_quota()->CreateMemoryOwner(), nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      1);
  connection->RefAsSubclass<NewChttp2ServerListener::ActiveConnection>()
      .release();

  ActiveConnectionTestPeer(connection.get()).OnClose();
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      0);
}

TEST_F(Chttp2ActiveConnectionTest, CloseAfterHandshakeButBeforeSettingsFrame) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);

  auto mock_endpoint_controller =
      grpc_event_engine::experimental::MockEndpointController::Create(
          args_.GetObjectRef<EventEngine>());
  mock_endpoint_controller->NoMoreReads();
  ASSERT_TRUE(listener_state_->connection_quota()->AllowIncomingConnection(
      listener_state_->memory_quota(), "peer"));
  auto connection = MakeOrphanable<NewChttp2ServerListener::ActiveConnection>(
      listener_state_->Ref(), nullptr,
      nullptr,
      nullptr, args_,
      listener_state_->memory_quota()->CreateMemoryOwner(),
      OrphanablePtr<grpc_endpoint>(mock_endpoint_controller->TakeCEndpoint()));
  auto* connection_ptr = connection.get();
  listener_state_->AddLogicalConnection(std::move(connection), args_,
                                        nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      1);
  connection_ptr->Start(args_);

  absl::Time test_deadline =
      absl::Now() + absl::Seconds(10) * grpc_test_slowdown_factor();
  while (ListenerStateTestPeer(listener_state_).ConnectionsSize() != 0) {
    ASSERT_LE(absl::Now(), test_deadline);

    std::this_thread::yield();
  }

  grpc_server_cancel_all_calls(server_->c_ptr());
  while (listener_state_->connection_quota()
             ->TestOnlyActiveIncomingConnections() != 0) {
    ASSERT_LE(absl::Now(), test_deadline);

    std::this_thread::yield();
  }
}

TEST_F(Chttp2ActiveConnectionTest, CloseAfterSettingsFrame) {
  SetUpServer();
  listener_state_->connection_quota()->SetMaxIncomingConnections(10);

  auto mock_endpoint_controller =
      grpc_event_engine::experimental::MockEndpointController::Create(
          args_.GetObjectRef<EventEngine>());

  mock_endpoint_controller->TriggerReadEvent(
      grpc_event_engine::experimental::Slice::FromCopiedString(
          "PRI * "
          "HTTP/2.0\r\n\r\nSM\r\n\r\n\x00\x00\x00\x04\x00\x00\x00\x00\x00"));
  mock_endpoint_controller->NoMoreReads();
  ASSERT_TRUE(listener_state_->connection_quota()->AllowIncomingConnection(
      listener_state_->memory_quota(), "peer"));
  auto connection = MakeOrphanable<NewChttp2ServerListener::ActiveConnection>(
      listener_state_->Ref(), nullptr,
      nullptr,
      nullptr, args_,
      listener_state_->memory_quota()->CreateMemoryOwner(),
      OrphanablePtr<grpc_endpoint>(mock_endpoint_controller->TakeCEndpoint()));
  auto* connection_ptr = connection.get();

  RefCountedPtr<NewChttp2ServerListener::ActiveConnection::HandshakingState>
      handshaking_state =
          HandshakingStateTestPeer(
              ActiveConnectionTestPeer(connection_ptr).handshaking_state())
              .Ref();
  listener_state_->AddLogicalConnection(std::move(connection), args_,
                                        nullptr);
  EXPECT_EQ(
      listener_state_->connection_quota()->TestOnlyActiveIncomingConnections(),
      1);
  connection_ptr->Start(args_);

  absl::Time test_deadline =
      absl::Now() + absl::Seconds(10) * grpc_test_slowdown_factor();
  while (ListenerStateTestPeer(listener_state_).ConnectionsSize() != 0) {
    ASSERT_LE(absl::Now(), test_deadline);

    std::this_thread::yield();
  }

  ASSERT_TRUE(
      HandshakingStateTestPeer(handshaking_state.get()).WaitForSettingsFrame());

  grpc_server_cancel_all_calls(server_->c_ptr());
  while (listener_state_->connection_quota()
             ->TestOnlyActiveIncomingConnections() != 0) {
    ASSERT_LE(absl::Now(), test_deadline);

    std::this_thread::yield();
  }
}

}
}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  int ret = RUN_ALL_TESTS();
  grpc_shutdown();
  return ret;
}
