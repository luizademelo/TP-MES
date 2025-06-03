Here's the commented version of the code:

```c++
// Header guard to prevent multiple inclusions of this header file
#ifndef THIRD_PARTY_UTF8_RANGE_UTF8_RANGE_H_
#define THIRD_PARTY_UTF8_RANGE_UTF8_RANGE_H_

// Include standard size definitions
#include <stddef.h>

// C++ compatibility: if compiled as C++, use C linkage
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Checks if the given UTF-8 encoded string is valid.
 * 
 * @param data Pointer to the UTF-8 string to validate
 * @param len Length of the string in bytes
 * @return 1 if the string is valid UTF-8, 0 otherwise
 */
int utf8_range_IsValid(const char* data, size_t len);

/**
 * Finds the length of the longest valid UTF-8 prefix in the given string.
 * 
 * @param data Pointer to the UTF-8 string to check
 * @param len Length of the string in bytes
 * @return Length (in bytes) of the longest valid UTF-8 prefix
 */
size_t utf8_range_ValidPrefix(const char* data, size_t len);

// End of C linkage section for C++
#ifdef __cplusplus
}
#endif

// End of header guard
#endif  // THIRD_PARTY_UTF8_RANGE_UTF8_RANGE_H_
```

The comments explain:
1. The purpose of the header guard
2. The inclusion of stddef.h for size_t
3. The C linkage specification for C++ compatibility
4. Detailed documentation for each function including parameters and return values
5. The closing of the header guard

The comments follow standard documentation practices and provide clear explanations of the code's purpose and functionality.