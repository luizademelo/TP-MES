// Copyright 2025 The gRPC Authors.

#ifndef GRPC_TEST_CORE_TEST_UTIL_FAIL_FIRST_CALL_FILTER_H
#define GRPC_TEST_CORE_TEST_UTIL_FAIL_FIRST_CALL_FILTER_H

#include "src/core/lib/channel/channel_stack.h"

namespace grpc_core {
namespace testing {

class FailFirstCallFilter {
 public:
  static grpc_channel_filter kFilterVtable;

 private:
  class CallData {
   public:
    static grpc_error_handle Init(grpc_call_element* elem,
                                  const grpc_call_element_args* args) {
      new (elem->call_data) CallData(args);
      return absl::OkStatus();
    }

    static void Destroy(grpc_call_element* elem,
                        const grpc_call_final_info* ,
                        grpc_closure* ) {
      auto* calld = static_cast<CallData*>(elem->call_data);
      calld->~CallData();
    }

    static void StartTransportStreamOpBatch(
        grpc_call_element* elem, grpc_transport_stream_op_batch* batch);

   private:
    explicit CallData(const grpc_call_element_args* args)
        : call_combiner_(args->call_combiner) {}

    CallCombiner* call_combiner_;
    bool fail_ = false;
  };

  static grpc_error_handle Init(grpc_channel_element* elem,
                                grpc_channel_element_args* ) {
    new (elem->channel_data) FailFirstCallFilter();
    return absl::OkStatus();
  }

  static void Destroy(grpc_channel_element* elem) {
    auto* chand = static_cast<FailFirstCallFilter*>(elem->channel_data);
    chand->~FailFirstCallFilter();
  }

  bool seen_call_ = false;
};

}
}

#endif