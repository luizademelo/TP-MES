// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_ACTIVITY_H
#define GRPC_SRC_CORE_LIB_PROMISE_ACTIVITY_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <algorithm>
#include <atomic>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/detail/status.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/construct_destruct.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/latent_see.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class Activity;

using WakeupMask = uint16_t;

class Wakeable {
 public:

  virtual void Wakeup(WakeupMask wakeup_mask) = 0;

  virtual void WakeupAsync(WakeupMask wakeup_mask) = 0;

  virtual void Drop(WakeupMask wakeup_mask) = 0;

  virtual std::string ActivityDebugTag(WakeupMask wakeup_mask) const = 0;

 protected:
  inline ~Wakeable() {}
};

namespace promise_detail {
struct Unwakeable final : public Wakeable {
  void Wakeup(WakeupMask) override {}
  void WakeupAsync(WakeupMask) override {}
  void Drop(WakeupMask) override {}
  std::string ActivityDebugTag(WakeupMask) const override;
};
static Unwakeable* unwakeable() {
  return NoDestructSingleton<Unwakeable>::Get();
}
}

class Waker {
 public:
  Waker(Wakeable* wakeable, WakeupMask wakeup_mask)
      : wakeable_and_arg_{wakeable, wakeup_mask} {}
  Waker() : Waker(promise_detail::unwakeable(), 0) {}
  ~Waker() { wakeable_and_arg_.Drop(); }
  Waker(const Waker&) = delete;
  Waker& operator=(const Waker&) = delete;
  Waker(Waker&& other) noexcept : wakeable_and_arg_(other.Take()) {}
  Waker& operator=(Waker&& other) noexcept {
    std::swap(wakeable_and_arg_, other.wakeable_and_arg_);
    return *this;
  }

  void Wakeup() { Take().Wakeup(); }

  void WakeupAsync() { Take().WakeupAsync(); }

  template <typename H>
  friend H AbslHashValue(H h, const Waker& w) {
    return H::combine(H::combine(std::move(h), w.wakeable_and_arg_.wakeable),
                      w.wakeable_and_arg_.wakeup_mask);
  }

  bool operator==(const Waker& other) const noexcept {
    return wakeable_and_arg_ == other.wakeable_and_arg_;
  }

  bool operator!=(const Waker& other) const noexcept {
    return !operator==(other);
  }

  std::string ActivityDebugTag() {
    return wakeable_and_arg_.ActivityDebugTag();
  }

  std::string DebugString() const {
    if (is_unwakeable()) return "<unwakeable>";
    return absl::StrFormat("Waker{%p, %d}", wakeable_and_arg_.wakeable,
                           wakeable_and_arg_.wakeup_mask);
  }

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const Waker& waker) {
    sink.Append(waker.DebugString());
  }

  bool is_unwakeable() const {
    return wakeable_and_arg_.wakeable == promise_detail::unwakeable();
  }

 private:
  struct WakeableAndArg {
    Wakeable* wakeable;
    WakeupMask wakeup_mask;

    void Wakeup() { wakeable->Wakeup(wakeup_mask); }
    void WakeupAsync() { wakeable->WakeupAsync(wakeup_mask); }
    void Drop() { wakeable->Drop(wakeup_mask); }
    std::string ActivityDebugTag() const {
      return wakeable == nullptr ? "<unknown>"
                                 : wakeable->ActivityDebugTag(wakeup_mask);
    }
    bool operator==(const WakeableAndArg& other) const noexcept {
      return wakeable == other.wakeable && wakeup_mask == other.wakeup_mask;
    }
  };

  WakeableAndArg Take() {
    return std::exchange(wakeable_and_arg_, {promise_detail::unwakeable(), 0});
  }

  WakeableAndArg wakeable_and_arg_;
};

class IntraActivityWaiter {
 public:

  Pending pending();

  void Wake();

