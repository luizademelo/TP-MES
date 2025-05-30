#include "utf8_validity.h"

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"

namespace utf8_range {

TEST(Utf8Validity, SpanStructurallyValid) {

  EXPECT_EQ(4, SpanStructurallyValid("abcd"));
  EXPECT_EQ(4, SpanStructurallyValid(absl::string_view("a\0cd", 4)));
  EXPECT_EQ(4, SpanStructurallyValid("ab\xc2\x81"));
  EXPECT_EQ(4, SpanStructurallyValid("a\xe2\x81\x81"));
  EXPECT_EQ(4, SpanStructurallyValid("\xf2\x81\x81\x81"));

  EXPECT_EQ(3, SpanStructurallyValid("abc\x80"));
  EXPECT_EQ(3, SpanStructurallyValid("abc\xc2"));
  EXPECT_EQ(2, SpanStructurallyValid("ab\xe2\x81"));
  EXPECT_EQ(1, SpanStructurallyValid("a\xf2\x81\x81"));
  EXPECT_EQ(2, SpanStructurallyValid("ab\xc0\x81"));
  EXPECT_EQ(1, SpanStructurallyValid("a\xe0\x81\x81"));
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x81\x81\x81"));
  EXPECT_EQ(0, SpanStructurallyValid("\xf4\xbf\xbf\xbf"));

  EXPECT_EQ(0, SpanStructurallyValid("\xED\xA0\x80"));
  EXPECT_EQ(0, SpanStructurallyValid("\xED\xBF\xBF"));

  EXPECT_EQ(0, SpanStructurallyValid("\xc0\x80"));
  EXPECT_EQ(0, SpanStructurallyValid("\xc1\xbf"));
  EXPECT_EQ(0, SpanStructurallyValid("\xe0\x80\x80"));
  EXPECT_EQ(0, SpanStructurallyValid("\xe0\x9f\xbf"));
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x80\x80\x80"));
  EXPECT_EQ(0, SpanStructurallyValid("\xf0\x83\xbf\xbf"));

  EXPECT_EQ(0, SpanStructurallyValid("\xc7\xc8\xcd\xcb"));
}

TEST(Utf8Validity, IsStructurallyValid) {

  EXPECT_TRUE(IsStructurallyValid("abcd"));
  EXPECT_TRUE(IsStructurallyValid(absl::string_view("a\0cd", 4)));
  EXPECT_TRUE(IsStructurallyValid("ab\xc2\x81"));
  EXPECT_TRUE(IsStructurallyValid("a\xe2\x81\x81"));
  EXPECT_TRUE(IsStructurallyValid("\xf2\x81\x81\x81"));

  EXPECT_FALSE(IsStructurallyValid("abc\x80"));
  EXPECT_FALSE(IsStructurallyValid("abc\xc2"));
  EXPECT_FALSE(IsStructurallyValid("ab\xe2\x81"));
  EXPECT_FALSE(IsStructurallyValid("a\xf2\x81\x81"));
  EXPECT_FALSE(IsStructurallyValid("ab\xc0\x81"));
  EXPECT_FALSE(IsStructurallyValid("a\xe0\x81\x81"));
  EXPECT_FALSE(IsStructurallyValid("\xf0\x81\x81\x81"));
  EXPECT_FALSE(IsStructurallyValid("\xf4\xbf\xbf\xbf"));

  EXPECT_FALSE(IsStructurallyValid("\xED\xA0\x80"));
  EXPECT_FALSE(IsStructurallyValid("\xED\xBF\xBF"));

  EXPECT_FALSE(IsStructurallyValid("\xc0\x80"));
  EXPECT_FALSE(IsStructurallyValid("\xc1\xbf"));
  EXPECT_FALSE(IsStructurallyValid("\xe0\x80\x80"));
  EXPECT_FALSE(IsStructurallyValid("\xe0\x9f\xbf"));
  EXPECT_FALSE(IsStructurallyValid("\xf0\x80\x80\x80"));
  EXPECT_FALSE(IsStructurallyValid("\xf0\x83\xbf\xbf"));

  EXPECT_FALSE(IsStructurallyValid("\xc7\xc8\xcd\xcb"));
}

}
