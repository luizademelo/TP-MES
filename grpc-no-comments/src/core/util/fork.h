
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_FORK_H
#define GRPC_SRC_CORE_UTIL_FORK_H

#include <grpc/support/port_platform.h>

#include <atomic>
#include <set>

// NOTE: FORKING IS NOT GENERALLY SUPPORTED, THIS IS ONLY INTENDED TO WORK

namespace grpc_core {

class GPR_DLL Fork {
 public:
  typedef void (*child_postfork_func)(void);

  static void GlobalInit();

  static bool Enabled();

  static void IncExecCtxCount() {
    if (GPR_UNLIKELY(support_enabled_.load(std::memory_order_relaxed))) {
      DoIncExecCtxCount();
    }
  }

  static void DecExecCtxCount() {
    if (GPR_UNLIKELY(support_enabled_.load(std::memory_order_relaxed))) {
      DoDecExecCtxCount();
    }
  }

  static bool RegisterResetChildPollingEngineFunc(
      child_postfork_func reset_child_polling_engine);
  static const std::set<child_postfork_func>& GetResetChildPollingEngineFunc();

  static bool BlockExecCtx();
  static void AllowExecCtx();

  static void IncThreadCount();

  static void DecThreadCount();

  static void AwaitThreads();

  static void Enable(bool enable);

 private:
  static void DoIncExecCtxCount();
  static void DoDecExecCtxCount();

  static std::atomic<bool> support_enabled_;
  static bool override_enabled_;
  static std::set<child_postfork_func>* reset_child_polling_engine_;
};

}

#endif
