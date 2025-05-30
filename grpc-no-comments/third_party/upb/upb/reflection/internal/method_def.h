
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_METHOD_DEF_INTERNAL_H_
#define UPB_REFLECTION_METHOD_DEF_INTERNAL_H_

#include "upb/reflection/method_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_MethodDef* _upb_MethodDef_At(const upb_MethodDef* m, int i);

upb_MethodDef* _upb_MethodDefs_New(upb_DefBuilder* ctx, int n,
                                   const UPB_DESC(MethodDescriptorProto*)
                                       const* protos,
                                   const UPB_DESC(FeatureSet*) parent_features,
                                   upb_ServiceDef* s);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
