
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_FIELD_H_
#define UPB_MINI_TABLE_FIELD_H_

#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/field.h"

#include "upb/port/def.inc"

typedef struct upb_MiniTableField upb_MiniTableField;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType upb_MiniTableField_CType(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_HasPresence(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsArray(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsClosedEnum(
    const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsExtension(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsInOneof(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsMap(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsPacked(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsScalar(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsSubMessage(
    const upb_MiniTableField* f);

UPB_API_INLINE uint32_t upb_MiniTableField_Number(const upb_MiniTableField* f);

UPB_API_INLINE upb_FieldType
upb_MiniTableField_Type(const upb_MiniTableField* f);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
