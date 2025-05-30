
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_COMPAT_H_
#define UPB_MINI_TABLE_COMPAT_H_

#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

bool upb_MiniTable_Compatible(const upb_MiniTable* src,
                              const upb_MiniTable* dst);

typedef enum {
  kUpb_MiniTableEquals_NotEqual,
  kUpb_MiniTableEquals_Equal,
  kUpb_MiniTableEquals_OutOfMemory,
} upb_MiniTableEquals_Status;

upb_MiniTableEquals_Status upb_MiniTable_Equals(const upb_MiniTable* src,
                                                const upb_MiniTable* dst);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
