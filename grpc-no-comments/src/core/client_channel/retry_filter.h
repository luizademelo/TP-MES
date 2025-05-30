
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_FILTER_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_RETRY_FILTER_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/port_platform.h>
#include <limits.h>
#include <stddef.h>

#include <new>
#include <optional>

#include "absl/log/check.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/client_channel/retry_service_config.h"
#include "src/core/client_channel/retry_throttle.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class RetryFilter final {
 public:
  static const grpc_channel_filter kVtable;

 private:

  class LegacyCallData;

  grpc_event_engine::experimental::EventEngine* event_engine() const {
    return event_engine_;
  }

  static double BackoffJitter() { return 0.2; }

  const internal::RetryMethodConfig* GetRetryPolicy(Arena* arena);

  RefCountedPtr<internal::ServerRetryThrottleData> retry_throttle_data() const {
    return retry_throttle_data_;
  }

  ClientChannelFilter* client_channel() const { return client_channel_; }

  size_t per_rpc_retry_buffer_size() const {
    return per_rpc_retry_buffer_size_;
  }

  static size_t GetMaxPerRpcRetryBufferSize(const ChannelArgs& args) {

    static constexpr int kDefaultPerRpcRetryBufferSize = (256 << 10);

    return Clamp(args.GetInt(GRPC_ARG_PER_RPC_RETRY_BUFFER_SIZE)
                     .value_or(kDefaultPerRpcRetryBufferSize),
                 0, INT_MAX);
  }

  RetryFilter(const ChannelArgs& args, grpc_error_handle* error);

  static grpc_error_handle Init(grpc_channel_element* elem,
                                grpc_channel_element_args* args) {
    CHECK(args->is_last);
    CHECK(elem->filter == &kVtable);
    grpc_error_handle error;
    new (elem->channel_data) RetryFilter(args->channel_args, &error);
    return error;
  }

  static void Destroy(grpc_channel_element* elem) {
    auto* chand = static_cast<RetryFilter*>(elem->channel_data);
    chand->~RetryFilter();
  }

  static void StartTransportOp(grpc_channel_element* ,
                               grpc_transport_op* ) {}
  static void GetChannelInfo(grpc_channel_element* ,
                             const grpc_channel_info* ) {}

  ClientChannelFilter* client_channel_;
  grpc_event_engine::experimental::EventEngine* const event_engine_;
  size_t per_rpc_retry_buffer_size_;
  RefCountedPtr<internal::ServerRetryThrottleData> retry_throttle_data_;
  const size_t service_config_parser_index_;
};

}

#endif
