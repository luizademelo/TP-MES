
// Copyright 2015 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <stdio.h>

#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

class LargeMetadataTest {
 public:
  LargeMetadataTest(CoreEnd2endTest& test, const ChannelArgs& args)
      : test_(test) {
    test_.InitClient(args);
    test_.InitServer(args);
  }

  int PerformRequests(size_t metadata_size, int count) {
    int num_requests_accepted = 0;
    for (int i = 0; i < count; ++i) {
      auto status = PerformOneRequest(metadata_size);
      if (status.status() == GRPC_STATUS_RESOURCE_EXHAUSTED) {
        EXPECT_THAT(status.message(),
                    ::testing::HasSubstr("received metadata size exceeds"));
      } else {
        num_requests_accepted++;
        EXPECT_EQ(status.status(), GRPC_STATUS_OK);
        EXPECT_EQ(status.message(), IsErrorFlattenEnabled() ? "" : "xyz");
      }
    }
    return num_requests_accepted;
  }

 private:
  IncomingStatusOnClient PerformOneRequest(const size_t metadata_size) {
    auto c = test_.NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
    IncomingMetadata server_initial_metadata;
    IncomingStatusOnClient server_status;
    c.NewBatch(1)
        .SendInitialMetadata({})
        .SendCloseFromClient()
        .RecvInitialMetadata(server_initial_metadata)
        .RecvStatusOnClient(server_status);
    auto s = test_.RequestCall(101);
    test_.Expect(101, true);
    test_.Step();

    IncomingCloseOnServer client_close;
    s.NewBatch(102)
        .SendInitialMetadata({{"key", std::string(metadata_size, 'a')}})
        .RecvCloseOnServer(client_close)
        .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});
    test_.Expect(102, true);
    test_.Expect(1, true);
    test_.Step();
    return server_status;
  }

  CoreEnd2endTest& test_;
};

CORE_END2END_TEST(Http2SingleHopTests, RequestWithLargeMetadataUnderSoftLimit) {
  const size_t soft_limit = 32 * 1024;
  const size_t hard_limit = 45 * 1024;
  const size_t metadata_size = soft_limit;
  LargeMetadataTest test(
      *this, ChannelArgs()
                 .Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024)
                 .Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE, hard_limit + 1024));
  EXPECT_EQ(test.PerformRequests(metadata_size, 100), 100);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataBetweenSoftAndHardLimits) {
  const size_t soft_limit = 32 * 1024;
  const size_t hard_limit = 45 * 1024;
  const size_t metadata_size = (soft_limit + hard_limit) / 2;
  LargeMetadataTest test(
      *this, ChannelArgs()
                 .Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024)
                 .Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE, hard_limit + 1024));
  EXPECT_THAT(test.PerformRequests(metadata_size, 100),
              ::testing::AllOf(::testing::Ge(5), ::testing::Le(95)));
}

CORE_END2END_TEST(Http2SingleHopTests, RequestWithLargeMetadataAboveHardLimit) {
  const size_t soft_limit = 32 * 1024;
  const size_t hard_limit = 45 * 1024;
  const size_t metadata_size = hard_limit * 3 / 2;
  LargeMetadataTest test(
      *this, ChannelArgs()
                 .Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024)
                 .Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE, hard_limit + 1024));
  EXPECT_EQ(test.PerformRequests(metadata_size, 100), 0);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataSoftLimitAboveHardLimit) {
  const size_t soft_limit = 64 * 1024;
  const size_t hard_limit = 32 * 1024;
  const size_t metadata_size_below_hard_limit = hard_limit;
  const size_t metadata_size_above_hard_limit = hard_limit * 2;
  LargeMetadataTest test(
      *this, ChannelArgs()
                 .Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024)
                 .Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE, hard_limit + 1024));

  EXPECT_EQ(test.PerformRequests(metadata_size_below_hard_limit, 50), 50);

  EXPECT_EQ(test.PerformRequests(metadata_size_above_hard_limit, 50), 0);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataSoftLimitOverridesDefaultHard) {
  const size_t soft_limit = 64 * 1024;
  const size_t metadata_size_below_soft_limit = soft_limit;
  const size_t metadata_size_above_hard_limit = soft_limit * 1.5;
  const size_t metadata_size_between_limits =
      (soft_limit + soft_limit * 1.25) / 2;
  LargeMetadataTest test(
      *this, ChannelArgs().Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024));

  EXPECT_EQ(test.PerformRequests(metadata_size_below_soft_limit, 50), 50);

  EXPECT_THAT(test.PerformRequests(metadata_size_between_limits, 100),
              ::testing::AllOf(::testing::Ge(5), ::testing::Le(95)));

  EXPECT_EQ(test.PerformRequests(metadata_size_above_hard_limit, 50), 0);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataHardLimitOverridesDefaultSoft) {
  const size_t hard_limit = 45 * 1024;
  const size_t metadata_size_below_soft_limit = hard_limit * 0.5;
  const size_t metadata_size_above_hard_limit = hard_limit * 1.5;
  const size_t metadata_size_between_limits =
      (hard_limit * 0.8 + hard_limit) / 2;
  LargeMetadataTest test(*this,
                         ChannelArgs().Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE,
                                           hard_limit + 1024));

  EXPECT_EQ(test.PerformRequests(metadata_size_below_soft_limit, 50), 50);

  EXPECT_THAT(test.PerformRequests(metadata_size_between_limits, 100),
              ::testing::AllOf(::testing::Ge(5), ::testing::Le(95)));

  EXPECT_EQ(test.PerformRequests(metadata_size_above_hard_limit, 50), 0);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataHardLimitBelowDefaultHard) {
  const size_t hard_limit = 4 * 1024;
  const size_t metadata_size_below_hard_limit = hard_limit;
  const size_t metadata_size_above_hard_limit = hard_limit * 2;
  LargeMetadataTest test(*this,
                         ChannelArgs().Set(GRPC_ARG_ABSOLUTE_MAX_METADATA_SIZE,
                                           hard_limit + 1024));

  EXPECT_EQ(test.PerformRequests(metadata_size_below_hard_limit, 50), 50);

  EXPECT_EQ(test.PerformRequests(metadata_size_above_hard_limit, 50), 0);
}

CORE_END2END_TEST(Http2SingleHopTests,
                  RequestWithLargeMetadataSoftLimitBelowDefaultSoft) {
  const size_t soft_limit = 1 * 1024;
  const size_t metadata_size_below_soft_limit = soft_limit;

  const size_t metadata_size_between_limits = 10 * 1024;
  const size_t metadata_size_above_hard_limit = 75 * 1024;
  LargeMetadataTest test(
      *this, ChannelArgs().Set(GRPC_ARG_MAX_METADATA_SIZE, soft_limit + 1024));

  EXPECT_EQ(test.PerformRequests(metadata_size_below_soft_limit, 50), 50);

  EXPECT_THAT(test.PerformRequests(metadata_size_between_limits, 100),
              ::testing::AllOf(::testing::Ge(1), ::testing::Le(99)));

  EXPECT_EQ(test.PerformRequests(metadata_size_above_hard_limit, 50), 0);
}

}
}
