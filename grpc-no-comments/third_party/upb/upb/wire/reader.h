
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_READER_H_
#define UPB_WIRE_READER_H_

#include "upb/base/internal/endian.h"
#include "upb/wire/eps_copy_input_stream.h"
#include "upb/wire/internal/reader.h"
#include "upb/wire/types.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_FORCEINLINE const char* upb_WireReader_ReadTag(const char* ptr,
                                                   uint32_t* tag) {
  uint64_t val;
  ptr = UPB_PRIVATE(_upb_WireReader_ReadVarint)(ptr, &val, 5, UINT32_MAX);
  if (!ptr) return NULL;
  *tag = val;
  return ptr;
}

UPB_API_INLINE uint32_t upb_WireReader_GetFieldNumber(uint32_t tag);

UPB_API_INLINE uint8_t upb_WireReader_GetWireType(uint32_t tag);

UPB_INLINE const char* upb_WireReader_ReadVarint(const char* ptr,
                                                 uint64_t* val) {
  return UPB_PRIVATE(_upb_WireReader_ReadVarint)(ptr, val, 10, UINT64_MAX);
}

UPB_INLINE const char* upb_WireReader_SkipVarint(const char* ptr) {
  uint64_t val;
  return upb_WireReader_ReadVarint(ptr, &val);
}

UPB_INLINE const char* upb_WireReader_ReadSize(const char* ptr, int* size) {
  uint64_t size64;
  ptr = upb_WireReader_ReadVarint(ptr, &size64);
  if (!ptr || size64 >= INT32_MAX) return NULL;
  *size = size64;
  return ptr;
}

UPB_INLINE const char* upb_WireReader_ReadFixed32(const char* ptr, void* val) {
  uint32_t uval;
  memcpy(&uval, ptr, 4);
  uval = upb_BigEndian32(uval);
  memcpy(val, &uval, 4);
  return ptr + 4;
}

UPB_INLINE const char* upb_WireReader_ReadFixed64(const char* ptr, void* val) {
  uint64_t uval;
  memcpy(&uval, ptr, 8);
  uval = upb_BigEndian64(uval);
  memcpy(val, &uval, 8);
  return ptr + 8;
}

const char* UPB_PRIVATE(_upb_WireReader_SkipGroup)(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream);

// TODO: evaluate how the depth_limit should be specified. Do users need

UPB_INLINE const char* upb_WireReader_SkipGroup(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, 100, stream);
}

UPB_INLINE const char* _upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream) {
  switch (upb_WireReader_GetWireType(tag)) {
    case kUpb_WireType_Varint:
      return upb_WireReader_SkipVarint(ptr);
    case kUpb_WireType_32Bit:
      return ptr + 4;
    case kUpb_WireType_64Bit:
      return ptr + 8;
    case kUpb_WireType_Delimited: {
      int size;
      ptr = upb_WireReader_ReadSize(ptr, &size);
      if (!ptr) return NULL;
      ptr += size;
      return ptr;
    }
    case kUpb_WireType_StartGroup:
      return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, depth_limit,
                                                    stream);
    case kUpb_WireType_EndGroup:
      return NULL;
    default:
      return NULL;
  }
}

// TODO: evaluate how the depth_limit should be specified. Do users need

UPB_INLINE const char* upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return _upb_WireReader_SkipValue(ptr, tag, 100, stream);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
