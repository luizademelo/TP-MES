Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/slice/percent_encoding.h"

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <cstdint>
#include <utility>

#include "absl/log/check.h"
#include "src/core/util/bitset.h"

namespace grpc_core {

namespace {
// BitSet class representing URL-safe characters that don't need percent-encoding
class UrlTable : public BitSet<256> {
 public:
  // Constructor initializes the bitset with URL-safe characters:
  // - Lowercase letters (a-z)
  // - Uppercase letters (A-Z)
  // - Digits (0-9)
  // - Special characters: '-', '_', '.', '~'
  constexpr UrlTable() {
    for (int i = 'a'; i <= 'z'; i++) set(i);
    for (int i = 'A'; i <= 'Z'; i++) set(i);
    for (int i = '0'; i <= '9'; i++) set(i);
    set('-');
    set('_');
    set('.');
    set('~');
  }
};

// Global instance of URL-safe characters table
constexpr UrlTable g_url_table;

// BitSet class representing a broader set of compatible characters that don't need percent-encoding
class CompatibleTable : public BitSet<256> {
 public:
  // Constructor initializes the bitset with all printable ASCII characters (32-126)
  // except '%' which always needs encoding
  constexpr CompatibleTable() {
    for (int i = 32; i <= 126; i++) {
      if (i == '%') continue;
      set(i);
    }
  }
};

// Global instance of compatible characters table
constexpr CompatibleTable g_compatible_table;

// Returns the appropriate lookup table based on the requested percent encoding type
const BitSet<256>& LookupTableForPercentEncodingType(PercentEncodingType type) {
  switch (type) {
    case PercentEncodingType::URL:
      return g_url_table;
    case PercentEncodingType::Compatible:
      return g_compatible_table;
  }

  // Should never reach here - abort if invalid type is passed
  GPR_UNREACHABLE_CODE(abort());
}
}

// Percent-encodes a slice according to the specified encoding type
Slice PercentEncodeSlice(Slice slice, PercentEncodingType type) {
  // Hex digits for percent encoding
  static const uint8_t hex[] = "0123456789ABCDEF";

  // Get the appropriate lookup table for the encoding type
  const BitSet<256>& lut = LookupTableForPercentEncodingType(type);

  // First pass: calculate output length and check if any encoding is needed
  size_t output_length = 0;
  bool any_reserved_bytes = false;
  for (uint8_t c : slice) {
    bool unres = lut.is_set(c);
    output_length += unres ? 1 : 3;  // Reserved bytes take 3 chars (%XX)
    any_reserved_bytes |= !unres;
  }

  // If no reserved bytes found, return original slice
  if (!any_reserved_bytes) {
    return slice;
  }

  // Second pass: perform the actual encoding
  auto out = MutableSlice::CreateUninitialized(output_length);
  uint8_t* q = out.begin();
  for (uint8_t c : slice) {
    if (lut.is_set(c)) {
      // Copy character directly if it's in the allowed set
      *q++ = c;
    } else {
      // Percent-encode the character as %XX
      *q++ = '%';
      *q++ = hex[c >> 4];    // High nibble
      *q++ = hex[c & 15];    // Low nibble
    }
  }
  // Verify we filled exactly the expected output length
  CHECK(q == out.end());
  return Slice(std::move(out));
}

// Checks if the given pointer points to a valid hex digit
static bool ValidHex(const uint8_t* p, const uint8_t* end) {
  if (p >= end) return false;
  return (*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') ||
         (*p >= 'A' && *p <= 'F');
}

// Converts a hex character to its numeric value
static uint8_t DeHex(uint8_t c) {
  if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
  if (c >= 'A' && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);
  if (c >= 'a' && c <= 'f') return static_cast<uint8_t>(c - 'a' + 10);
  // Should never reach here for valid input
  GPR_UNREACHABLE_CODE(return 255);
}

// Decodes percent-encoded sequences in a slice, leniently handling invalid sequences
Slice PermissivePercentDecodeSlice(Slice slice_in) {
  // First check if there are any percent-encoded sequences
  bool any_percent_encoded_stuff = false;
  for (uint8_t c : slice_in) {
    if (c == '%') {
      any_percent_encoded_stuff = true;
      break;
    }
  }
  // If no percent-encoded sequences found, return original slice
  if (!any_percent_encoded_stuff) return slice_in;

  // Perform the decoding in-place
  MutableSlice out = slice_in.TakeMutable();
  uint8_t* q = out.begin();
  const uint8_t* p = out.begin();
  const uint8_t* end = out.end();
  while (p != end) {
    if (*p == '%') {
      // Check if we have two valid hex digits following the '%'
      if (!ValidHex(p + 1, end) || !ValidHex(p + 2, end)) {
        // Invalid sequence - copy the '%' as-is and continue
        *q++ = *p++;
      } else {
        // Valid sequence - decode and store the byte
        *q++ = static_cast<uint8_t>(DeHex(p[1]) << 4) | (DeHex(p[2]));
        p += 3;
      }
    } else {
      // Copy non-percent characters as-is
      *q++ = *p++;
    }
  }
  // Return the decoded slice (which may be shorter than original)
  return Slice(out.TakeSubSlice(0, q - out.begin()));
}

}
```