  std::string DebugString() const;

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const IntraActivityWaiter& waker) {
    sink.Append(waker.DebugString());
  }

 private:
  WakeupMask wakeups_ = 0;
};

class Activity : public Orphanable {
 public:

  void ForceWakeup() { MakeOwningWaker().Wakeup(); }

  virtual void ForceImmediateRepoll(WakeupMask mask) = 0;

  void ForceImmediateRepoll() { ForceImmediateRepoll(CurrentParticipant()); }

  virtual WakeupMask CurrentParticipant() const { return 1; }

  static Activity* current() { return current_ref(); }

  virtual Waker MakeOwningWaker() = 0;

  virtual Waker MakeNonOwningWaker() = 0;

  virtual std::string DebugTag() const;

 protected:

  bool is_current() const { return this == current(); }

  static bool have_current() { return current() != nullptr; }

  class ScopedActivity {
   public:
    explicit ScopedActivity(Activity* activity) : prior_activity_(current()) {
      current_ref() = activity;
    }
    ~ScopedActivity() { current_ref() = prior_activity_; }
    ScopedActivity(const ScopedActivity&) = delete;
    ScopedActivity& operator=(const ScopedActivity&) = delete;

   private:
    Activity* const prior_activity_;
  };

 private:
  static Activity*& current_ref() {
#if !defined(_WIN32) || !defined(_DLL)
    return g_current_activity_;
#else

    static thread_local Activity* current_activity;
    return current_activity;
#endif
  }
#if !defined(_WIN32) || !defined(_DLL)

  static thread_local Activity* g_current_activity_;
#endif
};

using ActivityPtr = OrphanablePtr<Activity>;

namespace promise_detail {

template <typename Context>
class ContextHolder {
 public:
  using ContextType = Context;

  explicit ContextHolder(Context value) : value_(std::move(value)) {}
  Context* GetContext() { return &value_; }

 private:
  Context value_;
};

template <typename Context>
class ContextHolder<Context*> {
 public:
  using ContextType = Context;

  explicit ContextHolder(Context* value) : value_(value) {}
  Context* GetContext() { return value_; }

 private:
  Context* value_;
};

template <typename Context, typename Deleter>
class ContextHolder<std::unique_ptr<Context, Deleter>> {
 public:
  using ContextType = Context;

  explicit ContextHolder(std::unique_ptr<Context, Deleter> value)
      : value_(std::move(value)) {}
  Context* GetContext() { return value_.get(); }

 private:
  std::unique_ptr<Context, Deleter> value_;
};

template <typename Context>
class ContextHolder<RefCountedPtr<Context>> {
 public:
  using ContextType = Context;

  explicit ContextHolder(RefCountedPtr<Context> value)
      : value_(std::move(value)) {}
  Context* GetContext() { return value_.get(); }

 private:
  RefCountedPtr<Context> value_;
};

template <>
class Context<Activity> {
 public:
  static Activity* get() { return Activity::current(); }
};

template <typename HeldContext>
using ContextTypeFromHeld = typename ContextHolder<
    typename std::remove_reference<HeldContext>::type>::ContextType;

template <typename... Contexts>
class ActivityContexts
    : public ContextHolder<typename std::remove_reference<Contexts>::type>... {
 public:
  explicit ActivityContexts(Contexts&&... contexts)
      : ContextHolder<typename std::remove_reference<Contexts>::type>(
            std::forward<Contexts>(contexts))... {}

  class ScopedContext : public Context<ContextTypeFromHeld<Contexts>>... {
   public:
    explicit ScopedContext(ActivityContexts* contexts)
        : Context<ContextTypeFromHeld<Contexts>>(
              static_cast<ContextHolder<
                  typename std::remove_reference<Contexts>::type>*>(contexts)
                  ->GetContext())... {

      (void)contexts;
    }
  };
};

class FreestandingActivity : public Activity, private Wakeable {
 public:
  Waker MakeOwningWaker() final {
    Ref();
    return Waker(this, 0);
  }
  Waker MakeNonOwningWaker() final;

