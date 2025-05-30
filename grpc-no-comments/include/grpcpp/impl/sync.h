
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_IMPL_SYNC_H
#define GRPCPP_IMPL_SYNC_H

#include <grpc/support/port_platform.h>

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

#ifdef GPR_ABSEIL_SYNC

using Mutex = absl::Mutex;
using MutexLock = absl::MutexLock;
using ReleasableMutexLock = absl::ReleasableMutexLock;
using CondVar = absl::CondVar;

#else

class ABSL_LOCKABLE Mutex {
 public:
  Mutex() { gpr_mu_init(&mu_); }
  ~Mutex() { gpr_mu_destroy(&mu_); }

  Mutex(const Mutex&) = delete;
  Mutex& operator=(const Mutex&) = delete;

  void Lock() ABSL_EXCLUSIVE_LOCK_FUNCTION() { gpr_mu_lock(&mu_); }
  void Unlock() ABSL_UNLOCK_FUNCTION() { gpr_mu_unlock(&mu_); }

 private:
  union {
    gpr_mu mu_;
    std::mutex do_not_use_sth_;
#ifdef GPR_HAS_PTHREAD_H
    pthread_mutex_t do_not_use_pth_;
#endif
  };

  friend class CondVar;
};

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
    ABSL_DCHECK(!released_);
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

  void Wait(Mutex* mu) {
    gpr_cv_wait(&cv_, &mu->mu_, gpr_inf_future(GPR_CLOCK_REALTIME));
  }

 private:
  gpr_cv cv_;
};

#endif

template <typename Predicate>
GRPC_DEPRECATED("incompatible with thread safety analysis")
static void WaitUntil(CondVar* cv, Mutex* mu, Predicate pred) {
  while (!pred()) {
    cv->Wait(mu);
  }
}

}
}

#endif
