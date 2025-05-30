
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_COMPAT_H_
#define UPB_MESSAGE_COMPAT_H_

#include <stdint.h>

#include "upb/message/message.h"
#include "upb/mini_table/extension.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

bool upb_Message_NextExtensionReverse(const upb_Message* msg,
                                      const upb_MiniTableExtension** result,
                                      uintptr_t* iter);

const upb_MiniTableExtension* upb_Message_FindExtensionByNumber(
    const upb_Message* msg, uint32_t field_number);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
