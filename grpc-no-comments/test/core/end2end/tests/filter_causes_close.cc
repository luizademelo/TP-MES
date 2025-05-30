
// Copyright 2015 gRPC authors.

#include <grpc/status.h>
#include <stdint.h>

#include <memory>
#include <utility>

#include "absl/status/status.h"
#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/time.h"
#include "test/core/end2end/end2end_tests.h"

namespace grpc_core {
namespace {

class TestFilter : public ImplementChannelFilter<TestFilter> {
 public:
  static const grpc_channel_filter kFilter;
  static absl::string_view TypeName() { return "filter_causes_close"; }
  static absl::StatusOr<std::unique_ptr<TestFilter>> Create(
      const ChannelArgs&, ChannelFilter::Args) {
    return std::make_unique<TestFilter>();
  }

  class Call {
   public:
    absl::Status OnClientInitialMetadata(ClientMetadata&) {
      return grpc_error_set_int(
          absl::PermissionDeniedError("Failure that's not preventable."),
          StatusIntProperty::kRpcStatus, GRPC_STATUS_PERMISSION_DENIED);
    }
    static const NoInterceptor OnServerInitialMetadata;
    static const NoInterceptor OnServerTrailingMetadata;
    static const NoInterceptor OnClientToServerMessage;
    static const NoInterceptor OnClientToServerHalfClose;
    static const NoInterceptor OnServerToClientMessage;
    static const NoInterceptor OnFinalize;
  };
};

const NoInterceptor TestFilter::Call::OnServerInitialMetadata;
const NoInterceptor TestFilter::Call::OnServerTrailingMetadata;
const NoInterceptor TestFilter::Call::OnClientToServerMessage;
const NoInterceptor TestFilter::Call::OnClientToServerHalfClose;
const NoInterceptor TestFilter::Call::OnServerToClientMessage;
const NoInterceptor TestFilter::Call::OnFinalize;

const grpc_channel_filter TestFilter::kFilter =
    MakePromiseBasedFilter<TestFilter, FilterEndpoint::kServer>();

CORE_END2END_TEST(CoreEnd2endTests, FilterCausesClose) {
  CoreConfiguration::RegisterEphemeralBuilder(
      [](CoreConfiguration::Builder* builder) {
        builder->channel_init()->RegisterFilter<TestFilter>(
            GRPC_SERVER_CHANNEL);
      });
  auto c = NewClientCall("/foo").Timeout(Duration::Seconds(5)).Create();
  IncomingStatusOnClient server_status;
  IncomingMetadata server_initial_metadata;
  c.NewBatch(1)
      .SendInitialMetadata({})
      .SendMessage("foo")
      .SendCloseFromClient()
      .RecvInitialMetadata(server_initial_metadata)
      .RecvStatusOnClient(server_status);
  Expect(1, true);
  Step();

  EXPECT_EQ(server_status.status(), GRPC_STATUS_PERMISSION_DENIED);
  EXPECT_EQ(server_status.message(), "Failure that's not preventable.");
}

}
}
