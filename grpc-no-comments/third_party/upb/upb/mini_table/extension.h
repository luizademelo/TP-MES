
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_EXTENSION_H_
#define UPB_MINI_TABLE_EXTENSION_H_

#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/enum.h"
#include "upb/mini_table/internal/extension.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

typedef struct upb_MiniTableExtension upb_MiniTableExtension;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType
upb_MiniTableExtension_CType(const upb_MiniTableExtension* e);

UPB_API_INLINE uint32_t
upb_MiniTableExtension_Number(const upb_MiniTableExtension* e);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableExtension_GetSubMessage(
    const upb_MiniTableExtension* e);

UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableExtension_GetSubEnum(
    const upb_MiniTableExtension* e);

UPB_API_INLINE bool upb_MiniTableExtension_SetSubMessage(
    upb_MiniTableExtension* e, const upb_MiniTable* m);

UPB_API_INLINE bool upb_MiniTableExtension_SetSubEnum(
    upb_MiniTableExtension* e, const upb_MiniTableEnum* m);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
