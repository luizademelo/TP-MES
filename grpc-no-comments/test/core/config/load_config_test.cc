// Copyright 2023 gRPC authors.

#include "src/core/config/load_config.h"

#include "absl/flags/flag.h"
#include "gtest/gtest.h"
#include "src/core/util/env.h"

ABSL_FLAG(std::vector<std::string>, comma_separated_strings, {}, "");

namespace grpc_core {

TEST(LoadConfigTest, LoadCommaSeparated) {
  SetEnv("grpc_comma_separated_strings", "foo");
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", {}, ""),
            "foo");
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", "bar", ""),
            "bar");
  absl::SetFlag(&FLAGS_comma_separated_strings, {"hello"});
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", {}, ""),
            "hello");
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", "bar", ""),
            "bar");
  absl::SetFlag(&FLAGS_comma_separated_strings, {"hello", "world"});
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", {}, ""),
            "hello,world");
  EXPECT_EQ(LoadConfig(FLAGS_comma_separated_strings,
                       "grpc_comma_separated_strings", "bar", ""),
            "bar");
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
