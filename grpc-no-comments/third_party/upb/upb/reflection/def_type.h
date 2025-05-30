
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_DEF_TYPE_H_
#define UPB_REFLECTION_DEF_TYPE_H_

#include "upb/hash/common.h"

#include "upb/port/def.inc"

typedef enum {
  UPB_DEFTYPE_MASK = 7,

  UPB_DEFTYPE_EXT = 0,
  UPB_DEFTYPE_MSG = 1,
  UPB_DEFTYPE_ENUM = 2,
  UPB_DEFTYPE_ENUMVAL = 3,
  UPB_DEFTYPE_SERVICE = 4,

  UPB_DEFTYPE_FIELD = 0,
  UPB_DEFTYPE_ONEOF = 1,
} upb_deftype_t;

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void _upb_DefType_CheckPadding(size_t size) {
  UPB_ASSERT((size & UPB_DEFTYPE_MASK) == 0);
}

upb_deftype_t _upb_DefType_Type(upb_value v);

upb_value _upb_DefType_Pack(const void* ptr, upb_deftype_t type);

const void* _upb_DefType_Unpack(upb_value v, upb_deftype_t type);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
