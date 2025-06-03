Here's the commented version of the code:

```c++
// Copyright 2023 Google LLC.  All rights reserved.

#ifndef UPB_PORT_ATOMIC_H_
#define UPB_PORT_ATOMIC_H_

// Include platform definitions
#include "upb/port/def.inc"

// Check if we should use C11 atomics
#ifdef UPB_USE_C11_ATOMICS

#include <stdatomic.h>
#include <stdbool.h>

// Define atomic operations using C11 standard library
#define upb_Atomic_Init(addr, val) atomic_init(addr, val)
#define upb_Atomic_Load(addr, order) atomic_load_explicit(addr, order)
#define upb_Atomic_Store(addr, val, order) \
  atomic_store_explicit(addr, val, order)
#define upb_Atomic_Exchange(addr, val, order) \
  atomic_exchange_explicit(addr, val, order)
#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  atomic_compare_exchange_strong_explicit(addr, expected, desired,     \
                                          success_order, failure_order)
#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  atomic_compare_exchange_weak_explicit(addr, expected, desired,               \
                                        success_order, failure_order)

// Check if we should use Microsoft compiler intrinsics
#elif defined(UPB_USE_MSC_ATOMICS)
#include <intrin.h>
#include <stdbool.h>
#include <stdint.h>

// Basic atomic initialization
#define upb_Atomic_Init(addr, val) (*(addr) = val)

// 64-bit implementation for Windows
#if defined(_WIN64)

#pragma intrinsic(_InterlockedExchange64)
// Atomic store operation using MSVC intrinsic
#define upb_Atomic_Store(addr, val, order) \
  (void)_InterlockedExchange64((uint64_t volatile *)addr, (uint64_t)val)

#pragma intrinsic(_InterlockedCompareExchange64)
// Helper function for atomic load using compare-exchange
static uintptr_t upb_Atomic_LoadMsc(uint64_t volatile *addr) {
  // Use a dummy value for compare-exchange to implement load
  return _InterlockedCompareExchange64(addr, 0xDEADC0DEBAADF00D,
                                       0xDEADC0DEBAADF00D);
}

// C11 generic selection for type-safe operations
#if __STDC_VERSION__ >= 201112L
#define upb_Atomic_Load(addr, order)                           \
  _Generic(addr,                                               \
      UPB_ATOMIC(uintptr_t) *: upb_Atomic_LoadMsc(             \
                                 (uint64_t volatile *)(addr)), \
      default: (void *)upb_Atomic_LoadMsc((uint64_t volatile *)(addr)))

#define upb_Atomic_Exchange(addr, val, order)                                 \
  _Generic(addr,                                                              \
      UPB_ATOMIC(uintptr_t) *: _InterlockedExchange64(                        \
                                 (uint64_t volatile *)(addr), (uint64_t)val), \
      default: (void *)_InterlockedExchange64((uint64_t volatile *)addr,      \
                                              (uint64_t)val))
#else
// Fallback for non-C11 compilers
#define upb_Atomic_Load(addr, order) \
  (void *)upb_Atomic_LoadMsc((uint64_t volatile *)(addr))

#define upb_Atomic_Exchange(addr, val, order) \
  (void *)_InterlockedExchange64((uint64_t volatile *)addr, (uint64_t)val)
#endif

#pragma intrinsic(_InterlockedCompareExchange64)
// Helper function for atomic compare-and-exchange
static bool upb_Atomic_CompareExchangeMscP(uint64_t volatile *addr,
                                           uint64_t *expected,
                                           uint64_t desired) {
  uint64_t expect_val = *expected;
  uint64_t actual_val =
      _InterlockedCompareExchange64(addr, desired, expect_val);
  if (expect_val != actual_val) {
    *expected = actual_val;
    return false;
  }
  return true;
}

// Strong and weak compare-exchange operations
#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  upb_Atomic_CompareExchangeMscP((uint64_t volatile *)addr,            \
                                 (uint64_t *)expected, (uint64_t)desired)

#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeMscP((uint64_t volatile *)addr,                    \
                                 (uint64_t *)expected, (uint64_t)desired)

#else
// 32-bit implementation for Windows

#pragma intrinsic(_InterlockedExchange)
#define upb_Atomic_Store(addr, val, order) \
  (void)_InterlockedExchange((uint32_t volatile *)addr, (uint32_t)val)

#pragma intrinsic(_InterlockedCompareExchange)
static uintptr_t upb_Atomic_LoadMsc(uint32_t volatile *addr) {
  // Use a dummy value for compare-exchange to implement load
  return _InterlockedCompareExchange(addr, 0xDEADC0DE, 0xDEADC0DE);
}

#if __STDC_VERSION__ >= 201112L
#define upb_Atomic_Load(addr, order)                           \
  _Generic(addr,                                               \
      UPB_ATOMIC(uintptr_t) *: upb_Atomic_LoadMsc(             \
                                 (uint32_t volatile *)(addr)), \
      default: (void *)upb_Atomic_LoadMsc((uint32_t volatile *)(addr)))

#define upb_Atomic_Exchange(addr, val, order)                                 \
  _Generic(addr,                                                              \
      UPB_ATOMIC(uintptr_t) *: _InterlockedExchange(                          \
                                 (uint32_t volatile *)(addr), (uint32_t)val), \
      default: (void *)_InterlockedExchange64((uint32_t volatile *)addr,      \
                                              (uint32_t)val))
#else
#define upb_Atomic_Load(addr, order) \
  (void *)upb_Atomic_LoadMsc((uint32_t volatile *)(addr))

#define upb_Atomic_Exchange(addr, val, order) \
  (void *)_InterlockedExchange((uint32_t volatile *)addr, (uint32_t)val)
#endif

#pragma intrinsic(_InterlockedCompareExchange)
static bool upb_Atomic_CompareExchangeMscP(uint32_t volatile *addr,
                                           uint32_t *expected,
                                           uint32_t desired) {
  uint32_t expect_val = *expected;
  uint32_t actual_val = _InterlockedCompareExchange(addr, desired, expect_val);
  if (expect_val != actual_val) {
    *expected = actual_val;
    return false;
  }
  return true;
}

#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  upb_Atomic_CompareExchangeMscP((uint32_t volatile *)addr,            \
                                 (uint32_t *)expected, (uint32_t)desired)

#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeMscP((uint32_t volatile *)addr,                    \
                                 (uint32_t *)expected, (uint32_t)desired)
#endif

#else
// Fallback implementation when no atomic support is available

#if !defined(UPB_SUPPRESS_MISSING_ATOMICS)
#error Your compiler does not support atomic instructions, which UPB uses. If you do not use UPB on multiple threads, you can suppress this error by defining UPB_SUPPRESS_MISSING_ATOMICS.
#endif

#include <string.h>

// Non-atomic fallback implementations
#define upb_Atomic_Init(addr, val) (*addr = val)
#define upb_Atomic_Load(addr, order) (*addr)
#define upb_Atomic_Store(addr, val, order) (*(addr) = val)

// Non-atomic exchange implementation using memcpy
UPB_INLINE void* _upb_NonAtomic_Exchange(void* addr, void* value) {
  void* old;
  memcpy(&old, addr, sizeof(value));
  memcpy(addr, &value, sizeof(value));
  return old;
}

#define upb_Atomic_Exchange(addr, val, order) _upb_NonAtomic_Exchange(addr, val)

// Non-atomic compare-and-exchange implementation
UPB_INLINE bool _upb_NonAtomic_CompareExchangeStrongP(void* addr,
                                                      void* expected,
                                                      void* desired) {
  if (memcmp(addr, expected, sizeof(desired)) == 0) {
    memcpy(addr, &desired, sizeof(desired));
    return true;
  } else {
    memcpy(expected, addr, sizeof(desired));
    return false;
  }
}

#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  _upb_NonAtomic_CompareExchangeStrongP((void*)addr, (void*)expected,  \
                                        (void*)desired)
#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeStrong(addr, expected, desired, 0, 0)

#endif

// Clean up platform definitions
#include "upb/port/undef.inc"

#endif  // UPB_PORT_ATOMIC_H_
```

The comments explain:
1. The overall purpose of the file (atomic operations abstraction)
2. The different implementations (C11, MSVC intrinsics, fallback)
3. The purpose of each macro and helper function
4. The platform-specific details for different architectures (32-bit vs 64-bit)
5. The non-atomic fallback implementation
6. Important implementation details like the use of dummy values for atomic loads

The comments are designed to help maintainers understand:
- Why certain implementations were chosen
- How the atomic operations work under the hood
- Where to look when porting to new platforms
- The thread-safety implications of each implementation