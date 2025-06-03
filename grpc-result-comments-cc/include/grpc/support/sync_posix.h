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

#ifndef GRPC_SUPPORT_SYNC_POSIX_H
#define GRPC_SUPPORT_SYNC_POSIX_H

// Include necessary headers
#include <grpc/support/port_platform.h>  // Platform-specific configuration
#include <grpc/support/sync_generic.h>   // Generic synchronization primitives
#include <pthread.h>                    // POSIX threads library

// Check if AddressSanitizer (ASAN) is enabled
#ifdef GRPC_ASAN_ENABLED

// When ASAN is enabled, wrap pthread primitives with leak checking
typedef struct {
  pthread_mutex_t mutex;  // POSIX mutex for thread synchronization
  int* leak_checker;      // Pointer for ASAN leak detection
} gpr_mu;

typedef struct {
  pthread_cond_t cond_var;  // POSIX condition variable for thread signaling
  int* leak_checker;        // Pointer for ASAN leak detection
} gpr_cv;

#else
// When ASAN is not enabled, use pthread types directly
typedef pthread_mutex_t gpr_mu;  // POSIX mutex type
typedef pthread_cond_t gpr_cv;   // POSIX condition variable type
#endif

// Type for one-time initialization (pthread_once_t wrapper)
typedef pthread_once_t gpr_once;

// Macro for initializing one-time initialization structure
#define GPR_ONCE_INIT PTHREAD_ONCE_INIT

#endif  // GRPC_SUPPORT_SYNC_POSIX_H
```

The comments explain:
1. The header's purpose (POSIX synchronization primitives for gRPC)
2. The conditional compilation for AddressSanitizer support
3. The wrapper structures when ASAN is enabled
4. The direct typedefs when ASAN is disabled
5. The one-time initialization type and macro
6. The relationship to pthread types

The comments maintain the original license header while adding explanations for the technical implementation details.