
// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_CLIENT_LOAD_REPORTING_FILTER_H
#define GRPC_SRC_CORE_LOAD_BALANCING_GRPCLB_CLIENT_LOAD_REPORTING_FILTER_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/load_balancing/grpclb/grpclb_client_stats.h"

namespace grpc_core {

class ClientLoadReportingFilter final
    : public ImplementChannelFilter<ClientLoadReportingFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "client_load_reporting"; }

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& client_initial_metadata);
    void OnServerInitialMetadata(ServerMetadata& server_initial_metadata);
    void OnServerTrailingMetadata(ServerMetadata& server_trailing_metadata);
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnFinalize;

   private:
    RefCountedPtr<GrpcLbClientStats> client_stats_;
    bool saw_initial_metadata_ = false;
  };

  static absl::StatusOr<std::unique_ptr<ClientLoadReportingFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);
};

}

#endif
