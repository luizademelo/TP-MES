Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

// Header guard to prevent multiple inclusions
#ifndef GRPCPP_IMPL_SYNC_H
#define GRPCPP_IMPL_SYNC_H

#include <grpc/support/port_platform.h>

// Include pthread.h if available on the platform
#ifdef GPR_HAS_PTHREAD_H
#include <pthread.h>
#endif

#include <grpc/support/sync.h>
#include <grpc/support/time.h>

#include <mutex>

#include "absl/log/absl_check.h"
#include "absl/synchronization/mutex.h"

namespace grpc {
namespace internal {

// If using Abseil synchronization primitives
#ifdef GPR_ABSEIL_SYNC

// Define synchronization types using Abseil implementations
using Mutex = absl::Mutex;
using MutexLock = absl::MutexLock;
using ReleasableMutexLock = absl::ReleasableMutexLock;
using CondVar = absl::CondVar;

#else

// Custom Mutex class implementation when not using Abseil
class ABSL_LOCKABLE Mutex {
 public:
  Mutex() { gpr_mu_init(&mu_); }  // Initialize the mutex
  ~Mutex() { gpr_mu_destroy(&mu_); }  // Destroy the mutex

  // Delete copy constructor and assignment operator
  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  // Lock the mutex (exclusive access)
  void Lock() ABSL_EXCLUSIVE_LOCK_FUNCTION() { gpr_mu_lock(&mu_); }
  // Unlock the mutex
  void Unlock() ABSL_UNLOCK_FUNCTION() { gpr_mu_unlock(&mu_); }

 private:
  // Union to hold different mutex implementations
  union {
    gpr_mu mu_;  // gRPC mutex implementation
    std::mutex do_not_use_sth_;  // Standard mutex (not to be used directly)
#ifdef GPR_HAS_PTHREAD_H
    pthread_mutex_t do_not_use_pth_;  // pthread mutex (not to be used directly)
#endif
  };

  friend class CondVar;  // Allow CondVar to access private members
};

// RAII-style mutex lock guard
class ABSL_SCOPED_LOCKABLE MutexLock {
 public:
  // Constructor locks the mutex
  explicit MutexLock(Mutex* mu) ABSL_EXCLUSIVE_LOCK_FUNCTION(mu) : mu_(mu) {
    mu_->Lock();
  }
  // Destructor unlocks the mutex
  ~MutexLock() ABSL_UNLOCK_FUNCTION() { mu_->Unlock(); }

  // Delete copy constructor and assignment operator
  MutexLock(const MutexLock&) = delete;
  MutexLock& operator=(const MutexLock&) = delete;

 private:
  Mutex* const mu_;  // The mutex being managed
};

// RAII-style mutex lock guard with manual release capability
class ABSL_SCOPED_LOCKABLE ReleasableMutexLock {
 public:
  // Constructor locks the mutex
  explicit ReleasableMutexLock(Mutex* mu) ABSL_EXCLUSIVE_LOCK_FUNCTION(mu)
      : mu_(mu) {
    mu_->Lock();
  }
  // Destructor unlocks the mutex if not released
  ~ReleasableMutexLock() ABSL_UNLOCK_FUNCTION() {
    if (!released_) mu_->Unlock();
  }

  // Delete copy constructor and assignment operator
  ReleasableMutexLock(const ReleasableMutexLock&) = delete;
  ReleasableMutexLock& operator=(const ReleasableMutexLock&) = delete;

  // Manually release the lock before destruction
  void Release() ABSL_UNLOCK_FUNCTION() {
    ABSL_DCHECK(!released_);  // Debug check to prevent double release
    released_ = true;
    mu_->Unlock();
  }

 private:
  Mutex* const mu_;  // The mutex being managed
  bool released_ = false;  // Flag indicating if lock was manually released
};

// Condition variable implementation
class CondVar {
 public:
  CondVar() { gpr_cv_init(&cv_); }  // Initialize condition variable
  ~CondVar() { gpr_cv_destroy(&cv_); }  // Destroy condition variable

  // Delete copy constructor and assignment operator
  CondVar(const CondVar&) = delete;
  CondVar& operator=(const CondVar&) = delete;

  // Signal one waiting thread
  void Signal() { gpr_cv_signal(&cv_); }
  // Signal all waiting threads
  void SignalAll() { gpr_cv_broadcast(&cv_); }

  // Wait for condition (atomically releases mutex and waits)
  void Wait(Mutex* mu) {
    gpr_cv_wait(&cv_, &mu->mu_, gpr_inf_future(GPR_CLOCK_REALTIME));
  }

 private:
  gpr_cv cv_;  // gRPC condition variable implementation
};

#endif

// Helper function to wait for a condition predicate to become true
template <typename Predicate>
GRPC_DEPRECATED("incompatible with thread safety analysis")
static void WaitUntil(CondVar* cv, Mutex* mu, Predicate pred) {
  while (!pred()) {
    cv->Wait(mu);
  }
}

}  // namespace internal
}  // namespace grpc

#endif  // GRPCPP_IMPL_SYNC_H
```