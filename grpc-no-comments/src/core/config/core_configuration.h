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

class GRPC_DLL CoreConfiguration {
 public:
  CoreConfiguration(const CoreConfiguration&) = delete;
  CoreConfiguration& operator=(const CoreConfiguration&) = delete;

  enum class BuilderScope {
    kPersistent,
    kEphemeral,

    kCount,
  };

  class Builder {
   public:
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
    CoreConfiguration* Build();
  };

  struct RegisteredBuilder {
    absl::AnyInvocable<void(Builder*)> builder;
    RegisteredBuilder* next;
    SourceLocation whence;
  };

  class WithSubstituteBuilder {
   public:
    template <typename BuildFunc>
    explicit WithSubstituteBuilder(BuildFunc build) {

      Builder builder;
      build(&builder);
      CoreConfiguration* p = builder.Build();

      config_restore_ =
          CoreConfiguration::config_.exchange(p, std::memory_order_acquire);
      builders_restore_ =
          CoreConfiguration::builders_[static_cast<size_t>(
                                           BuilderScope::kEphemeral)]
              .exchange(nullptr, std::memory_order_acquire);
    }

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
    CoreConfiguration* config_restore_;
    RegisteredBuilder* builders_restore_;
  };

  static const CoreConfiguration& Get() {
    CoreConfiguration* p = config_.load(std::memory_order_acquire);
    if (p != nullptr) {
      return *p;
    }
    return BuildNewAndMaybeSet();
  }

  static void RegisterBuilder(BuilderScope scope,
                              absl::AnyInvocable<void(Builder*)> builder,
                              SourceLocation whence);

  static void RegisterPersistentBuilder(
      absl::AnyInvocable<void(Builder*)> builder, SourceLocation whence = {}) {
    RegisterBuilder(BuilderScope::kPersistent, std::move(builder), whence);
  }

  static void RegisterEphemeralBuilder(
      absl::AnyInvocable<void(Builder*)> builder, SourceLocation whence = {}) {
    RegisterBuilder(BuilderScope::kEphemeral, std::move(builder), whence);
  }

  static void Reset();

  static void
  ResetEverythingIncludingPersistentBuildersAbsolutelyNotRecommended();

  template <typename BuildFunc, typename RunFunc>
  static void RunWithSpecialConfiguration(BuildFunc build_configuration,
                                          RunFunc code_to_run) {
    WithSubstituteBuilder builder(build_configuration);
    code_to_run();
  }

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

  static void SetDefaultBuilder(void (*builder)(CoreConfiguration::Builder*)) {
    default_builder_ = builder;
  }

 private:
  explicit CoreConfiguration(Builder* builder);

  static const CoreConfiguration& BuildNewAndMaybeSet();

  static std::atomic<CoreConfiguration*> config_;

  static std::atomic<bool> has_config_ever_been_produced_;

  static std::atomic<RegisteredBuilder*>
      builders_[static_cast<size_t>(BuilderScope::kCount)];

  static void (*default_builder_)(CoreConfiguration::Builder*);

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

extern void BuildCoreConfiguration(CoreConfiguration::Builder* builder);

}

#endif
