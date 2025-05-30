
// Copyright 2017 gRPC authors.

#include <grpc/impl/channel_arg_names.h>
#include <grpc/status.h>
#include <string.h>

#include <memory>
#include <new>
#include <optional>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
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

class FailFirstTenCallsFilter {
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
        grpc_call_element* elem, grpc_transport_stream_op_batch* batch) {
      auto* chand = static_cast<FailFirstTenCallsFilter*>(elem->channel_data);
      auto* calld = static_cast<CallData*>(elem->call_data);
      if (chand->num_calls_ < 10) calld->fail_ = true;
      if (batch->send_initial_metadata) ++chand->num_calls_;
      if (calld->fail_) {
        if (batch->recv_trailing_metadata) {
          batch->payload->recv_trailing_metadata.recv_trailing_metadata->Set(
              GrpcStreamNetworkState(), GrpcStreamNetworkState::kNotSentOnWire);
        }
        if (!batch->cancel_stream) {
          grpc_transport_stream_op_batch_finish_with_failure(
              batch,
              grpc_error_set_int(
                  GRPC_ERROR_CREATE("FailFirstTenCallsFilter failing batch"),
                  StatusIntProperty::kRpcStatus, GRPC_STATUS_UNAVAILABLE),
              calld->call_combiner_);
          return;
        }
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
    new (elem->channel_data) FailFirstTenCallsFilter();
    return absl::OkStatus();
  }

  static void Destroy(grpc_channel_element* elem) {
    auto* chand = static_cast<FailFirstTenCallsFilter*>(elem->channel_data);
    chand->~FailFirstTenCallsFilter();
  }

  size_t num_calls_ = 0;
};

grpc_channel_filter FailFirstTenCallsFilter::kFilterVtable = {
    CallData::StartTransportStreamOpBatch,
    grpc_channel_next_op,
    sizeof(CallData),
    CallData::Init,
    grpc_call_stack_ignore_set_pollset_or_pollset_set,
    CallData::Destroy,
    sizeof(FailFirstTenCallsFilter),
    Init,
    grpc_channel_stack_no_post_init,
    Destroy,
    grpc_channel_next_get_info,
    GRPC_UNIQUE_TYPE_NAME_HERE("FailFirstTenCallsFilter"),
};

CORE_END2END_TEST(RetryTests, RetryTransparentNotSentOnWire) {
  SKIP_IF_V3();
  CoreConfiguration::RegisterEphemeralBuilder(
      [](CoreConfiguration::Builder* builder) {
        builder->channel_init()
            ->RegisterFilter(GRPC_CLIENT_SUBCHANNEL,
                             &FailFirstTenCallsFilter::kFilterVtable)

            .IfChannelArg(GRPC_ARG_ENABLE_RETRIES, true);
      });
  auto c =
      NewClientCall("/service/method").Timeout(Duration::Minutes(1)).Create();
  EXPECT_NE(c.GetPeer(), std::nullopt);

  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient();

  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  IncomingMessage server_message;
  c.NewBatch(2)
      .RecvInitialMetadata(server_initial_metadata)
      .RecvMessage(server_message)
      .RecvStatusOnClient(server_status);

  Expect(1, true);
  Step();

  auto s = RequestCall(101);
  Expect(101, true);
  Step();

  IncomingMessage client_message;
  s.NewBatch(102).RecvMessage(client_message);
  Expect(102, true);
  Step();

  IncomingCloseOnServer client_close;
  s.NewBatch(103)
      .RecvCloseOnServer(client_close)
      .SendInitialMetadata({})
      .SendMessage("bar")
      .SendStatusFromServer(GRPC_STATUS_OK, "xyz", {});

  Expect(103, true);
  Expect(2, true);
  Step();
  EXPECT_EQ(server_status.status(), GRPC_STATUS_OK);
  EXPECT_EQ(server_status.message(), IsErrorFlattenEnabled() ? "" : "xyz");
  EXPECT_EQ(s.method(), "/service/method");
  EXPECT_FALSE(client_close.was_cancelled());
  EXPECT_EQ(client_message.payload(), "foo");
  EXPECT_EQ(server_message.payload(), "bar");

  EXPECT_EQ(s.GetInitialMetadata("grpc-previous-rpc-attempts"), std::nullopt);
}

}
}
