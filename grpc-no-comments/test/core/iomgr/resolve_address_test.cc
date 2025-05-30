
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/resolve_address.h"

#include <address_sorting/address_sorting.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <string.h>

#include "absl/functional/bind_front.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/match.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/test_config.h"

namespace {

grpc_core::Timestamp NSecDeadline(int seconds) {
  return grpc_core::Timestamp::FromTimespecRoundUp(
      grpc_timeout_seconds_to_deadline(seconds));
}

const char* g_resolver_type = "";

class ResolveAddressTest : public ::testing::Test {
 public:
  ResolveAddressTest() {
    grpc_init();
    grpc_core::ExecCtx exec_ctx;
    pollset_ = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(pollset_, &mu_);
    pollset_set_ = grpc_pollset_set_create();
    grpc_pollset_set_add_pollset(pollset_set_, pollset_);
    default_inject_config_ = grpc_ares_test_only_inject_config;
  }

  ~ResolveAddressTest() override {
    {
      grpc_core::ExecCtx exec_ctx;
      grpc_pollset_set_del_pollset(pollset_set_, pollset_);
      grpc_pollset_set_destroy(pollset_set_);
      grpc_closure do_nothing_cb;
      GRPC_CLOSURE_INIT(&do_nothing_cb, DoNothing, nullptr,
                        grpc_schedule_on_exec_ctx);
      gpr_mu_lock(mu_);
      grpc_pollset_shutdown(pollset_, &do_nothing_cb);
      gpr_mu_unlock(mu_);

      grpc_core::ExecCtx::Get()->Flush();
      grpc_pollset_destroy(pollset_);
      gpr_free(pollset_);

      grpc_ares_test_only_inject_config = default_inject_config_;
    }
    grpc_shutdown();
  }

  void PollPollsetUntilRequestDone() {

    grpc_core::Timestamp deadline = NSecDeadline(90);
    while (true) {
      grpc_core::ExecCtx exec_ctx;
      {
        grpc_core::MutexLockForGprMu lock(mu_);
        if (done_) {
          break;
        }
        grpc_core::Duration time_left = deadline - grpc_core::Timestamp::Now();
        VLOG(2) << "done=" << done_ << ", time_left=" << time_left.millis();
        ASSERT_GE(time_left, grpc_core::Duration::Zero());
        grpc_pollset_worker* worker = nullptr;
        GRPC_LOG_IF_ERROR("pollset_work", grpc_pollset_work(pollset_, &worker,
                                                            NSecDeadline(1)));
      }
    }
  }

  void MustSucceed(absl::StatusOr<std::vector<grpc_resolved_address>> result) {
    EXPECT_EQ(result.status(), absl::OkStatus());
    EXPECT_FALSE(result->empty());
    Finish();
  }

  void MustFail(absl::StatusOr<std::vector<grpc_resolved_address>> result) {
    EXPECT_NE(result.status(), absl::OkStatus());
    Finish();
  }

  void MustFailExpectCancelledErrorMessage(
      absl::StatusOr<std::vector<grpc_resolved_address>> result) {
    EXPECT_NE(result.status(), absl::OkStatus());
    EXPECT_THAT(result.status().ToString(),
                testing::HasSubstr("DNS query cancelled"));
    Finish();
  }

  void DontCare(
      absl::StatusOr<std::vector<grpc_resolved_address>> ) {
    Finish();
  }

  void MustSucceedWithIPv6First(
      absl::StatusOr<std::vector<grpc_resolved_address>> result) {
    EXPECT_EQ(result.status(), absl::OkStatus());
    EXPECT_TRUE(!result->empty() &&
                reinterpret_cast<const struct sockaddr*>((*result)[0].addr)
                        ->sa_family == AF_INET6);
    Finish();
  }

  void MustSucceedWithIPv4First(
      absl::StatusOr<std::vector<grpc_resolved_address>> result) {
    EXPECT_EQ(result.status(), absl::OkStatus());
    EXPECT_TRUE(!result->empty() &&
                reinterpret_cast<const struct sockaddr*>((*result)[0].addr)
                        ->sa_family == AF_INET);
    Finish();
  }

  void MustNotBeCalled(
      absl::StatusOr<std::vector<grpc_resolved_address>> ) {
    FAIL() << "This should never be called";
  }

  void Finish() {
    grpc_core::MutexLockForGprMu lock(mu_);
    done_ = true;
    GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(pollset_, nullptr));
  }

