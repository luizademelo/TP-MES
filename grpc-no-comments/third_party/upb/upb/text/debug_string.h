
// Copyright 2024 Google LLC.  All rights reserved.

#ifndef UPB_TEXT_ENCODE_DEBUG_H_
#define UPB_TEXT_ENCODE_DEBUG_H_

#include <stddef.h>

#include "upb/message/message.h"
#include "upb/mini_table/message.h"
#include "upb/text/options.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_API size_t upb_DebugString(const upb_Message* msg, const upb_MiniTable* mt,
                               int options, char* buf, size_t size);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
