Here's the commented version of the code:

```c++
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
// Global atomic pointer to the event engine factory function
std::atomic<absl::AnyInvocable<std::shared_ptr<EventEngine>()>*>
    g_event_engine_factory{nullptr};
// Global mutex for thread-safe access to the default event engine
grpc_core::NoDestruct<grpc_core::Mutex> g_mu;

// Global storage for the default event engine, which can be either:
// 1. A weak_ptr (when no strong references exist externally)
// 2. A shared_ptr (when actively being used)
grpc_core::NoDestruct<
    std::variant<std::weak_ptr<EventEngine>, std::shared_ptr<EventEngine>>>
    g_default_event_engine ABSL_GUARDED_BY(*g_mu);

// Internal helper function to get the default event engine if it exists
// Must be called with g_mu held
std::shared_ptr<EventEngine> InternalGetDefaultEventEngineIfAny()
    ABSL_EXCLUSIVE_LOCKS_REQUIRED(*g_mu) {
  return grpc_core::MatchMutable(
      g_default_event_engine.get(),
      [&](std::shared_ptr<EventEngine>* event_engine) { return *event_engine; },
      [&](std::weak_ptr<EventEngine>* weak_ee) { return weak_ee->lock(); });
}

}  // namespace

// Sets a custom factory function for creating event engines
// This will replace any existing factory and reset the default engine
void SetEventEngineFactory(
    absl::AnyInvocable<std::shared_ptr<EventEngine>()> factory) {
  // Atomically replace the factory and delete the old one
  delete g_event_engine_factory.exchange(
      new absl::AnyInvocable<std::shared_ptr<EventEngine>()>(
          std::move(factory)));

  // Reset the default engine to a weak_ptr (no strong references)
  grpc_core::MutexLock lock(&*g_mu);
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
}

// Resets the event engine factory to default and clears any stored engine
void EventEngineFactoryReset() {
  grpc_core::MutexLock lock(&*g_mu);
  // Atomically reset the factory to nullptr
  delete g_event_engine_factory.exchange(nullptr);
  // Reset the default engine to a weak_ptr
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
}

// Creates a new event engine instance using either:
// 1. The custom factory if set
// 2. The default factory otherwise
// If GRPC_MAXIMIZE_THREADYNESS is defined, wraps the engine in a ThreadyEventEngine
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

// Sets the default event engine to be returned by GetDefaultEventEngine()
// If engine is nullptr, resets to a weak_ptr (no default engine)
void SetDefaultEventEngine(std::shared_ptr<EventEngine> engine) {
  grpc_core::MutexLock lock(&*g_mu);
  if (engine == nullptr) {
    g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
  } else {
    *g_default_event_engine = std::move(engine);
  }
}

// Gets the default event engine, creating one if none exists
// Maintains a weak_ptr reference internally to avoid keeping the engine alive
// when no external references exist
std::shared_ptr<EventEngine> GetDefaultEventEngine() {
  grpc_core::MutexLock lock(&*g_mu);
  auto engine = InternalGetDefaultEventEngineIfAny();
  if (engine != nullptr) return engine;
  engine = CreateEventEngine();
  g_default_event_engine->emplace<std::weak_ptr<EventEngine>>(engine);
  return engine;
}

// Shuts down the default event engine and waits for all references to be released
void ShutdownDefaultEventEngine() {
  std::shared_ptr<EventEngine> tmp_engine;
  {
    grpc_core::MutexLock lock(&*g_mu);
    // Get any existing engine and reset to weak_ptr
    tmp_engine = InternalGetDefaultEventEngineIfAny();
    g_default_event_engine->emplace<std::weak_ptr<EventEngine>>();
  }
  // Wait for all external references to be released
  if (tmp_engine != nullptr) {
    grpc_core::WaitForSingleOwner(std::move(tmp_engine));
  }
}

namespace {
// Ensures that the channel args contain an EventEngine instance
// If none exists, adds the default event engine
grpc_core::ChannelArgs EnsureEventEngineInChannelArgs(
    grpc_core::ChannelArgs args) {
  if (args.ContainsObject<EventEngine>()) return args;
  return args.SetObject<EventEngine>(GetDefaultEventEngine());
}
}  // namespace

// Registers the EventEngine preconditioning stage with CoreConfiguration
// This ensures all channel args will have an EventEngine instance
void RegisterEventEngineChannelArgPreconditioning(
    grpc_core::CoreConfiguration::Builder* builder) {
  builder->channel_args_preconditioning()->RegisterStage(
      grpc_event_engine::experimental::EnsureEventEngineInChannelArgs);
}

}  // namespace grpc_event_engine::experimental
```