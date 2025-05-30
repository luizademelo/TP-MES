
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_MESSAGE_RESERVED_RANGE_H_
#define UPB_REFLECTION_MESSAGE_RESERVED_RANGE_H_

#include "upb/reflection/common.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

int32_t upb_MessageReservedRange_Start(const upb_MessageReservedRange* r);
int32_t upb_MessageReservedRange_End(const upb_MessageReservedRange* r);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
