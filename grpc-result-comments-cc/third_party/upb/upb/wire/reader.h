Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_READER_H_
#define UPB_WIRE_READER_H_

// Include necessary headers for endian conversion, input stream handling,
// internal reader implementation, and wire type definitions
#include "upb/base/internal/endian.h"
#include "upb/wire/eps_copy_input_stream.h"
#include "upb/wire/internal/reader.h"
#include "upb/wire/types.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

// Reads a protocol buffer tag from the wire format.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   tag: Output parameter for the read tag
// Returns:
//   Updated pointer position after reading, or NULL if reading failed
UPB_FORCEINLINE const char* upb_WireReader_ReadTag(const char* ptr,
                                                   uint32_t* tag) {
  uint64_t val;
  ptr = UPB_PRIVATE(_upb_WireReader_ReadVarint)(ptr, &val, 5, UINT32_MAX);
  if (!ptr) return NULL;
  *tag = val;
  return ptr;
}

// API function declarations (implemented elsewhere)
UPB_API_INLINE uint32_t upb_WireReader_GetFieldNumber(uint32_t tag);
UPB_API_INLINE uint8_t upb_WireReader_GetWireType(uint32_t tag);

// Reads a varint from the wire format.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   val: Output parameter for the read value
// Returns:
//   Updated pointer position after reading, or NULL if reading failed
UPB_INLINE const char* upb_WireReader_ReadVarint(const char* ptr,
                                                 uint64_t* val) {
  return UPB_PRIVATE(_upb_WireReader_ReadVarint)(ptr, val, 10, UINT64_MAX);
}

// Skips over a varint in the wire format without storing its value.
// Args:
//   ptr: Pointer to the current position in the input buffer
// Returns:
//   Updated pointer position after skipping
UPB_INLINE const char* upb_WireReader_SkipVarint(const char* ptr) {
  uint64_t val;
  return upb_WireReader_ReadVarint(ptr, &val);
}

// Reads a size value (delimited field length) from the wire format.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   size: Output parameter for the read size
// Returns:
//   Updated pointer position after reading, or NULL if size is too large
UPB_INLINE const char* upb_WireReader_ReadSize(const char* ptr, int* size) {
  uint64_t size64;
  ptr = upb_WireReader_ReadVarint(ptr, &size64);
  if (!ptr || size64 >= INT32_MAX) return NULL;
  *size = size64;
  return ptr;
}

// Reads a 32-bit fixed-width value from the wire format.
// Performs big-endian to host byte order conversion.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   val: Output parameter for the read value
// Returns:
//   Updated pointer position after reading
UPB_INLINE const char* upb_WireReader_ReadFixed32(const char* ptr, void* val) {
  uint32_t uval;
  memcpy(&uval, ptr, 4);
  uval = upb_BigEndian32(uval);
  memcpy(val, &uval, 4);
  return ptr + 4;
}

// Reads a 64-bit fixed-width value from the wire format.
// Performs big-endian to host byte order conversion.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   val: Output parameter for the read value
// Returns:
//   Updated pointer position after reading
UPB_INLINE const char* upb_WireReader_ReadFixed64(const char* ptr, void* val) {
  uint64_t uval;
  memcpy(&uval, ptr, 8);
  uval = upb_BigEndian64(uval);
  memcpy(val, &uval, 8);
  return ptr + 8;
}

// Internal function to skip a group field in the wire format.
const char* UPB_PRIVATE(_upb_WireReader_SkipGroup)(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream);

// TODO: evaluate how the depth_limit should be specified. Do users need
//       control over this parameter?

// Skips a group field in the wire format with default depth limit.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   tag: The field tag containing the group
//   stream: Input stream context
// Returns:
//   Updated pointer position after skipping the group
UPB_INLINE const char* upb_WireReader_SkipGroup(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, 100, stream);
}

// Internal function to skip a field value based on its wire type.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   tag: The field tag containing type information
//   depth_limit: Maximum recursion depth for nested structures
//   stream: Input stream context
// Returns:
//   Updated pointer position after skipping, or NULL for unsupported types
UPB_INLINE const char* _upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream) {
  switch (upb_WireReader_GetWireType(tag)) {
    case kUpb_WireType_Varint:
      return upb_WireReader_SkipVarint(ptr);
    case kUpb_WireType_32Bit:
      return ptr + 4;  // Skip 4 bytes for 32-bit fixed-width
    case kUpb_WireType_64Bit:
      return ptr + 8;  // Skip 8 bytes for 64-bit fixed-width
    case kUpb_WireType_Delimited: {
      int size;
      ptr = upb_WireReader_ReadSize(ptr, &size);
      if (!ptr) return NULL;
      ptr += size;  // Skip the specified number of bytes
      return ptr;
    }
    case kUpb_WireType_StartGroup:
      return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, depth_limit,
                                                    stream);
    case kUpb_WireType_EndGroup:
      return NULL;  // End group should be handled by the group skipper
    default:
      return NULL;  // Unknown wire type
  }
}

// TODO: evaluate how the depth_limit should be specified. Do users need
//       control over this parameter?

// Skips a field value with default depth limit.
// Args:
//   ptr: Pointer to the current position in the input buffer
//   tag: The field tag containing type information
//   stream: Input stream context
// Returns:
//   Updated pointer position after skipping
UPB_INLINE const char* upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return _upb_WireReader_SkipValue(ptr, tag, 100, stream);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_WIRE_READER_H_
```