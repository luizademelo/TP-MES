
// Copyright 2024 Google LLC.  All rights reserved.

#ifndef GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__
#define GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__

#include <stddef.h>
#include <stdint.h>

#include "upb/message/message.h"
#include "upb/message/value.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#define kUpb_BaseField_Begin ((size_t)-1)
bool UPB_PRIVATE(_upb_Message_NextBaseField)(const upb_Message* msg,
                                             const upb_MiniTable* m,
                                             const upb_MiniTableField** out_f,
                                             upb_MessageValue* out_v,
                                             uintptr_t* iter);

#endif
