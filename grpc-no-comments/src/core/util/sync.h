
// Copyright 2019 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_SYNC_H
#define GRPC_SRC_CORE_UTIL_SYNC_H

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/synchronization/mutex.h"

#ifndef GPR_ABSEIL_SYNC
#include "src/core/util/time_util.h"
#endif

namespace grpc_core {

#ifdef GPR_ABSEIL_SYNC

using Mutex = absl::Mutex;
using MutexLock = absl::MutexLock;
using ReleasableMutexLock = absl::ReleasableMutexLock;
using CondVar = absl::CondVar;

inline gpr_mu* GetUnderlyingGprMu(Mutex* mutex) {
  return reinterpret_cast<gpr_mu*>(mutex);
}

#else

class ABSL_LOCKABLE Mutex {
 public:
  Mutex() { gpr_mu_init(&mu_); }
  ~Mutex() { gpr_mu_destroy(&mu_); }

  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  void Lock() ABSL_EXCLUSIVE_LOCK_FUNCTION() { gpr_mu_lock(&mu_); }
  void Unlock() ABSL_UNLOCK_FUNCTION() { gpr_mu_unlock(&mu_); }
  bool TryLock() ABSL_EXCLUSIVE_TRYLOCK_FUNCTION(true) {
    return gpr_mu_trylock(&mu_) != 0;
  }
  void AssertHeld() ABSL_ASSERT_EXCLUSIVE_LOCK() {}

 private:
  gpr_mu mu_;

  friend class CondVar;
  friend gpr_mu* GetUnderlyingGprMu(Mutex* mutex);
};

inline gpr_mu* GetUnderlyingGprMu(Mutex* mutex) { return &mutex->mu_; }

class ABSL_SCOPED_LOCKABLE MutexLock {
 public:
  explicit MutexLock(Mutex* mu) ABSL_EXCLUSIVE_LOCK_FUNCTION(mu) : mu_(mu) {
    mu_->Lock();
  }
  ~MutexLock() ABSL_UNLOCK_FUNCTION() { mu_->Unlock(); }

  MutexLock(const MutexLock&) = delete;
  MutexLock& operator=(const MutexLock&) = delete;

 private:
  Mutex* const mu_;
};

class ABSL_SCOPED_LOCKABLE ReleasableMutexLock {
 public:
  explicit ReleasableMutexLock(Mutex* mu) ABSL_EXCLUSIVE_LOCK_FUNCTION(mu)
      : mu_(mu) {
    mu_->Lock();
  }
  ~ReleasableMutexLock() ABSL_UNLOCK_FUNCTION() {
    if (!released_) mu_->Unlock();
  }

  ReleasableMutexLock(const ReleasableMutexLock&) = delete;
  ReleasableMutexLock& operator=(const ReleasableMutexLock&) = delete;

  void Release() ABSL_UNLOCK_FUNCTION() {
    DCHECK(!released_);
    released_ = true;
    mu_->Unlock();
  }

 private:
  Mutex* const mu_;
  bool released_ = false;
};

class CondVar {
 public:
  CondVar() { gpr_cv_init(&cv_); }
  ~CondVar() { gpr_cv_destroy(&cv_); }

  CondVar(const CondVar&) = delete;
  CondVar& operator=(const CondVar&) = delete;

  void Signal() { gpr_cv_signal(&cv_); }
  void SignalAll() { gpr_cv_broadcast(&cv_); }

  void Wait(Mutex* mu) { WaitWithDeadline(mu, absl::InfiniteFuture()); }
  bool WaitWithTimeout(Mutex* mu, absl::Duration timeout) {
    return gpr_cv_wait(&cv_, &mu->mu_, ToGprTimeSpec(timeout)) != 0;
  }
  bool WaitWithDeadline(Mutex* mu, absl::Time deadline) {
    return gpr_cv_wait(&cv_, &mu->mu_, ToGprTimeSpec(deadline)) != 0;
  }

 private:
  gpr_cv cv_;
};

#endif

class MutexLockForGprMu {
 public:
  explicit MutexLockForGprMu(gpr_mu* mu) : mu_(mu) { gpr_mu_lock(mu_); }
  ~MutexLockForGprMu() { gpr_mu_unlock(mu_); }

  MutexLockForGprMu(const MutexLock&) = delete;
  MutexLockForGprMu& operator=(const MutexLock&) = delete;

 private:
  gpr_mu* const mu_;
};

class ABSL_SCOPED_LOCKABLE LockableAndReleasableMutexLock {
 public:
  explicit LockableAndReleasableMutexLock(Mutex* mu)
      ABSL_EXCLUSIVE_LOCK_FUNCTION(mu)
      : mu_(mu) {
    mu_->Lock();
  }
  ~LockableAndReleasableMutexLock() ABSL_UNLOCK_FUNCTION() {
    if (!released_) mu_->Unlock();
  }

  LockableAndReleasableMutexLock(const LockableAndReleasableMutexLock&) =
      delete;
  LockableAndReleasableMutexLock& operator=(
      const LockableAndReleasableMutexLock&) = delete;

  void Lock() ABSL_EXCLUSIVE_LOCK_FUNCTION() {
    DCHECK(released_);
    mu_->Lock();
    released_ = false;
  }

  void Release() ABSL_UNLOCK_FUNCTION() {
    DCHECK(!released_);
    released_ = true;
    mu_->Unlock();
  }

 private:
  Mutex* const mu_;
  bool released_ = false;
};

}

#endif
