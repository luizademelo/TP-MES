
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>

#include <memory>
#include <new>
#include <optional>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/iomgr/call_combiner.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

class FailFirstSendOpFilter {
 public:
  static grpc_channel_filter kFilterVtable;

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
        grpc_call_element* elem, grpc_transport_stream_op_batch* batch) {
      auto* chand = static_cast<FailFirstSendOpFilter*>(elem->channel_data);
      auto* calld = static_cast<CallData*>(elem->call_data);
      if (!chand->seen_first_) {
        chand->seen_first_ = true;
        calld->fail_ = true;
      }
      if (calld->fail_ && !batch->cancel_stream) {
        grpc_transport_stream_op_batch_finish_with_failure(
            batch,
            grpc_error_set_int(
                GRPC_ERROR_CREATE("FailFirstSendOpFilter failing batch"),
                StatusIntProperty::kRpcStatus, GRPC_STATUS_ABORTED),
            calld->call_combiner_);
        return;
      }
      grpc_call_next_op(elem, batch);
    }

   private:
    explicit CallData(const grpc_call_element_args* args)
        : call_combiner_(args->call_combiner) {}

    CallCombiner* call_combiner_;
    bool fail_ = false;
  };

  static grpc_error_handle Init(grpc_channel_element* elem,
                                grpc_channel_element_args* ) {
    new (elem->channel_data) FailFirstSendOpFilter();
    return absl::OkStatus();
  }

  static void Destroy(grpc_channel_element* elem) {
    auto* chand = static_cast<FailFirstSendOpFilter*>(elem->channel_data);
    chand->~FailFirstSendOpFilter();
  }

  bool seen_first_ = false;
};

grpc_channel_filter FailFirstSendOpFilter::kFilterVtable = {
    CallData::StartTransportStreamOpBatch,
    grpc_channel_next_op,
    sizeof(CallData),
    CallData::Init,
    grpc_call_stack_ignore_set_pollset_or_pollset_set,
    CallData::Destroy,
    sizeof(FailFirstSendOpFilter),
    Init,
    grpc_channel_stack_no_post_init,
    Destroy,
    grpc_channel_next_get_info,
    GRPC_UNIQUE_TYPE_NAME_HERE("FailFirstSendOpFilter"),
};

CORE_END2END_TEST(RetryTests, RetryRecvMessageReplay) {
  SKIP_IF_V3();
  CoreConfiguration::RegisterEphemeralBuilder(
      [](CoreConfiguration::Builder* builder) {
        builder->channel_init()
            ->RegisterFilter(GRPC_CLIENT_SUBCHANNEL,
                             &FailFirstSendOpFilter::kFilterVtable)

            .IfChannelArg(GRPC_ARG_ENABLE_RETRIES, true);
      });
  InitServer(ChannelArgs());
  InitClient(ChannelArgs().Set(
      GRPC_ARG_SERVICE_CONFIG,
      "{\n"
      "  \"methodConfig\": [ {\n"
      "    \"name\": [\n"
      "      { \"service\": \"service\", \"method\": \"method\" }\n"
      "    ],\n"
      "    \"retryPolicy\": {\n"
      "      \"maxAttempts\": 2,\n"
      "      \"initialBackoff\": \"1s\",\n"
      "      \"maxBackoff\": \"120s\",\n"
      "      \"backoffMultiplier\": 1.6,\n"
      "      \"retryableStatusCodes\": [ \"ABORTED\" ]\n"
      "    }\n"
      "  } ]\n"
      "}"));
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Seconds(5)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  IncomingMetadata server_initial_metadata;
  c.NewBatch(1).SendInitialMetadata({}).RecvInitialMetadata(
      server_initial_metadata);

  IncomingMessage server_message;
  c.NewBatch(2).RecvMessage(server_message);

  IncomingStatusOnClient server_status;
  c.NewBatch(3).RecvStatusOnClient(server_status);

  auto s = RequestCall(101);
  Expect(101, true);
  Step();

  IncomingCloseOnServer client_close;
  s.NewBatch(102)
      .SendInitialMetadata({})
      .SendStatusFromServer(GRPC_STATUS_ABORTED, "xyz", {})
      .RecvCloseOnServer(client_close);

  Expect(102, true);
  Expect(1, true);
  Expect(2, true);
  Expect(3, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_ABORTED);
  EXPECT_EQ(server_status.message(), "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
}

}
}
