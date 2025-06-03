Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Includes necessary headers for SSL/TLS functionality and core utilities
#include "src/core/tsi/ssl_transport_security_utils.h"

#include <grpc/support/port_platform.h>
#include <openssl/bio.h>
#include <openssl/crypto.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "src/core/tsi/transport_security_interface.h"

namespace grpc_core {

// Returns a string representation of an SSL error code
const char* SslErrorString(int error) {
  switch (error) {
    case SSL_ERROR_NONE:
      return "SSL_ERROR_NONE";
    case SSL_ERROR_ZERO_RETURN:
      return "SSL_ERROR_ZERO_RETURN";
    case SSL_ERROR_WANT_READ:
      return "SSL_ERROR_WANT_READ";
    case SSL_ERROR_WANT_WRITE:
      return "SSL_ERROR_WANT_WRITE";
    case SSL_ERROR_WANT_CONNECT:
      return "SSL_ERROR_WANT_CONNECT";
    case SSL_ERROR_WANT_ACCEPT:
      return "SSL_ERROR_WANT_ACCEPT";
    case SSL_ERROR_WANT_X509_LOOKUP:
      return "SSL_ERROR_WANT_X509_LOOKUP";
    case SSL_ERROR_SYSCALL:
      return "SSL_ERROR_SYSCALL";
    case SSL_ERROR_SSL:
      return "SSL_ERROR_SSL";
    default:
      return "Unknown error";
  }
}

// Logs the current SSL error stack to ERROR level
void LogSslErrorStack(void) {
  unsigned long err;
  while ((err = ERR_get_error()) != 0) {
    char details[256];
    ERR_error_string_n(static_cast<uint32_t>(err), details, sizeof(details));
    LOG(ERROR) << details;
  }
}

// Performs SSL write operation and handles potential errors
tsi_result DoSslWrite(SSL* ssl, unsigned char* unprotected_bytes,
                      size_t unprotected_bytes_size) {
  CHECK_LE(unprotected_bytes_size, static_cast<size_t>(INT_MAX));
  ERR_clear_error();
  int ssl_write_result = SSL_write(ssl, unprotected_bytes,
                                   static_cast<int>(unprotected_bytes_size));
  if (ssl_write_result < 0) {
    ssl_write_result = SSL_get_error(ssl, ssl_write_result);
    if (ssl_write_result == SSL_ERROR_WANT_READ) {
      LOG(ERROR)
          << "Peer tried to renegotiate SSL connection. This is unsupported.";
      return TSI_UNIMPLEMENTED;
    } else {
      LOG(ERROR) << "SSL_write failed with error "
                 << SslErrorString(ssl_write_result);
      return TSI_INTERNAL_ERROR;
    }
  }
  return TSI_OK;
}

// Performs SSL read operation and handles potential errors
tsi_result DoSslRead(SSL* ssl, unsigned char* unprotected_bytes,
                     size_t* unprotected_bytes_size) {
  CHECK_LE(*unprotected_bytes_size, static_cast<size_t>(INT_MAX));
  ERR_clear_error();
  int read_from_ssl = SSL_read(ssl, unprotected_bytes,
                               static_cast<int>(*unprotected_bytes_size));
  if (read_from_ssl <= 0) {
    read_from_ssl = SSL_get_error(ssl, read_from_ssl);
    switch (read_from_ssl) {
      case SSL_ERROR_ZERO_RETURN:
      case SSL_ERROR_WANT_READ:
        *unprotected_bytes_size = 0;
        return TSI_OK;
      case SSL_ERROR_WANT_WRITE:
        LOG(ERROR)
            << "Peer tried to renegotiate SSL connection. This is unsupported.";
        return TSI_UNIMPLEMENTED;
      case SSL_ERROR_SSL:
        LOG(ERROR) << "Corruption detected.";
        LogSslErrorStack();
        return TSI_DATA_CORRUPTED;
      default:
        LOG(ERROR) << "SSL_read failed with error "
                   << SslErrorString(read_from_ssl);
        return TSI_PROTOCOL_FAILURE;
    }
  }
  *unprotected_bytes_size = static_cast<size_t>(read_from_ssl);
  return TSI_OK;
}

// Protects data using SSL encryption and handles buffering
tsi_result SslProtectorProtect(const unsigned char* unprotected_bytes,
                               const size_t buffer_size, size_t& buffer_offset,
                               unsigned char* buffer, SSL* ssl, BIO* network_io,
                               size_t* unprotected_bytes_size,
                               unsigned char* protected_output_frames,
                               size_t* protected_output_frames_size) {
  int read_from_ssl;
  size_t available;
  tsi_result result = TSI_OK;

  // First check if there's pending data in the BIO
  int pending_in_ssl = static_cast<int>(BIO_pending(network_io));
  if (pending_in_ssl > 0) {
    *unprotected_bytes_size = 0;
    CHECK_LE(*protected_output_frames_size, static_cast<size_t>(INT_MAX));
    read_from_ssl = BIO_read(network_io, protected_output_frames,
                             static_cast<int>(*protected_output_frames_size));
    if (read_from_ssl < 0) {
      LOG(ERROR) << "Could not read from BIO even though some data is pending";
      return TSI_INTERNAL_ERROR;
    }
    *protected_output_frames_size = static_cast<size_t>(read_from_ssl);
    return TSI_OK;
  }

  // Buffer the data if there's space
  available = buffer_size - buffer_offset;
  if (available > *unprotected_bytes_size) {
    memcpy(buffer + buffer_offset, unprotected_bytes, *unprotected_bytes_size);
    buffer_offset += *unprotected_bytes_size;
    *protected_output_frames_size = 0;
    return TSI_OK;
  }

  // Buffer is full, perform SSL write
  memcpy(buffer + buffer_offset, unprotected_bytes, available);
  result = DoSslWrite(ssl, buffer, buffer_size);
  if (result != TSI_OK) return result;

  // Read the encrypted output
  CHECK_LE(*protected_output_frames_size, static_cast<size_t>(INT_MAX));
  read_from_ssl = BIO_read(network_io, protected_output_frames,
                           static_cast<int>(*protected_output_frames_size));
  if (read_from_ssl < 0) {
    LOG(ERROR) << "Could not read from BIO after SSL_write.";
    return TSI_INTERNAL_ERROR;
  }
  *protected_output_frames_size = static_cast<size_t>(read_from_ssl);
  *unprotected_bytes_size = available;
  buffer_offset = 0;
  return TSI_OK;
}

// Flushes any remaining protected data in the buffer
tsi_result SslProtectorProtectFlush(size_t& buffer_offset,
                                    unsigned char* buffer, SSL* ssl,
                                    BIO* network_io,
                                    unsigned char* protected_output_frames,
                                    size_t* protected_output_frames_size,
                                    size_t* still_pending_size) {
  tsi_result result = TSI_OK;
  int read_from_ssl = 0;
  int pending;

  // Write any remaining buffered data
  if (buffer_offset != 0) {
    result = DoSslWrite(ssl, buffer, buffer_offset);
    if (result != TSI_OK) return result;
    buffer_offset = 0;
  }

  // Check for pending data in BIO
  pending = static_cast<int>(BIO_pending(network_io));
  CHECK_GE(pending, 0);
  *still_pending_size = static_cast<size_t>(pending);
  if (*still_pending_size == 0) return TSI_OK;

  // Read the encrypted output
  CHECK_LE(*protected_output_frames_size, static_cast<size_t>(INT_MAX));
  read_from_ssl = BIO_read(network_io, protected_output_frames,
                           static_cast<int>(*protected_output_frames_size));
  if (read_from_ssl <= 0) {
    LOG(ERROR) << "Could not read from BIO after SSL_write.";
    return TSI_INTERNAL_ERROR;
  }
  *protected_output_frames_size = static_cast<size_t>(read_from_ssl);
  pending = static_cast<int>(BIO_pending(network_io));
  CHECK_GE(pending, 0);
  *still_pending_size = static_cast<size_t>(pending);
  return TSI_OK;
}

// Unprotects (decrypts) SSL-protected data
tsi_result SslProtectorUnprotect(const unsigned char* protected_frames_bytes,
                                 SSL* ssl, BIO* network_io,
                                 size_t* protected_frames_bytes_size,
                                 unsigned char* unprotected_bytes,
                                 size_t* unprotected_bytes_size) {
  tsi_result result = TSI_OK;
  int written_into_ssl = 0;
  size_t output_bytes_size = *unprotected_bytes_size;
  size_t output_bytes_offset = 0;

  // First try to read decrypted data
  result = DoSslRead(ssl, unprotected_bytes, unprotected_bytes_size);
  if (result != TSI_OK) return result;
  if (*unprotected_bytes_size == output_bytes_size) {
    // Output buffer full, no more data to process
    *protected_frames_bytes_size = 0;
    return TSI_OK;
  }
  output_bytes_offset = *unprotected_bytes_size;
  unprotected_bytes += output_bytes_offset;
  *unprotected_bytes_size = output_bytes_size - output_bytes_offset;

  // Write encrypted data to SSL for decryption
  CHECK_LE(*protected_frames_bytes_size, static_cast<size_t>(INT_MAX));
  written_into_ssl = BIO_write(network_io, protected_frames_bytes,
                               static_cast<int>(*protected_frames_bytes_size));
  if (written_into_ssl < 0) {
    LOG(ERROR) << "Sending protected frame to ssl failed with "
               << written_into_ssl;
    return TSI_INTERNAL_ERROR;
  }
  *protected_frames_bytes_size = static_cast<size_t>(written_into_ssl);

  // Try to read more decrypted data
  result = DoSslRead(ssl, unprotected_bytes, unprotected_bytes_size);
  if (result == TSI_OK) {
    // Combine with previously read data
    *unprotected_bytes_size += output_bytes_offset;
  }
  return result;
}

// Verifies the signature of a CRL using the issuer's public key
bool VerifyCrlSignature(X509_CRL* crl, X509* issuer) {
  if (issuer == nullptr || crl == nullptr) {
    return false;
  }
  EVP_PKEY* ikey = X509_get_pubkey(issuer);
  if (ikey == nullptr) {
    VLOG(2) << "Could not get public key from certificate.";
    EVP_PKEY_free(ikey);
    return false;
  }
  int ret = X509_CRL_verify(crl, ikey);
  if (ret < 0) {
    VLOG(2) << "There was an unexpected problem checking the CRL signature.";
  } else if (ret == 0) {
    VLOG(2) << "CRL failed verification.";
  }
  EVP_PKEY_free(ikey);
  return ret == 1;
}

// Checks if the issuer names in a certificate and CRL match
bool VerifyCrlCertIssuerNamesMatch(X509_CRL* crl, X509* cert) {
  if (cert == nullptr || crl == nullptr) {
    return false;
  }
  X509_NAME* cert_issuer_name = X509_get_issuer_name(cert);
  if (cert == nullptr) {
    return false;
  }
  X509_NAME* crl_issuer_name = X509_CRL_get_issuer(crl);
  if (crl_issuer_name == nullptr) {
    return false;
  }
  return X509_NAME_cmp(cert_issuer_name, crl_issuer_name) == 0;
}

// Checks if a certificate has the CRL signing key usage bit set
bool HasCrlSignBit(X509* cert) {
  if (cert == nullptr) {
    return false;
  }

#if OPENSSL_VERSION_NUMBER < 0x10100000
  // Legacy OpenSSL version handling
  X509_check_ca(cert);
  if (!(cert->ex_flags & EXFLAG_KUSAGE)) {
    return true;
  }
  return (cert->ex_kusage & KU_CRL_SIGN) != 0;
#else
  // Modern OpenSSL version handling
  return (X509_get_key_usage(cert) & KU_CRL_SIGN) != 0;
#endif
}

// Extracts the issuer name from a certificate as a string
absl::StatusOr<std::string> IssuerFromCert(X509* cert) {
  if (cert == nullptr) {
    return absl::InvalidArgumentError("cert cannot be null");
  }
  X509_NAME* issuer = X509_get_issuer_name(cert);
  unsigned char* buf = nullptr;
  int len = i2d_X509_NAME(issuer, &buf);
  if (len < 0 || buf == nullptr) {
    return absl::InvalidArgumentError("could not read issuer name from cert");
  }
  std::string ret(reinterpret_cast<char const*>(buf), len);
  OPENSSL_free(buf);
  return ret;
}

// Extracts the Authority Key Identifier (AKID) from a certificate
absl::StatusOr<std::string> AkidFromCertificate(X509* cert) {
  if (cert == nullptr) {
    return absl::InvalidArgumentError("cert cannot be null.");
  }
  ASN1_OCTET_STRING* akid = nullptr;
  int j = X509_get_ext_by_NID(cert, NID_authority_key_identifier, -1);

  if (j >= 0) {
    if (X509_get_ext_by_NID(cert, NID_authority_key_identifier, j) != -1) {
      return absl::InvalidArgumentError("Could not get AKID from certificate.");
    }
    akid = X509_EXTENSION_get_data(X509_get_ext(cert, j));
  } else {
    return absl::InvalidArgumentError("Could not get AKID from certificate.");
  }
  unsigned char* buf = nullptr;
  int len = i2d_ASN1_OCTET_STRING(akid, &buf);
  if (len <= 0) {
    return absl::InvalidArgumentError("Could not get AKID from certificate.");
  }
  std::string ret(reinterpret_cast<char const*>(buf), len);
  OPENSSL_free(buf);
  return ret;
}

// Extracts the Authority Key Identifier (AKID) from a CRL
absl::StatusOr<std::string> AkidFromCrl(X509_CRL* crl) {
  if (crl == nullptr) {
    return absl::InvalidArgumentError("Could not get AKID from crl.");
  }
  ASN1_OCTET_STRING* akid = nullptr;
  int j = X509_CRL_get_ext_by_NID(crl, NID_authority_key_identifier, -1);

  if (j >= 0) {
    if (X509_CRL_get_ext_by_NID(crl, NID_authority_key_identifier, j) != -1) {
      return absl::InvalidArgumentError("Could not get AKID from crl.");
    }
    akid = X509_EXTENSION_get_data(X509_CRL_get_ext(crl, j));
  } else {
    return absl::InvalidArgumentError("Could not get AKID from crl.");
  }
  unsigned char* buf = nullptr;
  int len = i2d_ASN1_OCTET_STRING(akid, &buf);
  if (len <= 0) {
    return absl::InvalidArgumentError("Could not get AKID from crl.");
  }
  std::string ret(reinterpret_cast<char const*>(buf), len);
  OPENSSL_free(buf);
  return ret;
}

// Parses a PEM-encoded certificate chain into X509 objects
absl::StatusOr<std::vector<X509*>> ParsePemCertificateChain(
    absl::string_view cert_chain_pem) {
  if (cert_chain_pem.empty()) {
    return absl::InvalidArgumentError("Cert chain PEM is empty.");
  }
  BIO* in = BIO_new_mem_buf(cert_chain_pem.data(), cert_chain_pem.size());
  if (in == nullptr) {
    return absl::InternalError("BIO_new_mem_buf failed.");
  }
  std::vector<X509*> certs;
  while (X509* cert = PEM_read_bio_X509(in, nullptr, nullptr,
                                        nullptr)) {
    certs.push_back(cert);
  }

  // Check if the error was just EOF (expected) or something else
  const int last_error = ERR_peek_last_error();
  if (ERR_GET_LIB(last_error) != ERR_LIB_PEM ||
      ERR_GET_REASON(last_error) != PEM_R_NO_START_LINE) {
    for (X509* cert : certs) {
      X509_free(cert);
    }
    BIO_free(in);
    return absl::FailedPreconditionError("Invalid PEM.");
  }
  ERR_clear_error();
  BIO_free(in);
  if (certs.empty()) {
    return absl::NotFoundError("No certificates found.");
  }
  return certs;
}

// Parses a PEM-encoded private key into an EVP_PKEY object
absl::StatusOr<EVP_PKEY*> ParsePemPrivateKey(
    absl::string_view private_key_pem) {
  BIO* in = BIO_new_mem_buf(private_key_pem.data(), private_key_pem.size());
  if (in == nullptr) {
    return absl::InvalidArgumentError("Private key PEM is empty.");
  }
  EVP_PKEY* pkey =
      PEM_read_bio_PrivateKey(in, nullptr, nullptr, nullptr);
  BIO_free(in);
  if (pkey ==