Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_LEX_ATOI_H_
#define UPB_LEX_ATOI_H_

// Include standard integer types
#include <stdint.h>

// Include platform-specific definitions
#include "upb/port/def.inc"

// C++ compatibility - ensures functions have C linkage when compiled as C++
#ifdef __cplusplus
extern "C" {
#endif

// Function to convert a buffer of characters to an unsigned 64-bit integer
// Parameters:
//   ptr: Pointer to the start of the character buffer
//   end: Pointer to the end of the character buffer (exclusive)
//   val: Output parameter for the converted value
// Returns:
//   Pointer to the first character that couldn't be converted,
//   or 'end' if the entire buffer was converted successfully
const char* upb_BufToUint64(const char* ptr, const char* end, uint64_t* val);

// Function to convert a buffer of characters to a signed 64-bit integer
// Parameters:
//   ptr: Pointer to the start of the character buffer
//   end: Pointer to the end of the character buffer (exclusive)
//   val: Output parameter for the converted value
//   is_neg: Output parameter indicating if the number is negative
// Returns:
//   Pointer to the first character that couldn't be converted,
//   or 'end' if the entire buffer was converted successfully
const char* upb_BufToInt64(const char* ptr, const char* end, int64_t* val,
                           bool* is_neg);

// End C++ compatibility block
#ifdef __cplusplus
}
#endif

// Undefine any platform-specific macros that were defined earlier
#include "upb/port/undef.inc"

// End of header guard
#endif  // UPB_LEX_ATOI_H_
```

The comments explain:
1. The purpose of the header guard
2. The included files and their purposes
3. The C++ compatibility block
4. Detailed documentation for each function including parameters and return values
5. The purpose of the undef include
6. The closing of the header guard

The comments follow a consistent style and provide clear explanations of both the structural elements of the header file and the functionality of the exported functions.