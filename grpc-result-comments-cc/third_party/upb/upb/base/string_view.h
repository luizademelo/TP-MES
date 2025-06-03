Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_STRING_VIEW_H_
#define UPB_BASE_STRING_VIEW_H_

#include <string.h>

#include "upb/port/def.inc"

// Macro to initialize a upb_StringView with given pointer and length
#define UPB_STRINGVIEW_INIT(ptr, len) \
  { ptr, len }

// Format specifier for printf-style functions to print a upb_StringView
#define UPB_STRINGVIEW_FORMAT "%.*s"
// Arguments for printf-style functions to print a upb_StringView
#define UPB_STRINGVIEW_ARGS(view) (int)(view).size, (view).data

// Lightweight non-owning reference to a string (similar to C++17 string_view)
// Contains:
//   data - pointer to the string data
//   size - length of the string in bytes
typedef struct {
  const char* data;
  size_t size;
} upb_StringView;

#ifdef __cplusplus
extern "C" {
#endif

// Creates a upb_StringView from raw data pointer and size
// Args:
//   data: Pointer to the string data (does not take ownership)
//   size: Length of the string in bytes
// Returns: Initialized upb_StringView structure
UPB_API_INLINE upb_StringView upb_StringView_FromDataAndSize(const char* data,
                                                             size_t size) {
  upb_StringView ret;
  ret.data = data;
  ret.size = size;
  return ret;
}

// Creates a upb_StringView from a null-terminated C string
// Args:
//   data: Null-terminated string (does not take ownership)
// Returns: Initialized upb_StringView structure
UPB_INLINE upb_StringView upb_StringView_FromString(const char* data) {
  return upb_StringView_FromDataAndSize(data, strlen(data));
}

// Compares two string views for equality
// Args:
//   a: First string view to compare
//   b: Second string view to compare
// Returns: true if contents are identical, false otherwise
UPB_INLINE bool upb_StringView_IsEqual(upb_StringView a, upb_StringView b) {
  return (a.size == b.size) && (!a.size || !memcmp(a.data, b.data, a.size));
}

// Lexicographically compares two string views
// Args:
//   a: First string view to compare
//   b: Second string view to compare
// Returns:
//   <0 if a < b
//   0 if a == b
//   >0 if a > b
UPB_INLINE int upb_StringView_Compare(upb_StringView a, upb_StringView b) {
  int result = memcmp(a.data, b.data, UPB_MIN(a.size, b.size));
  if (result == 0) {
    return a.size - b.size;
  }
  return result;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_BASE_STRING_VIEW_H_
```

Key improvements made:
1. Added detailed comments for each function and macro explaining their purpose and usage
2. Documented parameters and return values
3. Explained the upb_StringView struct and its fields
4. Added clear section comments
5. Included a proper closing comment for the header guard
6. Explained the comparison function's return value convention
7. Noted the non-owning nature of the string view operations

The comments now provide comprehensive documentation for developers who need to use or maintain this string view implementation.