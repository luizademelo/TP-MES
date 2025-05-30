
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_DECODE_H_
#define UPB_WIRE_DECODE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/mem/arena.h"
#include "upb/message/message.h"
#include "upb/mini_table/extension_registry.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

enum {

  kUpb_DecodeOption_AliasString = 1,

  kUpb_DecodeOption_CheckRequired = 2,

  kUpb_DecodeOption_ExperimentalAllowUnlinked = 4,

  kUpb_DecodeOption_AlwaysValidateUtf8 = 8,
};

UPB_INLINE uint32_t upb_DecodeOptions_MaxDepth(uint16_t depth) {
  return (uint32_t)depth << 16;
}

UPB_INLINE uint16_t upb_DecodeOptions_GetMaxDepth(uint32_t options) {
  return options >> 16;
}

uint16_t upb_DecodeOptions_GetEffectiveMaxDepth(uint32_t options);

UPB_INLINE int upb_Decode_LimitDepth(uint32_t decode_options, uint32_t limit) {
  uint32_t max_depth = upb_DecodeOptions_GetMaxDepth(decode_options);
  if (max_depth > limit) max_depth = limit;
  return upb_DecodeOptions_MaxDepth(max_depth) | (decode_options & 0xffff);
}

typedef enum {
  kUpb_DecodeStatus_Ok = 0,
  kUpb_DecodeStatus_Malformed = 1,
  kUpb_DecodeStatus_OutOfMemory = 2,
  kUpb_DecodeStatus_BadUtf8 = 3,
  kUpb_DecodeStatus_MaxDepthExceeded =
      4,

  kUpb_DecodeStatus_MissingRequired = 5,

  kUpb_DecodeStatus_UnlinkedSubMessage = 6,
} upb_DecodeStatus;

UPB_API upb_DecodeStatus upb_Decode(const char* buf, size_t size,
                                    upb_Message* msg, const upb_MiniTable* mt,
                                    const upb_ExtensionRegistry* extreg,
                                    int options, upb_Arena* arena);

UPB_API upb_DecodeStatus upb_DecodeLengthPrefixed(
    const char* buf, size_t size, upb_Message* msg, size_t* num_bytes_read,
    const upb_MiniTable* mt, const upb_ExtensionRegistry* extreg, int options,
    upb_Arena* arena);

UPB_API const char* upb_DecodeStatus_String(upb_DecodeStatus status);
#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
