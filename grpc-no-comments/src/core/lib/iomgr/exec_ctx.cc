
// Copyright 2015 gRPC authors.

#include "src/core/lib/iomgr/exec_ctx.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "src/core/lib/iomgr/combiner.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/crash.h"

static void exec_ctx_run(grpc_closure* closure) {
#ifndef NDEBUG
  closure->scheduled = false;
  GRPC_TRACE_VLOG(closure, 2)
      << "running closure " << closure << ": created [" << closure->file_created
      << ":" << closure->line_created
      << "]: " << (closure->run ? "run" : "scheduled") << " ["
      << closure->file_initiated << ":" << closure->line_initiated << "]";
#endif
  grpc_error_handle error =
      grpc_core::internal::StatusMoveFromHeapPtr(closure->error_data.error);
  closure->error_data.error = 0;
  closure->cb(closure->cb_arg, std::move(error));
#ifndef NDEBUG
  GRPC_TRACE_VLOG(closure, 2) << "closure " << closure << " finished";
#endif
}

static void exec_ctx_sched(grpc_closure* closure) {
  grpc_closure_list_append(grpc_core::ExecCtx::Get()->closure_list(), closure);
}

namespace grpc_core {

#if !defined(_WIN32) || !defined(_DLL)
thread_local ExecCtx* ExecCtx::exec_ctx_;
#else
ExecCtx*& ExecCtx::exec_ctx() {
  static thread_local ExecCtx* exec_ctx;
  return exec_ctx;
}

#endif

bool ExecCtx::Flush() {
  bool did_something = false;
  for (;;) {
    if (!grpc_closure_list_empty(closure_list_)) {
      grpc_closure* c = closure_list_.head;
      closure_list_.head = closure_list_.tail = nullptr;
      while (c != nullptr) {
        grpc_closure* next = c->next_data.next;
        did_something = true;
        exec_ctx_run(c);
        c = next;
      }
    } else if (!grpc_combiner_continue_exec_ctx()) {
      break;
    }
  }
  CHECK_EQ(combiner_data_.active_combiner, nullptr);
  return did_something;
}

void ExecCtx::Run(const DebugLocation& location, grpc_closure* closure,
                  grpc_error_handle error) {
  (void)location;
  if (closure == nullptr) {
    return;
  }
#ifndef NDEBUG
  if (closure->scheduled) {
    Crash(absl::StrFormat(
        "Closure already scheduled. (closure: %p, created: [%s:%d], "
        "previously scheduled at: [%s: %d], newly scheduled at [%s: %d]",
        closure, closure->file_created, closure->line_created,
        closure->file_initiated, closure->line_initiated, location.file(),
        location.line()));
  }
  closure->scheduled = true;
  closure->file_initiated = location.file();
  closure->line_initiated = location.line();
  closure->run = false;
  CHECK_NE(closure->cb, nullptr);
#endif
  closure->error_data.error = internal::StatusAllocHeapPtr(error);
  exec_ctx_sched(closure);
}

void ExecCtx::RunList(const DebugLocation& location, grpc_closure_list* list) {
  (void)location;
  grpc_closure* c = list->head;
  while (c != nullptr) {
    grpc_closure* next = c->next_data.next;
#ifndef NDEBUG
    if (c->scheduled) {
      Crash(absl::StrFormat(
          "Closure already scheduled. (closure: %p, created: [%s:%d], "
          "previously scheduled at: [%s: %d], newly scheduled at [%s:%d]",
          c, c->file_created, c->line_created, c->file_initiated,
          c->line_initiated, location.file(), location.line()));
    }
    c->scheduled = true;
    c->file_initiated = location.file();
    c->line_initiated = location.line();
    c->run = false;
    CHECK_NE(c->cb, nullptr);
#endif
    exec_ctx_sched(c);
    c = next;
  }
  list->head = list->tail = nullptr;
}

}
