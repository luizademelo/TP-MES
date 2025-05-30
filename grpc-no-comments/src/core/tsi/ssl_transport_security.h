
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_TRANSPORT_SECURITY_H
#define GRPC_SRC_CORE_TSI_SSL_TRANSPORT_SECURITY_H

#include <grpc/grpc_crl_provider.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <openssl/x509.h>

#include <memory>

#include "absl/strings/string_view.h"
#include "src/core/tsi/ssl/key_logging/ssl_key_logging.h"
#include "src/core/tsi/ssl_transport_security_utils.h"
#include "src/core/tsi/transport_security_interface.h"

#define TSI_X509_CERTIFICATE_TYPE "X509"

#define TSI_X509_SUBJECT_PEER_PROPERTY "x509_subject"
#define TSI_X509_SUBJECT_COMMON_NAME_PEER_PROPERTY "x509_subject_common_name"
#define TSI_X509_SUBJECT_ALTERNATIVE_NAME_PEER_PROPERTY \
  "x509_subject_alternative_name"
#define TSI_SSL_SESSION_REUSED_PEER_PROPERTY "ssl_session_reused"
#define TSI_X509_PEM_CERT_PROPERTY "x509_pem_cert"
#define TSI_X509_PEM_CERT_CHAIN_PROPERTY "x509_pem_cert_chain"
#define TSI_SSL_ALPN_SELECTED_PROTOCOL "ssl_alpn_selected_protocol"
#define TSI_X509_DNS_PEER_PROPERTY "x509_dns"
#define TSI_X509_URI_PEER_PROPERTY "x509_uri"
#define TSI_X509_EMAIL_PEER_PROPERTY "x509_email"
#define TSI_X509_IP_PEER_PROPERTY "x509_ip"
#define TSI_X509_VERIFIED_ROOT_CERT_SUBECT_PEER_PROPERTY \
  "x509_verified_root_cert_subject"

typedef struct tsi_ssl_root_certs_store tsi_ssl_root_certs_store;

tsi_ssl_root_certs_store* tsi_ssl_root_certs_store_create(
    const char* pem_roots);

void tsi_ssl_root_certs_store_destroy(tsi_ssl_root_certs_store* self);

typedef struct tsi_ssl_session_cache tsi_ssl_session_cache;

tsi_ssl_session_cache* tsi_ssl_session_cache_create_lru(size_t capacity);

void tsi_ssl_session_cache_ref(tsi_ssl_session_cache* cache);

void tsi_ssl_session_cache_unref(tsi_ssl_session_cache* cache);

static constexpr bool tsi_tls_session_key_logging_supported() {

#if OPENSSL_VERSION_NUMBER >= 0x10101000 && !defined(LIBRESSL_VERSION_NUMBER)
  return true;
#else
  return false;
#endif
}

typedef struct tsi_ssl_client_handshaker_factory
    tsi_ssl_client_handshaker_factory;

struct tsi_ssl_pem_key_cert_pair {

  const char* private_key;

  const char* cert_chain;
};

tsi_result tsi_create_ssl_client_handshaker_factory(
    const tsi_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const char* pem_root_certs, const char* cipher_suites,
    const char** alpn_protocols, uint16_t num_alpn_protocols,
    tsi_ssl_client_handshaker_factory** factory);

struct tsi_ssl_client_handshaker_options {

  const tsi_ssl_pem_key_cert_pair* pem_key_cert_pair;

  const char* pem_root_certs;

  const tsi_ssl_root_certs_store* root_store;

  const char* cipher_suites;

  const char** alpn_protocols;

  size_t num_alpn_protocols;

  tsi_ssl_session_cache* session_cache;

  tsi::TlsSessionKeyLoggerCache::TlsSessionKeyLogger* key_logger;

  bool skip_server_certificate_verification;

  tsi_tls_version min_tls_version;
  tsi_tls_version max_tls_version;

  const char* crl_directory;

  std::shared_ptr<grpc_core::experimental::CrlProvider> crl_provider;

  tsi_ssl_client_handshaker_options()
      : pem_key_cert_pair(nullptr),
        pem_root_certs(nullptr),
        root_store(nullptr),
        cipher_suites(nullptr),
        alpn_protocols(nullptr),
        num_alpn_protocols(0),
        session_cache(nullptr),
        key_logger(nullptr),
        skip_server_certificate_verification(false),
        min_tls_version(tsi_tls_version::TSI_TLS1_2),
        max_tls_version(tsi_tls_version::TSI_TLS1_3),
        crl_directory(nullptr) {}
};

