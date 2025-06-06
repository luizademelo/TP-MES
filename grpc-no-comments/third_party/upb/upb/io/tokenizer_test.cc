
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/io/tokenizer.h"

#include <gtest/gtest.h>
#include "absl/strings/escaping.h"
#include "absl/strings/str_format.h"
#include "upb/io/chunked_input_stream.h"
#include "upb/io/string.h"
#include "upb/lex/unicode.h"
#include "upb/mem/arena.hpp"

#include "upb/port/def.inc"

namespace google {
namespace protobuf {
namespace io {
namespace {

#ifndef arraysize
#define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

static bool StringEquals(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

// TODO:  This is copied from coded_stream_unittest.  This is

#define TEST_1D(FIXTURE, NAME, CASES)                             \
  class FIXTURE##_##NAME##_DD : public FIXTURE {                  \
   protected:                                                     \
    template <typename CaseType>                                  \
    void DoSingleCase(const CaseType& CASES##_case);              \
  };                                                              \
                                                                  \
  TEST_F(FIXTURE##_##NAME##_DD, NAME) {                           \
    for (size_t i = 0; i < arraysize(CASES); i++) {               \
      SCOPED_TRACE(testing::Message()                             \
                   << #CASES " case #" << i << ": " << CASES[i]); \
      DoSingleCase(CASES[i]);                                     \
    }                                                             \
  }                                                               \
                                                                  \
  template <typename CaseType>                                    \
  void FIXTURE##_##NAME##_DD::DoSingleCase(const CaseType& CASES##_case)

#define TEST_2D(FIXTURE, NAME, CASES1, CASES2)                              \
  class FIXTURE##_##NAME##_DD : public FIXTURE {                            \
   protected:                                                               \
    template <typename CaseType1, typename CaseType2>                       \
    void DoSingleCase(const CaseType1& CASES1##_case,                       \
                      const CaseType2& CASES2##_case);                      \
  };                                                                        \
                                                                            \
  TEST_F(FIXTURE##_##NAME##_DD, NAME) {                                     \
    for (size_t i = 0; i < arraysize(CASES1); i++) {                        \
      for (size_t j = 0; j < arraysize(CASES2); j++) {                      \
        SCOPED_TRACE(testing::Message()                                     \
                     << #CASES1 " case #" << i << ": " << CASES1[i] << ", " \
                     << #CASES2 " case #" << j << ": " << CASES2[j]);       \
        DoSingleCase(CASES1[i], CASES2[j]);                                 \
      }                                                                     \
    }                                                                       \
  }                                                                         \
                                                                            \
  template <typename CaseType1, typename CaseType2>                         \
  void FIXTURE##_##NAME##_DD::DoSingleCase(const CaseType1& CASES1##_case,  \
                                           const CaseType2& CASES2##_case)

upb_ZeroCopyInputStream* TestInputStream(const void* data, size_t size,
                                         size_t block_size, upb_Arena* arena) {
  return upb_ChunkedInputStream_New(data, size, block_size, arena);
}

const int kBlockSizes[] = {1, 2, 3, 5, 7, 13, 32, 1024};

class TokenizerTest : public testing::Test {
 protected:

  uint64_t ParseInteger(const std::string& text) {
    uint64_t result;
    EXPECT_TRUE(upb_Parse_Integer(text.data(), UINT64_MAX, &result))
        << "'" << text << "'";
    return result;
  }
};

#if !defined(__GNUC__) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)

struct SimpleTokenCase {
  std::string input;
  upb_TokenType type;
};

inline std::ostream& operator<<(std::ostream& out,
                                const SimpleTokenCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

SimpleTokenCase kSimpleTokenCases[] = {

    {"hello", kUpb_TokenType_Identifier},

    {"123", kUpb_TokenType_Integer},
    {"0xab6", kUpb_TokenType_Integer},
    {"0XAB6", kUpb_TokenType_Integer},
    {"0X1234567", kUpb_TokenType_Integer},
    {"0x89abcdef", kUpb_TokenType_Integer},
    {"0x89ABCDEF", kUpb_TokenType_Integer},
    {"01234567", kUpb_TokenType_Integer},

    {"123.45", kUpb_TokenType_Float},
    {"1.", kUpb_TokenType_Float},
    {"1e3", kUpb_TokenType_Float},
    {"1E3", kUpb_TokenType_Float},
    {"1e-3", kUpb_TokenType_Float},
    {"1e+3", kUpb_TokenType_Float},
    {"1.e3", kUpb_TokenType_Float},
    {"1.2e3", kUpb_TokenType_Float},
    {".1", kUpb_TokenType_Float},
    {".1e3", kUpb_TokenType_Float},
    {".1e-3", kUpb_TokenType_Float},
    {".1e+3", kUpb_TokenType_Float},

    {"'hello'", kUpb_TokenType_String},
    {"\"foo\"", kUpb_TokenType_String},
    {"'a\"b'", kUpb_TokenType_String},
    {"\"a'b\"", kUpb_TokenType_String},
    {"'a\\'b'", kUpb_TokenType_String},
    {"\"a\\\"b\"", kUpb_TokenType_String},
    {"'\\xf'", kUpb_TokenType_String},
    {"'\\0'", kUpb_TokenType_String},

    {"+", kUpb_TokenType_Symbol},
    {".", kUpb_TokenType_Symbol},
};

TEST_2D(TokenizerTest, SimpleTokens, kSimpleTokenCases, kBlockSizes) {
  upb::Arena arena;

  auto input = TestInputStream(kSimpleTokenCases_case.input.data(),
                               kSimpleTokenCases_case.input.size(),
                               kBlockSizes_case, arena.ptr());
  auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());

  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Start);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), 0);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));

  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));

