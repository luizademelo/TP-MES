
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_INTERNAL_STRDUP2_H_
#define UPB_REFLECTION_INTERNAL_STRDUP2_H_

#include <stddef.h>

#include "upb/mem/arena.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

char* upb_strdup2(const char* s, size_t len, upb_Arena* a);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
