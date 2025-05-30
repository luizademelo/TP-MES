
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <stdint.h>
#include <string.h>

#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/uri.h"

namespace grpc_core {
namespace {

void ParseRoundTrips(std::string buffer) {
  auto uri = URI::Parse(buffer);
  if (!uri.ok()) return;
  auto buffer2 = uri->ToString();
  auto uri2 = URI::Parse(buffer2);
  CHECK_OK(uri2);
  EXPECT_EQ(uri->ToString(), uri2->ToString())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->scheme(), uri2->scheme())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->authority(), uri2->authority())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->user_info(), uri2->user_info())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->host_port(), uri2->host_port())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->path(), uri2->path())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->query_parameter_pairs(), uri2->query_parameter_pairs())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri->fragment(), uri2->fragment())
      << GRPC_DUMP_ARGS(absl::CEscape(buffer), absl::CEscape(buffer2));
  EXPECT_EQ(uri, uri2);
}
FUZZ_TEST(UriTest, ParseRoundTrips);

TEST(UriTest, ParseRoundTripsRegression) { ParseRoundTrips("W:////\244"); }

}
}
