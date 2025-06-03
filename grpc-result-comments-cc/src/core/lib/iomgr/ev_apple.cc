Here's the commented version of the code:

```c++
// Copyright 2020 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_APPLE_EV  // Apple-specific event handling implementation

#include <CoreFoundation/CoreFoundation.h>
#include <list>

#include "absl/time/time.h"
#include "src/core/lib/iomgr/ev_apple.h"
#include "src/core/util/thd.h"
#include "src/core/util/time_util.h"

// Special value indicating a broadcast kick to all workers
#define GRPC_POLLSET_KICK_BROADCAST ((grpc_pollset_worker*)1)

// Global context for managing the Apple run loop
struct GlobalRunLoopContext {
  grpc_core::CondVar init_cv;        // Condition variable for initialization
  grpc_core::CondVar input_source_cv; // Condition variable for input sources
  
  grpc_core::Mutex mu;               // Mutex for thread synchronization
  
  bool input_source_registered = false; // Flag indicating if input source is registered
  
  CFRunLoopRef run_loop;             // Reference to Apple's CFRunLoop
  
  bool is_shutdown = false;          // Flag indicating shutdown state
};

// Represents a worker in the Apple event system
struct GrpcAppleWorker {
  grpc_core::CondVar cv;             // Condition variable for worker signaling
  bool kicked = false;               // Flag indicating if worker was kicked
};

// Apple-specific implementation of a pollset
struct GrpcApplePollset {
  grpc_core::Mutex mu;               // Mutex for thread safety
  
  std::list<GrpcAppleWorker*> workers; // List of active workers
  
  bool is_shutdown = false;          // Flag indicating shutdown state
  
  grpc_closure* shutdown_closure;    // Closure to execute on shutdown
  
  bool kicked_without_poller = false; // Flag for kick without active poller
};

// Global variables for run loop management
static GlobalRunLoopContext* gGlobalRunLoopContext = nullptr;
static grpc_core::Thread* gGlobalRunLoopThread = nullptr;

// Register read stream with dispatch queue
static void grpc_apple_register_read_stream_queue(
    CFReadStreamRef read_stream, dispatch_queue_t dispatch_queue) {
  CFReadStreamSetDispatchQueue(read_stream, dispatch_queue);
}

// Register write stream with dispatch queue
static void grpc_apple_register_write_stream_queue(
    CFWriteStreamRef write_stream, dispatch_queue_t dispatch_queue) {
  CFWriteStreamSetDispatchQueue(write_stream, dispatch_queue);
}

// Register read stream with run loop
static void grpc_apple_register_read_stream_run_loop(
    CFReadStreamRef read_stream, dispatch_queue_t ) {
  GRPC_TRACE_VLOG(apple_polling, 2)
      << "(polling) Register read stream: " << read_stream;
  grpc_core::MutexLock lock(&gGlobalRunLoopContext->mu);
  CFReadStreamScheduleWithRunLoop(read_stream, gGlobalRunLoopContext->run_loop,
                                  kCFRunLoopDefaultMode);
  gGlobalRunLoopContext->input_source_registered = true;
  gGlobalRunLoopContext->input_source_cv.Signal();
}

// Register write stream with run loop
static void grpc_apple_register_write_stream_run_loop(
    CFWriteStreamRef write_stream, dispatch_queue_t ) {
  GRPC_TRACE_VLOG(apple_polling, 2)
      << "(polling) Register write stream: " << write_stream;
  grpc_core::MutexLock lock(&gGlobalRunLoopContext->mu);
  CFWriteStreamScheduleWithRunLoop(
      write_stream, gGlobalRunLoopContext->run_loop, kCFRunLoopDefaultMode);
  gGlobalRunLoopContext->input_source_registered = true;
  gGlobalRunLoopContext->input_source_cv.Signal();
}

// Function pointers for stream registration methods
static void (*grpc_apple_register_read_stream_impl)(
    CFReadStreamRef, dispatch_queue_t) = grpc_apple_register_read_stream_queue;
static void (*grpc_apple_register_write_stream_impl)(CFWriteStreamRef,
                                                     dispatch_queue_t) =
    grpc_apple_register_write_stream_queue;

// Public interface for read stream registration
void grpc_apple_register_read_stream(CFReadStreamRef read_stream,
                                     dispatch_queue_t dispatch_queue) {
  grpc_apple_register_read_stream_impl(read_stream, dispatch_queue);
}

// Public interface for write stream registration
void grpc_apple_register_write_stream(CFWriteStreamRef write_stream,
                                      dispatch_queue_t dispatch_queue) {
  grpc_apple_register_write_stream_impl(write_stream, dispatch_queue);
}

// Main function for the global run loop thread
static void GlobalRunLoopFunc(void* ) {
  grpc_core::LockableAndReleasableMutexLock lock(&gGlobalRunLoopContext->mu);
  gGlobalRunLoopContext->run_loop = CFRunLoopGetCurrent();
  gGlobalRunLoopContext->init_cv.Signal();

  // Main run loop processing
  while (!gGlobalRunLoopContext->is_shutdown) {
    // Wait for input sources to be registered
    while (!gGlobalRunLoopContext->input_source_registered) {
      gGlobalRunLoopContext->input_source_cv.Wait(&gGlobalRunLoopContext->mu);
    }
    gGlobalRunLoopContext->input_source_registered = false;
    lock.Release();
    CFRunLoopRun();  // Run the Apple event loop
    lock.Lock();
  }
  lock.Release();
}

// Initialize global pollset state
static void pollset_global_init(void) {
  gGlobalRunLoopContext = new GlobalRunLoopContext;

  // Set up run loop based registration
  grpc_apple_register_read_stream_impl =
      grpc_apple_register_read_stream_run_loop;
  grpc_apple_register_write_stream_impl =
      grpc_apple_register_write_stream_run_loop;

  // Start the global run loop thread
  grpc_core::MutexLock lock(&gGlobalRunLoopContext->mu);
  gGlobalRunLoopThread =
      new grpc_core::Thread("apple_ev", GlobalRunLoopFunc, nullptr);
  gGlobalRunLoopThread->Start();
  // Wait for run loop initialization
  while (gGlobalRunLoopContext->run_loop == NULL)
    gGlobalRunLoopContext->init_cv.Wait(&gGlobalRunLoopContext->mu);
}

// Shutdown global pollset state
static void pollset_global_shutdown(void) {
  {
    grpc_core::MutexLock lock(&gGlobalRunLoopContext->mu);
    gGlobalRunLoopContext->is_shutdown = true;
    CFRunLoopStop(gGlobalRunLoopContext->run_loop);
  }
  gGlobalRunLoopThread->Join();
  delete gGlobalRunLoopThread;
  delete gGlobalRunLoopContext;
}

// Main pollset work function
static grpc_error_handle pollset_work(grpc_pollset* pollset,
                                      grpc_pollset_worker** worker,
                                      grpc_core::Timestamp deadline) {
  GRPC_TRACE_VLOG(apple_polling, 2)
      << "(polling) pollset work: " << pollset << ", worker: " << worker
      << ", deadline: " << deadline.milliseconds_after_process_epoch();
  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);
  GrpcAppleWorker actual_worker;
  if (worker) {
    *worker = reinterpret_cast<grpc_pollset_worker*>(&actual_worker);
  }

  if (apple_pollset->kicked_without_poller) {
    // Handle case where pollset was kicked without a worker
    apple_pollset->kicked_without_poller = false;
  } else {
    // Add worker to the pollset and wait for events
    apple_pollset->workers.push_front(&actual_worker);
    auto it = apple_pollset->workers.begin();

    // Wait until kicked or shutdown or deadline expires
    while (!actual_worker.kicked && !apple_pollset->is_shutdown) {
      if (actual_worker.cv.WaitWithDeadline(
              &apple_pollset->mu, grpc_core::ToAbslTime(deadline.as_timespec(
                                      GPR_CLOCK_REALTIME)))) {
        break;
      }
    }

    apple_pollset->workers.erase(it);

    // Handle shutdown if all workers are done
    if (apple_pollset->is_shutdown && apple_pollset->workers.empty()) {
      grpc_core::ExecCtx::Run(DEBUG_LOCATION, apple_pollset->shutdown_closure,
                              absl::OkStatus());
    }
  }

  return absl::OkStatus();
}

// Helper function to kick a worker
static void kick_worker(GrpcAppleWorker* worker) {
  worker->kicked = true;
  worker->cv.Signal();
}

// Kick specific worker(s) in a pollset
static grpc_error_handle pollset_kick(grpc_pollset* pollset,
                                      grpc_pollset_worker* specific_worker) {
  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);

  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset kick: " << pollset
                                    << ", worker:" << specific_worker;

  if (specific_worker == nullptr) {
    // Kick most recently added worker if none specified
    if (apple_pollset->workers.empty()) {
      apple_pollset->kicked_without_poller = true;
    } else {
      GrpcAppleWorker* actual_worker = apple_pollset->workers.front();
      kick_worker(actual_worker);
    }
  } else if (specific_worker == GRPC_POLLSET_KICK_BROADCAST) {
    // Broadcast kick to all workers
    for (auto& actual_worker : apple_pollset->workers) {
      kick_worker(actual_worker);
    }
  } else {
    // Kick specific worker
    GrpcAppleWorker* actual_worker =
        reinterpret_cast<GrpcAppleWorker*>(specific_worker);
    kick_worker(actual_worker);
  }

  return absl::OkStatus();
}

// Initialize a pollset
static void pollset_init(grpc_pollset* pollset, gpr_mu** mu) {
  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset init: " << pollset;
  GrpcApplePollset* apple_pollset = new (pollset) GrpcApplePollset();
  *mu = grpc_core::GetUnderlyingGprMu(&apple_pollset->mu);
}

// Shutdown a pollset
static void pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  GRPC_TRACE_VLOG(apple_polling, 2)
      << "(polling) pollset shutdown: " << pollset;

  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);
  apple_pollset->is_shutdown = true;
  (void)pollset_kick(pollset, GRPC_POLLSET_KICK_BROADCAST);

  if (apple_pollset->workers.empty()) {
    // Execute shutdown closure immediately if no workers
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
  } else {
    // Store closure to execute when last worker finishes
    apple_pollset->shutdown_closure = closure;
  }
}

// Destroy a pollset
static void pollset_destroy(grpc_pollset* pollset) {
  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset destroy: " << pollset;
  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);
  apple_pollset->~GrpcApplePollset();
}

// Get size of pollset structure
size_t pollset_size(void) { return sizeof(GrpcApplePollset); }

// Pollset virtual function table
grpc_pollset_vtable grpc_apple_pollset_vtable = {
    pollset_global_init, pollset_global_shutdown,
    pollset_init,        pollset_shutdown,
    pollset_destroy,     pollset_work,
    pollset_kick,        pollset_size};

// The following are stubs for pollset set functionality (not implemented)
grpc_pollset_set* pollset_set_create(void) { return nullptr; }
void pollset_set_destroy(grpc_pollset_set* ) {}
void pollset_set_add_pollset(grpc_pollset_set* ,
                             grpc_pollset* ) {}
void pollset_set_del_pollset(grpc_pollset_set* ,
                             grpc_pollset* ) {}
void pollset_set_add_pollset_set(grpc_pollset_set* ,
                                 grpc_pollset_set* ) {}
void pollset_set_del_pollset_set(grpc_pollset_set* ,
                                 grpc_pollset_set* ) {}

// Pollset set virtual function table (stubs)
grpc_pollset_set_vtable grpc_apple_pollset_set_vtable = {
    pollset_set_create,          pollset_set_destroy,
    pollset_set_add_pollset,     pollset_set_del_pollset,
    pollset_set_add_pollset_set, pollset_set_del_pollset_set};

#endif  // GRPC_APPLE_EV
```