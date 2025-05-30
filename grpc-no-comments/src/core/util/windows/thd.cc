
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#ifdef GPR_WINDOWS

#include <grpc/support/alloc.h>
#include <grpc/support/sync.h>
#include <grpc/support/thd_id.h>
#include <grpc/support/time.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/memory.h"
#include "src/core/util/thd.h"

namespace {
class ThreadInternalsWindows;
struct thd_info {
  ThreadInternalsWindows* thread;
  void (*body)(void* arg);
  void* arg;
  HANDLE join_event;
  bool joinable;
};

thread_local struct thd_info* g_thd_info;

class ThreadInternalsWindows
    : public grpc_core::internal::ThreadInternalsInterface {
 public:
  ThreadInternalsWindows(void (*thd_body)(void* arg), void* arg, bool* success,
                         const grpc_core::Thread::Options& options)
      : started_(false) {
    gpr_mu_init(&mu_);
    gpr_cv_init(&ready_);

    HANDLE handle;
    info_ = (struct thd_info*)gpr_malloc(sizeof(*info_));
    info_->thread = this;
    info_->body = thd_body;
    info_->arg = arg;
    info_->join_event = nullptr;
    info_->joinable = options.joinable();
    if (info_->joinable) {
      info_->join_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
      if (info_->join_event == nullptr) {
        gpr_free(info_);
        *success = false;
        return;
      }
    }

    if (options.stack_size() != 0) {

      handle = CreateThread(nullptr, options.stack_size(), thread_body, info_,
                            0, nullptr);
    } else {
      handle = CreateThread(nullptr, 64 * 1024, thread_body, info_, 0, nullptr);
    }

    if (handle == nullptr) {
      destroy_thread();
      *success = false;
    } else {
      CloseHandle(handle);
      *success = true;
    }
  }

  ~ThreadInternalsWindows() override {
    gpr_mu_destroy(&mu_);
    gpr_cv_destroy(&ready_);
  }

  void Start() override {
    gpr_mu_lock(&mu_);
    started_ = true;
    gpr_cv_signal(&ready_);
    gpr_mu_unlock(&mu_);
  }

  void Join() override {
    DWORD ret = WaitForSingleObject(info_->join_event, INFINITE);
    CHECK(ret == WAIT_OBJECT_0);
    destroy_thread();
  }

 private:
  static DWORD WINAPI thread_body(void* v) {
    g_thd_info = static_cast<thd_info*>(v);
    gpr_mu_lock(&g_thd_info->thread->mu_);
    while (!g_thd_info->thread->started_) {
      gpr_cv_wait(&g_thd_info->thread->ready_, &g_thd_info->thread->mu_,
                  gpr_inf_future(GPR_CLOCK_MONOTONIC));
    }
    gpr_mu_unlock(&g_thd_info->thread->mu_);
    if (!g_thd_info->joinable) {
      delete g_thd_info->thread;
      g_thd_info->thread = nullptr;
    }
    g_thd_info->body(g_thd_info->arg);
    if (g_thd_info->joinable) {
      BOOL ret = SetEvent(g_thd_info->join_event);
      CHECK(ret);
    } else {
      gpr_free(g_thd_info);
    }
    return 0;
  }

  void destroy_thread() {
    if (info_ != nullptr && info_->joinable) {
      CloseHandle(info_->join_event);
    }
    gpr_free(info_);
  }

  gpr_mu mu_;
  gpr_cv ready_;
  bool started_;
  thd_info* info_;
};

}

namespace grpc_core {

void Thread::Signal(gpr_thd_id , int ) {

  VLOG(2) << "Thread signals are not supported on Windows.";
}

void Thread::Kill(gpr_thd_id ) {

  VLOG(2) << "Thread::Kill is not supported on Windows.";
}

Thread::Thread(const char* , void (*thd_body)(void* arg),
               void* arg, bool* success, const Options& options)
    : options_(options) {
  bool outcome = false;
  impl_ = new ThreadInternalsWindows(thd_body, arg, &outcome, options);
  if (outcome) {
    state_ = ALIVE;
  } else {
    state_ = FAILED;
    delete impl_;
    impl_ = nullptr;
  }

  if (success != nullptr) {
    *success = outcome;
  }
}

}

gpr_thd_id gpr_thd_currentid(void) {
  return reinterpret_cast<gpr_thd_id>(g_thd_info);
}

#endif
