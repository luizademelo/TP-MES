
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/ext/health_check_service_server_builder_option.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <cinttypes>
#include <memory>
#include <thread>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "src/core/client_channel/backup_poller.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/proto/grpc/health/v1/health.grpc.pb.h"
#include "src/proto/grpc/testing/duplicate/echo_duplicate.grpc.pb.h"
#include "src/proto/grpc/testing/echo.grpc.pb.h"
#include "test/core/test_util/build.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/string_ref_helper.h"
#include "test/cpp/util/test_credentials_provider.h"

#ifdef GRPC_POSIX_SOCKET_EV
#include "src/core/lib/iomgr/ev_posix.h"
#endif

#include "gtest/gtest.h"

using grpc::testing::EchoRequest;
using grpc::testing::EchoResponse;
using std::chrono::system_clock;

namespace grpc {
namespace testing {

namespace {

void* tag(int t) { return reinterpret_cast<void*>(t); }
int detag(void* p) { return static_cast<int>(reinterpret_cast<intptr_t>(p)); }

class Verifier {
 public:
  Verifier() : lambda_run_(false) {}

  Verifier& Expect(
      int i, bool expect_ok,
      grpc_core::SourceLocation whence = grpc_core::SourceLocation()) {
    return ExpectUnless(i, expect_ok, false, whence);
  }

  Verifier& ExpectUnless(
      int i, bool expect_ok, bool seen,
      grpc_core::SourceLocation whence = grpc_core::SourceLocation()) {
    if (!seen) {
      expectations_[tag(i)] = {expect_ok, whence};
    }
    return *this;
  }

  Verifier& ExpectMaybe(
      int i, bool expect_ok, bool* seen,
      grpc_core::SourceLocation whence = grpc_core::SourceLocation()) {
    if (!*seen) {
      maybe_expectations_[tag(i)] = MaybeExpect{expect_ok, seen, whence};
    }
    return *this;
  }

  int Next(CompletionQueue* cq, bool ignore_ok) {
    bool ok;
    void* got_tag;
    EXPECT_TRUE(cq->Next(&got_tag, &ok));
    GotTag(got_tag, ok, ignore_ok);
    return detag(got_tag);
  }

  template <typename T>
  CompletionQueue::NextStatus DoOnceThenAsyncNext(
      CompletionQueue* cq, void** got_tag, bool* ok, T deadline,
      std::function<void(void)> lambda) {
    if (lambda_run_) {
      return cq->AsyncNext(got_tag, ok, deadline);
    } else {
      lambda_run_ = true;
      return cq->DoThenAsyncNext(lambda, got_tag, ok, deadline);
    }
  }

  void Verify(CompletionQueue* cq) { Verify(cq, false); }

  void Verify(CompletionQueue* cq, bool ignore_ok) {
    CHECK(!expectations_.empty() || !maybe_expectations_.empty());
    while (!expectations_.empty()) {
      Next(cq, ignore_ok);
    }
    maybe_expectations_.clear();
  }

  void Verify(CompletionQueue* cq,
              std::chrono::system_clock::time_point deadline) {
    if (expectations_.empty()) {
      bool ok;
      void* got_tag;
      EXPECT_EQ(cq->AsyncNext(&got_tag, &ok, deadline),
                CompletionQueue::TIMEOUT);
    } else {
      while (!expectations_.empty()) {
        bool ok;
        void* got_tag;
        EXPECT_EQ(cq->AsyncNext(&got_tag, &ok, deadline),
                  CompletionQueue::GOT_EVENT);
        GotTag(got_tag, ok, false);
      }
    }
    maybe_expectations_.clear();
  }

  void Verify(CompletionQueue* cq,
              std::chrono::system_clock::time_point deadline,
              const std::function<void(void)>& lambda) {
    if (expectations_.empty()) {
      bool ok;
      void* got_tag;
      EXPECT_EQ(DoOnceThenAsyncNext(cq, &got_tag, &ok, deadline, lambda),
                CompletionQueue::TIMEOUT);
    } else {
      while (!expectations_.empty()) {
        bool ok;
        void* got_tag;
        EXPECT_EQ(DoOnceThenAsyncNext(cq, &got_tag, &ok, deadline, lambda),
                  CompletionQueue::GOT_EVENT);
        GotTag(got_tag, ok, false);
      }
    }
    maybe_expectations_.clear();
  }

 private:
  void GotTag(void* got_tag, bool ok, bool ignore_ok) {
    auto it = expectations_.find(got_tag);
    if (it != expectations_.end()) {
      if (!ignore_ok) {
        EXPECT_EQ(it->second.ok, ok) << it->second.ToString(it->first);
      }
      expectations_.erase(it);
    } else if (auto it2 = maybe_expectations_.find(got_tag);
               it2 != maybe_expectations_.end()) {
      if (it2->second.seen != nullptr) {
        EXPECT_FALSE(*it2->second.seen);
        *it2->second.seen = true;
      }
      if (!ignore_ok) {
        EXPECT_EQ(it2->second.ok, ok) << it->second.ToString(it->first);
      }
      maybe_expectations_.erase(it2);
    } else {
      grpc_core::Crash(absl::StrFormat("Unexpected tag: %p", got_tag));
    }
  }

  struct MaybeExpect {
    bool ok;
    bool* seen;
    grpc_core::SourceLocation whence;
    std::string ToString(void* tag) const {
      return absl::StrCat(
          "[MaybeExpect] tag=", reinterpret_cast<uintptr_t>(tag),
          " expect_ok=", ok, " whence=", whence.file(), ":", whence.line());
    }
  };

  struct DefinitelyExpect {
    bool ok;
    grpc_core::SourceLocation whence;
    std::string ToString(void* tag) const {
      return absl::StrCat("[Expect] tag=", reinterpret_cast<uintptr_t>(tag),
                          " expect_ok=", ok, " whence=", whence.file(), ":",
                          whence.line());
    }
  };

  std::map<void*, DefinitelyExpect> expectations_;
  std::map<void*, MaybeExpect> maybe_expectations_;
  bool lambda_run_;
};

bool plugin_has_sync_methods(std::unique_ptr<ServerBuilderPlugin>& plugin) {
  return plugin->has_sync_methods();
}

class ServerBuilderSyncPluginDisabler : public grpc::ServerBuilderOption {
 public:
  void UpdateArguments(ChannelArguments* ) override {}