  grpc_pollset_set* pollset_set() const { return pollset_set_; }

 protected:
  void SetUp() override {
    if (grpc_core::IsEventEngineForAllOtherEndpointsEnabled() &&
        !grpc_event_engine::experimental::
            EventEngineExperimentDisabledForPython()) {
      GTEST_SKIP()
          << "Skipping all legacy ResolveAddress tests. The "
             "event_engine_for_all_other_endpoints experiment is enabled, so "
             "the grpc_core::GetDNSResolver() API is not in use. Further, the "
             "experiment replaces iomgr grpc_fds with minimal implementations. "
             "The legacy resolvers use the grpc_fd APIs directly, so these "
             "tests would fail.";
    }
  }

 private:
  static void DoNothing(void* , grpc_error_handle ) {}

  gpr_mu* mu_;
  bool done_ = false;
  grpc_pollset* pollset_;
  grpc_pollset_set* pollset_set_;

  void (*default_inject_config_)(ares_channel* channel) = nullptr;
};

}

TEST_F(ResolveAddressTest, Localhost) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, this), "localhost:1",
      "", grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, DefaultPort) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, this), "localhost",
      "1", grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, LocalhostResultHasIPv6First) {
  if (std::string(g_resolver_type) != "ares") {
    GTEST_SKIP() << "this test is only valid with the c-ares resolver";
  }
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceedWithIPv6First, this),
      "localhost:1", "", grpc_core::kDefaultDNSRequestTimeout, pollset_set(),
      "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

namespace {

bool IPv6DisabledGetSourceAddr(address_sorting_source_addr_factory* ,
                               const address_sorting_address* dest_addr,
                               address_sorting_address* source_addr) {

  if (address_sorting_abstract_get_family(dest_addr) ==
      ADDRESS_SORTING_AF_INET6) {
    return false;
  }
  memcpy(source_addr->addr, &dest_addr->addr, dest_addr->len);
  source_addr->len = dest_addr->len;
  return true;
}

void DeleteSourceAddrFactory(address_sorting_source_addr_factory* factory) {
  delete factory;
}

const address_sorting_source_addr_factory_vtable
    kMockIpv6DisabledSourceAddrFactoryVtable = {
        IPv6DisabledGetSourceAddr,
        DeleteSourceAddrFactory,
};

}

TEST_F(ResolveAddressTest, LocalhostResultHasIPv4FirstWhenIPv6IsntAvailable) {
  if (std::string(g_resolver_type) != "ares") {
    GTEST_SKIP() << "this test is only valid with the c-ares resolver";
  }

  address_sorting_source_addr_factory* mock =
      new address_sorting_source_addr_factory();
  mock->vtable = &kMockIpv6DisabledSourceAddrFactoryVtable;
  address_sorting_override_source_addr_factory_for_testing(mock);

  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceedWithIPv4First, this),
      "localhost:1", "", grpc_core::kDefaultDNSRequestTimeout, pollset_set(),
      "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, NonNumericDefaultPort) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, this), "localhost",
      "http", grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, MissingDefaultPort) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustFail, this), "localhost", "",
      grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, IPv6WithPort) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, this),
      "[2001:db8::1]:1", "", grpc_core::kDefaultDNSRequestTimeout,
      pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

void TestIPv6WithoutPort(ResolveAddressTest* test, const char* target) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, test), target, "80",
      grpc_core::kDefaultDNSRequestTimeout, test->pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  test->PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, IPv6WithoutPortNoBrackets) {
  TestIPv6WithoutPort(this, "2001:db8::1");
}

TEST_F(ResolveAddressTest, IPv6WithoutPortWithBrackets) {
  TestIPv6WithoutPort(this, "[2001:db8::1]");
}

TEST_F(ResolveAddressTest, IPv6WithoutPortV4MappedV6) {
  TestIPv6WithoutPort(this, "2001:db8::1.2.3.4");
}

void TestInvalidIPAddress(ResolveAddressTest* test, const char* target) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustFail, test), target, "",
      grpc_core::kDefaultDNSRequestTimeout, test->pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  test->PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, InvalidIPv4Addresses) {
  TestInvalidIPAddress(this, "293.283.1238.3:1");
}

TEST_F(ResolveAddressTest, InvalidIPv6Addresses) {
  TestInvalidIPAddress(this, "[2001:db8::11111]:1");
}

