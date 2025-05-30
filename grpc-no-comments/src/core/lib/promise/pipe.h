// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_PIPE_H
#define GRPC_SRC_CORE_LIB_PROMISE_PIPE_H

#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <stdlib.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/promise/if.h"
#include "src/core/lib/promise/interceptor_list.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

namespace pipe_detail {
template <typename T>
class Center;
}

template <typename T>
struct Pipe;

template <typename T>
class NextResult final {
 public:
  NextResult() : center_(nullptr) {}
  explicit NextResult(RefCountedPtr<pipe_detail::Center<T>> center)
      : center_(std::move(center)) {
    CHECK(center_ != nullptr);
  }
  explicit NextResult(bool cancelled)
      : center_(nullptr), cancelled_(cancelled) {}
  ~NextResult();
  NextResult(const NextResult&) = delete;
  NextResult& operator=(const NextResult&) = delete;
  NextResult(NextResult&& other) noexcept = default;
  NextResult& operator=(NextResult&& other) noexcept = default;

  using value_type = T;

  void reset();
  bool has_value() const;

  const T& value() const {
    CHECK(has_value());
    return **this;
  }
  T& value() {
    CHECK(has_value());
    return **this;
  }
  const T& operator*() const;
  T& operator*();

  bool cancelled() const { return cancelled_; }

 private:
  RefCountedPtr<pipe_detail::Center<T>> center_;
  bool cancelled_;
};

namespace pipe_detail {

template <typename T>
class Push;
template <typename T>
class Next;

template <typename T>
class Center : public InterceptorList<T> {
 public:

  Center() {
    refs_ = 2;
    value_state_ = ValueState::kEmpty;
  }

  void IncrementRefCount() {
    GRPC_TRACE_VLOG(promise_primitives, 2)
        << DebugOpString("IncrementRefCount");
    refs_++;
    DCHECK_NE(refs_, 0);
  }

  RefCountedPtr<Center> Ref() {
    IncrementRefCount();
    return RefCountedPtr<Center>(this);
  }

  void Unref() {
    GRPC_TRACE_VLOG(promise_primitives, 2) << DebugOpString("Unref");
    DCHECK_GT(refs_, 0);
    refs_--;
    if (0 == refs_) {
      this->~Center();
    }
  }

  Poll<bool> Push(T* value) {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("Push");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kClosed:
      case ValueState::kReadyClosed:
      case ValueState::kCancelled:
      case ValueState::kWaitingForAckAndClosed:
        return false;
      case ValueState::kReady:
      case ValueState::kAcked:
      case ValueState::kWaitingForAck:
        return on_empty_.pending();
      case ValueState::kEmpty:
        value_state_ = ValueState::kReady;
        value_ = std::move(*value);
        on_full_.Wake();
        return true;
    }
    GPR_UNREACHABLE_CODE(return false);
  }