  void UpdatePlugins(
      std::vector<std::unique_ptr<ServerBuilderPlugin>>* plugins) override {
    plugins->erase(std::remove_if(plugins->begin(), plugins->end(),
                                  plugin_has_sync_methods),
                   plugins->end());
  }
};

class TestScenario {
 public:
  TestScenario(bool inproc_stub, const std::string& creds_type, bool hcs,
               const std::string& content)
      : inproc(inproc_stub),
        health_check_service(hcs),
        credentials_type(creds_type),
        message_content(content) {}
  void Log() const;
  bool inproc;
  bool health_check_service;
  const std::string credentials_type;
  const std::string message_content;
};

std::ostream& operator<<(std::ostream& out, const TestScenario& scenario) {
  return out << "TestScenario{inproc=" << (scenario.inproc ? "true" : "false")
             << ", credentials='" << scenario.credentials_type
             << ", health_check_service="
             << (scenario.health_check_service ? "true" : "false")
             << "', message_size=" << scenario.message_content.size() << "}";
}

void TestScenario::Log() const {
  std::ostringstream out;
  out << *this;
  VLOG(2) << out.str();
}

class HealthCheck : public health::v1::Health::Service {};

class AsyncEnd2endTest : public ::testing::TestWithParam<TestScenario> {
 protected:
  AsyncEnd2endTest() { GetParam().Log(); }

  void SetUp() override {
    port_ = grpc_pick_unused_port_or_die();
    server_address_ << "localhost:" << port_;

    BuildAndStartServer();
  }

  void TearDown() override {
    stub_.reset();
    ServerShutdown();
    grpc_recycle_unused_port(port_);
  }

  void ServerShutdown() {
    std::thread t([this]() {
      void* ignored_tag;
      bool ignored_ok;
      while (cq_->Next(&ignored_tag, &ignored_ok)) {
      }
    });
    server_->Shutdown();
    cq_->Shutdown();
    t.join();
  }

  void BuildAndStartServer() {
    ServerBuilder builder;
    auto server_creds = GetCredentialsProvider()->GetServerCredentials(
        GetParam().credentials_type);
    builder.AddListeningPort(server_address_.str(), server_creds);
    service_ = std::make_unique<grpc::testing::EchoTestService::AsyncService>();
    builder.RegisterService(service_.get());
    if (GetParam().health_check_service) {
      builder.RegisterService(&health_check_);
    }
    cq_ = builder.AddCompletionQueue();

    std::unique_ptr<ServerBuilderOption> sync_plugin_disabler(
        new ServerBuilderSyncPluginDisabler());
    builder.SetOption(std::move(sync_plugin_disabler));
    server_ = builder.BuildAndStart();
  }

  void ResetStub() {
    ChannelArguments args;
    auto channel_creds = GetCredentialsProvider()->GetChannelCredentials(
        GetParam().credentials_type, &args);
    std::shared_ptr<Channel> channel =
        !(GetParam().inproc) ? grpc::CreateCustomChannel(server_address_.str(),
                                                         channel_creds, args)
                             : server_->InProcessChannel(args);
    stub_ = grpc::testing::EchoTestService::NewStub(channel);
  }

  void SendRpc(int num_rpcs) {
    for (int i = 0; i < num_rpcs; i++) {
      EchoRequest send_request;
      EchoRequest recv_request;
      EchoResponse send_response;
      EchoResponse recv_response;
      Status recv_status;

      ClientContext cli_ctx;
      ServerContext srv_ctx;
      grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

      send_request.set_message(GetParam().message_content);
      std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
          stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));

      service_->RequestEcho(&srv_ctx, &recv_request, &response_writer,
                            cq_.get(), cq_.get(), tag(2));

      response_reader->Finish(&recv_response, &recv_status, tag(4));

      Verifier().Expect(2, true).Verify(cq_.get());
      EXPECT_EQ(send_request.message(), recv_request.message());

      send_response.set_message(recv_request.message());
      response_writer.Finish(send_response, Status::OK, tag(3));
      Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());

      EXPECT_EQ(send_response.message(), recv_response.message());
      EXPECT_TRUE(recv_status.ok());
    }
  }

  std::unique_ptr<ServerCompletionQueue> cq_;
  std::unique_ptr<grpc::testing::EchoTestService::Stub> stub_;
  std::unique_ptr<Server> server_;
  std::unique_ptr<grpc::testing::EchoTestService::AsyncService> service_;
  HealthCheck health_check_;
  std::ostringstream server_address_;
  int port_;
};

TEST_P(AsyncEnd2endTest, SimpleRpc) {
  ResetStub();
  SendRpc(1);
}

TEST_P(AsyncEnd2endTest, SimpleRpcWithExpectedError) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);
  ErrorStatus error_status;

  send_request.set_message(GetParam().message_content);
  error_status.set_code(1);
  error_status.set_error_message("cancel error message");
  *send_request.mutable_param()->mutable_expected_error() = error_status;

  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));

  srv_ctx.AsyncNotifyWhenDone(tag(5));
  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));

  response_reader->Finish(&recv_response, &recv_status, tag(4));

  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  response_writer.Finish(
      send_response,
      Status(
          static_cast<StatusCode>(recv_request.param().expected_error().code()),
          recv_request.param().expected_error().error_message()),
      tag(3));
  Verifier().Expect(3, true).Expect(4, true).Expect(5, true).Verify(cq_.get());

  EXPECT_EQ(recv_response.message(), "");
  EXPECT_EQ(recv_status.error_code(), error_status.code());
  EXPECT_EQ(recv_status.error_message(), error_status.error_message());
  EXPECT_FALSE(srv_ctx.IsCancelled());
}

TEST_P(AsyncEnd2endTest, SequentialRpcs) {
  ResetStub();
  SendRpc(10);
}

TEST_P(AsyncEnd2endTest, ReconnectChannel) {

  if (GetParam().inproc) {
    return;
  }
  int poller_slowdown_factor = 1;
#ifdef GRPC_POSIX_SOCKET_EV

  if (grpc_core::ConfigVars::Get().PollStrategy() == "poll") {
    poller_slowdown_factor = 2;
  }
#endif
  ResetStub();
  SendRpc(1);
  ServerShutdown();
  BuildAndStartServer();

  gpr_sleep_until(gpr_time_add(
      gpr_now(GPR_CLOCK_REALTIME),
      gpr_time_from_millis(
          300 * poller_slowdown_factor * grpc_test_slowdown_factor(),
          GPR_TIMESPAN)));
  SendRpc(1);
}

