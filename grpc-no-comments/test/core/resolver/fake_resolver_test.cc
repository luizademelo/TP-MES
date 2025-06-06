
// Copyright 2017 gRPC authors.

#include "src/core/resolver/fake/fake_resolver.h"

#include <grpc/grpc.h>
#include <inttypes.h>
#include <string.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/container/inlined_vector.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/synchronization/notification.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"
#include "test/core/test_util/test_config.h"

namespace grpc_core {
namespace testing {

class FakeResolverTest : public ::testing::Test {
 protected:
  class ResultHandler : public Resolver::ResultHandler {
   public:
    void SetExpectedAndNotification(Resolver::Result expected,
                                    absl::Notification* notification) {
      MutexLock lock(&mu_);
      ASSERT_EQ(notification_, nullptr);
      expected_ = std::move(expected);
      notification_ = notification;
    }

    void ReportResult(Resolver::Result actual) override {
      MutexLock lock(&mu_);
      ASSERT_NE(notification_, nullptr);

      // Note: No good way to compare result_health_callback.
      ASSERT_TRUE(actual.addresses.ok());
      ASSERT_EQ(actual.addresses->size(), expected_.addresses->size());
      for (size_t i = 0; i < expected_.addresses->size(); ++i) {
        ASSERT_EQ((*actual.addresses)[i], (*expected_.addresses)[i]);
      }
      notification_->Notify();
      notification_ = nullptr;
    }

   private:
    Mutex mu_;
    Resolver::Result expected_ ABSL_GUARDED_BY(mu_);
    absl::Notification* notification_ ABSL_GUARDED_BY(mu_) = nullptr;
  };

  static OrphanablePtr<Resolver> BuildFakeResolver(
      std::shared_ptr<WorkSerializer> work_serializer,
      RefCountedPtr<FakeResolverResponseGenerator> response_generator,
      std::unique_ptr<Resolver::ResultHandler> result_handler) {
    ResolverFactory* factory =
        CoreConfiguration::Get().resolver_registry().LookupResolverFactory(
            "fake");
    ResolverArgs args;
    args.args = ChannelArgs().SetObject(std::move(response_generator));
    args.work_serializer = std::move(work_serializer);
    args.result_handler = std::move(result_handler);
    return factory->CreateResolver(std::move(args));
  }

  static Resolver::Result CreateResolverResult() {
    static size_t test_counter = 0;
    const size_t num_addresses = 2;

    EndpointAddressesList addresses;
    for (size_t i = 0; i < num_addresses; ++i) {
      std::string uri_string = absl::StrFormat(
          "ipv4:127.0.0.1:100%" PRIuPTR, (test_counter * num_addresses) + i);
      absl::StatusOr<URI> uri = URI::Parse(uri_string);
      EXPECT_TRUE(uri.ok());
      grpc_resolved_address address;
      EXPECT_TRUE(grpc_parse_uri(*uri, &address));
      addresses.emplace_back(address, ChannelArgs());
    }
    ++test_counter;
    Resolver::Result result;
    result.addresses = std::move(addresses);
    return result;
  }

  OrphanablePtr<Resolver> CreateResolver() {
    result_handler_ = new ResultHandler();
    return BuildFakeResolver(
        work_serializer_, response_generator_,
        std::unique_ptr<Resolver::ResultHandler>(result_handler_));
  }

  void RunSynchronously(std::function<void()> callback) {
    Notification notification;
    work_serializer_->Run([callback = std::move(callback), &notification]() {
      callback();
      notification.Notify();
    });
    notification.WaitForNotification();
  }

  ExecCtx exec_ctx_;
  std::shared_ptr<WorkSerializer> work_serializer_ =
      std::make_shared<WorkSerializer>(
          grpc_event_engine::experimental::GetDefaultEventEngine());
  RefCountedPtr<FakeResolverResponseGenerator> response_generator_ =
      MakeRefCounted<FakeResolverResponseGenerator>();
  ResultHandler* result_handler_ = nullptr;
};

TEST_F(FakeResolverTest, WaitForResolverSet) {
  EXPECT_FALSE(response_generator_->WaitForResolverSet(absl::Milliseconds(1)));
  auto resolver = CreateResolver();
  ASSERT_NE(resolver, nullptr);
  EXPECT_TRUE(response_generator_->WaitForResolverSet(absl::Milliseconds(1)));
}

TEST_F(FakeResolverTest, ReturnResultBeforeResolverCreated) {

  Resolver::Result result = CreateResolverResult();
  response_generator_->SetResponseAsync(result);

  auto resolver = CreateResolver();
  ASSERT_NE(resolver, nullptr);
  absl::Notification notification;
  result_handler_->SetExpectedAndNotification(std::move(result), &notification);
  RunSynchronously([resolver = resolver.get()] { resolver->StartLocked(); });

  ASSERT_TRUE(notification.WaitForNotificationWithTimeout(
      absl::Seconds(5 * grpc_test_slowdown_factor())));
}

TEST_F(FakeResolverTest, ReturnResultBeforeResolverStarted) {

  auto resolver = CreateResolver();
  ASSERT_NE(resolver, nullptr);
  Resolver::Result result = CreateResolverResult();
  absl::Notification notification;
  result_handler_->SetExpectedAndNotification(result, &notification);

  response_generator_->SetResponseAsync(std::move(result));

  RunSynchronously([resolver = resolver.get()] { resolver->StartLocked(); });

  ASSERT_TRUE(notification.WaitForNotificationWithTimeout(
      absl::Seconds(5 * grpc_test_slowdown_factor())));
}

TEST_F(FakeResolverTest, ReturnResult) {

  auto resolver = CreateResolver();
  ASSERT_NE(resolver, nullptr);
  RunSynchronously([resolver = resolver.get()] { resolver->StartLocked(); });
  Resolver::Result result = CreateResolverResult();
  absl::Notification notification;
  result_handler_->SetExpectedAndNotification(result, &notification);

  response_generator_->SetResponseAsync(std::move(result));

  ASSERT_TRUE(notification.WaitForNotificationWithTimeout(
      absl::Seconds(5 * grpc_test_slowdown_factor())));
}

TEST_F(FakeResolverTest, WaitForReresolutionRequest) {

  auto resolver = CreateResolver();
  ASSERT_NE(resolver, nullptr);
  RunSynchronously([resolver = resolver.get()] { resolver->StartLocked(); });

  EXPECT_FALSE(
      response_generator_->WaitForReresolutionRequest(absl::Milliseconds(1)));

  RunSynchronously(
      [resolver = resolver.get()] { resolver->RequestReresolutionLocked(); });
  EXPECT_TRUE(
      response_generator_->WaitForReresolutionRequest(absl::Milliseconds(1)));
}

}
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
