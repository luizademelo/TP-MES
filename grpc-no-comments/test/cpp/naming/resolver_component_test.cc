
// Copyright 2017 gRPC authors.

#include <errno.h>
#include <fcntl.h>
#include <grpc/grpc.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <string.h>

#include <string>
#include <thread>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "gmock/gmock.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/ares_resolver.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/load_balancing/grpclb/grpclb_balancer_addresses.h"
#include "src/core/resolver/dns/c_ares/grpc_ares_wrapper.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/util/crash.h"
#include "src/core/util/host_port.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/string.h"
#include "src/core/util/work_serializer.h"
#include "test/core/test_util/fake_udp_and_tcp_server.h"
#include "test/core/test_util/port.h"
#include "test/core/test_util/socket_use_after_close_detector.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/subprocess.h"
#include "test/cpp/util/test_config.h"

using ::grpc_event_engine::experimental::GetDefaultEventEngine;
using std::vector;
using testing::UnorderedElementsAreArray;

ABSL_FLAG(std::string, target_name, "", "Target name to resolve.");
ABSL_FLAG(std::string, do_ordered_address_comparison, "",
          "Whether or not to compare resolved addresses to expected "
          "addresses using an ordered comparison. This is useful for "
          "testing certain behaviors that involve sorting of resolved "
          "addresses. Note it would be better if this argument was a "
          "bool flag, but it's a string for ease of invocation from "
          "the generated python test runner.");
ABSL_FLAG(std::string, expected_addrs, "",
          "List of expected backend or balancer addresses in the form "
          "'<ip0:port0>,<is_balancer0>;<ip1:port1>,<is_balancer1>;...'. "
          "'is_balancer' should be bool, i.e. true or false.");
ABSL_FLAG(std::string, expected_chosen_service_config, "",
          "Expected service config json string that gets chosen (no "
          "whitespace). Empty for none.");
ABSL_FLAG(std::string, expected_service_config_error, "",
          "Expected service config error. Empty for none.");
ABSL_FLAG(std::string, local_dns_server_address, "",
          "Optional. This address is placed as the uri authority if present.");

ABSL_FLAG(
    std::string, enable_srv_queries, "",
    "Whether or not to enable SRV queries for the ares resolver instance."
    "It would be better if this arg could be bool, but the way that we "
    "generate "
    "the python script runner doesn't allow us to pass a gflags bool to this "
    "binary.");

ABSL_FLAG(
    std::string, enable_txt_queries, "",
    "Whether or not to enable TXT queries for the ares resolver instance."
    "It would be better if this arg could be bool, but the way that we "
    "generate "
    "the python script runner doesn't allow us to pass a gflags bool to this "
    "binary.");

ABSL_FLAG(
    std::string, inject_broken_nameserver_list, "",
    "Whether or not to configure c-ares to use a broken nameserver list, in "
    "which "
    "the first nameserver in the list is non-responsive, but the second one "
    "works, i.e "
    "serves the expected DNS records; using for testing such a real scenario."
    "It would be better if this arg could be bool, but the way that we "
    "generate "
    "the python script runner doesn't allow us to pass a gflags bool to this "
    "binary.");
ABSL_FLAG(std::string, expected_lb_policy, "",
          "Expected lb policy name that appears in resolver result channel "
          "arg. Empty for none.");

namespace {

class GrpcLBAddress final {
 public:
  GrpcLBAddress(std::string address, bool is_balancer)
      : is_balancer(is_balancer), address(std::move(address)) {}

  bool operator==(const GrpcLBAddress& other) const {
    return this->is_balancer == other.is_balancer &&
           this->address == other.address;
  }

  bool operator!=(const GrpcLBAddress& other) const {
    return !(*this == other);
  }