void ServerWait(Server* server, int* notify) {
  server->Wait();
  *notify = 1;
}
TEST_P(AsyncEnd2endTest, WaitAndShutdownTest) {
  int notify = 0;
  std::thread wait_thread(&ServerWait, server_.get(), &notify);
  ResetStub();
  SendRpc(1);
  EXPECT_EQ(0, notify);
  ServerShutdown();
  wait_thread.join();
  EXPECT_EQ(1, notify);
}

TEST_P(AsyncEnd2endTest, ShutdownThenWait) {
  ResetStub();
  SendRpc(1);
  std::thread t([this]() { ServerShutdown(); });
  server_->Wait();
  t.join();
}

TEST_P(AsyncEnd2endTest, AsyncNextRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));

  std::chrono::system_clock::time_point time_now(
      std::chrono::system_clock::now());
  std::chrono::system_clock::time_point time_limit(
      std::chrono::system_clock::now() + std::chrono::seconds(10));
  Verifier().Verify(cq_.get(), time_now);
  Verifier().Verify(cq_.get(), time_now);

  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));
  response_reader->Finish(&recv_response, &recv_status, tag(4));

  Verifier().Expect(2, true).Verify(cq_.get(), time_limit);
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  response_writer.Finish(send_response, Status::OK, tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(
      cq_.get(), std::chrono::system_clock::time_point::max());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, DoThenAsyncNextRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));

  std::chrono::system_clock::time_point time_now(
      std::chrono::system_clock::now());
  std::chrono::system_clock::time_point time_limit(
      std::chrono::system_clock::now() + std::chrono::seconds(10));
  Verifier().Verify(cq_.get(), time_now);
  Verifier().Verify(cq_.get(), time_now);

  auto resp_writer_ptr = &response_writer;
  auto lambda_2 = [&, this, resp_writer_ptr]() {
    service_->RequestEcho(&srv_ctx, &recv_request, resp_writer_ptr, cq_.get(),
                          cq_.get(), tag(2));
  };
  response_reader->Finish(&recv_response, &recv_status, tag(4));

  Verifier().Expect(2, true).Verify(cq_.get(), time_limit, lambda_2);
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  auto lambda_3 = [resp_writer_ptr, send_response]() {
    resp_writer_ptr->Finish(send_response, Status::OK, tag(3));
  };
  Verifier().Expect(3, true).Expect(4, true).Verify(
      cq_.get(), std::chrono::system_clock::time_point::max(), lambda_3);

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleClientStreaming) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncReader<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncWriter<EchoRequest>> cli_stream(
      stub_->AsyncRequestStream(&cli_ctx, &recv_response, cq_.get(), tag(1)));

  service_->RequestRequestStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                                 tag(2));

  Verifier().Expect(2, true).Expect(1, true).Verify(cq_.get());

  cli_stream->Write(send_request, tag(3));
  srv_stream.Read(&recv_request, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  cli_stream->Write(send_request, tag(5));
  srv_stream.Read(&recv_request, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  EXPECT_EQ(send_request.message(), recv_request.message());
  cli_stream->WritesDone(tag(7));
  srv_stream.Read(&recv_request, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  send_response.set_message(recv_request.message());
  srv_stream.Finish(send_response, Status::OK, tag(9));
  cli_stream->Finish(&recv_status, tag(10));
  Verifier().Expect(9, true).Expect(10, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleClientStreamingWithCoalescingApi) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncReader<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  cli_ctx.set_initial_metadata_corked(true);

  std::unique_ptr<ClientAsyncWriter<EchoRequest>> cli_stream(
      stub_->AsyncRequestStream(&cli_ctx, &recv_response, cq_.get(), tag(1)));

  service_->RequestRequestStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                                 tag(2));

  cli_stream->Write(send_request, tag(3));

  bool seen3 = false;

  Verifier().Expect(2, true).ExpectMaybe(3, true, &seen3).Verify(cq_.get());

  srv_stream.Read(&recv_request, tag(4));

  Verifier().ExpectUnless(3, true, seen3).Expect(4, true).Verify(cq_.get());

  EXPECT_EQ(send_request.message(), recv_request.message());

  cli_stream->WriteLast(send_request, WriteOptions(), tag(5));
  srv_stream.Read(&recv_request, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  srv_stream.Read(&recv_request, tag(7));
  Verifier().Expect(7, false).Verify(cq_.get());

  send_response.set_message(recv_request.message());
  srv_stream.Finish(send_response, Status::OK, tag(8));
  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(8, true).Expect(9, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleServerStreaming) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx, send_request, cq_.get(), tag(1)));

  service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                  cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  srv_stream.Write(send_response, tag(3));
  cli_stream->Read(&recv_response, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  srv_stream.Write(send_response, tag(5));
  cli_stream->Read(&recv_response, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  srv_stream.Finish(Status::OK, tag(7));
  cli_stream->Read(&recv_response, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleServerStreamingWithCoalescingApiWAF) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx, send_request, cq_.get(), tag(1)));

  service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                  cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  srv_stream.Write(send_response, tag(3));
  cli_stream->Read(&recv_response, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  srv_stream.WriteAndFinish(send_response, WriteOptions(), Status::OK, tag(5));
  cli_stream->Read(&recv_response, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  cli_stream->Read(&recv_response, tag(7));
  Verifier().Expect(7, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status, tag(8));
  Verifier().Expect(8, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleServerStreamingWithCoalescingApiWL) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx, send_request, cq_.get(), tag(1)));

  service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                  cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  srv_stream.Write(send_response, tag(3));
  cli_stream->Read(&recv_response, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  srv_stream.WriteLast(send_response, WriteOptions(), tag(5));
  cli_stream->Read(&recv_response, tag(6));
  srv_stream.Finish(Status::OK, tag(7));
  Verifier().Expect(5, true).Expect(6, true).Expect(7, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  cli_stream->Read(&recv_response, tag(8));
  Verifier().Expect(8, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleBidiStreaming) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncReaderWriter<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncReaderWriter<EchoRequest, EchoResponse>>
      cli_stream(stub_->AsyncBidiStream(&cli_ctx, cq_.get(), tag(1)));

  service_->RequestBidiStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                              tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());

  cli_stream->Write(send_request, tag(3));
  srv_stream.Read(&recv_request, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  srv_stream.Write(send_response, tag(5));
  cli_stream->Read(&recv_response, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  cli_stream->WritesDone(tag(7));
  srv_stream.Read(&recv_request, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  srv_stream.Finish(Status::OK, tag(9));
  cli_stream->Finish(&recv_status, tag(10));
  Verifier().Expect(9, true).Expect(10, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleBidiStreamingWithCoalescingApiWAF) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncReaderWriter<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  cli_ctx.set_initial_metadata_corked(true);
  std::unique_ptr<ClientAsyncReaderWriter<EchoRequest, EchoResponse>>
      cli_stream(stub_->AsyncBidiStream(&cli_ctx, cq_.get(), tag(1)));

  service_->RequestBidiStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                              tag(2));

  cli_stream->WriteLast(send_request, WriteOptions(), tag(3));

  bool seen3 = false;

  Verifier().Expect(2, true).ExpectMaybe(3, true, &seen3).Verify(cq_.get());

  srv_stream.Read(&recv_request, tag(4));

  Verifier().ExpectUnless(3, true, seen3).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  srv_stream.Read(&recv_request, tag(5));
  Verifier().Expect(5, false).Verify(cq_.get());

  send_response.set_message(recv_request.message());
  srv_stream.WriteAndFinish(send_response, WriteOptions(), Status::OK, tag(6));
  cli_stream->Read(&recv_response, tag(7));
  Verifier().Expect(6, true).Expect(7, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  cli_stream->Finish(&recv_status, tag(8));
  Verifier().Expect(8, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, SimpleBidiStreamingWithCoalescingApiWL) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncReaderWriter<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  cli_ctx.set_initial_metadata_corked(true);
  std::unique_ptr<ClientAsyncReaderWriter<EchoRequest, EchoResponse>>
      cli_stream(stub_->AsyncBidiStream(&cli_ctx, cq_.get(), tag(1)));

  service_->RequestBidiStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                              tag(2));

  cli_stream->WriteLast(send_request, WriteOptions(), tag(3));

  bool seen3 = false;

  Verifier().Expect(2, true).ExpectMaybe(3, true, &seen3).Verify(cq_.get());

  srv_stream.Read(&recv_request, tag(4));

  Verifier().ExpectUnless(3, true, seen3).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  srv_stream.Read(&recv_request, tag(5));
  Verifier().Expect(5, false).Verify(cq_.get());

  send_response.set_message(recv_request.message());
  srv_stream.WriteLast(send_response, WriteOptions(), tag(6));
  srv_stream.Finish(Status::OK, tag(7));
  cli_stream->Read(&recv_response, tag(8));
  Verifier().Expect(6, true).Expect(7, true).Expect(8, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, ClientInitialMetadataRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::pair<std::string, std::string> meta1("key1", "val1");
  std::pair<std::string, std::string> meta2("key2", "val2");
  std::pair<std::string, std::string> meta3("g.r.d-bin", "xyz");
  cli_ctx.AddMetadata(meta1.first, meta1.second);
  cli_ctx.AddMetadata(meta2.first, meta2.second);
  cli_ctx.AddMetadata(meta3.first, meta3.second);

  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->Finish(&recv_response, &recv_status, tag(4));

  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());
  const auto& client_initial_metadata = srv_ctx.client_metadata();
  EXPECT_EQ(meta1.second,
            ToString(client_initial_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(client_initial_metadata.find(meta2.first)->second));
  EXPECT_EQ(meta3.second,
            ToString(client_initial_metadata.find(meta3.first)->second));
  EXPECT_GE(client_initial_metadata.size(), 2);

  send_response.set_message(recv_request.message());
  response_writer.Finish(send_response, Status::OK, tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, ServerInitialMetadataRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::pair<std::string, std::string> meta1("key1", "val1");
  std::pair<std::string, std::string> meta2("key2", "val2");

  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->ReadInitialMetadata(tag(4));

  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());
  srv_ctx.AddInitialMetadata(meta1.first, meta1.second);
  srv_ctx.AddInitialMetadata(meta2.first, meta2.second);
  response_writer.SendInitialMetadata(tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  const auto& server_initial_metadata = cli_ctx.GetServerInitialMetadata();
  EXPECT_EQ(meta1.second,
            ToString(server_initial_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(server_initial_metadata.find(meta2.first)->second));
  EXPECT_EQ(2, server_initial_metadata.size());

  send_response.set_message(recv_request.message());
  response_writer.Finish(send_response, Status::OK, tag(5));
  response_reader->Finish(&recv_response, &recv_status, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, ServerInitialMetadataServerStreaming) {
  ResetStub();
  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

  std::pair<::std::string, ::std::string> meta1("key1", "val1");
  std::pair<::std::string, ::std::string> meta2("key2", "val2");

  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx, send_request, cq_.get(), tag(1)));
  cli_stream->ReadInitialMetadata(tag(11));
  service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                  cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());

  srv_ctx.AddInitialMetadata(meta1.first, meta1.second);
  srv_ctx.AddInitialMetadata(meta2.first, meta2.second);
  srv_stream.SendInitialMetadata(tag(10));
  Verifier().Expect(10, true).Expect(11, true).Verify(cq_.get());
  auto server_initial_metadata = cli_ctx.GetServerInitialMetadata();
  EXPECT_EQ(meta1.second,
            ToString(server_initial_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(server_initial_metadata.find(meta2.first)->second));
  EXPECT_EQ(2, server_initial_metadata.size());

  srv_stream.Write(send_response, tag(3));

  cli_stream->Read(&recv_response, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());

  srv_stream.Write(send_response, tag(5));
  cli_stream->Read(&recv_response, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  srv_stream.Finish(Status::OK, tag(7));
  cli_stream->Read(&recv_response, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, ServerInitialMetadataServerStreamingImplicit) {
  ResetStub();
  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;
  ClientContext cli_ctx;
  ServerContext srv_ctx;
  ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::pair<::std::string, ::std::string> meta1("key1", "val1");
  std::pair<::std::string, ::std::string> meta2("key2", "val2");

  std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
      stub_->AsyncResponseStream(&cli_ctx, send_request, cq_.get(), tag(1)));
  service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                  cq_.get(), cq_.get(), tag(2));

  Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  srv_ctx.AddInitialMetadata(meta1.first, meta1.second);
  srv_ctx.AddInitialMetadata(meta2.first, meta2.second);
  send_response.set_message(recv_request.message());
  srv_stream.Write(send_response, tag(3));

  cli_stream->Read(&recv_response, tag(4));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  EXPECT_EQ(send_response.message(), recv_response.message());

  auto server_initial_metadata = cli_ctx.GetServerInitialMetadata();
  EXPECT_EQ(meta1.second,
            ToString(server_initial_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(server_initial_metadata.find(meta2.first)->second));
  EXPECT_EQ(2, server_initial_metadata.size());

  srv_stream.Write(send_response, tag(5));
  cli_stream->Read(&recv_response, tag(6));
  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  srv_stream.Finish(Status::OK, tag(7));
  cli_stream->Read(&recv_response, tag(8));
  Verifier().Expect(7, true).Expect(8, false).Verify(cq_.get());

  cli_stream->Finish(&recv_status, tag(9));
  Verifier().Expect(9, true).Verify(cq_.get());

  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, ServerTrailingMetadataRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::pair<std::string, std::string> meta1("key1", "val1");
  std::pair<std::string, std::string> meta2("key2", "val2");

  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->Finish(&recv_response, &recv_status, tag(5));

  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());
  response_writer.SendInitialMetadata(tag(3));
  Verifier().Expect(3, true).Verify(cq_.get());

  send_response.set_message(recv_request.message());
  srv_ctx.AddTrailingMetadata(meta1.first, meta1.second);
  srv_ctx.AddTrailingMetadata(meta2.first, meta2.second);
  response_writer.Finish(send_response, Status::OK, tag(4));

  Verifier().Expect(4, true).Expect(5, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
  const auto& server_trailing_metadata = cli_ctx.GetServerTrailingMetadata();
  EXPECT_EQ(meta1.second,
            ToString(server_trailing_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(server_trailing_metadata.find(meta2.first)->second));
  EXPECT_EQ(2, server_trailing_metadata.size());
}

TEST_P(AsyncEnd2endTest, MetadataRpc) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::pair<std::string, std::string> meta1("key1", "val1");
  std::pair<std::string, std::string> meta2(
      "key2-bin",
      std::string("\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc", 13));
  std::pair<std::string, std::string> meta3("key3", "val3");
  std::pair<std::string, std::string> meta6(
      "key4-bin",
      std::string("\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d",
                  14));
  std::pair<std::string, std::string> meta5("key5", "val5");
  std::pair<std::string, std::string> meta4(
      "key6-bin",
      std::string(
          "\xe0\xe1\xe2\xe3\xe4\xe5\xe6\xe7\xe8\xe9\xea\xeb\xec\xed\xee", 15));

  cli_ctx.AddMetadata(meta1.first, meta1.second);
  cli_ctx.AddMetadata(meta2.first, meta2.second);

  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->ReadInitialMetadata(tag(4));

  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));
  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());
  const auto& client_initial_metadata = srv_ctx.client_metadata();
  EXPECT_EQ(meta1.second,
            ToString(client_initial_metadata.find(meta1.first)->second));
  EXPECT_EQ(meta2.second,
            ToString(client_initial_metadata.find(meta2.first)->second));
  EXPECT_GE(client_initial_metadata.size(), 2);

  srv_ctx.AddInitialMetadata(meta3.first, meta3.second);
  srv_ctx.AddInitialMetadata(meta4.first, meta4.second);
  response_writer.SendInitialMetadata(tag(3));
  Verifier().Expect(3, true).Expect(4, true).Verify(cq_.get());
  const auto& server_initial_metadata = cli_ctx.GetServerInitialMetadata();
  EXPECT_EQ(meta3.second,
            ToString(server_initial_metadata.find(meta3.first)->second));
  EXPECT_EQ(meta4.second,
            ToString(server_initial_metadata.find(meta4.first)->second));
  EXPECT_GE(server_initial_metadata.size(), 2);

  send_response.set_message(recv_request.message());
  srv_ctx.AddTrailingMetadata(meta5.first, meta5.second);
  srv_ctx.AddTrailingMetadata(meta6.first, meta6.second);
  response_writer.Finish(send_response, Status::OK, tag(5));
  response_reader->Finish(&recv_response, &recv_status, tag(6));

  Verifier().Expect(5, true).Expect(6, true).Verify(cq_.get());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
  const auto& server_trailing_metadata = cli_ctx.GetServerTrailingMetadata();
  EXPECT_EQ(meta5.second,
            ToString(server_trailing_metadata.find(meta5.first)->second));
  EXPECT_EQ(meta6.second,
            ToString(server_trailing_metadata.find(meta6.first)->second));
  EXPECT_GE(server_trailing_metadata.size(), 2);
}

TEST_P(AsyncEnd2endTest, ServerCheckCancellation) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->Finish(&recv_response, &recv_status, tag(4));

  srv_ctx.AsyncNotifyWhenDone(tag(5));
  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));

  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  cli_ctx.TryCancel();
  Verifier().Expect(5, true).Expect(4, true).Verify(cq_.get());
  EXPECT_TRUE(srv_ctx.IsCancelled());

  EXPECT_EQ(StatusCode::CANCELLED, recv_status.error_code());
}

