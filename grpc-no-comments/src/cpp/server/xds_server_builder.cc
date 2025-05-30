
// Copyright 2023 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/support/channel_arguments.h>
#include <grpcpp/xds_server_builder.h>

#include "src/core/xds/grpc/xds_enabled_server.h"

namespace grpc {

ChannelArguments XdsServerBuilder::BuildChannelArgs() {
  ChannelArguments args = ServerBuilder::BuildChannelArgs();
  if (drain_grace_time_ms_ >= 0) {
    args.SetInt(GRPC_ARG_SERVER_CONFIG_CHANGE_DRAIN_GRACE_TIME_MS,
                drain_grace_time_ms_);
  }
  args.SetInt(GRPC_ARG_XDS_ENABLED_SERVER, 1);
  grpc_channel_args c_channel_args = args.c_channel_args();
  grpc_server_config_fetcher* fetcher = grpc_server_config_fetcher_xds_create(
      {OnServingStatusUpdate, notifier_}, &c_channel_args);
  if (fetcher != nullptr) set_fetcher(fetcher);
  return args;
}

}
