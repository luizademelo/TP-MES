
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_ENCODE_H_
#define UPB_WIRE_ENCODE_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/mem/arena.h"
#include "upb/message/message.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

enum {

  kUpb_EncodeOption_Deterministic = 1,

  kUpb_EncodeOption_SkipUnknown = 2,

  kUpb_EncodeOption_CheckRequired = 4,
};

typedef enum {
  kUpb_EncodeStatus_Ok = 0,
  kUpb_EncodeStatus_OutOfMemory = 1,
  kUpb_EncodeStatus_MaxDepthExceeded = 2,

  kUpb_EncodeStatus_MissingRequired = 3,
} upb_EncodeStatus;

UPB_INLINE uint32_t upb_EncodeOptions_MaxDepth(uint16_t depth) {
  return (uint32_t)depth << 16;
}

UPB_INLINE uint16_t upb_EncodeOptions_GetMaxDepth(uint32_t options) {
  return options >> 16;
}

uint16_t upb_EncodeOptions_GetEffectiveMaxDepth(uint32_t options);

UPB_INLINE int upb_Encode_LimitDepth(uint32_t encode_options, uint32_t limit) {
  uint32_t max_depth = upb_EncodeOptions_GetMaxDepth(encode_options);
  if (max_depth > limit) max_depth = limit;
  return upb_EncodeOptions_MaxDepth(max_depth) | (encode_options & 0xffff);
}

UPB_API upb_EncodeStatus upb_Encode(const upb_Message* msg,
                                    const upb_MiniTable* l, int options,
                                    upb_Arena* arena, char** buf, size_t* size);

UPB_API upb_EncodeStatus upb_EncodeLengthPrefixed(const upb_Message* msg,
                                                  const upb_MiniTable* l,
                                                  int options, upb_Arena* arena,
                                                  char** buf, size_t* size);

UPB_API const char* upb_EncodeStatus_String(upb_EncodeStatus status);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
