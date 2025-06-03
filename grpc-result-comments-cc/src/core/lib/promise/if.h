Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_IF_H
#define GRPC_SRC_CORE_LIB_PROMISE_IF_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>
#include <variant>

#include "absl/status/statusor.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/detail/promise_like.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/util/construct_destruct.h"

namespace grpc_core {

namespace promise_detail {

// Helper function that chooses between two promise factories based on a boolean condition
// and immediately calls the selected promise.
// Template parameters:
// - CallPoll: The polling function type
// - T: Type of the "if_true" promise factory
// - F: Type of the "if_false" promise factory
template <typename CallPoll, typename T, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline typename CallPoll::PollResult
ChooseIf(CallPoll call_poll, bool result, T* if_true, F* if_false) {
  if (result) {
    auto promise = if_true->Make();
    return call_poll(promise);
  } else {
    auto promise = if_false->Make();
    return call_poll(promise);
  }
}

// Overload of ChooseIf that handles absl::StatusOr<bool> conditions.
// If the status is not OK, returns the error status immediately.
// Otherwise behaves like the boolean version.
template <typename CallPoll, typename T, typename F>
GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION inline typename CallPoll::PollResult
ChooseIf(CallPoll call_poll, absl::StatusOr<bool> result, T* if_true,
         F* if_false) {
  if (!result.ok()) {
    return typename CallPoll::PollResult(result.status());
  } else if (*result) {
    auto promise = if_true->Make();
    return call_poll(promise);
  } else {
    auto promise = if_false->Make();
    return call_poll(promise);
  }
}

}  // namespace promise_detail

// Main If template class that implements conditional promise execution.
// Template parameters:
// - C: Type of the condition (must be convertible to bool or a promise returning bool)
// - T: Type of the "if_true" branch
// - F: Type of the "if_false" branch
template <typename C, typename T, typename F>
class If {
 private:
  // Type aliases for promise factories and promises
  using TrueFactory = promise_detail::OncePromiseFactory<void, T>;
  using FalseFactory = promise_detail::OncePromiseFactory<void, F>;
  using ConditionPromise = promise_detail::PromiseLike<C>;
  using TruePromise = typename TrueFactory::Promise;
  using FalsePromise = typename FalseFactory::Promise;
  using Result =
      typename PollTraits<decltype(std::declval<TruePromise>()())>::Type;

 public:
  // Constructor that takes the condition and both branches
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If(C condition, T if_true, F if_false)
      : state_(Evaluating{ConditionPromise(std::move(condition)),
                          TrueFactory(std::move(if_true)),
                          FalseFactory(std::move(if_false))}) {}

  // Main polling function that drives the promise execution
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> operator()() {
    return std::visit(CallPoll<false>{this}, state_);
  }

 private:
  // State representing the initial evaluation phase
  struct Evaluating {
    ConditionPromise condition;  // Promise for the condition
    TrueFactory if_true;         // Factory for true branch
    FalseFactory if_false;       // Factory for false branch
  };
  
  // Variant that can hold either the evaluating state or one of the branch promises
  using State = std::variant<Evaluating, TruePromise, FalsePromise>;
  State state_;

  // Helper struct for polling the condition and branches
  template <bool kSetState>
  struct CallPoll {
    using PollResult = Poll<Result>;

    If* const self;  // Pointer to parent If instance

    // Handles the Evaluating state - polls the condition and chooses a branch
    GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION PollResult
    operator()(Evaluating& evaluating) const {
      static_assert(
          !kSetState,
          "shouldn't need to set state coming through the initial branch");
      auto r = evaluating.condition();
      if (auto* p = r.value_if_ready()) {
        return promise_detail::ChooseIf(CallPoll<true>{self}, std::move(*p),
                        &evaluating.if_true, &evaluating.if_false);
      }
      return Pending();
    }

    // Handles either branch promise - polls it and updates state if needed
    template <class Promise>
    GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION PollResult
    operator()(Promise& promise) const {
      auto r = promise();
      if (kSetState && r.pending()) {
        self->state_.template emplace<Promise>(std::move(promise));
      }
      return r;
    }
  };
};

// Specialization of If for when the condition is a simple bool
template <typename T, typename F>
class If<bool, T, F> {
 private:
  // Type aliases for promise factories and promises
  using TrueFactory = promise_detail::OncePromiseFactory<void, T>;
  using FalseFactory = promise_detail::OncePromiseFactory<void, F>;
  using TruePromise = typename TrueFactory::Promise;
  using FalsePromise = typename FalseFactory::Promise;
  using Result =
      typename PollTraits<decltype(std::declval<TruePromise>()())>::Type;

 public:
  // Constructor that immediately creates the appropriate branch promise
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If(bool condition, T if_true, F if_false)
      : condition_(condition) {
    TrueFactory true_factory(std::move(if_true));
    FalseFactory false_factory(std::move(if_false));
    if (condition_) {
      Construct(&if_true_, true_factory.Make());
    } else {
      Construct(&if_false_, false_factory.Make());
    }
  }

  // Destructor that properly destroys the active branch promise
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~If() {
    if (condition_) {
      Destruct(&if_true_);
    } else {
      Destruct(&if_false_);
    }
  }

  // Deleted copy constructor/assignment
  If(const If&) = delete;
  If& operator=(const If&) = delete;

  // Move constructor - properly moves the active branch promise
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If(If&& other) noexcept
      : condition_(other.condition_) {
    if (condition_) {
      Construct(&if_true_, std::move(other.if_true_));
    } else {
      Construct(&if_false_, std::move(other.if_false_));
    }
  }

  // Move assignment operator - properly handles self-assignment
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If& operator=(If&& other) noexcept {
    if (&other == this) return *this;
    Destruct(this);
    Construct(this, std::move(other));
    return *this;
  }

  // Main polling function - polls the active branch promise
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> operator()() {
#ifndef NDEBUG
    asan_canary_ = std::make_unique<int>(1 + *asan_canary_);
#endif
    if (condition_) {
      return if_true_();
    } else {
      return if_false_();
    }
  }

  // Converts the If instance to JSON for debugging purposes
  Json ToJson() const {
    Json::Object json;
    json["condition"] = Json::FromBool(condition_);
    json["true"] = Json::FromString(std::string(TypeName<TruePromise>()));
    json["false"] = Json::FromString(std::string(TypeName<FalsePromise>()));
    if (condition_) {
      json["promise"] = if_true_.ToJson();
    } else {
      json["promise"] = if_false_.ToJson();
    }
    return Json::FromObject(std::move(json));
  }

 private:
  bool condition_;  // The boolean condition
  union {
    TruePromise if_true_;   // Active when condition is true
    FalsePromise if_false_; // Active when condition is false
  };

#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);  // Debug helper
#endif
};

// Deduction guide for If template
template <typename C, typename T, typename F>
If(C, T, F) -> If<C, T, F>;

}  // namespace grpc_core

#endif
```