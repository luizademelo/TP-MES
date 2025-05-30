
// Copyright 2015 gRPC authors.

#include "src/core/util/http_client/httpcli.h"

#include <ares.h>
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <string.h>
#include <sys/socket.h>

#include <memory>
#include <string>
#include <thread>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/time/clock.h"
#include "absl/time/time.h"
#include "gtest/gtest.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/subprocess.h"
#include "src/core/util/time.h"
#include "src/core/util/time_util.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/port.h"
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

class HttpRequestTest : public ::testing::Test {
 public:
  HttpRequestTest() {
    grpc_init();
    grpc_core::ExecCtx exec_ctx;
    grpc_pollset* pollset =
        static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(pollset, &mu_);
    pops_ = grpc_polling_entity_create_from_pollset(pollset);
  }
  ~HttpRequestTest() override {
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
        g_argc, g_argv, false );
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
  explicit RequestState(HttpRequestTest* test) : test(test) {}

  ~RequestState() {
    grpc_core::ExecCtx exec_ctx;
    grpc_http_response_destroy(&response);
  }

  HttpRequestTest* test;
  bool done = false;
  grpc_http_response response = {};
  grpc_pollset_set* pollset_set_to_destroy_eagerly = nullptr;
};

void OnFinish(void* arg, grpc_error_handle error) {
  RequestState* request_state = static_cast<RequestState*>(arg);
  if (request_state->pollset_set_to_destroy_eagerly != nullptr) {

    grpc_pollset_set_destroy(request_state->pollset_set_to_destroy_eagerly);
  }
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
  if (request_state->pollset_set_to_destroy_eagerly != nullptr) {

    grpc_pollset_set_destroy(request_state->pollset_set_to_destroy_eagerly);
  }
  grpc_http_response response = request_state->response;
  LOG(INFO) << "response status=" << response.status
            << " error=" << grpc_core::StatusToString(error);
  CHECK(!error.ok());
  request_state->test->RunAndKick(
      [request_state]() { request_state->done = true; });
}

TEST_F(HttpRequestTest, Get) {
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  std::string host = absl::StrFormat("localhost:%d", g_server_port);
  LOG(INFO) << "requesting from " << host;
  memset(&req, 0, sizeof(req));
  auto uri = grpc_core::URI::Create(
      "http", "", host, "/get",
      {{"foo", "bar"}, {"baz", "quux"}},
      "");
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Get(
          std::move(*uri), nullptr , pops(), &req,
          NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinish, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::RefCountedPtr<grpc_channel_credentials>(
              grpc_insecure_credentials_create()));
  http_request->Start();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
}

TEST_F(HttpRequestTest, Post) {
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  std::string host = absl::StrFormat("localhost:%d", g_server_port);
  LOG(INFO) << "posting to " << host;
  memset(&req, 0, sizeof(req));
  req.body = const_cast<char*>("hello");
  req.body_length = 5;
  auto uri = grpc_core::URI::Create(
      "http", "", host, "/post",
      {{"foo", "bar"}, {"mumble", "frotz"}},
      "");
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Post(
          std::move(*uri), nullptr , pops(), &req,
          NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinish, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::RefCountedPtr<grpc_channel_credentials>(
              grpc_insecure_credentials_create()));
  http_request->Start();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
}

int g_fake_non_responsive_dns_server_port;

void InjectNonResponsiveDNSServer(ares_channel* channel) {
  VLOG(2) << "Injecting broken nameserver list. Bad server address:|[::1]:"
          << g_fake_non_responsive_dns_server_port << "|.";

  struct ares_addr_port_node dns_server_addrs[1];
  dns_server_addrs[0].family = AF_INET6;
  (reinterpret_cast<char*>(&dns_server_addrs[0].addr.addr6))[15] = 0x1;
  dns_server_addrs[0].tcp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].udp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].next = nullptr;
  CHECK(ares_set_servers_ports(*channel, dns_server_addrs) == ARES_SUCCESS);
}

