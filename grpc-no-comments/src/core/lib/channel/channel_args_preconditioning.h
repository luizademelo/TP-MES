// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_ARGS_PRECONDITIONING_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_ARGS_PRECONDITIONING_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <functional>
#include <vector>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

class ChannelArgsPreconditioning {
 public:

  using Stage = std::function<ChannelArgs(ChannelArgs)>;

  class Builder {
   public:

    void RegisterStage(Stage stage);

    ChannelArgsPreconditioning Build();

   private:
    std::vector<Stage> stages_;
  };

  ChannelArgs PreconditionChannelArgs(const grpc_channel_args* args) const;

 private:
  std::vector<Stage> stages_;
};

}

#endif
