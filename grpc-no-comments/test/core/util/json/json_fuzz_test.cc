
// Copyright 2015 gRPC authors.

#include <grpc/support/json.h>
#include <stdint.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "fuzztest/fuzztest.h"
#include "gtest/gtest.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"

namespace grpc_core {
namespace {

void ParseRoundTrips(std::string input) {
  auto json = JsonParse(input);
  if (json.ok()) {
    auto text2 = JsonDump(*json);
    auto json2 = JsonParse(text2);
    CHECK_OK(json2);
    EXPECT_EQ(*json, *json2)
        << GRPC_DUMP_ARGS(absl::CEscape(input), absl::CEscape(text2));
  }
}
FUZZ_TEST(JsonTest, ParseRoundTrips);

}
}
