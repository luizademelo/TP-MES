
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EXEC_CTX_H
#define GRPC_SRC_CORE_LIB_IOMGR_EXEC_CTX_H

#include <grpc/support/port_platform.h>

#include <limits>

#if __APPLE__

#include <TargetConditionals.h>
#endif

#include <grpc/impl/grpc_types.h>
#include <grpc/support/atm.h>
#include <grpc/support/cpu.h>
#include <grpc/support/time.h>

#include "absl/log/check.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/fork.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/time.h"
#include "src/core/util/time_precise.h"

#if !defined(_WIN32) || !defined(_DLL)
#define EXEC_CTX exec_ctx_
#define CALLBACK_EXEC_CTX callback_exec_ctx_
#else
#define EXEC_CTX exec_ctx()
#define CALLBACK_EXEC_CTX callback_exec_ctx()
#endif

typedef struct grpc_combiner grpc_combiner;

#define GRPC_EXEC_CTX_FLAG_IS_FINISHED 1

#define GRPC_EXEC_CTX_FLAG_THREAD_RESOURCE_LOOP 2

#define GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD 4

#define GRPC_APP_CALLBACK_EXEC_CTX_FLAG_IS_INTERNAL_THREAD 1

namespace grpc_core {
class Combiner;

class GRPC_DLL ExecCtx : public latent_see::ParentScope {
 public:

  ExecCtx()
      : latent_see::ParentScope(GRPC_LATENT_SEE_METADATA("ExecCtx")),
        flags_(GRPC_EXEC_CTX_FLAG_IS_FINISHED) {
    Fork::IncExecCtxCount();
    Set(this);
  }

  explicit ExecCtx(uintptr_t fl)
      : ExecCtx(fl, GRPC_LATENT_SEE_METADATA("ExecCtx")) {}

  explicit ExecCtx(uintptr_t fl, latent_see::Metadata* latent_see_metadata)
      : latent_see::ParentScope(latent_see_metadata), flags_(fl) {
    if (!(GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD & flags_)) {
      Fork::IncExecCtxCount();
    }
    Set(this);
  }

  virtual ~ExecCtx() {
    flags_ |= GRPC_EXEC_CTX_FLAG_IS_FINISHED;
    Flush();
    Set(last_exec_ctx_);
    if (!(GRPC_EXEC_CTX_FLAG_IS_INTERNAL_THREAD & flags_)) {
      Fork::DecExecCtxCount();
    }
  }

  ExecCtx(const ExecCtx&) = delete;
  ExecCtx& operator=(const ExecCtx&) = delete;

  struct CombinerData {

    Combiner* active_combiner;

    Combiner* last_combiner;
  };

  CombinerData* combiner_data() { return &combiner_data_; }

  grpc_closure_list* closure_list() { return &closure_list_; }

  uintptr_t flags() { return flags_; }

  bool HasWork() {
    return combiner_data_.active_combiner != nullptr ||
           !grpc_closure_list_empty(closure_list_);
  }

  bool Flush();

  bool IsReadyToFinish() {
    if ((flags_ & GRPC_EXEC_CTX_FLAG_IS_FINISHED) == 0) {
      if (CheckReadyToFinish()) {
        flags_ |= GRPC_EXEC_CTX_FLAG_IS_FINISHED;
        return true;
      }
      return false;
    } else {
      return true;
    }
  }

  void SetReadyToFinishFlag() { flags_ |= GRPC_EXEC_CTX_FLAG_IS_FINISHED; }

  Timestamp Now() { return Timestamp::Now(); }

  void InvalidateNow() {
    if (time_cache_.has_value()) time_cache_->InvalidateCache();
  }

  void SetNowIomgrShutdown() {

    TestOnlySetNow(Timestamp::InfFuture());
  }

  void TestOnlySetNow(Timestamp now) {
    if (!time_cache_.has_value()) time_cache_.emplace();
    time_cache_->TestOnlySetNow(now);
  }

  static ExecCtx* Get() { return EXEC_CTX; }

  static void Run(const DebugLocation& location, grpc_closure* closure,
                  grpc_error_handle error);

  static void RunList(const DebugLocation& location, grpc_closure_list* list);

 protected:

  virtual bool CheckReadyToFinish() { return false; }

  static void operator delete(void* ) { abort(); }

 private:

  static void Set(ExecCtx* ctx) { EXEC_CTX = ctx; }

  grpc_closure_list closure_list_ = GRPC_CLOSURE_LIST_INIT;
  CombinerData combiner_data_ = {nullptr, nullptr};
  uintptr_t flags_;

  std::optional<ScopedTimeCache> time_cache_;

#if !defined(_WIN32) || !defined(_DLL)
  static thread_local ExecCtx* exec_ctx_;
#else

  static ExecCtx*& exec_ctx();
#endif
  ExecCtx* last_exec_ctx_ = Get();
};

template <typename F>
void EnsureRunInExecCtx(F f) {
  if (ExecCtx::Get() == nullptr) {
    ExecCtx exec_ctx;
    f();
  } else {
    f();
  }
}

#undef EXEC_CTX
#undef CALLBACK_EXEC_CTX

}

#endif