TEST_F(HttpRequestTest, CancelGetDuringDNSResolution) {

  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  g_fake_non_responsive_dns_server_port = fake_dns_server.port();
  void (*prev_test_only_inject_config)(ares_channel* channel) =
      grpc_ares_test_only_inject_config;
  grpc_ares_test_only_inject_config = InjectNonResponsiveDNSServer;

  int kNumThreads = 10;
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    threads.push_back(std::thread([this]() {
      RequestState request_state(this);
      grpc_http_request req;
      grpc_core::ExecCtx exec_ctx;
      memset(&req, 0, sizeof(grpc_http_request));
      auto uri = grpc_core::URI::Create(
          "http", "",
          "dont-care-since-wont-be-resolved.test.com:443", "/get",
          {} , "" );
      CHECK(uri.ok());
      grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
          grpc_core::HttpRequest::Get(
              std::move(*uri), nullptr , pops(), &req,
              NSecondsTime(120),
              GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                                  grpc_schedule_on_exec_ctx),
              &request_state.response,
              grpc_core::RefCountedPtr<grpc_channel_credentials>(
                  grpc_insecure_credentials_create()));
      http_request->Start();
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
  grpc_ares_test_only_inject_config = prev_test_only_inject_config;
}

TEST_F(HttpRequestTest, CancelGetWhileReadingResponse) {

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
      auto uri = grpc_core::URI::Create(
          "http", "", fake_http_server_ptr->address(), "/get",
          {} , "" );
      CHECK(uri.ok());
      grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
          grpc_core::HttpRequest::Get(
              std::move(*uri), nullptr , pops(), &req,
              NSecondsTime(120),
              GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                                  grpc_schedule_on_exec_ctx),
              &request_state.response,
              grpc_core::RefCountedPtr<grpc_channel_credentials>(
                  grpc_insecure_credentials_create()));
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

TEST_F(HttpRequestTest, CancelGetRacesWithConnectionFailure) {

  int fake_server_port = grpc_pick_unused_port_or_die();
  std::string fake_server_address =
      absl::StrCat("[::1]:", std::to_string(fake_server_port));

  int kNumThreads = 10;
  std::vector<std::thread> threads;
  threads.reserve(kNumThreads);
  for (int i = 0; i < kNumThreads; i++) {
    threads.push_back(std::thread([this, fake_server_address]() {
      RequestState request_state(this);
      grpc_http_request req;
      grpc_core::ExecCtx exec_ctx;
      memset(&req, 0, sizeof(req));
      auto uri = grpc_core::URI::Create(
          "http", "", fake_server_address, "/get",
          {} , "" );
      CHECK(uri.ok());
      grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
          grpc_core::HttpRequest::Get(
              std::move(*uri), nullptr , pops(), &req,
              NSecondsTime(120),
              GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                                  grpc_schedule_on_exec_ctx),
              &request_state.response,
              grpc_core::RefCountedPtr<grpc_channel_credentials>(
                  grpc_insecure_credentials_create()));

      http_request->Start();
      exec_ctx.Flush();

      std::thread cancel_thread([&http_request]() {
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

TEST_F(HttpRequestTest, CallerPollentsAreNotReferencedAfterCallbackIsRan) {

  int fake_server_port = grpc_pick_unused_port_or_die();
  std::string fake_server_address =
      absl::StrCat("[::1]:", std::to_string(fake_server_port));
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  memset(&req, 0, sizeof(req));
  req.path = const_cast<char*>("/get");
  request_state.pollset_set_to_destroy_eagerly = grpc_pollset_set_create();
  grpc_polling_entity_add_to_pollset_set(
      pops(), request_state.pollset_set_to_destroy_eagerly);
  grpc_polling_entity wrapped_pollset_set_to_destroy_eagerly =
      grpc_polling_entity_create_from_pollset_set(
          request_state.pollset_set_to_destroy_eagerly);
  auto uri =
      grpc_core::URI::Create("http", "", fake_server_address,
                             "/get", {} , "" );
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Get(
          std::move(*uri), nullptr ,
          &wrapped_pollset_set_to_destroy_eagerly, &req, NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::RefCountedPtr<grpc_channel_credentials>(
              grpc_insecure_credentials_create()));

  http_request->Start();
  exec_ctx.Flush();
  http_request.reset();

  exec_ctx.Flush();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
}

void CancelRequest(grpc_core::HttpRequest* req) {
  LOG(INFO) << "test only HttpRequest::OnHandshakeDone intercept orphaning "
               "request: "
            << req;
  req->Orphan();
}

TEST_F(HttpRequestTest,
       CancelDuringSecurityHandshakeButHandshakeStillSucceeds) {
  RequestState request_state(this);
  grpc_http_request req;
  grpc_core::ExecCtx exec_ctx;
  std::string host = absl::StrFormat("localhost:%d", g_server_port);
  LOG(INFO) << "requesting from " << host;
  memset(&req, 0, sizeof(req));
  auto uri = grpc_core::URI::Create("http", "", host, "/get",
                                    {} , "" );
  CHECK(uri.ok());
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> http_request =
      grpc_core::HttpRequest::Get(
          std::move(*uri), nullptr , pops(), &req,
          NSecondsTime(15),
          GRPC_CLOSURE_CREATE(OnFinishExpectFailure, &request_state,
                              grpc_schedule_on_exec_ctx),
          &request_state.response,
          grpc_core::RefCountedPtr<grpc_channel_credentials>(
              grpc_insecure_credentials_create()));
  grpc_core::HttpRequest::TestOnlySetOnHandshakeDoneIntercept(CancelRequest);
  http_request->Start();
  (void)http_request.release();
  exec_ctx.Flush();
  PollUntil([&request_state]() { return request_state.done; },
            AbslDeadlineSeconds(60));
  grpc_core::HttpRequest::TestOnlySetOnHandshakeDoneIntercept(nullptr);
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);

  g_argc = argc;
  g_argv = argv;

  return RUN_ALL_TESTS();
}
