// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_BACKEND_METRICS_BACKEND_METRIC_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_BACKEND_METRICS_BACKEND_METRIC_FILTER_H

#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "src/core/ext/filters/backend_metrics/backend_metric_provider.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class BackendMetricFilter : public ImplementChannelFilter<BackendMetricFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "backend_metric"; }

  static absl::StatusOr<std::unique_ptr<BackendMetricFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args);

  class Call {
   public:
    static inline const NoInterceptor OnClientInitialMetadata;
    static inline const NoInterceptor OnServerInitialMetadata;
    void OnServerTrailingMetadata(ServerMetadata& md);
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };
};

}

#endif
