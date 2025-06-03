Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

// Header guard to prevent multiple inclusions
#ifndef UPB_WIRE_INTERNAL_READER_H_
#define UPB_WIRE_INTERNAL_READER_H_

#include "upb/port/def.inc"

// Constants for wire type handling:
// - Number of bits used for wire type in protocol buffers tags
// - Bitmask to extract wire type from tag
#define kUpb_WireReader_WireTypeBits 3
#define kUpb_WireReader_WireTypeMask 7

// Structure to hold the result of reading a long varint:
// - ptr: Pointer to the next byte after the varint
// - val: The decoded varint value
typedef struct {
  const char* ptr;
  uint64_t val;
} UPB_PRIVATE(_upb_WireReader_LongVarint);

#ifdef __cplusplus
extern "C" {
#endif

// Function prototype for reading a long varint (variable-length integer)
// - ptr: Pointer to the buffer containing the varint
// - val: Initial byte value (first byte of the varint)
UPB_PRIVATE(_upb_WireReader_LongVarint)
UPB_PRIVATE(_upb_WireReader_ReadLongVarint)(const char* ptr, uint64_t val);

// Inline function to read a varint from a buffer with safety checks:
// - ptr: Pointer to the buffer containing the varint
// - val: Output parameter for the decoded value
// - maxlen: Maximum allowed length of the varint (for security)
// - maxval: Maximum allowed value of the varint
UPB_FORCEINLINE const char* UPB_PRIVATE(_upb_WireReader_ReadVarint)(
    const char* ptr, uint64_t* val, int maxlen, uint64_t maxval) {
  // Read first byte
  uint64_t byte = (uint8_t)*ptr;
  
  // Fast path for single-byte varints (most common case)
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = (uint32_t)byte;
    return ptr + 1;
  }
  
  // Slow path for multi-byte varints
  const char* start = ptr;
  UPB_PRIVATE(_upb_WireReader_LongVarint)
  res = UPB_PRIVATE(_upb_WireReader_ReadLongVarint)(ptr, byte);
  
  // Validate the result:
  // - Check if reading was successful (res.ptr != NULL)
  // - Check if varint length exceeds maxlen (if maxlen is less than 10)
  // - Check if value exceeds maxval
  if (!res.ptr || (maxlen < 10 && res.ptr - start > maxlen) ||
      res.val > maxval) {
    return NULL;
  }
  
  *val = res.val;
  return res.ptr;
}

// Extracts the field number from a protocol buffers tag
UPB_API_INLINE uint32_t upb_WireReader_GetFieldNumber(uint32_t tag) {
  // Field number is stored in the upper bits of the tag
  return tag >> kUpb_WireReader_WireTypeBits;
}

// Extracts the wire type from a protocol buffers tag
UPB_API_INLINE uint8_t upb_WireReader_GetWireType(uint32_t tag) {
  // Wire type is stored in the lower 3 bits of the tag
  return tag & kUpb_WireReader_WireTypeMask;
}

#ifdef __cplusplus
}  // extern "C"
#endif

#include "upb/port/undef.inc"

#endif  // UPB_WIRE_INTERNAL_READER_H_
```

The comments explain:
1. The purpose of each constant and structure
2. The functionality of each function
3. The parameters and return values
4. The logic flow in the varint reading function
5. The bit manipulation used in tag processing
6. The safety checks performed during varint reading

The comments are designed to help future developers understand:
- The protocol buffers wire format handling
- The varint decoding process
- The safety considerations in the implementation
- The purpose of each bit manipulation operation