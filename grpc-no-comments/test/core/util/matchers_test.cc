// Copyright 2021 gRPC authors.

#include "src/core/util/matchers.h"

#include "absl/status/status.h"
#include "gtest/gtest.h"

namespace grpc_core {

TEST(StringMatcherTest, ExactMatchCaseSensitive) {
  auto string_matcher =
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "exact", true);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("exact"));
  EXPECT_FALSE(string_matcher->Match("Exact"));
  EXPECT_FALSE(string_matcher->Match("exacz"));
}

TEST(StringMatcherTest, ExactMatchCaseInsensitive) {
  auto string_matcher =
      StringMatcher::Create(StringMatcher::Type::kExact,
                            "exact", false);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("Exact"));
  EXPECT_FALSE(string_matcher->Match("Exacz"));
}

TEST(StringMatcherTest, PrefixMatchCaseSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kPrefix,
                                              "prefix",
                                              true);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("prefix-test"));
  EXPECT_FALSE(string_matcher->Match("xx-prefix-test"));
  EXPECT_FALSE(string_matcher->Match("Prefix-test"));
  EXPECT_FALSE(string_matcher->Match("pre-test"));
}

TEST(StringMatcherTest, PrefixMatchCaseInsensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kPrefix,
                                              "prefix",
                                              false);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("PREfix-test"));
  EXPECT_FALSE(string_matcher->Match("xx-PREfix-test"));
  EXPECT_FALSE(string_matcher->Match("PRE-test"));
}

TEST(StringMatcherTest, SuffixMatchCaseSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kSuffix,
                                              "suffix",
                                              true);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("test-suffix"));
  EXPECT_FALSE(string_matcher->Match("test-Suffix"));
  EXPECT_FALSE(string_matcher->Match("test-suffix-xx"));
  EXPECT_FALSE(string_matcher->Match("test-suffiz"));
}

TEST(StringMatcherTest, SuffixMatchCaseInSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kSuffix,
                                              "suffix",
                                              false);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("Test-SUFFIX"));
  EXPECT_FALSE(string_matcher->Match("Test-SUFFIX-xx"));
  EXPECT_FALSE(string_matcher->Match("Test-SUFFIZ"));
}

TEST(StringMatcherTest, InvalidRegex) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kSafeRegex,
                                              "a[b-a]",
                                              true);
  EXPECT_FALSE(string_matcher.ok());
  EXPECT_EQ(string_matcher.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(string_matcher.status().message(),
            "Invalid regex string specified in matcher: "
            "invalid character class range: b-a")
      << string_matcher.status();
}

TEST(StringMatcherTest, SafeRegexMatchCaseSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kSafeRegex,
                                              "regex.*");
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("regex-test"));
  EXPECT_FALSE(string_matcher->Match("xx-regex-test"));
  EXPECT_FALSE(string_matcher->Match("Regex-test"));
  EXPECT_FALSE(string_matcher->Match("test-regex"));
}

TEST(StringMatcherTest, PresenceMatchUsingSafeRegex) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kSafeRegex,
                                              ".+");
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("any-value"));
  EXPECT_FALSE(string_matcher->Match(""));
}

TEST(StringMatcherTest, ContainsMatchCaseSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kContains,
                                              "contains",
                                              true);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("test-contains"));
  EXPECT_TRUE(string_matcher->Match("test-contains-test"));
  EXPECT_FALSE(string_matcher->Match("test-Contains"));
  EXPECT_FALSE(string_matcher->Match("test-containz"));
}

TEST(StringMatcherTest, ContainsMatchCaseInSensitive) {
  auto string_matcher = StringMatcher::Create(StringMatcher::Type::kContains,
                                              "contains",
                                              false);
  ASSERT_TRUE(string_matcher.ok());
  EXPECT_TRUE(string_matcher->Match("Test-Contains"));
  EXPECT_TRUE(string_matcher->Match("Test-Contains-Test"));
  EXPECT_FALSE(string_matcher->Match("Test-Containz"));
}

TEST(HeaderMatcherTest, StringMatcher) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kExact,
                            "exact");
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_TRUE(header_matcher->Match("exact"));
  EXPECT_FALSE(header_matcher->Match("Exact"));
  EXPECT_FALSE(header_matcher->Match("exacz"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, StringMatcherCaseInsensitive) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kExact,
                            "exact", 0,
                            0, false,
                            false, false);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_TRUE(header_matcher->Match("exact"));
  EXPECT_TRUE(header_matcher->Match("Exact"));
  EXPECT_FALSE(header_matcher->Match("exacz"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, StringMatcherWithInvertMatch) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kExact,
                            "exact",
                            0, 0,
                            false, true);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_FALSE(header_matcher->Match("exact"));
  EXPECT_TRUE(header_matcher->Match("Exact"));
  EXPECT_TRUE(header_matcher->Match("exacz"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, InvalidRegex) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kSafeRegex,
                            "a[b-a]",
                            0, 0,
                            false, true);
  EXPECT_FALSE(header_matcher.ok());
  EXPECT_EQ(header_matcher.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(header_matcher.status().message(),
            "Invalid regex string specified in matcher: "
            "invalid character class range: b-a")
      << header_matcher.status();
}

TEST(HeaderMatcherTest, RangeMatcherValidRange) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kRange,
                            "", 10,
                             20);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_TRUE(header_matcher->Match("16"));
  EXPECT_TRUE(header_matcher->Match("10"));
  EXPECT_FALSE(header_matcher->Match("3"));
  EXPECT_FALSE(header_matcher->Match("20"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, RangeMatcherValidRangeWithInvertMatch) {
  auto header_matcher = HeaderMatcher::Create(
      "key", HeaderMatcher::Type::kRange,
      "", 10,
      20, false, true);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_FALSE(header_matcher->Match("16"));
  EXPECT_FALSE(header_matcher->Match("10"));
  EXPECT_TRUE(header_matcher->Match("3"));
  EXPECT_TRUE(header_matcher->Match("20"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, RangeMatcherInvalidRange) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kRange,
                            "", 20,
                            10);
  EXPECT_FALSE(header_matcher.ok());
  EXPECT_EQ(header_matcher.status().code(), absl::StatusCode::kInvalidArgument);
  EXPECT_EQ(
      header_matcher.status().message(),
      "Invalid range specifier specified: end cannot be smaller than start.");
}

TEST(HeaderMatcherTest, PresentMatcherTrue) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kPresent,
                            "", 0,
                            0, true);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_TRUE(header_matcher->Match("any_value"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, PresentMatcherTrueWithInvertMatch) {
  auto header_matcher = HeaderMatcher::Create(
      "key", HeaderMatcher::Type::kPresent,
      "", 0,
      0, true, true);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_FALSE(header_matcher->Match("any_value"));
  EXPECT_TRUE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, PresentMatcherFalse) {
  auto header_matcher =
      HeaderMatcher::Create("key", HeaderMatcher::Type::kPresent,
                            "", 0,
                            0, false);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_FALSE(header_matcher->Match("any_value"));
  EXPECT_TRUE(header_matcher->Match(std::nullopt));
}

TEST(HeaderMatcherTest, PresentMatcherFalseWithInvertMatch) {
  auto header_matcher = HeaderMatcher::Create(
      "key", HeaderMatcher::Type::kPresent,
      "", 0,
      0, false, true);
  ASSERT_TRUE(header_matcher.ok());
  EXPECT_TRUE(header_matcher->Match("any_value"));
  EXPECT_FALSE(header_matcher->Match(std::nullopt));
}

}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
