
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_INTERNAL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_INTERNAL_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/call/call_destination.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/load_balancing/lb_policy.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/telemetry/call_tracer.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/unique_type_name.h"

#define GRPC_ARG_HEALTH_CHECK_SERVICE_NAME \
  "grpc.internal.health_check_service_name"

namespace grpc_core {

class ClientChannelLbCallState : public LoadBalancingPolicy::CallState {
 public:
  template <typename A>
  A* GetCallAttribute() const {
    return DownCast<A*>(GetCallAttribute(A::TypeName()));
  }

  virtual ServiceConfigCallData::CallAttributeInterface* GetCallAttribute(
      UniqueTypeName type) const = 0;
  virtual ClientCallTracer::CallAttemptTracer* GetCallAttemptTracer() const = 0;
};

class ClientChannelServiceConfigCallData final : public ServiceConfigCallData {
 public:
  explicit ClientChannelServiceConfigCallData(Arena* arena)
      : ServiceConfigCallData(arena) {}

  void SetOnCommit(absl::AnyInvocable<void()> on_commit) {
    CHECK(on_commit_ == nullptr);
    on_commit_ = std::move(on_commit);
  }

  void Commit() {
    auto on_commit = std::move(on_commit_);
    if (on_commit != nullptr) on_commit();
  }

 private:
  absl::AnyInvocable<void()> on_commit_;
};

template <>
struct ContextSubclass<ClientChannelServiceConfigCallData> {
  using Base = ServiceConfigCallData;
};

class SubchannelInterfaceWithCallDestination : public SubchannelInterface {
 public:
  using SubchannelInterface::SubchannelInterface;

  virtual RefCountedPtr<UnstartedCallDestination> call_destination() = 0;
};

}

#endif
