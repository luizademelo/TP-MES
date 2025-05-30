
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_FIELD_DEF_INTERNAL_H_
#define UPB_REFLECTION_FIELD_DEF_INTERNAL_H_

#include "upb/reflection/field_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_FieldDef* _upb_FieldDef_At(const upb_FieldDef* f, int i);

bool _upb_FieldDef_IsClosedEnum(const upb_FieldDef* f);
bool _upb_FieldDef_IsProto3Optional(const upb_FieldDef* f);
int _upb_FieldDef_LayoutIndex(const upb_FieldDef* f);
uint64_t _upb_FieldDef_Modifiers(const upb_FieldDef* f);
void _upb_FieldDef_Resolve(upb_DefBuilder* ctx, const char* prefix,
                           upb_FieldDef* f);
void _upb_FieldDef_BuildMiniTableExtension(upb_DefBuilder* ctx,
                                           const upb_FieldDef* f);

upb_FieldDef* _upb_Extensions_New(upb_DefBuilder* ctx, int n,
                                  const UPB_DESC(FieldDescriptorProto*)
                                      const* protos,
                                  const UPB_DESC(FeatureSet*) parent_features,
                                  const char* prefix, upb_MessageDef* m);

upb_FieldDef* _upb_FieldDefs_New(upb_DefBuilder* ctx, int n,
                                 const UPB_DESC(FieldDescriptorProto*)
                                     const* protos,
                                 const UPB_DESC(FeatureSet*) parent_features,
                                 const char* prefix, upb_MessageDef* m,
                                 bool* is_sorted);

const upb_FieldDef** _upb_FieldDefs_Sorted(const upb_FieldDef* f, int n,
                                           upb_Arena* a);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
