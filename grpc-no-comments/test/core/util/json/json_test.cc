
// Copyright 2015-2016 gRPC authors.

#include "src/core/util/json/json.h"

#include <string.h>

#include <map>
#include <string>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {

void ValidateValue(const Json& actual, const Json& expected);

void ValidateObject(const Json::Object& actual, const Json::Object& expected) {
  ASSERT_EQ(actual.size(), expected.size());
  auto actual_it = actual.begin();
  for (const auto& [key, value] : expected) {
    EXPECT_EQ(actual_it->first, key);
    ValidateValue(actual_it->second, value);
    ++actual_it;
  }
}

void ValidateArray(const Json::Array& actual, const Json::Array& expected) {
  ASSERT_EQ(actual.size(), expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    ValidateValue(actual[i], expected[i]);
  }
}

void ValidateValue(const Json& actual, const Json& expected) {
  ASSERT_EQ(actual.type(), expected.type());
  switch (expected.type()) {
    case Json::Type::kNull:
      break;
    case Json::Type::kBoolean:
      EXPECT_EQ(actual.boolean(), expected.boolean());
      break;
    case Json::Type::kString:
    case Json::Type::kNumber:
      EXPECT_EQ(actual.string(), expected.string());
      break;
    case Json::Type::kObject:
      ValidateObject(actual.object(), expected.object());
      break;
    case Json::Type::kArray:
      ValidateArray(actual.array(), expected.array());
      break;
  }
}

void RunSuccessTest(const char* input, const Json& expected,
                    const char* expected_output) {
  LOG(INFO) << "parsing string \"" << input << "\" - should succeed";
  auto json = JsonParse(input);
  ASSERT_TRUE(json.ok()) << json.status();
  ValidateValue(*json, expected);
  std::string output = JsonDump(*json);
  EXPECT_EQ(output, expected_output);
}

TEST(Json, Whitespace) {
  RunSuccessTest(" 0 ", Json::FromNumber(0), "0");
  RunSuccessTest(" 1 ", Json::FromNumber(1), "1");
  RunSuccessTest(" \"    \" ", Json::FromString("    "), "\"    \"");
  RunSuccessTest(" \"a\" ", Json::FromString("a"), "\"a\"");
  RunSuccessTest(" true ", Json::FromBool(true), "true");
}

TEST(Json, Utf16) {
  RunSuccessTest("\"\\u0020\\\\\\u0010\\u000a\\u000D\"",
                 Json::FromString(" \\\u0010\n\r"), "\" \\\\\\u0010\\n\\r\"");
}

MATCHER(ContainsInvalidUtf8,
        absl::StrCat(negation ? "Contains" : "Does not contain",
                     " invalid UTF-8 characters.")) {
  auto json = JsonParse(arg);
  return json.status().code() == absl::StatusCode::kInvalidArgument &&
         absl::StrContains(json.status().message(), "JSON parsing failed");
}

TEST(Json, Utf8) {
  RunSuccessTest("\"ßâñć௵⇒\"", Json::FromString("ßâñć௵⇒"),
                 "\"\\u00df\\u00e2\\u00f1\\u0107\\u0bf5\\u21d2\"");
  RunSuccessTest("\"\\u00df\\u00e2\\u00f1\\u0107\\u0bf5\\u21d2\"",
                 Json::FromString("ßâñć௵⇒"),
                 "\"\\u00df\\u00e2\\u00f1\\u0107\\u0bf5\\u21d2\"");

  RunSuccessTest("\"\xf0\x9d\x84\x9e\"", Json::FromString("\xf0\x9d\x84\x9e"),
                 "\"\\ud834\\udd1e\"");
  RunSuccessTest("\"\\ud834\\udd1e\"", Json::FromString("\xf0\x9d\x84\x9e"),
                 "\"\\ud834\\udd1e\"");
  RunSuccessTest("{\"\\ud834\\udd1e\":0}",
                 Json::FromObject({{"\xf0\x9d\x84\x9e", Json::FromNumber(0)}}),
                 "{\"\\ud834\\udd1e\":0}");

  EXPECT_THAT("\"\xa0\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xc0\xbc\"", ContainsInvalidUtf8());
  EXPECT_THAT("\"\xbc\xc0\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xe0\x80\x80\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xed\xa0\x80\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xf0\x80\x80\x80\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xf4\x90\x80\x80\"", ContainsInvalidUtf8());

  EXPECT_THAT("\"\xf5\x80\x80\x80\"", ContainsInvalidUtf8());
}

