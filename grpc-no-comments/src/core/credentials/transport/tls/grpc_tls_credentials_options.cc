
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/tls/grpc_tls_credentials_options.h"

#include <grpc/grpc_crl_provider.h>
#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/util/debug_location.h"

grpc_tls_credentials_options* grpc_tls_credentials_options_create() {
  grpc_core::ExecCtx exec_ctx;
  return new grpc_tls_credentials_options();
}

grpc_tls_credentials_options* grpc_tls_credentials_options_copy(
    grpc_tls_credentials_options* options) {
  CHECK_NE(options, nullptr);
  return new grpc_tls_credentials_options(*options);
}

void grpc_tls_credentials_options_destroy(
    grpc_tls_credentials_options* options) {
  delete options;
}

void grpc_tls_credentials_options_set_cert_request_type(
    grpc_tls_credentials_options* options,
    grpc_ssl_client_certificate_request_type type) {
  CHECK_NE(options, nullptr);
  options->set_cert_request_type(type);
}

void grpc_tls_credentials_options_set_verify_server_cert(
    grpc_tls_credentials_options* options, int verify_server_cert) {
  CHECK_NE(options, nullptr);
  options->set_verify_server_cert(verify_server_cert);
}

void grpc_tls_credentials_options_set_certificate_provider(
    grpc_tls_credentials_options* options,
    grpc_tls_certificate_provider* provider) {
  CHECK_NE(options, nullptr);
  CHECK_NE(provider, nullptr);
  grpc_core::ExecCtx exec_ctx;
  options->set_certificate_provider(
      provider->Ref(DEBUG_LOCATION, "set_certificate_provider"));
}

void grpc_tls_credentials_options_watch_root_certs(
    grpc_tls_credentials_options* options) {
  CHECK_NE(options, nullptr);
  options->set_watch_root_cert(true);
}

void grpc_tls_credentials_options_set_root_cert_name(
    grpc_tls_credentials_options* options, const char* root_cert_name) {
  CHECK_NE(options, nullptr);
  options->set_root_cert_name(root_cert_name);
}

void grpc_tls_credentials_options_watch_identity_key_cert_pairs(
    grpc_tls_credentials_options* options) {
  CHECK_NE(options, nullptr);
  options->set_watch_identity_pair(true);
}

void grpc_tls_credentials_options_set_identity_cert_name(
    grpc_tls_credentials_options* options, const char* identity_cert_name) {
  CHECK_NE(options, nullptr);
  options->set_identity_cert_name(identity_cert_name);
}

void grpc_tls_credentials_options_set_certificate_verifier(
    grpc_tls_credentials_options* options,
    grpc_tls_certificate_verifier* verifier) {
  CHECK_NE(options, nullptr);
  CHECK_NE(verifier, nullptr);
  options->set_certificate_verifier(verifier->Ref());
}

void grpc_tls_credentials_options_set_crl_directory(
    grpc_tls_credentials_options* options, const char* crl_directory) {
  CHECK_NE(options, nullptr);
  options->set_crl_directory(crl_directory);
}

void grpc_tls_credentials_options_set_check_call_host(
    grpc_tls_credentials_options* options, int check_call_host) {
  CHECK_NE(options, nullptr);
  options->set_check_call_host(check_call_host);
}

void grpc_tls_credentials_options_set_tls_session_key_log_file_path(
    grpc_tls_credentials_options* options, const char* path) {
  if (!tsi_tls_session_key_logging_supported() || options == nullptr) {
    return;
  }
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_tls_credentials_options_set_tls_session_key_log_config(options="
      << options << ")";

  if (path != nullptr) {
    VLOG(2) << "Enabling TLS session key logging with keys stored at: " << path;
  } else {
    VLOG(2) << "Disabling TLS session key logging";
  }
  options->set_tls_session_key_log_file_path(path != nullptr ? path : "");
}

void grpc_tls_credentials_options_set_send_client_ca_list(
    grpc_tls_credentials_options* options, bool send_client_ca_list) {
  if (options == nullptr) {
    return;
  }
  options->set_send_client_ca_list(send_client_ca_list);
}

void grpc_tls_credentials_options_set_crl_provider(
    grpc_tls_credentials_options* options,
    std::shared_ptr<grpc_core::experimental::CrlProvider> provider) {
  CHECK_NE(options, nullptr);
  options->set_crl_provider(provider);
}

void grpc_tls_credentials_options_set_min_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version min_tls_version) {
  CHECK_NE(options, nullptr);
  options->set_min_tls_version(min_tls_version);
}

void grpc_tls_credentials_options_set_max_tls_version(
    grpc_tls_credentials_options* options, grpc_tls_version max_tls_version) {
  CHECK_NE(options, nullptr);
  options->set_max_tls_version(max_tls_version);
}
