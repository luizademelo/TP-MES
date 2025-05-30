
// Copyright 2020 gRPC authors.

#include "src/core/xds/grpc/certificate_provider_store.h"

#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>

#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/tls/certificate_provider_registry.h"

namespace grpc_core {

const JsonLoaderInterface*
CertificateProviderStore::PluginDefinition::JsonLoader(const JsonArgs&) {
  static const auto* loader =
      JsonObjectLoader<PluginDefinition>()
          .Field("plugin_name", &PluginDefinition::plugin_name)
          .Finish();
  return loader;
}

void CertificateProviderStore::PluginDefinition::JsonPostLoad(
    const Json& json, const JsonArgs& args, ValidationErrors* errors) {

  CertificateProviderFactory* factory = nullptr;
  if (!plugin_name.empty()) {
    ValidationErrors::ScopedField field(errors, ".plugin_name");
    factory = CoreConfiguration::Get()
                  .certificate_provider_registry()
                  .LookupCertificateProviderFactory(plugin_name);
    if (factory == nullptr) {
      errors->AddError(absl::StrCat("Unrecognized plugin name: ", plugin_name));
      return;
    }
  }

  {
    ValidationErrors::ScopedField field(errors, ".config");
    auto it = json.object().find("config");

    Json::Object config_json;
    if (it != json.object().end()) {
      if (it->second.type() != Json::Type::kObject) {
        errors->AddError("is not an object");
        return;
      } else {
        config_json = it->second.object();
      }
    }
    if (factory == nullptr) return;

    config = factory->CreateCertificateProviderConfig(
        Json::FromObject(std::move(config_json)), args, errors);
  }
}

UniqueTypeName CertificateProviderStore::CertificateProviderWrapper::type()
    const {
  static UniqueTypeName::Factory kFactory("Wrapper");
  return kFactory.Create();
}

RefCountedPtr<grpc_tls_certificate_provider>
CertificateProviderStore::CreateOrGetCertificateProvider(
    absl::string_view key) {
  RefCountedPtr<CertificateProviderWrapper> result;
  MutexLock lock(&mu_);
  auto it = certificate_providers_map_.find(key);
  if (it == certificate_providers_map_.end()) {
    result = CreateCertificateProviderLocked(key);
    if (result != nullptr) {
      certificate_providers_map_.insert({result->key(), result.get()});
    }
  } else if (result = it->second->RefIfNonZero()
                          .TakeAsSubclass<CertificateProviderWrapper>();
             result == nullptr) {
    result = CreateCertificateProviderLocked(key);
    it->second = result.get();
  }
  return result;
}

RefCountedPtr<CertificateProviderStore::CertificateProviderWrapper>
CertificateProviderStore::CreateCertificateProviderLocked(
    absl::string_view key) {
  auto it = plugin_config_map_.find(std::string(key));
  if (it == plugin_config_map_.end()) return nullptr;
  const auto& [name, definition] = *it;
  CertificateProviderFactory* factory =
      CoreConfiguration::Get()
          .certificate_provider_registry()
          .LookupCertificateProviderFactory(definition.plugin_name);
  if (factory == nullptr) {

    LOG(ERROR) << "Certificate provider factory " << definition.plugin_name
               << " not found";
    return nullptr;
  }
  return MakeRefCounted<CertificateProviderWrapper>(
      factory->CreateCertificateProvider(definition.config), Ref(), name);
}

void CertificateProviderStore::ReleaseCertificateProvider(
    absl::string_view key, CertificateProviderWrapper* wrapper) {
  MutexLock lock(&mu_);
  auto it = certificate_providers_map_.find(key);
  if (it != certificate_providers_map_.end()) {
    if (it->second == wrapper) {
      certificate_providers_map_.erase(it);
    }
  }
}

}