  EXPECT_EQ(upb_Tokenizer_Type(t), kSimpleTokenCases_case.type);

  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t),
                           kSimpleTokenCases_case.input.data()));

  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), kSimpleTokenCases_case.input.size());

  upb_Status status;
  upb_Status_Clear(&status);

  EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
  EXPECT_TRUE(upb_Status_IsOk(&status));

  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_End);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), kSimpleTokenCases_case.input.size());
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), kSimpleTokenCases_case.input.size());
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));
}

TEST_1D(TokenizerTest, FloatSuffix, kBlockSizes) {

  upb::Arena arena;
  const char* text = "1f 2.5f 6e3f 7F";
  auto input =
      TestInputStream(text, strlen(text), kBlockSizes_case, arena.ptr());
  const int options = kUpb_TokenizerOption_AllowFAfterFloat;
  auto t = upb_Tokenizer_New(nullptr, 0, input, options, arena.ptr());

  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Float);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), "1f"));

  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Float);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), "2.5f"));

  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Float);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), "6e3f"));

  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Float);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), "7F"));

  upb_Status status;
  upb_Status_Clear(&status);

  EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
  EXPECT_TRUE(upb_Status_IsOk(&status));
}

SimpleTokenCase kWhitespaceTokenCases[] = {
    {" ", kUpb_TokenType_Whitespace},
    {"    ", kUpb_TokenType_Whitespace},
    {"\t", kUpb_TokenType_Whitespace},
    {"\v", kUpb_TokenType_Whitespace},
    {"\t ", kUpb_TokenType_Whitespace},
    {"\v\t", kUpb_TokenType_Whitespace},
    {"   \t\r", kUpb_TokenType_Whitespace},

    {"\n", kUpb_TokenType_Newline},
};

TEST_2D(TokenizerTest, Whitespace, kWhitespaceTokenCases, kBlockSizes) {
  upb::Arena arena;
  {
    auto input = TestInputStream(kWhitespaceTokenCases_case.input.data(),
                                 kWhitespaceTokenCases_case.input.size(),
                                 kBlockSizes_case, arena.ptr());
    auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());

    EXPECT_FALSE(upb_Tokenizer_Next(t, nullptr));
  }
  {
    auto input = TestInputStream(kWhitespaceTokenCases_case.input.data(),
                                 kWhitespaceTokenCases_case.input.size(),
                                 kBlockSizes_case, arena.ptr());
    const int options = kUpb_TokenizerOption_ReportNewlines;
    auto t = upb_Tokenizer_New(nullptr, 0, input, options, arena.ptr());

    EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));

    EXPECT_EQ(upb_Tokenizer_Type(t), kWhitespaceTokenCases_case.type);
    EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t),
                             kWhitespaceTokenCases_case.input.data()));
    EXPECT_FALSE(upb_Tokenizer_Next(t, nullptr));
  }
}

#endif

struct TokenFields {
  upb_TokenType type;
  std::string text;
  size_t line;
  size_t column;
  size_t end_column;
};

struct MultiTokenCase {
  std::string input;
  std::vector<TokenFields> output;
};

