
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/util/http_client/httpcli.h"
#include "src/core/util/http_client/httpcli_ssl_credentials.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/subprocess.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_util.h"
#include "src/core/util/uri.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/test_config.h"
#include "test/core/util/http_client/httpcli_test_util.h"

namespace {

grpc_core::Timestamp NSecondsTime(int seconds) {
  return grpc_core::Timestamp::FromTimespecRoundUp(
      grpc_timeout_seconds_to_deadline(seconds));
}

absl::Time AbslDeadlineSeconds(int s) {
  return grpc_core::ToAbslTime(grpc_timeout_seconds_to_deadline(s));
}

int g_argc;
char** g_argv;
int g_server_port;
gpr_subprocess* g_server;

class HttpsCliTest : public ::testing::Test {
 public:
  HttpsCliTest() {
    grpc_init();
    grpc_core::ExecCtx exec_ctx;
    grpc_pollset* pollset =
        static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(pollset, &mu_);
    pops_ = grpc_polling_entity_create_from_pollset(pollset);
  }
  ~HttpsCliTest() override {
    {
      grpc_core::ExecCtx exec_ctx;
      grpc_pollset_shutdown(
          grpc_polling_entity_pollset(&pops_),
          GRPC_CLOSURE_CREATE(DestroyPops, &pops_, grpc_schedule_on_exec_ctx));
    }
    grpc_shutdown();
  }

  void RunAndKick(const std::function<void()>& f) {
    grpc_core::MutexLockForGprMu lock(mu_);
    f();
    CHECK(GRPC_LOG_IF_ERROR(
        "pollset_kick",
        grpc_pollset_kick(grpc_polling_entity_pollset(&pops_), nullptr)));
  }

  void PollUntil(const std::function<bool()>& predicate, absl::Time deadline) {
    gpr_mu_lock(mu_);
    while (!predicate()) {
      CHECK(absl::Now() < deadline);
      grpc_pollset_worker* worker = nullptr;
      CHECK(GRPC_LOG_IF_ERROR(
          "pollset_work", grpc_pollset_work(grpc_polling_entity_pollset(&pops_),
                                            &worker, NSecondsTime(1))));
      gpr_mu_unlock(mu_);
      gpr_mu_lock(mu_);
    }
    gpr_mu_unlock(mu_);
  }

  grpc_polling_entity* pops() { return &pops_; }

 protected:
  static void SetUpTestSuite() {
    auto test_server = grpc_core::testing::StartHttpRequestTestServer(
        g_argc, g_argv, true );
    g_server = test_server.server;
    g_server_port = test_server.port;
  }

  static void TearDownTestSuite() { gpr_subprocess_destroy(g_server); }

 private:
  static void DestroyPops(void* p, grpc_error_handle ) {
    grpc_polling_entity* pops = static_cast<grpc_polling_entity*>(p);
    grpc_pollset_destroy(grpc_polling_entity_pollset(pops));
    gpr_free(grpc_polling_entity_pollset(pops));
  }

  gpr_mu* mu_;
  grpc_polling_entity pops_;
};

struct RequestState {
  explicit RequestState(HttpsCliTest* test) : test(test) {}

  ~RequestState() {
    grpc_core::ExecCtx exec_ctx;
    grpc_http_response_destroy(&response);
  }

