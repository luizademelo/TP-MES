
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_JSON_ENCODE_H_
#define UPB_JSON_ENCODE_H_

#include "upb/reflection/def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

enum {

  upb_JsonEncode_EmitDefaults = 1 << 0,

  upb_JsonEncode_UseProtoNames = 1 << 1,

  upb_JsonEncode_FormatEnumsAsIntegers = 1 << 2
};

UPB_API size_t upb_JsonEncode(const upb_Message* msg, const upb_MessageDef* m,
                              const upb_DefPool* ext_pool, int options,
                              char* buf, size_t size, upb_Status* status);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
