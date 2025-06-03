Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MEM_INTERNAL_ARENA_H_
#define UPB_MEM_INTERNAL_ARENA_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "upb/port/def.inc"

// Define a constant for arena size adjustment that accounts for TSAN (Thread Sanitizer) overhead
#define UPB_ARENA_SIZE_HACK (9 + UPB_TSAN_PUBLISH)

// Structure representing a memory arena
// An arena is a region of memory used for efficient allocation and deallocation
struct upb_Arena {
  char* UPB_ONLYBITS(ptr);  // Current position (next available byte) in the arena
  char* UPB_ONLYBITS(end);  // End of the arena (one byte past last available byte)
};

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes for arena swapping operations
void UPB_PRIVATE(_upb_Arena_SwapIn)(struct upb_Arena* des,
                                    const struct upb_Arena* src);
void UPB_PRIVATE(_upb_Arena_SwapOut)(struct upb_Arena* des,
                                     const struct upb_Arena* src);

// Returns the amount of remaining space in the arena
UPB_INLINE size_t UPB_PRIVATE(_upb_ArenaHas)(const struct upb_Arena* a) {
  return (size_t)(a->UPB_ONLYBITS(end) - a->UPB_ONLYBITS(ptr));
}

// Allocates memory from the arena
UPB_API_INLINE void* upb_Arena_Malloc(struct upb_Arena* a, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));  // Thread sanitizer check
  void* UPB_PRIVATE(_upb_Arena_SlowMalloc)(struct upb_Arena * a, size_t size);

  // Align the requested size and add ASAN (Address Sanitizer) guard space
  size = UPB_ALIGN_MALLOC(size);
  const size_t span = size + UPB_ASAN_GUARD_SIZE;
  
  // If there's not enough space, fall back to slow path allocation
  if (UPB_UNLIKELY(UPB_PRIVATE(_upb_ArenaHas)(a) < span)) {
    return UPB_PRIVATE(_upb_Arena_SlowMalloc)(a, span);
  }

  // Get current position and verify alignment
  void* ret = a->UPB_ONLYBITS(ptr);
  UPB_ASSERT(UPB_ALIGN_MALLOC((uintptr_t)ret) == (uintptr_t)ret);
  UPB_ASSERT(UPB_ALIGN_MALLOC(size) == size);
  UPB_UNPOISON_MEMORY_REGION(ret, size);  // Mark memory as accessible for ASAN

  // Advance the pointer
  a->UPB_ONLYBITS(ptr) += span;

  return ret;
}

// Shrinks the last allocation in the arena
UPB_API_INLINE void upb_Arena_ShrinkLast(struct upb_Arena* a, void* ptr,
                                         size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  UPB_ASSERT(ptr);
  UPB_ASSERT(size <= oldsize);
  
  // Align sizes and add ASAN guard space
  size = UPB_ALIGN_MALLOC(size) + UPB_ASAN_GUARD_SIZE;
  oldsize = UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE;
  
  if (size == oldsize) {
    return;  // No change needed
  }
  
  char* arena_ptr = a->UPB_ONLYBITS(ptr);

  // If this was the most recent allocation, we can simply move the pointer back
  if ((char*)ptr + oldsize == arena_ptr) {
    a->UPB_ONLYBITS(ptr) = (char*)ptr + size;
  } else {
    // In debug mode, verify this was indeed the last allocation
#ifndef NDEBUG
    bool _upb_Arena_WasLastAlloc(struct upb_Arena * a, void* ptr,
                                 size_t oldsize);
    UPB_ASSERT(_upb_Arena_WasLastAlloc(a, ptr, oldsize));
#endif
  }
  
  // Mark the freed memory as poisoned for ASAN
  UPB_POISON_MEMORY_REGION((char*)ptr + (size - UPB_ASAN_GUARD_SIZE),
                           oldsize - size);
}

// Attempts to extend an existing allocation in the arena
UPB_API_INLINE bool upb_Arena_TryExtend(struct upb_Arena* a, void* ptr,
                                        size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  UPB_ASSERT(ptr);
  UPB_ASSERT(size > oldsize);
  
  // Align sizes and add ASAN guard space
  size = UPB_ALIGN_MALLOC(size) + UPB_ASAN_GUARD_SIZE;
  oldsize = UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE;
  
  if (size == oldsize) {
    return true;  // No actual extension needed
  }
  
  size_t extend = size - oldsize;
  
  // Check if this is the most recent allocation and there's enough space
  if ((char*)ptr + oldsize == a->UPB_ONLYBITS(ptr) &&
      UPB_PRIVATE(_upb_ArenaHas)(a) >= extend) {
    // Extend the allocation by moving the pointer
    a->UPB_ONLYBITS(ptr) += extend;
    UPB_UNPOISON_MEMORY_REGION((char*)ptr + (oldsize - UPB_ASAN_GUARD_SIZE),
                               extend);
    return true;
  }
  
  return false;  // Extension not possible
}

// Reallocates memory in the arena (similar to standard realloc)
UPB_API_INLINE void* upb_Arena_Realloc(struct upb_Arena* a, void* ptr,
                                       size_t oldsize, size_t size) {
  UPB_TSAN_CHECK_WRITE(a->UPB_ONLYBITS(ptr));
  if (ptr) {
    if (size == oldsize) {
      return ptr;  // No change needed
    }
    
    if (size > oldsize) {
      // Try to extend existing allocation
      if (upb_Arena_TryExtend(a, ptr, oldsize, size)) return ptr;
    } else {
      // Try to shrink existing allocation
      if ((char*)ptr + (UPB_ALIGN_MALLOC(oldsize) + UPB_ASAN_GUARD_SIZE) ==
          a->UPB_ONLYBITS(ptr)) {
        upb_Arena_ShrinkLast(a, ptr, oldsize, size);
      } else {
        // If not last allocation, just poison the unused portion
        UPB_POISON_MEMORY_REGION((char*)ptr + size, oldsize - size);
      }
      return ptr;
    }
  }
  
  // If we can't resize in place, allocate new memory and copy
  void* ret = upb_Arena_Malloc(a, size);

  if (ret && oldsize > 0) {
    memcpy(ret, ptr, UPB_MIN(oldsize, size));  // Copy old data
    UPB_POISON_MEMORY_REGION(ptr, oldsize);    // Mark old memory as poisoned
  }

  return ret;
}

#ifdef __cplusplus
}
#endif

#include "upb/port/undef.inc"

#endif  // UPB_MEM_INTERNAL_ARENA_H_
```