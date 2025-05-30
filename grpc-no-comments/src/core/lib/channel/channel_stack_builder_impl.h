// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_BUILDER_IMPL_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_BUILDER_IMPL_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack_builder.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class Blackboard;

class ChannelStackBuilderImpl final : public ChannelStackBuilder {
 public:
  using ChannelStackBuilder::ChannelStackBuilder;

  void SetBlackboards(const Blackboard* old_blackboard,
                      Blackboard* new_blackboard) {
    old_blackboard_ = old_blackboard;
    new_blackboard_ = new_blackboard;
  }

  absl::StatusOr<RefCountedPtr<grpc_channel_stack>> Build() override;

 private:
  const Blackboard* old_blackboard_ = nullptr;
  Blackboard* new_blackboard_ = nullptr;
};

}

#endif
