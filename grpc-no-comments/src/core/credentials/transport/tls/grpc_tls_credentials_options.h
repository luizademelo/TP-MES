
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CREDENTIALS_OPTIONS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_GRPC_TLS_CREDENTIALS_OPTIONS_H

#include <grpc/support/port_platform.h>

#include "absl/container/inlined_vector.h"

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>

#include "src/core/util/ref_counted.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_distributor.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_provider.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_verifier.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"

struct grpc_tls_credentials_options
    : public grpc_core::RefCounted<grpc_tls_credentials_options> {
 public:
  grpc_tls_credentials_options() = default;
  ~grpc_tls_credentials_options() override = default;

  grpc_ssl_client_certificate_request_type cert_request_type() const { return cert_request_type_; }
  bool verify_server_cert() const { return verify_server_cert_; }
  grpc_tls_version min_tls_version() const { return min_tls_version_; }
  grpc_tls_version max_tls_version() const { return max_tls_version_; }
  grpc_tls_certificate_verifier* certificate_verifier() {
    return certificate_verifier_.get();
  }
  bool check_call_host() const { return check_call_host_; }

  grpc_tls_certificate_distributor* certificate_distributor() {
    if (certificate_provider_ != nullptr) { return certificate_provider_->distributor().get(); }
    return nullptr;
  }
  bool watch_root_cert() const { return watch_root_cert_; }
  const std::string& root_cert_name() const { return root_cert_name_; }
  bool watch_identity_pair() const { return watch_identity_pair_; }
  const std::string& identity_cert_name() const { return identity_cert_name_; }
  const std::string& tls_session_key_log_file_path() const { return tls_session_key_log_file_path_; }
  const std::string& crl_directory() const { return crl_directory_; }

  std::shared_ptr<grpc_core::experimental::CrlProvider> crl_provider() const { return crl_provider_; }
  bool send_client_ca_list() const { return send_client_ca_list_; }

  void set_cert_request_type(grpc_ssl_client_certificate_request_type cert_request_type) { cert_request_type_ = cert_request_type; }
  void set_verify_server_cert(bool verify_server_cert) { verify_server_cert_ = verify_server_cert; }
  void set_min_tls_version(grpc_tls_version min_tls_version) { min_tls_version_ = min_tls_version; }
  void set_max_tls_version(grpc_tls_version max_tls_version) { max_tls_version_ = max_tls_version; }
  void set_certificate_verifier(grpc_core::RefCountedPtr<grpc_tls_certificate_verifier> certificate_verifier) { certificate_verifier_ = std::move(certificate_verifier); }
  void set_check_call_host(bool check_call_host) { check_call_host_ = check_call_host; }
  void set_certificate_provider(grpc_core::RefCountedPtr<grpc_tls_certificate_provider> certificate_provider) { certificate_provider_ = std::move(certificate_provider); }

  void set_watch_root_cert(bool watch_root_cert) { watch_root_cert_ = watch_root_cert; }

  void set_root_cert_name(std::string root_cert_name) { root_cert_name_ = std::move(root_cert_name); }

  void set_watch_identity_pair(bool watch_identity_pair) { watch_identity_pair_ = watch_identity_pair; }

  void set_identity_cert_name(std::string identity_cert_name) { identity_cert_name_ = std::move(identity_cert_name); }
  void set_tls_session_key_log_file_path(std::string tls_session_key_log_file_path) { tls_session_key_log_file_path_ = std::move(tls_session_key_log_file_path); }

  void set_crl_directory(std::string crl_directory) { crl_directory_ = std::move(crl_directory); }
  void set_crl_provider(std::shared_ptr<grpc_core::experimental::CrlProvider> crl_provider) { crl_provider_ = std::move(crl_provider); }
  void set_send_client_ca_list(bool send_client_ca_list) { send_client_ca_list_ = send_client_ca_list; }

  bool operator==(const grpc_tls_credentials_options& other) const {
    return cert_request_type_ == other.cert_request_type_ &&
      verify_server_cert_ == other.verify_server_cert_ &&
      min_tls_version_ == other.min_tls_version_ &&
      max_tls_version_ == other.max_tls_version_ &&
      (certificate_verifier_ == other.certificate_verifier_ || (certificate_verifier_ != nullptr && other.certificate_verifier_ != nullptr && certificate_verifier_->Compare(other.certificate_verifier_.get()) == 0)) &&
      check_call_host_ == other.check_call_host_ &&
      (certificate_provider_ == other.certificate_provider_ || (certificate_provider_ != nullptr && other.certificate_provider_ != nullptr && certificate_provider_->Compare(other.certificate_provider_.get()) == 0)) &&
      watch_root_cert_ == other.watch_root_cert_ &&
      root_cert_name_ == other.root_cert_name_ &&
      watch_identity_pair_ == other.watch_identity_pair_ &&
      identity_cert_name_ == other.identity_cert_name_ &&
      tls_session_key_log_file_path_ == other.tls_session_key_log_file_path_ &&
      crl_directory_ == other.crl_directory_ &&
      (crl_provider_ == other.crl_provider_) &&
      send_client_ca_list_ == other.send_client_ca_list_;
  }

  grpc_tls_credentials_options(grpc_tls_credentials_options& other) :
      cert_request_type_(other.cert_request_type_),
      verify_server_cert_(other.verify_server_cert_),
      min_tls_version_(other.min_tls_version_),
      max_tls_version_(other.max_tls_version_),
      certificate_verifier_(other.certificate_verifier_),
      check_call_host_(other.check_call_host_),
      certificate_provider_(other.certificate_provider_),
      watch_root_cert_(other.watch_root_cert_),
      root_cert_name_(other.root_cert_name_),
      watch_identity_pair_(other.watch_identity_pair_),
      identity_cert_name_(other.identity_cert_name_),
      tls_session_key_log_file_path_(other.tls_session_key_log_file_path_),
      crl_directory_(other.crl_directory_),
      crl_provider_(other.crl_provider_),
      send_client_ca_list_(other.send_client_ca_list_)  {}

 private:
  grpc_ssl_client_certificate_request_type cert_request_type_ = GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE;
  bool verify_server_cert_ = true;
  grpc_tls_version min_tls_version_ = grpc_tls_version::TLS1_2;
  grpc_tls_version max_tls_version_ = grpc_tls_version::TLS1_3;
  grpc_core::RefCountedPtr<grpc_tls_certificate_verifier> certificate_verifier_;
  bool check_call_host_ = true;
  grpc_core::RefCountedPtr<grpc_tls_certificate_provider> certificate_provider_;
  bool watch_root_cert_ = false;
  std::string root_cert_name_;
  bool watch_identity_pair_ = false;
  std::string identity_cert_name_;
  std::string tls_session_key_log_file_path_;
  std::string crl_directory_;
  std::shared_ptr<grpc_core::experimental::CrlProvider> crl_provider_;
  bool send_client_ca_list_ = false;
};

#endif
