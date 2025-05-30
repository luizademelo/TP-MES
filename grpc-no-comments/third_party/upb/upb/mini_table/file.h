
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_FILE_H_
#define UPB_MINI_TABLE_FILE_H_

#include "upb/mini_table/enum.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/internal/file.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

typedef struct upb_MiniTableFile upb_MiniTableFile;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableFile_Enum(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_EnumCount(const upb_MiniTableFile* f);

UPB_API_INLINE const upb_MiniTableExtension* upb_MiniTableFile_Extension(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_ExtensionCount(const upb_MiniTableFile* f);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableFile_Message(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_MessageCount(const upb_MiniTableFile* f);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