  Poll<bool> PollAck() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("PollAck");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kClosed:
        return true;
      case ValueState::kCancelled:
        return false;
      case ValueState::kReady:
      case ValueState::kReadyClosed:
      case ValueState::kEmpty:
      case ValueState::kWaitingForAck:
      case ValueState::kWaitingForAckAndClosed:
        return on_empty_.pending();
      case ValueState::kAcked:
        value_state_ = ValueState::kEmpty;
        on_empty_.Wake();
        return true;
    }
    return true;
  }

  Poll<std::optional<T>> Next() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("Next");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kEmpty:
      case ValueState::kAcked:
      case ValueState::kWaitingForAck:
      case ValueState::kWaitingForAckAndClosed:
        return on_full_.pending();
      case ValueState::kReadyClosed:
        value_state_ = ValueState::kWaitingForAckAndClosed;
        return std::move(value_);
      case ValueState::kReady:
        value_state_ = ValueState::kWaitingForAck;
        return std::move(value_);
      case ValueState::kClosed:
      case ValueState::kCancelled:
        return std::nullopt;
    }
    GPR_UNREACHABLE_CODE(return std::nullopt);
  }

  Poll<bool> PollClosedForSender() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugOpString("PollClosedForSender");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kEmpty:
      case ValueState::kAcked:
      case ValueState::kReady:
      case ValueState::kWaitingForAck:
        return on_closed_.pending();
      case ValueState::kWaitingForAckAndClosed:
      case ValueState::kReadyClosed:
      case ValueState::kClosed:
        return false;
      case ValueState::kCancelled:
        return true;
    }
    GPR_UNREACHABLE_CODE(return true);
  }

  Poll<bool> PollClosedForReceiver() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << DebugOpString("PollClosedForReceiver");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kEmpty:
      case ValueState::kAcked:
      case ValueState::kReady:
      case ValueState::kReadyClosed:
      case ValueState::kWaitingForAck:
      case ValueState::kWaitingForAckAndClosed:
        return on_closed_.pending();
      case ValueState::kClosed:
        return false;
      case ValueState::kCancelled:
        return true;
    }
    GPR_UNREACHABLE_CODE(return true);
  }

  Poll<Empty> PollEmpty() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("PollEmpty");
    DCHECK_NE(refs_, 0);
    switch (value_state_) {
      case ValueState::kReady:
      case ValueState::kReadyClosed:
        return on_empty_.pending();
      case ValueState::kWaitingForAck:
      case ValueState::kWaitingForAckAndClosed:
      case ValueState::kAcked:
      case ValueState::kEmpty:
      case ValueState::kClosed:
      case ValueState::kCancelled:
        return Empty{};
    }
    GPR_UNREACHABLE_CODE(return Empty{});
  }

  void AckNext() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("AckNext");
    switch (value_state_) {
      case ValueState::kReady:
      case ValueState::kWaitingForAck:
        value_state_ = ValueState::kAcked;
        on_empty_.Wake();
        break;
      case ValueState::kReadyClosed:
      case ValueState::kWaitingForAckAndClosed:
        this->ResetInterceptorList();
        value_state_ = ValueState::kClosed;
        on_closed_.Wake();
        on_empty_.Wake();
        on_full_.Wake();
        break;
      case ValueState::kClosed:
      case ValueState::kCancelled:
        break;
      case ValueState::kEmpty:
      case ValueState::kAcked:
        abort();
    }
  }

  void MarkClosed() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("MarkClosed");
    switch (value_state_) {
      case ValueState::kEmpty:
      case ValueState::kAcked:
        this->ResetInterceptorList();
        value_state_ = ValueState::kClosed;
        on_empty_.Wake();
        on_full_.Wake();
        on_closed_.Wake();
        break;
      case ValueState::kReady:
        value_state_ = ValueState::kReadyClosed;
        on_closed_.Wake();
        break;
      case ValueState::kWaitingForAck:
        value_state_ = ValueState::kWaitingForAckAndClosed;
        on_closed_.Wake();
        break;
      case ValueState::kReadyClosed:
      case ValueState::kClosed:
      case ValueState::kCancelled:
      case ValueState::kWaitingForAckAndClosed:
        break;
    }
  }

  void MarkCancelled() {
    GRPC_TRACE_LOG(promise_primitives, INFO) << DebugOpString("MarkCancelled");
    switch (value_state_) {
      case ValueState::kEmpty:
      case ValueState::kAcked:
      case ValueState::kReady:
      case ValueState::kReadyClosed:
      case ValueState::kWaitingForAck:
      case ValueState::kWaitingForAckAndClosed:
        this->ResetInterceptorList();
        value_state_ = ValueState::kCancelled;
        on_empty_.Wake();
        on_full_.Wake();
        on_closed_.Wake();
        break;
      case ValueState::kClosed:
      case ValueState::kCancelled:
        break;
    }
  }

  bool cancelled() { return value_state_ == ValueState::kCancelled; }

  T& value() { return value_; }
  const T& value() const { return value_; }

  std::string DebugTag() {
    if (auto* activity = GetContext<Activity>()) {
      return absl::StrCat(activity->DebugTag(), " PIPE[0x", absl::Hex(this),
                          "]: ");
    } else {
      return absl::StrCat("PIPE[0x", reinterpret_cast<uintptr_t>(this), "]: ");
    }
  }

 private:

  enum class ValueState : uint8_t {

    kEmpty,

    kReady,

    kWaitingForAck,

    kAcked,

    kClosed,

    kReadyClosed,

    kWaitingForAckAndClosed,

    kCancelled,
  };

  std::string DebugOpString(std::string op) {
    return absl::StrCat(DebugTag(), op, " refs=", refs_,
                        " value_state=", ValueStateName(value_state_),
                        " on_empty=", on_empty_.DebugString().c_str(),
                        " on_full=", on_full_.DebugString().c_str(),
                        " on_closed=", on_closed_.DebugString().c_str());
  }

  static const char* ValueStateName(ValueState state) {
    switch (state) {
      case ValueState::kEmpty:
        return "Empty";
      case ValueState::kReady:
        return "Ready";
      case ValueState::kAcked:
        return "Acked";
      case ValueState::kClosed:
        return "Closed";
      case ValueState::kReadyClosed:
        return "ReadyClosed";
      case ValueState::kWaitingForAck:
        return "WaitingForAck";
      case ValueState::kWaitingForAckAndClosed:
        return "WaitingForAckAndClosed";
      case ValueState::kCancelled:
        return "Cancelled";
    }
    GPR_UNREACHABLE_CODE(return "unknown");
  }

  T value_;

  uint8_t refs_;

  ValueState value_state_;
  IntraActivityWaiter on_empty_;
  IntraActivityWaiter on_full_;
  IntraActivityWaiter on_closed_;

