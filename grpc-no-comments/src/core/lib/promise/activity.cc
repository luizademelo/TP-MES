// Copyright 2021 gRPC authors.

#include "src/core/lib/promise/activity.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <vector>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/util/atomic_utils.h"

namespace grpc_core {

#if !defined(_WIN32) || !defined(_DLL)
thread_local Activity* Activity::g_current_activity_{nullptr};
#endif

namespace promise_detail {

std::string Unwakeable::ActivityDebugTag(WakeupMask) const {
  return "<unknown>";
}

class FreestandingActivity::Handle final : public Wakeable {
 public:
  explicit Handle(FreestandingActivity* activity) : activity_(activity) {}

  void Ref() { refs_.fetch_add(1, std::memory_order_relaxed); }

  void DropActivity() ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();
    CHECK_NE(activity_, nullptr);
    activity_ = nullptr;
    mu_.Unlock();
    Unref();
  }

  void Wakeup(WakeupMask) override ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();

    if (activity_ && activity_->RefIfNonzero()) {
      FreestandingActivity* activity = activity_;
      mu_.Unlock();

      activity->Wakeup(0);
    } else {

      mu_.Unlock();
    }

    Unref();
  }

  void WakeupAsync(WakeupMask) override ABSL_LOCKS_EXCLUDED(mu_) {
    mu_.Lock();

    if (activity_ && activity_->RefIfNonzero()) {
      FreestandingActivity* activity = activity_;
      mu_.Unlock();

      activity->WakeupAsync(0);
    } else {

      mu_.Unlock();
    }

    Unref();
  }

  void Drop(WakeupMask) override { Unref(); }

  std::string ActivityDebugTag(WakeupMask) const override {
    MutexLock lock(&mu_);
    return activity_ == nullptr ? "<unknown>" : activity_->DebugTag();
  }

 private:

  void Unref() {
    if (1 == refs_.fetch_sub(1, std::memory_order_acq_rel)) {
      delete this;
    }
  }

  std::atomic<size_t> refs_{2};
  mutable Mutex mu_ ABSL_ACQUIRED_AFTER(activity_->mu_);
  FreestandingActivity* activity_ ABSL_GUARDED_BY(mu_);
};

bool FreestandingActivity::RefIfNonzero() { return IncrementIfNonzero(&refs_); }

FreestandingActivity::Handle* FreestandingActivity::RefHandle() {
  if (handle_ == nullptr) {

    handle_ = new Handle(this);
    return handle_;
  } else {

    handle_->Ref();
    return handle_;
  }
}

void FreestandingActivity::DropHandle() {
  handle_->DropActivity();
  handle_ = nullptr;
}

Waker FreestandingActivity::MakeNonOwningWaker() {
  mu_.AssertHeld();
  return Waker(RefHandle(), 0);
}

}

std::string Activity::DebugTag() const {
  return absl::StrFormat("ACTIVITY[%p]", this);
}

std::string IntraActivityWaiter::DebugString() const {
  std::vector<int> bits;
  for (size_t i = 0; i < 8 * sizeof(WakeupMask); i++) {
    if (wakeups_ & (1 << i)) bits.push_back(i);
  }
  return absl::StrCat("{", absl::StrJoin(bits, ","), "}");
}

}
