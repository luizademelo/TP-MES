
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_ENUM_DEF_INTERNAL_H_
#define UPB_REFLECTION_ENUM_DEF_INTERNAL_H_

#include "upb/reflection/enum_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_EnumDef* _upb_EnumDef_At(const upb_EnumDef* e, int i);
bool _upb_EnumDef_Insert(upb_EnumDef* e, upb_EnumValueDef* v, upb_Arena* a);
const upb_MiniTableEnum* _upb_EnumDef_MiniTable(const upb_EnumDef* e);

upb_EnumDef* _upb_EnumDefs_New(upb_DefBuilder* ctx, int n,
                               const UPB_DESC(EnumDescriptorProto*)
                                   const* protos,
                               const UPB_DESC(FeatureSet*) parent_features,
                               const upb_MessageDef* containing_type);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
