
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_ENUM_VALUE_DEF_INTERNAL_H_
#define UPB_REFLECTION_ENUM_VALUE_DEF_INTERNAL_H_

#include "upb/reflection/enum_value_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_EnumValueDef* _upb_EnumValueDef_At(const upb_EnumValueDef* v, int i);

upb_EnumValueDef* _upb_EnumValueDefs_New(
    upb_DefBuilder* ctx, const char* prefix, int n,
    const UPB_DESC(EnumValueDescriptorProto*) const* protos,
    const UPB_DESC(FeatureSet*) parent_features, upb_EnumDef* e,
    bool* is_sorted);

const upb_EnumValueDef** _upb_EnumValueDefs_Sorted(const upb_EnumValueDef* v,
                                                   size_t n, upb_Arena* a);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
