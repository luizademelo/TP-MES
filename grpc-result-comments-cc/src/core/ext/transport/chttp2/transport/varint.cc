Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include "src/core/ext/transport/chttp2/transport/varint.h"
#include <grpc/support/port_platform.h>
#include "absl/base/attributes.h"

namespace grpc_core {

// Calculates the length (in bytes) needed to represent a variable-length integer
// with the given tail value in HTTP/2 varint format.
// The tail value is the actual numeric value being encoded.
// Returns:
//   - 2 bytes for values < 128 (2^7)
//   - 3 bytes for values < 16384 (2^14)
//   - 4 bytes for values < 2097152 (2^21)
//   - 5 bytes for values < 268435456 (2^28)
//   - 6 bytes for larger values
size_t VarintLength(size_t tail_value) {
  if (tail_value < (1 << 7)) {
    return 2;
  } else if (tail_value < (1 << 14)) {
    return 3;
  } else if (tail_value < (1 << 21)) {
    return 4;
  } else if (tail_value < (1 << 28)) {
    return 5;
  } else {
    return 6;
  }
}

// Writes a variable-length integer in HTTP/2 varint format to the target buffer.
// Parameters:
//   tail_value: The numeric value to encode
//   target: Pointer to the buffer where the varint will be written
//   tail_length: The number of bytes to use for encoding (as determined by VarintLength)
//
// The encoding process:
// 1. For each byte except the last:
//    - Right-shifts the value to get the relevant bits
//    - Sets the MSB (0x80) to indicate continuation
// 2. For the last byte:
//    - Clears the MSB (using &= 0x7f) to mark the end of the varint
// Uses fallthrough in switch cases to efficiently handle all bytes in sequence
void VarintWriteTail(size_t tail_value, uint8_t* target, size_t tail_length) {
  switch (tail_length) {
    case 5:
      target[4] = static_cast<uint8_t>((tail_value >> 28) | 0x80);
      [[fallthrough]];
    case 4:
      target[3] = static_cast<uint8_t>((tail_value >> 21) | 0x80);
      [[fallthrough]];
    case 3:
      target[2] = static_cast<uint8_t>((tail_value >> 14) | 0x80);
      [[fallthrough]];
    case 2:
      target[1] = static_cast<uint8_t>((tail_value >> 7) | 0x80);
      [[fallthrough]];
    case 1:
      target[0] = static_cast<uint8_t>((tail_value) | 0x80);
  }
  // Clear the MSB of the last byte to mark end of varint
  target[tail_length - 1] &= 0x7f;
}

}  // namespace grpc_core
```

Key improvements in the comments:
1. Added clear description of what each function does
2. Explained the parameters and return values
3. Documented the encoding format and logic
4. Explained the purpose of the fallthrough behavior
5. Added note about the MSB handling in varint encoding
6. Added namespace closing comment
7. Explained the bit manipulation operations

The comments now provide comprehensive understanding of the varint encoding/decoding logic used in HTTP/2 transport layer.