Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/tls/tls_security_connector.h"

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <memory>
#include <utility>
#include <vector>

#include "absl/functional/bind_front.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/tls/grpc_tls_certificate_verifier.h"
#include "src/core/credentials/transport/tls/grpc_tls_credentials_options.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/host_port.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {

namespace {

// Copies a string with given length and adds null terminator
char* CopyCoreString(char* src, size_t length) {
  char* target = static_cast<char*>(gpr_malloc(length + 1));
  memcpy(target, src, length);
  target[length] = '\0';
  return target;
}

// Initializes a verification request by extracting peer information from TSI peer
// and populating the verification request structure
void PendingVerifierRequestInit(
    const char* target_name, tsi_peer peer,
    grpc_tls_custom_verification_check_request* request) {
  CHECK_NE(request, nullptr);

  request->target_name = target_name;

  // Flags to track which properties we've found
  bool has_common_name = false;
  bool has_peer_cert = false;
  bool has_peer_cert_full_chain = false;
  bool has_verified_root_cert_subject = false;
  
  // Vectors to store different types of SANs (Subject Alternative Names)
  std::vector<char*> uri_names;
  std::vector<char*> dns_names;
  std::vector<char*> email_names;
  std::vector<char*> ip_names;

  // Iterate through all peer properties
  for (size_t i = 0; i < peer.property_count; ++i) {
    const tsi_peer_property* prop = &peer.properties[i];
    if (prop->name == nullptr) continue;
    
    // Check property type and copy the value accordingly
    if (strcmp(prop->name, TSI_X509_SUBJECT_COMMON_NAME_PEER_PROPERTY) == 0) {
      request->peer_info.common_name =
          CopyCoreString(prop->value.data, prop->value.length);
      has_common_name = true;
    } else if (strcmp(prop->name, TSI_X509_PEM_CERT_PROPERTY) == 0) {
      request->peer_info.peer_cert =
          CopyCoreString(prop->value.data, prop->value.length);
      has_peer_cert = true;
    } else if (strcmp(prop->name, TSI_X509_PEM_CERT_CHAIN_PROPERTY) == 0) {
      request->peer_info.peer_cert_full_chain =
          CopyCoreString(prop->value.data, prop->value.length);
      has_peer_cert_full_chain = true;
    } else if (strcmp(prop->name, TSI_X509_URI_PEER_PROPERTY) == 0) {
      char* uri = CopyCoreString(prop->value.data, prop->value.length);
      uri_names.emplace_back(uri);
    } else if (strcmp(prop->name, TSI_X509_DNS_PEER_PROPERTY) == 0) {
      char* dns = CopyCoreString(prop->value.data, prop->value.length);
      dns_names.emplace_back(dns);
    } else if (strcmp(prop->name, TSI_X509_EMAIL_PEER_PROPERTY) == 0) {
      char* email = CopyCoreString(prop->value.data, prop->value.length);
      email_names.emplace_back(email);
    } else if (strcmp(prop->name, TSI_X509_IP_PEER_PROPERTY) == 0) {
      char* ip = CopyCoreString(prop->value.data, prop->value.length);
      ip_names.emplace_back(ip);
    } else if (strcmp(prop->name,
                      TSI_X509_VERIFIED_ROOT_CERT_SUBECT_PEER_PROPERTY) == 0) {
      request->peer_info.verified_root_cert_subject =
          CopyCoreString(prop->value.data, prop->value.length);
      has_verified_root_cert_subject = true;
    }
  }

  // Set null for properties that weren't found
  if (!has_common_name) {
    request->peer_info.common_name = nullptr;
  }
  if (!has_peer_cert) {
    request->peer_info.peer_cert = nullptr;
  }
  if (!has_peer_cert_full_chain) {
    request->peer_info.peer_cert_full_chain = nullptr;
  }
  if (!has_verified_root_cert_subject) {
    request->peer_info.verified_root_cert_subject = nullptr;
  }

  // Populate SANs (Subject Alternative Names) in the request
  request->peer_info.san_names.uri_names_size = uri_names.size();
  if (!uri_names.empty()) {
    request->peer_info.san_names.uri_names =
        new char*[request->peer_info.san_names.uri_names_size];
    for (size_t i = 0; i < request->peer_info.san_names.uri_names_size; ++i) {
      request->peer_info.san_names.uri_names[i] = uri_names[i];
    }
  } else {
    request->peer_info.san_names.uri_names = nullptr;
  }

  request->peer_info.san_names.dns_names_size = dns_names.size();
  if (!dns_names.empty()) {
    request->peer_info.san_names.dns_names =
        new char*[request->peer_info.san_names.dns_names_size];
    for (size_t i = 0; i < request->peer_info.san_names.dns_names_size; ++i) {
      request->peer_info.san_names.dns_names[i] = dns_names[i];
    }
  } else {
    request->peer_info.san_names.dns_names = nullptr;
  }

  request->peer_info.san_names.email_names_size = email_names.size();
  if (!email_names.empty()) {
    request->peer_info.san_names.email_names =
        new char*[request->peer_info.san_names.email_names_size];
    for (size_t i = 0; i < request->peer_info.san_names.email_names_size; ++i) {
      request->peer_info.san_names.email_names[i] = email_names[i];
    }
  } else {
    request->peer_info.san_names.email_names = nullptr;
  }

  request->peer_info.san_names.ip_names_size = ip_names.size();
  if (!ip_names.empty()) {
    request->peer_info.san_names.ip_names =
        new char*[request->peer_info.san_names.ip_names_size];
    for (size_t i = 0; i < request->peer_info.san_names.ip_names_size; ++i) {
      request->peer_info.san_names.ip_names[i] = ip_names[i];
    }
  } else {
    request->peer_info.san_names.ip_names = nullptr;
  }
}

// Cleans up resources allocated for a verification request
void PendingVerifierRequestDestroy(
    grpc_tls_custom_verification_check_request* request) {
  CHECK_NE(request, nullptr);
  
  // Free all allocated strings and arrays
  if (request->peer_info.common_name != nullptr) {
    gpr_free(const_cast<char*>(request->peer_info.common_name));
  }
  
  // Free URI SANs
  if (request->peer_info.san_names.uri_names_size > 0) {
    for (size_t i = 0; i < request->peer_info.san_names.uri_names_size; ++i) {
      gpr_free(request->peer_info.san_names.uri_names[i]);
    }
    delete[] request->peer_info.san_names.uri_names;
  }
  
  // Free DNS SANs
  if (request->peer_info.san_names.dns_names_size > 0) {
    for (size_t i = 0; i < request->peer_info.san_names.dns_names_size; ++i) {
      gpr_free(request->peer_info.san_names.dns_names[i]);
    }
    delete[] request->peer_info.san_names.dns_names;
  }
  
  // Free Email SANs
  if (request->peer_info.san_names.email_names_size > 0) {
    for (size_t i = 0; i < request->peer_info.san_names.email_names_size; ++i) {
      gpr_free(request->peer_info.san_names.email_names[i]);
    }
    delete[] request->peer_info.san_names.email_names;
  }
  
  // Free IP SANs
  if (request->peer_info.san_names.ip_names_size > 0) {
    for (size_t i = 0; i < request->peer_info.san_names.ip_names_size; ++i) {
      gpr_free(request->peer_info.san_names.ip_names[i]);
    }
    delete[] request->peer_info.san_names.ip_names;
  }
  
  // Free other certificate-related strings
  if (request->peer_info.peer_cert != nullptr) {
    gpr_free(const_cast<char*>(request->peer_info.peer_cert));
  }
  if (request->peer_info.peer_cert_full_chain != nullptr) {
    gpr_free(const_cast<char*>(request->peer_info.peer_cert_full_chain));
  }
  if (request->peer_info.verified_root_cert_subject != nullptr) {
    gpr_free(const_cast<char*>(request->peer_info.verified_root_cert_subject));
  }
}

// Converts a list of PEM key-cert pairs to TSI format
tsi_ssl_pem_key_cert_pair* ConvertToTsiPemKeyCertPair(
    const PemKeyCertPairList& cert_pair_list) {
  tsi_ssl_pem_key_cert_pair* tsi_pairs = nullptr;
  size_t num_key_cert_pairs = cert_pair_list.size();
  if (num_key_cert_pairs > 0) {
    CHECK_NE(cert_pair_list.data(), nullptr);
    tsi_pairs = static_cast<tsi_ssl_pem_key_cert_pair*>(
        gpr_zalloc(num_key_cert_pairs * sizeof(tsi_ssl_pem_key_cert_pair)));
  }
  for (size_t i = 0; i < num_key_cert_pairs; i++) {
    CHECK(!cert_pair_list[i].private_key().empty());
    CHECK(!cert_pair_list[i].cert_chain().empty());
    tsi_pairs[i].cert_chain =
        gpr_strdup(cert_pair_list[i].cert_chain().c_str());
    tsi_pairs[i].private_key =
        gpr_strdup(cert_pair_list[i].private_key().c_str());
  }
  return tsi_pairs;
}

}  // namespace

