
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_DECODE_H_
#define UPB_MINI_TABLE_DECODE_H_

#include "upb/base/status.h"
#include "upb/mem/arena.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/sub.h"

#include "upb/mini_descriptor/build_enum.h"
#include "upb/mini_descriptor/link.h"

#include "upb/port/def.inc"

typedef enum {
  kUpb_MiniTablePlatform_32Bit,
  kUpb_MiniTablePlatform_64Bit,
  kUpb_MiniTablePlatform_Native =
      UPB_SIZE(kUpb_MiniTablePlatform_32Bit, kUpb_MiniTablePlatform_64Bit),
} upb_MiniTablePlatform;

#ifdef __cplusplus
extern "C" {
#endif

upb_MiniTable* _upb_MiniTable_Build(const char* data, size_t len,
                                    upb_MiniTablePlatform platform,
                                    upb_Arena* arena, upb_Status* status);

UPB_API_INLINE upb_MiniTable* upb_MiniTable_Build(const char* data, size_t len,
                                                  upb_Arena* arena,
                                                  upb_Status* status) {
  return _upb_MiniTable_Build(data, len, kUpb_MiniTablePlatform_Native, arena,
                              status);
}

const char* _upb_MiniTableExtension_Init(const char* data, size_t len,
                                         upb_MiniTableExtension* ext,
                                         const upb_MiniTable* extendee,
                                         upb_MiniTableSub sub,
                                         upb_MiniTablePlatform platform,
                                         upb_Status* status);

UPB_API_INLINE const char* upb_MiniTableExtension_Init(
    const char* data, size_t len, upb_MiniTableExtension* ext,
    const upb_MiniTable* extendee, upb_MiniTableSub sub, upb_Status* status) {
  return _upb_MiniTableExtension_Init(data, len, ext, extendee, sub,
                                      kUpb_MiniTablePlatform_Native, status);
}

UPB_API upb_MiniTableExtension* _upb_MiniTableExtension_Build(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_MiniTableSub sub, upb_MiniTablePlatform platform, upb_Arena* arena,
    upb_Status* status);

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_Build(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromMessage(NULL);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_BuildMessage(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_MiniTable* submsg, upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromMessage(submsg);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_BuildEnum(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_MiniTableEnum* subenum, upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromEnum(subenum);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

upb_MiniTable* upb_MiniTable_BuildWithBuf(const char* data, size_t len,
                                          upb_MiniTablePlatform platform,
                                          upb_Arena* arena, void** buf,
                                          size_t* buf_size, upb_Status* status);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
