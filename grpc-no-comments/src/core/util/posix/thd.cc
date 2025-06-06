
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <csignal>
#include <string>

#ifdef GPR_POSIX_SYNC

#include <grpc/support/sync.h>
#include <grpc/support/thd_id.h>
#include <grpc/support/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/core/util/fork.h"
#include "src/core/util/strerror.h"
#include "src/core/util/thd.h"
#include "src/core/util/useful.h"

namespace grpc_core {
namespace {

class ThreadInternalsPosix;

struct thd_arg {
  ThreadInternalsPosix* thread;
  void (*body)(void* arg);
  void* arg;
  const char* name;
  bool joinable;
  bool tracked;
};

size_t RoundUpToPageSize(size_t size) {

  size_t page_size = static_cast<size_t>(sysconf(_SC_PAGESIZE));
  return (size + page_size - 1) & ~(page_size - 1);
}

size_t MinValidStackSize(size_t request_size) {
  size_t min_stacksize = sysconf(_SC_THREAD_STACK_MIN);
  if (request_size < min_stacksize) {
    request_size = min_stacksize;
  }

  return RoundUpToPageSize(request_size);
}

class ThreadInternalsPosix : public internal::ThreadInternalsInterface {
 public:
  ThreadInternalsPosix(const char* thd_name, void (*thd_body)(void* arg),
                       void* arg, bool* success, const Thread::Options& options)
      : started_(false) {
    gpr_mu_init(&mu_);
    gpr_cv_init(&ready_);
    pthread_attr_t attr;

    thd_arg* info = static_cast<thd_arg*>(malloc(sizeof(*info)));
    CHECK_NE(info, nullptr);
    info->thread = this;
    info->body = thd_body;
    info->arg = arg;
    info->name = thd_name;
    info->joinable = options.joinable();
    info->tracked = options.tracked();
    if (options.tracked()) {
      Fork::IncThreadCount();
    }

    CHECK_EQ(pthread_attr_init(&attr), 0);
    if (options.joinable()) {
      CHECK(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) == 0);
    } else {
      CHECK(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) == 0);
    }

    if (options.stack_size() != 0) {
      size_t stack_size = MinValidStackSize(options.stack_size());
      CHECK_EQ(pthread_attr_setstacksize(&attr, stack_size), 0);
    }

    int pthread_create_err = pthread_create(
        &pthread_id_, &attr,
        [](void* v) -> void* {
          thd_arg arg = *static_cast<thd_arg*>(v);
          free(v);
          if (arg.name != nullptr) {
#if GPR_APPLE_PTHREAD_NAME

            pthread_setname_np(arg.name);
#elif GPR_LINUX_PTHREAD_NAME

            char buf[16];
            size_t buf_len = GPR_ARRAY_SIZE(buf) - 1;
            strncpy(buf, arg.name, buf_len);
            buf[buf_len] = '\0';
            pthread_setname_np(pthread_self(), buf);
#endif
          }

          gpr_mu_lock(&arg.thread->mu_);
          while (!arg.thread->started_) {
            gpr_cv_wait(&arg.thread->ready_, &arg.thread->mu_,
                        gpr_inf_future(GPR_CLOCK_MONOTONIC));
          }
          gpr_mu_unlock(&arg.thread->mu_);

          if (!arg.joinable) {
            delete arg.thread;
          }

          (*arg.body)(arg.arg);
          if (arg.tracked) {
            Fork::DecThreadCount();
          }
          return nullptr;
        },
        info);
    *success = (pthread_create_err == 0);

    CHECK_EQ(pthread_attr_destroy(&attr), 0);

    if (!(*success)) {
      LOG(ERROR) << "pthread_create failed: " << StrError(pthread_create_err);

      free(info);
      if (options.tracked()) {
        Fork::DecThreadCount();
      }
    }
  }

  ~ThreadInternalsPosix() override {
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
    int pthread_join_err = pthread_join(pthread_id_, nullptr);
    if (pthread_join_err != 0) {
      Crash("pthread_join failed: " + StrError(pthread_join_err));
    }
  }

 private:
  gpr_mu mu_;
  gpr_cv ready_;
  bool started_;
  pthread_t pthread_id_;
};

}

void Thread::Signal(gpr_thd_id tid, int sig) {
  auto kill_err = pthread_kill((pthread_t)tid, sig);
  if (kill_err != 0) {
    LOG(ERROR) << "pthread_kill for tid " << tid
               << " failed: " << StrError(kill_err);
  }
}

#ifndef GPR_ANDROID
void Thread::Kill(gpr_thd_id tid) {
  auto cancel_err = pthread_cancel((pthread_t)tid);
  if (cancel_err != 0) {
    LOG(ERROR) << "pthread_cancel for tid " << tid
               << " failed: " << StrError(cancel_err);
  }
}
#else
void Thread::Kill(gpr_thd_id ) {
  VLOG(2) << "Thread::Kill is not supported on Android.";
}
#endif

Thread::Thread(const char* thd_name, void (*thd_body)(void* arg), void* arg,
               bool* success, const Options& options)
    : options_(options) {
  bool outcome = false;
  impl_ = new ThreadInternalsPosix(thd_name, thd_body, arg, &outcome, options);
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

  return (gpr_thd_id)pthread_self();
}

#endif
