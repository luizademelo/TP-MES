
// Copyright 2015 gRPC authors.

#include <memory>
#include <string>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "gtest/gtest.h"
#include "src/core/config/config_vars.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"
#include "test/core/test_util/test_config.h"

using ::grpc_event_engine::experimental::GetDefaultEventEngine;

static std::shared_ptr<grpc_core::WorkSerializer>* g_work_serializer;

class TestResultHandler : public grpc_core::Resolver::ResultHandler {
  void ReportResult(grpc_core::Resolver::Result ) override {}
};

static void test_succeeds(grpc_core::ResolverFactory* factory,
                          const char* string) {
  VLOG(2) << "test: '" << string << "' should be valid for '"
          << factory->scheme() << "'";
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(string);
  if (!uri.ok()) {
    FAIL() << "Error: " << uri.status().ToString();
  }
  grpc_core::ResolverArgs args;
  args.uri = std::move(*uri);
  args.work_serializer = *g_work_serializer;
  args.result_handler = std::make_unique<TestResultHandler>();
  args.args = args.args.SetObject(GetDefaultEventEngine());
  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      factory->CreateResolver(std::move(args));
  ASSERT_NE(resolver, nullptr);
}

static void test_fails(grpc_core::ResolverFactory* factory,
                       const char* string) {
  VLOG(2) << "test: '" << string << "' should be invalid for '"
          << factory->scheme() << "'";
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(string);
  if (!uri.ok()) {
    FAIL() << "Error: " << uri.status().ToString();
  }
  grpc_core::ResolverArgs args;
  args.uri = std::move(*uri);
  args.work_serializer = *g_work_serializer;
  args.result_handler = std::make_unique<TestResultHandler>();
  args.args = args.args.SetObject(GetDefaultEventEngine());
  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      factory->CreateResolver(std::move(args));
  ASSERT_EQ(resolver, nullptr);
}

TEST(DnsResolverTest, MainTest) {
  auto work_serializer = std::make_shared<grpc_core::WorkSerializer>(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  g_work_serializer = &work_serializer;

  grpc_core::ResolverFactory* dns = grpc_core::CoreConfiguration::Get()
                                        .resolver_registry()
                                        .LookupResolverFactory("dns");

  test_succeeds(dns, "dns:10.2.1.1");
  test_succeeds(dns, "dns:10.2.1.1:1234");
  test_succeeds(dns, "dns:www.google.com");
  test_succeeds(dns, "dns:///www.google.com");
  if (grpc_core::ConfigVars::Get().DnsResolver() == "native") {
    test_fails(dns, "dns://8.8.8.8/8.8.8.8:8888");
  } else {
    test_succeeds(dns, "dns://8.8.8.8/8.8.8.8:8888");
  }
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
