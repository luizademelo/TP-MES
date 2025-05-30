
// Copyright 2015-2016 gRPC authors.

#include "src/core/lib/surface/completion_queue.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/atm.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <stdio.h>

#include <algorithm>
#include <atomic>
#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/lib/event_engine/shim.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/surface/event_string.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/atomic_utils.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/spinlock.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"

namespace {

// NOTE: Only one event will ever be cached.
thread_local grpc_cq_completion* g_cached_event;
thread_local grpc_completion_queue* g_cached_cq;

struct plucker {
  grpc_pollset_worker** worker;
  void* tag;
};
struct cq_poller_vtable {
  bool (*can_get_pollset)();
  bool can_listen;
  size_t (*size)(void);
  void (*init)(grpc_pollset* pollset, gpr_mu** mu);
  grpc_error_handle (*kick)(grpc_pollset* pollset,
                            grpc_pollset_worker* specific_worker);
  grpc_error_handle (*work)(grpc_pollset* pollset, grpc_pollset_worker** worker,
                            grpc_core::Timestamp deadline);
  void (*shutdown)(grpc_pollset* pollset, grpc_closure* closure);
  void (*destroy)(grpc_pollset* pollset);
};
typedef struct non_polling_worker {
  gpr_cv cv;
  bool kicked;
  struct non_polling_worker* next;
  struct non_polling_worker* prev;
} non_polling_worker;

struct non_polling_poller {
  gpr_mu mu;
  bool kicked_without_poller;
  non_polling_worker* root;
  grpc_closure* shutdown;
};
size_t non_polling_poller_size(void) { return sizeof(non_polling_poller); }

void non_polling_poller_init(grpc_pollset* pollset, gpr_mu** mu) {
  non_polling_poller* npp = reinterpret_cast<non_polling_poller*>(pollset);
  gpr_mu_init(&npp->mu);
  *mu = &npp->mu;
}

void non_polling_poller_destroy(grpc_pollset* pollset) {
  non_polling_poller* npp = reinterpret_cast<non_polling_poller*>(pollset);
  gpr_mu_destroy(&npp->mu);
}

grpc_error_handle non_polling_poller_work(grpc_pollset* pollset,
                                          grpc_pollset_worker** worker,
                                          grpc_core::Timestamp deadline) {
  non_polling_poller* npp = reinterpret_cast<non_polling_poller*>(pollset);
  if (npp->shutdown) return absl::OkStatus();
  if (npp->kicked_without_poller) {
    npp->kicked_without_poller = false;
    return absl::OkStatus();
  }
  non_polling_worker w;
  gpr_cv_init(&w.cv);
  if (worker != nullptr) *worker = reinterpret_cast<grpc_pollset_worker*>(&w);
  if (npp->root == nullptr) {
    npp->root = w.next = w.prev = &w;
  } else {
    w.next = npp->root;
    w.prev = w.next->prev;
    w.next->prev = w.prev->next = &w;
  }
  w.kicked = false;
  gpr_timespec deadline_ts = deadline.as_timespec(GPR_CLOCK_MONOTONIC);
  while (!npp->shutdown && !w.kicked &&
         !gpr_cv_wait(&w.cv, &npp->mu, deadline_ts)) {
  }
  grpc_core::ExecCtx::Get()->InvalidateNow();
  if (&w == npp->root) {
    npp->root = w.next;
    if (&w == npp->root) {
      if (npp->shutdown) {
        grpc_core::ExecCtx::Run(DEBUG_LOCATION, npp->shutdown,
                                absl::OkStatus());
      }
      npp->root = nullptr;
    }
  }
  w.next->prev = w.prev;
  w.prev->next = w.next;
  gpr_cv_destroy(&w.cv);
  if (worker != nullptr) *worker = nullptr;
  return absl::OkStatus();
}

grpc_error_handle non_polling_poller_kick(
    grpc_pollset* pollset, grpc_pollset_worker* specific_worker) {
  non_polling_poller* p = reinterpret_cast<non_polling_poller*>(pollset);
  if (specific_worker == nullptr) {
    specific_worker = reinterpret_cast<grpc_pollset_worker*>(p->root);
  }
  if (specific_worker != nullptr) {
    non_polling_worker* w =
        reinterpret_cast<non_polling_worker*>(specific_worker);
    if (!w->kicked) {
      w->kicked = true;
      gpr_cv_signal(&w->cv);
    }
  } else {
    p->kicked_without_poller = true;
  }
  return absl::OkStatus();
}

void non_polling_poller_shutdown(grpc_pollset* pollset, grpc_closure* closure) {
  non_polling_poller* p = reinterpret_cast<non_polling_poller*>(pollset);
  CHECK_NE(closure, nullptr);
  p->shutdown = closure;
  if (p->root == nullptr) {
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, closure, absl::OkStatus());
  } else {
    non_polling_worker* w = p->root;
    do {
      gpr_cv_signal(&w->cv);
      w = w->next;
    } while (w != p->root);
  }
}

bool non_polling_poller_can_never_get_pollset() { return false; }

bool maybe_event_engine_poller_can_get_pollset() {
  return !grpc_event_engine::experimental::UsePollsetAlternative();
}

size_t maybe_event_engine_poller_size(void) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    return non_polling_poller_size();
  } else {
    return grpc_pollset_size();
  }
}

void maybe_event_engine_poller_init(grpc_pollset* pollset, gpr_mu** mu) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    non_polling_poller_init(pollset, mu);
  } else {
    grpc_pollset_init(pollset, mu);
  }
}

void maybe_event_engine_poller_destroy(grpc_pollset* pollset) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    non_polling_poller_destroy(pollset);
  } else {
    grpc_pollset_destroy(pollset);
  }
}

grpc_error_handle maybe_event_engine_pollset_work(
    grpc_pollset* pollset, grpc_pollset_worker** worker,
    grpc_core::Timestamp deadline) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    return non_polling_poller_work(pollset, worker, deadline);
  } else {
    return grpc_pollset_work(pollset, worker, deadline);
  }
}