  void Orphan() final {
    Cancel();
    Unref();
  }

  void ForceImmediateRepoll(WakeupMask) final {
    mu_.AssertHeld();
    SetActionDuringRun(ActionDuringRun::kWakeup);
  }

 protected:

  enum class ActionDuringRun : uint8_t {
    kNone,
    kWakeup,
    kCancel,
  };

  inline ~FreestandingActivity() override {
    if (handle_) {
      DropHandle();
    }
  }

  ActionDuringRun GotActionDuringRun() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return std::exchange(action_during_run_, ActionDuringRun::kNone);
  }

  void WakeupComplete() { Unref(); }

  void SetActionDuringRun(ActionDuringRun action)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    action_during_run_ = std::max(action_during_run_, action);
  }

  Mutex* mu() ABSL_LOCK_RETURNED(mu_) { return &mu_; }

  std::string ActivityDebugTag(WakeupMask) const override { return DebugTag(); }

 private:
  class Handle;

  virtual void Cancel() = 0;

  void Ref() { refs_.fetch_add(1, std::memory_order_relaxed); }
  void Unref() {
    if (1 == refs_.fetch_sub(1, std::memory_order_acq_rel)) {
      delete this;
    }
  }

  Handle* RefHandle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  bool RefIfNonzero();

  void DropHandle() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  Mutex mu_;

  std::atomic<uint32_t> refs_{1};

  ActionDuringRun action_during_run_ ABSL_GUARDED_BY(mu_) =
      ActionDuringRun::kNone;

  Handle* handle_ ABSL_GUARDED_BY(mu_) = nullptr;
};

