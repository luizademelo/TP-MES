
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_INTERNAL_SIZE_LOG2_H_
#define UPB_MINI_TABLE_INTERNAL_SIZE_LOG2_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/base/descriptor_constants.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE int UPB_PRIVATE(_upb_CType_SizeLg2)(upb_CType c_type) {
  static const int8_t size[] = {
      0,
      2,
      2,
      2,
      2,
      UPB_SIZE(2, 3),
      3,
      3,
      3,
      UPB_SIZE(3, 4),
      UPB_SIZE(3, 4),
  };

  return size[c_type - 1];
}

UPB_INLINE int UPB_PRIVATE(_upb_FieldType_SizeLg2)(upb_FieldType field_type) {
  static const int8_t size[] = {
      3,
      2,
      3,
      3,
      2,
      3,
      2,
      0,
      UPB_SIZE(3, 4),
      UPB_SIZE(2, 3),
      UPB_SIZE(2, 3),
      UPB_SIZE(3, 4),
      2,
      2,
      2,
      3,
      2,
      3,
  };

  return size[field_type - 1];
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
