
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_EXTENSION_RANGE_H_
#define UPB_REFLECTION_EXTENSION_RANGE_H_

#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

int32_t upb_ExtensionRange_Start(const upb_ExtensionRange* r);
int32_t upb_ExtensionRange_End(const upb_ExtensionRange* r);

bool upb_ExtensionRange_HasOptions(const upb_ExtensionRange* r);
const UPB_DESC(ExtensionRangeOptions) *
    upb_ExtensionRange_Options(const upb_ExtensionRange* r);
const UPB_DESC(FeatureSet) *
    upb_ExtensionRange_ResolvedFeatures(const upb_ExtensionRange* e);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
