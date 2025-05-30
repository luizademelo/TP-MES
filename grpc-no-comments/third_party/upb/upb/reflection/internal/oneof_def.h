
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_ONEOF_DEF_INTERNAL_H_
#define UPB_REFLECTION_ONEOF_DEF_INTERNAL_H_

#include "upb/reflection/oneof_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_OneofDef* _upb_OneofDef_At(const upb_OneofDef* o, int i);
void _upb_OneofDef_Insert(upb_DefBuilder* ctx, upb_OneofDef* o,
                          const upb_FieldDef* f, const char* name, size_t size);

upb_OneofDef* _upb_OneofDefs_New(upb_DefBuilder* ctx, int n,
                                 const UPB_DESC(OneofDescriptorProto*)
                                     const* protos,
                                 const UPB_DESC(FeatureSet*) parent_features,
                                 upb_MessageDef* m);

size_t _upb_OneofDefs_Finalize(upb_DefBuilder* ctx, upb_MessageDef* m);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
