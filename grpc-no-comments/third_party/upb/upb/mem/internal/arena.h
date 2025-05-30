
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MEM_INTERNAL_ARENA_H_
#define UPB_MEM_INTERNAL_ARENA_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "upb/port/def.inc"

#define UPB_ARENA_SIZE_HACK (9 + UPB_TSAN_PUBLISH)

struct upb_Arena {
  char* UPB_ONLYBITS(ptr);
  char* UPB_ONLYBITS(end);
};

#ifdef __cplusplus
extern "C" {
#endif

void UPB_PRIVATE(_upb_Arena_SwapIn)(struct upb_Arena* des,
                                    const struct upb_Arena* src);
void UPB_PRIVATE(_upb_Arena_SwapOut)(struct upb_Arena* des,
                                     const struct upb_Arena* src);

UPB_INLINE size_t UPB_PRIVATE(_upb_ArenaHas)(const struct upb_Arena* a) {
  return (size_t)(a->UPB_ONLYBITS(end) - a->UPB_ONLYBITS(ptr));
}

UPB_API_INLINE void* upb_Arena_Malloc(struct upb_Arena* a, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  void* UPB_PRIVATE(_upb_Arena_SlowMalloc)(struct upb_Arena * a, size_t size);

  size = UPB_ALIGN_MALLOC(size);
  const size_t span = size + UPB_ASAN_GUARD_SIZE;
  if (UPB_UNLIKELY(UPB_PRIVATE(_upb_ArenaHas)(a) < span)) {
    return UPB_PRIVATE(_upb_Arena_SlowMalloc)(a, span);
  }

  void* ret = a->UPB_ONLYBITS(ptr);
  UPB_ASSERT(UPB_ALIGN_MALLOC((uintptr_t)ret) == (uintptr_t)ret);
  UPB_ASSERT(UPB_ALIGN_MALLOC(size) == size);
  UPB_UNPOISON_MEMORY_REGION(ret, size);

  a->UPB_ONLYBITS(ptr) += span;

  return ret;
}

UPB_API_INLINE void upb_Arena_ShrinkLast(struct upb_Arena* a, void* ptr,
                                         size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  UPB_ASSERT(ptr);
  UPB_ASSERT(size <= oldsize);
  size = UPB_ALIGN_MALLOC(size) + UPB_ASAN_GUARD_SIZE;
  oldsize = UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE;
  if (size == oldsize) {
    return;
  }
  char* arena_ptr = a->UPB_ONLYBITS(ptr);

  if ((char*)ptr + oldsize == arena_ptr) {
    a->UPB_ONLYBITS(ptr) = (char*)ptr + size;
  } else {

#ifndef NDEBUG
    bool _upb_Arena_WasLastAlloc(struct upb_Arena * a, void* ptr,
                                 size_t oldsize);
    UPB_ASSERT(_upb_Arena_WasLastAlloc(a, ptr, oldsize));
#endif
  }
  UPB_POISON_MEMORY_REGION((char*)ptr + (size - UPB_ASAN_GUARD_SIZE),
                           oldsize - size);
}

UPB_API_INLINE bool upb_Arena_TryExtend(struct upb_Arena* a, void* ptr,
                                        size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  UPB_ASSERT(ptr);
  UPB_ASSERT(size > oldsize);
  size = UPB_ALIGN_MALLOC(size) + UPB_ASAN_GUARD_SIZE;
  oldsize = UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE;
  if (size == oldsize) {
    return true;
  }
  size_t extend = size - oldsize;
  if ((char*)ptr + oldsize == a->UPB_ONLYBITS(ptr) &&
      UPB_PRIVATE(_upb_ArenaHas)(a) >= extend) {
    a->UPB_ONLYBITS(ptr) += extend;
    UPB_UNPOISON_MEMORY_REGION((char*)ptr + (oldsize - UPB_ASAN_GUARD_SIZE),
                               extend);
    return true;
  }
  return false;
}

UPB_API_INLINE void* upb_Arena_Realloc(struct upb_Arena* a, void* ptr,
                                       size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  if (ptr) {
    if (size == oldsize) {
      return ptr;
    }
    if (size > oldsize) {
      if (upb_Arena_TryExtend(a, ptr, oldsize, size)) return ptr;
    } else {
      if ((char*)ptr + (UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE) ==
          a->UPB_ONLYBITS(ptr)) {
        upb_Arena_ShrinkLast(a, ptr, oldsize, size);
      } else {
        UPB_POISON_MEMORY_REGION((char*)ptr + size, oldsize - size);
      }
      return ptr;
    }
  }
  void* ret = upb_Arena_Malloc(a, size);

  if (ret && oldsize > 0) {
    memcpy(ret, ptr, UPB_MIN(oldsize, size));
    UPB_POISON_MEMORY_REGION(ptr, oldsize);
  }

  return ret;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif
