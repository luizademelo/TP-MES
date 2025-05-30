
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MEM_ARENA_H_
#define UPB_MEM_ARENA_H_

#include <stddef.h>
#include <stdint.h>

#include "upb/mem/alloc.h"
#include "upb/mem/internal/arena.h"

#include "upb/port/def.inc"

typedef struct upb_Arena upb_Arena;

typedef void upb_AllocCleanupFunc(upb_alloc* alloc);

#ifdef __cplusplus
extern "C" {
#endif

UPB_API upb_Arena* upb_Arena_Init(void* mem, size_t n, upb_alloc* alloc);

UPB_API void upb_Arena_Free(upb_Arena* a);

UPB_API void upb_Arena_SetAllocCleanup(upb_Arena* a,
                                       upb_AllocCleanupFunc* func);

UPB_API bool upb_Arena_Fuse(const upb_Arena* a, const upb_Arena* b);

UPB_API bool upb_Arena_IsFused(const upb_Arena* a, const upb_Arena* b);

UPB_API upb_alloc* upb_Arena_GetUpbAlloc(upb_Arena* a);

bool upb_Arena_IncRefFor(const upb_Arena* a, const void* owner);

void upb_Arena_DecRefFor(const upb_Arena* a, const void* owner);

uintptr_t upb_Arena_SpaceAllocated(const upb_Arena* a, size_t* fused_count);

uint32_t upb_Arena_DebugRefCount(const upb_Arena* a);

UPB_API_INLINE upb_Arena* upb_Arena_New(void) {
  return upb_Arena_Init(NULL, 0, &upb_alloc_global);
}

UPB_API_INLINE upb_Arena* upb_Arena_NewSized(size_t size_hint) {
  return upb_Arena_Init(NULL, size_hint, &upb_alloc_global);
}

UPB_API_INLINE void* upb_Arena_Malloc(struct upb_Arena* a, size_t size);

UPB_API_INLINE void* upb_Arena_Realloc(upb_Arena* a, void* ptr, size_t oldsize,
                                       size_t size);

static const size_t UPB_PRIVATE(kUpbDefaultMaxBlockSize) =
    UPB_DEFAULT_MAX_BLOCK_SIZE;

void upb_Arena_SetMaxBlockSize(size_t max);

UPB_API_INLINE void upb_Arena_ShrinkLast(upb_Arena* a, void* ptr,
                                         size_t oldsize, size_t size);

UPB_API_INLINE bool upb_Arena_TryExtend(upb_Arena* a, void* ptr, size_t oldsize,
                                        size_t size);

#ifdef UPB_TRACING_ENABLED
void upb_Arena_SetTraceHandler(void (*initArenaTraceHandler)(const upb_Arena*,
                                                             size_t size),
                               void (*fuseArenaTraceHandler)(const upb_Arena*,
                                                             const upb_Arena*),
                               void (*freeArenaTraceHandler)(const upb_Arena*));
#endif

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