grpc_error_handle maybe_event_engine_poller_kick(
    grpc_pollset* pollset, grpc_pollset_worker* specific_worker) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    return non_polling_poller_kick(pollset, specific_worker);
  } else {
    return grpc_pollset_kick(pollset, specific_worker);
  }
}

void maybe_event_engine_poller_shutdown(grpc_pollset* pollset,
                                        grpc_closure* closure) {
  if (grpc_event_engine::experimental::UsePollsetAlternative()) {
    non_polling_poller_shutdown(pollset, closure);
  } else {
    grpc_pollset_shutdown(pollset, closure);
  }
}

const cq_poller_vtable g_poller_vtable_by_poller_type[] = {

    {maybe_event_engine_poller_can_get_pollset, true,
     maybe_event_engine_poller_size, maybe_event_engine_poller_init,
     maybe_event_engine_poller_kick, maybe_event_engine_pollset_work,
     maybe_event_engine_poller_shutdown, maybe_event_engine_poller_destroy},

    {maybe_event_engine_poller_can_get_pollset, false,
     maybe_event_engine_poller_size, maybe_event_engine_poller_init,
     maybe_event_engine_poller_kick, maybe_event_engine_pollset_work,
     maybe_event_engine_poller_shutdown, maybe_event_engine_poller_destroy},

    {non_polling_poller_can_never_get_pollset, false, non_polling_poller_size,
     non_polling_poller_init, non_polling_poller_kick, non_polling_poller_work,
     non_polling_poller_shutdown, non_polling_poller_destroy},
};

}

struct cq_vtable {
  grpc_cq_completion_type cq_completion_type;
  size_t data_size;
  void (*init)(void* data, grpc_completion_queue_functor* shutdown_callback);
  void (*shutdown)(grpc_completion_queue* cq);
  void (*destroy)(void* data);
  bool (*begin_op)(grpc_completion_queue* cq, void* tag);
  void (*end_op)(grpc_completion_queue* cq, void* tag, grpc_error_handle error,
                 void (*done)(void* done_arg, grpc_cq_completion* storage),
                 void* done_arg, grpc_cq_completion* storage, bool internal);
  grpc_event (*next)(grpc_completion_queue* cq, gpr_timespec deadline,
                     void* reserved);
  grpc_event (*pluck)(grpc_completion_queue* cq, void* tag,
                      gpr_timespec deadline, void* reserved);
};

namespace {

class CqEventQueue {
 public:
  CqEventQueue() = default;
  ~CqEventQueue() = default;

  // Note: The counter is not incremented/decremented atomically with push/pop.

  intptr_t num_items() const {
    return num_queue_items_.load(std::memory_order_relaxed);
  }

  bool Push(grpc_cq_completion* c);
  grpc_cq_completion* Pop();

 private:

  gpr_spinlock queue_lock_ = GPR_SPINLOCK_INITIALIZER;

  grpc_core::MultiProducerSingleConsumerQueue queue_;

  std::atomic<intptr_t> num_queue_items_{0};
};

struct cq_next_data {
  ~cq_next_data() {
    CHECK_EQ(queue.num_items(), 0);
#ifndef NDEBUG
    if (pending_events.load(std::memory_order_acquire) != 0) {
      LOG(ERROR) << "Destroying CQ without draining it fully.";
    }
#endif
  }

  CqEventQueue queue;

  std::atomic<intptr_t> things_queued_ever{0};

  std::atomic<intptr_t> pending_events{1};

  bool shutdown_called = false;
};

struct cq_pluck_data {
  cq_pluck_data() {
    completed_tail = &completed_head;
    completed_head.next = reinterpret_cast<uintptr_t>(completed_tail);
  }

  ~cq_pluck_data() {
    CHECK(completed_head.next == reinterpret_cast<uintptr_t>(&completed_head));
#ifndef NDEBUG
    if (pending_events.load(std::memory_order_acquire) != 0) {
      LOG(ERROR) << "Destroying CQ without draining it fully.";
    }
#endif
  }

  grpc_cq_completion completed_head;
  grpc_cq_completion* completed_tail;

  std::atomic<intptr_t> pending_events{1};

  std::atomic<intptr_t> things_queued_ever{0};

  std::atomic<bool> shutdown{false};

  bool shutdown_called = false;

  int num_pluckers = 0;
  plucker pluckers[GRPC_MAX_COMPLETION_QUEUE_PLUCKERS];
};

struct cq_callback_data {
  explicit cq_callback_data(grpc_completion_queue_functor* shutdown_callback)
      : shutdown_callback(shutdown_callback),
        event_engine(grpc_event_engine::experimental::GetDefaultEventEngine()) {
  }

  ~cq_callback_data() {
#ifndef NDEBUG
    if (pending_events.load(std::memory_order_acquire) != 0) {
      LOG(ERROR) << "Destroying CQ without draining it fully.";
    }
#endif
  }

  std::atomic<intptr_t> pending_events{1};

  bool shutdown_called = false;

  grpc_completion_queue_functor* shutdown_callback;

  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine;
};

}

struct grpc_completion_queue {

  grpc_core::RefCount owning_refs;

  char padding_1[GPR_CACHELINE_SIZE];
  gpr_mu* mu;

  char padding_2[GPR_CACHELINE_SIZE];
  const cq_vtable* vtable;

  char padding_3[GPR_CACHELINE_SIZE];
  const cq_poller_vtable* poller_vtable;

#ifndef NDEBUG
  void** outstanding_tags;
  size_t outstanding_tag_count;
  size_t outstanding_tag_capacity;
#endif

  grpc_closure pollset_shutdown_done;
  int num_polls;
};

