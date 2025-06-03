Here's the commented version of the code:

```c++
// Copyright 2024 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions of this header file
#ifndef UPB_TEXT_OPTIONS_H_
#define UPB_TEXT_OPTIONS_H_

// Enum defining text encoding options for protocol buffers text format
// These values can be combined using bitwise OR operations
enum {
  // Format the output as a single line (no newlines or indentation)
  UPB_TXTENC_SINGLELINE = 1,

  // Skip unknown fields during encoding rather than raising an error
  UPB_TXTENC_SKIPUNKNOWN = 2,

  // Do not sort fields numerically (output in declaration order)
  UPB_TXTENC_NOSORT = 4
};

// End of header guard
#endif
```

The comments explain:
1. The purpose of the header guard
2. The overall purpose of the enum
3. The meaning and usage of each flag
4. That the flags are designed to be combinable via bitwise operations
5. The closing of the header guard

Each enum value is documented with:
- What behavior it enables
- What the default/alternative behavior would be
- Any notable consequences of using the option