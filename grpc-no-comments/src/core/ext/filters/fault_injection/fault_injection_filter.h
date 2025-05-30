
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_FILTERS_FAULT_INJECTION_FAULT_INJECTION_FILTER_H
#define GRPC_SRC_CORE_EXT_FILTERS_FAULT_INJECTION_FAULT_INJECTION_FILTER_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/random/random.h"
#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class FaultInjectionFilter
    : public ImplementChannelFilter<FaultInjectionFilter> {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "fault_injection_filter"; }

  static absl::StatusOr<std::unique_ptr<FaultInjectionFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);

  explicit FaultInjectionFilter(ChannelFilter::Args filter_args);

  class Call {
   public:
    ArenaPromise<absl::Status> OnClientInitialMetadata(
        ClientMetadata& md, FaultInjectionFilter* filter);
    static inline const NoInterceptor OnServerInitialMetadata;
    static inline const NoInterceptor OnServerTrailingMetadata;
    static inline const NoInterceptor OnClientToServerMessage;
    static inline const NoInterceptor OnClientToServerHalfClose;
    static inline const NoInterceptor OnServerToClientMessage;
    static inline const NoInterceptor OnFinalize;
  };

 private:
  class InjectionDecision;
  InjectionDecision MakeInjectionDecision(
      const ClientMetadata& initial_metadata);

  size_t index_;
  const size_t service_config_parser_index_;
  Mutex mu_;
  absl::InsecureBitGen abort_rand_generator_ ABSL_GUARDED_BY(mu_);
  absl::InsecureBitGen delay_rand_generator_ ABSL_GUARDED_BY(mu_);
};

}

#endif
