
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/reflection/def_type.h"

#include "upb/port/def.inc"

upb_deftype_t _upb_DefType_Type(upb_value v) {
  const uintptr_t num = (uintptr_t)upb_value_getconstptr(v);
  return num & UPB_DEFTYPE_MASK;
}

upb_value _upb_DefType_Pack(const void* ptr, upb_deftype_t type) {
  uintptr_t num = (uintptr_t)ptr;
  UPB_ASSERT((num & UPB_DEFTYPE_MASK) == 0);
  num |= type;
  return upb_value_constptr((const void*)num);
}

const void* _upb_DefType_Unpack(upb_value v, upb_deftype_t type) {
  uintptr_t num = (uintptr_t)upb_value_getconstptr(v);
  return (num & UPB_DEFTYPE_MASK) == type
             ? (const void*)(num & ~UPB_DEFTYPE_MASK)
             : NULL;
}
