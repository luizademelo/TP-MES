
// Copyright 2016 gRPC authors.

#include "src/cpp/thread_manager/thread_manager.h"

#include <climits>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/thd.h"

namespace grpc {

ThreadManager::WorkerThread::WorkerThread(ThreadManager* thd_mgr)
    : thd_mgr_(thd_mgr) {

  thd_ = grpc_core::Thread(
      "grpcpp_sync_server",
      [](void* th) { static_cast<ThreadManager::WorkerThread*>(th)->Run(); },
      this, &created_);
  if (!created_) {
    LOG(ERROR) << "Could not create grpc_sync_server worker-thread";
  }
}

void ThreadManager::WorkerThread::Run() {
  thd_mgr_->MainWorkLoop();
  thd_mgr_->MarkAsCompleted(this);
}

ThreadManager::WorkerThread::~WorkerThread() {

  thd_.Join();
}

ThreadManager::ThreadManager(const char*, grpc_resource_quota* resource_quota,
                             int min_pollers, int max_pollers)
    : shutdown_(false),
      thread_quota_(
          grpc_core::ResourceQuota::FromC(resource_quota)->thread_quota()),
      num_pollers_(0),
      min_pollers_(min_pollers),
      max_pollers_(max_pollers == -1 ? INT_MAX : max_pollers),
      num_threads_(0),
      max_active_threads_sofar_(0) {}

ThreadManager::~ThreadManager() {
  {
    grpc_core::MutexLock lock(&mu_);
    CHECK_EQ(num_threads_, 0);
  }

  CleanupCompletedThreads();
}

void ThreadManager::Wait() {
  grpc_core::MutexLock lock(&mu_);
  while (num_threads_ != 0) {
    shutdown_cv_.Wait(&mu_);
  }
}

void ThreadManager::Shutdown() {
  grpc_core::MutexLock lock(&mu_);
  shutdown_ = true;
}

bool ThreadManager::IsShutdown() {
  grpc_core::MutexLock lock(&mu_);
  return shutdown_;
}

int ThreadManager::GetMaxActiveThreadsSoFar() {
  grpc_core::MutexLock list_lock(&list_mu_);
  return max_active_threads_sofar_;
}

void ThreadManager::MarkAsCompleted(WorkerThread* thd) {
  {
    grpc_core::MutexLock list_lock(&list_mu_);
    completed_threads_.push_back(thd);
  }

  {
    grpc_core::MutexLock lock(&mu_);
    num_threads_--;
    if (num_threads_ == 0) {
      shutdown_cv_.Signal();
    }
  }

  thread_quota_->Release(1);
}

void ThreadManager::CleanupCompletedThreads() {
  std::list<WorkerThread*> completed_threads;
  {

    grpc_core::MutexLock lock(&list_mu_);
    completed_threads.swap(completed_threads_);
  }
  for (auto thd : completed_threads) delete thd;
}

void ThreadManager::Initialize() {
  if (!thread_quota_->Reserve(min_pollers_)) {
    grpc_core::Crash(absl::StrFormat(
        "No thread quota available to even create the minimum required "
        "polling threads (i.e %d). Unable to start the thread manager",
        min_pollers_));
  }

  {
    grpc_core::MutexLock lock(&mu_);
    num_pollers_ = min_pollers_;
    num_threads_ = min_pollers_;
    max_active_threads_sofar_ = min_pollers_;
  }

  for (int i = 0; i < min_pollers_; i++) {
    WorkerThread* worker = new WorkerThread(this);
    CHECK(worker->created());
    worker->Start();
  }
}

void ThreadManager::MainWorkLoop() {
  while (true) {
    void* tag;
    bool ok;
    WorkStatus work_status = PollForWork(&tag, &ok);

    grpc_core::LockableAndReleasableMutexLock lock(&mu_);

    num_pollers_--;
    bool done = false;
    switch (work_status) {
      case TIMEOUT:

        if (shutdown_ || num_pollers_ > max_pollers_) done = true;
        break;
      case SHUTDOWN:

        done = true;
        break;
      case WORK_FOUND:

        bool resource_exhausted = false;
        if (!shutdown_ && num_pollers_ < min_pollers_) {
          if (thread_quota_->Reserve(1)) {

            num_pollers_++;
            num_threads_++;
            if (num_threads_ > max_active_threads_sofar_) {
              max_active_threads_sofar_ = num_threads_;
            }

            lock.Release();
            WorkerThread* worker = new WorkerThread(this);
            if (worker->created()) {
              worker->Start();
            } else {

              grpc_core::MutexLock failure_lock(&mu_);
              num_pollers_--;
              num_threads_--;
              resource_exhausted = true;
              delete worker;
            }
          } else if (num_pollers_ > 0) {

            lock.Release();
          } else {

            lock.Release();
            resource_exhausted = true;
          }
        } else {

          lock.Release();
        }

        DoWork(tag, ok, !resource_exhausted);

        lock.Lock();

        if (shutdown_) done = true;
        break;
    }

    if (done) break;

    if (num_pollers_ < max_pollers_) {
      num_pollers_++;
    } else {
      break;
    }
  };

  CleanupCompletedThreads();

}

}