#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);
#endif
};

}

template <typename T>
class PipeSender {
 public:
  using PushType = pipe_detail::Push<T>;

  PipeSender(const PipeSender&) = delete;
  PipeSender& operator=(const PipeSender&) = delete;
  PipeSender(PipeSender&& other) noexcept = default;
  PipeSender& operator=(PipeSender&& other) noexcept = default;

  ~PipeSender() {
    if (center_ != nullptr) center_->MarkClosed();
  }

  void Close() {
    if (center_ != nullptr) {
      center_->MarkClosed();
      center_.reset();
    }
  }

  void CloseWithError() {
    if (center_ != nullptr) {
      center_->MarkCancelled();
      center_.reset();
    }
  }

  void Swap(PipeSender<T>* other) { std::swap(center_, other->center_); }

  PushType Push(T value);

  auto AwaitClosed() {
    return [center = center_]() { return center->PollClosedForSender(); };
  }

  template <typename Fn>
  void InterceptAndMap(Fn f, DebugLocation from = {}) {
    center_->PrependMap(std::move(f), from);
  }

  template <typename Fn, typename OnHalfClose>
  void InterceptAndMap(Fn f, OnHalfClose cleanup_fn, DebugLocation from = {}) {
    center_->PrependMapWithCleanup(std::move(f), std::move(cleanup_fn), from);
  }

 private:
  friend struct Pipe<T>;
  explicit PipeSender(pipe_detail::Center<T>* center) : center_(center) {}
  RefCountedPtr<pipe_detail::Center<T>> center_;

#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);
#endif
};

template <typename T>
class PipeReceiver;

namespace pipe_detail {

template <typename T>
class Next {
 public:
  Next(const Next&) = delete;
  Next& operator=(const Next&) = delete;
  Next(Next&& other) noexcept = default;
  Next& operator=(Next&& other) noexcept = default;

  Poll<std::optional<T>> operator()() {
    return center_ == nullptr ? std::nullopt : center_->Next();
  }

 private:
  friend class PipeReceiver<T>;
  explicit Next(RefCountedPtr<Center<T>> center) : center_(std::move(center)) {}

  RefCountedPtr<Center<T>> center_;
};

}

template <typename T>
class PipeReceiver {
 public:
  PipeReceiver(const PipeReceiver&) = delete;
  PipeReceiver& operator=(const PipeReceiver&) = delete;
  PipeReceiver(PipeReceiver&& other) noexcept = default;
  PipeReceiver& operator=(PipeReceiver&& other) noexcept = default;
  ~PipeReceiver() {
    if (center_ != nullptr) center_->MarkCancelled();
  }

  void Swap(PipeReceiver<T>* other) { std::swap(center_, other->center_); }

