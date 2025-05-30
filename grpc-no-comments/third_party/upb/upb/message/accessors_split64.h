
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_ACCESSORS_SPLIT64_H_
#define UPB_MESSAGE_ACCESSORS_SPLIT64_H_

#include "upb/message/accessors.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE uint32_t upb_Message_GetInt64Hi(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)(upb_Message_GetInt64(msg, field, default_value) >> 32);
}

UPB_API_INLINE uint32_t upb_Message_GetInt64Lo(const upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t default_value) {
  return (uint32_t)upb_Message_GetInt64(msg, field, default_value);
}

UPB_API_INLINE bool upb_Message_SetInt64Split(upb_Message* msg,
                                              const upb_MiniTableField* field,
                                              uint32_t hi, uint32_t lo,
                                              upb_Arena* arena) {
  return upb_Message_SetInt64(msg, field, ((int64_t)hi << 32) | lo, arena);
}

UPB_API_INLINE uint32_t upb_Message_GetUInt64Hi(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)(upb_Message_GetUInt64(msg, field, default_value) >> 32);
}

UPB_API_INLINE uint32_t upb_Message_GetUInt64Lo(const upb_Message* msg,
                                                const upb_MiniTableField* field,
                                                uint32_t default_value) {
  return (uint32_t)upb_Message_GetUInt64(msg, field, default_value);
}

UPB_API_INLINE bool upb_Message_SetUInt64Split(upb_Message* msg,
                                               const upb_MiniTableField* field,
                                               uint32_t hi, uint32_t lo,
                                               upb_Arena* arena) {
  return upb_Message_SetUInt64(msg, field, ((uint64_t)hi << 32) | lo, arena);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