TEST(Json, NestedEmptyContainers) {
  RunSuccessTest(" [ [ ] , { } , [ ] ] ",
                 Json::FromArray({
                     Json::FromArray({}),
                     Json::FromObject({}),
                     Json::FromArray({}),
                 }),
                 "[[],{},[]]");
}

TEST(Json, EscapesAndControlCharactersInKeyStrings) {
  RunSuccessTest(" { \"\\u007f\x7f\\n\\r\\\"\\f\\b\\\\a , b\": 1, \"\": 0 } ",
                 Json::FromObject({
                     {"\u007f\u007f\n\r\"\f\b\\a , b", Json::FromNumber(1)},
                     {"", Json::FromNumber(0)},
                 }),
                 "{\"\":0,\"\\u007f\\u007f\\n\\r\\\"\\f\\b\\\\a , b\":1}");
}

TEST(Json, WriterCutsOffInvalidUtf8) {
  EXPECT_EQ(JsonDump(Json::FromString("abc\xf0\x9d\x24")), "\"abc\"");
  EXPECT_EQ(JsonDump(Json::FromString("\xff")), "\"\"");
}

TEST(Json, ValidNumbers) {
  RunSuccessTest("[0, 42 , 0.0123, 123.456]",
                 Json::FromArray({
                     Json::FromNumber(0),
                     Json::FromNumber(42),
                     Json::FromNumber("0.0123"),
                     Json::FromNumber("123.456"),
                 }),
                 "[0,42,0.0123,123.456]");
  RunSuccessTest("[1e4,-53.235e-31, 0.3e+3]",
                 Json::FromArray({
                     Json::FromNumber("1e4"),
                     Json::FromNumber("-53.235e-31"),
                     Json::FromNumber("0.3e+3"),
                 }),
                 "[1e4,-53.235e-31,0.3e+3]");
}

TEST(Json, Keywords) {
  RunSuccessTest("[true, false, null]",
                 Json::FromArray({
                     Json::FromBool(true),
                     Json::FromBool(false),
                     Json(),
                 }),
                 "[true,false,null]");
}

void RunParseFailureTest(const char* input) {
  LOG(INFO) << "parsing string \"" << input << "\" - should fail";
  auto json = JsonParse(input);
  EXPECT_FALSE(json.ok()) << "input: \"" << input << "\"";
}

TEST(Json, InvalidInput) {
  RunParseFailureTest("\\");
  RunParseFailureTest("nu ll");
  RunParseFailureTest("{\"foo\": bar}");
  RunParseFailureTest("{\"foo\": bar\"x\"}");
  RunParseFailureTest("fals");
  RunParseFailureTest("0,0 ");
  RunParseFailureTest("\"foo\",[]");
  RunParseFailureTest("{\"field\": {},}");
  RunParseFailureTest("[{},]");
  RunParseFailureTest("{\"field\": [],}");
  RunParseFailureTest("[[],]");
}

TEST(Json, UnterminatedString) { RunParseFailureTest("\"\\x"); }

TEST(Json, InvalidUtf16) {
  RunParseFailureTest("\"\\u123x");
  RunParseFailureTest("{\"\\u123x");
}

TEST(Json, ImbalancedSurrogatePairs) {
  RunParseFailureTest("\"\\ud834f");
  RunParseFailureTest("{\"\\ud834f\":0}");
  RunParseFailureTest("\"\\ud834\\n");
  RunParseFailureTest("{\"\\ud834\\n\":0}");
  RunParseFailureTest("\"\\udd1ef");
  RunParseFailureTest("{\"\\udd1ef\":0}");
  RunParseFailureTest("\"\\ud834\\ud834\"");
  RunParseFailureTest("{\"\\ud834\\ud834\"\":0}");
  RunParseFailureTest("\"\\ud834\\u1234\"");
  RunParseFailureTest("{\"\\ud834\\u1234\"\":0}");
  RunParseFailureTest("\"\\ud834]\"");
  RunParseFailureTest("{\"\\ud834]\"\":0}");
  RunParseFailureTest("\"\\ud834 \"");
  RunParseFailureTest("{\"\\ud834 \"\":0}");
  RunParseFailureTest("\"\\ud834\\\\\"");
  RunParseFailureTest("{\"\\ud834\\\\\"\":0}");
}

