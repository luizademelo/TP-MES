
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_POSIX_ENGINE_TIMER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "src/core/lib/event_engine/posix_engine/timer_heap.h"
#include "src/core/util/sync.h"
#include "src/core/util/time.h"
#include "src/core/util/time_averaged_stats.h"

namespace grpc_event_engine::experimental {

struct Timer {
  int64_t deadline;

  size_t heap_index;
  bool pending;
  struct Timer* next;
  struct Timer* prev;
  experimental::EventEngine::Closure* closure;
#ifndef NDEBUG
  struct Timer* hash_table_next;
#endif

  grpc_event_engine::experimental::EventEngine::TaskHandle task_handle;
};

class TimerListHost {
 public:

  virtual grpc_core::Timestamp Now() = 0;

  virtual void Kick() = 0;

 protected:
  ~TimerListHost() = default;
};

class TimerList {
 public:
  explicit TimerList(TimerListHost* host);

  TimerList(const TimerList&) = delete;
  TimerList& operator=(const TimerList&) = delete;

  void TimerInit(Timer* timer, grpc_core::Timestamp deadline,
                 experimental::EventEngine::Closure* closure);

  GRPC_MUST_USE_RESULT bool TimerCancel(Timer* timer);

  std::optional<std::vector<experimental::EventEngine::Closure*>> TimerCheck(
      grpc_core::Timestamp* next);

 private:

  struct Shard {
    Shard();

    grpc_core::Timestamp ComputeMinDeadline() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu);
    bool RefillHeap(grpc_core::Timestamp now) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu);
    Timer* PopOne(grpc_core::Timestamp now) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu);
    void PopTimers(grpc_core::Timestamp now,
                   grpc_core::Timestamp* new_min_deadline,
                   std::vector<experimental::EventEngine::Closure*>* out)
        ABSL_LOCKS_EXCLUDED(mu);

    grpc_core::Mutex mu;
    grpc_core::TimeAveragedStats stats ABSL_GUARDED_BY(mu);

    grpc_core::Timestamp queue_deadline_cap ABSL_GUARDED_BY(mu);

    grpc_core::Timestamp min_deadline ABSL_GUARDED_BY(&TimerList::mu_);

    uint32_t shard_queue_index ABSL_GUARDED_BY(&TimerList::mu_);

    TimerHeap heap ABSL_GUARDED_BY(mu);

    Timer list ABSL_GUARDED_BY(mu);
  };

  void SwapAdjacentShardsInQueue(uint32_t first_shard_queue_index)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  void NoteDeadlineChange(Shard* shard) ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);
  std::vector<experimental::EventEngine::Closure*> FindExpiredTimers(
      grpc_core::Timestamp now, grpc_core::Timestamp* next);

  TimerListHost* const host_;
  const size_t num_shards_;
  grpc_core::Mutex mu_;

  std::atomic<uint64_t> min_timer_;

  grpc_core::Mutex checker_mu_;

  const std::unique_ptr<Shard[]> shards_;

  const std::unique_ptr<Shard*[]> shard_queue_ ABSL_GUARDED_BY(mu_);
};

}

#endif
