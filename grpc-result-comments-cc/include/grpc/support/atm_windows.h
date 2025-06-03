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

#ifndef GRPC_SUPPORT_ATM_WINDOWS_H
#define GRPC_SUPPORT_ATM_WINDOWS_H

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

// Define atomic integer type for Windows platform
typedef intptr_t gpr_atm;
// Define maximum and minimum values for atomic type
#define GPR_ATM_MAX INTPTR_MAX
#define GPR_ATM_MIN INTPTR_MIN

// Full memory barrier macro using Windows MemoryBarrier intrinsic
#define gpr_atm_full_barrier MemoryBarrier

/**
 * Atomic load with acquire semantics
 * @param p Pointer to atomic variable
 * @return The loaded value
 * Note: Includes a full memory barrier after load
 */
static __inline gpr_atm gpr_atm_acq_load(const gpr_atm* p) {
  gpr_atm result = *p;
  gpr_atm_full_barrier();
  return result;
}

/**
 * Atomic load without memory barriers
 * @param p Pointer to atomic variable
 * @return The loaded value
 * Note: Currently implemented same as acquire load
 */
static __inline gpr_atm gpr_atm_no_barrier_load(const gpr_atm* p) {
  return gpr_atm_acq_load(p);
}

/**
 * Atomic store with release semantics
 * @param p Pointer to atomic variable
 * @param value Value to store
 * Note: Includes a full memory barrier before store
 */
static __inline void gpr_atm_rel_store(gpr_atm* p, gpr_atm value) {
  gpr_atm_full_barrier();
  *p = value;
}

/**
 * Atomic store without memory barriers
 * @param p Pointer to atomic variable
 * @param value Value to store
 * Note: Currently implemented same as release store
 */
static __inline void gpr_atm_no_barrier_store(gpr_atm* p, gpr_atm value) {
  gpr_atm_rel_store(p, value);
}

/**
 * Atomic compare-and-swap without memory barriers
 * @param p Pointer to atomic variable
 * @param o Expected old value
 * @param n New value to store
 * @return 1 if successful, 0 otherwise
 * Note: Uses Windows InterlockedCompareExchange with acquire semantics
 */
static __inline int gpr_atm_no_barrier_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
#ifdef GPR_ARCH_64
  return o == (gpr_atm)InterlockedCompareExchangeAcquire64(
                  (volatile LONGLONG*)p, (LONGLONG)n, (LONGLONG)o);
#else
  return o == (gpr_atm)InterlockedCompareExchangeAcquire((volatile LONG*)p,
                                                         (LONG)n, (LONG)o);
#endif
}

/**
 * Atomic compare-and-swap with acquire semantics
 * @param p Pointer to atomic variable
 * @param o Expected old value
 * @param n New value to store
 * @return 1 if successful, 0 otherwise
 */
static __inline int gpr_atm_acq_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
#ifdef GPR_ARCH_64
  return o == (gpr_atm)InterlockedCompareExchangeAcquire64(
                  (volatile LONGLONG*)p, (LONGLONG)n, (LONGLONG)o);
#else
  return o == (gpr_atm)InterlockedCompareExchangeAcquire((volatile LONG*)p,
                                                         (LONG)n, (LONG)o);
#endif
}

/**
 * Atomic compare-and-swap with release semantics
 * @param p Pointer to atomic variable
 * @param o Expected old value
 * @param n New value to store
 * @return 1 if successful, 0 otherwise
 */
static __inline int gpr_atm_rel_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
#ifdef GPR_ARCH_64
  return o == (gpr_atm)InterlockedCompareExchangeRelease64(
                  (volatile LONGLONG*)p, (LONGLONG)n, (LONGLONG)o);
#else
  return o == (gpr_atm)InterlockedCompareExchangeRelease((volatile LONG*)p,
                                                         (LONG)n, (LONG)o);
#endif
}

/**
 * Atomic compare-and-swap with full barrier semantics
 * @param p Pointer to atomic variable
 * @param o Expected old value
 * @param n New value to store
 * @return 1 if successful, 0 otherwise
 */
static __inline int gpr_atm_full_cas(gpr_atm* p, gpr_atm o, gpr_atm n) {
#ifdef GPR_ARCH_64
  return o == (gpr_atm)InterlockedCompareExchange64((volatile LONGLONG*)p,
                                                    (LONGLONG)n, (LONGLONG)o);
#else
  return o == (gpr_atm)InterlockedCompareExchange((volatile LONG*)p, (LONG)n,
                                                  (LONG)o);
#endif
}

/**
 * Atomic fetch-and-add without memory barriers
 * @param p Pointer to atomic variable
 * @param delta Value to add
 * @return The old value before addition
 * Note: Implemented using compare-and-swap loop
 */
static __inline gpr_atm gpr_atm_no_barrier_fetch_add(gpr_atm* p,
                                                     gpr_atm delta) {
  gpr_atm old;
  do {
    old = *p;
  } while (!gpr_atm_no_barrier_cas(p, old, old + delta));
  return old;
}

/**
 * Atomic fetch-and-add with full barrier semantics
 * @param p Pointer to atomic variable
 * @param delta Value to add
 * @return The old value before addition
 * Note: Uses Windows InterlockedCompareExchange directly
 */
static __inline gpr_atm gpr_atm_full_fetch_add(gpr_atm* p, gpr_atm delta) {
  gpr_atm old;
#ifdef GPR_ARCH_64
  do {
    old = *p;
  } while (old != (gpr_atm)InterlockedCompareExchange64((volatile LONGLONG*)p,
                                                        (LONGLONG)old + delta,
                                                        (LONGLONG)old));
#else
  do {
    old = *p;
  } while (old != (gpr_atm)InterlockedCompareExchange(
                      (volatile LONG*)p, (LONG)old + delta, (LONG)old));
#endif
  return old;
}

/**
 * Atomic exchange operation
 * @param p Pointer to atomic variable
 * @param n New value to store
 * @return The old value before exchange
 * Note: Uses Windows InterlockedExchangePointer
 */
static __inline gpr_atm gpr_atm_full_xchg(gpr_atm* p, gpr_atm n) {
  return (gpr_atm)InterlockedExchangePointer((PVOID*)p, (PVOID)n);
}

#endif

#endif
```

The comments added:
1. Explain the purpose of each function and macro
2. Document parameters and return values
3. Note important implementation details
4. Highlight memory ordering semantics (acquire, release, full barrier)
5. Point out platform-specific implementations (32-bit vs 64-bit)
6. Explain the behavior of compare-and-swap loops
7. Note where functions are currently implemented identically to others (no-barrier variants)

The comments follow a consistent style and provide enough information for maintenance while not being overly verbose.