  bool is_balancer;
  std::string address;
};

vector<GrpcLBAddress> ParseExpectedAddrs(std::string expected_addrs) {
  std::vector<GrpcLBAddress> out;
  while (!expected_addrs.empty()) {

    size_t next_comma = expected_addrs.find(',');
    if (next_comma == std::string::npos) {
      grpc_core::Crash(absl::StrFormat(
          "Missing ','. Expected_addrs arg should be a semicolon-separated "
          "list of <ip-port>,<bool> pairs. Left-to-be-parsed arg is |%s|",
          expected_addrs.c_str()));
    }
    std::string next_addr = expected_addrs.substr(0, next_comma);
    expected_addrs = expected_addrs.substr(next_comma + 1, std::string::npos);

    size_t next_semicolon = expected_addrs.find(';');
    bool is_balancer = false;
    gpr_parse_bool_value(expected_addrs.substr(0, next_semicolon).c_str(),
                         &is_balancer);
    out.emplace_back(GrpcLBAddress(next_addr, is_balancer));
    if (next_semicolon == std::string::npos) {
      break;
    }
    expected_addrs =
        expected_addrs.substr(next_semicolon + 1, std::string::npos);
  }
  if (out.empty()) {
    grpc_core::Crash(
        "expected_addrs arg should be a semicolon-separated list of "
        "<ip-port>,<bool> pairs");
  }
  return out;
}

gpr_timespec TestDeadline(void) {
  return grpc_timeout_seconds_to_deadline(100);
}

struct ArgsStruct {
  gpr_event ev;
  gpr_mu* mu;
  bool done;
  grpc_pollset* pollset;
  grpc_pollset_set* pollset_set;
  std::shared_ptr<grpc_core::WorkSerializer> lock;
  grpc_channel_args* channel_args;
  vector<GrpcLBAddress> expected_addrs;
  std::string expected_service_config_string;
  std::string expected_service_config_error;
  std::string expected_lb_policy;
};

void ArgsInit(ArgsStruct* args) {
  gpr_event_init(&args->ev);
  args->pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(args->pollset, &args->mu);
  args->pollset_set = grpc_pollset_set_create();
  grpc_pollset_set_add_pollset(args->pollset_set, args->pollset);
  args->lock = std::make_shared<grpc_core::WorkSerializer>(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  args->done = false;
  args->channel_args = nullptr;
}

void DoNothing(void* , grpc_error_handle ) {}

void ArgsFinish(ArgsStruct* args) {
  CHECK(gpr_event_wait(&args->ev, TestDeadline()));
  grpc_pollset_set_del_pollset(args->pollset_set, args->pollset);
  grpc_pollset_set_destroy(args->pollset_set);
  grpc_closure DoNothing_cb;
  GRPC_CLOSURE_INIT(&DoNothing_cb, DoNothing, nullptr,
                    grpc_schedule_on_exec_ctx);
  grpc_pollset_shutdown(args->pollset, &DoNothing_cb);

  grpc_channel_args_destroy(args->channel_args);
  grpc_core::ExecCtx::Get()->Flush();
  grpc_pollset_destroy(args->pollset);
  gpr_free(args->pollset);
}

gpr_timespec NSecondDeadline(int seconds) {
  return gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                      gpr_time_from_seconds(seconds, GPR_TIMESPAN));
}

void PollPollsetUntilRequestDone(ArgsStruct* args) {

  gpr_timespec deadline = NSecondDeadline(20);
  while (true) {
    grpc_core::MutexLockForGprMu lock(args->mu);
    if (args->done) {
      break;
    }
    gpr_timespec time_left =
        gpr_time_sub(deadline, gpr_now(GPR_CLOCK_REALTIME));
    VLOG(2) << "done=" << args->done << ", time_left=" << time_left.tv_sec
            << "." << absl::StrFormat("%09d", time_left.tv_nsec);
    CHECK_GE(gpr_time_cmp(time_left, gpr_time_0(GPR_TIMESPAN)), 0);
    grpc_pollset_worker* worker = nullptr;
    grpc_core::ExecCtx exec_ctx;
    if (grpc_core::IsEventEngineDnsEnabled()) {

      GRPC_LOG_IF_ERROR(
          "pollset_work",
          grpc_pollset_work(
              args->pollset, &worker,
              grpc_core::Timestamp::FromTimespecRoundUp(deadline)));
    } else {
      GRPC_LOG_IF_ERROR(
          "pollset_work",
          grpc_pollset_work(
              args->pollset, &worker,
              grpc_core::Timestamp::FromTimespecRoundUp(NSecondDeadline(1))));
    }
  }
  gpr_event_set(&args->ev, reinterpret_cast<void*>(1));
}

void CheckServiceConfigResultLocked(const char* service_config_json,
                                    absl::Status service_config_error,
                                    ArgsStruct* args) {
  if (!args->expected_service_config_string.empty()) {
    ASSERT_NE(service_config_json, nullptr);
    EXPECT_EQ(service_config_json, args->expected_service_config_string);
  }
  if (args->expected_service_config_error.empty()) {
    EXPECT_TRUE(service_config_error.ok())
        << "Actual error: " << service_config_error.ToString();
  } else {
    EXPECT_THAT(service_config_error.ToString(),
                testing::HasSubstr(args->expected_service_config_error));
  }
}

void CheckLBPolicyResultLocked(const grpc_core::ChannelArgs channel_args,
                               ArgsStruct* args) {
  std::optional<absl::string_view> lb_policy_arg =
      channel_args.GetString(GRPC_ARG_LB_POLICY_NAME);
  if (!args->expected_lb_policy.empty()) {
    EXPECT_TRUE(lb_policy_arg.has_value());
    EXPECT_EQ(*lb_policy_arg, args->expected_lb_policy);
  } else {
    EXPECT_FALSE(lb_policy_arg.has_value());
  }
}

class ResultHandler : public grpc_core::Resolver::ResultHandler {
 public:
  static std::unique_ptr<grpc_core::Resolver::ResultHandler> Create(
      ArgsStruct* args) {
    return std::unique_ptr<grpc_core::Resolver::ResultHandler>(
        new ResultHandler(args));
  }

