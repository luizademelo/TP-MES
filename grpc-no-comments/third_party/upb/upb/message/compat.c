
// Copyright 2023 Google LLC.  All rights reserved.

#include "upb/message/compat.h"

#include <stddef.h>
#include <stdint.h>

#include "upb/message/message.h"
#include "upb/message/value.h"
#include "upb/mini_table/extension.h"

#include "upb/port/def.inc"

bool upb_Message_NextExtensionReverse(const upb_Message* msg,
                                      const upb_MiniTableExtension** result,
                                      uintptr_t* iter) {
  upb_MessageValue val;
  return UPB_PRIVATE(_upb_Message_NextExtensionReverse)(msg, result, &val,
                                                        iter);
}

const upb_MiniTableExtension* upb_Message_FindExtensionByNumber(
    const upb_Message* msg, uint32_t field_number) {
  uintptr_t iter = kUpb_Message_ExtensionBegin;
  const upb_MiniTableExtension* result;
  while (upb_Message_NextExtensionReverse(msg, &result, &iter)) {
    if (upb_MiniTableExtension_Number(result) == field_number) return result;
  }
  return NULL;
}