static void cq_finish_shutdown_next(grpc_completion_queue* cq);
static void cq_finish_shutdown_pluck(grpc_completion_queue* cq);
static void cq_finish_shutdown_callback(grpc_completion_queue* cq);
static void cq_shutdown_next(grpc_completion_queue* cq);
static void cq_shutdown_pluck(grpc_completion_queue* cq);
static void cq_shutdown_callback(grpc_completion_queue* cq);

static bool cq_begin_op_for_next(grpc_completion_queue* cq, void* tag);
static bool cq_begin_op_for_pluck(grpc_completion_queue* cq, void* tag);
static bool cq_begin_op_for_callback(grpc_completion_queue* cq, void* tag);

static void cq_end_op_for_next(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool internal);

static void cq_end_op_for_pluck(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool internal);

static void cq_end_op_for_callback(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool internal);

static grpc_event cq_next(grpc_completion_queue* cq, gpr_timespec deadline,
                          void* reserved);

static grpc_event cq_pluck(grpc_completion_queue* cq, void* tag,
                           gpr_timespec deadline, void* reserved);

static void cq_init_next(void* data,
                         grpc_completion_queue_functor* shutdown_callback);
static void cq_init_pluck(void* data,
                          grpc_completion_queue_functor* shutdown_callback);
static void cq_init_callback(void* data,
                             grpc_completion_queue_functor* shutdown_callback);
static void cq_destroy_next(void* data);
static void cq_destroy_pluck(void* data);
static void cq_destroy_callback(void* data);

static const cq_vtable g_cq_vtable[] = {

    {GRPC_CQ_NEXT, sizeof(cq_next_data), cq_init_next, cq_shutdown_next,
     cq_destroy_next, cq_begin_op_for_next, cq_end_op_for_next, cq_next,
     nullptr},

    {GRPC_CQ_PLUCK, sizeof(cq_pluck_data), cq_init_pluck, cq_shutdown_pluck,
     cq_destroy_pluck, cq_begin_op_for_pluck, cq_end_op_for_pluck, nullptr,
     cq_pluck},

    {GRPC_CQ_CALLBACK, sizeof(cq_callback_data), cq_init_callback,
     cq_shutdown_callback, cq_destroy_callback, cq_begin_op_for_callback,
     cq_end_op_for_callback, nullptr, nullptr},
};

#define DATA_FROM_CQ(cq) ((void*)((cq) + 1))
#define POLLSET_FROM_CQ(cq) \
  ((grpc_pollset*)((cq)->vtable->data_size + (char*)DATA_FROM_CQ(cq)))

#define GRPC_SURFACE_TRACE_RETURNED_EVENT(cq, event)  \
  do {                                                \
    if (GRPC_TRACE_FLAG_ENABLED(api) &&               \
        (GRPC_TRACE_FLAG_ENABLED(queue_pluck) ||      \
         (event)->type != GRPC_QUEUE_TIMEOUT)) {      \
      LOG(INFO) << "RETURN_EVENT[" << (cq)            \
                << "]: " << grpc_event_string(event); \
    }                                                 \
  } while (0)

static void on_pollset_shutdown_done(void* arg, grpc_error_handle error);

void grpc_completion_queue_thread_local_cache_init(grpc_completion_queue* cq) {
  if (g_cached_cq == nullptr) {
    g_cached_event = nullptr;
    g_cached_cq = cq;
  }
}

int grpc_completion_queue_thread_local_cache_flush(grpc_completion_queue* cq,
                                                   void** tag, int* ok) {
  grpc_cq_completion* storage = g_cached_event;
  int ret = 0;
  if (storage != nullptr && g_cached_cq == cq) {
    *tag = storage->tag;
    grpc_core::ExecCtx exec_ctx;
    *ok = (storage->next & uintptr_t{1}) == 1;
    storage->done(storage->done_arg, storage);
    ret = 1;
    cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);
    if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      GRPC_CQ_INTERNAL_REF(cq, "shutting_down");
      gpr_mu_lock(cq->mu);
      cq_finish_shutdown_next(cq);
      gpr_mu_unlock(cq->mu);
      GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down");
    }
  }
  g_cached_event = nullptr;
  g_cached_cq = nullptr;

  return ret;
}

bool CqEventQueue::Push(grpc_cq_completion* c) {
  queue_.Push(
      reinterpret_cast<grpc_core::MultiProducerSingleConsumerQueue::Node*>(c));
  return num_queue_items_.fetch_add(1, std::memory_order_relaxed) == 0;
}

grpc_cq_completion* CqEventQueue::Pop() {
  grpc_cq_completion* c = nullptr;

  if (gpr_spinlock_trylock(&queue_lock_)) {
    bool is_empty = false;
    c = reinterpret_cast<grpc_cq_completion*>(queue_.PopAndCheckEnd(&is_empty));
    gpr_spinlock_unlock(&queue_lock_);
  }

  if (c) {
    num_queue_items_.fetch_sub(1, std::memory_order_relaxed);
  }

  return c;
}

grpc_completion_queue* grpc_completion_queue_create_internal(
    grpc_cq_completion_type completion_type, grpc_cq_polling_type polling_type,
    grpc_completion_queue_functor* shutdown_callback) {
  grpc_completion_queue* cq;

  GRPC_TRACE_LOG(api, INFO)
      << "grpc_completion_queue_create_internal(completion_type="
      << completion_type << ", polling_type=" << polling_type << ")";

  switch (completion_type) {
    case GRPC_CQ_NEXT:
      grpc_core::global_stats().IncrementCqNextCreates();
      break;
    case GRPC_CQ_PLUCK:
      grpc_core::global_stats().IncrementCqPluckCreates();
      break;
    case GRPC_CQ_CALLBACK:
      grpc_core::global_stats().IncrementCqCallbackCreates();
      break;
  }

  const cq_vtable* vtable = &g_cq_vtable[completion_type];
  const cq_poller_vtable* poller_vtable =
      &g_poller_vtable_by_poller_type[polling_type];

  grpc_core::ExecCtx exec_ctx;

  cq = static_cast<grpc_completion_queue*>(
      gpr_zalloc(sizeof(grpc_completion_queue) + vtable->data_size +
                 poller_vtable->size()));

  cq->vtable = vtable;
  cq->poller_vtable = poller_vtable;

  new (&cq->owning_refs) grpc_core::RefCount(
      2, GRPC_TRACE_FLAG_ENABLED(cq_refcount) ? "completion_queue" : nullptr);

  poller_vtable->init(POLLSET_FROM_CQ(cq), &cq->mu);
  vtable->init(DATA_FROM_CQ(cq), shutdown_callback);

  GRPC_CLOSURE_INIT(&cq->pollset_shutdown_done, on_pollset_shutdown_done, cq,
                    grpc_schedule_on_exec_ctx);
  return cq;
}

