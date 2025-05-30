// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_POLL_H
#define GRPC_SRC_CORE_LIB_PROMISE_POLL_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "src/core/util/construct_destruct.h"

namespace grpc_core {

struct Pending {};
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool operator==(const Pending&,
                                                            const Pending&) {
  return true;
}

struct Empty {};
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool operator==(const Empty&,
                                                            const Empty&) {
  return true;
}
template <typename Sink>
void AbslStringify(Sink& sink, Empty) {
  sink.Append("{}");
}

template <typename T>
class Poll {
 public:

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(Pending) : ready_(false) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll() : ready_(false) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(const Poll& other)
      : ready_(other.ready_) {
    if (ready_) Construct(&value_, other.value_);
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(Poll&& other) noexcept
      : ready_(other.ready_) {
    if (ready_) Construct(&value_, std::move(other.value_));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll& operator=(const Poll& other) {
    if (ready_) {
      if (other.ready_) {
        value_ = other.value_;
      } else {
        Destruct(&value_);
        ready_ = false;
      }
    } else if (other.ready_) {
      Construct(&value_, other.value_);
      ready_ = true;
    }
    return *this;
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll& operator=(Poll&& other) noexcept {
    if (ready_) {
      if (other.ready_) {
        value_ = std::move(other.value_);
      } else {
        Destruct(&value_);
        ready_ = false;
      }
    } else if (other.ready_) {
      Construct(&value_, std::move(other.value_));
      ready_ = true;
    }
    return *this;
  }
  template <typename U>

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(U value) : ready_(true) {
    Construct(&value_, std::move(value));
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(T&& value) : ready_(true) {
    Construct(&value_, std::forward<T>(value));
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Poll() {
    if (ready_) Destruct(&value_);
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool pending() const { return !ready_; }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool ready() const { return ready_; }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION T& value() {
    DCHECK(ready());
    return value_;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION const T& value() const {
    DCHECK(ready());
    return value_;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION T* value_if_ready() {
    if (ready()) return &value_;
    return nullptr;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION const T* value_if_ready() const {
    if (ready()) return &value_;
    return nullptr;
  }

 private:

  bool ready_;

  union {
    T value_;
  };
};

template <typename T>
class Poll<T&&>;

template <>
class Poll<Empty> {
 public:

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(Pending) : ready_(false) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll() : ready_(false) {}
  Poll(const Poll& other) = default;
  Poll(Poll&& other) noexcept = default;
  Poll& operator=(const Poll& other) = default;
  Poll& operator=(Poll&& other) = default;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll(Empty) : ready_(true) {}
  ~Poll() = default;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool pending() const { return !ready_; }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION bool ready() const { return ready_; }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Empty value() const {
    DCHECK(ready());
    return Empty{};
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Empty* value_if_ready() {
    static Empty value;
    if (ready()) return &value;
    return nullptr;
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION const Empty* value_if_ready() const {
    static Empty value;
    if (ready()) return &value;
    return nullptr;
  }

 private:

  bool ready_;
};

template <>
class Poll<Pending>;

template <class T>
class Poll<Poll<T>>;

template <typename T>
struct PollTraits {
  using Type = T;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static constexpr bool is_poll() {
    return false;
  }
};

template <typename T>
struct PollTraits<Poll<T>> {
  using Type = T;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static constexpr bool is_poll() {
    return true;
  }
};

template <typename T>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline bool operator==(const Poll<T>& a,
                                                            const Poll<T>& b) {
  if (a.pending() && b.pending()) return true;
  if (a.ready() && b.ready()) return a.value() == b.value();
  return false;
}

template <typename T, typename U, typename SfinaeVoid = void>
struct PollCastImpl;

template <typename T, typename U>
struct PollCastImpl<T, Poll<U>> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Cast(Poll<U>&& poll) {
    if (poll.pending()) return Pending{};
    return static_cast<T>(std::move(poll.value()));
  }
};

template <typename T, typename U>
struct PollCastImpl<T, U, std::enable_if<!PollTraits<U>::is_poll()>> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Cast(U&& poll) {
    return Poll<T>(T(std::move(poll)));
  }
};

template <typename T>
struct PollCastImpl<T, T> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Cast(T&& poll) {
    return Poll<T>(std::move(poll));
  }
};

template <typename T>
struct PollCastImpl<T, Poll<T>> {
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static Poll<T> Cast(Poll<T>&& poll) {
    return std::move(poll);
  }
};

template <typename T, typename U>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline Poll<T> poll_cast(U poll) {
  return PollCastImpl<T, U>::Cast(std::move(poll));
}

template <typename T, typename F>
std::string PollToString(
    const Poll<T>& poll,
    F t_to_string = [](const T& t) { return t.ToString(); }) {
  if (poll.pending()) {
    return "<<pending>>";
  }
  return t_to_string(poll.value());
}

template <typename Sink, typename T>
void PollValueStringify(Sink& sink, const T& value) {
  absl::Format(&sink, "%v", value);
}

template <typename Sink, typename... Ts>
void PollValueStringify(Sink& sink, const std::tuple<Ts...>& values) {
  absl::Format(&sink, "(%v)", absl::StrJoin(values, ", "));
}

template <typename Sink, typename T>
void PollValueStringify(Sink& sink, const std::optional<T>& value) {
  if (!value.has_value()) {
    sink.Append("nullopt");
    return;
  }
  PollValueStringify(sink, *value);
}

template <typename Sink, typename T>
void PollValueStringify(Sink& sink, const absl::StatusOr<T>& value) {
  if (!value.ok()) {
    PollValueStringify(sink, value.status());
    return;
  }
  PollValueStringify(sink, *value);
}

template <typename Sink, typename T>
void AbslStringify(Sink& sink, const Poll<T>& poll) {
  if (poll.pending()) {
    absl::Format(&sink, "<<pending>>");
    return;
  }
  PollValueStringify(sink, poll.value());
}

template <typename Sink, typename T, typename Deleter>
void AbslStringify(
    Sink& sink, const Poll<std::optional<std::unique_ptr<T, Deleter>>>& poll) {
  if (poll.pending()) {
    absl::Format(&sink, "<<pending>>");
    return;
  }
  const auto& value = poll.value();
  if (value.has_value()) {
    PollValueStringify(sink, *value);
  } else {
    sink.Append("nullopt");
  }
}

}

#endif
