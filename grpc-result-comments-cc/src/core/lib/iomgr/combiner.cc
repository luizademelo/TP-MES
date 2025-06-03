Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/lib/iomgr/combiner.h"

#include <assert.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <inttypes.h>
#include <string.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/iomgr_internal.h"
#include "src/core/util/crash.h"
#include "src/core/util/mpscq.h"

// State flag indicating the combiner is not orphaned
#define STATE_UNORPHANED 1
// State flag used for counting elements (using low bit for counting)
#define STATE_ELEM_COUNT_LOW_BIT 2

// Forward declarations
static void combiner_exec(grpc_core::Combiner* lock, grpc_closure* closure,
                          grpc_error_handle error);
static void combiner_finally_exec(grpc_core::Combiner* lock,
                                  grpc_closure* closure,
                                  grpc_error_handle error);

// Creates a new combiner with the given event engine
grpc_core::Combiner* grpc_combiner_create(
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>
        event_engine) {
  grpc_core::Combiner* lock = new grpc_core::Combiner();
  lock->event_engine = event_engine;
  gpr_ref_init(&lock->refs, 1);  // Initialize reference count to 1
  gpr_atm_no_barrier_store(&lock->state, STATE_UNORPHANED);  // Initial state
  grpc_closure_list_init(&lock->final_list);  // Initialize final closure list
  GRPC_TRACE_LOG(combiner, INFO) << "C:" << lock << " create";
  return lock;
}

// Actually destroys the combiner when reference count reaches zero
static void really_destroy(grpc_core::Combiner* lock) {
  GRPC_TRACE_LOG(combiner, INFO) << "C:" << lock << " really_destroy";
  CHECK_EQ(gpr_atm_no_barrier_load(&lock->state), 0);  // Verify state is 0
  delete lock;
}

// Begins the destruction process of the combiner
static void start_destroy(grpc_core::Combiner* lock) {
  // Atomically decrement the unorphaned state
  gpr_atm old_state = gpr_atm_full_fetch_add(&lock->state, -STATE_UNORPHANED);
  GRPC_TRACE_LOG(combiner, INFO)
      << "C:" << lock << " really_destroy old_state=" << old_state;
  // If this was the last reference, destroy immediately
  if (old_state == 1) {
    really_destroy(lock);
  }
}

// Debug macro for reference counting operations
#ifndef NDEBUG
#define GRPC_COMBINER_DEBUG_SPAM(op, delta)                          \
  GRPC_TRACE_VLOG(combiner, 2).AtLocation(file, line)                \
      << "C:" << lock << " " << (op) << " "                          \
      << gpr_atm_no_barrier_load(&lock->refs.count) << " --> "       \
      << gpr_atm_no_barrier_load(&lock->refs.count) + (delta) << " " \
      << reason;
#else
#define GRPC_COMBINER_DEBUG_SPAM(op, delta)
#endif

// Decrements the combiner's reference count, potentially starting destruction
void grpc_combiner_unref(grpc_core::Combiner* lock GRPC_COMBINER_DEBUG_ARGS) {
  GRPC_COMBINER_DEBUG_SPAM("UNREF", -1);
  if (gpr_unref(&lock->refs)) {  // If reference count reaches zero
    start_destroy(lock);
  }
}

// Increments the combiner's reference count
grpc_core::Combiner* grpc_combiner_ref(
    grpc_core::Combiner* lock GRPC_COMBINER_DEBUG_ARGS) {
  GRPC_COMBINER_DEBUG_SPAM("  REF", 1);
  gpr_ref(&lock->refs);
  return lock;
}

// Adds the combiner to the end of the execution context's combiner list
static void push_last_on_exec_ctx(grpc_core::Combiner* lock) {
  lock->next_combiner_on_this_exec_ctx = nullptr;
  if (grpc_core::ExecCtx::Get()->combiner_data()->active_combiner == nullptr) {
    // If no active combiner, this becomes both first and last
    grpc_core::ExecCtx::Get()->combiner_data()->active_combiner =
        grpc_core::ExecCtx::Get()->combiner_data()->last_combiner = lock;
  } else {
    // Otherwise append to the end
    grpc_core::ExecCtx::Get()
        ->combiner_data()
        ->last_combiner->next_combiner_on_this_exec_ctx = lock;
    grpc_core::ExecCtx::Get()->combiner_data()->last_combiner = lock;
  }
}

// Adds the combiner to the beginning of the execution context's combiner list
static void push_first_on_exec_ctx(grpc_core::Combiner* lock) {
  lock->next_combiner_on_this_exec_ctx =
      grpc_core::ExecCtx::Get()->combiner_data()->active_combiner;
  grpc_core::ExecCtx::Get()->combiner_data()->active_combiner = lock;
  if (lock->next_combiner_on_this_exec_ctx == nullptr) {
    // If list was empty, this is also the last combiner
    grpc_core::ExecCtx::Get()->combiner_data()->last_combiner = lock;
  }
}