TEST_P(AsyncEnd2endTest, ServerCheckDone) {
  ResetStub();

  EchoRequest send_request;
  EchoRequest recv_request;
  EchoResponse send_response;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  ServerContext srv_ctx;
  grpc::ServerAsyncResponseWriter<EchoResponse> response_writer(&srv_ctx);

  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub_->AsyncEcho(&cli_ctx, send_request, cq_.get()));
  response_reader->Finish(&recv_response, &recv_status, tag(4));

  srv_ctx.AsyncNotifyWhenDone(tag(5));
  service_->RequestEcho(&srv_ctx, &recv_request, &response_writer, cq_.get(),
                        cq_.get(), tag(2));

  Verifier().Expect(2, true).Verify(cq_.get());
  EXPECT_EQ(send_request.message(), recv_request.message());

  send_response.set_message(recv_request.message());
  response_writer.Finish(send_response, Status::OK, tag(3));
  Verifier().Expect(3, true).Expect(4, true).Expect(5, true).Verify(cq_.get());
  EXPECT_FALSE(srv_ctx.IsCancelled());

  EXPECT_EQ(send_response.message(), recv_response.message());
  EXPECT_TRUE(recv_status.ok());
}

TEST_P(AsyncEnd2endTest, UnimplementedRpc) {
  ChannelArguments args;
  const auto& channel_creds = GetCredentialsProvider()->GetChannelCredentials(
      GetParam().credentials_type, &args);
  std::shared_ptr<Channel> channel =
      !(GetParam().inproc) ? grpc::CreateCustomChannel(server_address_.str(),
                                                       channel_creds, args)
                           : server_->InProcessChannel(args);
  std::unique_ptr<grpc::testing::UnimplementedEchoService::Stub> stub;
  stub = grpc::testing::UnimplementedEchoService::NewStub(channel);
  EchoRequest send_request;
  EchoResponse recv_response;
  Status recv_status;

  ClientContext cli_ctx;
  send_request.set_message(GetParam().message_content);
  std::unique_ptr<ClientAsyncResponseReader<EchoResponse>> response_reader(
      stub->AsyncUnimplemented(&cli_ctx, send_request, cq_.get()));

  response_reader->Finish(&recv_response, &recv_status, tag(4));
  Verifier().Expect(4, true).Verify(cq_.get());

  EXPECT_EQ(StatusCode::UNIMPLEMENTED, recv_status.error_code());
  EXPECT_EQ("", recv_status.error_message());
}

