Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CPP_THREAD_MANAGER_THREAD_MANAGER_H
#define GRPC_SRC_CPP_THREAD_MANAGER_THREAD_MANAGER_H

#include <list>

#include "src/core/lib/resource_quota/api.h"
#include "src/core/lib/resource_quota/thread_quota.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"

namespace grpc {

// ThreadManager class manages a pool of worker threads for performing asynchronous operations.
// It provides functionality to initialize, shutdown, and manage the lifecycle of worker threads.
class ThreadManager {
 public:
  // Constructor for ThreadManager.
  // Parameters:
  //   name: Name identifier for the thread manager
  //   resource_quota: Resource quota for thread allocation
  //   min_pollers: Minimum number of active polling threads to maintain
  //   max_pollers: Maximum number of active polling threads allowed
  explicit ThreadManager(const char* name, grpc_resource_quota* resource_quota,
                         int min_pollers, int max_pollers);
  
  // Virtual destructor to allow proper cleanup in derived classes
  virtual ~ThreadManager();

  // Initializes the thread manager and starts the minimum number of pollers
  void Initialize();

  // Enum representing possible work statuses returned by PollForWork
  enum WorkStatus { 
    WORK_FOUND,   // Work item was found
    SHUTDOWN,     // Thread manager is shutting down
    TIMEOUT       // Polling timed out
  };

  // Pure virtual function to be implemented by derived classes.
  // Polls for available work items.
  // Parameters:
  //   tag: Output parameter for work item identifier
  //   ok: Output parameter indicating work item status
  virtual WorkStatus PollForWork(void** tag, bool* ok) = 0;

  // Pure virtual function to be implemented by derived classes.
  // Processes a work item.
  // Parameters:
  //   tag: Work item identifier
  //   ok: Status of the work item
  //   resources: Indicates if resources are available for processing
  virtual void DoWork(void* tag, bool ok, bool resources) = 0;

  // Shuts down the thread manager and all worker threads
  virtual void Shutdown();

  // Checks if the thread manager is in shutdown state
  bool IsShutdown();

  // Waits for all worker threads to complete
  virtual void Wait();

  // Returns the maximum number of active threads observed so far
  int GetMaxActiveThreadsSoFar();

 private:
  // Nested class representing a worker thread
  class WorkerThread {
   public:
    // Constructor taking a pointer to the managing ThreadManager
    explicit WorkerThread(ThreadManager* thd_mgr);
    ~WorkerThread();

    // Returns whether the thread was successfully created
    bool created() const { return created_; }
    
    // Starts the worker thread
    void Start() { thd_.Start(); }

   private:
    // Main execution function for the worker thread
    void Run();

    // Pointer to the managing ThreadManager instance
    ThreadManager* const thd_mgr_;
    // The actual thread object
    grpc_core::Thread thd_;
    // Flag indicating successful thread creation
    bool created_;
  };

  // Main work loop for worker threads
  void MainWorkLoop();

  // Marks a worker thread as completed and adds it to cleanup list
  void MarkAsCompleted(WorkerThread* thd);
  
  // Cleans up completed worker threads
  void CleanupCompletedThreads();

  // Mutex for protecting shared state
  grpc_core::Mutex mu_;

  // Flag indicating shutdown state
  bool shutdown_;
  // Condition variable for shutdown notification
  grpc_core::CondVar shutdown_cv_;

  // Note: The user of this ThreadManager object must create grpc_resource_quota

  // Resource quota for thread allocation
  grpc_core::ThreadQuotaPtr thread_quota_;

  // Current number of active pollers
  int num_pollers_;

  // Minimum number of pollers to maintain
  int min_pollers_;
  // Maximum number of pollers allowed
  int max_pollers_;

  // Current total number of threads (active + idle)
  int num_threads_;

  // Maximum number of active threads observed so far
  int max_active_threads_sofar_;

  // Mutex for protecting the completed threads list
  grpc_core::Mutex list_mu_;
  // List of completed threads waiting for cleanup
  std::list<WorkerThread*> completed_threads_;
};

}  // namespace grpc

#endif  // GRPC_SRC_CPP_THREAD_MANAGER_THREAD_MANAGER_H
```

The comments explain:
1. The overall purpose of the ThreadManager class
2. Each public method's functionality and parameters
3. The WorkStatus enum values
4. Private implementation details including the WorkerThread nested class
5. Member variables and their purposes
6. Synchronization mechanisms (mutexes and condition variables)
7. Resource management components

The comments are designed to help future developers understand both the interface and implementation details while maintaining the original code structure and functionality.