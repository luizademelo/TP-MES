
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_MESSAGE_RESERVED_RANGE_INTERNAL_H_
#define UPB_REFLECTION_MESSAGE_RESERVED_RANGE_INTERNAL_H_

#include "upb/reflection/message_reserved_range.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

upb_MessageReservedRange* _upb_MessageReservedRange_At(
    const upb_MessageReservedRange* r, int i);

upb_MessageReservedRange* _upb_MessageReservedRanges_New(
    upb_DefBuilder* ctx, int n,
    const UPB_DESC(DescriptorProto_ReservedRange) * const* protos,
    const upb_MessageDef* m);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
