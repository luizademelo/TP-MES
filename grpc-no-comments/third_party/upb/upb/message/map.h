
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_MAP_H_
#define UPB_MESSAGE_MAP_H_

#include <stddef.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mem/arena.h"
#include "upb/message/internal/map.h"
#include "upb/message/internal/types.h"
#include "upb/message/value.h"
#include "upb/mini_table/field.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

typedef struct upb_Map upb_Map;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_Map* upb_Map_New(upb_Arena* a, upb_CType key_type,
                             upb_CType value_type);

UPB_API size_t upb_Map_Size(const upb_Map* map);

UPB_API bool upb_Map_Get(const upb_Map* map, upb_MessageValue key,
                         upb_MessageValue* val);

UPB_API struct upb_Message* upb_Map_GetMutable(upb_Map* map,
                                               upb_MessageValue key);

UPB_API void upb_Map_Clear(upb_Map* map);

UPB_API upb_MapInsertStatus upb_Map_Insert(upb_Map* map, upb_MessageValue key,
                                           upb_MessageValue val,
                                           upb_Arena* arena);

UPB_API_INLINE bool upb_Map_Set(upb_Map* map, upb_MessageValue key,
                                upb_MessageValue val, upb_Arena* arena) {
  return upb_Map_Insert(map, key, val, arena) !=
         kUpb_MapInsertStatus_OutOfMemory;
}

UPB_API bool upb_Map_Delete(upb_Map* map, upb_MessageValue key,
                            upb_MessageValue* val);

#define kUpb_Map_Begin ((size_t)-1)

UPB_API bool upb_Map_Next(const upb_Map* map, upb_MessageValue* key,
                          upb_MessageValue* val, size_t* iter);

UPB_API void upb_Map_SetEntryValue(upb_Map* map, size_t iter,
                                   upb_MessageValue val);

UPB_API bool upb_MapIterator_Next(const upb_Map* map, size_t* iter);

UPB_API bool upb_MapIterator_Done(const upb_Map* map, size_t iter);

UPB_API upb_MessageValue upb_MapIterator_Key(const upb_Map* map, size_t iter);
UPB_API upb_MessageValue upb_MapIterator_Value(const upb_Map* map, size_t iter);

UPB_API void upb_Map_Freeze(upb_Map* map, const upb_MiniTable* m);

UPB_API_INLINE bool upb_Map_IsFrozen(const upb_Map* map);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