  explicit ResultHandler(ArgsStruct* args) : args_(args) {}

  void ReportResult(grpc_core::Resolver::Result result) override {
    CheckResult(result);
    grpc_core::MutexLockForGprMu lock(args_->mu);
    CHECK(!args_->done);
    args_->done = true;
    GRPC_LOG_IF_ERROR("pollset_kick",
                      grpc_pollset_kick(args_->pollset, nullptr));
  }

  virtual void CheckResult(const grpc_core::Resolver::Result& ) {}

 protected:
  ArgsStruct* args_struct() const { return args_; }

 private:
  ArgsStruct* args_;
};

class CheckingResultHandler : public ResultHandler {
 public:
  static std::unique_ptr<grpc_core::Resolver::ResultHandler> Create(
      ArgsStruct* args) {
    return std::unique_ptr<grpc_core::Resolver::ResultHandler>(
        new CheckingResultHandler(args));
  }

  explicit CheckingResultHandler(ArgsStruct* args) : ResultHandler(args) {}

  void CheckResult(const grpc_core::Resolver::Result& result) override {
    ASSERT_TRUE(result.addresses.ok()) << result.addresses.status().ToString();
    ArgsStruct* args = args_struct();
    std::vector<GrpcLBAddress> found_lb_addrs;
    AddActualAddresses(*result.addresses, false,
                       &found_lb_addrs);
    const grpc_core::EndpointAddressesList* balancer_addresses =
        grpc_core::FindGrpclbBalancerAddressesInChannelArgs(result.args);
    if (balancer_addresses != nullptr) {
      AddActualAddresses(*balancer_addresses, true,
                         &found_lb_addrs);
    }
    LOG(INFO) << "found " << result.addresses->size()
              << " backend addresses and "
              << (balancer_addresses == nullptr ? 0L
                                                : balancer_addresses->size())
              << " balancer addresses";
    if (args->expected_addrs.size() != found_lb_addrs.size()) {
      grpc_core::Crash(absl::StrFormat("found lb addrs size is: %" PRIdPTR
                                       ". expected addrs size is %" PRIdPTR,
                                       found_lb_addrs.size(),
                                       args->expected_addrs.size()));
    }
    if (absl::GetFlag(FLAGS_do_ordered_address_comparison) == "True") {
      EXPECT_EQ(args->expected_addrs, found_lb_addrs);
    } else if (absl::GetFlag(FLAGS_do_ordered_address_comparison) == "False") {
      EXPECT_THAT(args->expected_addrs,
                  UnorderedElementsAreArray(found_lb_addrs));
    } else {
      LOG(ERROR) << "Invalid for setting for --do_ordered_address_comparison. "
                    "Have "
                 << absl::GetFlag(FLAGS_do_ordered_address_comparison)
                 << ", want True or False";
      CHECK(0);
    }
    if (!result.service_config.ok()) {
      CheckServiceConfigResultLocked(nullptr, result.service_config.status(),
                                     args);
    } else if (*result.service_config == nullptr) {
      CheckServiceConfigResultLocked(nullptr, absl::OkStatus(), args);
    } else {
      CheckServiceConfigResultLocked(
          std::string((*result.service_config)->json_string()).c_str(),
          absl::OkStatus(), args);
    }
    if (args->expected_service_config_string.empty()) {
      CheckLBPolicyResultLocked(result.args, args);
    }
  }

