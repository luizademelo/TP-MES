
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_LEX_ATOI_H_
#define UPB_LEX_ATOI_H_

#include <stdint.h>

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

const char* upb_BufToUint64(const char* ptr, const char* end, uint64_t* val);
const char* upb_BufToInt64(const char* ptr, const char* end, int64_t* val,
                           bool* is_neg);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
