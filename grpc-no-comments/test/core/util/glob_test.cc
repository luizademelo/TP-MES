// Copyright 2024 The gRPC Authors

#include "src/core/util/glob.h"

#include <grpc/grpc.h>

#include "absl/strings/match.h"
#include "gtest/gtest.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {

TEST(GlobTest, DefaultsToStringMatching) {
  EXPECT_TRUE(GlobMatch("arst", "arst"));
}

TEST(GlobTest, AsteriskMatchesMultipleCharacters) {
  EXPECT_TRUE(GlobMatch("a", "*"));
  EXPECT_TRUE(GlobMatch("arst", "*"));
}

TEST(GlobTest, QuestionMarkMatchesSingleCharacter) {
  EXPECT_TRUE(GlobMatch("a", "?"));
  EXPECT_FALSE(GlobMatch("arst", "?"));
}

TEST(GlobTest, AsteriskMatchesEmpty) { EXPECT_TRUE(GlobMatch("", "*")); }

TEST(GlobTest, QuestionMarkDoesNotMatcheEmpty) {
  EXPECT_FALSE(GlobMatch("", "?"));
}

TEST(GlobTest, EmbeddedAsterisk) {
  EXPECT_TRUE(GlobMatch("arst", "a*t"));
  EXPECT_TRUE(GlobMatch("arst", "*rst"));
  EXPECT_TRUE(GlobMatch("arst", "ar*"));
  EXPECT_TRUE(GlobMatch("arst", "*r*"));
  EXPECT_FALSE(GlobMatch("arst", "*q*"));
  EXPECT_FALSE(GlobMatch("*arst", "**q*"));
}

TEST(GlobTest, EmbeddedQuestionMark) {
  EXPECT_TRUE(GlobMatch("arst", "?rst"));
  EXPECT_TRUE(GlobMatch("arst", "a?st"));
  EXPECT_TRUE(GlobMatch("arst", "ar?t"));
  EXPECT_TRUE(GlobMatch("arst", "ars?"));
  EXPECT_TRUE(GlobMatch("arst", "??s?"));
  EXPECT_TRUE(GlobMatch("?arst", "???s?"));
  EXPECT_FALSE(GlobMatch("?arst", "arst"));
}

TEST(GlobTest, BothWildcardsWorkTogether) {
  EXPECT_TRUE(GlobMatch("arst", "?r*"));
  EXPECT_TRUE(GlobMatch("arst", "*s?"));
  EXPECT_TRUE(GlobMatch("arst", "a?*"));
  EXPECT_TRUE(GlobMatch("arst", "*?t"));
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc_init();
  auto res = RUN_ALL_TESTS();
  grpc_shutdown();
  return res;
}
