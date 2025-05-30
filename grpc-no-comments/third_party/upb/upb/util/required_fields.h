
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_UTIL_REQUIRED_FIELDS_H_
#define UPB_UTIL_REQUIRED_FIELDS_H_

#include <stddef.h>

#include "upb/reflection/def.h"
#include "upb/reflection/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
  const upb_FieldDef* field;
  size_t array_index;
  upb_MessageValue map_key;
} upb_FieldPathEntry;

size_t upb_FieldPath_ToText(upb_FieldPathEntry** path, char* buf, size_t size);

bool upb_util_HasUnsetRequired(const upb_Message* msg, const upb_MessageDef* m,
                               const upb_DefPool* ext_pool,
                               upb_FieldPathEntry** fields);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
