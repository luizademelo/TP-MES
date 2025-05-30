
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_SERVICE_DEF_INTERNAL_H_
#define UPB_REFLECTION_SERVICE_DEF_INTERNAL_H_

#include "upb/reflection/service_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_ServiceDef* _upb_ServiceDef_At(const upb_ServiceDef* s, int i);

upb_ServiceDef* _upb_ServiceDefs_New(upb_DefBuilder* ctx, int n,
                                     const UPB_DESC(ServiceDescriptorProto*)
                                         const* protos,
                                     const UPB_DESC(FeatureSet*)
                                         parent_features);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
