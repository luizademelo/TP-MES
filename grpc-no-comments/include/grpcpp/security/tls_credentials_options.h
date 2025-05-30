
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_SECURITY_TLS_CREDENTIALS_OPTIONS_H
#define GRPCPP_SECURITY_TLS_CREDENTIALS_OPTIONS_H

#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/status.h>
#include <grpcpp/security/tls_certificate_provider.h>
#include <grpcpp/security/tls_certificate_verifier.h>
#include <grpcpp/security/tls_crl_provider.h>
#include <grpcpp/support/config.h>

#include <memory>
#include <vector>

namespace grpc {
namespace experimental {

class TlsCredentialsOptions {
 public:

  TlsCredentialsOptions();
  ~TlsCredentialsOptions();

  TlsCredentialsOptions(const TlsCredentialsOptions& other);
  TlsCredentialsOptions& operator=(const TlsCredentialsOptions& other) = delete;

  void set_certificate_provider(
      std::shared_ptr<CertificateProviderInterface> certificate_provider);

  void watch_root_certs();

  void set_root_cert_name(const std::string& root_cert_name);

  void watch_identity_key_cert_pairs();

  void set_identity_cert_name(const std::string& identity_cert_name);

  void set_tls_session_key_log_file_path(
      const std::string& tls_session_key_log_file_path);

  void set_certificate_verifier(
      std::shared_ptr<CertificateVerifier> certificate_verifier);

  void set_check_call_host(bool check_call_host);

  void set_crl_directory(const std::string& path);

  void set_crl_provider(std::shared_ptr<CrlProvider> crl_provider);

  void set_min_tls_version(grpc_tls_version tls_version);

  void set_max_tls_version(grpc_tls_version tls_version);

  grpc_tls_credentials_options* c_credentials_options() const;

 protected:

  grpc_tls_credentials_options* mutable_c_credentials_options() {
    return c_credentials_options_;
  }

 private:
  std::shared_ptr<CertificateProviderInterface> certificate_provider_;
  std::shared_ptr<CertificateVerifier> certificate_verifier_;
  grpc_tls_credentials_options* c_credentials_options_ = nullptr;
};

class TlsChannelCredentialsOptions final : public TlsCredentialsOptions {
 public:

  void set_verify_server_certs(bool verify_server_certs);

 private:
};

class TlsServerCredentialsOptions final : public TlsCredentialsOptions {
 public:

  explicit TlsServerCredentialsOptions(
      std::shared_ptr<CertificateProviderInterface> certificate_provider)
      : TlsCredentialsOptions() {
    set_certificate_provider(certificate_provider);
  }

  void set_cert_request_type(
      grpc_ssl_client_certificate_request_type cert_request_type);

  void set_send_client_ca_list(bool send_client_ca_list);

 private:
};

}
}

#endif
