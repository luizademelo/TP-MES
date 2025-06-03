Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

// Header guard to prevent multiple inclusions of this header file
#ifndef GRPC_SRC_CORE_LIB_SLICE_PERCENT_ENCODING_H
#define GRPC_SRC_CORE_LIB_SLICE_PERCENT_ENCODING_H

// Include platform-specific support macros and types
#include <grpc/support/port_platform.h>

// Include the Slice class definition
#include "src/core/lib/slice/slice.h"

namespace grpc_core {

// Enumeration defining different types of percent encoding schemes
enum class PercentEncodingType {
  // Standard URL percent encoding as defined in RFC 3986
  URL,

  // A more compatible encoding scheme that might handle additional cases
  Compatible
};

// Percent-encodes a Slice according to the specified encoding type
// @param slice The input data to be encoded
// @param type The encoding scheme to use (URL or Compatible)
// @return A new Slice containing the percent-encoded data
Slice PercentEncodeSlice(Slice slice, PercentEncodingType type);

// Decodes a percent-encoded Slice, being permissive with invalid encodings
// (e.g., not failing on malformed percent encodings)
// @param slice_in The percent-encoded input data
// @return A new Slice containing the decoded data
Slice PermissivePercentDecodeSlice(Slice slice_in);

}  // namespace grpc_core

#endif  // GRPC_SRC_CORE_LIB_SLICE_PERCENT_ENCODING_H
```

The comments added:
1. Explained the purpose of the header guard
2. Documented the purpose of the platform support include
3. Added documentation for the Slice include
4. Documented the PercentEncodingType enum and its values
5. Added detailed documentation for both function declarations including parameters and return values
6. Added namespace closing comment
7. Added comment for the header guard endif

The comments follow standard documentation practices, explaining both what the code does and why certain design decisions might have been made (like the permissive decoding).