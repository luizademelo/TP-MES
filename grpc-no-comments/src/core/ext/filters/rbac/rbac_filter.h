
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_RBAC_RBAC_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_RBAC_RBAC_FILTER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/security/authorization/evaluate_args.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class RbacFilter : public ImplementChannelFilter<RbacFilter> {
 public:

  static const grpc_channel_filter kFilterVtable;

  static absl::string_view TypeName() { return "rbac_filter"; }

  static absl::StatusOr<std::unique_ptr<RbacFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  RbacFilter(size_t index,
             EvaluateArgs::PerChannelArgs per_channel_evaluate_args);

  class Call {
   public:
    absl::Status OnClientInitialMetadata(ClientMetadata& md,
                                         RbacFilter* filter);
    static inline const NoInterceptor OnServerInitialMetadata;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:

  size_t index_;

  const size_t service_config_parser_index_;

  EvaluateArgs::PerChannelArgs per_channel_evaluate_args_;
};

}

#endif
