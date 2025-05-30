// Copyright 2021 The gRPC Authors

#include "src/core/lib/event_engine/default_event_engine.h"

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <utility>
#include <variant>

#include "absl/functional/any_invocable.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/event_engine/default_event_engine_factory.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/match.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/sync.h"
#include "src/core/util/wait_for_single_owner.h"

#ifdef GRPC_MAXIMIZE_THREADYNESS
#include "src/core/lib/event_engine/thready_event_engine/thready_event_engine.h"
#endif

namespace grpc_event_engine::experimental {

namespace {

std::atomic<absl::AnyInvocable<std::shared_ptr<EventEngine>()>*>
    g_event_engine_factory{nullptr};
grpc_core::NoDestruct<grpc_core::Mutex> g_mu;

grpc_core::NoDestruct<
    std::variant<std::weak_ptr<EventEngine>, std::shared_ptr<EventEngine>>>
    g_default_event_engine ABSL_GUARDED_BY(*g_mu);

std::shared_ptr<EventEngine> InternalGetDefaultEventEngineIfAny()
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(*g_mu) {
  return grpc_core::MatchMutable(
      g_default_event_engine.get(),
      [&](std::shared_ptr<EventEngine>* event_engine) { return *event_engine; },
      [&](std::weak_ptr<EventEngine>* weak_ee) { return weak_ee->lock(); });
}

}

void SetEventEngineFactory(
    absl::AnyInvocable<std::shared_ptr<EventEngine>()> factory) {
  delete g_event_engine_factory.exchange(
      new absl::AnyInvocable<std::shared_ptr<EventEngine>()>(
          std::move(factory)));

  grpc_core::MutexLock lock(&*g_mu);
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
}

void EventEngineFactoryReset() {
  grpc_core::MutexLock lock(&*g_mu);
  delete g_event_engine_factory.exchange(nullptr);
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
}

std::shared_ptr<EventEngine> CreateEventEngine() {
  std::shared_ptr<EventEngine> engine;
  if (auto* factory = g_event_engine_factory.load()) {
    engine = (*factory)();
  } else {
    engine = DefaultEventEngineFactory();
  }
#ifdef GRPC_MAXIMIZE_THREADYNESS
  return std::make_shared<ThreadyEventEngine>(std::move(engine));
#endif
  return engine;
}

void SetDefaultEventEngine(std::shared_ptr<EventEngine> engine) {
  grpc_core::MutexLock lock(&*g_mu);
  if (engine == nullptr) {

    g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
  } else {
    *g_default_event_engine = std::move(engine);
  }
}

std::shared_ptr<EventEngine> GetDefaultEventEngine() {
  grpc_core::MutexLock lock(&*g_mu);
  auto engine = InternalGetDefaultEventEngineIfAny();
  if (engine != nullptr) return engine;
  engine = CreateEventEngine();
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>(engine);
  return engine;
}

void ShutdownDefaultEventEngine() {
  std::shared_ptr<EventEngine> tmp_engine;
  {
    grpc_core::MutexLock lock(&*g_mu);
    tmp_engine = InternalGetDefaultEventEngineIfAny();
    g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
  }
  if (tmp_engine != nullptr) {
    grpc_core::WaitForSingleOwner(std::move(tmp_engine));
  }
}

namespace {
grpc_core::ChannelArgs EnsureEventEngineInChannelArgs(
    grpc_core::ChannelArgs args) {
  if (args.ContainsObject<EventEngine>()) return args;
  return args.SetObject<EventEngine>(GetDefaultEventEngine());
}
}

void RegisterEventEngineChannelArgPreconditioning(
    grpc_core::CoreConfiguration::Builder* builder) {
  builder->channel_args_preconditioning()->RegisterStage(
      grpc_event_engine::experimental::EnsureEventEngineInChannelArgs);
}

}