inline std::ostream& operator<<(std::ostream& out,
                                const MultiTokenCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

MultiTokenCase kMultiTokenCases[] = {

    {"",
     {
         {kUpb_TokenType_End, "", 0, 0, 0},
     }},

    {"foo 1 1.2 + 'bar'",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Integer, "1", 0, 4, 5},
         {kUpb_TokenType_Float, "1.2", 0, 6, 9},
         {kUpb_TokenType_Symbol, "+", 0, 10, 11},
         {kUpb_TokenType_String, "'bar'", 0, 12, 17},
         {kUpb_TokenType_End, "", 0, 17, 17},
     }},

    {"!@+%",
     {
         {kUpb_TokenType_Symbol, "!", 0, 0, 1},
         {kUpb_TokenType_Symbol, "@", 0, 1, 2},
         {kUpb_TokenType_Symbol, "+", 0, 2, 3},
         {kUpb_TokenType_Symbol, "%", 0, 3, 4},
         {kUpb_TokenType_End, "", 0, 4, 4},
     }},

    {"foo bar\nrab oof",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 4, 7},
         {kUpb_TokenType_Identifier, "rab", 1, 0, 3},
         {kUpb_TokenType_Identifier, "oof", 1, 4, 7},
         {kUpb_TokenType_End, "", 1, 7, 7},
     }},

    {"foo\tbar  \tbaz",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 8, 11},
         {kUpb_TokenType_Identifier, "baz", 0, 16, 19},
         {kUpb_TokenType_End, "", 0, 19, 19},
     }},

    {"\"foo\tbar\" baz",
     {
         {kUpb_TokenType_String, "\"foo\tbar\"", 0, 0, 12},
         {kUpb_TokenType_Identifier, "baz", 0, 13, 16},
         {kUpb_TokenType_End, "", 0, 16, 16},
     }},

    {"foo // This is a comment\n"
     "bar // This is another comment",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 1, 0, 3},
         {kUpb_TokenType_End, "", 1, 30, 30},
     }},

    {"foo /* This is a block comment */ bar",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 34, 37},
         {kUpb_TokenType_End, "", 0, 37, 37},
     }},

    {"foo # bar\n"
     "baz",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Symbol, "#", 0, 4, 5},
         {kUpb_TokenType_Identifier, "bar", 0, 6, 9},
         {kUpb_TokenType_Identifier, "baz", 1, 0, 3},
         {kUpb_TokenType_End, "", 1, 3, 3},
     }},

    {"foo\n\t\r\v\fbar",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 1, 11, 14},
         {kUpb_TokenType_End, "", 1, 14, 14},
     }},
};

TEST_2D(TokenizerTest, MultipleTokens, kMultiTokenCases, kBlockSizes) {

  upb::Arena arena;
  auto input = TestInputStream(kMultiTokenCases_case.input.data(),
                               kMultiTokenCases_case.input.size(),
                               kBlockSizes_case, arena.ptr());
  auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());

  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Start);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), 0);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));

  TokenFields token_fields;
  upb_Status status;
  upb_Status_Clear(&status);
  int i = 0;
  do {
    token_fields = kMultiTokenCases_case.output[i++];

    SCOPED_TRACE(testing::Message()
                 << "Token #" << i << ": " << absl::CEscape(token_fields.text));

    if (token_fields.type == kUpb_TokenType_End) {
      EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
      EXPECT_TRUE(upb_Status_IsOk(&status));
    } else {
      EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
    }

    EXPECT_EQ(upb_Tokenizer_Type(t), token_fields.type);
    EXPECT_EQ(upb_Tokenizer_Line(t), token_fields.line);
    EXPECT_EQ(upb_Tokenizer_Column(t), token_fields.column);
    EXPECT_EQ(upb_Tokenizer_EndColumn(t), token_fields.end_column);
    EXPECT_EQ(upb_Tokenizer_TextSize(t), token_fields.text.size());
    EXPECT_TRUE(
        StringEquals(upb_Tokenizer_TextData(t), token_fields.text.data()));
  } while (token_fields.type != kUpb_TokenType_End);
}

MultiTokenCase kMultiWhitespaceTokenCases[] = {

    {"foo 1 \t1.2  \n   +\v'bar'",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Whitespace, " ", 0, 3, 4},
         {kUpb_TokenType_Integer, "1", 0, 4, 5},
         {kUpb_TokenType_Whitespace, " \t", 0, 5, 8},
         {kUpb_TokenType_Float, "1.2", 0, 8, 11},
         {kUpb_TokenType_Whitespace, "  ", 0, 11, 13},
         {kUpb_TokenType_Newline, "\n", 0, 13, 0},
         {kUpb_TokenType_Whitespace, "   ", 1, 0, 3},
         {kUpb_TokenType_Symbol, "+", 1, 3, 4},
         {kUpb_TokenType_Whitespace, "\v", 1, 4, 5},
         {kUpb_TokenType_String, "'bar'", 1, 5, 10},
         {kUpb_TokenType_End, "", 1, 10, 10},
     }},

};

TEST_2D(TokenizerTest, MultipleWhitespaceTokens, kMultiWhitespaceTokenCases,
        kBlockSizes) {

  upb::Arena arena;
  auto input = TestInputStream(kMultiWhitespaceTokenCases_case.input.data(),
                               kMultiWhitespaceTokenCases_case.input.size(),
                               kBlockSizes_case, arena.ptr());
  const int options = kUpb_TokenizerOption_ReportNewlines;
  auto t = upb_Tokenizer_New(nullptr, 0, input, options, arena.ptr());

  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Start);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), 0);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));

  TokenFields token_fields;
  upb_Status status;
  upb_Status_Clear(&status);
  int i = 0;
  do {
    token_fields = kMultiWhitespaceTokenCases_case.output[i++];

    SCOPED_TRACE(testing::Message()
                 << "Token #" << i << ": " << token_fields.text);

    if (token_fields.type == kUpb_TokenType_End) {
      EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
      EXPECT_TRUE(upb_Status_IsOk(&status));
    } else {
      EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
    }

    EXPECT_EQ(upb_Tokenizer_Type(t), token_fields.type);
    EXPECT_EQ(upb_Tokenizer_Line(t), token_fields.line);
    EXPECT_EQ(upb_Tokenizer_Column(t), token_fields.column);
    EXPECT_EQ(upb_Tokenizer_EndColumn(t), token_fields.end_column);
    EXPECT_TRUE(
        StringEquals(upb_Tokenizer_TextData(t), token_fields.text.data()));
  } while (token_fields.type != kUpb_TokenType_End);
}

