Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Includes necessary headers for SSL security connector implementation
#include "src/core/credentials/transport/ssl/ssl_security_connector.h"

#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <stdint.h>
#include <string.h>

#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/ssl/ssl_credentials.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/host_port.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace {

// Helper function to verify peer identity and certificate
// Parameters:
//   peer_name: The expected peer name to verify against
//   peer: The peer's certificate information
//   auth_context: Output parameter for authentication context
// Returns:
//   grpc_error_handle indicating success or failure
grpc_error_handle ssl_check_peer(
    const char* peer_name, const tsi_peer* peer,
    grpc_core::RefCountedPtr<grpc_auth_context>* auth_context) {
  // First check ALPN (Application-Layer Protocol Negotiation)
  grpc_error_handle error = grpc_ssl_check_alpn(peer);
  if (!error.ok()) {
    return error;
  }

  // Verify host name matches certificate name if peer_name is provided
  if (peer_name != nullptr && !grpc_ssl_host_matches_name(peer, peer_name)) {
    return GRPC_ERROR_CREATE(
        absl::StrCat("Peer name ", peer_name, " is not in peer certificate"));
  }
  // Create auth context from peer certificate
  *auth_context =
      grpc_ssl_peer_to_auth_context(peer, GRPC_SSL_TRANSPORT_SECURITY_TYPE);
  return absl::OkStatus();
}

// SSL channel security connector implementation
class grpc_ssl_channel_security_connector final
    : public grpc_channel_security_connector {
 public:
  // Constructor for SSL channel security connector
  // Parameters:
  //   channel_creds: Channel credentials
  //   request_metadata_creds: Call credentials
  //   config: SSL configuration
  //   target_name: Original target name
  //   overridden_target_name: Overridden target name (if any)
  //   client_handshaker_factory: Factory for creating client handshakers
  grpc_ssl_channel_security_connector(
      grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
      grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const grpc_ssl_config* config, const char* target_name,
      const char* overridden_target_name,
      tsi_ssl_client_handshaker_factory* client_handshaker_factory)
      : grpc_channel_security_connector(GRPC_SSL_URL_SCHEME,
                                        std::move(channel_creds),
                                        std::move(request_metadata_creds)),
        client_handshaker_factory_(client_handshaker_factory),
        overridden_target_name_(
            overridden_target_name == nullptr ? "" : overridden_target_name),
        verify_options_(&config->verify_options) {
    // Extract host from target name (strip port if present)
    absl::string_view host;
    absl::string_view port;
    grpc_core::SplitHostPort(target_name, &host, &port);
    target_name_ = std::string(host);
  }

  ~grpc_ssl_channel_security_connector() override {
    tsi_ssl_client_handshaker_factory_unref(client_handshaker_factory_);
  }

  // Adds SSL handshakers to the handshake manager
  void add_handshakers(const grpc_core::ChannelArgs& args,
                       grpc_pollset_set* ,
                       grpc_core::HandshakeManager* handshake_mgr) override {
    // Create TSI handshaker
    tsi_handshaker* tsi_hs = nullptr;
    tsi_result result = tsi_ssl_client_handshaker_factory_create_handshaker(
        client_handshaker_factory_,
        overridden_target_name_.empty() ? target_name_.c_str()
                                        : overridden_target_name_.c_str(),
        0,
        0,
        args.GetOwnedString(GRPC_ARG_TRANSPORT_PROTOCOLS), &tsi_hs);
    if (result != TSI_OK) {
      LOG(ERROR) << "Handshaker creation failed with error "
                 << tsi_result_to_string(result);
      return;
    }

    // Add security handshaker to the manager
    handshake_mgr->Add(grpc_core::SecurityHandshakerCreate(tsi_hs, this, args));
  }

  // Verifies peer identity and certificate
  void check_peer(tsi_peer peer, grpc_endpoint* ,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    // Determine which target name to use for verification
    const char* target_name = overridden_target_name_.empty()
                                  ? target_name_.c_str()
                                  : overridden_target_name_.c_str();
    // Perform basic SSL peer verification
    grpc_error_handle error = ssl_check_peer(target_name, &peer, auth_context);
    
    // If verification succeeded and there's a custom verification callback
    if (error.ok() && verify_options_->verify_peer_callback != nullptr) {
      // Get peer's PEM certificate
      const tsi_peer_property* p =
          tsi_peer_get_property_by_name(&peer, TSI_X509_PEM_CERT_PROPERTY);
      if (p == nullptr) {
        error =
            GRPC_ERROR_CREATE("Cannot check peer: missing pem cert property.");
      } else {
        // Copy certificate for callback
        char* peer_pem = static_cast<char*>(gpr_malloc(p->value.length + 1));
        memcpy(peer_pem, p->value.data, p->value.length);
        peer_pem[p->value.length] = '\0';
        // Invoke custom verification callback
        int callback_status = verify_options_->verify_peer_callback(
            target_name, peer_pem,
            verify_options_->verify_peer_callback_userdata);
        gpr_free(peer_pem);
        if (callback_status) {
          error = GRPC_ERROR_CREATE(absl::StrFormat(
              "Verify peer callback returned a failure (%d)", callback_status));
        }
      }
    }
    // Complete peer verification
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
    tsi_peer_destruct(&peer);
  }

  // Cancels ongoing peer verification (no-op in this implementation)
  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  // Compares this security connector with another
  int cmp(const grpc_security_connector* other_sc) const override {
    auto* other =
        reinterpret_cast<const grpc_ssl_channel_security_connector*>(other_sc);
    int c = channel_security_connector_cmp(other);
    if (c != 0) return c;
    c = target_name_.compare(other->target_name_);
    if (c != 0) return c;
    return overridden_target_name_.compare(other->overridden_target_name_);
  }

  // Verifies the host name during a call
  grpc_core::ArenaPromise<absl::Status> CheckCallHost(
      absl::string_view host, grpc_auth_context* auth_context) override {
    return grpc_core::Immediate(
        SslCheckCallHost(host, target_name_.c_str(),
                         overridden_target_name_.c_str(), auth_context));
  }

 private:
  tsi_ssl_client_handshaker_factory* client_handshaker_factory_ = nullptr;
  std::string target_name_;  // Original target name
  std::string overridden_target_name_;  // Overridden target name (if any)
  const verify_peer_options* verify_options_;  // Verification options
};

