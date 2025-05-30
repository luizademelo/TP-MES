
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_BASE_INTERNAL_LOG2_H_
#define UPB_BASE_INTERNAL_LOG2_H_

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE int upb_Log2Ceiling(int x) {
  if (x <= 1) return 0;
#ifdef __GNUC__
  return 32 - __builtin_clz(x - 1);
#else
  int lg2 = 0;
  while ((1 << lg2) < x) lg2++;
  return lg2;
#endif
}

UPB_INLINE int upb_RoundUpToPowerOfTwo(int x) {
  return 1 << upb_Log2Ceiling(x);
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
