// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_LOAD_BALANCED_CALL_DESTINATION_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_LOAD_BALANCED_CALL_DESTINATION_H

#include "absl/functional/any_invocable.h"
#include "src/core/call/call_destination.h"
#include "src/core/client_channel/client_channel.h"
#include "src/core/lib/promise/context.h"
#include "src/core/load_balancing/lb_policy.h"

namespace grpc_core {

using LbOnCommit = absl::AnyInvocable<void()>;
template <>
struct ContextType<LbOnCommit> {};

class LoadBalancedCallDestination final : public UnstartedCallDestination {
 public:
  explicit LoadBalancedCallDestination(ClientChannel::PickerObservable picker)
      : picker_(std::move(picker)) {}

  void Orphaned() override {}

  void StartCall(UnstartedCallHandler unstarted_handler) override;

 private:
  ClientChannel::PickerObservable picker_;
};

}

#endif
