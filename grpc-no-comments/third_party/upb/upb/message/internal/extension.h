
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_INTERNAL_EXTENSION_H_
#define UPB_MESSAGE_INTERNAL_EXTENSION_H_

#include <stddef.h>

#include "upb/mem/arena.h"
#include "upb/message/internal/array.h"
#include "upb/message/internal/map.h"
#include "upb/message/internal/types.h"
#include "upb/message/value.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/internal/field.h"

#include "upb/port/def.inc"

typedef struct {
  const upb_MiniTableExtension* ext;
  upb_MessageValue data;
} upb_Extension;

#ifdef __cplusplus
extern "C" {
#endif

upb_Extension* UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(
    struct upb_Message* msg, const upb_MiniTableExtension* ext,
    upb_Arena* arena);

const upb_Extension* UPB_PRIVATE(_upb_Message_Getext)(
    const struct upb_Message* msg, const upb_MiniTableExtension* ext);

UPB_INLINE bool UPB_PRIVATE(_upb_Extension_IsEmpty)(const upb_Extension* ext) {
  switch (
      UPB_PRIVATE(_upb_MiniTableField_Mode)(&ext->ext->UPB_PRIVATE(field))) {
    case kUpb_FieldMode_Scalar:
      return false;
    case kUpb_FieldMode_Array:
      return upb_Array_Size(ext->data.array_val) == 0;
    case kUpb_FieldMode_Map:
      return _upb_Map_Size(ext->data.map_val) == 0;
  }
  UPB_UNREACHABLE();
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