#if !defined(__GNUC__) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)

TEST_1D(TokenizerTest, ShCommentStyle, kBlockSizes) {

  const char* text =
      "foo # bar\n"
      "baz // qux\n"
      "corge /* grault */\n"
      "garply";
  const char* const kTokens[] = {"foo",
                                 "baz", "/",      "/", "qux", "corge", "/",
                                 "*",   "grault", "*", "/",   "garply"};

  upb::Arena arena;
  auto input =
      TestInputStream(text, strlen(text), kBlockSizes_case, arena.ptr());
  const int options = kUpb_TokenizerOption_CommentStyleShell;
  auto t = upb_Tokenizer_New(nullptr, 0, input, options, arena.ptr());

  for (size_t i = 0; i < arraysize(kTokens); i++) {
    EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));
    EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), kTokens[i]));
  }

  upb_Status status;
  upb_Status_Clear(&status);
  EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
  EXPECT_TRUE(upb_Status_IsOk(&status));
}

#endif

#if 0  // TODO: Extended comments are currently unimplemented.

struct DocCommentCase {
  std::string input;

  const char* prev_trailing_comments;
  const char* detached_comments[10];
  const char* next_leading_comments;
};

inline std::ostream& operator<<(std::ostream& out,
                                const DocCommentCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

DocCommentCase kDocCommentCases[] = {
    {"prev next",

     "",
     {},
     ""},

    {"prev /* ignored */ next",

     "",
     {},
     ""},

    {"prev // trailing comment\n"
     "next",

     " trailing comment\n",
     {},
     ""},

    {"prev\n"
     "// leading comment\n"
     "// line 2\n"
     "next",

     "",
     {},
     " leading comment\n"
     " line 2\n"},

    {"prev\n"
     "// trailing comment\n"
     "// line 2\n"
     "\n"
     "next",

     " trailing comment\n"
     " line 2\n",
     {},
     ""},

    {"prev // trailing comment\n"
     "// leading comment\n"
     "// line 2\n"
     "next",

     " trailing comment\n",
     {},
     " leading comment\n"
     " line 2\n"},

    {"prev /* trailing block comment */\n"
     "/* leading block comment\n"
     " * line 2\n"
     " * line 3 */"
     "next",

     " trailing block comment ",
     {},
     " leading block comment\n"
     " line 2\n"
     " line 3 "},

    {"prev\n"
     "/* trailing block comment\n"
     " * line 2\n"
     " * line 3\n"
     " */\n"
     "/* leading block comment\n"
     " * line 2\n"
     " * line 3 */"
     "next",

     " trailing block comment\n"
     " line 2\n"
     " line 3\n",
     {},
     " leading block comment\n"
     " line 2\n"
     " line 3 "},

    {"prev\n"
     "// trailing comment\n"
     "\n"
     "// detached comment\n"
     "// line 2\n"
     "\n"
     "// second detached comment\n"
     "/* third detached comment\n"
     " * line 2 */\n"
     "// leading comment\n"
     "next",

     " trailing comment\n",
     {" detached comment\n"
      " line 2\n",
      " second detached comment\n",
      " third detached comment\n"
      " line 2 "},
     " leading comment\n"},

    {"prev /**/\n"
     "\n"
     "// detached comment\n"
     "\n"
     "// leading comment\n"
     "next",

     "",
     {" detached comment\n"},
     " leading comment\n"},

    {"prev /**/\n"
     "// leading comment\n"
     "next",

     "",
     {},
     " leading comment\n"},
};

TEST_2D(TokenizerTest, DocComments, kDocCommentCases, kBlockSizes) {

  TestInputStream input(kDocCommentCases_case.input.data(),
                        kDocCommentCases_case.input.size(), kBlockSizes_case);
  TestErrorCollector error_collector;
  Tokenizer tokenizer(&input, &error_collector);

  TestInputStream input2(kDocCommentCases_case.input.data(),
                         kDocCommentCases_case.input.size(), kBlockSizes_case);
  Tokenizer tokenizer2(&input2, &error_collector);

  tokenizer.Next();
  tokenizer2.Next();

  EXPECT_EQ("prev", tokenizer.current().text);
  EXPECT_EQ("prev", tokenizer2.current().text);

  std::string prev_trailing_comments;
  std::vector<std::string> detached_comments;
  std::string next_leading_comments;
  tokenizer.NextWithComments(&prev_trailing_comments, &detached_comments,
                             &next_leading_comments);
  tokenizer2.NextWithComments(nullptr, nullptr, nullptr);
  EXPECT_EQ("next", tokenizer.current().text);
  EXPECT_EQ("next", tokenizer2.current().text);

  EXPECT_EQ(kDocCommentCases_case.prev_trailing_comments,
            prev_trailing_comments);

  for (int i = 0; i < detached_comments.size(); i++) {
    EXPECT_LT(i, arraysize(kDocCommentCases));
    EXPECT_TRUE(kDocCommentCases_case.detached_comments[i] != nullptr);
    EXPECT_EQ(kDocCommentCases_case.detached_comments[i], detached_comments[i]);
  }

  EXPECT_EQ(nullptr,
            kDocCommentCases_case.detached_comments[detached_comments.size()]);

  EXPECT_EQ(kDocCommentCases_case.next_leading_comments, next_leading_comments);
}

#endif

// TODO: Add a fuzz test for this.
TEST_F(TokenizerTest, ParseInteger) {
  EXPECT_EQ(0, ParseInteger("0"));
  EXPECT_EQ(123, ParseInteger("123"));
  EXPECT_EQ(0xabcdef12u, ParseInteger("0xabcdef12"));
  EXPECT_EQ(0xabcdef12u, ParseInteger("0xABCDEF12"));
  EXPECT_EQ(UINT64_MAX, ParseInteger("0xFFFFFFFFFFFFFFFF"));
  EXPECT_EQ(01234567, ParseInteger("01234567"));
  EXPECT_EQ(0X123, ParseInteger("0X123"));

  EXPECT_EQ(0, ParseInteger("0x"));

  uint64_t i;

  EXPECT_FALSE(upb_Parse_Integer("zxy", UINT64_MAX, &i));
  EXPECT_FALSE(upb_Parse_Integer("1.2", UINT64_MAX, &i));
  EXPECT_FALSE(upb_Parse_Integer("08", UINT64_MAX, &i));
  EXPECT_FALSE(upb_Parse_Integer("0xg", UINT64_MAX, &i));
  EXPECT_FALSE(upb_Parse_Integer("-1", UINT64_MAX, &i));

  EXPECT_TRUE(upb_Parse_Integer("0", 0, &i));
  EXPECT_FALSE(upb_Parse_Integer("1", 0, &i));
  EXPECT_TRUE(upb_Parse_Integer("1", 1, &i));
  EXPECT_TRUE(upb_Parse_Integer("12345", 12345, &i));
  EXPECT_FALSE(upb_Parse_Integer("12346", 12345, &i));
  EXPECT_TRUE(upb_Parse_Integer("0xFFFFFFFFFFFFFFFF", UINT64_MAX, &i));
  EXPECT_FALSE(upb_Parse_Integer("0x10000000000000000", UINT64_MAX, &i));

  for (int64_t offset = -1600; offset <= 1600; ++offset) {

    uint64_t i = 0x7FFFFFFFFFFFFFFFu + static_cast<uint64_t>(offset);
    char decimal[32];
    snprintf(decimal, 32, "%llu", static_cast<unsigned long long>(i));
    if (offset > 0) {
      uint64_t parsed = -1;
      EXPECT_FALSE(upb_Parse_Integer(decimal, INT64_MAX, &parsed))
          << decimal << "=>" << parsed;
    } else {
      uint64_t parsed = -1;
      EXPECT_TRUE(upb_Parse_Integer(decimal, INT64_MAX, &parsed))
          << decimal << "=>" << parsed;
      EXPECT_EQ(parsed, i);
    }
    char octal[32];
    snprintf(octal, 32, "0%llo", static_cast<unsigned long long>(i));
    if (offset > 0) {
      uint64_t parsed = -1;
      EXPECT_FALSE(upb_Parse_Integer(octal, INT64_MAX, &parsed))
          << octal << "=>" << parsed;
    } else {
      uint64_t parsed = -1;
      EXPECT_TRUE(upb_Parse_Integer(octal, INT64_MAX, &parsed))
          << octal << "=>" << parsed;
      EXPECT_EQ(parsed, i);
    }
    char hex[32];
    snprintf(hex, 32, "0x%llx", static_cast<unsigned long long>(i));
    if (offset > 0) {
      uint64_t parsed = -1;
      EXPECT_FALSE(upb_Parse_Integer(hex, INT64_MAX, &parsed))
          << hex << "=>" << parsed;
    } else {
      uint64_t parsed = -1;
      EXPECT_TRUE(upb_Parse_Integer(hex, INT64_MAX, &parsed)) << hex;
      EXPECT_EQ(parsed, i);
    }

  }

  for (int64_t offset = -1600; offset <= 1600; ++offset) {
    {
      uint64_t i = 18446744073709551615u + offset;
      char decimal[32];
      snprintf(decimal, 32, "1844674407370955%04llu",
               static_cast<unsigned long long>(1615 + offset));
      if (offset > 0) {
        uint64_t parsed = -1;
        EXPECT_FALSE(upb_Parse_Integer(decimal, UINT64_MAX, &parsed))
            << decimal << "=>" << parsed;
      } else {
        uint64_t parsed = -1;
        EXPECT_TRUE(upb_Parse_Integer(decimal, UINT64_MAX, &parsed)) << decimal;
        EXPECT_EQ(parsed, i);
      }
    }
    {
      uint64_t i = 01777777777777777777777u + offset;
      if (offset > 0) {
        char octal[32];
        snprintf(octal, 32, "0200000000000000000%04llo",
                 static_cast<unsigned long long>(offset - 1));
        uint64_t parsed = -1;
        EXPECT_FALSE(upb_Parse_Integer(octal, UINT64_MAX, &parsed))
            << octal << "=>" << parsed;
      } else {
        char octal[32];
        snprintf(octal, 32, "0%llo", static_cast<unsigned long long>(i));
        uint64_t parsed = -1;
        EXPECT_TRUE(upb_Parse_Integer(octal, UINT64_MAX, &parsed)) << octal;
        EXPECT_EQ(parsed, i);
      }
    }
    {
      uint64_t ui = 0xffffffffffffffffu + offset;
      char hex[32];
      if (offset > 0) {
        snprintf(hex, 32, "0x1000000000000%04llx",
                 static_cast<unsigned long long>(offset - 1));
        uint64_t parsed = -1;
        EXPECT_FALSE(upb_Parse_Integer(hex, UINT64_MAX, &parsed))
            << hex << "=>" << parsed;
      } else {
        snprintf(hex, 32, "0x%llx", static_cast<unsigned long long>(ui));
        uint64_t parsed = -1;
        EXPECT_TRUE(upb_Parse_Integer(hex, UINT64_MAX, &parsed)) << hex;
        EXPECT_EQ(parsed, ui);
      }
    }
  }
}

TEST_F(TokenizerTest, ParseFloat) {
  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1."));
  EXPECT_DOUBLE_EQ(1e3, upb_Parse_Float("1e3"));
  EXPECT_DOUBLE_EQ(1e3, upb_Parse_Float("1E3"));
  EXPECT_DOUBLE_EQ(1.5e3, upb_Parse_Float("1.5e3"));
  EXPECT_DOUBLE_EQ(.1, upb_Parse_Float(".1"));
  EXPECT_DOUBLE_EQ(.25, upb_Parse_Float(".25"));
  EXPECT_DOUBLE_EQ(.1e3, upb_Parse_Float(".1e3"));
  EXPECT_DOUBLE_EQ(.25e3, upb_Parse_Float(".25e3"));
  EXPECT_DOUBLE_EQ(.1e+3, upb_Parse_Float(".1e+3"));
  EXPECT_DOUBLE_EQ(.1e-3, upb_Parse_Float(".1e-3"));
  EXPECT_DOUBLE_EQ(5, upb_Parse_Float("5"));
  EXPECT_DOUBLE_EQ(6e-12, upb_Parse_Float("6e-12"));
  EXPECT_DOUBLE_EQ(1.2, upb_Parse_Float("1.2"));
  EXPECT_DOUBLE_EQ(1.e2, upb_Parse_Float("1.e2"));

  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1e"));
  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1e-"));
  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1.e"));

  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1f"));
  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1.0f"));
  EXPECT_DOUBLE_EQ(1, upb_Parse_Float("1F"));

  EXPECT_EQ(0.0, upb_Parse_Float("1e-9999999999999999999999999999"));
  EXPECT_EQ(HUGE_VAL, upb_Parse_Float("1e+9999999999999999999999999999"));

#if GTEST_HAS_DEATH_TEST

  EXPECT_DEBUG_DEATH(
      upb_Parse_Float("zxy"),
      "passed text that could not have been tokenized as a float");
  EXPECT_DEBUG_DEATH(
      upb_Parse_Float("1-e0"),
      "passed text that could not have been tokenized as a float");
  EXPECT_DEBUG_DEATH(
      upb_Parse_Float("-1.0"),
      "passed text that could not have been tokenized as a float");
#endif
}

TEST_F(TokenizerTest, ParseString) {
  const std::string inputs[] = {
      "'hello'",
      "\"blah\\nblah2\"",
      "'\\1x\\1\\123\\739\\52\\334n\\3'",
      "'\\x20\\x4'",

      "\"\\a\\l\\v\\t",
      "'",
      "'\\",

      // Experiment with Unicode escapes.
      // Here are one-, two- and three-byte Unicode characters.
      "'\\u0024\\u00a2\\u20ac\\U00024b62XX'",
      "'\\u0024\\u00a2\\u20ac\\ud852\\udf62XX'",  // Same, encoded using UTF16.

      // Here's some broken UTF16: a head surrogate with no tail surrogate.
      // We just output this as if it were UTF8; it's not a defined code point,
      // but it has a defined encoding.
      "'\\ud852XX'",

      // Malformed escape: Demons may fly out of the nose.
      "'\\u0'",

      // Beyond the range of valid UTF-32 code units.
      "'\\U00110000\\U00200000\\UFFFFFFFF'",
  };

  const std::string outputs[] = {
      "hello",
      "blah\nblah2",
      "\1x\1\123\739\52\334n\3",
      "\x20\x4",

      "\a?\v\t",
      "",
      "\\",

      "$¢€𤭢XX",
      "$¢€𤭢XX",

      "\xed\xa1\x92XX",

      "u0",

      "\\U00110000\\U00200000\\Uffffffff",
  };

  upb::Arena arena;

  for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
    auto sv = upb_Parse_String(inputs[i].data(), arena.ptr());
    EXPECT_TRUE(StringEquals(sv.data, outputs[i].data()));
  }

  // Test invalid strings that will never be tokenized as strings.
#if GTEST_HAS_DEATH_TEST  // death tests do not work on Windows yet
  EXPECT_DEBUG_DEATH(
      upb_Parse_String("", arena.ptr()),
      "passed text that could not have been tokenized as a string");
#endif  // GTEST_HAS_DEATH_TEST
}

