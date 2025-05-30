// Copyright 2024 gRPC authors.

#ifndef GRPC_TEST_CORE_TRANSPORT_TEST_SUITE_CHAOTIC_GOOD_FIXTURE_HELPERS_H
#define GRPC_TEST_CORE_TRANSPORT_TEST_SUITE_CHAOTIC_GOOD_FIXTURE_HELPERS_H

#include <memory>

#include "absl/log/check.h"
#include "gmock/gmock.h"
#include "src/core/ext/transport/chaotic_good/client_transport.h"
#include "src/core/ext/transport/chaotic_good/server_transport.h"
#include "src/core/lib/event_engine/memory_allocator_factory.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/lib/resource_quota/resource_quota.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "test/core/transport/test_suite/transport_test.h"

namespace grpc_core {

class MockEndpointConfig
    : public grpc_event_engine::experimental::EndpointConfig {
 public:
  MOCK_METHOD(std::optional<int>, GetInt, (absl::string_view key),
              (const, override));
  MOCK_METHOD(std::optional<absl::string_view>, GetString,
              (absl::string_view key), (const, override));
  MOCK_METHOD(void*, GetVoidPointer, (absl::string_view key),
              (const, override));
};

struct EndpointPair {
  PromiseEndpoint client;
  PromiseEndpoint server;
};

EndpointPair CreateEndpointPair(
    grpc_event_engine::experimental::FuzzingEventEngine* event_engine,
    ResourceQuota* resource_quota, int port);

class FakeClientConnectionFactory final
    : public chaotic_good::ClientConnectionFactory {
 public:
  chaotic_good::PendingConnection Connect(absl::string_view) override {
    Crash("Connect not implemented");
  }
  void Orphaned() override {}
};

class FakeServerConnectionFactory final
    : public chaotic_good::ServerConnectionFactory {
 public:
  chaotic_good::PendingConnection RequestDataConnection() override {
    Crash("RequestDataConnection not implemented");
  }
  void Orphaned() override {}
};

}

#endif
