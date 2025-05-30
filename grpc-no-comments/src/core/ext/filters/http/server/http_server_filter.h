
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_HTTP_SERVER_HTTP_SERVER_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_HTTP_SERVER_HTTP_SERVER_FILTER_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class HttpServerFilter : public ImplementChannelFilter<HttpServerFilter>,
                         public channelz::DataSource {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "http-server"; }

  static absl::StatusOr<std::unique_ptr<HttpServerFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  HttpServerFilter(const ChannelArgs& args, bool surface_user_agent,
                   bool allow_put_requests)
      : channelz::DataSource(args.GetObjectRef<channelz::BaseNode>()),
        surface_user_agent_(surface_user_agent),
        allow_put_requests_(allow_put_requests) {}
  ~HttpServerFilter() override { ResetDataSource(); }

  void AddData(channelz::DataSink sink) override {
    Json::Object object;
    object["surfaceUserAgent"] = Json::FromBool(surface_user_agent_);
    object["allowPutRequests"] = Json::FromBool(allow_put_requests_);
    sink.AddAdditionalInfo("httpServerFilter", object);
  }

  class Call {
   public:
    ServerMetadataHandle OnClientInitialMetadata(ClientMetadata& md,
                                                 HttpServerFilter* filter);
    void OnServerInitialMetadata(ServerMetadata& md);
    void OnServerTrailingMetadata(ServerMetadata& md);
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:
  bool surface_user_agent_;
  bool allow_put_requests_;
};

}

#define GRPC_ARG_DO_NOT_USE_UNLESS_YOU_HAVE_PERMISSION_FROM_GRPC_TEAM_ALLOW_BROKEN_PUT_REQUESTS \
  "grpc.http.do_not_use_unless_you_have_permission_from_grpc_team_allow_"                       \
  "broken_put_requests"

#endif
