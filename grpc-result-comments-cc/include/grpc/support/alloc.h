Here's the commented version of the code:

```c++
/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPC_SUPPORT_ALLOC_H
#define GRPC_SUPPORT_ALLOC_H

#include <grpc/support/port_platform.h>  // Platform-specific configuration
#include <stddef.h>                     // For size_t definition

#ifdef __cplusplus
extern "C" {  // Ensure C linkage when included in C++ programs
#endif

// Allocates a block of memory of given size.
// Returns a pointer to the allocated memory or NULL on failure.
GPRAPI void* gpr_malloc(size_t size);

// Allocates a block of memory of given size and initializes it to zero.
// Returns a pointer to the allocated memory or NULL on failure.
GPRAPI void* gpr_zalloc(size_t size);

// Frees memory previously allocated by gpr_malloc, gpr_zalloc, or gpr_realloc.
GPRAPI void gpr_free(void* ptr);

// Reallocates memory block pointed by 'p' to new 'size'.
// If 'p' is NULL, equivalent to gpr_malloc.
// If 'size' is 0, equivalent to gpr_free.
// Returns a pointer to the reallocated memory or NULL on failure.
GPRAPI void* gpr_realloc(void* p, size_t size);

// Allocates memory aligned to specified boundary.
// Parameters:
//   size - number of bytes to allocate
//   alignment - alignment boundary (must be power of 2)
// Returns a pointer to the allocated memory or NULL on failure.
GPRAPI void* gpr_malloc_aligned(size_t size, size_t alignment);

// Frees memory previously allocated by gpr_malloc_aligned.
GPRAPI void gpr_free_aligned(void* ptr);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // GRPC_SUPPORT_ALLOC_H
```

The comments added:
1. Explained the purpose of each memory allocation function
2. Documented the parameters and return values
3. Noted special cases for gpr_realloc (NULL pointer and zero size)
4. Added requirements for alignment parameter in gpr_malloc_aligned
5. Explained the extern "C" wrapper for C++ compatibility
6. Added brief comments for the include statements
7. Maintained all original copyright and license information

The comments follow standard documentation practices for C/C++ headers, making it clear how to use each function and what to expect from them.