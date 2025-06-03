Here's the commented version of the code:

```c++
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
// Macro to calculate the number of elements in a static array
#define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

// Helper function to compare two C strings
static bool StringEquals(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

// TODO: This is copied from coded_stream_unittest. This is

// Macro to define a 1-dimensional test case
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

// Macro to define a 2-dimensional test case
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

// Creates a test input stream with given data and block size
upb_ZeroCopyInputStream* TestInputStream(const void* data, size_t size,
                                         size_t block_size, upb_Arena* arena) {
  return upb_ChunkedInputStream_New(data, size, block_size, arena);
}

// Array of block sizes to test with
const int kBlockSizes[] = {1, 2, 3, 5, 7, 13, 32, 1024};

// Base test fixture for tokenizer tests
class TokenizerTest : public testing::Test {
 protected:
  // Helper method to parse an integer string
  uint64_t ParseInteger(const std::string& text) {
    uint64_t result;
    EXPECT_TRUE(upb_Parse_Integer(text.data(), UINT64_MAX, &result))
        << "'" << text << "'";
    return result;
  }
};

#if !defined(__GNUC__) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)

// Structure for simple token test cases
struct SimpleTokenCase {
  std::string input;
  upb_TokenType type;
};

// Overload << operator for SimpleTokenCase
inline std::ostream& operator<<(std::ostream& out,
                                const SimpleTokenCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

// Test cases for simple tokens
SimpleTokenCase kSimpleTokenCases[] = {
    // Identifier cases
    {"hello", kUpb_TokenType_Identifier},

    // Integer cases
    {"123", kUpb_TokenType_Integer},
    {"0xab6", kUpb_TokenType_Integer},
    {"0XAB6", kUpb_TokenType_Integer},
    {"0X1234567", kUpb_TokenType_Integer},
    {"0x89abcdef", kUpb_TokenType_Integer},
    {"0x89ABCDEF", kUpb_TokenType_Integer},
    {"01234567", kUpb_TokenType_Integer},

    // Float cases
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

    // String cases
    {"'hello'", kUpb_TokenType_String},
    {"\"foo\"", kUpb_TokenType_String},
    {"'a\"b'", kUpb_TokenType_String},
    {"\"a'b\"", kUpb_TokenType_String},
    {"'a\\'b'", kUpb_TokenType_String},
    {"\"a\\\"b\"", kUpb_TokenType_String},
    {"'\\xf'", kUpb_TokenType_String},
    {"'\\0'", kUpb_TokenType_String},

    // Symbol cases
    {"+", kUpb_TokenType_Symbol},
    {".", kUpb_TokenType_Symbol},
};

// Test case for simple tokens with different block sizes
TEST_2D(TokenizerTest, SimpleTokens, kSimpleTokenCases, kBlockSizes) {
  upb::Arena arena;

  // Create input stream and tokenizer
  auto input = TestInputStream(kSimpleTokenCases_case.input.data(),
                               kSimpleTokenCases_case.input.size(),
                               kBlockSizes_case, arena.ptr());
  auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());

  // Verify initial state
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_Start);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), 0);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));

  // Get first token
  EXPECT_TRUE(upb_Tokenizer_Next(t, nullptr));

  // Verify token type and content
  EXPECT_EQ(upb_Tokenizer_Type(t), kSimpleTokenCases_case.type);
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t),
                           kSimpleTokenCases_case.input.data()));

  // Verify position information
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), 0);
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), kSimpleTokenCases_case.input.size());

  // Verify end of input
  upb_Status status;
  upb_Status_Clear(&status);
  EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
  EXPECT_TRUE(upb_Status_IsOk(&status));

  // Verify final state
  EXPECT_EQ(upb_Tokenizer_Type(t), kUpb_TokenType_End);
  EXPECT_EQ(upb_Tokenizer_Line(t), 0);
  EXPECT_EQ(upb_Tokenizer_Column(t), kSimpleTokenCases_case.input.size());
  EXPECT_EQ(upb_Tokenizer_EndColumn(t), kSimpleTokenCases_case.input.size());
  EXPECT_TRUE(StringEquals(upb_Tokenizer_TextData(t), ""));
}

// Test case for float suffix handling
TEST_1D(TokenizerTest, FloatSuffix, kBlockSizes) {
  upb::Arena arena;
  const char* text = "1f 2.5f 6e3f 7F";
  auto input =
      TestInputStream(text, strlen(text), kBlockSizes_case, arena.ptr());
  // Enable option to allow 'f' after float
  const int options = kUpb_TokenizerOption_AllowFAfterFloat;
  auto t = upb_Tokenizer_New(nullptr, 0, input, options, arena.ptr());

  // Verify all float tokens with 'f' suffix are parsed correctly
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

  // Verify end of input
  upb_Status status;
  upb_Status_Clear(&status);
  EXPECT_FALSE(upb_Tokenizer_Next(t, &status));
  EXPECT_TRUE(upb_Status_IsOk(&status));
}

// Test cases for whitespace tokens
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

// Test case for whitespace tokens with different block sizes
TEST_2D(TokenizerTest, Whitespace, kWhitespaceTokenCases, kBlockSizes) {
  upb::Arena arena;
  {
    // Test without ReportNewlines option (should skip whitespace)
    auto input = TestInputStream(kWhitespaceTokenCases_case.input.data(),
                                 kWhitespaceTokenCases_case.input.size(),
                                 kBlockSizes_case, arena.ptr());
    auto t = upb_Tokenizer_New(nullptr, 0, input, 0, arena.ptr());
    EXPECT_FALSE(upb_Tokenizer_Next(t, nullptr));
  }
  {
    // Test with ReportNewlines option (should report whitespace)
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

// Structure for token fields (type, text, position)
struct TokenFields {
  upb_TokenType type;
  std::string text;
  size_t line;
  size_t column;
  size_t end_column;
};

// Structure for multiple token test cases
struct MultiTokenCase {
  std::string input;
  std::vector<TokenFields> output;
};

// Overload << operator for MultiTokenCase
inline std::ostream& operator<<(std::ostream& out,
                                const MultiTokenCase& test_case) {
  return out << absl::CEscape(test_case.input);
}

// Test cases for multiple tokens
MultiTokenCase kMultiTokenCases[] = {
    // Empty input case
    {"",
     {
         {kUpb_TokenType_End, "", 0, 0, 0},
     }},

    // Mixed token types
    {"foo 1 1.2 + 'bar'",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Integer, "1", 0, 4, 5},
         {kUpb_TokenType_Float, "1.2", 0, 6, 9},
         {kUpb_TokenType_Symbol, "+", 0, 10, 11},
         {kUpb_TokenType_String, "'bar'", 0, 12, 17},
         {kUpb_TokenType_End, "", 0, 17, 17},
     }},

    // Multiple symbols
    {"!@+%",
     {
         {kUpb_TokenType_Symbol, "!", 0, 0, 1},
         {kUpb_TokenType_Symbol, "@", 0, 1, 2},
         {kUpb_TokenType_Symbol, "+", 0, 2, 3},
         {kUpb_TokenType_Symbol, "%", 0, 3, 4},
         {kUpb_TokenType_End, "", 0, 4, 4},
     }},

    // Newline handling
    {"foo bar\nrab oof",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 4, 7},
         {kUpb_TokenType_Identifier, "rab", 1, 0, 3},
         {kUpb_TokenType_Identifier, "oof", 1, 4, 7},
         {kUpb_TokenType_End, "", 1, 7, 7},
     }},

    // Tab handling
    {"foo\tbar  \tbaz",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 8, 11},
         {kUpb_TokenType_Identifier, "baz", 0, 16, 19},
         {kUpb_TokenType_End, "", 0, 19, 19},
     }},

    // String with tab
    {"\"foo\tbar\" baz",
     {
         {kUpb_TokenType_String, "\"foo\tbar\"", 0, 0, 12},
         {kUpb_TokenType_Identifier, "baz", 0, 13, 16},
         {kUpb_TokenType_End, "", 0, 16, 16},
     }},

    // Comment handling
    {"foo // This is a comment\n"
     "bar // This is another comment",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 1, 0, 3},
         {kUpb_TokenType_End, "", 1, 30, 30},
     }},

    // Block comment handling
    {"foo /* This is a block comment */ bar",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Identifier, "bar", 0, 34, 37},
         {kUpb_TokenType_End, "", 0, 37, 37},
     }},

    // Hash symbol handling
    {"foo # bar\n"
     "baz",
     {
         {kUpb_TokenType_Identifier, "foo", 0, 0, 3},
         {kUpb_TokenType_Symbol, "#", 0, 4, 5},
         {kUpb_TokenType_Identifier, "bar", 0, 6, 9},
         {kUpb_TokenType_Identifier, "baz", 1, 0, 3