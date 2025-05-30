
// Copyright 2020 gRPC authors.

#ifndef GRPCPP_SECURITY_TLS_CERTIFICATE_PROVIDER_H
#define GRPCPP_SECURITY_TLS_CERTIFICATE_PROVIDER_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/support/config.h>

#include <memory>
#include <string>
#include <vector>

#include "absl/status/statusor.h"

namespace grpc {
namespace experimental {

class GRPCXX_DLL CertificateProviderInterface {
 public:
  virtual ~CertificateProviderInterface() = default;
  virtual grpc_tls_certificate_provider* c_provider() = 0;
};

struct GRPCXX_DLL IdentityKeyCertPair {
  std::string private_key;
  std::string certificate_chain;
};

class GRPCXX_DLL StaticDataCertificateProvider
    : public CertificateProviderInterface {
 public:
  StaticDataCertificateProvider(
      const std::string& root_certificate,
      const std::vector<IdentityKeyCertPair>& identity_key_cert_pairs);

  explicit StaticDataCertificateProvider(const std::string& root_certificate)
      : StaticDataCertificateProvider(root_certificate, {}) {}

  explicit StaticDataCertificateProvider(
      const std::vector<IdentityKeyCertPair>& identity_key_cert_pairs)
      : StaticDataCertificateProvider("", identity_key_cert_pairs) {}

  ~StaticDataCertificateProvider() override;

  grpc_tls_certificate_provider* c_provider() override { return c_provider_; }

  absl::Status ValidateCredentials() const;

 private:
  grpc_tls_certificate_provider* c_provider_ = nullptr;
};

class GRPCXX_DLL FileWatcherCertificateProvider final
    : public CertificateProviderInterface {
 public:

  FileWatcherCertificateProvider(const std::string& private_key_path,
                                 const std::string& identity_certificate_path,
                                 const std::string& root_cert_path,
                                 unsigned int refresh_interval_sec);

  FileWatcherCertificateProvider(const std::string& private_key_path,
                                 const std::string& identity_certificate_path,
                                 unsigned int refresh_interval_sec)
      : FileWatcherCertificateProvider(private_key_path,
                                       identity_certificate_path, "",
                                       refresh_interval_sec) {}

  FileWatcherCertificateProvider(const std::string& root_cert_path,
                                 unsigned int refresh_interval_sec)
      : FileWatcherCertificateProvider("", "", root_cert_path,
                                       refresh_interval_sec) {}

  ~FileWatcherCertificateProvider() override;

  grpc_tls_certificate_provider* c_provider() override { return c_provider_; }

  absl::Status ValidateCredentials() const;

 private:
  grpc_tls_certificate_provider* c_provider_ = nullptr;
};

}
}

#endif
