
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_COMBINER_H
#define GRPC_SRC_CORE_LIB_IOMGR_COMBINER_H

#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"

namespace grpc_core {

class Combiner {
 public:
  void Run(grpc_closure* closure, grpc_error_handle error);

  void FinallyRun(grpc_closure* closure, grpc_error_handle error);

  void ForceOffload();
  Combiner* next_combiner_on_this_exec_ctx = nullptr;
  MultiProducerSingleConsumerQueue queue;

  gpr_atm initiating_exec_ctx_or_null;

  gpr_atm state;
  bool time_to_execute_final_list = false;
  grpc_closure_list final_list;

  grpc_closure offload;
  gpr_refcount refs;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine;
};
}

grpc_core::Combiner* grpc_combiner_create(
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine);

#ifndef NDEBUG
#define GRPC_COMBINER_DEBUG_ARGS \
  , const char *file, int line, const char *reason
#define GRPC_COMBINER_REF(combiner, reason) \
  grpc_combiner_ref((combiner), __FILE__, __LINE__, (reason))
#define GRPC_COMBINER_UNREF(combiner, reason) \
  grpc_combiner_unref((combiner), __FILE__, __LINE__, (reason))
#else
#define GRPC_COMBINER_DEBUG_ARGS
#define GRPC_COMBINER_REF(combiner, reason) grpc_combiner_ref((combiner))
#define GRPC_COMBINER_UNREF(combiner, reason) grpc_combiner_unref((combiner))
#endif

grpc_core::Combiner* grpc_combiner_ref(
    grpc_core::Combiner* lock GRPC_COMBINER_DEBUG_ARGS);
void grpc_combiner_unref(grpc_core::Combiner* lock GRPC_COMBINER_DEBUG_ARGS);

bool grpc_combiner_continue_exec_ctx();

#endif