class AsyncEnd2endServerTryCancelTest : public AsyncEnd2endTest {
 protected:
  typedef enum {
    DO_NOT_CANCEL = 0,
    CANCEL_BEFORE_PROCESSING,
    CANCEL_DURING_PROCESSING,
    CANCEL_AFTER_PROCESSING
  } ServerTryCancelRequestPhase;

  void TestClientStreamingServerCancel(
      ServerTryCancelRequestPhase server_try_cancel) {
    ResetStub();

    EchoRequest recv_request;
    EchoResponse send_response;
    EchoResponse recv_response;
    Status recv_status;

    ClientContext cli_ctx;
    ServerContext srv_ctx;
    ServerAsyncReader<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

    CompletionQueue cli_cq;

    std::unique_ptr<ClientAsyncWriter<EchoRequest>> cli_stream(
        stub_->AsyncRequestStream(&cli_ctx, &recv_response, &cli_cq, tag(1)));

    srv_ctx.AsyncNotifyWhenDone(tag(11));
    service_->RequestRequestStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                                   tag(2));
    std::thread t1([&cli_cq] { Verifier().Expect(1, true).Verify(&cli_cq); });
    Verifier().Expect(2, true).Verify(cq_.get());
    t1.join();

    bool expected_server_cq_result = true;
    bool expected_client_cq_result = true;

