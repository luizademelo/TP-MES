
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_LOAD_REPORTING_SERVER_LOAD_REPORTING_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_LOAD_REPORTING_SERVER_LOAD_REPORTING_FILTER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <string>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class ServerLoadReportingFilter
    : public ImplementChannelFilter<ServerLoadReportingFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "server_load_reporting"; }

  static absl::StatusOr<std::unique_ptr<ServerLoadReportingFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args);

  const char* peer_identity() { return peer_identity_.c_str(); }
  size_t peer_identity_len() { return peer_identity_.length(); }

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ServerLoadReportingFilter* filter);
    static inline const NoInterceptor OnServerInitialMetadata;
    void OnServerTrailingMetadata(ServerMetadata& md,
                                  ServerLoadReportingFilter* filter);
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    void OnFinalize(const grpc_call_final_info* final_info,
                    ServerLoadReportingFilter* filter);

   private:
    std::string client_ip_and_lr_token_;
    std::string target_host_;
  };

 private:

  std::string peer_identity_;
};

}

#endif
