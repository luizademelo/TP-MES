
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_ENUM_RESERVED_RANGE_INTERNAL_H_
#define UPB_REFLECTION_ENUM_RESERVED_RANGE_INTERNAL_H_

#include "upb/reflection/enum_reserved_range.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_EnumReservedRange* _upb_EnumReservedRange_At(const upb_EnumReservedRange* r,
                                                 int i);

upb_EnumReservedRange* _upb_EnumReservedRanges_New(
    upb_DefBuilder* ctx, int n,
    const UPB_DESC(EnumDescriptorProto_EnumReservedRange*) const* protos,
    const upb_EnumDef* e);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