void TestUnparsableHostPort(ResolveAddressTest* test, const char* target) {
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustFail, test), target, "1",
      grpc_core::kDefaultDNSRequestTimeout, test->pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  test->PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, UnparsableHostPortsOnlyBracket) {
  TestUnparsableHostPort(this, "[");
}

TEST_F(ResolveAddressTest, UnparsableHostPortsMissingRightBracket) {
  TestUnparsableHostPort(this, "[::1");
}

TEST_F(ResolveAddressTest, UnparsableHostPortsBadPort) {
  TestUnparsableHostPort(this, "[::1]bad");
}

TEST_F(ResolveAddressTest, UnparsableHostPortsBadIPv6) {
  TestUnparsableHostPort(this, "[1.2.3.4]");
}

TEST_F(ResolveAddressTest, UnparsableHostPortsBadLocalhost) {
  TestUnparsableHostPort(this, "[localhost]");
}

TEST_F(ResolveAddressTest, UnparsableHostPortsBadLocalhostWithPort) {
  TestUnparsableHostPort(this, "[localhost]:1");
}

TEST_F(ResolveAddressTest, ImmediateCancel) {
  grpc_core::ExecCtx exec_ctx;
  auto resolver = grpc_core::GetDNSResolver();
  auto request_handle = resolver->LookupHostname(
      absl::bind_front(&ResolveAddressTest::DontCare, this), "localhost:1", "1",
      grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  if (resolver->Cancel(request_handle)) {
    Finish();
  }
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, CancelDoesNotSucceed) {
  grpc_core::ExecCtx exec_ctx;
  auto resolver = grpc_core::GetDNSResolver();
  auto request_handle = resolver->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustSucceed, this), "localhost:1",
      "1", grpc_core::kDefaultDNSRequestTimeout, pollset_set(), "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
  ASSERT_FALSE(resolver->Cancel(request_handle));
}

namespace {

int g_fake_non_responsive_dns_server_port;

void InjectNonResponsiveDNSServer(ares_channel* channel) {
  VLOG(2) << "Injecting broken nameserver list. Bad server address:|[::1]:"
          << g_fake_non_responsive_dns_server_port << "|.";

  struct ares_addr_port_node dns_server_addrs[1];
  memset(dns_server_addrs, 0, sizeof(dns_server_addrs));
  dns_server_addrs[0].family = AF_INET6;
  (reinterpret_cast<char*>(&dns_server_addrs[0].addr.addr6))[15] = 0x1;
  dns_server_addrs[0].tcp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].udp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].next = nullptr;
  ASSERT_EQ(ares_set_servers_ports(*channel, dns_server_addrs), ARES_SUCCESS);
}

}

