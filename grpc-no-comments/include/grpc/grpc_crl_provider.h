
// Copyright 2023 gRPC authors.

#ifndef GRPC_GRPC_CRL_PROVIDER_H
#define GRPC_GRPC_CRL_PROVIDER_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {
namespace experimental {

class Crl {
 public:
  static absl::StatusOr<std::unique_ptr<Crl>> Parse(
      absl::string_view crl_string);
  virtual ~Crl() = default;
  virtual absl::string_view Issuer() = 0;
};

class CertificateInfo {
 public:
  virtual ~CertificateInfo() = default;
  virtual absl::string_view Issuer() const = 0;
  virtual absl::string_view AuthorityKeyIdentifier() const = 0;
};

class CrlProvider {
 public:
  virtual ~CrlProvider() = default;

  virtual std::shared_ptr<Crl> GetCrl(
      const CertificateInfo& certificate_info) = 0;
};

absl::StatusOr<std::shared_ptr<CrlProvider>> CreateStaticCrlProvider(
    absl::Span<const std::string> crls);

absl::StatusOr<std::shared_ptr<CrlProvider>> CreateDirectoryReloaderCrlProvider(
    absl::string_view directory, std::chrono::seconds refresh_duration,
    std::function<void(absl::Status)> reload_error_callback);

}
}

void grpc_tls_credentials_options_set_crl_provider(
    grpc_tls_credentials_options* options,
    std::shared_ptr<grpc_core::experimental::CrlProvider> provider);
#endif
