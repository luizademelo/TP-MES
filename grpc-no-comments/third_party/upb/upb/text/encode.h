
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_TEXT_ENCODE_H_
#define UPB_TEXT_ENCODE_H_

#include "upb/reflection/def.h"
#include "upb/text/options.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

size_t upb_TextEncode(const upb_Message* msg, const upb_MessageDef* m,
                      const upb_DefPool* ext_pool, int options, char* buf,
                      size_t size);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