TEST_F(TokenizerTest, ParseStringAppend) {
  upb::Arena arena;
  upb_String output;
  upb_String_Init(&output, arena.ptr());

  upb_String_Assign(&output, "stuff+", 6);
  auto sv = upb_Parse_String("'hello'", arena.ptr());
  EXPECT_TRUE(StringEquals(sv.data, "hello"));
  upb_String_Append(&output, sv.data, sv.size);
  EXPECT_TRUE(StringEquals(upb_String_Data(&output), "stuff+hello"));
}

// -------------------------------------------------------------------

// Each case parses some input text, ignoring the tokens produced, and
// checks that the error output matches what is expected.
struct ErrorCase {
  std::string input;
  const char* errors;
};

inline std::ostream& operator<<(std::ostream& out, const ErrorCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

ErrorCase kErrorCases[] = {
    // String errors.
    {"'\\l'", "0:2: Invalid escape sequence in string literal."},
    {"'\\X'", "0:2: Invalid escape sequence in string literal."},
    {"'\\x'", "0:3: Expected hex digits for escape sequence."},
    {"'foo", "0:4: Unexpected end of string."},
    {"'bar\nfoo", "0:4: String literals cannot cross line boundaries."},
    {"'\\u01'", "0:5: Expected four hex digits for \\u escape sequence."},
    {"'\\uXYZ'", "0:3: Expected four hex digits for \\u escape sequence."},

    // Integer errors.
    {"123foo", "0:3: Need space between number and identifier."},

    // Hex/octal errors.
    {"0x foo", "0:2: \"0x\" must be followed by hex digits."},
    {"0541823", "0:4: Numbers starting with leading zero must be in octal."},
    {"0x123z", "0:5: Need space between number and identifier."},
    {"0x123.4", "0:5: Hex and octal numbers must be integers."},
    {"0123.4", "0:4: Hex and octal numbers must be integers."},

    {"1e foo", "0:2: \"e\" must be followed by exponent."},
    {"1e- foo", "0:3: \"e\" must be followed by exponent."},
    {"1.2.3",
     "0:3: Already saw decimal point or exponent; can't have another one."},
    {"1e2.3",
     "0:3: Already saw decimal point or exponent; can't have another one."},
    {"a.1", "0:1: Need space between identifier and decimal point."},

    {"1.0f", "0:3: Need space between number and identifier."},

    {"/*",
     "0:2: End-of-file inside block comment.\n0:0: Comment started here."},
    {"/*/*/ foo",
     "0:3: \"/*\" inside block comment.  Block comments cannot be nested."},

    {"\b foo", "0:0: Invalid control characters encountered in text."},
    {"\b\b foo", "0:0: Invalid control characters encountered in text."},

    {"\b", "0:0: Invalid control characters encountered in text."},

    {std::string("\0foo", 4),
     "0:0: Invalid control characters encountered in text."},
    {std::string("\0\0foo", 5),
     "0:0: Invalid control characters encountered in text."},

    {"\300", "0:0: Interpreting non ascii codepoint 192."},
};

TEST_2D(TokenizerTest, Errors, kErrorCases, kBlockSizes) {

  upb::Arena arena;
  auto input = TestInputStream(kErrorCases_case.input.data(),
                               kErrorCases_case.input.size(), kBlockSizes_case,
                               arena.ptr());
  auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());

  upb_Status status;
  upb_Status_Clear(&status);

  while (upb_Tokenizer_Next(t, &status))
    ;
  EXPECT_TRUE(
      StringEquals(upb_Status_ErrorMessage(&status), kErrorCases_case.errors));
}

