
// Copyright 2015 gRPC authors.

#include <grpc/support/port_platform.h>

#if defined(GPR_WINDOWS) && !defined(GPR_ABSEIL_SYNC) && \
    !defined(GPR_CUSTOM_SYNC)

#include <grpc/support/sync.h>
#include <grpc/support/time.h>

#include "absl/log/check.h"

void gpr_mu_init(gpr_mu* mu) {
  InitializeCriticalSection(&mu->cs);
  mu->locked = 0;
}

void gpr_mu_destroy(gpr_mu* mu) { DeleteCriticalSection(&mu->cs); }

void gpr_mu_lock(gpr_mu* mu) {
  EnterCriticalSection(&mu->cs);
  CHECK(!mu->locked);
  mu->locked = 1;
}

void gpr_mu_unlock(gpr_mu* mu) {
  mu->locked = 0;
  LeaveCriticalSection(&mu->cs);
}

int gpr_mu_trylock(gpr_mu* mu) {
  int result = TryEnterCriticalSection(&mu->cs);
  if (result) {
    if (mu->locked) {
      LeaveCriticalSection(&mu->cs);
      result = 0;
    }
    mu->locked = 1;
  }
  return result;
}

void gpr_cv_init(gpr_cv* cv) { InitializeConditionVariable(cv); }

void gpr_cv_destroy(gpr_cv* cv) {

}

int gpr_cv_wait(gpr_cv* cv, gpr_mu* mu, gpr_timespec abs_deadline) {
  int timeout = 0;
  DWORD timeout_max_ms;
  mu->locked = 0;
  if (gpr_time_cmp(abs_deadline, gpr_inf_future(abs_deadline.clock_type)) ==
      0) {
    SleepConditionVariableCS(cv, &mu->cs, INFINITE);
  } else {
    abs_deadline = gpr_convert_clock_type(abs_deadline, GPR_CLOCK_REALTIME);
    gpr_timespec now = gpr_now(abs_deadline.clock_type);
    int64_t now_ms = (int64_t)now.tv_sec * 1000 + now.tv_nsec / 1000000;
    int64_t deadline_ms =
        (int64_t)abs_deadline.tv_sec * 1000 + abs_deadline.tv_nsec / 1000000;
    if (now_ms >= deadline_ms) {
      timeout = 1;
    } else {
      if ((deadline_ms - now_ms) >= INFINITE) {
        timeout_max_ms = INFINITE - 1;
      } else {
        timeout_max_ms = (DWORD)(deadline_ms - now_ms);
      }
      timeout = (SleepConditionVariableCS(cv, &mu->cs, timeout_max_ms) == 0 &&
                 GetLastError() == ERROR_TIMEOUT);
    }
  }
  mu->locked = 1;
  return timeout;
}

void gpr_cv_signal(gpr_cv* cv) { WakeConditionVariable(cv); }

void gpr_cv_broadcast(gpr_cv* cv) { WakeAllConditionVariable(cv); }

static void* phony;
struct run_once_func_arg {
  void (*init_function)(void);
};
static BOOL CALLBACK run_once_func(gpr_once* once, void* v, void** pv) {
  struct run_once_func_arg* arg = (struct run_once_func_arg*)v;
  (*arg->init_function)();
  return 1;
}

void gpr_once_init(gpr_once* once, void (*init_function)(void)) {
  struct run_once_func_arg arg;
  arg.init_function = init_function;
  InitOnceExecuteOnce(once, run_once_func, &arg, &phony);
}

#endif
