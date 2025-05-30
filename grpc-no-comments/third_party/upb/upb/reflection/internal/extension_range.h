
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_EXTENSION_RANGE_INTERNAL_H_
#define UPB_REFLECTION_EXTENSION_RANGE_INTERNAL_H_

#include "upb/reflection/extension_range.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_ExtensionRange* _upb_ExtensionRange_At(const upb_ExtensionRange* r, int i);

upb_ExtensionRange* _upb_ExtensionRanges_New(
    upb_DefBuilder* ctx, int n,
    const UPB_DESC(DescriptorProto_ExtensionRange*) const* protos,
    const UPB_DESC(FeatureSet*) parent_features, const upb_MessageDef* m);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