    if (server_try_cancel == CANCEL_BEFORE_PROCESSING) {
      srv_ctx.TryCancel();
      Verifier().Expect(11, true).Verify(cq_.get());
      EXPECT_TRUE(srv_ctx.IsCancelled());

      expected_server_cq_result = false;
      expected_client_cq_result = false;
    }

    bool ignore_client_cq_result =
        (server_try_cancel == CANCEL_DURING_PROCESSING) ||
        (server_try_cancel == CANCEL_BEFORE_PROCESSING);

    std::thread cli_thread([&cli_cq, &cli_stream, &expected_client_cq_result,
                            &ignore_client_cq_result] {
      EchoRequest send_request;

      for (int tag_idx = 3; tag_idx <= 5; tag_idx++) {
        send_request.set_message("Ping " + std::to_string(tag_idx));
        cli_stream->Write(send_request, tag(tag_idx));
        Verifier()
            .Expect(tag_idx, expected_client_cq_result)
            .Verify(&cli_cq, ignore_client_cq_result);
      }
      cli_stream->WritesDone(tag(6));

      Verifier()
          .Expect(6, expected_client_cq_result)
          .Verify(&cli_cq, ignore_client_cq_result);
    });

    bool ignore_cq_result = false;
    bool want_done_tag = false;
    std::thread* server_try_cancel_thd = nullptr;

    auto verif = Verifier();

    if (server_try_cancel == CANCEL_DURING_PROCESSING) {
      server_try_cancel_thd =
          new std::thread([&srv_ctx] { srv_ctx.TryCancel(); });

      ignore_cq_result = true;

      want_done_tag = true;
      verif.Expect(11, true);
    }

    for (int tag_idx = 6; tag_idx <= 8; tag_idx++) {
      srv_stream.Read(&recv_request, tag(tag_idx));

      int got_tag = verif.Expect(tag_idx, expected_server_cq_result)
                        .Next(cq_.get(), ignore_cq_result);
      CHECK((got_tag == tag_idx) || (got_tag == 11 && want_done_tag));
      if (got_tag == 11) {
        EXPECT_TRUE(srv_ctx.IsCancelled());
        want_done_tag = false;

        EXPECT_EQ(verif.Next(cq_.get(), ignore_cq_result), tag_idx);
      }
    }

    cli_thread.join();

    if (server_try_cancel_thd != nullptr) {
      server_try_cancel_thd->join();
      delete server_try_cancel_thd;
    }

    if (server_try_cancel == CANCEL_AFTER_PROCESSING) {
      srv_ctx.TryCancel();
      want_done_tag = true;
      verif.Expect(11, true);
    }

    if (want_done_tag) {
      verif.Verify(cq_.get());
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;
    }

    srv_stream.Finish(send_response, Status::CANCELLED, tag(9));
    Verifier().Expect(9, false).Verify(cq_.get());