// Creates a new TLS channel security connector
RefCountedPtr<grpc_channel_security_connector>
TlsChannelSecurityConnector::CreateTlsChannelSecurityConnector(
    RefCountedPtr<grpc_channel_credentials> channel_creds,
    RefCountedPtr<grpc_tls_credentials_options> options,
    RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* target_name, const char* overridden_target_name,
    tsi_ssl_session_cache* ssl_session_cache) {
  // Validate input parameters
  if (channel_creds == nullptr) {
    LOG(ERROR) << "channel_creds is nullptr in "
                  "TlsChannelSecurityConnectorCreate()";
    return nullptr;
  }
  if (options == nullptr) {
    LOG(ERROR) << "options is nullptr in "
                  "TlsChannelSecurityConnectorCreate()";
    return nullptr;
  }
  if (target_name == nullptr) {
    LOG(ERROR) << "target_name is nullptr in "
                  "TlsChannelSecurityConnectorCreate()";
    return nullptr;
  }
  return MakeRefCounted<TlsChannelSecurityConnector>(
      std::move(channel_creds), std::move(options),
      std::move(request_metadata_creds), target_name, overridden_target_name,
      ssl_session_cache);
}

// Constructor for TLS channel security connector
TlsChannelSecurityConnector::TlsChannelSecurityConnector(
    RefCountedPtr<grpc_channel_credentials> channel_creds,
    RefCountedPtr<grpc_tls_credentials_options> options,
    RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* target_name, const char* overridden_target_name,
    tsi_ssl_session_cache* ssl_session_cache)
    : grpc_channel_security_connector(GRPC_SSL_URL_SCHEME,
                                      std::move(channel_creds),
                                      std::move(request_metadata_creds)),
      options_(std::move(options)),
      overridden_target_name_(
          overridden_target_name == nullptr ? "" : overridden_target_name),
      ssl_session_cache_(ssl_session_cache) {
  // Initialize TLS session key logger if configured
  const std::string& tls_session_key_log_file_path =
      options_->tls_session_key_log_file_path();
  if (!tls_session_key_log_file_path.empty()) {
    tls_session_key_logger_ =
        tsi::TlsSessionKeyLoggerCache::Get(tls_session_key_log_file_path);
  }
  
  // Take reference to SSL session cache if provided
  if (ssl_session_cache_ != nullptr) {
    tsi_ssl_session_cache_ref(ssl_session_cache_);
  }
  
  // Extract host and port from target name
  absl::string_view host;
  absl::string_view port;
  SplitHostPort(target_name, &host, &port);
  target_name_ = std::string(host);

  // Set up certificate watcher
  auto watcher_ptr = std::make_unique<TlsChannelCertificateWatcher>(this);
  certificate_watcher_ = watcher_ptr.get();

  grpc_tls_certificate_distributor* distributor =
      options_->certificate_distributor();
  
  // Determine which certificates to watch based on options
  std::optional<std::string> watched_root_cert_name;
  if (options_->watch_root_cert()) {
    watched_root_cert_name = options_->root_cert_name();
  }
  std::optional<std::string> watched_identity_cert_name;
  if (options_->watch_identity_pair()) {
    watched_identity_cert_name = options_->identity_cert_name();
  }

  bool use_default_roots = !options_->watch_root_cert();
  if (use_default_roots && !options_->watch_identity_pair()) {
    // If not watching any certificates, trigger immediate update
    watcher_ptr->OnCertificatesChanged(std::nullopt, std::nullopt);
  } else {
    // Start watching for certificate updates
    distributor->WatchTlsCertificates(std::move(watcher_ptr),
                                      watched_root_cert_name,
                                      watched_identity_cert_name);
  }
}

