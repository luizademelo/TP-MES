
// Copyright 2020 gRPC authors.

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/port.h"

#ifdef GRPC_APPLE_EV

#include <CoreFoundation/CoreFoundation.h>

#include <list>

#include "absl/time/time.h"
#include "src/core/lib/iomgr/ev_apple.h"
#include "src/core/util/thd.h"
#include "src/core/util/time_util.h"

#define GRPC_POLLSET_KICK_BROADCAST ((grpc_pollset_worker*)1)

struct GlobalRunLoopContext {
  grpc_core::CondVar init_cv;
  grpc_core::CondVar input_source_cv;

  grpc_core::Mutex mu;

  bool input_source_registered = false;

  CFRunLoopRef run_loop;

  bool is_shutdown = false;
};

struct GrpcAppleWorker {

  grpc_core::CondVar cv;

  bool kicked = false;
};

struct GrpcApplePollset {
  grpc_core::Mutex mu;

  std::list<GrpcAppleWorker*> workers;

  bool is_shutdown = false;

  grpc_closure* shutdown_closure;

  bool kicked_without_poller = false;
};

static GlobalRunLoopContext* gGlobalRunLoopContext = nullptr;
static grpc_core::Thread* gGlobalRunLoopThread = nullptr;

static void grpc_apple_register_read_stream_queue(
    CFReadStreamRef read_stream, dispatch_queue_t dispatch_queue) {
  CFReadStreamSetDispatchQueue(read_stream, dispatch_queue);
}

static void grpc_apple_register_write_stream_queue(
    CFWriteStreamRef write_stream, dispatch_queue_t dispatch_queue) {
  CFWriteStreamSetDispatchQueue(write_stream, dispatch_queue);
}

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

static void (*grpc_apple_register_read_stream_impl)(
    CFReadStreamRef, dispatch_queue_t) = grpc_apple_register_read_stream_queue;
static void (*grpc_apple_register_write_stream_impl)(CFWriteStreamRef,
                                                     dispatch_queue_t) =
    grpc_apple_register_write_stream_queue;

void grpc_apple_register_read_stream(CFReadStreamRef read_stream,
                                     dispatch_queue_t dispatch_queue) {
  grpc_apple_register_read_stream_impl(read_stream, dispatch_queue);
}

void grpc_apple_register_write_stream(CFWriteStreamRef write_stream,
                                      dispatch_queue_t dispatch_queue) {
  grpc_apple_register_write_stream_impl(write_stream, dispatch_queue);
}

static void GlobalRunLoopFunc(void* ) {
  grpc_core::LockableAndReleasableMutexLock lock(&gGlobalRunLoopContext->mu);
  gGlobalRunLoopContext->run_loop = CFRunLoopGetCurrent();
  gGlobalRunLoopContext->init_cv.Signal();

  while (!gGlobalRunLoopContext->is_shutdown) {

    while (!gGlobalRunLoopContext->input_source_registered) {
      gGlobalRunLoopContext->input_source_cv.Wait(&gGlobalRunLoopContext->mu);
    }
    gGlobalRunLoopContext->input_source_registered = false;
    lock.Release();
    CFRunLoopRun();
    lock.Lock();
  }
  lock.Release();
}

static void pollset_global_init(void) {
  gGlobalRunLoopContext = new GlobalRunLoopContext;

  grpc_apple_register_read_stream_impl =
      grpc_apple_register_read_stream_run_loop;
  grpc_apple_register_write_stream_impl =
      grpc_apple_register_write_stream_run_loop;

  grpc_core::MutexLock lock(&gGlobalRunLoopContext->mu);
  gGlobalRunLoopThread =
      new grpc_core::Thread("apple_ev", GlobalRunLoopFunc, nullptr);
  gGlobalRunLoopThread->Start();
  while (gGlobalRunLoopContext->run_loop == NULL)
    gGlobalRunLoopContext->init_cv.Wait(&gGlobalRunLoopContext->mu);
}

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

    apple_pollset->kicked_without_poller = false;
  } else {

    apple_pollset->workers.push_front(&actual_worker);
    auto it = apple_pollset->workers.begin();

    while (!actual_worker.kicked && !apple_pollset->is_shutdown) {
      if (actual_worker.cv.WaitWithDeadline(
              &apple_pollset->mu, grpc_core::ToAbslTime(deadline.as_timespec(
                                      GPR_CLOCK_REALTIME)))) {

        break;
      }
    }

    apple_pollset->workers.erase(it);

    if (apple_pollset->is_shutdown && apple_pollset->workers.empty()) {
      grpc_core::ExecCtx::Run(DEBUG_LOCATION, apple_pollset->shutdown_closure,
                              absl::OkStatus());
    }
  }

  return absl::OkStatus();
}

static void kick_worker(GrpcAppleWorker* worker) {
  worker->kicked = true;
  worker->cv.Signal();
}

static grpc_error_handle pollset_kick(grpc_pollset* pollset,
                                      grpc_pollset_worker* specific_worker) {
  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);

  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset kick: " << pollset
                                    << ", worker:" << specific_worker;

  if (specific_worker == nullptr) {
    if (apple_pollset->workers.empty()) {
      apple_pollset->kicked_without_poller = true;
    } else {
      GrpcAppleWorker* actual_worker = apple_pollset->workers.front();
      kick_worker(actual_worker);
    }
  } else if (specific_worker == GRPC_POLLSET_KICK_BROADCAST) {
    for (auto& actual_worker : apple_pollset->workers) {
      kick_worker(actual_worker);
    }
  } else {
    GrpcAppleWorker* actual_worker =
        reinterpret_cast<GrpcAppleWorker*>(specific_worker);
    kick_worker(actual_worker);
  }

  return absl::OkStatus();
}

static void pollset_init(grpc_pollset* pollset, gpr_mu** mu) {
  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset init: " << pollset;
  GrpcApplePollset* apple_pollset = new (pollset) GrpcApplePollset();
  *mu = grpc_core::GetUnderlyingGprMu(&apple_pollset->mu);
}

static void pollset_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  GRPC_TRACE_VLOG(apple_polling, 2)
      << "(polling) pollset shutdown: " << pollset;

  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);
  apple_pollset->is_shutdown = true;
  (void)pollset_kick(pollset, GRPC_POLLSET_KICK_BROADCAST);

  if (apple_pollset->workers.empty()) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
  } else {
    apple_pollset->shutdown_closure = closure;
  }
}

static void pollset_destroy(grpc_pollset* pollset) {
  GRPC_TRACE_VLOG(apple_polling, 2) << "(polling) pollset destroy: " << pollset;
  GrpcApplePollset* apple_pollset =
      reinterpret_cast<GrpcApplePollset*>(pollset);
  apple_pollset->~GrpcApplePollset();
}

size_t pollset_size(void) { return sizeof(GrpcApplePollset); }

grpc_pollset_vtable grpc_apple_pollset_vtable = {
    pollset_global_init, pollset_global_shutdown,
    pollset_init,        pollset_shutdown,
    pollset_destroy,     pollset_work,
    pollset_kick,        pollset_size};

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

grpc_pollset_set_vtable grpc_apple_pollset_set_vtable = {
    pollset_set_create,          pollset_set_destroy,
    pollset_set_add_pollset,     pollset_set_del_pollset,
    pollset_set_add_pollset_set, pollset_set_del_pollset_set};

#endif
