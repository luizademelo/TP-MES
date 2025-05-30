
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_SSL_TRANSPORT_SECURITY_UTILS_H
#define GRPC_SRC_CORE_TSI_SSL_TRANSPORT_SECURITY_UTILS_H

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/tsi/ssl/key_logging/ssl_key_logging.h"
#include "src/core/tsi/transport_security_interface.h"

namespace grpc_core {

const char* SslErrorString(int error);

void LogSslErrorStack(void);

tsi_result DoSslWrite(SSL* ssl, unsigned char* unprotected_bytes,
                      size_t unprotected_bytes_size);

tsi_result DoSslRead(SSL* ssl, unsigned char* unprotected_bytes,
                     size_t* unprotected_bytes_size);

tsi_result SslProtectorProtect(const unsigned char* unprotected_bytes,
                               const size_t buffer_size, size_t& buffer_offset,
                               unsigned char* buffer, SSL* ssl, BIO* network_io,
                               std::size_t* unprotected_bytes_size,
                               unsigned char* protected_output_frames,
                               size_t* protected_output_frames_size);

tsi_result SslProtectorProtectFlush(size_t& buffer_offset,
                                    unsigned char* buffer, SSL* ssl,
                                    BIO* network_io,
                                    unsigned char* protected_output_frames,
                                    size_t* protected_output_frames_size,
                                    size_t* still_pending_size);

tsi_result SslProtectorUnprotect(const unsigned char* protected_frames_bytes,
                                 SSL* ssl, BIO* network_io,
                                 size_t* protected_frames_bytes_size,
                                 unsigned char* unprotected_bytes,
                                 size_t* unprotected_bytes_size);

bool VerifyCrlSignature(X509_CRL* crl, X509* issuer);

bool VerifyCrlCertIssuerNamesMatch(X509_CRL* crl, X509* cert);

bool HasCrlSignBit(X509* cert);

absl::StatusOr<std::string> IssuerFromCert(X509* cert);

absl::StatusOr<std::string> AkidFromCertificate(X509* cert);

absl::StatusOr<std::string> AkidFromCrl(X509_CRL* crl);

absl::StatusOr<std::vector<X509*>> ParsePemCertificateChain(
    absl::string_view cert_chain_pem);

absl::StatusOr<EVP_PKEY*> ParsePemPrivateKey(absl::string_view private_key_pem);
}

#endif
