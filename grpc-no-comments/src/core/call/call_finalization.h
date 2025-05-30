// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_CALL_FINALIZATION_H
#define GRPC_SRC_CORE_CALL_CALL_FINALIZATION_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/transport/call_final_info.h"

namespace grpc_core {

class CallFinalization {
 public:

  template <typename F>
  void Add(F&& t) {
    first_ =
        GetContext<Arena>()->New<FuncFinalizer<F>>(std::forward<F>(t), first_);
  }

  void Run(const grpc_call_final_info* final_info) {
    if (Finalizer* f = std::exchange(first_, nullptr)) f->Run(final_info);
  }

 private:

  class Finalizer {
   public:

    virtual void Run(const grpc_call_final_info* final_info) = 0;

   protected:
    ~Finalizer() {}
  };

  template <typename F>
  class FuncFinalizer final : public Finalizer {
   public:
    FuncFinalizer(F&& f, Finalizer* next)
        : next_(next), f_(std::forward<F>(f)) {}

    void Run(const grpc_call_final_info* final_info) override {
      f_(final_info);
      Finalizer* next = next_;
      this->~FuncFinalizer();
      if (next != nullptr) next->Run(final_info);
    }

   private:
    Finalizer* next_;
    F f_;
  };

  Finalizer* first_ = nullptr;
};

template <>
struct ContextType<CallFinalization> {};

}

#endif
