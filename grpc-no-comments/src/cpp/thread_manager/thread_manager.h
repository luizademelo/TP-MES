
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CPP_THREAD_MANAGER_THREAD_MANAGER_H
#define GRPC_SRC_CPP_THREAD_MANAGER_THREAD_MANAGER_H

#include <list>

#include "src/core/lib/resource_quota/api.h"
#include "src/core/lib/resource_quota/thread_quota.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"

namespace grpc {

class ThreadManager {
 public:
  explicit ThreadManager(const char* name, grpc_resource_quota* resource_quota,
                         int min_pollers, int max_pollers);
  virtual ~ThreadManager();

  void Initialize();

  enum WorkStatus { WORK_FOUND, SHUTDOWN, TIMEOUT };

  virtual WorkStatus PollForWork(void** tag, bool* ok) = 0;

  virtual void DoWork(void* tag, bool ok, bool resources) = 0;

  virtual void Shutdown();

  bool IsShutdown();

  virtual void Wait();

  int GetMaxActiveThreadsSoFar();

 private:

  class WorkerThread {
   public:
    explicit WorkerThread(ThreadManager* thd_mgr);
    ~WorkerThread();

    bool created() const { return created_; }
    void Start() { thd_.Start(); }

   private:

    void Run();

    ThreadManager* const thd_mgr_;
    grpc_core::Thread thd_;
    bool created_;
  };

  void MainWorkLoop();

  void MarkAsCompleted(WorkerThread* thd);
  void CleanupCompletedThreads();

  grpc_core::Mutex mu_;

  bool shutdown_;
  grpc_core::CondVar shutdown_cv_;

  // Note: The user of this ThreadManager object must create grpc_resource_quota

  grpc_core::ThreadQuotaPtr thread_quota_;

  int num_pollers_;

  int min_pollers_;
  int max_pollers_;

  int num_threads_;

  int max_active_threads_sofar_;

  grpc_core::Mutex list_mu_;
  std::list<WorkerThread*> completed_threads_;
};

}

#endif