TEST_1D(TokenizerTest, BackUpOnDestruction, kBlockSizes) {
  const std::string text = "foo bar";
  upb::Arena arena;
  auto input =
      TestInputStream(text.data(), text.size(), kBlockSizes_case, arena.ptr());

  auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());
  upb_Tokenizer_Next(t, nullptr);
  upb_Tokenizer_Fini(t);

  EXPECT_EQ(strlen("foo"), upb_ZeroCopyInputStream_ByteCount(input));
}

static const char* kParseBenchmark[] = {
    "\"partner-google-mobile-modes-print\"",
    "\"partner-google-mobile-modes-products\"",
    "\"partner-google-mobile-modes-realtime\"",
    "\"partner-google-mobile-modes-video\"",
    "\"partner-google-modes-news\"",
    "\"partner-google-modes-places\"",
    "\"partner-google-news\"",
    "\"partner-google-print\"",
    "\"partner-google-products\"",
    "\"partner-google-realtime\"",
    "\"partner-google-video\"",
    "\"true\"",
    "\"BigImagesHover__js_list\"",
    "\"XFEExternJsVersionParameters\"",
    "\"Available versions of the big images hover javascript\"",
    "\"Version: {\n\"",
    "\"  script_name: \"extern_js/dummy_file_compiled_post20070813.js\"\n\"",
    "\"  version_number: 0\n\"",
    "\"}\"",
    "\"BigImagesHover__js_selection\"",
    "\"XFEExternJsVersionParameters\"",
    "\"Versioning info for the big images hover javascript.\"",
    "\"current_version: 0\"",
    "\"BigImagesHover__js_suppressed\"",
    "\"Indicates if the client-side javascript associated with big images.\"",
    "\"true\"",
    "\"BrowserAnyOf\"",
    "\"IsChrome5OrAbove\"",
    "\"IsFirefox3OrAbove\"",
    "IsIE8OrAboveBinary",
    "\"Abe \"Sausage King\" Froman\"",
    "\"Frank \"Meatball\" Febbraro\"",
};

