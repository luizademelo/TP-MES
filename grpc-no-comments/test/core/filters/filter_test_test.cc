// Copyright 2023 gRPC authors.

#include "test/core/filters/filter_test.h"

#include <grpc/compression.h>

#include <functional>
#include <memory>
#include <type_traits>
#include <utility>

#include "absl/status/statusor.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/promise_based_filter.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/map.h"
#include "src/core/lib/promise/pipe.h"
#include "src/core/lib/promise/poll.h"
#include "src/core/lib/promise/seq.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"

using ::testing::_;

namespace grpc_core {
namespace {

class NoOpFilter final : public ChannelFilter {
 public:
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs args, NextPromiseFactory next) override {
    return next(std::move(args));
  }

  static absl::StatusOr<std::unique_ptr<NoOpFilter>> Create(
      const ChannelArgs&, ChannelFilter::Args) {
    return std::make_unique<NoOpFilter>();
  }
};
using NoOpFilterTest = FilterTest<NoOpFilter>;

class DelayStartFilter final : public ChannelFilter {
 public:
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs args, NextPromiseFactory next) override {
    return Seq(
        [args = std::move(args), i = 10]() mutable -> Poll<CallArgs> {
          --i;
          if (i == 0) return std::move(args);
          GetContext<Activity>()->ForceImmediateRepoll();
          return Pending{};
        },
        next);
  }

  static absl::StatusOr<std::unique_ptr<DelayStartFilter>> Create(
      const ChannelArgs&, ChannelFilter::Args) {
    return std::make_unique<DelayStartFilter>();
  }
};
using DelayStartFilterTest = FilterTest<DelayStartFilter>;

class AddClientInitialMetadataFilter final : public ChannelFilter {
 public:
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs args, NextPromiseFactory next) override {
    args.client_initial_metadata->Set(HttpPathMetadata(),
                                      Slice::FromCopiedString("foo.bar"));
    return next(std::move(args));
  }

  static absl::StatusOr<std::unique_ptr<AddClientInitialMetadataFilter>> Create(
      const ChannelArgs&, ChannelFilter::Args) {
    return absl::make_unique<AddClientInitialMetadataFilter>();
  }
};
using AddClientInitialMetadataFilterTest =
    FilterTest<AddClientInitialMetadataFilter>;

class AddServerTrailingMetadataFilter final : public ChannelFilter {
 public:
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs args, NextPromiseFactory next) override {
    return Map(next(std::move(args)), [](ServerMetadataHandle handle) {
      handle->Set(HttpStatusMetadata(), 420);
      return handle;
    });
  }

  static absl::StatusOr<std::unique_ptr<AddServerTrailingMetadataFilter>>
  Create(const ChannelArgs&, ChannelFilter::Args) {
    return absl::make_unique<AddServerTrailingMetadataFilter>();
  }
};
using AddServerTrailingMetadataFilterTest =
    FilterTest<AddServerTrailingMetadataFilter>;

class AddServerInitialMetadataFilter final : public ChannelFilter {
 public:
  ArenaPromise<ServerMetadataHandle> MakeCallPromise(
      CallArgs args, NextPromiseFactory next) override {
    args.server_initial_metadata->InterceptAndMap([](ServerMetadataHandle md) {
      md->Set(GrpcEncodingMetadata(), GRPC_COMPRESS_GZIP);
      return md;
    });
    return next(std::move(args));
  }
  static absl::StatusOr<std::unique_ptr<AddServerInitialMetadataFilter>> Create(
      const ChannelArgs&, ChannelFilter::Args) {
    return absl::make_unique<AddServerInitialMetadataFilter>();
  }
};
using AddServerInitialMetadataFilterTest =
    FilterTest<AddServerInitialMetadataFilter>;

TEST_F(NoOpFilterTest, NoOp) {}

TEST_F(NoOpFilterTest, MakeCall) {
  Call call(MakeChannel(ChannelArgs()).value());
}

TEST_F(NoOpFilterTest, MakeClientMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  auto md = call.NewClientMetadata({{":path", "foo.bar"}});
  EXPECT_EQ(md->get_pointer(HttpPathMetadata())->as_string_view(), "foo.bar");
}

TEST_F(NoOpFilterTest, MakeServerMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  auto md = call.NewServerMetadata({{":status", "200"}});
  EXPECT_EQ(md->get(HttpStatusMetadata()), HttpStatusMetadata::ValueType(200));
}

TEST_F(NoOpFilterTest, CanStart) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  Step();
}

TEST_F(DelayStartFilterTest, CanStartWithDelay) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  Step();
}

TEST_F(NoOpFilterTest, CanCancel) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.Cancel();
}

TEST_F(DelayStartFilterTest, CanCancelWithDelay) {
  Call call(MakeChannel(ChannelArgs()).value());
  call.Start(call.NewClientMetadata());
  call.Cancel();
}

TEST_F(AddClientInitialMetadataFilterTest, CanSetClientInitialMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, HasMetadataKeyValue(":path", "foo.bar")));
  call.Start(call.NewClientMetadata());
  Step();
}

TEST_F(NoOpFilterTest, CanFinish) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.FinishNextFilter(call.NewServerMetadata());
  EXPECT_EVENT(Finished(&call, _));
  Step();
}

TEST_F(AddServerTrailingMetadataFilterTest, CanSetServerTrailingMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.FinishNextFilter(call.NewServerMetadata());
  EXPECT_EVENT(Finished(&call, HasMetadataKeyValue(":status", "420")));
  Step();
}

TEST_F(NoOpFilterTest, CanProcessServerInitialMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.ForwardServerInitialMetadata(call.NewServerMetadata());
  EXPECT_EVENT(ForwardedServerInitialMetadata(&call, _));
  Step();
}

TEST_F(AddServerInitialMetadataFilterTest, CanSetServerInitialMetadata) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.ForwardServerInitialMetadata(call.NewServerMetadata());
  EXPECT_EVENT(ForwardedServerInitialMetadata(
      &call, HasMetadataKeyValue("grpc-encoding", "gzip")));
  Step();
}

TEST_F(NoOpFilterTest, CanProcessClientToServerMessage) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.ForwardMessageClientToServer(call.NewMessage("abc"));
  EXPECT_CALL(events,
              ForwardedMessageClientToServer(&call, HasMessagePayload("abc")));
  Step();
}

TEST_F(NoOpFilterTest, CanProcessServerToClientMessage) {
  Call call(MakeChannel(ChannelArgs()).value());
  EXPECT_EVENT(Started(&call, _));
  call.Start(call.NewClientMetadata());
  call.ForwardServerInitialMetadata(call.NewServerMetadata());
  call.ForwardMessageServerToClient(call.NewMessage("abc"));
  EXPECT_EVENT(ForwardedServerInitialMetadata(&call, _));
  EXPECT_CALL(events,
              ForwardedMessageServerToClient(&call, HasMessagePayload("abc")));
  Step();
}

}
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
