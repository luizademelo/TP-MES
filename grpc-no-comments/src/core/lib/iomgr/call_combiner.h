
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_CALL_COMBINER_H
#define GRPC_SRC_CORE_LIB_IOMGR_CALL_COMBINER_H

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/container/inlined_vector.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/dynamic_annotations.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/util/mpscq.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class CallCombiner {
 public:
  CallCombiner();
  ~CallCombiner();

#ifndef NDEBUG
#define GRPC_CALL_COMBINER_START(call_combiner, closure, error, reason) \
  (call_combiner)->Start((closure), (error), __FILE__, __LINE__, (reason))
#define GRPC_CALL_COMBINER_STOP(call_combiner, reason) \
  (call_combiner)->Stop(__FILE__, __LINE__, (reason))

  void Start(grpc_closure* closure, grpc_error_handle error, const char* file,
             int line, const char* reason);

  void Stop(const char* file, int line, const char* reason);
#else
#define GRPC_CALL_COMBINER_START(call_combiner, closure, error, reason) \
  (call_combiner)->Start((closure), (error), (reason))
#define GRPC_CALL_COMBINER_STOP(call_combiner, reason) \
  (call_combiner)->Stop((reason))

  void Start(grpc_closure* closure, grpc_error_handle error,
             const char* reason);

  void Stop(const char* reason);
#endif

  void SetNotifyOnCancel(grpc_closure* closure);

  void Cancel(grpc_error_handle error);

 private:
  void ScheduleClosure(grpc_closure* closure, grpc_error_handle error);
#ifdef GRPC_TSAN_ENABLED
  static void TsanClosure(void* arg, grpc_error_handle error);
#endif

  gpr_atm size_ = 0;
  MultiProducerSingleConsumerQueue queue_;

  gpr_atm cancel_state_ = 0;
#ifdef GRPC_TSAN_ENABLED

  struct TsanLock : public RefCounted<TsanLock, NonPolymorphicRefCount> {
    TsanLock() { TSAN_ANNOTATE_RWLOCK_CREATE(&taken); }
    ~TsanLock() { TSAN_ANNOTATE_RWLOCK_DESTROY(&taken); }

    std::atomic<bool> taken{false};
  };
  RefCountedPtr<TsanLock> tsan_lock_ = MakeRefCounted<TsanLock>();
  grpc_closure tsan_closure_;
  grpc_closure* original_closure_;
#endif
};

class CallCombinerClosureList {
 public:
  CallCombinerClosureList() {}

  void Add(grpc_closure* closure, grpc_error_handle error, const char* reason) {
    closures_.emplace_back(closure, error, reason);
  }

  void RunClosures(CallCombiner* call_combiner) {
    if (closures_.empty()) {
      GRPC_CALL_COMBINER_STOP(call_combiner, "no closures to schedule");
      return;
    }
    for (size_t i = 1; i < closures_.size(); ++i) {
      auto& closure = closures_[i];
      GRPC_CALL_COMBINER_START(call_combiner, closure.closure, closure.error,
                               closure.reason);
    }
    GRPC_TRACE_LOG(call_combiner, INFO)
        << "CallCombinerClosureList executing closure while already "
           "holding call_combiner "
        << call_combiner << ": closure=" << closures_[0].closure->DebugString()
        << " error=" << StatusToString(closures_[0].error)
        << " reason=" << closures_[0].reason;

    ExecCtx::Run(DEBUG_LOCATION, closures_[0].closure, closures_[0].error);
    closures_.clear();
  }

  void RunClosuresWithoutYielding(CallCombiner* call_combiner) {
    for (size_t i = 0; i < closures_.size(); ++i) {
      auto& closure = closures_[i];
      GRPC_CALL_COMBINER_START(call_combiner, closure.closure, closure.error,
                               closure.reason);
    }
    closures_.clear();
  }

  size_t size() const { return closures_.size(); }

 private:
  struct CallCombinerClosure {
    grpc_closure* closure;
    grpc_error_handle error;
    const char* reason;

    CallCombinerClosure(grpc_closure* closure, grpc_error_handle error,
                        const char* reason)
        : closure(closure), error(error), reason(reason) {}
  };

  absl::InlinedVector<CallCombinerClosure, 6> closures_;
};

}

#endif
