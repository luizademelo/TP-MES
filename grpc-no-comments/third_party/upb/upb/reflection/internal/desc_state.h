
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_DESC_STATE_INTERNAL_H_
#define UPB_REFLECTION_DESC_STATE_INTERNAL_H_

#include "upb/mem/arena.h"
#include "upb/mini_descriptor/internal/encode.h"

#include "upb/port/def.inc"

// TODO: Move some of this state directly into the encoder, maybe.
typedef struct {
  upb_MtDataEncoder e;
  size_t bufsize;
  char* buf;
  char* ptr;
} upb_DescState;

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void _upb_DescState_Init(upb_DescState* d) {
  d->bufsize = kUpb_MtDataEncoder_MinSize * 2;
  d->buf = NULL;
  d->ptr = NULL;
}

bool _upb_DescState_Grow(upb_DescState* d, upb_Arena* a);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
