
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_
#define UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_

#include <stdint.h>

#include "upb/message/internal/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE uintptr_t
UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(struct upb_Message* ptr, bool empty) {
  UPB_ASSERT(((uintptr_t)ptr & 1) == 0);
  return (uintptr_t)ptr | (empty ? 1 : 0);
}

UPB_API_INLINE bool upb_TaggedMessagePtr_IsEmpty(uintptr_t ptr) {
  return ptr & 1;
}

UPB_INLINE struct upb_Message* UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(
    uintptr_t ptr) {
  return (struct upb_Message*)(ptr & ~(uintptr_t)1);
}

UPB_API_INLINE struct upb_Message* upb_TaggedMessagePtr_GetNonEmptyMessage(
    uintptr_t ptr) {
  UPB_ASSERT(!upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

UPB_INLINE struct upb_Message* UPB_PRIVATE(
    _upb_TaggedMessagePtr_GetEmptyMessage)(uintptr_t ptr) {
  UPB_ASSERT(upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
