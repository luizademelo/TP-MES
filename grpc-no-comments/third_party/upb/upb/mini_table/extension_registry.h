
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MINI_TABLE_EXTENSION_REGISTRY_H_
#define UPB_MINI_TABLE_EXTENSION_REGISTRY_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/mem/arena.h"
#include "upb/mini_table/extension.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct upb_ExtensionRegistry upb_ExtensionRegistry;

typedef enum {
  kUpb_ExtensionRegistryStatus_Ok = 0,
  kUpb_ExtensionRegistryStatus_DuplicateEntry = 1,
  kUpb_ExtensionRegistryStatus_OutOfMemory = 2,
} upb_ExtensionRegistryStatus;

UPB_API upb_ExtensionRegistry* upb_ExtensionRegistry_New(upb_Arena* arena);

UPB_API upb_ExtensionRegistryStatus upb_ExtensionRegistry_Add(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension* e);

upb_ExtensionRegistryStatus upb_ExtensionRegistry_AddArray(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension** e, size_t count);

#ifdef UPB_LINKARR_DECLARE

UPB_API bool upb_ExtensionRegistry_AddAllLinkedExtensions(
    upb_ExtensionRegistry* r);

#endif

UPB_API const upb_MiniTableExtension* upb_ExtensionRegistry_Lookup(
    const upb_ExtensionRegistry* r, const upb_MiniTable* t, uint32_t num);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
