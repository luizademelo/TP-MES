// Copyright 2021 gRPC authors.

#include "test/core/event_engine/test_suite/event_engine_test_framework.h"

#include <grpc/event_engine/event_engine.h>

#include "gtest/gtest.h"

absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>*
    g_ee_factory = nullptr;

absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>*
    g_oracle_ee_factory = nullptr;

void SetEventEngineFactories(
    absl::AnyInvocable<
        std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
        factory,
    absl::AnyInvocable<
        std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
        oracle_ee_factory) {
  testing::AddGlobalTestEnvironment(new EventEngineTestEnvironment(
      std::move(factory), std::move(oracle_ee_factory)));
}
