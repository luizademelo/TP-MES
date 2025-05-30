
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_CLOSURE_H
#define GRPC_SRC_CORE_LIB_IOMGR_CLOSURE_H

#include <assert.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/crash.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/manual_constructor.h"
#include "src/core/util/mpscq.h"

struct grpc_closure;
typedef struct grpc_closure grpc_closure;

typedef struct grpc_closure_list {
  grpc_closure* head;
  grpc_closure* tail;
} grpc_closure_list;

typedef void (*grpc_iomgr_cb_func)(void* arg, grpc_error_handle error);

struct grpc_closure {

  union {
    grpc_closure* next;
    grpc_core::ManualConstructor<
        grpc_core::MultiProducerSingleConsumerQueue::Node>
        mpscq_node;
    uintptr_t scratch;
  } next_data;

  grpc_iomgr_cb_func cb;

  void* cb_arg;

  union {
    uintptr_t error;
    uintptr_t scratch;
  } error_data;

#ifndef NDEBUG
  bool scheduled;
  bool run;
  const char* file_created;
  int line_created;
  const char* file_initiated;
  int line_initiated;
#endif

  std::string DebugString() const;
};

#ifndef NDEBUG
inline grpc_closure* grpc_closure_init(const char* file, int line,
                                       grpc_closure* closure,
                                       grpc_iomgr_cb_func cb, void* cb_arg) {
#else
inline grpc_closure* grpc_closure_init(grpc_closure* closure,
                                       grpc_iomgr_cb_func cb, void* cb_arg) {
#endif
  closure->cb = cb;
  closure->cb_arg = cb_arg;
  closure->error_data.error = 0;
#ifndef NDEBUG
  closure->scheduled = false;
  closure->file_initiated = nullptr;
  closure->line_initiated = 0;
  closure->run = false;
  closure->file_created = file;
  closure->line_created = line;
#endif
  return closure;
}

#ifndef NDEBUG
#define GRPC_CLOSURE_INIT(closure, cb, cb_arg, scheduler) \
  grpc_closure_init(__FILE__, __LINE__, closure, cb, cb_arg)
#else
#define GRPC_CLOSURE_INIT(closure, cb, cb_arg, scheduler) \
  grpc_closure_init(closure, cb, cb_arg)
#endif

namespace grpc_core {
template <typename T, void (T::*cb)(grpc_error_handle)>
grpc_closure MakeMemberClosure(T* p, DebugLocation location = DebugLocation()) {
  grpc_closure out;
  GRPC_CLOSURE_INIT(
      &out, [](void* p, grpc_error_handle e) { (static_cast<T*>(p)->*cb)(e); },
      p, nullptr);
#ifndef NDEBUG
  out.file_created = location.file();
  out.line_created = location.line();
#else
  (void)location;
#endif
  return out;
}

template <typename T, void (T::*cb)()>
grpc_closure MakeMemberClosure(T* p, DebugLocation location = DebugLocation()) {
  grpc_closure out;
  GRPC_CLOSURE_INIT(
      &out, [](void* p, grpc_error_handle) { (static_cast<T*>(p)->*cb)(); }, p,
      nullptr);
#ifndef NDEBUG
  out.file_created = location.file();
  out.line_created = location.line();
#else
  (void)location;
#endif
  return out;
}

template <typename F>
grpc_closure* NewClosure(F f) {
  struct Closure : public grpc_closure {
    explicit Closure(F f) : f(std::move(f)) {}
    F f;
    static void Run(void* arg, grpc_error_handle error) {
      auto self = static_cast<Closure*>(arg);
      self->f(error);
      delete self;
    }
  };
  Closure* c = new Closure(std::move(f));
  GRPC_CLOSURE_INIT(c, Closure::Run, c, nullptr);
  return c;
}
}

namespace closure_impl {

struct wrapped_closure {
  grpc_iomgr_cb_func cb;
  void* cb_arg;
  grpc_closure wrapper;
};
inline void closure_wrapper(void* arg, grpc_error_handle error) {
  wrapped_closure* wc = static_cast<wrapped_closure*>(arg);
  grpc_iomgr_cb_func cb = wc->cb;
  void* cb_arg = wc->cb_arg;
  gpr_free(wc);
  cb(cb_arg, error);
}

}

#ifndef NDEBUG
inline grpc_closure* grpc_closure_create(const char* file, int line,
                                         grpc_iomgr_cb_func cb, void* cb_arg) {
#else
inline grpc_closure* grpc_closure_create(grpc_iomgr_cb_func cb, void* cb_arg) {
#endif
  closure_impl::wrapped_closure* wc =
      static_cast<closure_impl::wrapped_closure*>(gpr_malloc(sizeof(*wc)));
  wc->cb = cb;
  wc->cb_arg = cb_arg;
#ifndef NDEBUG
  grpc_closure_init(file, line, &wc->wrapper, closure_impl::closure_wrapper,
                    wc);
#else
  grpc_closure_init(&wc->wrapper, closure_impl::closure_wrapper, wc);
#endif
  return &wc->wrapper;
}

#ifndef NDEBUG
#define GRPC_CLOSURE_CREATE(cb, cb_arg, scheduler) \
  grpc_closure_create(__FILE__, __LINE__, cb, cb_arg)
#else
#define GRPC_CLOSURE_CREATE(cb, cb_arg, scheduler) \
  grpc_closure_create(cb, cb_arg)
#endif

#define GRPC_CLOSURE_LIST_INIT {nullptr, nullptr}

inline void grpc_closure_list_init(grpc_closure_list* closure_list) {
  closure_list->head = closure_list->tail = nullptr;
}

inline bool grpc_closure_list_append(grpc_closure_list* closure_list,
                                     grpc_closure* closure) {
  if (closure == nullptr) {
    return false;
  }
  closure->next_data.next = nullptr;
  bool was_empty = (closure_list->head == nullptr);
  if (was_empty) {
    closure_list->head = closure;
  } else {
    closure_list->tail->next_data.next = closure;
  }
  closure_list->tail = closure;
  return was_empty;
}

inline bool grpc_closure_list_append(grpc_closure_list* closure_list,
                                     grpc_closure* closure,
                                     grpc_error_handle error) {
  if (closure == nullptr) {
    return false;
  }
  closure->error_data.error = grpc_core::internal::StatusAllocHeapPtr(error);
  return grpc_closure_list_append(closure_list, closure);
}

inline void grpc_closure_list_fail_all(grpc_closure_list* list,
                                       grpc_error_handle forced_failure) {
  for (grpc_closure* c = list->head; c != nullptr; c = c->next_data.next) {
    if (c->error_data.error == 0) {
      c->error_data.error =
          grpc_core::internal::StatusAllocHeapPtr(forced_failure);
    }
  }
}

inline void grpc_closure_list_move(grpc_closure_list* src,
                                   grpc_closure_list* dst) {
  if (src->head == nullptr) {
    return;
  }
  if (dst->head == nullptr) {
    *dst = *src;
  } else {
    dst->tail->next_data.next = src->head;
    dst->tail = src->tail;
  }
  src->head = src->tail = nullptr;
}

inline bool grpc_closure_list_empty(grpc_closure_list closure_list) {
  return closure_list.head == nullptr;
}

namespace grpc_core {
class Closure {
 public:
  static void Run(const DebugLocation& location, grpc_closure* closure,
                  grpc_error_handle error) {
    (void)location;
    if (closure == nullptr) {
      return;
    }
#ifndef NDEBUG
    GRPC_TRACE_VLOG(closure, 2)
        << "running closure " << closure << ": created ["
        << closure->file_created << ":" << closure->line_created << "]: run ["
        << location.file() << ":" << location.line() << "]";
    CHECK_NE(closure->cb, nullptr);
#endif
    closure->cb(closure->cb_arg, error);
#ifndef NDEBUG
    GRPC_TRACE_VLOG(closure, 2) << "closure " << closure << " finished";
#endif
  }
};
}

#endif
