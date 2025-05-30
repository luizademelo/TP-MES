
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_EXTENSION_H_
#define UPB_MINI_TABLE_INTERNAL_EXTENSION_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mini_table/internal/field.h"
#include "upb/mini_table/internal/sub.h"

#include "upb/port/def.inc"

struct upb_MiniTableExtension {

  struct upb_MiniTableField UPB_PRIVATE(field);

  const struct upb_MiniTable* UPB_PRIVATE(extendee);
  union upb_MiniTableSub UPB_PRIVATE(sub);
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType
upb_MiniTableExtension_CType(const struct upb_MiniTableExtension* e) {
  return upb_MiniTableField_CType(&e->UPB_PRIVATE(field));
}

UPB_API_INLINE uint32_t
upb_MiniTableExtension_Number(const struct upb_MiniTableExtension* e) {
  return e->UPB_PRIVATE(field).UPB_ONLYBITS(number);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableExtension_GetSubMessage(
    const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Message) {
    return NULL;
  }
  return upb_MiniTableSub_Message(e->UPB_PRIVATE(sub));
}

UPB_API_INLINE const struct upb_MiniTableEnum*
upb_MiniTableExtension_GetSubEnum(const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Enum) {
    return NULL;
  }
  return upb_MiniTableSub_Enum(e->UPB_PRIVATE(sub));
}

UPB_API_INLINE bool upb_MiniTableExtension_SetSubMessage(
    struct upb_MiniTableExtension* e, const struct upb_MiniTable* m) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Message) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(submsg) = m;
  return true;
}

UPB_API_INLINE bool upb_MiniTableExtension_SetSubEnum(
    struct upb_MiniTableExtension* e, const struct upb_MiniTableEnum* en) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Enum) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(subenum) = en;
  return true;
}

UPB_INLINE upb_FieldRep UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(
    const struct upb_MiniTableExtension* e) {
  return UPB_PRIVATE(_upb_MiniTableField_GetRep)(&e->UPB_PRIVATE(field));
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
