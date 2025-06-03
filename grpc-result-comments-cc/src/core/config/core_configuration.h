Here's the commented version of the code:

```c++
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_CONFIG_CORE_CONFIGURATION_H
#define GRPC_SRC_CORE_CONFIG_CORE_CONFIGURATION_H

#include <grpc/support/port_platform.h>
#include <sys/stat.h>

#include <atomic>

#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"
#include "src/core/credentials/transport/channel_creds_registry.h"
#include "src/core/credentials/transport/tls/certificate_provider_registry.h"
#include "src/core/handshaker/handshaker_registry.h"
#include "src/core/handshaker/proxy_mapper_registry.h"
#include "src/core/lib/channel/channel_args_preconditioning.h"
#include "src/core/lib/surface/channel_init.h"
#include "src/core/load_balancing/lb_policy_registry.h"
#include "src/core/resolver/resolver_registry.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/transport/endpoint_transport.h"
#include "src/core/util/debug_location.h"

namespace grpc_core {

// CoreConfiguration class represents the central configuration for gRPC core.
// It manages various registries and builders that configure core functionality.
class GRPC_DLL CoreConfiguration {
 public:
  // Delete copy constructor and assignment operator to ensure singleton pattern
  CoreConfiguration(const CoreConfiguration&) = delete;
  CoreConfiguration& operator=(const CoreConfiguration&) = delete;

  // Enum defining the scope of configuration builders
  enum class BuilderScope {
    kPersistent,  // Persistent configurations survive resets
    kEphemeral,   // Ephemeral configurations are cleared on reset

    kCount,  // Sentinel value for counting scopes
  };

  // Builder class for constructing CoreConfiguration instances
  class Builder {
   public:
    // Accessors for various configuration builders
    ChannelArgsPreconditioning::Builder* channel_args_preconditioning() {
      return &channel_args_preconditioning_;
    }

    ChannelInit::Builder* channel_init() { return &channel_init_; }

    HandshakerRegistry::Builder* handshaker_registry() {
      return &handshaker_registry_;
    }

    ChannelCredsRegistry<>::Builder* channel_creds_registry() {
      return &channel_creds_registry_;
    }

    ServiceConfigParser::Builder* service_config_parser() {
      return &service_config_parser_;
    }

    ResolverRegistry::Builder* resolver_registry() {
      return &resolver_registry_;
    }

    LoadBalancingPolicyRegistry::Builder* lb_policy_registry() {
      return &lb_policy_registry_;
    }

    ProxyMapperRegistry::Builder* proxy_mapper_registry() {
      return &proxy_mapper_registry_;
    }

    CertificateProviderRegistry::Builder* certificate_provider_registry() {
      return &certificate_provider_registry_;
    }

    EndpointTransportRegistry::Builder* endpoint_transport_registry() {
      return &endpoint_transport_registry_;
    }

   private:
    friend class CoreConfiguration;

    // Builder components for various core functionalities
    ChannelArgsPreconditioning::Builder channel_args_preconditioning_;
    ChannelInit::Builder channel_init_;
    HandshakerRegistry::Builder handshaker_registry_;
    ChannelCredsRegistry<>::Builder channel_creds_registry_;
    ServiceConfigParser::Builder service_config_parser_;
    ResolverRegistry::Builder resolver_registry_;
    LoadBalancingPolicyRegistry::Builder lb_policy_registry_;
    ProxyMapperRegistry::Builder proxy_mapper_registry_;
    CertificateProviderRegistry::Builder certificate_provider_registry_;
    EndpointTransportRegistry::Builder endpoint_transport_registry_;

    Builder();
    CoreConfiguration* Build();  // Builds a CoreConfiguration instance
  };

  // Structure representing a registered builder with its metadata
  struct RegisteredBuilder {
    absl::AnyInvocable<void(Builder*)> builder;  // The builder function
    RegisteredBuilder* next;                     // Next builder in the chain
    SourceLocation whence;                       // Source location for debugging
  };

  // RAII class for temporarily substituting the core configuration
  class WithSubstituteBuilder {
   public:
    // Constructs a temporary configuration using the provided build function
    template <typename BuildFunc>
    explicit WithSubstituteBuilder(BuildFunc build) {
      Builder builder;
      build(&builder);
      CoreConfiguration* p = builder.Build();

      // Store current config and replace with new one
      config_restore_ =
          CoreConfiguration::config_.exchange(p, std::memory_order_acquire);
      builders_restore_ =
          CoreConfiguration::builders_[static_cast<size_t>(
                                           BuilderScope::kEphemeral)]
              .exchange(nullptr, std::memory_order_acquire);
    }

    // Restores original configuration on destruction
    ~WithSubstituteBuilder() {
      Reset();
      CHECK(CoreConfiguration::config_.exchange(
                config_restore_, std::memory_order_acquire) == nullptr);
      CHECK(CoreConfiguration::builders_[static_cast<size_t>(
                                             BuilderScope::kEphemeral)]
                .exchange(builders_restore_, std::memory_order_acquire) ==
            nullptr);
    }

   private:
    CoreConfiguration* config_restore_;   // Saved configuration to restore
    RegisteredBuilder* builders_restore_; // Saved builders to restore
  };

  // Returns the current configuration, building if necessary
  static const CoreConfiguration& Get() {
    CoreConfiguration* p = config_.load(std::memory_order_acquire);
    if (p != nullptr) {
      return *p;
    }
    return BuildNewAndMaybeSet();
  }

  // Registers a builder function with the specified scope
  static void RegisterBuilder(BuilderScope scope,
                              absl::AnyInvocable<void(Builder*)> builder,
                              SourceLocation whence);

  // Convenience methods for registering persistent/ephemeral builders
  static void RegisterPersistentBuilder(
      absl::AnyInvocable<void(Builder*)> builder, SourceLocation whence = {}) {
    RegisterBuilder(BuilderScope::kPersistent, std::move(builder), whence);
  }

  static void RegisterEphemeralBuilder(
      absl::AnyInvocable<void(Builder*)> builder, SourceLocation whence = {}) {
    RegisterBuilder(BuilderScope::kEphemeral, std::move(builder), whence);
  }

  // Resets the configuration (clears ephemeral builders)
  static void Reset();

  // Resets all configuration including persistent builders (use with caution)
  static void
  ResetEverythingIncludingPersistentBuildersAbsolutelyNotRecommended();

  // Runs code with a temporary special configuration
  template <typename BuildFunc, typename RunFunc>
  static void RunWithSpecialConfiguration(BuildFunc build_configuration,
                                          RunFunc code_to_run) {
    WithSubstituteBuilder builder(build_configuration);
    code_to_run();
  }

  // Accessors for various configuration components
  const ChannelArgsPreconditioning& channel_args_preconditioning() const {
    return channel_args_preconditioning_;
  }

  const ChannelInit& channel_init() const { return channel_init_; }

  const HandshakerRegistry& handshaker_registry() const {
    return handshaker_registry_;
  }

  const ChannelCredsRegistry<>& channel_creds_registry() const {
    return channel_creds_registry_;
  }

  const ServiceConfigParser& service_config_parser() const {
    return service_config_parser_;
  }

  const ResolverRegistry& resolver_registry() const {
    return resolver_registry_;
  }

  const LoadBalancingPolicyRegistry& lb_policy_registry() const {
    return lb_policy_registry_;
  }

  const ProxyMapperRegistry& proxy_mapper_registry() const {
    return proxy_mapper_registry_;
  }

  const CertificateProviderRegistry& certificate_provider_registry() const {
    return certificate_provider_registry_;
  }

  const EndpointTransportRegistry& endpoint_transport_registry() const {
    return endpoint_transport_registry_;
  }

  // Sets the default builder function
  static void SetDefaultBuilder(void (*builder)(CoreConfiguration::Builder*)) {
    default_builder_ = builder;
  }

 private:
  explicit CoreConfiguration(Builder* builder);

  // Builds a new configuration and sets it if needed
  static const CoreConfiguration& BuildNewAndMaybeSet();

  // Static members for managing the singleton configuration
  static std::atomic<CoreConfiguration*> config_;
  static std::atomic<bool> has_config_ever_been_produced_;
  static std::atomic<RegisteredBuilder*>
      builders_[static_cast<size_t>(BuilderScope::kCount)];
  static void (*default_builder_)(CoreConfiguration::Builder*);

  // Configuration components
  ChannelArgsPreconditioning channel_args_preconditioning_;
  ChannelInit channel_init_;
  HandshakerRegistry handshaker_registry_;
  ChannelCredsRegistry<> channel_creds_registry_;
  ServiceConfigParser service_config_parser_;
  ResolverRegistry resolver_registry_;
  LoadBalancingPolicyRegistry lb_policy_registry_;
  ProxyMapperRegistry proxy_mapper_registry_;
  CertificateProviderRegistry certificate_provider_registry_;
  EndpointTransportRegistry endpoint_transport_registry_;
};

// Stringification for BuilderScope enum
template <typename Sink>
void AbslStringify(Sink& sink, CoreConfiguration::BuilderScope scope) {
  switch (scope) {
    case CoreConfiguration::BuilderScope::kPersistent:
      sink.Append("Persistent");
      break;
    case CoreConfiguration::BuilderScope::kEphemeral:
      sink.Append("Ephemeral");
      break;
    case CoreConfiguration::BuilderScope::kCount:
      sink.Append("Count(");
      sink.Append(std::to_string(static_cast<size_t>(scope)));
      sink.Append(")");
      break;
  }
}

// Default core configuration builder function
extern void BuildCoreConfiguration(CoreConfiguration::Builder* builder);

}  // namespace grpc_core

#endif
```