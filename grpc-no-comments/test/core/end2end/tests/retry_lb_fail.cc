
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <atomic>
#include <memory>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"
#include "test/core/test_util/test_lb_policies.h"

namespace grpc_core {
namespace {
std::atomic<int> g_num_lb_picks;

CORE_END2END_TEST(RetryTests, RetryLbFail) {
  SKIP_IF_V3();
  CoreConfiguration::RegisterEphemeralBuilder(
      [](CoreConfiguration::Builder* builder) {
        RegisterFailLoadBalancingPolicy(
            builder, absl::UnavailableError("LB pick failed"), &g_num_lb_picks);
      });
  g_num_lb_picks.store(0, std::memory_order_relaxed);
  InitServer(ChannelArgs());
  InitClient(
      ChannelArgs()
          .Set(GRPC_ARG_ENABLE_RETRIES, true)
          .Set(GRPC_ARG_SERVICE_CONFIG,
               "{\n"
               "  \"loadBalancingConfig\": [ {\n"
               "    \"fail_lb\": {}\n"
               "  } ],\n"
               "  \"methodConfig\": [ {\n"
               "    \"name\": [\n"
               "      { \"service\": \"service\", \"method\": \"method\" }\n"
               "    ],\n"
               "    \"retryPolicy\": {\n"
               "      \"maxAttempts\": 2,\n"
               "      \"initialBackoff\": \"1s\",\n"
               "      \"maxBackoff\": \"120s\",\n"
               "      \"backoffMultiplier\": 1.6,\n"
               "      \"retryableStatusCodes\": [ \"UNAVAILABLE\" ]\n"
               "    }\n"
               "  } ]\n"
               "}"));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  c.NewBatch(1).SendInitialMetadata({});
  Expect(1, false);
  Step();
  IncomingStatusOnClient server_status;
  c.NewBatch(2).RecvStatusOnClient(server_status);
  Expect(2, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_UNAVAILABLE);
  EXPECT_EQ(server_status.message(), "LB pick failed");
  EXPECT_EQ(g_num_lb_picks.load(std::memory_order_relaxed), 2);
}

}
}
