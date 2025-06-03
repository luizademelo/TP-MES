Here's the commented version of the code:

```c++
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

// Central implementation of a lock-based multi-producer single-consumer queue
template <typename T>
class Center : public RefCounted<Center<T>> {
 public:
  // Constructor with maximum queue size parameter
  explicit Center(size_t max_queued) : max_queued_(max_queued) {}

  // Special batch number indicating the queue is closed
  static constexpr const uint64_t kClosedBatch =
      std::numeric_limits<uint64_t>::max();

  // Poll for receiving a batch of items from the queue
  // Moves available items into dest vector if any are available
  Poll<bool> PollReceiveBatch(std::vector<T>& dest) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::PollReceiveBatch: "
        << GRPC_DUMP_ARGS(this, batch_, queue_.size());
    if (queue_.empty()) {
      if (batch_ == kClosedBatch) return false;  // Queue is closed
      receive_waker_ = GetContext<Activity>()->MakeNonOwningWaker();
      return Pending{};  // No items available yet
    }
    // Swap contents with destination vector to transfer ownership
    dest.swap(queue_);
    queue_.clear();
    if (batch_ != kClosedBatch) ++batch_;  // Increment batch counter if not closed
    auto wakeups = send_wakers_.TakeWakeupSet();
    lock.Release();
    wakeups.Wakeup();  // Wake up any waiting senders
    return true;       // Successfully received items
  }

  // Send an item to the queue
  // kAwaitReceipt template parameter controls whether to wait for receipt
  template <bool kAwaitReceipt>
  uint64_t Send(T t) {
    ReleasableMutexLock lock(&mu_);
    if (batch_ == kClosedBatch) return kClosedBatch;  // Queue is closed
    queue_.push_back(std::move(t));                  // Add item to queue
    auto receive_waker = std::move(receive_waker_);
    // Determine batch number based on await receipt flag and queue size
    const uint64_t batch =
        (!kAwaitReceipt && queue_.size() <= max_queued_) ? batch_ : batch_ + 1;
    lock.Release();
    receive_waker.Wakeup();  // Wake up receiver if waiting
    return batch;            // Return current batch number
  }

  // Poll for receiving confirmation of a specific batch
  Poll<Empty> PollReceiveBatch(uint64_t batch) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::PollReceiveBatch: " << GRPC_DUMP_ARGS(this, batch_, batch);
    if (batch_ >= batch) return Empty{};  // Batch has been processed
    // Add current activity to wait set if batch not processed yet
    send_wakers_.AddPending(GetContext<Activity>()->MakeNonOwningWaker());
    return Pending{};  // Still waiting for batch to be processed
  }

  // Handle receiver closing the queue
  void ReceiverClosed(bool wake_receiver) {
    ReleasableMutexLock lock(&mu_);
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "MPSC::ReceiverClosed: " << GRPC_DUMP_ARGS(this, batch_);
    if (batch_ == kClosedBatch) return;  // Already closed
    batch_ = kClosedBatch;               // Mark as closed
    auto wakeups = send_wakers_.TakeWakeupSet();
    auto receive_waker = std::move(receive_waker_);
    lock.Release();
    if (wake_receiver) receive_waker.Wakeup();  // Optionally wake receiver
    wakeups.Wakeup();                           // Wake all waiting senders
  }

 private:
  Mutex mu_;                     // Mutex for thread safety
  const size_t max_queued_;      // Maximum allowed items in queue
  std::vector<T> queue_ ABSL_GUARDED_BY(mu_);  // The actual queue storage

  uint64_t batch_ ABSL_GUARDED_BY(mu_) = 1;  // Current batch counter
  Waker receive_waker_ ABSL_GUARDED_BY(mu_); // Waker for receiver
  WaitSet send_wakers_ ABSL_GUARDED_BY(mu_); // Wait set for senders
};

}  // namespace lock_based_mpscpipe_detail

// Forward declaration of receiver class
template <typename T>
class LockBasedMpscReceiver;

// Sender side of the MPSC queue
template <typename T>
class LockBasedMpscSender {
 public:
  // Default and copy/move constructors
  LockBasedMpscSender() = default;
  LockBasedMpscSender(const LockBasedMpscSender&) = default;
  LockBasedMpscSender& operator=(const LockBasedMpscSender&) = default;
  LockBasedMpscSender(LockBasedMpscSender&&) noexcept = default;
  LockBasedMpscSender& operator=(LockBasedMpscSender&&) noexcept = default;

  // Send an item without waiting for receipt confirmation
  auto Send(T t) { return SendGeneric<false>(std::move(t)); }

  // Send an item and wait for receipt confirmation
  auto SendAcked(T t) { return SendGeneric<true>(std::move(t)); }

  // Immediate send attempt without buffering
  StatusFlag UnbufferedImmediateSend(T t) {
    return StatusFlag(center_->template Send<false>(std::move(t)) !=
                      lock_based_mpscpipe_detail::Center<T>::kClosedBatch);
  }

 private:
  // Generic send implementation with template parameter for await receipt
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
  // Private constructor used by receiver to create senders
  explicit LockBasedMpscSender(
      RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center)
      : center_(std::move(center)) {}
  RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center_;
};

// Receiver side of the MPSC queue
template <typename T>
class LockBasedMpscReceiver {
 public:
  // Constructor with hint for maximum buffer size
  explicit LockBasedMpscReceiver(size_t max_buffer_hint)
      : center_(MakeRefCounted<lock_based_mpscpipe_detail::Center<T>>(
            std::max(static_cast<size_t>(1), max_buffer_hint / 2))) {}
  
  // Destructor - closes the receiver without waking
  ~LockBasedMpscReceiver() {
    if (center_ != nullptr) center_->ReceiverClosed(false);
  }

  // Explicitly mark the receiver as closed
  void MarkClosed() {
    if (center_ != nullptr) center_->ReceiverClosed(true);
  }

  // Disable copy operations
  LockBasedMpscReceiver(const LockBasedMpscReceiver&) = delete;
  LockBasedMpscReceiver& operator=(const LockBasedMpscReceiver&) = delete;

  // Move operations
  LockBasedMpscReceiver(LockBasedMpscReceiver&& other) noexcept
      : center_(std::move(other.center_)) {
    DCHECK(other.buffer_.empty());
  }
  LockBasedMpscReceiver& operator=(LockBasedMpscReceiver&& other) noexcept {
    DCHECK(other.buffer_.empty());
    center_ = std::move(other.center_);
    return *this;
  }

  // Create a new sender for this queue
  LockBasedMpscSender<T> MakeSender() {
    return LockBasedMpscSender<T>(center_);
  }

  // Get the next item from the queue
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

  // Get the next batch of items from the queue
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
  std::vector<T> buffer_;  // Local buffer for received items
  typename std::vector<T>::iterator buffer_it_ = buffer_.end();  // Iterator for current position
  RefCountedPtr<lock_based_mpscpipe_detail::Center<T>> center_;  // Reference to shared queue implementation
};

}  // namespace grpc_core

#endif
```