    cli_stream->Finish(&recv_status, tag(10));
    Verifier().Expect(10, true).Verify(&cli_cq);
    EXPECT_FALSE(recv_status.ok());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, recv_status.error_code());

    cli_cq.Shutdown();
    void* phony_tag;
    bool phony_ok;
    while (cli_cq.Next(&phony_tag, &phony_ok)) {
    }
  }

  void TestServerStreamingServerCancel(
      ServerTryCancelRequestPhase server_try_cancel) {
    ResetStub();

    EchoRequest send_request;
    EchoRequest recv_request;
    EchoResponse send_response;
    Status recv_status;
    ClientContext cli_ctx;
    ServerContext srv_ctx;
    ServerAsyncWriter<EchoResponse> srv_stream(&srv_ctx);

    send_request.set_message("Ping");

    CompletionQueue cli_cq;
    std::unique_ptr<ClientAsyncReader<EchoResponse>> cli_stream(
        stub_->AsyncResponseStream(&cli_ctx, send_request, &cli_cq, tag(1)));

    srv_ctx.AsyncNotifyWhenDone(tag(11));
    service_->RequestResponseStream(&srv_ctx, &recv_request, &srv_stream,
                                    cq_.get(), cq_.get(), tag(2));

    std::thread t1([&cli_cq] { Verifier().Expect(1, true).Verify(&cli_cq); });
    Verifier().Expect(2, true).Verify(cq_.get());
    t1.join();

    EXPECT_EQ(send_request.message(), recv_request.message());

    bool expected_cq_result = true;
    bool ignore_cq_result = false;
    bool want_done_tag = false;
    bool expected_client_cq_result = true;
    bool ignore_client_cq_result =
        (server_try_cancel != CANCEL_BEFORE_PROCESSING);

    if (server_try_cancel == CANCEL_BEFORE_PROCESSING) {
      srv_ctx.TryCancel();
      Verifier().Expect(11, true).Verify(cq_.get());
      EXPECT_TRUE(srv_ctx.IsCancelled());

      expected_cq_result = false;
      expected_client_cq_result = false;
    }

    std::thread cli_thread([&cli_cq, &cli_stream, &expected_client_cq_result,
                            &ignore_client_cq_result] {

      for (int tag_idx = 6; tag_idx <= 8; tag_idx++) {
        EchoResponse recv_response;
        cli_stream->Read(&recv_response, tag(tag_idx));
        Verifier()
            .Expect(tag_idx, expected_client_cq_result)
            .Verify(&cli_cq, ignore_client_cq_result);
      }
    });

    std::thread* server_try_cancel_thd = nullptr;

    auto verif = Verifier();

    if (server_try_cancel == CANCEL_DURING_PROCESSING) {
      server_try_cancel_thd =
          new std::thread([&srv_ctx] { srv_ctx.TryCancel(); });

      ignore_cq_result = true;

      want_done_tag = true;
      verif.Expect(11, true);
    }

    for (int tag_idx = 3; tag_idx <= 5; tag_idx++) {
      send_response.set_message("Pong " + std::to_string(tag_idx));
      srv_stream.Write(send_response, tag(tag_idx));

      int got_tag = verif.Expect(tag_idx, expected_cq_result)
                        .Next(cq_.get(), ignore_cq_result);
      CHECK((got_tag == tag_idx) || (got_tag == 11 && want_done_tag));
      if (got_tag == 11) {
        EXPECT_TRUE(srv_ctx.IsCancelled());
        want_done_tag = false;

        EXPECT_EQ(verif.Next(cq_.get(), ignore_cq_result), tag_idx);
      }
    }

    if (server_try_cancel_thd != nullptr) {
      server_try_cancel_thd->join();
      delete server_try_cancel_thd;
    }

    if (server_try_cancel == CANCEL_AFTER_PROCESSING) {
      srv_ctx.TryCancel();
      want_done_tag = true;
      verif.Expect(11, true);
    }

    if (want_done_tag) {
      verif.Verify(cq_.get());
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;
    }

    cli_thread.join();

    srv_stream.Finish(Status::CANCELLED, tag(9));
    Verifier().Expect(9, false).Verify(cq_.get());

    cli_stream->Finish(&recv_status, tag(10));
    Verifier().Expect(10, true).Verify(&cli_cq);
    EXPECT_FALSE(recv_status.ok());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, recv_status.error_code());

    cli_cq.Shutdown();
    void* phony_tag;
    bool phony_ok;
    while (cli_cq.Next(&phony_tag, &phony_ok)) {
    }
  }

  void TestBidiStreamingServerCancel(
      ServerTryCancelRequestPhase server_try_cancel) {
    ResetStub();

    EchoRequest send_request;
    EchoRequest recv_request;
    EchoResponse send_response;
    EchoResponse recv_response;
    Status recv_status;
    ClientContext cli_ctx;
    ServerContext srv_ctx;
    ServerAsyncReaderWriter<EchoResponse, EchoRequest> srv_stream(&srv_ctx);

    std::unique_ptr<ClientAsyncReaderWriter<EchoRequest, EchoResponse>>
        cli_stream(stub_->AsyncBidiStream(&cli_ctx, cq_.get(), tag(1)));

    srv_ctx.AsyncNotifyWhenDone(tag(11));
    service_->RequestBidiStream(&srv_ctx, &srv_stream, cq_.get(), cq_.get(),
                                tag(2));
    Verifier().Expect(1, true).Expect(2, true).Verify(cq_.get());

    auto verif = Verifier();

    send_request.set_message("Ping");
    cli_stream->Write(send_request, tag(3));
    verif.Expect(3, true);

    bool expected_cq_result = true;
    bool ignore_cq_result = false;
    bool want_done_tag = false;

    int got_tag, got_tag2;
    bool tag_3_done = false;

    if (server_try_cancel == CANCEL_BEFORE_PROCESSING) {
      srv_ctx.TryCancel();
      verif.Expect(11, true);

      expected_cq_result = false;
      ignore_cq_result = true;

      do {
        got_tag = verif.Next(cq_.get(), ignore_cq_result);
        CHECK(((got_tag == 3) && !tag_3_done) || (got_tag == 11));
        if (got_tag == 3) {
          tag_3_done = true;
        }
      } while (got_tag != 11);
      EXPECT_TRUE(srv_ctx.IsCancelled());
    }

    std::thread* server_try_cancel_thd = nullptr;

    if (server_try_cancel == CANCEL_DURING_PROCESSING) {
      server_try_cancel_thd =
          new std::thread([&srv_ctx] { srv_ctx.TryCancel(); });

      ignore_cq_result = true;

      want_done_tag = true;
      verif.Expect(11, true);
    }

    srv_stream.Read(&recv_request, tag(4));
    verif.Expect(4, expected_cq_result);
    got_tag = tag_3_done ? 3 : verif.Next(cq_.get(), ignore_cq_result);
    got_tag2 = verif.Next(cq_.get(), ignore_cq_result);
    CHECK((got_tag == 3) || (got_tag == 4) || (got_tag == 11 && want_done_tag));
    CHECK((got_tag2 == 3) || (got_tag2 == 4) ||
          (got_tag2 == 11 && want_done_tag));

    if (got_tag + got_tag2 != 7) {
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;
      got_tag = verif.Next(cq_.get(), ignore_cq_result);
      CHECK((got_tag == 3) || (got_tag == 4));
    }

    send_response.set_message("Pong");
    srv_stream.Write(send_response, tag(5));
    verif.Expect(5, expected_cq_result);

    cli_stream->Read(&recv_response, tag(6));
    verif.Expect(6, expected_cq_result);
    got_tag = verif.Next(cq_.get(), ignore_cq_result);
    got_tag2 = verif.Next(cq_.get(), ignore_cq_result);
    CHECK((got_tag == 5) || (got_tag == 6) || (got_tag == 11 && want_done_tag));
    CHECK((got_tag2 == 5) || (got_tag2 == 6) ||
          (got_tag2 == 11 && want_done_tag));

    if (got_tag + got_tag2 != 11) {
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;
      got_tag = verif.Next(cq_.get(), ignore_cq_result);
      CHECK((got_tag == 5) || (got_tag == 6));
    }

    cli_stream->WritesDone(tag(7));
    verif.Expect(7, true);

    bool ignore_cq_wd_result =
        ignore_cq_result || (server_try_cancel == CANCEL_BEFORE_PROCESSING);
    got_tag = verif.Next(cq_.get(), ignore_cq_wd_result);
    CHECK((got_tag == 7) || (got_tag == 11 && want_done_tag));
    if (got_tag == 11) {
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;

      EXPECT_EQ(verif.Next(cq_.get(), ignore_cq_wd_result), 7);
    }

    srv_stream.Read(&recv_request, tag(8));
    verif.Expect(8, false);
    got_tag = verif.Next(cq_.get(), ignore_cq_result);
    CHECK((got_tag == 8) || (got_tag == 11 && want_done_tag));
    if (got_tag == 11) {
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;

      EXPECT_EQ(verif.Next(cq_.get(), ignore_cq_result), 8);
    }

    if (server_try_cancel_thd != nullptr) {
      server_try_cancel_thd->join();
      delete server_try_cancel_thd;
    }

    if (server_try_cancel == CANCEL_AFTER_PROCESSING) {
      srv_ctx.TryCancel();
      want_done_tag = true;
      verif.Expect(11, true);
    }

    if (want_done_tag) {
      verif.Verify(cq_.get());
      EXPECT_TRUE(srv_ctx.IsCancelled());
      want_done_tag = false;
    }

    srv_stream.Finish(Status::CANCELLED, tag(9));
    Verifier().Expect(9, false).Verify(cq_.get());

    cli_stream->Finish(&recv_status, tag(10));
    Verifier().Expect(10, true).Verify(cq_.get());
    EXPECT_FALSE(recv_status.ok());
    EXPECT_EQ(grpc::StatusCode::CANCELLED, recv_status.error_code());
  }
};

