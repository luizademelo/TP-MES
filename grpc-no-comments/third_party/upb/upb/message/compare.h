
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_COMPARE_H_
#define UPB_MESSAGE_COMPARE_H_

#include <stddef.h>

#include "upb/base/descriptor_constants.h"
#include "upb/message/message.h"
#include "upb/message/value.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

enum {

  kUpb_CompareOption_IncludeUnknownFields = (1 << 0)
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API bool upb_Message_IsEmpty(const upb_Message* msg,
                                 const upb_MiniTable* m);

UPB_API bool upb_Message_IsEqual(const upb_Message* msg1,
                                 const upb_Message* msg2,
                                 const upb_MiniTable* m, int options);

UPB_API_INLINE bool upb_MessageValue_IsEqual(upb_MessageValue val1,
                                             upb_MessageValue val2,
                                             upb_CType ctype,
                                             const upb_MiniTable* m,
                                             int options) {
  switch (ctype) {
    case kUpb_CType_Bool:
      return val1.bool_val == val2.bool_val;

    case kUpb_CType_Float:
    case kUpb_CType_Int32:
    case kUpb_CType_UInt32:
    case kUpb_CType_Enum:
      return val1.int32_val == val2.int32_val;

    case kUpb_CType_Double:
    case kUpb_CType_Int64:
    case kUpb_CType_UInt64:
      return val1.int64_val == val2.int64_val;

    case kUpb_CType_String:
    case kUpb_CType_Bytes:
      return upb_StringView_IsEqual(val1.str_val, val2.str_val);

    case kUpb_CType_Message:
      return upb_Message_IsEqual(val1.msg_val, val2.msg_val, m, options);

    default:
      UPB_UNREACHABLE();
      return false;
  }
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
