
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_DESCRIPTOR_BUILD_ENUM_H_
#define UPB_MINI_DESCRIPTOR_BUILD_ENUM_H_

#include "upb/base/status.h"
#include "upb/mem/arena.h"
#include "upb/mini_table/enum.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_MiniTableEnum* upb_MiniTableEnum_Build(const char* data, size_t len,
                                                   upb_Arena* arena,
                                                   upb_Status* status);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