  HttpsCliTest* test;
  bool done = false;
  grpc_http_response response = {};
};

void OnFinish(void* arg, grpc_error_handle error) {
  RequestState* request_state = static_cast<RequestState*>(arg);
  const char* expect =
      "<html><head><title>Hello world!</title></head>"
      "<body><p>This is a test</p></body></html>";
  grpc_http_response response = request_state->response;
  LOG(INFO) << "response status=" << response.status
            << " error=" << grpc_core::StatusToString(error);
  CHECK(error.ok());
  CHECK_EQ(response.status, 200);
  CHECK(response.body_length == strlen(expect));
  CHECK_EQ(memcmp(expect, response.body, response.body_length), 0);
  request_state->test->RunAndKick(
      [request_state]() { request_state->done = true; });
}

void OnFinishExpectFailure(void* arg, grpc_error_handle error) {
  RequestState* request_state = static_cast<RequestState*>(arg);
  grpc_http_response response = request_state->response;
  LOG(INFO) << "response status=" << response.status
            << " error=" << grpc_core::StatusToString(error);
  CHECK(!error.ok());
  request_state->test->RunAndKick(
      [request_state]() { request_state->done = true; });
}

TEST_F(HttpsCliTest, Get) {
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  std::string host = absl::StrFormat("localhost:%d", g_server_port);
  LOG(INFO) << "requesting from " << host;
  memset(&req, 0, sizeof(req));
  grpc_arg ssl_override_arg = grpc_channel_arg_string_create(
      const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
      const_cast<char*>("foo.test.google.fr"));
  grpc_channel_args args = {1, &ssl_override_arg};
  auto uri = grpc_core::URI::Create(
      "https", "", host, "/get",
      {{"foo", "bar"}, {"baz", "quux"}},
      "");
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Get(
          std::move(*uri), &args, pops(), &req, NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinish, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::CreateHttpRequestSSLCredentials());
  http_request->Start();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
}

TEST_F(HttpsCliTest, Post) {
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  std::string host = absl::StrFormat("localhost:%d", g_server_port);
  LOG(INFO) << "posting to " << host;
  memset(&req, 0, sizeof(req));
  req.body = const_cast<char*>("hello");
  req.body_length = 5;
  grpc_arg ssl_override_arg = grpc_channel_arg_string_create(
      const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
      const_cast<char*>("foo.test.google.fr"));
  grpc_channel_args args = {1, &ssl_override_arg};
  auto uri = grpc_core::URI::Create(
      "https", "", host, "/post",
      {{"foo", "bar"}, {"mumble", "frotz"}},
      "");
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Post(
          std::move(*uri), &args , pops(), &req,
          NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinish, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::CreateHttpRequestSSLCredentials());
  http_request->Start();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
}

TEST_F(HttpsCliTest, CancelGetDuringSSLHandshake) {

  grpc_core::testing::FakeUdpAndTcpServer fake_http_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);

  int kNumThreads = 10;
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    grpc_core::testing::FakeUdpAndTcpServer* fake_http_server_ptr =
        &fake_http_server;
    threads.push_back(std::thread([this, fake_http_server_ptr]() {
      RequestState request_state(this);
      grpc_http_request req;
      grpc_core::ExecCtx exec_ctx;
      memset(&req, 0, sizeof(req));
      grpc_arg ssl_override_arg = grpc_channel_arg_string_create(
          const_cast<char*>(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG),
          const_cast<char*>("foo.test.google.fr"));
      grpc_channel_args args = {1, &ssl_override_arg};
      auto uri = grpc_core::URI::Create(
          "https", "", fake_http_server_ptr->address(), "/get",
          {} , "" );
      grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
          grpc_core::HttpRequest::Get(
              std::move(*uri), &args, pops(), &req, NSecondsTime(120),
              GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                                  grpc_schedule_on_exec_ctx),
              &request_state.response,
              grpc_core::CreateHttpRequestSSLCredentials());

      http_request->Start();
      exec_ctx.Flush();
      std::thread cancel_thread([&http_request]() {

        gpr_sleep_until(grpc_timeout_seconds_to_deadline(1));
        grpc_core::ExecCtx exec_ctx;
        http_request.reset();
      });

      PollUntil([&request_state]() { return request_state.done; },
                AbslDeadlineSeconds(60));
      cancel_thread.join();
    }));
  }
  for (auto& t : threads) {
    t.join();
  }
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);

  g_argc = argc;
  g_argv = argv;

  return RUN_ALL_TESTS();
}