// Executes a closure on the combiner
static void combiner_exec(grpc_core::Combiner* lock, grpc_closure* cl,
                          grpc_error_handle error) {
  // Atomically increment the element count
  gpr_atm last = gpr_atm_full_fetch_add(&lock->state, STATE_ELEM_COUNT_LOW_BIT);
  GRPC_TRACE_LOG(combiner, INFO)
      << "C:" << lock << " grpc_combiner_execute c=" << cl << " last=" << last;
  
  if (last == 1) {
    // First element - store current execution context
    gpr_atm_no_barrier_store(
        &lock->initiating_exec_ctx_or_null,
        reinterpret_cast<gpr_atm>(grpc_core::ExecCtx::Get()));

    push_last_on_exec_ctx(lock);  // Add to execution context
  } else {
    // Subsequent elements - check if execution context changed
    gpr_atm initiator =
        gpr_atm_no_barrier_load(&lock->initiating_exec_ctx_or_null);
    if (initiator != 0 &&
        initiator != reinterpret_cast<gpr_atm>(grpc_core::ExecCtx::Get())) {
      gpr_atm_no_barrier_store(&lock->initiating_exec_ctx_or_null, 0);
    }
  }
  
  CHECK(last & STATE_UNORPHANED);  // Verify combiner is not orphaned
  assert(cl->cb);  // Closure must have a callback
  cl->error_data.error = grpc_core::internal::StatusAllocHeapPtr(error);
  lock->queue.Push(cl->next_data.mpscq_node.get());  // Add to queue
}

// Moves to the next combiner in the execution context
static void move_next() {
  grpc_core::ExecCtx::Get()->combiner_data()->active_combiner =
      grpc_core::ExecCtx::Get()
          ->combiner_data()
          ->active_combiner->next_combiner_on_this_exec_ctx;
  if (grpc_core::ExecCtx::Get()->combiner_data()->active_combiner == nullptr) {
    grpc_core::ExecCtx::Get()->combiner_data()->last_combiner = nullptr;
  }
}

// Offloads the combiner's work to the event engine
static void queue_offload(grpc_core::Combiner* lock) {
  move_next();  // Move to next combiner

  gpr_atm_no_barrier_store(&lock->initiating_exec_ctx_or_null, 1);
  GRPC_TRACE_LOG(combiner, INFO) << "C:" << lock << " queue_offload";
  // Schedule work on event engine
  lock->event_engine->Run([lock] {
    grpc_core::ExecCtx exec_ctx(0);
    push_last_on_exec_ctx(lock);  // Re-add to execution context
    exec_ctx.Flush();  // Execute pending work
  });
}

