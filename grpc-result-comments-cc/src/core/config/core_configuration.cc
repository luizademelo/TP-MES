Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#include "src/core/config/core_configuration.h"

#include <grpc/support/port_platform.h>

#include <atomic>
#include <utility>
#include <vector>

#include "absl/log/check.h"

namespace grpc_core {

// Static atomic pointer to the current CoreConfiguration instance
std::atomic<CoreConfiguration*> CoreConfiguration::config_{nullptr};
// Static array of atomic pointers to registered builders, indexed by BuilderScope
std::atomic<CoreConfiguration::RegisteredBuilder*>
    CoreConfiguration::builders_[static_cast<size_t>(BuilderScope::kCount)]{
        nullptr, nullptr};
// Flag indicating if a configuration has ever been produced
std::atomic<bool> CoreConfiguration::has_config_ever_been_produced_{false};
// Pointer to the default builder function
void (*CoreConfiguration::default_builder_)(CoreConfiguration::Builder*);

// Default constructor for Builder
CoreConfiguration::Builder::Builder() = default;

// Builds and returns a new CoreConfiguration instance from this builder
CoreConfiguration* CoreConfiguration::Builder::Build() {
  return new CoreConfiguration(this);
}

// CoreConfiguration constructor that initializes all registries from the builder
CoreConfiguration::CoreConfiguration(Builder* builder)
    : channel_args_preconditioning_(
          builder->channel_args_preconditioning_.Build()),
      channel_init_(builder->channel_init_.Build()),
      handshaker_registry_(builder->handshaker_registry_.Build()),
      channel_creds_registry_(builder->channel_creds_registry_.Build()),
      service_config_parser_(builder->service_config_parser_.Build()),
      resolver_registry_(builder->resolver_registry_.Build()),
      lb_policy_registry_(builder->lb_policy_registry_.Build()),
      proxy_mapper_registry_(builder->proxy_mapper_registry_.Build()),
      certificate_provider_registry_(
          builder->certificate_provider_registry_.Build()),
      endpoint_transport_registry_(
          builder->endpoint_transport_registry_.Build()) {}

// Registers a new builder for a specific scope
// Throws CHECK failures if registration is attempted at invalid times
void CoreConfiguration::RegisterBuilder(
    BuilderScope scope, absl::AnyInvocable<void(Builder*)> builder,
    SourceLocation whence) {
  CHECK(config_.load(std::memory_order_relaxed) == nullptr)
      << "CoreConfiguration was already instantiated before builder "
         "registration was completed";
  if (scope == BuilderScope::kPersistent) {
    CHECK(!has_config_ever_been_produced_.load(std::memory_order_relaxed))
        << "Persistent builders cannot be registered after the first "
           "CoreConfiguration has been produced";
  }
  CHECK_NE(scope, BuilderScope::kCount);
  auto& head = builders_[static_cast<size_t>(scope)];
  RegisteredBuilder* n = new RegisteredBuilder();
  VLOG(4) << "Registering " << scope << " builder from " << whence.file() << ":"
          << whence.line();
  n->builder = std::move(builder);
  n->whence = whence;
  n->next = head.load(std::memory_order_relaxed);
  // Atomically prepend the new builder to the linked list
  while (!head.compare_exchange_weak(n->next, n, std::memory_order_acq_rel,
                                     std::memory_order_relaxed)) {
  }
  CHECK(config_.load(std::memory_order_relaxed) == nullptr)
      << "CoreConfiguration was already instantiated before builder "
         "registration was completed";
}

// Builds a new CoreConfiguration and sets it as the active configuration
// if no other configuration exists
const CoreConfiguration& CoreConfiguration::BuildNewAndMaybeSet() {
  // Mark that we've produced at least one configuration
  has_config_ever_been_produced_.store(true, std::memory_order_relaxed);

  Builder builder;

  // Collect all registered builders from both scopes
  std::vector<RegisteredBuilder*> registered_builders;
  for (auto scope : {BuilderScope::kEphemeral, BuilderScope::kPersistent}) {
    for (RegisteredBuilder* b = builders_[static_cast<size_t>(scope)].load(
             std::memory_order_acquire);
         b != nullptr; b = b->next) {
      registered_builders.push_back(b);
    }
  }
  // Run builders in reverse order of registration (last registered runs first)
  for (auto it = registered_builders.rbegin(); it != registered_builders.rend();
       ++it) {
    VLOG(4) << "Running builder from " << (*it)->whence.file() << ":"
            << (*it)->whence.line();
    (*it)->builder(&builder);
  }

  // Run the default builder if one exists
  if (default_builder_ != nullptr) (*default_builder_)(&builder);

  // Build the final configuration
  CoreConfiguration* p = builder.Build();

  // Try to set the new configuration, but if someone else beat us to it,
  // use theirs and delete ours
  CoreConfiguration* expected = nullptr;
  if (!config_.compare_exchange_strong(expected, p, std::memory_order_acq_rel,
                                       std::memory_order_acquire)) {
    delete p;
    return *expected;
  }
  return *p;
}

// Resets the current configuration and clears all ephemeral builders
void CoreConfiguration::Reset() {
  delete config_.exchange(nullptr, std::memory_order_acquire);
  RegisteredBuilder* builder =
      builders_[static_cast<size_t>(BuilderScope::kEphemeral)].exchange(
          nullptr, std::memory_order_acquire);
  // Clean up all ephemeral builders
  while (builder != nullptr) {
    RegisteredBuilder* next = builder->next;
    delete builder;
    builder = next;
  }
}

// Full reset including persistent builders - should be used with caution
void CoreConfiguration::
    ResetEverythingIncludingPersistentBuildersAbsolutelyNotRecommended() {
  // Reset the "has ever been produced" flag
  has_config_ever_been_produced_.store(false, std::memory_order_relaxed);
  // Clean up all persistent builders
  RegisteredBuilder* builder =
      builders_[static_cast<size_t>(BuilderScope::kPersistent)].exchange(
          nullptr, std::memory_order_acquire);
  while (builder != nullptr) {
    RegisteredBuilder* next = builder->next;
    delete builder;
    builder = next;
  }
  // Call regular reset for the rest
  Reset();
}

}
```