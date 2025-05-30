// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_CALL_DESTINATION_H
#define GRPC_SRC_CORE_CALL_CALL_DESTINATION_H

#include <grpc/support/port_platform.h>

#include "src/core/call/call_spine.h"
#include "src/core/util/orphanable.h"

namespace grpc_core {

class UnstartedCallDestination
    : public DualRefCounted<UnstartedCallDestination> {
 public:
  using DualRefCounted::DualRefCounted;

  ~UnstartedCallDestination() override = default;

  virtual void StartCall(UnstartedCallHandler unstarted_call_handler) = 0;
};

class CallDestination : public DualRefCounted<CallDestination> {
 public:
  virtual void HandleCall(CallHandler unstarted_call_handler) = 0;
};

template <typename HC>
auto MakeCallDestinationFromHandlerFunction(HC handle_call) {
  class Impl : public CallDestination {
   public:
    explicit Impl(HC handle_call) : handle_call_(std::move(handle_call)) {}

    void Orphaned() override {}

    void HandleCall(CallHandler call_handler) override {
      handle_call_(std::move(call_handler));
    }

   private:
    HC handle_call_;
  };
  return MakeRefCounted<Impl>(std::move(handle_call));
}

}

#endif