// Continues execution of pending work in the combiner
bool grpc_combiner_continue_exec_ctx() {
  GRPC_LATENT_SEE_PARENT_SCOPE("grpc_combiner_continue_exec_ctx");

  grpc_core::Combiner* lock =
      grpc_core::ExecCtx::Get()->combiner_data()->active_combiner;
  if (lock == nullptr) {
    return false;  // No work to do
  }

  // Check if this combiner is contended (being used by another execution context)
  bool contended =
      gpr_atm_no_barrier_load(&lock->initiating_exec_ctx_or_null) == 0;

  GRPC_TRACE_LOG(combiner, INFO)
      << "C:" << lock << " grpc_combiner_continue_exec_ctx "
      << "contended=" << contended << " exec_ctx_ready_to_finish="
      << grpc_core::ExecCtx::Get()->IsReadyToFinish()
      << " time_to_execute_final_list=" << lock->time_to_execute_final_list;

  // If contended and ready to finish, offload the work
  if (contended && grpc_core::ExecCtx::Get()->IsReadyToFinish()) {
    queue_offload(lock);
    return true;
  }

  // Process either the regular queue or final list based on conditions
  if (!lock->time_to_execute_final_list ||
      (gpr_atm_acq_load(&lock->state) >> 1) > 1) {
    // Process regular queue
    grpc_core::MultiProducerSingleConsumerQueue::Node* n = lock->queue.Pop();
    GRPC_TRACE_LOG(combiner, INFO)
        << "C:" << lock << " maybe_finish_one n=" << n;

    if (n == nullptr) {
      // Queue empty, offload
      queue_offload(lock);
      return true;
    }
    grpc_closure* cl = reinterpret_cast<grpc_closure*>(n);
#ifndef NDEBUG
    cl->scheduled = false;
#endif
    // Execute the closure
    grpc_error_handle cl_err =
        grpc_core::internal::StatusMoveFromHeapPtr(cl->error_data.error);
    cl->error_data.error = 0;
    cl->cb(cl->cb_arg, std::move(cl_err));
  } else {
    // Process final list
    grpc_closure* c = lock->final_list.head;
    CHECK_NE(c, nullptr);
    grpc_closure_list_init(&lock->final_list);
    int loops = 0;
    while (c != nullptr) {
      GRPC_TRACE_LOG(combiner, INFO)
          << "C:" << lock << " execute_final[" << loops << "] c=" << c;
      grpc_closure* next = c->next_data.next;
#ifndef NDEBUG
      c->scheduled = false;
#endif
      grpc_error_handle error =
          grpc_core::internal::StatusMoveFromHeapPtr(c->error_data.error);
      c->error_data.error = 0;
      c->cb(c->cb_arg, std::move(error));
      c = next;
    }
  }

  move_next();  // Move to next combiner
  lock->time_to_execute_final_list = false;
  // Atomically decrement the element count
  gpr_atm old_state =
      gpr_atm_full_fetch_add(&lock->state, -STATE_ELEM_COUNT_LOW_BIT);
  GRPC_TRACE_LOG(combiner, INFO)
      << "C:" << lock << " finish old_state=" << old_state;

// Helper macro for state checking
#define OLD_STATE_WAS(orphaned, elem_count) \
  (((orphaned) ? 0 : STATE_UNORPHANED) |    \
   ((elem_count) * STATE_ELEM_COUNT_LOW_BIT))

  // Handle different state transitions
  switch (old_state) {
    default:
      // No special handling for most states
      break;
    case OLD_STATE_WAS(false, 2):
    case OLD_STATE_WAS(true, 2):
      // If we have final items to execute, schedule them
      if (!grpc_closure_list_empty(lock->final_list)) {
        lock->time_to_execute_final_list = true;
      }
      break;
    case OLD_STATE_WAS(false, 1):
      // Last element in non-orphaned state
      return true;
    case OLD_STATE_WAS(true, 1):
      // Last element in orphaned state - destroy
      really_destroy(lock);
      return true;
    case OLD_STATE_WAS(false, 0):
    case OLD_STATE_WAS(true, 0):
      // Shouldn't happen
      GPR_UNREACHABLE_CODE(return true);
  }
  push_first_on_exec_ctx(lock);  // Keep processing
  return true;
}

// Helper function for finally execution
static void enqueue_finally(void* closure, grpc_error_handle error);

// Executes a closure in the "finally" phase of the combiner
static void combiner_finally_exec(grpc_core::Combiner* lock,
                                  grpc_closure* closure,
                                  grpc_error_handle error) {
  CHECK_NE(lock, nullptr);
  GRPC_TRACE_LOG(combiner, INFO)
      << "C:" << lock << " grpc_combiner_execute_finally c=" << closure
      << "; ac=" << grpc_core::ExecCtx::Get()->combiner_data()->active_combiner;
  
  // If not the active combiner, enqueue via regular execution
  if (grpc_core::ExecCtx::Get()->combiner_data()->active_combiner != lock) {
    closure->error_data.scratch = reinterpret_cast<uintptr_t>(lock);
    lock->Run(GRPC_CLOSURE_CREATE(enqueue_finally, closure, nullptr), error);
    return;
  }

  // Add to final list
  if (grpc_closure_list_empty(lock->final_list)) {
    gpr_atm_full_fetch_add(&lock->state, STATE_ELEM_COUNT_LOW_BIT);
  }
  grpc_closure_list_append(&lock->final_list, closure, error);
}

// Enqueues a finally closure for execution
static void enqueue_finally(void* closure, grpc_error_handle error) {
  grpc_closure* cl = static_cast<grpc_closure*>(closure);
  grpc_core::Combiner* lock =
      reinterpret_cast<grpc_core::Combiner*>(cl->error_data.scratch);
  cl->error_data.scratch = 0;
  combiner_finally_exec(lock, cl, error);
}

namespace grpc_core {
// Combiner method implementations

// Runs a closure on this combiner
void Combiner::Run(grpc_closure* closure, grpc_error_handle error) {
  combiner_exec(this, closure, error);
}

// Runs a closure in the finally phase of this combiner
void Combiner::FinallyRun(grpc_closure* closure, grpc_error_handle error) {
  combiner_finally_exec(this, closure, error);
}

// Forces the combiner to offload its work
void Combiner::ForceOffload() {
  gpr_atm_no_barrier_store(&initiating_exec_ctx_or_null, 0);
  ExecCtx::Get()->SetReadyToFinishFlag();
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each function and major code block
2. The combiner's state management and reference counting
3. The execution flow of closures through the combiner
4. The difference between regular execution and finally execution
5. The offloading mechanism to the event engine
6. The combiner's integration with the execution context

Key concepts highlighted:
- The combiner acts as a synchronization mechanism for gRPC operations
- It manages a queue of closures to execute
- It handles both regular and "finally" phase executions
- It can offload work to avoid blocking the main thread
- It maintains state to track orphaned status and work items