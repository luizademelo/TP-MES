
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_STATEFUL_SESSION_STATEFUL_SESSION_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_STATEFUL_SESSION_STATEFUL_SESSION_FILTER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <utility>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/ext/filters/stateful_session/stateful_session_service_config_parser.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/service_config/service_config_call_data.h"
#include "src/core/util/ref_counted_string.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

class XdsOverrideHostAttribute
    : public ServiceConfigCallData::CallAttributeInterface {
 public:
  static UniqueTypeName TypeName();

  explicit XdsOverrideHostAttribute(absl::string_view cookie_address_list)
      : cookie_address_list_(cookie_address_list) {}

  absl::string_view cookie_address_list() const { return cookie_address_list_; }

  absl::string_view actual_address_list() const {
    return actual_address_list_.as_string_view();
  }
  void set_actual_address_list(RefCountedStringValue actual_address_list) {
    actual_address_list_ = std::move(actual_address_list);
  }

 private:
  UniqueTypeName type() const override { return TypeName(); }

  absl::string_view cookie_address_list_;
  RefCountedStringValue actual_address_list_;
};

class StatefulSessionFilter
    : public ImplementChannelFilter<StatefulSessionFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "stateful_session_filter"; }

  static absl::StatusOr<std::unique_ptr<StatefulSessionFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  explicit StatefulSessionFilter(ChannelFilter::Args filter_args);

  class Call {
   public:
    void OnClientInitialMetadata(ClientMetadata& md,
                                 StatefulSessionFilter* filter);
    void OnServerInitialMetadata(ServerMetadata& md);
    void OnServerTrailingMetadata(ServerMetadata& md);
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;

   private:
    const StatefulSessionMethodParsedConfig::CookieConfig* cookie_config_;
    XdsOverrideHostAttribute* override_host_attribute_;
    absl::string_view cluster_name_;
    absl::string_view cookie_address_list_;
    bool cluster_changed_;
    bool perform_filtering_ = false;
  };

 private:

  const size_t index_;

  const size_t service_config_parser_index_;
};

}

#endif