TEST_P(AsyncEnd2endServerTryCancelTest, ClientStreamingServerTryCancelBefore) {
  TestClientStreamingServerCancel(CANCEL_BEFORE_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ClientStreamingServerTryCancelDuring) {
  TestClientStreamingServerCancel(CANCEL_DURING_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ClientStreamingServerTryCancelAfter) {
  TestClientStreamingServerCancel(CANCEL_AFTER_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerStreamingServerTryCancelBefore) {
  TestServerStreamingServerCancel(CANCEL_BEFORE_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerStreamingServerTryCancelDuring) {
  TestServerStreamingServerCancel(CANCEL_DURING_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerStreamingServerTryCancelAfter) {
  TestServerStreamingServerCancel(CANCEL_AFTER_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerBidiStreamingTryCancelBefore) {
  TestBidiStreamingServerCancel(CANCEL_BEFORE_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerBidiStreamingTryCancelDuring) {
  TestBidiStreamingServerCancel(CANCEL_DURING_PROCESSING);
}

TEST_P(AsyncEnd2endServerTryCancelTest, ServerBidiStreamingTryCancelAfter) {
  TestBidiStreamingServerCancel(CANCEL_AFTER_PROCESSING);
}

std::vector<TestScenario> CreateTestScenarios(bool ,
                                              bool test_message_size_limit) {
  std::vector<TestScenario> scenarios;
  std::vector<std::string> credentials_types;
  std::vector<std::string> messages;

  auto insec_ok = [] {

    return GetCredentialsProvider()->GetChannelCredentials(
               kInsecureCredentialsType, nullptr) != nullptr;
  };

  if (insec_ok()) {
    credentials_types.push_back(kInsecureCredentialsType);
  }
  auto sec_list = GetCredentialsProvider()->GetSecureCredentialsTypeList();
  for (auto sec = sec_list.begin(); sec != sec_list.end(); sec++) {
    credentials_types.push_back(*sec);
  }
  CHECK(!credentials_types.empty());

  messages.push_back("Hello");
  if (test_message_size_limit) {
    for (size_t k = 1; k < GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH / 1024;
         k *= 32) {
      std::string big_msg;
      for (size_t i = 0; i < k * 1024; ++i) {
        char c = 'a' + (i % 26);
        big_msg += c;
      }
      messages.push_back(big_msg);
    }
    if (!BuiltUnderMsan()) {

      messages.push_back(
          std::string(GRPC_DEFAULT_MAX_RECV_MESSAGE_LENGTH - 100, 'a'));
    }
  }

  for (auto health_check_service : {false}) {
    for (auto msg = messages.begin(); msg != messages.end(); msg++) {
      for (auto cred = credentials_types.begin();
           cred != credentials_types.end(); ++cred) {
        scenarios.emplace_back(false, *cred, health_check_service, *msg);
      }
      if (insec_ok()) {
        scenarios.emplace_back(true, kInsecureCredentialsType,
                               health_check_service, *msg);
      }
    }
  }
  return scenarios;
}

INSTANTIATE_TEST_SUITE_P(AsyncEnd2end, AsyncEnd2endTest,
                         ::testing::ValuesIn(CreateTestScenarios(true, true)));
INSTANTIATE_TEST_SUITE_P(AsyncEnd2endServerTryCancel,
                         AsyncEnd2endServerTryCancelTest,
                         ::testing::ValuesIn(CreateTestScenarios(false,
                                                                 false)));

}
}
}

int main(int argc, char** argv) {

  grpc_core::ConfigVars::Overrides overrides;
  overrides.client_channel_backup_poll_interval_ms = 100;
  grpc_core::ConfigVars::SetOverrides(overrides);
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
