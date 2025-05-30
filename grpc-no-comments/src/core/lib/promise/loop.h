// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_LOOP_H
#define GRPC_SRC_CORE_LIB_PROMISE_LOOP_H

#include <grpc/support/port_platform.h>

#include <utility>
#include <variant>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/detail/promise_factory.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/util/construct_destruct.h"

namespace grpc_core {

struct Continue {};

template <typename T>
using LoopCtl = std::variant<Continue, T>;

namespace promise_detail {

template <typename T>
struct LoopTraits;

template <typename T>
struct LoopTraits<LoopCtl<T>> {
  using Result = T;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static LoopCtl<T> ToLoopCtl(
      LoopCtl<T> value) {
    return value;
  }
};

template <typename T>
struct LoopTraits<absl::StatusOr<LoopCtl<T>>> {
  using Result = absl::StatusOr<T>;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static LoopCtl<Result> ToLoopCtl(
      absl::StatusOr<LoopCtl<T>> value) {
    if (!value.ok()) return value.status();
    auto& inner = *value;
    if (std::holds_alternative<Continue>(inner)) return Continue{};
    return std::get<T>(std::move(inner));
  }
};

template <>
struct LoopTraits<absl::StatusOr<LoopCtl<absl::Status>>> {
  using Result = absl::Status;
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION static LoopCtl<Result> ToLoopCtl(
      absl::StatusOr<LoopCtl<absl::Status>> value) {
    if (!value.ok()) return value.status();
    const auto& inner = *value;
    if (std::holds_alternative<Continue>(inner)) return Continue{};
    return std::get<absl::Status>(inner);
  }
};

}

template <typename F>
class Loop {
 private:
  static_assert(promise_detail::kIsRepeatedPromiseFactory<void, F>);

  using Factory = promise_detail::RepeatedPromiseFactory<void, F>;
  using PromiseType = decltype(std::declval<Factory>().Make());
  using PromiseResult = typename PromiseType::Result;

 public:
  using Result = typename promise_detail::LoopTraits<PromiseResult>::Result;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Loop(F f)
      : factory_(std::move(f)) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION ~Loop() {
    if (started_) Destruct(&promise_);
  }

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Loop(Loop&& loop) noexcept
      : factory_(std::move(loop.factory_)), started_(loop.started_) {
    if (started_) Construct(&promise_, std::move(loop.promise_));
  }

  Loop(const Loop& loop) = delete;
  Loop& operator=(const Loop& loop) = delete;

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Poll<Result> operator()() {
    GRPC_TRACE_LOG(promise_primitives, INFO)
        << "loop[" << this << "] begin poll started=" << started_;
    if (!started_) {
      started_ = true;
      Construct(&promise_, factory_.Make());
    }
    while (true) {

      auto promise_result = promise_();

      if (auto* p = promise_result.value_if_ready()) {

        auto lc =
            promise_detail::LoopTraits<PromiseResult>::ToLoopCtl(std::move(*p));
        if (std::holds_alternative<Continue>(lc)) {
          GRPC_TRACE_LOG(promise_primitives, INFO)
              << "loop[" << this << "] iteration complete, continue";
          Destruct(&promise_);
          Construct(&promise_, factory_.Make());
          continue;
        }
        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "loop[" << this << "] iteration complete, return";

        return std::get<Result>(std::move(lc));
      } else {

        GRPC_TRACE_LOG(promise_primitives, INFO)
            << "loop[" << this << "] pending";
        return Pending();
      }
    }
  }

  Json ToJson() const {
    Json::Object obj;
    obj["loop_factory"] = Json::FromString(std::string(TypeName<Factory>()));
    if (started_) {
      obj["promise"] = PromiseAsJson(promise_);
    }
    return Json::FromObject(std::move(obj));
  }

 private:
  GPR_NO_UNIQUE_ADDRESS Factory factory_;
  GPR_NO_UNIQUE_ADDRESS union {
    GPR_NO_UNIQUE_ADDRESS PromiseType promise_;
  };
  bool started_ = false;
};

template <typename F>
Loop(F) -> Loop<F>;

}

#endif
