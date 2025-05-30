
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SPINLOCK_H
#define GRPC_SRC_CORE_UTIL_SPINLOCK_H

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>

struct gpr_spinlock {
  gpr_atm atm;
};
#ifdef __cplusplus
#define GPR_SPINLOCK_INITIALIZER (gpr_spinlock{0})
#else
#define GPR_SPINLOCK_INITIALIZER ((gpr_spinlock){0})
#endif
#define GPR_SPINLOCK_STATIC_INITIALIZER {0}

#define gpr_spinlock_trylock(lock) (gpr_atm_acq_cas(&(lock)->atm, 0, 1))
#define gpr_spinlock_unlock(lock) (gpr_atm_rel_store(&(lock)->atm, 0))

#define gpr_spinlock_lock(lock) \
  do {                          \
  } while (!gpr_spinlock_trylock((lock)))

#endif