static void cq_init_next(void* data,
                         grpc_completion_queue_functor* ) {
  new (data) cq_next_data();
}

static void cq_destroy_next(void* data) {
  cq_next_data* cqd = static_cast<cq_next_data*>(data);
  cqd->~cq_next_data();
}

static void cq_init_pluck(
    void* data, grpc_completion_queue_functor* ) {
  new (data) cq_pluck_data();
}

static void cq_destroy_pluck(void* data) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*>(data);
  cqd->~cq_pluck_data();
}

static void cq_init_callback(void* data,
                             grpc_completion_queue_functor* shutdown_callback) {
  new (data) cq_callback_data(shutdown_callback);
}

static void cq_destroy_callback(void* data) {
  cq_callback_data* cqd = static_cast<cq_callback_data*>(data);
  cqd->~cq_callback_data();
}

grpc_cq_completion_type grpc_get_cq_completion_type(grpc_completion_queue* cq) {
  return cq->vtable->cq_completion_type;
}

int grpc_get_cq_poll_num(grpc_completion_queue* cq) {
  int cur_num_polls;
  gpr_mu_lock(cq->mu);
  cur_num_polls = cq->num_polls;
  gpr_mu_unlock(cq->mu);
  return cur_num_polls;
}

#ifndef NDEBUG
void grpc_cq_internal_ref(grpc_completion_queue* cq, const char* reason,
                          const char* file, int line) {
  grpc_core::DebugLocation debug_location(file, line);
#else
void grpc_cq_internal_ref(grpc_completion_queue* cq) {
  grpc_core::DebugLocation debug_location;
  const char* reason = nullptr;
#endif
  cq->owning_refs.Ref(debug_location, reason);
}

static void on_pollset_shutdown_done(void* arg, grpc_error_handle ) {
  grpc_completion_queue* cq = static_cast<grpc_completion_queue*>(arg);
  GRPC_CQ_INTERNAL_UNREF(cq, "pollset_destroy");
}

#ifndef NDEBUG
void grpc_cq_internal_unref(grpc_completion_queue* cq, const char* reason,
                            const char* file, int line) {
  grpc_core::DebugLocation debug_location(file, line);
#else
void grpc_cq_internal_unref(grpc_completion_queue* cq) {
  grpc_core::DebugLocation debug_location;
  const char* reason = nullptr;
#endif
  if (GPR_UNLIKELY(cq->owning_refs.Unref(debug_location, reason))) {
    cq->vtable->destroy(DATA_FROM_CQ(cq));
    cq->poller_vtable->destroy(POLLSET_FROM_CQ(cq));
#ifndef NDEBUG
    gpr_free(cq->outstanding_tags);
#endif
    gpr_free(cq);
  }
}

#ifndef NDEBUG
static void cq_check_tag(grpc_completion_queue* cq, void* tag, bool lock_cq) {
  int found = 0;
  if (lock_cq) {
    gpr_mu_lock(cq->mu);
  }

  for (int i = 0; i < static_cast<int>(cq->outstanding_tag_count); i++) {
    if (cq->outstanding_tags[i] == tag) {
      cq->outstanding_tag_count--;
      std::swap(cq->outstanding_tags[i],
                cq->outstanding_tags[cq->outstanding_tag_count]);
      found = 1;
      break;
    }
  }

  if (lock_cq) {
    gpr_mu_unlock(cq->mu);
  }

  CHECK(found);
}
#else
static void cq_check_tag(grpc_completion_queue* , void* ,
                         bool ) {}
#endif

static bool cq_begin_op_for_next(grpc_completion_queue* cq, void* ) {
  cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);
  return grpc_core::IncrementIfNonzero(&cqd->pending_events);
}

static bool cq_begin_op_for_pluck(grpc_completion_queue* cq, void* ) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);
  return grpc_core::IncrementIfNonzero(&cqd->pending_events);
}

static bool cq_begin_op_for_callback(grpc_completion_queue* cq, void* ) {
  cq_callback_data* cqd = static_cast<cq_callback_data*> DATA_FROM_CQ(cq);
  return grpc_core::IncrementIfNonzero(&cqd->pending_events);
}

bool grpc_cq_begin_op(grpc_completion_queue* cq, void* tag) {
#ifndef NDEBUG
  gpr_mu_lock(cq->mu);
  if (cq->outstanding_tag_count == cq->outstanding_tag_capacity) {
    cq->outstanding_tag_capacity =
        std::max(size_t(4), 2 * cq->outstanding_tag_capacity);
    cq->outstanding_tags = static_cast<void**>(gpr_realloc(
        cq->outstanding_tags,
        sizeof(*cq->outstanding_tags) * cq->outstanding_tag_capacity));
  }
  cq->outstanding_tags[cq->outstanding_tag_count++] = tag;
  gpr_mu_unlock(cq->mu);
#endif
  return cq->vtable->begin_op(cq, tag);
}