// Destructor for TLS channel security connector
TlsChannelSecurityConnector::~TlsChannelSecurityConnector() {
  // Release SSL session cache reference
  if (ssl_session_cache_ != nullptr) {
    tsi_ssl_session_cache_unref(ssl_session_cache_);
  }

  // Stop watching for certificate updates
  grpc_tls_certificate_distributor* distributor =
      options_->certificate_distributor();
  if (distributor != nullptr) {
    distributor->CancelTlsCertificatesWatch(certificate_watcher_);
  }
  
  // Clean up handshaker factory
  if (client_handshaker_factory_ != nullptr) {
    tsi_ssl_client_handshaker_factory_unref(client_handshaker_factory_);
  }
}

// Adds handshakers to the handshake manager
void TlsChannelSecurityConnector::add_handshakers(
    const ChannelArgs& args, grpc_pollset_set* /*interested_parties*/,
    HandshakeManager* handshake_mgr) {
  MutexLock lock(&mu_);
  tsi_handshaker* tsi_hs = nullptr;
  if (client_handshaker_factory_ != nullptr) {
    // Create new handshaker using the factory
    tsi_result result = tsi_ssl_client_handshaker_factory_create_handshaker(
        client_handshaker_factory_,
        overridden_target_name_.empty() ? target_name_.c_str()
                                        : overridden_target_name_.c_str(),
        /*network_bio_buf_size=*/0,
        /*ssl_bio_buf_size=*/0,
        args.GetOwnedString(GRPC_ARG_TRANSPORT_PROTOCOLS), &tsi_hs);
    if (result != TSI_OK) {
      LOG(ERROR) << "Handshaker creation failed with error "
                 << tsi_result_to_string(result);
    }
  }

  // Add security handshaker to the manager
  handshake_mgr->Add(SecurityHandshakerCreate(tsi_hs, this, args));
}

// Verifies peer identity and properties
void TlsChannelSecurityConnector::check_peer(
    tsi_peer peer, grpc_endpoint* /*ep*/, const ChannelArgs& /*args*/,
    RefCountedPtr<grpc_auth_context>* auth_context,
    grpc_closure* on_peer_checked) {
  const char*