// SSL server security connector implementation
class grpc_ssl_server_security_connector
    : public grpc_server_security_connector {
 public:
  explicit grpc_ssl_server_security_connector(
      grpc_core::RefCountedPtr<grpc_server_credentials> server_creds)
      : grpc_server_security_connector(GRPC_SSL_URL_SCHEME,
                                       std::move(server_creds)) {}

  ~grpc_ssl_server_security_connector() override {
    tsi_ssl_server_handshaker_factory_unref(server_handshaker_factory_);
  }

  // Returns true if this connector has a certificate config fetcher
  bool has_cert_config_fetcher() const {
    return static_cast<const grpc_ssl_server_credentials*>(server_creds())
        ->has_cert_config_fetcher();
  }

  // Returns the server handshaker factory
  const tsi_ssl_server_handshaker_factory* server_handshaker_factory() const {
    return server_handshaker_factory_;
  }

  // Initializes the handshaker factory with SSL configuration
  grpc_security_status InitializeHandshakerFactory(
      std::optional<std::string> alpn_preferred_protocol_raw_list) {
    if (has_cert_config_fetcher()) {
      // Try to fetch initial server credentials
      if (!try_fetch_ssl_server_credentials()) {
        LOG(ERROR) << "Failed loading SSL server credentials from fetcher.";
        return GRPC_SECURITY_ERROR;
      }
    } else {
      // Use static credentials from server config
      auto* server_credentials =
          static_cast<const grpc_ssl_server_credentials*>(server_creds());
      size_t num_alpn_protocols = 0;
      const char** alpn_protocol_strings = nullptr;
      if (alpn_preferred_protocol_raw_list.has_value()) {
#if TSI_OPENSSL_ALPN_SUPPORT
        alpn_protocol_strings = ParseAlpnStringIntoArray(
            alpn_preferred_protocol_raw_list.value(), &num_alpn_protocols);
#endif
      }
      if (alpn_protocol_strings == nullptr) {
        alpn_protocol_strings =
            grpc_fill_alpn_protocol_strings(&num_alpn_protocols);
      }
      // Set up handshaker options
      tsi_ssl_server_handshaker_options options;
      options.pem_key_cert_pairs =
          server_credentials->config().pem_key_cert_pairs;
      options.num_key_cert_pairs =
          server_credentials->config().num_key_cert_pairs;
      options.pem_client_root_certs =
          server_credentials->config().pem_root_certs;
      options.client_certificate_request =
          grpc_get_tsi_client_certificate_request_type(
              server_credentials->config().client_certificate_request);
      options.cipher_suites = grpc_get_ssl_cipher_suites();
      options.alpn_protocols = alpn_protocol_strings;
      options.num_alpn_protocols = static_cast<uint16_t>(num_alpn_protocols);
      options.min_tls_version = grpc_get_tsi_tls_version(
          server_credentials->config().min_tls_version);
      options.max_tls_version = grpc_get_tsi_tls_version(
          server_credentials->config().max_tls_version);
      // Create handshaker factory
      const tsi_result result =
          tsi_create_ssl_server_handshaker_factory_with_options(
              &options, &server_handshaker_factory_);
      gpr_free(alpn_protocol_strings);
      if (result != TSI_OK) {
        LOG(ERROR) << "Handshaker factory creation failed with "
                   << tsi_result_to_string(result);
        return GRPC_SECURITY_ERROR;
      }
    }
    return GRPC_SECURITY_OK;
  }

  // Adds SSL handshakers to the handshake manager
  void add_handshakers(const grpc_core::ChannelArgs& args,
                       grpc_pollset_set* ,
                       grpc_core::HandshakeManager* handshake_mgr) override {
    // Try to fetch updated credentials if using a fetcher
    try_fetch_ssl_server_credentials();
    // Create TSI handshaker
    tsi_handshaker* tsi_hs = nullptr;
    tsi_result result = tsi_ssl_server_handshaker_factory_create_handshaker(
        server_handshaker_factory_, 0,
        0, &tsi_hs);
    if (result != TSI_OK) {
      LOG(ERROR) << "Handshaker creation failed with error "
                 << tsi_result_to_string(result);
      return;
    }

    // Add security handshaker to the manager
    handshake_mgr->Add(grpc_core::SecurityHandshakerCreate(tsi_hs, this, args));
  }

  // Verifies peer identity (client certificate in this case)
  void check_peer(tsi_peer peer, grpc_endpoint* ,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    // Perform basic SSL peer verification (no hostname check for servers)
    grpc_error_handle error = ssl_check_peer(nullptr, &peer, auth_context);
    tsi_peer_destruct(&peer);
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
  }

  // Cancels ongoing peer verification (no-op in this implementation)
  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  // Compares this security connector with another
  int cmp(const grpc_security_connector* other) const override {
    return server_security_connector_cmp(
        static_cast<const grpc_server_security_connector*>(other));
  }

 private:
  // Attempts to fetch new SSL server credentials if using a fetcher
  bool try_fetch_ssl_server_credentials() {
    grpc_ssl_server_certificate_config* certificate_config = nullptr;
    bool status;
    if (!has_cert_config_fetcher()) return false;

    grpc_core::MutexLock lock(&mu_);
    grpc_ssl_server_credentials* server_creds =
        static_cast<grpc_ssl_server_credentials*>(this->mutable_server_creds());
    // Fetch new certificate config
    grpc_ssl_certificate_config_reload_status cb_result =
        server_creds->FetchCertConfig(&certificate_config);
    if (cb_result == GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_UNCHANGED) {
      status = false;
    } else if (cb_result == GRPC_SSL_CERTIFICATE_CONFIG_RELOAD_NEW) {
      // Try to replace handshaker factory with new config
      status = try_replace_server_handshaker_factory(certificate_config);
    } else {
      // Failed to fetch new config
      LOG(ERROR) << "Failed fetching new server credentials, continuing to "
                    "use previously-loaded credentials.";
      status = false;
    }

    if (certificate_config != nullptr) {
      grpc_ssl_server_certificate_config_destroy(certificate_config);
    }
    return status;
  }

  // Attempts to create a new handshaker factory with the given config
  bool try_replace_server_handshaker_factory(
      const grpc_ssl_server_certificate_config* config) {
    if (config == nullptr) {
      LOG(ERROR)
          << "Server certificate config callback returned invalid (NULL) "
             "config.";
      return false;
    }
    VLOG(2) << "Using new server certificate config (" << config << ").";

    size_t num_alpn_protocols = 0;
    const char** alpn_protocol_strings =
        grpc_fill_alpn_protocol_strings(&num_alpn_protocols);
    tsi_ssl_server_handshaker_factory* new_handshaker_factory = nullptr;
    const grpc_ssl_server_credentials* server_creds =
        static_cast<const grpc_ssl_server_credentials*>(this->server_creds());
    DCHECK_NE(config->pem_root_certs, nullptr);
    // Set up handshaker options with new config
    tsi_ssl_server_handshaker_options options;
    options.pem_key_cert_pairs = grpc_convert_grpc_to_tsi_cert_pairs(
        config->pem_key_cert_pairs, config