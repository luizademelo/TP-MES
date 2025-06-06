
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <net/if.h>
#include <string.h>
#include <sys/un.h>

#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/iomgr.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/util/crash.h"
#include "src/core/util/env.h"
#include "src/core/util/string.h"
#include "src/core/util/thd.h"
#include "src/core/util/time.h"
#include "src/core/util/useful.h"
#include "test/core/test_util/cmdline.h"
#include "test/core/test_util/test_config.h"

static gpr_timespec test_deadline(void) {
  return grpc_timeout_seconds_to_deadline(100);
}

typedef struct args_struct {
  grpc_core::Thread thd;
  gpr_event ev;
  gpr_mu* mu;
  bool done;
  grpc_pollset* pollset;
  grpc_pollset_set* pollset_set;
} args_struct;

static void do_nothing(void* , grpc_error_handle ) {}

void args_init(args_struct* args) {
  gpr_event_init(&args->ev);
  args->pollset = static_cast<grpc_pollset*>(gpr_zalloc(grpc_pollset_size()));
  grpc_pollset_init(args->pollset, &args->mu);
  args->pollset_set = grpc_pollset_set_create();
  grpc_pollset_set_add_pollset(args->pollset_set, args->pollset);
  args->done = false;
}

void args_finish(args_struct* args) {
  ASSERT_TRUE(gpr_event_wait(&args->ev, test_deadline()));
  args->thd.Join();

  grpc_pollset_set_del_pollset(args->pollset_set, args->pollset);
  grpc_pollset_set_destroy(args->pollset_set);
  grpc_closure do_nothing_cb;
  GRPC_CLOSURE_INIT(&do_nothing_cb, do_nothing, nullptr,
                    grpc_schedule_on_exec_ctx);
  grpc_pollset_shutdown(args->pollset, &do_nothing_cb);

  grpc_core::ExecCtx::Get()->Flush();
  grpc_pollset_destroy(args->pollset);
  gpr_free(args->pollset);
}

static grpc_core::Timestamp n_sec_deadline(int seconds) {
  return grpc_core::Timestamp::FromTimespecRoundUp(
      grpc_timeout_seconds_to_deadline(seconds));
}

static void actually_poll(void* argsp) {
  args_struct* args = static_cast<args_struct*>(argsp);
  grpc_core::Timestamp deadline = n_sec_deadline(10);
  while (true) {
    grpc_core::ExecCtx exec_ctx;
    {
      grpc_core::MutexLockForGprMu lock(args->mu);
      if (args->done) {
        break;
      }
      grpc_core::Duration time_left = deadline - grpc_core::Timestamp::Now();
      VLOG(2) << "done=" << args->done << ", time_left=" << time_left.millis();
      ASSERT_GE(time_left, grpc_core::Duration::Zero());
      grpc_pollset_worker* worker = nullptr;
      GRPC_LOG_IF_ERROR(
          "pollset_work",
          grpc_pollset_work(args->pollset, &worker, n_sec_deadline(1)));
    }
  }
  gpr_event_set(&args->ev, reinterpret_cast<void*>(1));
}

static void poll_pollset_until_request_done(args_struct* args) {
  args->thd = grpc_core::Thread("grpc_poll_pollset", actually_poll, args);
  args->thd.Start();
}

namespace {

void MustSucceed(args_struct* args,
                 absl::StatusOr<std::vector<grpc_resolved_address>> result) {
  ASSERT_TRUE(result.ok());
  ASSERT_FALSE(result->empty());
  grpc_core::MutexLockForGprMu lock(args->mu);
  args->done = true;
  GRPC_LOG_IF_ERROR("pollset_kick", grpc_pollset_kick(args->pollset, nullptr));
}

}

static void resolve_address_must_succeed(const char* target) {
  grpc_core::ExecCtx exec_ctx;
  args_struct args;
  args_init(&args);
  poll_pollset_until_request_done(&args);
  grpc_core::GetDNSResolver()->LookupHostname(
      [&args](absl::StatusOr<std::vector<grpc_resolved_address>> result) {
        MustSucceed(&args, std::move(result));
      },
      target, "1", grpc_core::kDefaultDNSRequestTimeout,
      args.pollset_set,
      "");
  grpc_core::ExecCtx::Get()->Flush();
  args_finish(&args);
}

static void test_named_and_numeric_scope_ids(void) {
  char* arbitrary_interface_name = static_cast<char*>(gpr_zalloc(IF_NAMESIZE));
  int interface_index = 0;

  for (size_t i = 1; i < 65536; i++) {
    if (if_indextoname(i, arbitrary_interface_name) != nullptr) {
      VLOG(2) << "Found interface at index " << i << " named "
              << arbitrary_interface_name << ". Will use this for the test";
      interface_index = static_cast<int>(i);
      break;
    }
  }
  ASSERT_GT(strlen(arbitrary_interface_name), 0);

  VLOG(2) << "test resolution with a named scope ID";
  std::string target_with_named_scope_id =
      absl::StrFormat("fe80::1234%%%s", arbitrary_interface_name);
  resolve_address_must_succeed(target_with_named_scope_id.c_str());
  gpr_free(arbitrary_interface_name);

  VLOG(2) << "test resolution with a numeric scope ID";
  std::string target_with_numeric_scope_id =
      absl::StrFormat("fe80::1234%%%d", interface_index);
  resolve_address_must_succeed(target_with_numeric_scope_id.c_str());
}

ABSL_FLAG(std::string, resolver, "", "Resolver type (ares or native)");

TEST(ResolveAddressUsingAresResolverPosixTest, MainTest) {
  if (grpc_core::IsEventEngineDnsNonClientChannelEnabled() ||
      grpc_event_engine::experimental::
          EventEngineExperimentDisabledForPython()) {
    GTEST_SKIP()
        << "The event_engine_dns_non_client_channel experiment is "
           "enabled, so the legacy resolver is not used in this binary.";
  }

  std::string resolver_type = absl::GetFlag(FLAGS_resolver);

  grpc_core::ConfigVars::Overrides overrides;
  if (resolver_type == "native") {
    overrides.dns_resolver = "native";
  } else if (resolver_type == "ares") {
    overrides.dns_resolver = "ares";
  } else {
    LOG(ERROR) << "--resolver was not set to ares or native";
    ASSERT_TRUE(false);
  }
  grpc_core::ConfigVars::SetOverrides(overrides);

  grpc_init();
  {
    grpc_core::ExecCtx exec_ctx;
    test_named_and_numeric_scope_ids();
  }
  grpc_shutdown();
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  absl::ParseCommandLine(argc, argv);
  return RUN_ALL_TESTS();
}
