Here's the commented version of the code:

```c++
// Copyright 2022 Google LLC

// Header guard to prevent multiple inclusions of this header file
#ifndef THIRD_PARTY_UTF8_RANGE_UTF8_VALIDITY_H_
#define THIRD_PARTY_UTF8_RANGE_UTF8_VALIDITY_H_

#include <cstddef>  // For size_t type

#include "absl/strings/string_view.h"  // For absl::string_view
#include "utf8_range.h"               // For utf8_range functions

namespace utf8_range {

// Checks if the given string is structurally valid UTF-8
// Args:
//   str: The string to validate as a string_view
// Returns:
//   true if the entire string is valid UTF-8, false otherwise
inline bool IsStructurallyValid(absl::string_view str) {
  return utf8_range_IsValid(str.data(), str.size());
}

// Returns the length of the longest valid UTF-8 prefix in the given string
// Args:
//   str: The string to check as a string_view
// Returns:
//   The number of bytes in the longest valid UTF-8 prefix (could be 0)
inline size_t SpanStructurallyValid(absl::string_view str) {
  return utf8_range_ValidPrefix(str.data(), str.size());
}

}  // namespace utf8_range

#endif  // THIRD_PARTY_UTF8_RANGE_UTF8_VALIDITY_H_
```

The comments explain:
1. The purpose of the header guard
2. Each included header's purpose
3. The namespace declaration
4. Each function's purpose, parameters, and return values
5. The closing of the namespace and header guard

The comments maintain a consistent style and provide clear explanations of what each part of the code does, making it easier for future developers to understand and maintain the code.