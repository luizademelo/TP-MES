
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_LEX_STRTOD_H_
#define UPB_LEX_STRTOD_H_

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

double _upb_NoLocaleStrtod(const char *str, char **endptr);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