TEST(Benchmark, ParseStringAppendAccumulate) {
  upb::Arena arena;
  size_t outsize = 0;
  int benchmark_len = arraysize(kParseBenchmark);
  for (int i = 0; i < benchmark_len; i++) {
    auto sv = upb_Parse_String(kParseBenchmark[i], arena.ptr());
    outsize += sv.size;
  }
  EXPECT_NE(0, outsize);
}

TEST(Benchmark, ParseStringAppend) {
  upb::Arena arena;
  upb_String output;
  upb_String_Init(&output, arena.ptr());
  int benchmark_len = arraysize(kParseBenchmark);
  for (int i = 0; i < benchmark_len; i++) {
    auto sv = upb_Parse_String(kParseBenchmark[i], arena.ptr());
    upb_String_Append(&output, sv.data, sv.size);
  }
  EXPECT_NE(0, upb_String_Size(&output));
}

static std::string StandardUTF8(uint32_t code_point) {
  char buffer[4];
  int count = upb_Unicode_ToUTF8(code_point, &buffer[0]);

  EXPECT_NE(count, 0) << "Failed to encode point " << std::hex << code_point;
  return std::string(reinterpret_cast<const char*>(buffer), count);
}

static std::string DisplayHex(const std::string& data) {
  std::string output;
  for (size_t i = 0; i < data.size(); ++i) {
    absl::StrAppendFormat(&output, "%02x ", data[i]);
  }
  return output;
}

