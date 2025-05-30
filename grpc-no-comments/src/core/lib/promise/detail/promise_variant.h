// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_VARIANT_H
#define GRPC_SRC_CORE_LIB_PROMISE_DETAIL_PROMISE_VARIANT_H

#include <variant>

namespace grpc_core {

namespace promise_detail {

class PollVisitor {
 public:
  template <typename T>
  auto operator()(T& x) {
    return x();
  }
};

template <typename V>
class PromiseVariant {
 public:
  explicit PromiseVariant(V variant) : variant_(std::move(variant)) {}
  auto operator()() { return std::visit(PollVisitor(), variant_); }

 private:
  V variant_;
};

}

}

#endif
