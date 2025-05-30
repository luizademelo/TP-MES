
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_HTTP_CLIENT_HTTP_CLIENT_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_HTTP_CLIENT_HTTP_CLIENT_FILTER_H

#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

class HttpClientFilter : public ImplementChannelFilter<HttpClientFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "http-client"; }

  static absl::StatusOr<std::unique_ptr<HttpClientFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  HttpClientFilter(HttpSchemeMetadata::ValueType scheme, Slice user_agent,
                   bool test_only_use_put_requests);

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md, HttpClientFilter* filter);
    absl::Status OnServerInitialMetadata(ServerMetadata& md);
    absl::Status OnServerTrailingMetadata(ServerMetadata& md);
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:
  HttpSchemeMetadata::ValueType scheme_;
  bool test_only_use_put_requests_;
  Slice user_agent_;
};

#define GRPC_ARG_TEST_ONLY_USE_PUT_REQUESTS "grpc.testing.use_put_requests"

}

#endif
