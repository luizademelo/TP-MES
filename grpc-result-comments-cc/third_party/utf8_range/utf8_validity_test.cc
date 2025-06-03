Here's the commented version of the code:

```c++
#include "utf8_validity.h"

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

namespace utf8_range {

// Test case for SpanStructurallyValid function which verifies the length of valid UTF-8 sequences
TEST(Utf8Validity, SpanStructurallyValid) {
  // Test valid UTF-8 sequences of different lengths (1-4 bytes)
  EXPECT_EQ(4, SpanStructurallyValid("abcd"));  // All ASCII characters (1 byte each)
  EXPECT_EQ(4, SpanStructurallyValid(absl::string_view("a\0cd", 4)));  // Contains null byte
  EXPECT_EQ(4, SpanStructurallyValid("ab\xc2\x81"));  // 2-byte UTF-8 sequence
  EXPECT_EQ(4, SpanStructurallyValid("a\xe2\x81\x81"));  // 3-byte UTF-8 sequence
  EXPECT_EQ(4, SpanStructurallyValid("\xf2\x81\x81\x81"));  // 4-byte UTF-8 sequence

  // Test invalid UTF-8 sequences where partial sequences should be rejected
  EXPECT_EQ(3, SpanStructurallyValid("abc\x80"));  // Invalid continuation byte
  EXPECT_EQ(3, SpanStructurallyValid("abc\xc2"));  // Incomplete 2-byte sequence
  EXPECT_EQ(2, SpanStructurallyValid("ab\xe2\x81"));  // Incomplete 3-byte sequence
  EXPECT_EQ(1, SpanStructurallyValid("a\xf2\x81\x81"));  // Incomplete 4-byte sequence
  EXPECT_EQ(2, SpanStructurallyValid("ab\xc0\x81"));  // Overlong encoding
  EXPECT_EQ(1, SpanStructurallyValid("a\xe0\x81\x81"));  // Overlong encoding
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x81\x81\x81"));  // Overlong encoding
  EXPECT_EQ(0, SpanStructurallyValid("\xf4\xbf\xbf\xbf"));  // Code point beyond U+10FFFF

  // Test invalid surrogate pairs (U+D800 to U+DFFF)
  EXPECT_EQ(0, SpanStructurallyValid("\xED\xA0\x80"));  // High surrogate
  EXPECT_EQ(0, SpanStructurallyValid("\xED\xBF\xBF"));  // Low surrogate

  // Test various invalid UTF-8 sequences (overlong encodings and invalid ranges)
  EXPECT_EQ(0, SpanStructurallyValid("\xc0\x80"));  // Overlong encoding of null
  EXPECT_EQ(0, SpanStructurallyValid("\xc1\xbf"));  // Overlong encoding
  EXPECT_EQ(0, SpanStructurallyValid("\xe0\x80\x80"));  // Overlong encoding
  EXPECT_EQ(0, SpanStructurallyValid("\xe0\x9f\xbf"));  // Invalid range
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x80\x80\x80"));  // Overlong encoding
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x83\xbf\xbf"));  // Invalid range

  // Test completely invalid byte sequence
  EXPECT_EQ(0, SpanStructurallyValid("\xc7\xc8\xcd\xcb"));
}

// Test case for IsStructurallyValid function which checks if entire input is valid UTF-8
TEST(Utf8Validity, IsStructurallyValid) {
  // Test valid UTF-8 sequences
  EXPECT_TRUE(IsStructurallyValid("abcd"));  // All ASCII characters
  EXPECT_TRUE(IsStructurallyValid(absl::string_view("a\0cd", 4)));  // Contains null byte
  EXPECT_TRUE(IsStructurallyValid("ab\xc2\x81"));  // Valid 2-byte sequence
  EXPECT_TRUE(IsStructurallyValid("a\xe2\x81\x81"));  // Valid 3-byte sequence
  EXPECT_TRUE(IsStructurallyValid("\xf2\x81\x81\x81"));  // Valid 4-byte sequence

  // Test invalid UTF-8 sequences
  EXPECT_FALSE(IsStructurallyValid("abc\x80"));  // Invalid continuation byte
  EXPECT_FALSE(IsStructurallyValid("abc\xc2"));  // Incomplete 2-byte sequence
  EXPECT_FALSE(IsStructurallyValid("ab\xe2\x81"));  // Incomplete 3-byte sequence
  EXPECT_FALSE(IsStructurallyValid("a\xf2\x81\x81"));  // Incomplete 4-byte sequence
  EXPECT_FALSE(IsStructurallyValid("ab\xc0\x81"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("a\xe0\x81\x81"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("\xf0\x81\x81\x81"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("\xf4\xbf\xbf\xbf"));  // Code point beyond U+10FFFF

  // Test invalid surrogate pairs
  EXPECT_FALSE(IsStructurallyValid("\xED\xA0\x80"));  // High surrogate
  EXPECT_FALSE(IsStructurallyValid("\xED\xBF\xBF"));  // Low surrogate

  // Test various invalid UTF-8 sequences
  EXPECT_FALSE(IsStructurallyValid("\xc0\x80"));  // Overlong encoding of null
  EXPECT_FALSE(IsStructurallyValid("\xc1\xbf"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("\xe0\x80\x80"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("\xe0\x9f\xbf"));  // Invalid range
  EXPECT_FALSE(IsStructurallyValid("\xf0\x80\x80\x80"));  // Overlong encoding
  EXPECT_FALSE(IsStructurallyValid("\xf0\x83\xbf\xbf"));  // Invalid range

  // Test completely invalid byte sequence
  EXPECT_FALSE(IsStructurallyValid("\xc7\xc8\xcd\xcb"));
}

}  // namespace utf8_range
```

The comments explain:
1. The purpose of each test case
2. What each test is verifying (valid vs invalid UTF-8 sequences)
3. Specific UTF-8 edge cases being tested (overlong encodings, surrogate pairs, invalid ranges)
4. The difference between SpanStructurallyValid (returns length of valid prefix) and IsStructurallyValid (checks entire string)
5. The byte patterns being tested and why they're significant for UTF-8 validation

The comments are placed to help future maintainers understand both the intent of the tests and the specific UTF-8 validation rules being verified.