static void ExpectFormat(const std::string& expectation,
                         const std::string& formatted) {
  upb::Arena arena;
  auto sv = upb_Parse_String(formatted.data(), arena.ptr());
  EXPECT_EQ(strcmp(sv.data, expectation.data()), 0)
      << ": Incorrectly parsed " << formatted << ":\nGot      "
      << DisplayHex(sv.data) << "\nExpected " << DisplayHex(expectation);
}

TEST(TokenizerHandlesUnicode, BMPCodes) {
  for (uint32_t code_point = 0; code_point < 0x10000; ++code_point) {

    if (upb_Unicode_IsHigh(code_point)) continue;
    if (upb_Unicode_IsLow(code_point)) continue;

    const std::string expectation = StandardUTF8(code_point);

    ExpectFormat(expectation, absl::StrFormat("'\\u%04x'", code_point));
    ExpectFormat(expectation, absl::StrFormat("'\\u%04X'", code_point));
    ExpectFormat(expectation, absl::StrFormat("'\\U%08x'", code_point));
    ExpectFormat(expectation, absl::StrFormat("'\\U%08X'", code_point));
  }
}

TEST(TokenizerHandlesUnicode, NonBMPCodes) {
  for (uint32_t code_point = 0x10000; code_point < 0x110000; ++code_point) {
    const std::string expectation = StandardUTF8(code_point);

    ExpectFormat(expectation, absl::StrFormat("'\\U%08x'", code_point));
    ExpectFormat(expectation, absl::StrFormat("'\\U%08X'", code_point));
    ExpectFormat(expectation, absl::StrFormat("'\\u%04x\\u%04x'",
                                              upb_Unicode_ToHigh(code_point),
                                              upb_Unicode_ToLow(code_point)));
  }
}

}
}
}
}
