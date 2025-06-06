// Copyright 2025 The gRPC Authors.

#include "test/core/test_util/fail_first_call_filter.h"

namespace grpc_core {
namespace testing {

grpc_channel_filter FailFirstCallFilter::kFilterVtable = {
    CallData::StartTransportStreamOpBatch,
    grpc_channel_next_op,
    sizeof(CallData),
    CallData::Init,
    grpc_call_stack_ignore_set_pollset_or_pollset_set,
    CallData::Destroy,
    sizeof(FailFirstCallFilter),
    Init,
    grpc_channel_stack_no_post_init,
    Destroy,
    grpc_channel_next_get_info,
    GRPC_UNIQUE_TYPE_NAME_HERE("FailFirstCallFilter"),
};

void FailFirstCallFilter::CallData::StartTransportStreamOpBatch(
    grpc_call_element* elem, grpc_transport_stream_op_batch* batch) {
  auto* chand = static_cast<FailFirstCallFilter*>(elem->channel_data);
  auto* calld = static_cast<CallData*>(elem->call_data);
  if (!chand->seen_call_) {
    calld->fail_ = true;
    chand->seen_call_ = true;
  }
  if (calld->fail_) {
    if (batch->recv_trailing_metadata) {
      batch->payload->recv_trailing_metadata.recv_trailing_metadata->Set(
          GrpcStreamNetworkState(), GrpcStreamNetworkState::kNotSeenByServer);
    }
    if (!batch->cancel_stream) {
      grpc_transport_stream_op_batch_finish_with_failure(
          batch,
          grpc_error_set_int(
              GRPC_ERROR_CREATE("FailFirstCallFilter failing batch"),
              StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE),
          calld->call_combiner_);
      return;
    }
  }
  grpc_call_next_op(elem, batch);
}

}
}