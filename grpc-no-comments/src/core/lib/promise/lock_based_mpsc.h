// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_LOCK_BASED_MPSC_H
#define GRPC_SRC_CORE_LIB_PROMISE_LOCK_BASED_MPSC_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

#include "absl/base/thread_annotations.h"
#include "absl/log/check.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/status_flag.h"
#include "src/core/lib/promise/wait_set.h"
#include "src/core/util/dump_args.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

namespace lock_based_mpscpipe_detail {

template <typename T>
class Center : public RefCounted<Center<T>> {
 public:

  explicit Center(size_t max_queued) : max_queued_(max_queued) {}

  static constexpr const uint64_t kClosedBatch =
      std::numeric_limits<uint64_t>::max();

  Poll<bool> PollReceiveBatch(std::vector<T>& dest) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::PollReceiveBatch: "
        << GRPC_DUMP_ARGS(this, batch_, queue_.size());
    if (queue_.empty()) {
      if (batch_ == kClosedBatch) return false;
      receive_waker_ = GetContext<Activity>()->MakeNonOwningWaker();
      return Pending{};
    }
    dest.swap(queue_);
    queue_.clear();
    if (batch_ != kClosedBatch) ++batch_;
    auto wakeups = send_wakers_.TakeWakeupSet();
    lock.Release();
    wakeups.Wakeup();
    return true;
  }

  template <bool kAwaitReceipt>
  uint64_t Send(T t) {
    ReleasableMutexLock lock(&mu_);
    if (batch_ == kClosedBatch) return kClosedBatch;
    queue_.push_back(std::move(t));
    auto receive_waker = std::move(receive_waker_);
    const uint64_t batch =
        (!kAwaitReceipt && queue_.size() <= max_queued_) ? batch_ : batch_ + 1;
    lock.Release();
    receive_waker.Wakeup();
    return batch;
  }

  Poll<Empty> PollReceiveBatch(uint64_t batch) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::PollReceiveBatch: " << GRPC_DUMP_ARGS(this, batch_, batch);
    if (batch_ >= batch) return Empty{};
    send_wakers_.AddPending(GetContext<Activity>()->MakeNonOwningWaker());
    return Pending{};
  }

  void ReceiverClosed(bool wake_receiver) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::ReceiverClosed: " << GRPC_DUMP_ARGS(this, batch_);
    if (batch_ == kClosedBatch) return;
    batch_ = kClosedBatch;
    auto wakeups = send_wakers_.TakeWakeupSet();
    auto receive_waker = std::move(receive_waker_);
    lock.Release();
    if (wake_receiver) receive_waker.Wakeup();
    wakeups.Wakeup();
  }

 private:
  Mutex mu_;
  const size_t max_queued_;
  std::vector<T> queue_ ABSL_GUARDED_BY(mu_);

  uint64_t batch_ ABSL_GUARDED_BY(mu_) = 1;
  Waker receive_waker_ ABSL_GUARDED_BY(mu_);
  WaitSet send_wakers_ ABSL_GUARDED_BY(mu_);
};

}

template <typename T>
class LockBasedMpscReceiver;

template <typename T>
class LockBasedMpscSender {
 public:
  LockBasedMpscSender() = default;
  LockBasedMpscSender(const LockBasedMpscSender&) = default;
  LockBasedMpscSender& operator=(const LockBasedMpscSender&) = default;
  LockBasedMpscSender(LockBasedMpscSender&&) noexcept = default;
  LockBasedMpscSender& operator=(LockBasedMpscSender&&) noexcept = default;

  auto Send(T t) { return SendGeneric<false>(std::move(t)); }

  auto SendAcked(T t) { return SendGeneric<true>(std::move(t)); }

  StatusFlag UnbufferedImmediateSend(T t) {
    return StatusFlag(center_->template Send<false>(std::move(t)) !=
                      lock_based_mpscpipe_detail::Center<T>::kClosedBatch);
  }

 private:
  template <bool kAwaitReceipt>
  auto SendGeneric(T t) {
    return [center = center_, t = std::move(t),
            batch = uint64_t(0)]() mutable -> Poll<StatusFlag> {
      if (center == nullptr) return Failure{};
      if (batch == 0) {
        batch = center->template Send<kAwaitReceipt>(std::move(t));
        DCHECK_NE(batch, 0u);
        if (batch == lock_based_mpscpipe_detail::Center<T>::kClosedBatch) {
          return Failure{};
        }
      }
      auto p = center->PollReceiveBatch(batch);
      if (p.pending()) return Pending{};
      return Success{};
    };
  }

  friend class LockBasedMpscReceiver<T>;
  explicit LockBasedMpscSender(
      RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center)
      : center_(std::move(center)) {}
  RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center_;
};

template <typename T>
class LockBasedMpscReceiver {
 public:

  explicit LockBasedMpscReceiver(size_t max_buffer_hint)
      : center_(MakeRefCounted<lock_based_mpscpipe_detail::Center<T>>(
            std::max(static_cast<size_t>(1), max_buffer_hint / 2))) {}
  ~LockBasedMpscReceiver() {
    if (center_ != nullptr) center_->ReceiverClosed(false);
  }

  void MarkClosed() {
    if (center_ != nullptr) center_->ReceiverClosed(true);
  }
  LockBasedMpscReceiver(const LockBasedMpscReceiver&) = delete;
  LockBasedMpscReceiver& operator=(const LockBasedMpscReceiver&) = delete;

  LockBasedMpscReceiver(LockBasedMpscReceiver&& other) noexcept
      : center_(std::move(other.center_)) {
    DCHECK(other.buffer_.empty());
  }
  LockBasedMpscReceiver& operator=(LockBasedMpscReceiver&& other) noexcept {
    DCHECK(other.buffer_.empty());
    center_ = std::move(other.center_);
    return *this;
  }

  LockBasedMpscSender<T> MakeSender() {
    return LockBasedMpscSender<T>(center_);
  }

  auto Next() {
    return [this]() -> Poll<ValueOrFailure<T>> {
      if (buffer_it_ != buffer_.end()) {
        return Poll<ValueOrFailure<T>>(std::move(*buffer_it_++));
      }
      auto p = center_->PollReceiveBatch(buffer_);
      if (bool* r = p.value_if_ready()) {
        if (!*r) return Failure{};
        buffer_it_ = buffer_.begin();
        return Poll<ValueOrFailure<T>>(std::move(*buffer_it_++));
      }
      return Pending{};
    };
  }

  auto NextBatch() {
    return [this]() -> Poll<ValueOrFailure<std::vector<T>>> {
      if (buffer_it_ != buffer_.end()) {
        std::vector<T> tmp_buffer;
        std::move(buffer_it_, buffer_.end(), std::back_inserter(tmp_buffer));
        buffer_.clear();
        buffer_it_ = buffer_.end();
        return ValueOrFailure<std::vector<T>>(std::move(tmp_buffer));
      }

      auto p = center_->PollReceiveBatch(buffer_);
      if (bool* r = p.value_if_ready()) {
        if (!*r) return Failure{};
        auto tmp_buffer(std::move(buffer_));
        buffer_.clear();
        buffer_it_ = buffer_.end();
        return ValueOrFailure<std::vector<T>>(std::move(tmp_buffer));
      }
      return Pending{};
    };
  }

 private:

  std::vector<T> buffer_;
  typename std::vector<T>::iterator buffer_it_ = buffer_.end();
  RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center_;
};

}

#endif