 private:
  static void AddActualAddresses(
      const grpc_core::EndpointAddressesList& addresses, bool is_balancer,
      std::vector<GrpcLBAddress>* out) {
    for (size_t i = 0; i < addresses.size(); i++) {
      const grpc_core::EndpointAddresses& addr = addresses[i];
      std::string str =
          grpc_sockaddr_to_string(&addr.address(), true )
              .value();
      LOG(INFO) << str;
      out->emplace_back(GrpcLBAddress(std::move(str), is_balancer));
    }
  }
};

int g_fake_non_responsive_dns_server_port = -1;

void InjectBrokenNameServerList(ares_channel* channel) {
  struct ares_addr_port_node dns_server_addrs[2];
  memset(dns_server_addrs, 0, sizeof(dns_server_addrs));
  std::string unused_host;
  std::string local_dns_server_port;
  CHECK(grpc_core::SplitHostPort(
      absl::GetFlag(FLAGS_local_dns_server_address).c_str(), &unused_host,
      &local_dns_server_port));
  VLOG(2) << "Injecting broken nameserver list. Bad server address:|[::1]:"
          << g_fake_non_responsive_dns_server_port << "|. Good server address:"
          << absl::GetFlag(FLAGS_local_dns_server_address);

  dns_server_addrs[0].family = AF_INET6;
  (reinterpret_cast<char*>(&dns_server_addrs[0].addr.addr6))[15] = 0x1;
  dns_server_addrs[0].tcp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].udp_port = g_fake_non_responsive_dns_server_port;
  dns_server_addrs[0].next = &dns_server_addrs[1];

  dns_server_addrs[1].family = AF_INET;
  (reinterpret_cast<char*>(&dns_server_addrs[1].addr.addr4))[0] = 0x7f;
  (reinterpret_cast<char*>(&dns_server_addrs[1].addr.addr4))[3] = 0x1;
  dns_server_addrs[1].tcp_port = atoi(local_dns_server_port.c_str());
  dns_server_addrs[1].udp_port = atoi(local_dns_server_port.c_str());
  dns_server_addrs[1].next = nullptr;
  CHECK(ares_set_servers_ports(*channel, dns_server_addrs) == ARES_SUCCESS);
}

void StartResolvingLocked(grpc_core::Resolver* r) { r->StartLocked(); }