static void cq_end_op_for_next(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool ) {
  if (GRPC_TRACE_FLAG_ENABLED(api) ||
      (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok())) {
    std::string errmsg = grpc_core::StatusToString(error);
    GRPC_TRACE_LOG(api, INFO)
        << "cq_end_op_for_next(cq=" << cq << ", tag=" << tag
        << ", error=" << errmsg.c_str() << ", done=" << done
        << ", done_arg=" << done_arg << ", storage=" << storage << ")";
    if (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok()) {
      LOG(INFO) << "Operation failed: tag=" << tag << ", error=" << errmsg;
    }
  }
  cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);
  int is_success = (error.ok());

  storage->tag = tag;
  storage->done = done;
  storage->done_arg = done_arg;
  storage->next = static_cast<uintptr_t>(is_success);

  cq_check_tag(cq, tag, true);

  if (g_cached_cq == cq && g_cached_event == nullptr) {
    g_cached_event = storage;
  } else {

    bool is_first = cqd->queue.Push(storage);
    cqd->things_queued_ever.fetch_add(1, std::memory_order_relaxed);

    if (cqd->pending_events.load(std::memory_order_acquire) != 1) {

      if (is_first) {
        gpr_mu_lock(cq->mu);
        grpc_error_handle kick_error =
            cq->poller_vtable->kick(POLLSET_FROM_CQ(cq), nullptr);
        gpr_mu_unlock(cq->mu);

        if (!kick_error.ok()) {
          LOG(ERROR) << "Kick failed: "
                     << grpc_core::StatusToString(kick_error);
        }
      }
      if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
        GRPC_CQ_INTERNAL_REF(cq, "shutting_down");
        gpr_mu_lock(cq->mu);
        cq_finish_shutdown_next(cq);
        gpr_mu_unlock(cq->mu);
        GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down");
      }
    } else {
      GRPC_CQ_INTERNAL_REF(cq, "shutting_down");
      cqd->pending_events.store(0, std::memory_order_release);
      gpr_mu_lock(cq->mu);
      cq_finish_shutdown_next(cq);
      gpr_mu_unlock(cq->mu);
      GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down");
    }
  }
}

static void cq_end_op_for_pluck(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool ) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);
  int is_success = (error.ok());

  if (GRPC_TRACE_FLAG_ENABLED(api) ||
      (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok())) {
    std::string errmsg = grpc_core::StatusToString(error);
    GRPC_TRACE_LOG(api, INFO)
        << "cq_end_op_for_pluck(cq=" << cq << ", tag=" << tag
        << ", error=" << errmsg.c_str() << ", done=" << done
        << ", done_arg=" << done_arg << ", storage=" << storage << ")";
    if (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok()) {
      LOG(ERROR) << "Operation failed: tag=" << tag << ", error=" << errmsg;
    }
  }

  storage->tag = tag;
  storage->done = done;
  storage->done_arg = done_arg;
  storage->next = reinterpret_cast<uintptr_t>(&cqd->completed_head) |
                  static_cast<uintptr_t>(is_success);

  gpr_mu_lock(cq->mu);
  cq_check_tag(cq, tag, false);

  cqd->things_queued_ever.fetch_add(1, std::memory_order_relaxed);
  cqd->completed_tail->next =
      reinterpret_cast<uintptr_t>(storage) | (1u & cqd->completed_tail->next);
  cqd->completed_tail = storage;

  if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
    cq_finish_shutdown_pluck(cq);
    gpr_mu_unlock(cq->mu);
  } else {
    grpc_pollset_worker* pluck_worker = nullptr;
    for (int i = 0; i < cqd->num_pluckers; i++) {
      if (cqd->pluckers[i].tag == tag) {
        pluck_worker = *cqd->pluckers[i].worker;
        break;
      }
    }

    grpc_error_handle kick_error =
        cq->poller_vtable->kick(POLLSET_FROM_CQ(cq), pluck_worker);
    gpr_mu_unlock(cq->mu);
    if (!kick_error.ok()) {
      LOG(ERROR) << "Kick failed: " << kick_error;
    }
  }
}

static void cq_end_op_for_callback(
    grpc_completion_queue* cq, void* tag, grpc_error_handle error,
    void (*done)(void* done_arg, grpc_cq_completion* storage), void* done_arg,
    grpc_cq_completion* storage, bool internal) {
  (void)internal;
  cq_callback_data* cqd = static_cast<cq_callback_data*> DATA_FROM_CQ(cq);

  if (GRPC_TRACE_FLAG_ENABLED(api) ||
      (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok())) {
    std::string errmsg = grpc_core::StatusToString(error);
    GRPC_TRACE_LOG(api, INFO)
        << "cq_end_op_for_callback(cq=" << cq << ", tag=" << tag
        << ", error=" << errmsg.c_str() << ", done=" << done
        << ", done_arg=" << done_arg << ", storage=" << storage << ")";
    if (GRPC_TRACE_FLAG_ENABLED(op_failure) && !error.ok()) {
      LOG(ERROR) << "Operation failed: tag=" << tag << ", error=" << errmsg;
    }
  }

  done(done_arg, storage);

  cq_check_tag(cq, tag, true);

  if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
    cq_finish_shutdown_callback(cq);
  }

  auto* functor = static_cast<grpc_completion_queue_functor*>(tag);
  cqd->event_engine->Run(
      [engine = cqd->event_engine, functor, ok = error.ok()]() {
        grpc_core::ExecCtx exec_ctx;
        (*functor->functor_run)(functor, ok);
      });
}

void grpc_cq_end_op(grpc_completion_queue* cq, void* tag,
                    grpc_error_handle error,
                    void (*done)(void* done_arg, grpc_cq_completion* storage),
                    void* done_arg, grpc_cq_completion* storage,
                    bool internal) {
  cq->vtable->end_op(cq, tag, error, done, done_arg, storage, internal);
}

