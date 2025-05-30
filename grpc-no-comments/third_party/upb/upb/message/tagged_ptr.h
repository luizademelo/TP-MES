
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_TAGGED_PTR_H_
#define UPB_MINI_TABLE_TAGGED_PTR_H_

#include <stdint.h>

#include "upb/message/internal/tagged_ptr.h"
#include "upb/message/message.h"

#include "upb/port/def.inc"

typedef uintptr_t upb_TaggedMessagePtr;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE bool upb_TaggedMessagePtr_IsEmpty(upb_TaggedMessagePtr ptr);

UPB_API_INLINE upb_Message* upb_TaggedMessagePtr_GetNonEmptyMessage(
    upb_TaggedMessagePtr ptr);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
