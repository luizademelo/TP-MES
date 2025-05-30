
// Copyright 2019 gRPC authors.

#include "src/core/util/work_serializer.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include <utility>

#include "absl/container/inlined_vector.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/mpscq.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class WorkSerializer::WorkSerializerImpl
    : public Orphanable,
      public grpc_event_engine::experimental::EventEngine::Closure {
 public:
  explicit WorkSerializerImpl(
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>
          event_engine)
      : event_engine_(std::move(event_engine)) {}
  void Run(absl::AnyInvocable<void()> callback, DebugLocation location);
  void Run() override;
  void Orphan() override;

#ifndef NDEBUG
  bool RunningInWorkSerializer() const {
    return running_work_serializer_ == this;
  }
#endif
 private:

  struct CallbackWrapper {
    CallbackWrapper(absl::AnyInvocable<void()>&& cb, const DebugLocation& loc)
        : callback(std::forward<absl::AnyInvocable<void()>>(cb)),
          location(loc) {}
    absl::AnyInvocable<void()> callback;

    GPR_NO_UNIQUE_ADDRESS DebugLocation location;
  };
  using CallbackVector = absl::InlinedVector<CallbackWrapper, 1>;

  bool Refill();

  enum class RefillResult { kRefilled, kFinished, kFinishedAndOrphaned };
  RefillResult RefillInner();

#ifndef NDEBUG
  void SetCurrentThread() { running_work_serializer_ = this; }
  void ClearCurrentThread() { running_work_serializer_ = nullptr; }
#else
  void SetCurrentThread() {}
  void ClearCurrentThread() {}
#endif

  CallbackVector processing_;

  const std::shared_ptr<grpc_event_engine::experimental::EventEngine>
      event_engine_;
  std::chrono::steady_clock::time_point running_start_time_
      ABSL_GUARDED_BY(mu_);
  std::chrono::steady_clock::duration time_running_items_;
  uint64_t items_processed_during_run_;

  bool running_ ABSL_GUARDED_BY(mu_) = false;
  bool orphaned_ ABSL_GUARDED_BY(mu_) = false;
  Mutex mu_;

  CallbackVector incoming_ ABSL_GUARDED_BY(mu_);

  GPR_NO_UNIQUE_ADDRESS latent_see::Flow flow_;

#ifndef NDEBUG
  static thread_local WorkSerializerImpl* running_work_serializer_;
#endif
};

#ifndef NDEBUG
thread_local WorkSerializer::WorkSerializerImpl*
    WorkSerializer::WorkSerializerImpl::running_work_serializer_ = nullptr;
#endif

void WorkSerializer::WorkSerializerImpl::Orphan() {
  ReleasableMutexLock lock(&mu_);

  if (!running_) {
    lock.Release();
    delete this;
    return;
  }

  orphaned_ = true;
}

void WorkSerializer::WorkSerializerImpl::Run(
    absl::AnyInvocable<void()> callback, DebugLocation location) {
  GRPC_TRACE_LOG(work_serializer, INFO)
      << "WorkSerializer[" << this << "] Scheduling callback ["
      << location.file() << ":" << location.line() << "]";
  global_stats().IncrementWorkSerializerItemsEnqueued();
  MutexLock lock(&mu_);
  if (!running_) {

    running_ = true;
    running_start_time_ = std::chrono::steady_clock::now();
    items_processed_during_run_ = 0;
    time_running_items_ = std::chrono::steady_clock::duration();
    CHECK(processing_.empty());
    processing_.emplace_back(std::move(callback), location);
    event_engine_->Run(this);
  } else {

    incoming_.emplace_back(std::move(callback), location);
  }
}

void WorkSerializer::WorkSerializerImpl::Run() {
  GRPC_LATENT_SEE_PARENT_SCOPE("WorkSerializer::Run");
  flow_.End();

  ExecCtx exec_ctx;

  auto& cb = processing_.back();
  GRPC_TRACE_LOG(work_serializer, INFO)
      << "WorkSerializer[" << this << "] Executing callback ["
      << cb.location.file() << ":" << cb.location.line() << "]";

  const auto start = std::chrono::steady_clock::now();
  SetCurrentThread();
  cb.callback();

  processing_.pop_back();
  ClearCurrentThread();
  global_stats().IncrementWorkSerializerItemsDequeued();
  const auto work_time = std::chrono::steady_clock::now() - start;
  global_stats().IncrementWorkSerializerWorkTimePerItemMs(
      std::chrono::duration_cast<std::chrono::milliseconds>(work_time).count());
  time_running_items_ += work_time;
  ++items_processed_during_run_;

  if (processing_.empty() && !Refill()) return;

  flow_.Begin(GRPC_LATENT_SEE_METADATA("WorkSerializer::Link"));
  event_engine_->Run(this);
}

WorkSerializer::WorkSerializerImpl::RefillResult
WorkSerializer::WorkSerializerImpl::RefillInner() {

  processing_.shrink_to_fit();
  MutexLock lock(&mu_);

  processing_.swap(incoming_);

  if (processing_.empty()) {
    running_ = false;
    global_stats().IncrementWorkSerializerRunTimeMs(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - running_start_time_)
            .count());
    global_stats().IncrementWorkSerializerWorkTimeMs(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            time_running_items_)
            .count());
    global_stats().IncrementWorkSerializerItemsPerRun(
        items_processed_during_run_);

    if (orphaned_) {
      return RefillResult::kFinishedAndOrphaned;
    } else {
      return RefillResult::kFinished;
    }
  }
  return RefillResult::kRefilled;
}

bool WorkSerializer::WorkSerializerImpl::Refill() {
  const auto result = RefillInner();
  switch (result) {
    case RefillResult::kRefilled:

      std::reverse(processing_.begin(), processing_.end());
      return true;
    case RefillResult::kFinished:
      return false;
    case RefillResult::kFinishedAndOrphaned:

      delete this;
      return false;
  }
  GPR_UNREACHABLE_CODE(return false);
}

WorkSerializer::WorkSerializer(
    std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine)
    : impl_(OrphanablePtr<WorkSerializerImpl>(
          MakeOrphanable<WorkSerializerImpl>(std::move(event_engine)))) {}

WorkSerializer::~WorkSerializer() = default;

void WorkSerializer::Run(absl::AnyInvocable<void()> callback,
                         DebugLocation location) {
  impl_->Run(std::move(callback), location);
}

#ifndef NDEBUG
bool WorkSerializer::RunningInWorkSerializer() const {
  return impl_->RunningInWorkSerializer();
}
#endif

}