struct cq_is_finished_arg {
  gpr_atm last_seen_things_queued_ever;
  grpc_completion_queue* cq;
  grpc_core::Timestamp deadline;
  grpc_cq_completion* stolen_completion;
  void* tag;
  bool first_loop;
};
class ExecCtxNext : public grpc_core::ExecCtx {
 public:
  explicit ExecCtxNext(void* arg)
      : ExecCtx(0, GRPC_LATENT_SEE_METADATA("ExecCtx for CqNext")),
        check_ready_to_finish_arg_(arg) {}

  bool CheckReadyToFinish() override {
    cq_is_finished_arg* a =
        static_cast<cq_is_finished_arg*>(check_ready_to_finish_arg_);
    grpc_completion_queue* cq = a->cq;
    cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);
    CHECK_EQ(a->stolen_completion, nullptr);

    intptr_t current_last_seen_things_queued_ever =
        cqd->things_queued_ever.load(std::memory_order_relaxed);

    if (current_last_seen_things_queued_ever !=
        a->last_seen_things_queued_ever) {
      a->last_seen_things_queued_ever =
          cqd->things_queued_ever.load(std::memory_order_relaxed);

      a->stolen_completion = cqd->queue.Pop();
      if (a->stolen_completion != nullptr) {
        return true;
      }
    }
    return !a->first_loop && a->deadline < grpc_core::Timestamp::Now();
  }

 private:
  void* check_ready_to_finish_arg_;
};

#ifndef NDEBUG
static void dump_pending_tags(grpc_completion_queue* cq) {
  if (!GRPC_TRACE_FLAG_ENABLED(pending_tags)) return;
  std::vector<std::string> parts;
  parts.push_back("PENDING TAGS:");
  gpr_mu_lock(cq->mu);
  for (size_t i = 0; i < cq->outstanding_tag_count; i++) {
    parts.push_back(absl::StrFormat(" %p", cq->outstanding_tags[i]));
  }
  gpr_mu_unlock(cq->mu);
  VLOG(2) << absl::StrJoin(parts, "");
}
#else
static void dump_pending_tags(grpc_completion_queue* ) {}
#endif

static grpc_event cq_next(grpc_completion_queue* cq, gpr_timespec deadline,
                          void* reserved) {
  grpc_event ret;
  cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);

  GRPC_TRACE_LOG(api, INFO)
      << "grpc_completion_queue_next(cq=" << cq
      << ", deadline=gpr_timespec { tv_sec: " << deadline.tv_sec
      << ", tv_nsec: " << deadline.tv_nsec
      << ", clock_type: " << (int)deadline.clock_type
      << " }, reserved=" << reserved << ")";
  CHECK(!reserved);

  dump_pending_tags(cq);

  GRPC_CQ_INTERNAL_REF(cq, "next");

  grpc_core::Timestamp deadline_millis =
      grpc_core::Timestamp::FromTimespecRoundUp(deadline);
  cq_is_finished_arg is_finished_arg = {
      cqd->things_queued_ever.load(std::memory_order_relaxed),
      cq,
      deadline_millis,
      nullptr,
      nullptr,
      true};
  ExecCtxNext exec_ctx(&is_finished_arg);
  for (;;) {
    grpc_core::Timestamp iteration_deadline = deadline_millis;

    if (is_finished_arg.stolen_completion != nullptr) {
      grpc_cq_completion* c = is_finished_arg.stolen_completion;
      is_finished_arg.stolen_completion = nullptr;
      ret.type = GRPC_OP_COMPLETE;
      ret.success = c->next & 1u;
      ret.tag = c->tag;
      c->done(c->done_arg, c);
      break;
    }

    grpc_cq_completion* c = cqd->queue.Pop();

    if (c != nullptr) {
      ret.type = GRPC_OP_COMPLETE;
      ret.success = c->next & 1u;
      ret.tag = c->tag;
      c->done(c->done_arg, c);
      break;
    } else {

      if (cqd->queue.num_items() > 0) {
        iteration_deadline = grpc_core::Timestamp::ProcessEpoch();
      }
    }

    if (cqd->pending_events.load(std::memory_order_acquire) == 0) {

      if (cqd->queue.num_items() > 0) {

        continue;
      }

      ret.type = GRPC_QUEUE_SHUTDOWN;
      ret.success = 0;
      break;
    }

    if (!is_finished_arg.first_loop &&
        grpc_core::Timestamp::Now() >= deadline_millis) {
      ret.type = GRPC_QUEUE_TIMEOUT;
      ret.success = 0;
      dump_pending_tags(cq);
      break;
    }

    gpr_mu_lock(cq->mu);
    cq->num_polls++;
    grpc_error_handle err = cq->poller_vtable->work(
        POLLSET_FROM_CQ(cq), nullptr, iteration_deadline);
    gpr_mu_unlock(cq->mu);

    if (!err.ok()) {
      LOG(ERROR) << "Completion queue next failed: "
                 << grpc_core::StatusToString(err);
      if (err == absl::CancelledError()) {
        ret.type = GRPC_QUEUE_SHUTDOWN;
      } else {
        ret.type = GRPC_QUEUE_TIMEOUT;
      }
      ret.success = 0;
      dump_pending_tags(cq);
      break;
    }
    is_finished_arg.first_loop = false;
  }

  if (cqd->queue.num_items() > 0 &&
      cqd->pending_events.load(std::memory_order_acquire) > 0) {
    gpr_mu_lock(cq->mu);
    (void)cq->poller_vtable->kick(POLLSET_FROM_CQ(cq), nullptr);
    gpr_mu_unlock(cq->mu);
  }

  GRPC_SURFACE_TRACE_RETURNED_EVENT(cq, &ret);
  GRPC_CQ_INTERNAL_UNREF(cq, "next");

  CHECK_EQ(is_finished_arg.stolen_completion, nullptr);

  return ret;
}

static void cq_finish_shutdown_next(grpc_completion_queue* cq) {
  cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);

  CHECK(cqd->shutdown_called);
  CHECK_EQ(cqd->pending_events.load(std::memory_order_relaxed), 0);

  cq->poller_vtable->shutdown(POLLSET_FROM_CQ(cq), &cq->pollset_shutdown_done);
}