void RunResolvesRelevantRecordsTest(
    std::unique_ptr<grpc_core::Resolver::ResultHandler> (*CreateResultHandler)(
        ArgsStruct* args),
    grpc_core::ChannelArgs resolver_args) {
  grpc_core::ExecCtx exec_ctx;
  ArgsStruct args;
  ArgsInit(&args);
  args.expected_addrs = ParseExpectedAddrs(absl::GetFlag(FLAGS_expected_addrs));
  args.expected_service_config_string =
      absl::GetFlag(FLAGS_expected_chosen_service_config);
  args.expected_service_config_error =
      absl::GetFlag(FLAGS_expected_service_config_error);
  args.expected_lb_policy = absl::GetFlag(FLAGS_expected_lb_policy);

  std::string whole_uri;
  VLOG(2) << "resolver_component_test: --inject_broken_nameserver_list: "
          << absl::GetFlag(FLAGS_inject_broken_nameserver_list);
  std::unique_ptr<grpc_core::testing::FakeUdpAndTcpServer>
      fake_non_responsive_dns_server;
  if (absl::GetFlag(FLAGS_inject_broken_nameserver_list) == "True") {
    fake_non_responsive_dns_server = std::make_unique<
        grpc_core::testing::FakeUdpAndTcpServer>(
        grpc_core::testing::FakeUdpAndTcpServer::AcceptMode::
            kWaitForClientToSendFirstBytes,
        grpc_core::testing::FakeUdpAndTcpServer::CloseSocketUponCloseFromPeer);
    g_fake_non_responsive_dns_server_port =
        fake_non_responsive_dns_server->port();
    if (grpc_core::IsEventEngineDnsEnabled()) {
      event_engine_grpc_ares_test_only_inject_config =
          InjectBrokenNameServerList;
    } else {
      grpc_ares_test_only_inject_config = InjectBrokenNameServerList;
    }
    whole_uri = absl::StrCat("dns:///", absl::GetFlag(FLAGS_target_name));
  } else if (absl::GetFlag(FLAGS_inject_broken_nameserver_list) == "False") {
    LOG(INFO) << "Specifying authority in uris to: "
              << absl::GetFlag(FLAGS_local_dns_server_address);
    whole_uri = absl::StrFormat("dns://%s/%s",
                                absl::GetFlag(FLAGS_local_dns_server_address),
                                absl::GetFlag(FLAGS_target_name));
  } else {
    grpc_core::Crash("Invalid value for --inject_broken_nameserver_list.");
  }
  VLOG(2) << "resolver_component_test: --enable_srv_queries: "
          << absl::GetFlag(FLAGS_enable_srv_queries);

  if (absl::GetFlag(FLAGS_enable_srv_queries) == "True") {
    resolver_args = resolver_args.Set(GRPC_ARG_DNS_ENABLE_SRV_QUERIES, true);
  } else if (absl::GetFlag(FLAGS_enable_srv_queries) != "False") {
    grpc_core::Crash("Invalid value for --enable_srv_queries.");
  }
  VLOG(2) << "resolver_component_test: --enable_txt_queries: "
          << absl::GetFlag(FLAGS_enable_txt_queries);

  if (absl::GetFlag(FLAGS_enable_txt_queries) == "True") {

    resolver_args =
        resolver_args.Set(GRPC_ARG_SERVICE_CONFIG_DISABLE_RESOLUTION, false);
  } else if (absl::GetFlag(FLAGS_enable_txt_queries) != "False") {
    grpc_core::Crash("Invalid value for --enable_txt_queries.");
  }
  resolver_args = resolver_args.SetObject(GetDefaultEventEngine());

  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      grpc_core::CoreConfiguration::Get().resolver_registry().CreateResolver(
          whole_uri.c_str(), resolver_args, args.pollset_set, args.lock,
          CreateResultHandler(&args));
  auto* resolver_ptr = resolver.get();
  args.lock->Run([resolver_ptr]() { StartResolvingLocked(resolver_ptr); });
  grpc_core::ExecCtx::Get()->Flush();
  PollPollsetUntilRequestDone(&args);
  ArgsFinish(&args);
}

TEST(ResolverComponentTest, TestResolvesRelevantRecords) {
  RunResolvesRelevantRecordsTest(CheckingResultHandler::Create,
                                 grpc_core::ChannelArgs());
}

TEST(ResolverComponentTest, TestResolvesRelevantRecordsWithConcurrentFdStress) {
  grpc_core::testing::SocketUseAfterCloseDetector
      socket_use_after_close_detector;

  RunResolvesRelevantRecordsTest(ResultHandler::Create,
                                 grpc_core::ChannelArgs());
}

TEST(ResolverComponentTest, TestDoesntCrashOrHangWith1MsTimeout) {

  RunResolvesRelevantRecordsTest(
      ResultHandler::Create,
      grpc_core::ChannelArgs().Set(GRPC_ARG_DNS_ARES_QUERY_TIMEOUT_MS, 1));
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  grpc::testing::InitTest(&argc, &argv, true);
  grpc::testing::TestEnvironment env(&argc, argv);
  if (absl::GetFlag(FLAGS_target_name).empty()) {
    grpc_core::Crash("Missing target_name param.");
  }
  grpc_init();
  auto result = RUN_ALL_TESTS();
  grpc_shutdown();
  return result;
}