TEST(Json, EmbeddedInvalidWhitechars) {
  RunParseFailureTest("\"\n\"");
  RunParseFailureTest("\"\t\"");
}

TEST(Json, EmptyString) { RunParseFailureTest(""); }

TEST(Json, ExtraCharsAtEndOfParsing) {
  RunParseFailureTest("{},");
  RunParseFailureTest("{}x");
}

TEST(Json, ImbalancedContainers) {
  RunParseFailureTest("{}}");
  RunParseFailureTest("[]]");
  RunParseFailureTest("{{}");
  RunParseFailureTest("[[]");
  RunParseFailureTest("[}");
  RunParseFailureTest("{]");
}

TEST(Json, BadContainers) {
  RunParseFailureTest("{x}");
  RunParseFailureTest("{x=0,y}");
}

TEST(Json, DuplicateObjectKeys) { RunParseFailureTest("{\"x\": 1, \"x\": 1}"); }

TEST(Json, TrailingComma) {
  RunParseFailureTest("{,}");
  RunParseFailureTest("[1,2,3,4,]");
  RunParseFailureTest("{\"a\": 1, }");
}

TEST(Json, KeySyntaxInArray) { RunParseFailureTest("[\"x\":0]"); }

TEST(Json, InvalidNumbers) {
  RunParseFailureTest("1.");
  RunParseFailureTest("1e");
  RunParseFailureTest(".12");
  RunParseFailureTest("1.x");
  RunParseFailureTest("1.12x");
  RunParseFailureTest("1ex");
  RunParseFailureTest("1e12x");
  RunParseFailureTest(".12x");
  RunParseFailureTest("000");
};

TEST(Json, Equality) {

  EXPECT_EQ(Json(), Json());

  EXPECT_EQ(Json::FromNumber(1), Json::FromNumber(1));
  EXPECT_NE(Json::FromNumber(1), Json::FromNumber(2));
  EXPECT_EQ(Json::FromNumber(1), Json::FromNumber("1"));
  EXPECT_EQ(Json::FromNumber("-5e5"), Json::FromNumber("-5e5"));

  EXPECT_EQ(Json::FromBool(true), Json::FromBool(true));
  EXPECT_EQ(Json::FromBool(false), Json::FromBool(false));
  EXPECT_NE(Json::FromBool(true), Json::FromBool(false));

  EXPECT_EQ(Json::FromString("foo"), Json::FromString("foo"));
  EXPECT_NE(Json::FromString("foo"), Json::FromString("bar"));

  EXPECT_EQ(Json::FromArray({Json::FromString("foo")}),
            Json::FromArray({Json::FromString("foo")}));
  EXPECT_NE(Json::FromArray({Json::FromString("foo")}),
            Json::FromArray({Json::FromString("bar")}));

  EXPECT_EQ(Json::FromObject({{"foo", Json::FromNumber(1)}}),
            Json::FromObject({{"foo", Json::FromNumber(1)}}));
  EXPECT_NE(Json::FromObject({{"foo", Json::FromNumber(1)}}),
            Json::FromObject({{"foo", Json::FromNumber(2)}}));
  EXPECT_NE(Json::FromObject({{"foo", Json::FromNumber(1)}}),
            Json::FromObject({{"bar", Json::FromNumber(1)}}));

  EXPECT_NE(Json::FromNumber(1), Json::FromString("foo"));
  EXPECT_NE(Json::FromNumber(1), Json::FromBool(true));
  EXPECT_NE(Json::FromNumber(1), Json::FromArray({}));
  EXPECT_NE(Json::FromNumber(1), Json::FromObject({}));
  EXPECT_NE(Json::FromNumber(1), Json());
}

}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
