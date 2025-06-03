Here's the commented version of the code:

```c++
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

// WorkerThread constructor - creates a new worker thread for the ThreadManager
ThreadManager::WorkerThread::WorkerThread(ThreadManager* thd_mgr)
    : thd_mgr_(thd_mgr) {
  // Create a new thread that will execute the Run() method
  thd_ = grpc_core::Thread(
      "grpcpp_sync_server",
      [](void* th) { static_cast<ThreadManager::WorkerThread*>(th)->Run(); },
      this, &created_);
  if (!created_) {
    LOG(ERROR) << "Could not create grpc_sync_server worker-thread";
  }
}

// Main execution loop for worker threads
void ThreadManager::WorkerThread::Run() {
  // Enter the main work loop of the thread manager
  thd_mgr_->MainWorkLoop();
  // Notify thread manager that this thread is completing
  thd_mgr_->MarkAsCompleted(this);
}

// WorkerThread destructor - joins the thread
ThreadManager::WorkerThread::~WorkerThread() {
  // Wait for the thread to finish execution
  thd_.Join();
}

// ThreadManager constructor
ThreadManager::ThreadManager(const char*, grpc_resource_quota* resource_quota,
                             int min_pollers, int max_pollers)
    : shutdown_(false),
      thread_quota_(
          grpc_core::ResourceQuota::FromC(resource_quota)->thread_quota()),
      num_pollers_(0),
      min_pollers_(min_pollers),  // Minimum number of polling threads
      max_pollers_(max_pollers == -1 ? INT_MAX : max_pollers),  // Max threads
      num_threads_(0),
      max_active_threads_sofar_(0) {}  // Tracks peak thread usage

// ThreadManager destructor
ThreadManager::~ThreadManager() {
  {
    grpc_core::MutexLock lock(&mu_);
    CHECK_EQ(num_threads_, 0);  // Ensure all threads are gone
  }

  CleanupCompletedThreads();
}

// Wait for all threads to complete
void ThreadManager::Wait() {
  grpc_core::MutexLock lock(&mu_);
  while (num_threads_ != 0) {
    shutdown_cv_.Wait(&mu_);  // Wait until shutdown condition is signaled
  }
}

// Initiate shutdown of all threads
void ThreadManager::Shutdown() {
  grpc_core::MutexLock lock(&mu_);
  shutdown_ = true;  // Set shutdown flag
}

// Check if shutdown has been requested
bool ThreadManager::IsShutdown() {
  grpc_core::MutexLock lock(&mu_);
  return shutdown_;
}

// Get the peak number of active threads
int ThreadManager::GetMaxActiveThreadsSoFar() {
  grpc_core::MutexLock list_lock(&list_mu_);
  return max_active_threads_sofar_;
}

// Mark a thread as completed and clean up resources
void ThreadManager::MarkAsCompleted(WorkerThread* thd) {
  {
    // Add to completed threads list
    grpc_core::MutexLock list_lock(&list_mu_);
    completed_threads_.push_back(thd);
  }

  {
    // Update thread count and signal if we've reached zero
    grpc_core::MutexLock lock(&mu_);
    num_threads_--;
    if (num_threads_ == 0) {
      shutdown_cv_.Signal();  // Notify waiters that shutdown is complete
    }
  }

  // Release thread quota
  thread_quota_->Release(1);
}

// Clean up completed threads
void ThreadManager::CleanupCompletedThreads() {
  std::list<WorkerThread*> completed_threads;
  {
    // Swap out completed threads list under lock
    grpc_core::MutexLock lock(&list_mu_);
    completed_threads.swap(completed_threads_);
  }
  // Delete all completed threads
  for (auto thd : completed_threads) delete thd;
}

// Initialize the thread manager with minimum number of pollers
void ThreadManager::Initialize() {
  // Reserve thread quota for minimum pollers
  if (!thread_quota_->Reserve(min_pollers_)) {
    grpc_core::Crash(absl::StrFormat(
        "No thread quota available to even create the minimum required "
        "polling threads (i.e %d). Unable to start the thread manager",
        min_pollers_));
  }

  {
    // Initialize counters
    grpc_core::MutexLock lock(&mu_);
    num_pollers_ = min_pollers_;
    num_threads_ = min_pollers_;
    max_active_threads_sofar_ = min_pollers_;
  }

  // Create initial worker threads
  for (int i = 0; i < min_pollers_; i++) {
    WorkerThread* worker = new WorkerThread(this);
    CHECK(worker->created());
    worker->Start();
  }
}

// Main work loop for all worker threads
void ThreadManager::MainWorkLoop() {
  while (true) {
    void* tag;
    bool ok;
    // Poll for available work
    WorkStatus work_status = PollForWork(&tag, &ok);

    grpc_core::LockableAndReleasableMutexLock lock(&mu_);

    num_pollers_--;  // Decrement poller count as we're about to do work
    bool done = false;
    switch (work_status) {
      case TIMEOUT:
        // If we timed out and either shutting down or have too many pollers, exit
        if (shutdown_ || num_pollers_ > max_pollers_) done = true;
        break;
      case SHUTDOWN:
        // Exit on shutdown
        done = true;
        break;
      case WORK_FOUND:
        bool resource_exhausted = false;
        // If we found work and need more pollers (below minimum)
        if (!shutdown_ && num_pollers_ < min_pollers_) {
          if (thread_quota_->Reserve(1)) {
            // Reserve succeeded - create new worker
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
              // Worker creation failed - roll back counters
              grpc_core::MutexLock failure_lock(&mu_);
              num_pollers_--;
              num_threads_--;
              resource_exhausted = true;
              delete worker;
            }
          } else if (num_pollers_ > 0) {
            // Couldn't reserve but have other pollers - proceed
            lock.Release();
          } else {
            // No quota and no other pollers - mark as exhausted
            lock.Release();
            resource_exhausted = true;
          }
        } else {
          // No need to create more pollers
          lock.Release();
        }

        // Perform the actual work
        DoWork(tag, ok, !resource_exhausted);

        lock.Lock();

        if (shutdown_) done = true;
        break;
    }

    if (done) break;

    // If we're below max pollers, increment count before next iteration
    if (num_pollers_ < max_pollers_) {
      num_pollers_++;
    } else {
      break;
    }
  };

  // Clean up any completed threads
  CleanupCompletedThreads();
}

}  // namespace grpc
```