static void cq_shutdown_next(grpc_completion_queue* cq) {
  cq_next_data* cqd = static_cast<cq_next_data*> DATA_FROM_CQ(cq);

  GRPC_CQ_INTERNAL_REF(cq, "shutting_down");
  gpr_mu_lock(cq->mu);
  if (cqd->shutdown_called) {
    gpr_mu_unlock(cq->mu);
    GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down");
    return;
  }
  cqd->shutdown_called = true;

  if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
    cq_finish_shutdown_next(cq);
  }
  gpr_mu_unlock(cq->mu);
  GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down");
}

grpc_event grpc_completion_queue_next(grpc_completion_queue* cq,
                                      gpr_timespec deadline, void* reserved) {
  return cq->vtable->next(cq, deadline, reserved);
}

static int add_plucker(grpc_completion_queue* cq, void* tag,
                       grpc_pollset_worker** worker) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);
  if (cqd->num_pluckers == GRPC_MAX_COMPLETION_QUEUE_PLUCKERS) {
    return 0;
  }
  cqd->pluckers[cqd->num_pluckers].tag = tag;
  cqd->pluckers[cqd->num_pluckers].worker = worker;
  cqd->num_pluckers++;
  return 1;
}

static void del_plucker(grpc_completion_queue* cq, void* tag,
                        grpc_pollset_worker** worker) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);
  for (int i = 0; i < cqd->num_pluckers; i++) {
    if (cqd->pluckers[i].tag == tag && cqd->pluckers[i].worker == worker) {
      cqd->num_pluckers--;
      std::swap(cqd->pluckers[i], cqd->pluckers[cqd->num_pluckers]);
      return;
    }
  }
  GPR_UNREACHABLE_CODE(return);
}

class ExecCtxPluck : public grpc_core::ExecCtx {
 public:
  explicit ExecCtxPluck(void* arg)
      : ExecCtx(0, GRPC_LATENT_SEE_METADATA("ExecCtx for CqPluck")),
        check_ready_to_finish_arg_(arg) {}

  bool CheckReadyToFinish() override {
    cq_is_finished_arg* a =
        static_cast<cq_is_finished_arg*>(check_ready_to_finish_arg_);
    grpc_completion_queue* cq = a->cq;
    cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);

    CHECK_EQ(a->stolen_completion, nullptr);
    gpr_atm current_last_seen_things_queued_ever =
        cqd->things_queued_ever.load(std::memory_order_relaxed);
    if (current_last_seen_things_queued_ever !=
        a->last_seen_things_queued_ever) {
      gpr_mu_lock(cq->mu);
      a->last_seen_things_queued_ever =
          cqd->things_queued_ever.load(std::memory_order_relaxed);
      grpc_cq_completion* c;
      grpc_cq_completion* prev = &cqd->completed_head;
      while ((c = reinterpret_cast<grpc_cq_completion*>(
                  prev->next & ~uintptr_t{1})) != &cqd->completed_head) {
        if (c->tag == a->tag) {
          prev->next = (prev->next & uintptr_t{1}) | (c->next & ~uintptr_t{1});
          if (c == cqd->completed_tail) {
            cqd->completed_tail = prev;
          }
          gpr_mu_unlock(cq->mu);
          a->stolen_completion = c;
          return true;
        }
        prev = c;
      }
      gpr_mu_unlock(cq->mu);
    }
    return !a->first_loop && a->deadline < grpc_core::Timestamp::Now();
  }

 private:
  void* check_ready_to_finish_arg_;
};

static grpc_event cq_pluck(grpc_completion_queue* cq, void* tag,
                           gpr_timespec deadline, void* reserved) {
  grpc_event ret;
  grpc_cq_completion* c;
  grpc_cq_completion* prev;
  grpc_pollset_worker* worker = nullptr;
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);

  if (GRPC_TRACE_FLAG_ENABLED(queue_pluck)) {
    GRPC_TRACE_LOG(api, INFO)
        << "grpc_completion_queue_pluck(cq=" << cq << ", tag=" << tag
        << ", deadline=gpr_timespec { tv_sec: " << deadline.tv_sec
        << ", tv_nsec: " << deadline.tv_nsec
        << ", clock_type: " << (int)deadline.clock_type
        << " }, reserved=" << reserved << ")";
  }
  CHECK(!reserved);

  dump_pending_tags(cq);

  GRPC_CQ_INTERNAL_REF(cq, "pluck");
  gpr_mu_lock(cq->mu);
  grpc_core::Timestamp deadline_millis =
      grpc_core::Timestamp::FromTimespecRoundUp(deadline);
  cq_is_finished_arg is_finished_arg = {
      cqd->things_queued_ever.load(std::memory_order_relaxed),
      cq,
      deadline_millis,
      nullptr,
      tag,
      true};
  ExecCtxPluck exec_ctx(&is_finished_arg);
  for (;;) {
    if (is_finished_arg.stolen_completion != nullptr) {
      gpr_mu_unlock(cq->mu);
      c = is_finished_arg.stolen_completion;
      is_finished_arg.stolen_completion = nullptr;
      ret.type = GRPC_OP_COMPLETE;
      ret.success = c->next & 1u;
      ret.tag = c->tag;
      c->done(c->done_arg, c);
      break;
    }
    prev = &cqd->completed_head;
    while ((c = reinterpret_cast<grpc_cq_completion*>(
                prev->next & ~uintptr_t{1})) != &cqd->completed_head) {
      if (GPR_LIKELY(c->tag == tag)) {
        prev->next = (prev->next & uintptr_t{1}) | (c->next & ~uintptr_t{1});
        if (c == cqd->completed_tail) {
          cqd->completed_tail = prev;
        }
        gpr_mu_unlock(cq->mu);
        ret.type = GRPC_OP_COMPLETE;
        ret.success = c->next & 1u;
        ret.tag = c->tag;
        c->done(c->done_arg, c);
        goto done;
      }
      prev = c;
    }
    if (cqd->shutdown.load(std::memory_order_relaxed)) {
      gpr_mu_unlock(cq->mu);
      ret.type = GRPC_QUEUE_SHUTDOWN;
      ret.success = 0;
      break;
    }
    if (!add_plucker(cq, tag, &worker)) {
      VLOG(2) << "Too many outstanding grpc_completion_queue_pluck calls: "
                 "maximum is "
              << GRPC_MAX_COMPLETION_QUEUE_PLUCKERS;
      gpr_mu_unlock(cq->mu);

      ret.type = GRPC_QUEUE_TIMEOUT;
      ret.success = 0;
      dump_pending_tags(cq);
      break;
    }
    if (!is_finished_arg.first_loop &&
        grpc_core::Timestamp::Now() >= deadline_millis) {
      del_plucker(cq, tag, &worker);
      gpr_mu_unlock(cq->mu);
      ret.type = GRPC_QUEUE_TIMEOUT;
      ret.success = 0;
      dump_pending_tags(cq);
      break;
    }
    cq->num_polls++;
    grpc_error_handle err =
        cq->poller_vtable->work(POLLSET_FROM_CQ(cq), &worker, deadline_millis);
    if (!err.ok()) {
      del_plucker(cq, tag, &worker);
      gpr_mu_unlock(cq->mu);
      LOG(ERROR) << "Completion queue pluck failed: "
                 << grpc_core::StatusToString(err);
      ret.type = GRPC_QUEUE_TIMEOUT;
      ret.success = 0;
      dump_pending_tags(cq);
      break;
    }
    is_finished_arg.first_loop = false;
    del_plucker(cq, tag, &worker);
  }
