
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_CERTIFICATE_PROVIDER_REGISTRY_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_CERTIFICATE_PROVIDER_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/certificate_provider_factory.h"

namespace grpc_core {

class CertificateProviderRegistry {
 private:
  using FactoryMap =
      std::map<absl::string_view, std::unique_ptr<CertificateProviderFactory>>;

 public:
  class Builder {
   public:

    void RegisterCertificateProviderFactory(
        std::unique_ptr<CertificateProviderFactory> factory);

    CertificateProviderRegistry Build();

   private:
    FactoryMap factories_;
  };

  CertificateProviderRegistry(const CertificateProviderRegistry&) = delete;
  CertificateProviderRegistry& operator=(const CertificateProviderRegistry&) =
      delete;
  CertificateProviderRegistry(CertificateProviderRegistry&&) = default;
  CertificateProviderRegistry& operator=(CertificateProviderRegistry&&) =
      default;

  CertificateProviderFactory* LookupCertificateProviderFactory(
      absl::string_view name) const;

 private:
  explicit CertificateProviderRegistry(FactoryMap factories)
      : factories_(std::move(factories)) {}

  FactoryMap factories_;
};

}

#endif
