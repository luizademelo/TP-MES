// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_RACE_H
#define GRPC_SRC_CORE_LIB_PROMISE_RACE_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/util/json/json.h"

namespace grpc_core {

template <typename... Promises>
class Race;

template <typename Promise, typename... Promises>
class Race<Promise, Promises...> {
 public:
  using Result = decltype(std::declval<Promise>()());

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Race(Promise promise,
                                                     Promises... promises)
      : promise_(std::move(promise)), next_(std::move(promises)...) {}

  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Result operator()() {

    auto r = promise_();
    if (r.pending()) {

      return next_();
    }

    return std::move(r.value());
  }

  Json ToJson() const {
    Json::Object obj;
    Json::Array array;
    AddJson(array);
    obj["race"] = Json::FromArray(std::move(array));
    return Json::FromObject(std::move(obj));
  }

  void AddJson(Json::Array& array) const {
    array.emplace_back(PromiseAsJson(promise_));
    next_.AddJson(array);
  }

 private:

  Promise promise_;

  Race<Promises...> next_;
};

template <typename Promise>
class Race<Promise> {
 public:
  using Result = decltype(std::declval<Promise>()());
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION explicit Race(Promise promise)
      : promise_(std::move(promise)) {}
  GPR_ATTRIBUTE_ALWAYS_INLINE_FUNCTION Result operator()() {
    return promise_();
  }

  Json ToJson() const { return PromiseAsJson(promise_); }

  void AddJson(Json::Array& array) const {
    array.emplace_back(PromiseAsJson(promise_));
  }

 private:
  Promise promise_;
};

template <typename... Promises>
Race(Promises...) -> Race<Promises...>;

}

#endif
