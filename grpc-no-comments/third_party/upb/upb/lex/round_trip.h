
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_LEX_ROUND_TRIP_H_
#define UPB_LEX_ROUND_TRIP_H_

#include "upb/port/def.inc"

enum { kUpb_RoundTripBufferSize = 32 };

#ifdef __cplusplus
extern "C" {
#endif

void _upb_EncodeRoundTripDouble(double val, char* buf, size_t size);
void _upb_EncodeRoundTripFloat(float val, char* buf, size_t size);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