tsi_result tsi_create_ssl_client_handshaker_factory_with_options(
    const tsi_ssl_client_handshaker_options* options,
    tsi_ssl_client_handshaker_factory** factory);

tsi_result tsi_ssl_client_handshaker_factory_create_handshaker(
    tsi_ssl_client_handshaker_factory* factory,
    const char* server_name_indication, size_t network_bio_buf_size,
    size_t ssl_bio_buf_size,
    std::optional<std::string> alpn_preferred_protocol_list,
    tsi_handshaker** handshaker);

tsi_ssl_client_handshaker_factory* tsi_ssl_client_handshaker_factory_ref(
    tsi_ssl_client_handshaker_factory* client_factory);

void tsi_ssl_client_handshaker_factory_unref(
    tsi_ssl_client_handshaker_factory* factory);

typedef struct tsi_ssl_server_handshaker_factory
    tsi_ssl_server_handshaker_factory;

tsi_result tsi_create_ssl_server_handshaker_factory(
    const tsi_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs, const char* pem_client_root_certs,
    int force_client_auth, const char* cipher_suites,
    const char** alpn_protocols, uint16_t num_alpn_protocols,
    tsi_ssl_server_handshaker_factory** factory);

tsi_result tsi_create_ssl_server_handshaker_factory_ex(
    const tsi_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs, const char* pem_client_root_certs,
    tsi_client_certificate_request_type client_certificate_request,
    const char* cipher_suites, const char** alpn_protocols,
    uint16_t num_alpn_protocols, tsi_ssl_server_handshaker_factory** factory);

struct tsi_ssl_server_handshaker_options {

  const tsi_ssl_pem_key_cert_pair* pem_key_cert_pairs;

  size_t num_key_cert_pairs;

  const char* pem_client_root_certs;

  tsi_client_certificate_request_type client_certificate_request;

  const char* cipher_suites;

  const char** alpn_protocols;

  uint16_t num_alpn_protocols;

  const char* session_ticket_key;

  size_t session_ticket_key_size;

  tsi_tls_version min_tls_version;
  tsi_tls_version max_tls_version;

  tsi::TlsSessionKeyLoggerCache::TlsSessionKeyLogger* key_logger;

  const char* crl_directory;

  std::shared_ptr<grpc_core::experimental::CrlProvider> crl_provider;

  bool send_client_ca_list;

  tsi_ssl_server_handshaker_options()
      : pem_key_cert_pairs(nullptr),
        num_key_cert_pairs(0),
        pem_client_root_certs(nullptr),
        client_certificate_request(TSI_DONT_REQUEST_CLIENT_CERTIFICATE),
        cipher_suites(nullptr),
        alpn_protocols(nullptr),
        num_alpn_protocols(0),
        session_ticket_key(nullptr),
        session_ticket_key_size(0),
        min_tls_version(tsi_tls_version::TSI_TLS1_2),
        max_tls_version(tsi_tls_version::TSI_TLS1_3),
        key_logger(nullptr),
        crl_directory(nullptr),
        send_client_ca_list(true) {}
};

tsi_result tsi_create_ssl_server_handshaker_factory_with_options(
    const tsi_ssl_server_handshaker_options* options,
    tsi_ssl_server_handshaker_factory** factory);

tsi_result tsi_ssl_server_handshaker_factory_create_handshaker(
    tsi_ssl_server_handshaker_factory* factory, size_t network_bio_buf_size,
    size_t ssl_bio_buf_size, tsi_handshaker** handshaker);

void tsi_ssl_server_handshaker_factory_unref(
    tsi_ssl_server_handshaker_factory* factory);

int tsi_ssl_peer_matches_name(const tsi_peer* peer, absl::string_view name);

typedef struct tsi_ssl_handshaker_factory tsi_ssl_handshaker_factory;

typedef void (*tsi_ssl_handshaker_factory_destructor)(
    tsi_ssl_handshaker_factory* factory);

struct tsi_ssl_handshaker_factory_vtable {
  tsi_ssl_handshaker_factory_destructor destroy;
};

const tsi_ssl_handshaker_factory_vtable* tsi_ssl_handshaker_factory_swap_vtable(
    tsi_ssl_handshaker_factory* factory,
    tsi_ssl_handshaker_factory_vtable* new_vtable);

tsi_result tsi_ssl_extract_x509_subject_names_from_pem_cert(
    const char* pem_cert, tsi_peer* peer);

tsi_result tsi_ssl_get_cert_chain_contents(STACK_OF(X509) * peer_chain,
                                           tsi_peer_property* property);

#endif
