
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/certificate_provider_registry.h"

#include <grpc/support/port_platform.h>

#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"

namespace grpc_core {

void CertificateProviderRegistry::Builder::RegisterCertificateProviderFactory(
    std::unique_ptr<CertificateProviderFactory> factory) {
  absl::string_view name = factory->name();
  VLOG(2) << "registering certificate provider factory for \"" << name << "\"";
  CHECK(factories_.emplace(name, std::move(factory)).second);
}

CertificateProviderRegistry CertificateProviderRegistry::Builder::Build() {
  return CertificateProviderRegistry(std::move(factories_));
}

CertificateProviderFactory*
CertificateProviderRegistry::LookupCertificateProviderFactory(
    absl::string_view name) const {
  auto it = factories_.find(name);
  if (it == factories_.end()) return nullptr;
  return it->second.get();
}

}
