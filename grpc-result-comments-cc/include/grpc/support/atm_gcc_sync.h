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

#ifndef GRPC_SUPPORT_ATM_GCC_SYNC_H
#define GRPC_SUPPORT_ATM_GCC_SYNC_H

#include <grpc/support/port_platform.h>

// Define atomic integer type and its limits
typedef intptr_t gpr_atm;              // Atomic memory type (pointer-sized integer)
#define GPR_ATM_MAX INTPTR_MAX         // Maximum value for gpr_atm
#define GPR_ATM_MIN INTPTR_MIN         // Minimum value for gpr_atm

// Compile-time memory barrier to prevent instruction reordering
#define GPR_ATM_COMPILE_BARRIER_() __asm__ __volatile__("" : : : "memory")

// Define load-store barrier based on architecture
#if defined(__i386) || defined(__x86_64__)
// On x86 architectures, a compile barrier is sufficient for load-store ordering
#define GPR_ATM_LS_BARRIER_() GPR_ATM_COMPILE_BARRIER_()
#else
// On other architectures, use a full memory barrier
#define GPR_ATM_LS_BARRIER_() gpr_atm_full_barrier()
#endif

// Full memory barrier implementation using GCC built-in
#define gpr_atm_full_barrier() (__sync_synchronize())

// Atomic load with acquire semantics (ensures subsequent operations happen after)
static __inline gpr_atm gpr_atm_acq_load(const gpr_atm* p) {
  gpr_atm value = *p;
  GPR_ATM_LS_BARRIER_();  // Ensure load happens before subsequent operations
  return value;
}

// Atomic load without memory barrier (only prevents compiler reordering)
static __inline gpr_atm gpr_atm_no_barrier_load(const gpr_atm* p) {
  gpr_atm value = *p;
  GPR_ATM_COMPILE_BARRIER_();  // Prevent compiler reordering only
  return value;
}

// Atomic store with release semantics (ensures previous operations complete before)
static __inline void gpr_atm_rel_store(gpr_atm* p, gpr_atm value) {
  GPR_ATM_LS_BARRIER_();  // Ensure previous operations complete before store
  *p = value;
}

// Atomic store without memory barrier (only prevents compiler reordering)
static __inline void gpr_atm_no_barrier_store(gpr_atm* p, gpr_atm value) {
  GPR_ATM_COMPILE_BARRIER_();  // Prevent compiler reordering only
  *p = value;
}

// Clean up barrier macros
#undef GPR_ATM_LS_BARRIER_
#undef GPR_ATM_COMPILE_BARRIER_

// Atomic fetch-and-add operations
#define gpr_atm_no_barrier_fetch_add(p, delta) \
  gpr_atm_full_fetch_add((p), (delta))         // No-barrier version uses full barrier
#define gpr_atm_full_fetch_add(p, delta) (__sync_fetch_and_add((p), (delta)))

// Compare-and-swap operations with different memory ordering semantics
#define gpr_atm_no_barrier_cas(p, o, n) gpr_atm_acq_cas((p), (o), (n))  // No-barrier version uses acquire
#define gpr_atm_acq_cas(p, o, n) (__sync_bool_compare_and_swap((p), (o), (n)))  // Acquire CAS
#define gpr_atm_rel_cas(p, o, n) gpr_atm_acq_cas((p), (o), (n))         // Release CAS uses acquire
#define gpr_atm_full_cas(p, o, n) gpr_atm_acq_cas((p), (o), (n))       // Full CAS uses acquire

// Atomic exchange operation (swap)
static __inline gpr_atm gpr_atm_full_xchg(gpr_atm* p, gpr_atm n) {
  gpr_atm cur;
  do {
    cur = gpr_atm_acq_load(p);  // Load current value with acquire semantics
  } while (!gpr_atm_rel_cas(p, cur, n));  // Attempt swap until successful
  return cur;  // Return previous value
}

#endif  // GRPC_SUPPORT_ATM_GCC_SYNC_H
```

The comments explain:
1. The purpose of each atomic operation and its memory ordering semantics
2. How different architectures are handled for memory barriers
3. The implementation details of each operation
4. The relationship between different versions of operations (like no-barrier vs full versions)
5. The memory ordering guarantees provided by each operation

The comments maintain technical accuracy while being clear enough for developers who might need to maintain or modify this atomic operations implementation.