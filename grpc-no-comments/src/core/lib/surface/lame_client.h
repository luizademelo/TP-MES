
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_LAME_CLIENT_H
#define GRPC_SRC_CORE_LIB_SURFACE_LAME_CLIENT_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/base/thread_annotations.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/transport/connectivity_state.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/sync.h"

#define GRPC_ARG_LAME_FILTER_ERROR "grpc.lame_filter_error"

namespace grpc_core {

class LameClientFilter : public ChannelFilter {
 public:
  static const grpc_channel_filter kFilter;

  static absl::string_view TypeName() { return "lame-client"; }

  explicit LameClientFilter(absl::Status error);

  static absl::StatusOr<std::unique_ptr<LameClientFilter>> Create(
      const ChannelArgs& args, ChannelFilter::Args filter_args);
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs call_args, NextPromiseFactory next_promise_factory) override;
  bool StartTransportOp(grpc_transport_op*) override;
  bool GetChannelInfo(const grpc_channel_info*) override;

 private:
  absl::Status error_;
  Mutex mu_;
  ConnectivityStateTracker state_tracker_ ABSL_GUARDED_BY(mu_);
};

extern const grpc_arg_pointer_vtable kLameFilterErrorArgVtable;

grpc_arg MakeLameClientErrorArg(grpc_error_handle* error);

}

#endif
