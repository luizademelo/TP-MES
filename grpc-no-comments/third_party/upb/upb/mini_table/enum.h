
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_ENUM_H_
#define UPB_MINI_TABLE_ENUM_H_

#include <stdint.h>

#include "upb/mini_table/internal/enum.h"

#include "upb/port/def.inc"

typedef struct upb_MiniTableEnum upb_MiniTableEnum;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE bool upb_MiniTableEnum_CheckValue(const upb_MiniTableEnum* e,
                                                 uint32_t val);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
