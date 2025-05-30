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
#include "src/core/util/construct_destruct.h"

namespace grpc_core {

namespace promise_detail {

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

}

template <typename C, typename T, typename F>
class If {
 private:
  using TrueFactory = promise_detail::OncePromiseFactory<void, T>;
  using FalseFactory = promise_detail::OncePromiseFactory<void, F>;
  using ConditionPromise = promise_detail::PromiseLike<C>;
  using TruePromise = typename TrueFactory::Promise;
  using FalsePromise = typename FalseFactory::Promise;
  using Result =
      typename PollTraits<decltype(std::declval<TruePromise>()())>::Type;

 public:
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If(C condition, T if_true, F if_false)
      : state_(Evaluating{ConditionPromise(std::move(condition)),
                          TrueFactory(std::move(if_true)),
                          FalseFactory(std::move(if_false))}) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> operator()() {
    return std::visit(CallPoll<false>{this}, state_);
  }

 private:
  struct Evaluating {
    ConditionPromise condition;
    TrueFactory if_true;
    FalseFactory if_false;
  };
  using State = std::variant<Evaluating, TruePromise, FalsePromise>;
  State state_;

  template <bool kSetState>
  struct CallPoll {
    using PollResult = Poll<Result>;

    If* const self;

    GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION PollResult
    operator()(Evaluating& evaluating) const {
      static_assert(
          !kSetState,
          "shouldn't need to set state coming through the initial branch");
      auto r = evaluating.condition();
      if (auto* p = r.value_if_ready()) {
        return ChooseIf(CallPoll<true>{self}, std::move(*p),
                        &evaluating.if_true, &evaluating.if_false);
      }
      return Pending();
    }

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

template <typename T, typename F>
class If<bool, T, F> {
 private:
  using TrueFactory = promise_detail::OncePromiseFactory<void, T>;
  using FalseFactory = promise_detail::OncePromiseFactory<void, F>;
  using TruePromise = typename TrueFactory::Promise;
  using FalsePromise = typename FalseFactory::Promise;
  using Result =
      typename PollTraits<decltype(std::declval<TruePromise>()())>::Type;

 public:
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
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~If() {
    if (condition_) {
      Destruct(&if_true_);
    } else {
      Destruct(&if_false_);
    }
  }

  If(const If&) = delete;
  If& operator=(const If&) = delete;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If(If&& other) noexcept
      : condition_(other.condition_) {
    if (condition_) {
      Construct(&if_true_, std::move(other.if_true_));
    } else {
      Construct(&if_false_, std::move(other.if_false_));
    }
  }
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION If& operator=(If&& other) noexcept {
    if (&other == this) return *this;
    Destruct(this);
    Construct(this, std::move(other));
    return *this;
  }

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
  bool condition_;
  union {
    TruePromise if_true_;
    FalsePromise if_false_;
  };

#ifndef NDEBUG
  std::unique_ptr<int> asan_canary_ = std::make_unique<int>(0);
#endif
};

template <typename C, typename T, typename F>
If(C, T, F) -> If<C, T, F>;

}

#endif
