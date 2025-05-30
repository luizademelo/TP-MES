// Copyright 2021 gRPC authors.

#include "src/core/lib/channel/channel_args_preconditioning.h"

#include <grpc/support/port_platform.h>

#include <utility>

namespace grpc_core {

void ChannelArgsPreconditioning::Builder::RegisterStage(Stage stage) {
  stages_.emplace_back(std::move(stage));
}

ChannelArgsPreconditioning ChannelArgsPreconditioning::Builder::Build() {
  ChannelArgsPreconditioning preconditioning;
  preconditioning.stages_ = std::move(stages_);
  return preconditioning;
}

ChannelArgs ChannelArgsPreconditioning::PreconditionChannelArgs(
    const grpc_channel_args* args) const {
  ChannelArgs channel_args = ChannelArgsBuiltinPrecondition(args);
  for (auto& stage : stages_) {
    channel_args = stage(std::move(channel_args));
  }
  return channel_args;
}

}
