Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/lex/atoi.h"

#include <string.h>

#include <gtest/gtest.h>
#include "absl/strings/str_cat.h"

// Test case for converting string buffers to uint64_t values
TEST(AtoiTest, Uint64) {
  uint64_t val;

  // Test basic numeric conversion with trailing non-digit character
  const char* s = "1234z";
  EXPECT_EQ(s + 1, upb_BufToUint64(s, s + 1, &val));  // Convert first character
  EXPECT_EQ(val, 1);
  EXPECT_EQ(s + 4, upb_BufToUint64(s, s + 4, &val));  // Convert first 4 digits
  EXPECT_EQ(val, 1234);
  EXPECT_EQ(s + 4, upb_BufToUint64(s, s + 5, &val));  // Convert with extra character
  EXPECT_EQ(val, 1234);

  // Test numeric conversion with decimal point
  const char* t = "42.6";
  EXPECT_EQ(t + 1, upb_BufToUint64(t, t + 1, &val));  // Convert first digit
  EXPECT_EQ(val, 4);
  EXPECT_EQ(t + 2, upb_BufToUint64(t, t + 2, &val));  // Convert first 2 digits
  EXPECT_EQ(val, 42);
  EXPECT_EQ(t + 2, upb_BufToUint64(t, t + 3, &val));  // Stop at decimal point
  EXPECT_EQ(val, 42);

  // Test overflow case (number too large for uint64_t)
  const char* u = "1000000000000000000000000000000";
  EXPECT_EQ(nullptr, upb_BufToUint64(u, u + strlen(u), &val));

  // Test complete non-numeric input
  const char* v = "foobar";
  EXPECT_EQ(v, upb_BufToUint64(v, v + strlen(v), &val));

  // Test edge cases (max and min uint64_t values)
  const uint64_t values[] = {
      std::numeric_limits<uint64_t>::max(),
      std::numeric_limits<uint64_t>::min(),
  };
  for (size_t i = 0; i < ABSL_ARRAYSIZE(values); i++) {
    std::string v = absl::StrCat(values[i]);
    const char* ptr = v.c_str();
    const char* end = ptr + strlen(ptr);
    EXPECT_EQ(end, upb_BufToUint64(ptr, end, &val));  // Should convert entire string
    EXPECT_EQ(val, values[i]);
  }
}

// Test case for converting string buffers to int64_t values
TEST(AtoiTest, Int64) {
  int64_t val;
  bool neg;

  // Test basic numeric conversion with trailing non-digit character
  const char* s = "1234z";
  EXPECT_EQ(s + 1, upb_BufToInt64(s, s + 1, &val, &neg));  // Convert first digit
  EXPECT_EQ(val, 1);
  EXPECT_EQ(neg, false);
  EXPECT_EQ(s + 4, upb_BufToInt64(s, s + 4, &val, nullptr));  // Convert first 4 digits
  EXPECT_EQ(val, 1234);
  EXPECT_EQ(s + 4, upb_BufToInt64(s, s + 5, &val, nullptr));  // Convert with extra character
  EXPECT_EQ(val, 1234);

  // Test negative number conversion with decimal point
  const char* t = "-42.6";
  EXPECT_EQ(t + 2, upb_BufToInt64(t, t + 2, &val, &neg));  // Convert "-4"
  EXPECT_EQ(val, -4);
  EXPECT_EQ(neg, true);
  EXPECT_EQ(t + 3, upb_BufToInt64(t, t + 3, &val, nullptr));  // Convert "-42"
  EXPECT_EQ(val, -42);
  EXPECT_EQ(neg, true);
  EXPECT_EQ(t + 3, upb_BufToInt64(t, t + 5, &val, nullptr));  // Stop at decimal point
  EXPECT_EQ(val, -42);

  // Test edge cases (max/min int32_t and int64_t values)
  const int64_t values[] = {
      std::numeric_limits<int32_t>::max(),
      std::numeric_limits<int32_t>::min(),
      std::numeric_limits<int64_t>::max(),
      std::numeric_limits<int64_t>::min(),
  };
  for (size_t i = 0; i < ABSL_ARRAYSIZE(values); i++) {
    std::string v = absl::StrCat(values[i]);
    const char* ptr = v.c_str();
    const char* end = ptr + strlen(ptr);
    EXPECT_EQ(end, upb_BufToInt64(ptr, end, &val, nullptr));  // Should convert entire string
    EXPECT_EQ(val, values[i]);
  }
}
```

The comments explain:
1. The purpose of each test case
2. What each test is verifying
3. The expected behavior of the conversion functions
4. Edge cases being tested (max/min values, overflow, non-numeric input)
5. The handling of negative numbers in the Int64 test
6. The significance of the return values from the conversion functions

The comments are placed to help future maintainers understand:
- The test scenarios being covered
- The expected behavior in different cases
- The purpose of each assertion
- The edge cases being verified