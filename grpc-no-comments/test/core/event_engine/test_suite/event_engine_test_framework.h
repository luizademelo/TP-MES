// Copyright 2021 gRPC authors.

#ifndef GRPC_TEST_CORE_EVENT_ENGINE_TEST_SUITE_EVENT_ENGINE_TEST_FRAMEWORK_H
#define GRPC_TEST_CORE_EVENT_ENGINE_TEST_SUITE_EVENT_ENGINE_TEST_FRAMEWORK_H
#include <grpc/event_engine/event_engine.h>

#include <memory>
#include <utility>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "gtest/gtest.h"

extern absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>*
    g_ee_factory;

extern absl::AnyInvocable<
    std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>*
    g_oracle_ee_factory;

class EventEngineTestEnvironment : public testing::Environment {
 public:
  EventEngineTestEnvironment(
      absl::AnyInvocable<
          std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
          factory,
      absl::AnyInvocable<
          std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
          oracle_factory)
      : factory_(std::move(factory)),
        oracle_factory_(std::move(oracle_factory)) {}

  void SetUp() override {
    g_ee_factory = &factory_;
    g_oracle_ee_factory = &oracle_factory_;
  }

  void TearDown() override {
    g_ee_factory = nullptr;
    g_oracle_ee_factory = nullptr;
  }

 private:
  absl::AnyInvocable<
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
      factory_;
  absl::AnyInvocable<
      std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
      oracle_factory_;
};

class EventEngineTest : public testing::Test {
 protected:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine>
  NewEventEngine() {
    CHECK_NE(g_ee_factory, nullptr);
    return (*g_ee_factory)();
  }

  std::shared_ptr<grpc_event_engine::experimental::EventEngine>
  NewOracleEventEngine() {
    CHECK_NE(g_oracle_ee_factory, nullptr);
    return (*g_oracle_ee_factory)();
  }
};

void SetEventEngineFactories(
    absl::AnyInvocable<
        std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
        ee_factory,
    absl::AnyInvocable<
        std::shared_ptr<grpc_event_engine::experimental::EventEngine>()>
        oracle_ee_factory);

#endif
