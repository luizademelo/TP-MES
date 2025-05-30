
// Copyright 2024 Google LLC.  All rights reserved.

#ifndef UPB_WIRE_BYTE_SIZE_H_
#define UPB_WIRE_BYTE_SIZE_H_

#include <stddef.h>

#include "upb/message/message.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_API size_t upb_ByteSize(const upb_Message* msg, const upb_MiniTable* mt);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