done:
  GRPC_SURFACE_TRACE_RETURNED_EVENT(cq, &ret);
  GRPC_CQ_INTERNAL_UNREF(cq, "pluck");

  CHECK_EQ(is_finished_arg.stolen_completion, nullptr);

  return ret;
}

grpc_event grpc_completion_queue_pluck(grpc_completion_queue* cq, void* tag,
                                       gpr_timespec deadline, void* reserved) {
  return cq->vtable->pluck(cq, tag, deadline, reserved);
}

static void cq_finish_shutdown_pluck(grpc_completion_queue* cq) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);

  CHECK(cqd->shutdown_called);
  CHECK(!cqd->shutdown.load(std::memory_order_relaxed));
  cqd->shutdown.store(true, std::memory_order_relaxed);

  cq->poller_vtable->shutdown(POLLSET_FROM_CQ(cq), &cq->pollset_shutdown_done);
}

// NOTE: This function is almost exactly identical to cq_shutdown_next() but

static void cq_shutdown_pluck(grpc_completion_queue* cq) {
  cq_pluck_data* cqd = static_cast<cq_pluck_data*> DATA_FROM_CQ(cq);

  GRPC_CQ_INTERNAL_REF(cq, "shutting_down (pluck cq)");
  gpr_mu_lock(cq->mu);
  if (cqd->shutdown_called) {
    gpr_mu_unlock(cq->mu);
    GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down (pluck cq)");
    return;
  }
  cqd->shutdown_called = true;
  if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
    cq_finish_shutdown_pluck(cq);
  }
  gpr_mu_unlock(cq->mu);
  GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down (pluck cq)");
}

static void cq_finish_shutdown_callback(grpc_completion_queue* cq) {
  cq_callback_data* cqd = static_cast<cq_callback_data*> DATA_FROM_CQ(cq);
  auto* callback = cqd->shutdown_callback;

  CHECK(cqd->shutdown_called);

  cq->poller_vtable->shutdown(POLLSET_FROM_CQ(cq), &cq->pollset_shutdown_done);

  cqd->event_engine->Run([engine = cqd->event_engine, callback]() {
    grpc_core::ExecCtx exec_ctx;
    callback->functor_run(callback, 1);
  });
}

static void cq_shutdown_callback(grpc_completion_queue* cq) {
  cq_callback_data* cqd = static_cast<cq_callback_data*> DATA_FROM_CQ(cq);

  GRPC_CQ_INTERNAL_REF(cq, "shutting_down (callback cq)");
  gpr_mu_lock(cq->mu);
  if (cqd->shutdown_called) {
    gpr_mu_unlock(cq->mu);
    GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down (callback cq)");
    return;
  }
  cqd->shutdown_called = true;
  if (cqd->pending_events.fetch_sub(1, std::memory_order_acq_rel) == 1) {
    gpr_mu_unlock(cq->mu);
    cq_finish_shutdown_callback(cq);
  } else {
    gpr_mu_unlock(cq->mu);
  }
  GRPC_CQ_INTERNAL_UNREF(cq, "shutting_down (callback cq)");
}

void grpc_completion_queue_shutdown(grpc_completion_queue* cq) {
  grpc_core::ExecCtx exec_ctx;
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_completion_queue_shutdown(cq=" << cq << ")";
  cq->vtable->shutdown(cq);
}

void grpc_completion_queue_destroy(grpc_completion_queue* cq) {
  GRPC_TRACE_LOG(api, INFO) << "grpc_completion_queue_destroy(cq=" << cq << ")";
  grpc_completion_queue_shutdown(cq);

  grpc_core::ExecCtx exec_ctx;
  GRPC_CQ_INTERNAL_UNREF(cq, "destroy");
}

grpc_pollset* grpc_cq_pollset(grpc_completion_queue* cq) {
  return cq->poller_vtable->can_get_pollset() ? POLLSET_FROM_CQ(cq) : nullptr;
}

bool grpc_cq_can_listen(grpc_completion_queue* cq) {
  return cq->poller_vtable->can_listen;
}