template <class F, class WakeupScheduler, class OnDone, typename... Contexts>
class PromiseActivity final
    : public FreestandingActivity,
      public WakeupScheduler::template BoundScheduler<
          PromiseActivity<F, WakeupScheduler, OnDone, Contexts...>>,
      private ActivityContexts<Contexts...> {
 public:
  using Factory = OncePromiseFactory<void, F>;
  using ResultType = typename Factory::Promise::Result;

  PromiseActivity(F promise_factory, WakeupScheduler wakeup_scheduler,
                  OnDone on_done, Contexts&&... contexts)
      : FreestandingActivity(),
        WakeupScheduler::template BoundScheduler<PromiseActivity>(
            std::move(wakeup_scheduler)),
        ActivityContexts<Contexts...>(std::forward<Contexts>(contexts)...),
        on_done_(std::move(on_done)) {

    mu()->Lock();
    auto status = Start(Factory(std::move(promise_factory)));
    mu()->Unlock();

    if (status.has_value()) {
      on_done_(std::move(*status));
    }
  }

  ~PromiseActivity() override {

    CHECK(done_);
  }

  void RunScheduledWakeup() {
    CHECK(wakeup_scheduled_.exchange(false, std::memory_order_acq_rel));
    Step();
    WakeupComplete();
  }

 private:
  using typename ActivityContexts<Contexts...>::ScopedContext;

  void Cancel() final {
    if (Activity::is_current()) {
      mu()->AssertHeld();
      SetActionDuringRun(ActionDuringRun::kCancel);
      return;
    }
    bool was_done;
    {
      MutexLock lock(mu());

      was_done = done_;
      if (!done_) {
        ScopedActivity scoped_activity(this);
        ScopedContext contexts(this);
        MarkDone();
      }
    }

    if (!was_done) {
      on_done_(absl::CancelledError());
    }
  }

  void Wakeup(WakeupMask m) final {

    if (Activity::is_current()) {
      mu()->AssertHeld();
      SetActionDuringRun(ActionDuringRun::kWakeup);
      WakeupComplete();
      return;
    }
    WakeupAsync(m);
  }

  void WakeupAsync(WakeupMask) final {
    GRPC_LATENT_SEE_INNER_SCOPE("PromiseActivity::WakeupAsync");
    wakeup_flow_.Begin(GRPC_LATENT_SEE_METADATA("Activity::Wakeup"));
    if (!wakeup_scheduled_.exchange(true, std::memory_order_acq_rel)) {

      this->ScheduleWakeup();
    } else {

      WakeupComplete();
    }
  }

  void Drop(WakeupMask) final { this->WakeupComplete(); }

  void MarkDone() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    CHECK(!std::exchange(done_, true));
    ScopedContext contexts(this);
    Destruct(&promise_holder_.promise);
  }

  void Step() ABSL_LOCKS_EXCLUDED(mu()) {
    GRPC_LATENT_SEE_PARENT_SCOPE("PromiseActivity::Step");
    wakeup_flow_.End();

    mu()->Lock();
    if (done_) {

      mu()->Unlock();
      return;
    }
    auto status = RunStep();
    mu()->Unlock();
    if (status.has_value()) {
      on_done_(std::move(*status));
    }
  }

  std::optional<ResultType> RunStep() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    ScopedActivity scoped_activity(this);
    ScopedContext contexts(this);
    return StepLoop();
  }

  std::optional<ResultType> Start(Factory promise_factory)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    ScopedActivity scoped_activity(this);
    ScopedContext contexts(this);
    Construct(&promise_holder_.promise, promise_factory.Make());
    return StepLoop();
  }

  std::optional<ResultType> StepLoop() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    CHECK(is_current());
    while (true) {

      CHECK(!done_);
      auto r = promise_holder_.promise();
      if (auto* status = r.value_if_ready()) {

        MarkDone();
        return IntoStatus(status);
      }

      switch (GotActionDuringRun()) {
        case ActionDuringRun::kNone:
          return {};
        case ActionDuringRun::kWakeup:
          break;
        case ActionDuringRun::kCancel:
          MarkDone();
          return absl::CancelledError();
      }
    }
  }

  using Promise = typename Factory::Promise;

  GPR_NO_UNIQUE_ADDRESS OnDone on_done_;

  GPR_NO_UNIQUE_ADDRESS bool done_ ABSL_GUARDED_BY(mu()) = false;

  GPR_NO_UNIQUE_ADDRESS std::atomic<bool> wakeup_scheduled_{false};

  union PromiseHolder {
    PromiseHolder() {}
    ~PromiseHolder() {}
    GPR_NO_UNIQUE_ADDRESS Promise promise;
  };
  GPR_NO_UNIQUE_ADDRESS PromiseHolder promise_holder_ ABSL_GUARDED_BY(mu());
  GPR_NO_UNIQUE_ADDRESS latent_see::Flow wakeup_flow_;
};

}

template <typename Factory, typename WakeupScheduler, typename OnDone,
          typename... Contexts>
ActivityPtr MakeActivity(Factory promise_factory,
                         WakeupScheduler wakeup_scheduler, OnDone on_done,
                         Contexts&&... contexts) {
  return ActivityPtr(
      new promise_detail::PromiseActivity<Factory, WakeupScheduler, OnDone,
                                          Contexts...>(
          std::move(promise_factory), std::move(wakeup_scheduler),
          std::move(on_done), std::forward<Contexts>(contexts)...));
}

inline Pending IntraActivityWaiter::pending() {
  const auto new_wakeups = GetContext<Activity>()->CurrentParticipant();
  GRPC_TRACE_LOG(promise_primitives, INFO)
      << "IntraActivityWaiter::pending: "
      << GRPC_DUMP_ARGS(this, new_wakeups, wakeups_);
  wakeups_ |= new_wakeups;
  return Pending();
}

inline void IntraActivityWaiter::Wake() {
  if (wakeups_ == 0) return;
  GetContext<Activity>()->ForceImmediateRepoll(std::exchange(wakeups_, 0));
}

}

#endif
