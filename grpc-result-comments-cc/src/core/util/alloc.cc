Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdlib.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/util/crash.h"

// Allocates memory of given size using malloc.
// Returns nullptr if size is 0.
// Aborts the program if memory allocation fails.
void* gpr_malloc(size_t size) {
  void* p;
  if (size == 0) return nullptr;
  p = malloc(size);
  if (!p) {
    abort();  // Crash on allocation failure
  }
  return p;
}

// Allocates zero-initialized memory of given size using calloc.
// Returns nullptr if size is 0.
// Aborts the program if memory allocation fails.
void* gpr_zalloc(size_t size) {
  void* p;
  if (size == 0) return nullptr;
  p = calloc(size, 1);  // Allocate and zero memory
  if (!p) {
    abort();  // Crash on allocation failure
  }
  return p;
}

// Frees memory allocated by gpr_malloc, gpr_zalloc, or gpr_realloc.
void gpr_free(void* p) { free(p); }

// Reallocates memory to new size.
// Handles special case where both size is 0 and pointer is nullptr.
// Aborts the program if reallocation fails.
void* gpr_realloc(void* p, size_t size) {
  if ((size == 0) && (p == nullptr)) return nullptr;

  p = realloc(p, size);
  if (!p) {
    abort();  // Crash on reallocation failure
  }
  return p;
}

// Allocates memory aligned to specified boundary.
// Alignment must be a power of two (checked by CHECK_EQ).
// Returns pointer to aligned memory block.
// Stores original allocation pointer before aligned block for proper deallocation.
void* gpr_malloc_aligned(size_t size, size_t alignment) {
  // Verify alignment is power of two
  CHECK_EQ(((alignment - 1) & alignment), 0u);
  // Calculate extra space needed for alignment and storing original pointer
  size_t extra = alignment - 1 + sizeof(void*);
  // Allocate required memory plus extra space
  void* p = gpr_malloc(size + extra);
  // Calculate aligned address and store original pointer
  void** ret = reinterpret_cast<void**>(
      (reinterpret_cast<uintptr_t>(p) + extra) & ~(alignment - 1));
  ret[-1] = p;  // Store original pointer before aligned block
  return ret;
}

// Frees memory allocated by gpr_malloc_aligned.
// Retrieves original allocation pointer stored before aligned block.
void gpr_free_aligned(void* ptr) { gpr_free((static_cast<void**>(ptr))[-1]); }
```

The comments explain:
1. Each function's purpose and behavior
2. Special cases and edge conditions
3. Memory management details
4. Safety checks and abort conditions
5. Implementation details for aligned allocation
6. The relationship between allocation and deallocation functions

The comments are concise yet comprehensive, providing enough information for maintenance while not being overly verbose. They follow the style of explaining what the code does rather than just repeating what the code shows.