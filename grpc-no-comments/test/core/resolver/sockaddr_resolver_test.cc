
// Copyright 2015 gRPC authors.

#include <memory>
#include <string>
#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "gtest/gtest.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/port.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"
#include "src/core/util/work_serializer.h"
#include "test/core/test_util/test_config.h"

static std::shared_ptr<grpc_core::WorkSerializer>* g_work_serializer;

class ResultHandler : public grpc_core::Resolver::ResultHandler {
 public:
  void ReportResult(grpc_core::Resolver::Result ) override {}
};

static void test_succeeds(grpc_core::ResolverFactory* factory,
                          const char* string) {
  VLOG(2) << "test: '" << string << "' should be valid for '"
          << factory->scheme() << "'";
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(string);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status().ToString();
    ASSERT_TRUE(uri.ok());
  }
  grpc_core::ResolverArgs args;
  args.uri = std::move(*uri);
  args.work_serializer = *g_work_serializer;
  args.result_handler = std::make_unique<ResultHandler>();
  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      factory->CreateResolver(std::move(args));
  ASSERT_NE(resolver, nullptr);
  resolver->StartLocked();

  grpc_core::ExecCtx::Get()->Flush();
}

static void test_fails(grpc_core::ResolverFactory* factory,
                       const char* string) {
  VLOG(2) << "test: '" << string << "' should be invalid for '"
          << factory->scheme() << "'";
  grpc_core::ExecCtx exec_ctx;
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(string);
  if (!uri.ok()) {
    LOG(ERROR) << uri.status().ToString();
    ASSERT_TRUE(uri.ok());
  }
  grpc_core::ResolverArgs args;
  args.uri = std::move(*uri);
  args.work_serializer = *g_work_serializer;
  args.result_handler = std::make_unique<ResultHandler>();
  grpc_core::OrphanablePtr<grpc_core::Resolver> resolver =
      factory->CreateResolver(std::move(args));
  ASSERT_EQ(resolver, nullptr);
}

TEST(SockaddrResolverTest, MainTest) {
  auto work_serializer = std::make_shared<grpc_core::WorkSerializer>(
      grpc_event_engine::experimental::GetDefaultEventEngine());
  g_work_serializer = &work_serializer;

  grpc_core::ResolverFactory* ipv4 = grpc_core::CoreConfiguration::Get()
                                         .resolver_registry()
                                         .LookupResolverFactory("ipv4");
  grpc_core::ResolverFactory* ipv6 = grpc_core::CoreConfiguration::Get()
                                         .resolver_registry()
                                         .LookupResolverFactory("ipv6");

  test_fails(ipv4, "ipv4:10.2.1.1");
  test_succeeds(ipv4, "ipv4:10.2.1.1:1234");
  test_succeeds(ipv4, "ipv4:10.2.1.1:1234,127.0.0.1:4321");
  test_fails(ipv4, "ipv4:10.2.1.1:123456");
  test_fails(ipv4, "ipv4:www.google.com");
  test_fails(ipv4, "ipv4:[");
  test_fails(ipv4, "ipv4://8.8.8.8/8.8.8.8:8888");

  test_fails(ipv6, "ipv6:[");
  test_fails(ipv6, "ipv6:[::]");
  test_succeeds(ipv6, "ipv6:[::]:1234");
  test_fails(ipv6, "ipv6:[::]:123456");
  test_fails(ipv6, "ipv6:www.google.com");

#ifdef GRPC_HAVE_UNIX_SOCKET
  grpc_core::ResolverFactory* uds = grpc_core::CoreConfiguration::Get()
                                        .resolver_registry()
                                        .LookupResolverFactory("unix");
  grpc_core::ResolverFactory* uds_abstract =
      grpc_core::CoreConfiguration::Get()
          .resolver_registry()
          .LookupResolverFactory("unix-abstract");

  test_succeeds(uds, "unix:///tmp/sockaddr_resolver_test");
  test_succeeds(uds_abstract, "unix-abstract:sockaddr_resolver_test");
#endif
}

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  grpc::testing::TestGrpcScope grpc_scope;
  return RUN_ALL_TESTS();
}
