
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_SSL_SSL_SECURITY_CONNECTOR_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_SSL_SSL_SECURITY_CONNECTOR_H
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/util/ref_counted_ptr.h"

struct grpc_ssl_config {
  tsi_ssl_pem_key_cert_pair* pem_key_cert_pair;
  char* pem_root_certs;
  verify_peer_options verify_options;
  grpc_tls_version min_tls_version = grpc_tls_version::TLS1_2;
  grpc_tls_version max_tls_version = grpc_tls_version::TLS1_3;
};

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_ssl_channel_security_connector_create(
    grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const grpc_ssl_config* config, const char* target_name,
    const char* overridden_target_name,
    tsi_ssl_client_handshaker_factory* factory);

struct grpc_ssl_server_config {
  tsi_ssl_pem_key_cert_pair* pem_key_cert_pairs = nullptr;
  size_t num_key_cert_pairs = 0;
  char* pem_root_certs = nullptr;
  grpc_ssl_client_certificate_request_type client_certificate_request =
      GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE;
  grpc_tls_version min_tls_version = grpc_tls_version::TLS1_2;
  grpc_tls_version max_tls_version = grpc_tls_version::TLS1_3;
};

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_ssl_server_security_connector_create(
    grpc_core::RefCountedPtr<grpc_server_credentials> server_credentials,
    const grpc_core::ChannelArgs& args);

#endif
