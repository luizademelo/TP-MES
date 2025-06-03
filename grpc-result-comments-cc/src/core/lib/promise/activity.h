Here's the commented version of the code:

```c++
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

// Forward declaration of Activity class
class Activity;

// Type alias for wakeup mask (16-bit unsigned integer)
using WakeupMask = uint16_t;

// Abstract base class for objects that can be woken up
class Wakeable {
 public:
  // Wake up synchronously with the given wakeup mask
  virtual void Wakeup(WakeupMask wakeup_mask) = 0;

  // Wake up asynchronously with the given wakeup mask
  virtual void WakeupAsync(WakeupMask wakeup_mask) = 0;

  // Drop the wakeable with the given wakeup mask
  virtual void Drop(WakeupMask wakeup_mask) = 0;

  // Get debug tag for the activity associated with this wakeup
  virtual std::string ActivityDebugTag(WakeupMask wakeup_mask) const = 0;

 protected:
  inline ~Wakeable() {}
};

namespace promise_detail {
// Implementation of Wakeable that does nothing (used as a default)
struct Unwakeable final : public Wakeable {
  void Wakeup(WakeupMask) override {}
  void WakeupAsync(WakeupMask) override {}
  void Drop(WakeupMask) override {}
  std::string ActivityDebugTag(WakeupMask) const override;
};

// Get singleton instance of Unwakeable
static Unwakeable* unwakeable() {
  return NoDestructSingleton<Unwakeable>::Get();
}
}  // namespace promise_detail

// Wrapper class that holds a Wakeable and a wakeup mask
class Waker {
 public:
  // Construct with specific wakeable and mask
  Waker(Wakeable* wakeable, WakeupMask wakeup_mask)
      : wakeable_and_arg_{wakeable, wakeup_mask} {}
  // Default constructor uses unwakeable instance
  Waker() : Waker(promise_detail::unwakeable(), 0) {}
  // Destructor drops the wakeable
  ~Waker() { wakeable_and_arg_.Drop(); }
  // Disable copy
  Waker(const Waker&) = delete;
  Waker& operator=(const Waker&) = delete;
  // Move constructor/assignment
  Waker(Waker&& other) noexcept : wakeable_and_arg_(other.Take()) {}
  Waker& operator=(Waker&& other) noexcept {
    std::swap(wakeable_and_arg_, other.wakeable_and_arg_);
    return *this;
  }

  // Wake up synchronously
  void Wakeup() { Take().Wakeup(); }

  // Wake up asynchronously
  void WakeupAsync() { Take().WakeupAsync(); }

  // Hash support
  template <typename H>
  friend H AbslHashValue(H h, const Waker& w) {
    return H::combine(H::combine(std::move(h), w.wakeable_and_arg_.wakeable),
                      w.wakeable_and_arg_.wakeup_mask);
  }

  // Equality comparison
  bool operator==(const Waker& other) const noexcept {
    return wakeable_and_arg_ == other.wakeable_and_arg_;
  }

  bool operator!=(const Waker& other) const noexcept {
    return !operator==(other);
  }

  // Get debug tag for associated activity
  std::string ActivityDebugTag() {
    return wakeable_and_arg_.ActivityDebugTag();
  }

  // Get debug string representation
  std::string DebugString() const {
    if (is_unwakeable()) return "<unwakeable>";
    return absl::StrFormat("Waker{%p, %d}", wakeable_and_arg_.wakeable,
                           wakeable_and_arg_.wakeup_mask);
  }

  // Stringification support
  template <typename Sink>
  friend void AbslStringify(Sink& sink, const Waker& waker) {
    sink.Append(waker.DebugString());
  }

  // Check if this waker is unwakeable
  bool is_unwakeable() const {
    return wakeable_and_arg_.wakeable == promise_detail::unwakeable();
  }

 private:
  // Helper struct combining wakeable and mask
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

  // Take ownership of the wakeable and arg, replacing with unwakeable
  WakeableAndArg Take() {
    return std::exchange(wakeable_and_arg_, {promise_detail::unwakeable(), 0});
  }

  WakeableAndArg wakeable_and_arg_;
};

// Helper class for waiting within an activity
class IntraActivityWaiter {
 public:
  // Mark this waiter as pending with current participant
  Pending pending();

  // Wake up the activity with accumulated wakeups
  void Wake();

  // Get debug string representation
  std::string DebugString() const;

  // Stringification support
  template <typename Sink>
  friend void AbslStringify(Sink& sink, const IntraActivityWaiter& waker) {
    sink.Append(waker.DebugString());
  }

 private:
  WakeupMask wakeups_ = 0;
};

// Base class for activities that can execute promises
class Activity : public Orphanable {
 public:
  // Force a wakeup of this activity
  void ForceWakeup() { MakeOwningWaker().Wakeup(); }

  // Force immediate repoll with given wakeup mask
  virtual void ForceImmediateRepoll(WakeupMask mask) = 0;

  // Force immediate repoll with current participant
  void ForceImmediateRepoll() { ForceImmediateRepoll(CurrentParticipant()); }

  // Get current participant mask
  virtual WakeupMask CurrentParticipant() const { return 1; }

  // Get current activity
  static Activity* current() { return current_ref(); }

  // Create an owning waker for this activity
  virtual Waker MakeOwningWaker() = 0;

  // Create a non-owning waker for this activity
  virtual Waker MakeNonOwningWaker() = 0;

  // Get debug tag for this activity
  virtual std::string DebugTag() const;

 protected:
  // Check if this activity is the current one
  bool is_current() const { return this == current(); }

  // Check if there is a current activity
  static bool have_current() { return current() != nullptr; }

  // RAII class for setting current activity
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
  // Get reference to thread-local current activity
  static Activity*& current_ref() {
#if !defined(_WIN32) || !defined(_DLL)
    return g_current_activity_;
#else
    static thread_local Activity* current_activity;
    return current_activity;
#endif
  }
#if !defined(_WIN32) || !defined(_DLL)
  // Thread-local current activity
  static thread_local Activity* g_current_activity_;
#endif
};

// Smart pointer type for Activity
using ActivityPtr = OrphanablePtr<Activity>;

namespace promise_detail {

// Helper class for holding context by value
template <typename Context>
class ContextHolder {
 public:
  using ContextType = Context;

  explicit ContextHolder(Context value) : value_(std::move(value)) {}
  Context* GetContext() { return &value_; }

 private:
  Context value_;
};

// Specialization for pointer context
template <typename Context>
class ContextHolder<Context*> {
 public:
  using ContextType = Context;

  explicit ContextHolder(Context* value) : value_(value) {}
  Context* GetContext() { return value_; }

 private:
  Context* value_;
};

// Specialization for unique_ptr context
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

// Specialization for RefCountedPtr context
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

// Context specialization for Activity
template <>
class Context<Activity> {
 public:
  static Activity* get() { return Activity::current(); }
};

// Helper to get context type from held type
template <typename HeldContext>
using ContextTypeFromHeld = typename ContextHolder<
    typename std::remove_reference<HeldContext>::type>::ContextType;

// Class holding multiple contexts
template <typename... Contexts>
class ActivityContexts
    : public ContextHolder<typename std::remove_reference<Contexts>::type>... {
 public:
  explicit ActivityContexts(Contexts&&... contexts)
      : ContextHolder<typename std::remove_reference<Contexts>::type>(
            std::forward<Contexts>(contexts))... {}

  // RAII class for setting multiple contexts
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

// Base class for freestanding activities (not bound to external event loop)
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
  // Possible actions during activity run
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

  // Get and reset action that occurred during run
  ActionDuringRun GotActionDuringRun() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    return std::exchange(action_during_run_, ActionDuringRun::kNone);
  }

  // Called when wakeup is complete
  void WakeupComplete() { Unref(); }

  // Set action to be processed during run
  void SetActionDuringRun(ActionDuringRun action)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_) {
    action_during_run_ = std::max(action_during_run_, action);
  }

  // Get mutex for synchronization
  Mutex* mu() ABSL_LOCK_RETURNED(mu_) { return &mu_; }

  std::string ActivityDebugTag(WakeupMask) const override { return DebugTag(); }

 private:
  class Handle;

  // Cancel the activity (must be implemented by derived classes)
  virtual void Cancel() = 0;

  // Reference counting
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

// Implementation of Activity that executes promises
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

  // Run scheduled wakeup
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
      // First wakeup - schedule it
      this->ScheduleWakeup();
    } else {
      // Already scheduled - just complete
      WakeupComplete();
    }
  }

  void Drop(WakeupMask) final { this->WakeupComplete(); }

  // Mark activity as done and clean up promise
  void MarkDone() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    CHECK(!std::exchange(done_, true));
    ScopedContext contexts(this);
    Destruct(&promise_holder_.promise);
  }

  // Perform one step of promise execution
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

  // Run one step of promise execution (with lock held)
  std::optional<ResultType> RunStep() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    ScopedActivity scoped_activity(this);
    ScopedContext contexts(this);
    return StepLoop();
  }

  // Start promise execution
  std::optional<ResultType> Start(Factory promise_factory)
      ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu()) {
    ScopedActivity scoped_activity(this);
    ScopedContext contexts(this);
    Construct(&promise_holder_.promise, promise_factory.Make());
    return StepLoop();
  }

  // Main promise execution loop
  std::optional<ResultType> StepLoop() ABSL_EXCLUSIVE_LOCKS_RE