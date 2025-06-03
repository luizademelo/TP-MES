Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this file
#ifndef UPB_LEX_ROUND_TRIP_H_
#define UPB_LEX_ROUND_TRIP_H_

// Include platform-specific definitions
#include "upb/port/def.inc"

// Define a constant for the buffer size used in round-trip conversions
// This buffer must be large enough to hold the string representation of any double/float
enum { kUpb_RoundTripBufferSize = 32 };

// C++ compatibility - ensure functions have C linkage when included in C++ code
#ifdef __cplusplus
extern "C" {
#endif

// Function declarations for round-trip conversion of floating-point numbers to strings
// These functions convert a floating-point value to a string representation that can
// be perfectly round-tripped back to the original binary value when parsed

// Converts a double-precision floating-point value to its string representation
// Parameters:
//   val: The double value to convert
//   buf: Output buffer for the string representation
//   size: Size of the output buffer (must be at least kUpb_RoundTripBufferSize)
void _upb_EncodeRoundTripDouble(double val, char* buf, size_t size);

// Converts a single-precision floating-point value to its string representation
// Parameters:
//   val: The float value to convert
//   buf: Output buffer for the string representation
//   size: Size of the output buffer (must be at least kUpb_RoundTripBufferSize)
void _upb_EncodeRoundTripFloat(float val, char* buf, size_t size);

#ifdef __cplusplus
}  // extern "C"
#endif

// Undo platform-specific definitions
#include "upb/port/undef.inc"

#endif  // UPB_LEX_ROUND_TRIP_H_
```

The comments explain:
1. The purpose of the header guard
2. The inclusion of platform-specific definitions
3. The purpose of the buffer size constant
4. The C++ compatibility section
5. Each function's purpose and parameters
6. The closing of the extern "C" block
7. The undefining of platform-specific macros
8. The closing of the header guard

The comments are designed to help future developers understand:
- Why certain constructs exist (like the extern "C" block)
- What the functions do
- What the parameters represent
- Any requirements (like buffer size constraints)