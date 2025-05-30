
// Copyright 2015 gRPC authors.

#include "src/core/load_balancing/lb_policy.h"

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/pollset_set.h"

namespace grpc_core {

LoadBalancingPolicy::LoadBalancingPolicy(Args args, intptr_t initial_refcount)
    : InternallyRefCounted(GRPC_TRACE_FLAG_ENABLED(lb_policy_refcount)
                               ? "LoadBalancingPolicy"
                               : nullptr,
                           initial_refcount),
      work_serializer_(std::move(args.work_serializer)),
      interested_parties_(grpc_pollset_set_create()),
      channel_control_helper_(std::move(args.channel_control_helper)),
      channel_args_(std::move(args.args)) {}

LoadBalancingPolicy::~LoadBalancingPolicy() {
  grpc_pollset_set_destroy(interested_parties_);
}

void LoadBalancingPolicy::Orphan() {
  ShutdownLocked();
  Unref(DEBUG_LOCATION, "Orphan");
}

LoadBalancingPolicy::SubchannelPicker::SubchannelPicker()
    : DualRefCounted(GRPC_TRACE_FLAG_ENABLED(lb_policy_refcount)
                         ? "SubchannelPicker"
                         : nullptr) {}

LoadBalancingPolicy::PickResult LoadBalancingPolicy::QueuePicker::Pick(
    PickArgs ) {

  MutexLock lock(&mu_);
  if (parent_ != nullptr) {
    auto* parent = parent_.release();
    ExecCtx::Run(DEBUG_LOCATION,
                 GRPC_CLOSURE_CREATE(
                     [](void* arg, grpc_error_handle ) {
                       auto* parent = static_cast<LoadBalancingPolicy*>(arg);
                       parent->work_serializer()->Run([parent]() {
                         parent->ExitIdleLocked();
                         parent->Unref();
                       });
                     },
                     parent, nullptr),
                 absl::OkStatus());
  }
  return PickResult::Queue();
}

}
