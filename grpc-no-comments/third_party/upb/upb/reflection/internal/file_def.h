
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_REFLECTION_FILE_DEF_INTERNAL_H_
#define UPB_REFLECTION_FILE_DEF_INTERNAL_H_

#include "upb/reflection/file_def.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

const upb_MiniTableExtension* _upb_FileDef_ExtensionMiniTable(
    const upb_FileDef* f, int i);
const int32_t* _upb_FileDef_PublicDependencyIndexes(const upb_FileDef* f);
const int32_t* _upb_FileDef_WeakDependencyIndexes(const upb_FileDef* f);

const char* _upb_FileDef_RawPackage(const upb_FileDef* f);

void _upb_FileDef_Create(upb_DefBuilder* ctx,
                         const UPB_DESC(FileDescriptorProto) * file_proto);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
