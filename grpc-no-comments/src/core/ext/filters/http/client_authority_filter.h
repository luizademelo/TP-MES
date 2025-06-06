
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_HTTP_CLIENT_AUTHORITY_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_HTTP_CLIENT_AUTHORITY_FILTER_H

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class ClientAuthorityFilter final
    : public ImplementChannelFilter<ClientAuthorityFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "authority"; }

  static absl::StatusOr<std::unique_ptr<ClientAuthorityFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args);

  explicit ClientAuthorityFilter(Slice default_authority)
      : default_authority_(std::move(default_authority)) {}

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 ClientAuthorityFilter* filter);
    static inline const NoInterceptor OnServerInitialMetadata;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:
  Slice default_authority_;
};

}

#endif
