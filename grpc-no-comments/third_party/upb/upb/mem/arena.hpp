
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_MEM_ARENA_HPP_
#define UPB_MEM_ARENA_HPP_

#include "upb/mem/alloc.h"
#ifdef __cplusplus

#include <cstddef>
#include <memory>

#include "upb/mem/arena.h"

namespace upb {

class Arena {
 public:

  Arena() : ptr_(upb_Arena_New(), upb_Arena_Free) {}
  Arena(char* initial_block, size_t size)
      : ptr_(upb_Arena_Init(initial_block, size, &upb_alloc_global),
             upb_Arena_Free) {}
  explicit Arena(size_t size)
      : ptr_(upb_Arena_NewSized(size), upb_Arena_Free) {}

  upb_Arena* ptr() const { return ptr_.get(); }

  bool Fuse(Arena& other) { return upb_Arena_Fuse(ptr(), other.ptr()); }

 protected:
  std::unique_ptr<upb_Arena, decltype(&upb_Arena_Free)> ptr_;
};
}

#endif

#endif