TEST_F(ResolveAddressTest, CancelWithNonResponsiveDNSServer) {
  if (std::string(g_resolver_type) != "ares") {
    GTEST_SKIP() << "the native resolver doesn't support cancellation, so we "
                    "can only test this with c-ares";
  }

  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  g_fake_non_responsive_dns_server_port = fake_dns_server.port();
  grpc_ares_test_only_inject_config = InjectNonResponsiveDNSServer;

  grpc_core::ExecCtx exec_ctx;
  auto resolver = grpc_core::GetDNSResolver();
  auto request_handle = resolver->LookupHostname(
      absl::bind_front(&ResolveAddressTest::MustNotBeCalled, this),
      "foo.bar.com:1", "1", grpc_core::kDefaultDNSRequestTimeout, pollset_set(),
      "");
  grpc_core::ExecCtx::Get()->Flush();
  ASSERT_TRUE(resolver->Cancel(request_handle));
  Finish();

  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

class PollsetSetWrapper {
 public:
  static std::unique_ptr<PollsetSetWrapper> Create() {
    return absl::WrapUnique<PollsetSetWrapper>(new PollsetSetWrapper());
  }

  ~PollsetSetWrapper() {
    grpc_pollset_set_del_pollset(pss_, ps_);
    grpc_pollset_set_destroy(pss_);
    grpc_pollset_shutdown(ps_, nullptr);
    grpc_core::ExecCtx::Get()->Flush();
    grpc_pollset_destroy(ps_);
    gpr_free(ps_);
    VLOG(2) << "PollsetSetWrapper:" << this << " deleted";
  }

  grpc_pollset_set* pollset_set() { return pss_; }

 private:
  PollsetSetWrapper() {
    ps_ = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
    grpc_pollset_init(ps_, &mu_);
    pss_ = grpc_pollset_set_create();
    grpc_pollset_set_add_pollset(pss_, ps_);
    VLOG(2) << "PollsetSetWrapper:" << this << " created";
  }

  gpr_mu* mu_;
  grpc_pollset* ps_;
  grpc_pollset_set* pss_;
};

TEST_F(ResolveAddressTest, DeleteInterestedPartiesAfterCancellation) {

  if (absl::string_view(g_resolver_type) != "ares") {
    GTEST_SKIP() << "the native resolver doesn't support cancellation, so we "
                    "can only test this with c-ares";
  }

  grpc_core::testing::FakeUdpAndTcpServer fake_dns_server(
      grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
          kWaitForClientToSendFirstBytes,
      grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
  g_fake_non_responsive_dns_server_port = fake_dns_server.port();
  grpc_ares_test_only_inject_config = InjectNonResponsiveDNSServer;
  {
    grpc_core::ExecCtx exec_ctx;

    std::unique_ptr<PollsetSetWrapper> pss = PollsetSetWrapper::Create();

    auto resolver = grpc_core::GetDNSResolver();
    auto request_handle = resolver->LookupHostname(
        absl::bind_front(&ResolveAddressTest::MustNotBeCalled, this),
        "foo.bar.com:1", "1", grpc_core::kDefaultDNSRequestTimeout,
        pss->pollset_set(), "");
    grpc_core::ExecCtx::Get()->Flush();
    ASSERT_TRUE(resolver->Cancel(request_handle));
  }
  {

    grpc_core::ExecCtx ctx;
    Finish();
  }
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, StressTestTargetNameDeletion) {

  constexpr size_t kIterations = 100;
  auto resolver = grpc_core::GetDNSResolver();
  std::atomic<size_t> resolved_count{0};
  for (size_t i = 0; i < kIterations; i++) {
    grpc_core::ExecCtx exec_ctx;

    auto* target = new std::string("arst");
    resolver->LookupHostname(
        [&resolved_count](
            absl::StatusOr<std::vector<grpc_resolved_address>> ) {
          ++resolved_count;
        },
        *target, "8080", grpc_core::Duration::Milliseconds(10), pollset_set(),
        "");
    delete target;
  }
  while (resolved_count.load() != kIterations) {
    absl::SleepFor(absl::Milliseconds(10));
  }
}

TEST_F(ResolveAddressTest, NativeResolverCannotLookupSRVRecords) {
  if (absl::string_view(g_resolver_type) == "ares") {
    GTEST_SKIP() << "this test is only for native resolvers";
  }
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupSRV(
      [this](absl::StatusOr<std::vector<grpc_resolved_address>> error) {
        grpc_core::ExecCtx exec_ctx;
        EXPECT_EQ(error.status().code(), absl::StatusCode::kUnimplemented);
        Finish();
      },
      "localhost", grpc_core::kDefaultDNSRequestTimeout, pollset_set(),
      "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

TEST_F(ResolveAddressTest, NativeResolverCannotLookupTXTRecords) {
  if (absl::string_view(g_resolver_type) == "ares") {
    GTEST_SKIP() << "this test is only for native resolvers";
  }
  grpc_core::ExecCtx exec_ctx;
  grpc_core::GetDNSResolver()->LookupTXT(
      [this](absl::StatusOr<std::string> error) {
        grpc_core::ExecCtx exec_ctx;
        EXPECT_EQ(error.status().code(), absl::StatusCode::kUnimplemented);
        Finish();
      },
      "localhost", grpc_core::kDefaultDNSRequestTimeout, pollset_set(),
      "");
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone();
}

int main(int argc, char** argv) {
  if (grpc_core::IsPollsetAlternativeEnabled()) {
    LOG(WARNING) << "iomgr resolver tests are disabled since the pollset "
                    "alternative experiment breaks some iomgr APIs";
    return 0;
  }

  if (absl::StrContains(std::string(argv[0]), "using_native_resolver")) {
    g_resolver_type = "native";
  } else if (absl::StrContains(std::string(argv[0]), "using_ares_resolver")) {
    g_resolver_type = "ares";
  } else {
    CHECK(0);
  }
  grpc_core::ConfigVars::Overrides overrides;
  overrides.dns_resolver = g_resolver_type;
  grpc_core::ConfigVars::SetOverrides(overrides);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestEnvironment env(&argc, argv);
  const auto result = RUN_ALL_TESTS();
  return result;
}
