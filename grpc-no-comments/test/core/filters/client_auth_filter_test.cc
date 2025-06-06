// Copyright 2022 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>

#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/transport/fake/fake_credentials.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/filter/auth/auth_filters.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"
#include "test/core/filters/filter_test.h"

namespace grpc_core {
namespace {

class ClientAuthFilterTest : public FilterTest<ClientAuthFilter> {
 protected:
  class FailCallCreds : public grpc_call_credentials {
   public:
    explicit FailCallCreds(absl::Status status)
        : grpc_call_credentials(GRPC_SECURITY_NONE),
          status_(std::move(status)) {}

    void Orphaned() override {}

    UniqueTypeName type() const override {
      static UniqueTypeName::Factory kFactory("FailCallCreds");
      return kFactory.Create();
    }

    ArenaPromise<absl::StatusOr<ClientMetadataHandle>> GetRequestMetadata(
        ClientMetadataHandle ,
        const GetRequestMetadataArgs* ) override {
      return Immediate<absl::StatusOr<ClientMetadataHandle>>(status_);
    }

    int cmp_impl(const grpc_call_credentials* other) const override {
      return QsortCompare(
          status_.ToString(),
          static_cast<const FailCallCreds*>(other)->status_.ToString());
    }

   private:
    absl::Status status_;
  };

  ClientAuthFilterTest()
      : channel_creds_(grpc_fake_transport_security_credentials_create()) {}

  Channel MakeChannelWithCallCredsResult(absl::Status status) {
    return MakeChannel(MakeChannelArgs(std::move(status))).value();
  }

  ChannelArgs MakeChannelArgs(absl::Status status_for_call_creds) {
    ChannelArgs args;
    auto security_connector = channel_creds_->create_security_connector(
        status_for_call_creds.ok()
            ? nullptr
            : MakeRefCounted<FailCallCreds>(std::move(status_for_call_creds)),
        std::string(target()).c_str(), &args);
    auto auth_context = MakeRefCounted<grpc_auth_context>(nullptr);
    absl::string_view security_level = "TSI_SECURITY_NONE";
    auth_context->add_property(GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME,
                               security_level.data(), security_level.size());
    return args.SetObject(std::move(security_connector))
        .SetObject(std::move(auth_context));
  }

  absl::string_view target() { return "localhost:1234"; }

  RefCountedPtr<grpc_channel_credentials> channel_creds_;
};

TEST_F(ClientAuthFilterTest, CreateFailsWithoutRequiredChannelArgs) {
  EXPECT_FALSE(
      ClientAuthFilter::Create(ChannelArgs(), ChannelFilter::Args()).ok());
}

TEST_F(ClientAuthFilterTest, CreateSucceeds) {
  auto filter = MakeChannel(MakeChannelArgs(absl::OkStatus()));
  EXPECT_TRUE(filter.ok()) << filter.status();
}

TEST_F(ClientAuthFilterTest, CallCredsFails) {
  Call call(MakeChannelWithCallCredsResult(
      absl::UnauthenticatedError("access denied")));
  call.Start(call.NewClientMetadata({{":authority", target()}}));
  EXPECT_EVENT(Finished(
      &call, HasMetadataResult(absl::UnauthenticatedError("access denied"))));
  Step();
}

TEST_F(ClientAuthFilterTest, RewritesInvalidStatusFromCallCreds) {
  Call call(MakeChannelWithCallCredsResult(absl::AbortedError("nope")));
  call.Start(call.NewClientMetadata({{":authority", target()}}));
  EXPECT_EVENT(Finished(&call, HasMetadataResult(absl::InternalError(
                                   "Illegal status code from call credentials; "
                                   "original status: ABORTED: nope"))));
  Step();
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
