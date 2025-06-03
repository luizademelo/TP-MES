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

#ifndef GRPC_SUPPORT_ATM_GCC_ATOMIC_H
#define GRPC_SUPPORT_ATM_GCC_ATOMIC_H

#include <grpc/support/port_platform.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define atomic integer type (platform-dependent pointer-sized integer)
typedef intptr_t gpr_atm;

// Define maximum and minimum values for atomic type
#define GPR_ATM_MAX INTPTR_MAX
#define GPR_ATM_MIN INTPTR_MIN

// Memory barrier operations:

// Full memory barrier (sequentially consistent)
#define gpr_atm_full_barrier() (__atomic_thread_fence(__ATOMIC_SEQ_CST))

// Load operations:

// Atomic load with acquire semantics (ensures subsequent operations happen after)
#define gpr_atm_acq_load(p) (__atomic_load_n((p), __ATOMIC_ACQUIRE))
// Atomic load without memory ordering constraints
#define gpr_atm_no_barrier_load(p) (__atomic_load_n((p), __ATOMIC_RELAXED))

// Store operations:

// Atomic store with release semantics (ensures prior operations complete before)
#define gpr_atm_rel_store(p, value) \
  (__atomic_store_n((p), (intptr_t)(value), __ATOMIC_RELEASE))
// Atomic store without memory ordering constraints
#define gpr_atm_no_barrier_store(p, value) \
  (__atomic_store_n((p), (intptr_t)(value), __ATOMIC_RELAXED))

// Atomic arithmetic operations:

// Atomic fetch-and-add without memory ordering constraints
#define gpr_atm_no_barrier_fetch_add(p, delta) \
  __atomic_fetch_add((p), (intptr_t)(delta), __ATOMIC_RELAXED)
// Atomic fetch-and-add with acquire-release semantics
#define gpr_atm_full_fetch_add(p, delta) \
  __atomic_fetch_add((p), (intptr_t)(delta), __ATOMIC_ACQ_REL)

// Compare-and-swap operations:

// Atomic compare-and-swap without memory ordering constraints
static __inline int gpr_atm_no_barrier_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
  return __atomic_compare_exchange_n(p, &o, n, 0, __ATOMIC_RELAXED,
                                     __ATOMIC_RELAXED);
}

// Atomic compare-and-swap with acquire semantics (on success)
static __inline int gpr_atm_acq_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
  return __atomic_compare_exchange_n(p, &o, n, 0, __ATOMIC_ACQUIRE,
                                     __ATOMIC_RELAXED);
}

// Atomic compare-and-swap with release semantics (on success)
static __inline int gpr_atm_rel_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
  return __atomic_compare_exchange_n(p, &o, n, 0, __ATOMIC_RELEASE,
                                     __ATOMIC_RELAXED);
}

// Atomic compare-and-swap with acquire-release semantics
static __inline int gpr_atm_full_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
  return __atomic_compare_exchange_n(p, &o, n, 0, __ATOMIC_ACQ_REL,
                                     __ATOMIC_RELAXED);
}

// Atomic exchange operation with acquire-release semantics
#define gpr_atm_full_xchg(p, n) __atomic_exchange_n((p), (n), __ATOMIC_ACQ_REL)

#ifdef __cplusplus
}
#endif

#endif /* GRPC_SUPPORT_ATM_GCC_ATOMIC_H */
```

The comments added explain:
1. The purpose of each type definition and macro
2. The memory ordering semantics of each atomic operation
3. The behavior of different compare-and-swap variants
4. The difference between relaxed and sequentially consistent operations
5. The purpose of the memory barrier operations

The comments are structured to help developers understand:
- What each operation does
- Its memory ordering guarantees
- When to use which variant
- How these operations map to GCC's built-in atomic operations