  auto Next() {
    return Seq(pipe_detail::Next<T>(center_), [center = center_](
                                                  std::optional<T> value) {
      bool open = value.has_value();
      bool cancelled = center == nullptr ? true : center->cancelled();
      return If(
          open,
          [center = std::move(center), value = std::move(value)]() mutable {
            auto run = center->Run(std::move(value));
            return Map(std::move(run), [center = std::move(center)](
                                           std::optional<T> value) mutable {
              if (value.has_value()) {
                center->value() = std::move(*value);
                return NextResult<T>(std::move(center));
              } else {
                center->MarkCancelled();
                return NextResult<T>(true);
              }
            });
          },
          [cancelled]() { return NextResult<T>(cancelled); });
    });
  }

  auto AwaitClosed() {
    return [center = center_]() -> Poll<bool> {
      if (center == nullptr) return false;
      return center->PollClosedForReceiver();
    };
  }

  auto AwaitEmpty() {
    return [center = center_]() { return center->PollEmpty(); };
  }

  void CloseWithError() {
    if (center_ != nullptr) {
      center_->MarkCancelled();
      center_.reset();
    }
  }

  template <typename Fn>
  void InterceptAndMap(Fn f, DebugLocation from = {}) {
    center_->AppendMap(std::move(f), from);
  }

  template <typename Fn, typename OnHalfClose>
  void InterceptAndMapWithHalfClose(Fn f, OnHalfClose cleanup_fn,
                                    DebugLocation from = {}) {
    center_->AppendMapWithCleanup(std::move(f), std::move(cleanup_fn), from);
  }

 private:
  friend struct Pipe<T>;
  explicit PipeReceiver(pipe_detail::Center<T>* center) : center_(center) {}
  RefCountedPtr<pipe_detail::Center<T>> center_;
};

namespace pipe_detail {

template <typename T>
class Push {
 public:
  Push(const Push&) = delete;

  Push& operator=(const Push&) = delete;
  Push(Push&& other) noexcept = default;
  Push& operator=(Push&& other) noexcept = default;

  Poll<bool> operator()() {
    if (center_ == nullptr) {
      GRPC_TRACE_VLOG(promise_primitives, 2)
          << GetContext<Activity>()->DebugTag()
          << " Pipe push has a null center";
      return false;
    }
    if (auto* p = std::get_if<T>(&state_)) {
      auto r = center_->Push(p);
      if (auto* ok = r.value_if_ready()) {
        state_.template emplace<AwaitingAck>();
        if (!*ok) return false;
      } else {
        return Pending{};
      }
    }
    DCHECK(std::holds_alternative<AwaitingAck>(state_));
    return center_->PollAck();
  }

 private:
  struct AwaitingAck {};

  friend class PipeSender<T>;
  explicit Push(RefCountedPtr<pipe_detail::Center<T>> center, T push)
      : center_(std::move(center)), state_(std::move(push)) {}

  RefCountedPtr<Center<T>> center_;
  std::variant<T, AwaitingAck> state_;
};

}

template <typename T>
pipe_detail::Push<T> PipeSender<T>::Push(T value) {
  return pipe_detail::Push<T>(center_ == nullptr ? nullptr : center_->Ref(),
                              std::move(value));
}

template <typename T>
using PipeReceiverNextType = decltype(std::declval<PipeReceiver<T>>().Next());

template <typename T>
bool NextResult<T>::has_value() const {
  return center_ != nullptr;
}

template <typename T>
T& NextResult<T>::operator*() {
  return center_->value();
}

template <typename T>
const T& NextResult<T>::operator*() const {
  return center_->value();
}

template <typename T>
NextResult<T>::~NextResult() {
  if (center_ != nullptr) center_->AckNext();
}

template <typename T>
void NextResult<T>::reset() {
  if (center_ != nullptr) {
    center_->AckNext();
    center_.reset();
  }
}

template <typename T>
struct Pipe {
  Pipe() : Pipe(GetContext<Arena>()) {}
  explicit Pipe(Arena* arena) : Pipe(arena->New<pipe_detail::Center<T>>()) {}
  Pipe(const Pipe&) = delete;
  Pipe& operator=(const Pipe&) = delete;
  Pipe(Pipe&&) noexcept = default;
  Pipe& operator=(Pipe&&) noexcept = default;

  PipeSender<T> sender;
  PipeReceiver<T> receiver;

 private:
  explicit Pipe(pipe_detail::Center<T>* center)
      : sender(center), receiver(center) {}
};

}

#endif
