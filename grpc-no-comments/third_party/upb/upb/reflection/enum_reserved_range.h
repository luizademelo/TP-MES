
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_ENUM_RESERVED_RANGE_H_
#define UPB_REFLECTION_ENUM_RESERVED_RANGE_H_

#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

int32_t upb_EnumReservedRange_Start(const upb_EnumReservedRange* r);
int32_t upb_EnumReservedRange_End(const upb_EnumReservedRange* r);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
