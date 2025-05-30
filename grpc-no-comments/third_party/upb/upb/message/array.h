
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MESSAGE_ARRAY_H_
#define UPB_MESSAGE_ARRAY_H_

#include <stddef.h>

#include "upb/base/descriptor_constants.h"
#include "upb/mem/arena.h"
#include "upb/message/internal/array.h"
#include "upb/message/internal/types.h"
#include "upb/message/value.h"
#include "upb/mini_table/message.h"

#include "upb/port/def.inc"

typedef struct upb_Array upb_Array;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_Array* upb_Array_New(upb_Arena* a, upb_CType type);

UPB_API_INLINE size_t upb_Array_Size(const upb_Array* arr);

UPB_API upb_MessageValue upb_Array_Get(const upb_Array* arr, size_t i);

UPB_API struct upb_Message* upb_Array_GetMutable(upb_Array* arr, size_t i);

UPB_API void upb_Array_Set(upb_Array* arr, size_t i, upb_MessageValue val);

UPB_API bool upb_Array_Append(upb_Array* array, upb_MessageValue val,
                              upb_Arena* arena);

UPB_API void upb_Array_Move(upb_Array* array, size_t dst_idx, size_t src_idx,
                            size_t count);

UPB_API bool upb_Array_Insert(upb_Array* array, size_t i, size_t count,
                              upb_Arena* arena);

UPB_API void upb_Array_Delete(upb_Array* array, size_t i, size_t count);

UPB_API_INLINE bool upb_Array_Reserve(struct upb_Array* array, size_t size,
                                      upb_Arena* arena);

UPB_API bool upb_Array_Resize(upb_Array* array, size_t size, upb_Arena* arena);

UPB_API_INLINE const void* upb_Array_DataPtr(const upb_Array* arr);

UPB_API_INLINE void* upb_Array_MutableDataPtr(upb_Array* arr);

UPB_API void upb_Array_Freeze(upb_Array* arr, const upb_MiniTable* m);

UPB_API_INLINE bool upb_Array_IsFrozen(const upb_Array* arr);

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
