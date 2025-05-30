
// Copyright 2024 gRPC authors.

#include "src/core/ext/filters/gcp_authentication/gcp_authentication_filter.h"

#include <memory>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "src/core/call/security_context.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/call/gcp_service_account_identity/gcp_service_account_identity_credentials.h"
#include "src/core/ext/filters/gcp_authentication/gcp_authentication_service_config_parser.h"
#include "src/core/lib/channel/channel_stack.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/resolver/xds/xds_resolver_attributes.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_call_data.h"

namespace grpc_core {

absl::Status GcpAuthenticationFilter::Call::OnClientInitialMetadata(
    ClientMetadata& , GcpAuthenticationFilter* filter) {

  auto* service_config_call_data = GetContext<ServiceConfigCallData>();
  auto cluster_attribute =
      service_config_call_data->GetCallAttribute<XdsClusterAttribute>();
  if (cluster_attribute == nullptr) {

    return absl::InternalError(
        "GCP authentication filter: call has no xDS cluster attribute");
  }
  absl::string_view cluster_name = cluster_attribute->cluster();
  if (!absl::ConsumePrefix(&cluster_name, "cluster:")) {
    return absl::OkStatus();
  }

  auto it = filter->xds_config_->clusters.find(cluster_name);
  if (it == filter->xds_config_->clusters.end()) {

    return absl::InternalError(
        absl::StrCat("GCP authentication filter: xDS cluster ", cluster_name,
                     " not found in XdsConfig"));
  }
  if (!it->second.ok()) {

    // Note: For wait_for_ready calls, this does the wrong thing by

    return absl::UnavailableError(
        absl::StrCat("GCP authentication filter: CDS resource unavailable for ",
                     cluster_name));
  }
  if (it->second->cluster == nullptr) {

    return absl::InternalError(absl::StrCat(
        "GCP authentication filter: CDS resource not present for cluster ",
        cluster_name));
  }
  auto& metadata_map = it->second->cluster->metadata;
  const XdsMetadataValue* metadata_value =
      metadata_map.Find(filter->filter_config_->filter_instance_name);

  if (metadata_value == nullptr) return absl::OkStatus();

  if (metadata_value->type() != XdsGcpAuthnAudienceMetadataValue::Type()) {
    return absl::UnavailableError(absl::StrCat(
        "GCP authentication filter: audience metadata in wrong format for "
        "cluster ",
        cluster_name));
  }

  auto creds = filter->cache_->Get(
      DownCast<const XdsGcpAuthnAudienceMetadataValue*>(metadata_value)->url());

  auto* arena = GetContext<Arena>();
  auto* security_ctx = DownCast<grpc_client_security_context*>(
      arena->GetContext<SecurityContext>());
  if (security_ctx == nullptr) {
    security_ctx = arena->New<grpc_client_security_context>(std::move(creds));
    arena->SetContext<SecurityContext>(security_ctx);
  } else {
    security_ctx->creds = std::move(creds);
  }
  return absl::OkStatus();
}

UniqueTypeName GcpAuthenticationFilter::CallCredentialsCache::Type() {
  static UniqueTypeName::Factory factory("gcp_auth_call_creds_cache");
  return factory.Create();
}

void GcpAuthenticationFilter::CallCredentialsCache::SetMaxSize(
    size_t max_size) {
  MutexLock lock(&mu_);
  cache_.SetMaxSize(max_size);
}

RefCountedPtr<grpc_call_credentials>
GcpAuthenticationFilter::CallCredentialsCache::Get(
    const std::string& audience) {
  MutexLock lock(&mu_);
  return cache_.GetOrInsert(audience, [](const std::string& audience) {
    return MakeRefCounted<GcpServiceAccountIdentityCallCredentials>(audience);
  });
}

const grpc_channel_filter GcpAuthenticationFilter::kFilter =
    MakePromiseBasedFilter<GcpAuthenticationFilter, FilterEndpoint::kClient,
                           0>();

absl::StatusOr<std::unique_ptr<GcpAuthenticationFilter>>
GcpAuthenticationFilter::Create(const ChannelArgs& args,
                                ChannelFilter::Args filter_args) {

  auto service_config = args.GetObjectRef<ServiceConfig>();
  if (service_config == nullptr) {
    return absl::InvalidArgumentError(
        "gcp_auth: no service config in channel args");
  }
  auto* config = static_cast<const GcpAuthenticationParsedConfig*>(
      service_config->GetGlobalParsedConfig(
          GcpAuthenticationServiceConfigParser::ParserIndex()));
  if (config == nullptr) {
    return absl::InvalidArgumentError("gcp_auth: parsed config not found");
  }
  auto* filter_config = config->GetConfig(filter_args.instance_id());
  if (filter_config == nullptr) {
    return absl::InvalidArgumentError(
        "gcp_auth: filter instance ID not found in filter config");
  }

  auto xds_config = args.GetObjectRef<XdsConfig>();
  if (xds_config == nullptr) {
    return absl::InvalidArgumentError(
        "gcp_auth: xds config not found in channel args");
  }

  auto cache = filter_args.GetOrCreateState<CallCredentialsCache>(
      filter_config->filter_instance_name, [&]() {
        return MakeRefCounted<CallCredentialsCache>(filter_config->cache_size);
      });

  cache->SetMaxSize(filter_config->cache_size);

  return std::unique_ptr<GcpAuthenticationFilter>(
      new GcpAuthenticationFilter(std::move(service_config), filter_config,
                                  std::move(xds_config), std::move(cache)));
}

GcpAuthenticationFilter::GcpAuthenticationFilter(
    RefCountedPtr<ServiceConfig> service_config,
    const GcpAuthenticationParsedConfig::Config* filter_config,
    RefCountedPtr<const XdsConfig> xds_config,
    RefCountedPtr<CallCredentialsCache> cache)
    : service_config_(std::move(service_config)),
      filter_config_(filter_config),
      xds_config_(std::move(xds_config)),
      cache_(std::move(cache)) {}

void GcpAuthenticationFilterRegister(CoreConfiguration::Builder* builder) {
  GcpAuthenticationServiceConfigParser::Register(builder);
}

}
