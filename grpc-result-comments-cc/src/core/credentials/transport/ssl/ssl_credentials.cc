Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/credentials/transport/ssl/ssl_credentials.h"

#include <grpc/impl/channel_arg_names.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <optional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/credentials/transport/tls/ssl_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/tsi/ssl/session_cache/ssl_session_cache.h"
#include "src/core/tsi/ssl_transport_security.h"
#include "src/core/tsi/transport_security_interface.h"

// Constructor for SSL credentials
// Initializes SSL credentials with root certificates, key-cert pair, and verification options
grpc_ssl_credentials::grpc_ssl_credentials(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const grpc_ssl_verify_peer_options* verify_options) {
  build_config(pem_root_certs, pem_key_cert_pair, verify_options);

  // If no root certs were provided, try to use default root certs
  if (config_.pem_root_certs == nullptr) {
    const char* pem_root_certs =
        grpc_core::DefaultSslRootStore::GetPemRootCerts();
    if (pem_root_certs == nullptr) {
      LOG(ERROR) << "Could not get default pem root certs.";
    } else {
      char* default_roots = gpr_strdup(pem_root_certs);
      config_.pem_root_certs = default_roots;
      root_store_ = grpc_core::DefaultSslRootStore::GetRootStore();
    }
  } else {
    config_.pem_root_certs = config_.pem_root_certs;
    root_store_ = nullptr;
  }

  // Initialize client handshaker factory
  client_handshaker_initialization_status_ = InitializeClientHandshakerFactory(
      &config_, config_.pem_root_certs, root_store_, nullptr,
      &client_handshaker_factory_);
}

// Destructor for SSL credentials
// Cleans up allocated resources
grpc_ssl_credentials::~grpc_ssl_credentials() {
  gpr_free(config_.pem_root_certs);
  grpc_tsi_ssl_pem_key_cert_pairs_destroy(config_.pem_key_cert_pair, 1);
  if (config_.verify_options.verify_peer_destruct != nullptr) {
    config_.verify_options.verify_peer_destruct(
        config_.verify_options.verify_peer_callback_userdata);
  }
  tsi_ssl_client_handshaker_factory_unref(client_handshaker_factory_);
}

// Creates a security connector for SSL channel credentials
grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_ssl_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target, grpc_core::ChannelArgs* args) {
  if (config_.pem_root_certs == nullptr) {
    LOG(ERROR) << "No root certs in config. Client-side security connector "
                  "must have root certs.";
    return nullptr;
  }
  
  // Get target name override if specified
  std::optional<std::string> overridden_target_name =
      args->GetOwnedString(GRPC_SSL_TARGET_NAME_OVERRIDE_ARG);
  auto* ssl_session_cache = args->GetObject<tsi::SslSessionLRUCache>();
  tsi_ssl_session_cache* session_cache =
      ssl_session_cache == nullptr ? nullptr : ssl_session_cache->c_ptr();

  grpc_core::RefCountedPtr<grpc_channel_security_connector> security_connector =
      nullptr;
  
  // Create security connector with session cache if available
  if (session_cache != nullptr) {
    tsi_ssl_client_handshaker_factory* factory_with_cache = nullptr;
    grpc_security_status status = InitializeClientHandshakerFactory(
        &config_, config_.pem_root_certs, root_store_, session_cache,
        &factory_with_cache);
    if (status != GRPC_SECURITY_OK) {
      LOG(ERROR) << "InitializeClientHandshakerFactory returned bad status.";
      return nullptr;
    }
    security_connector = grpc_ssl_channel_security_connector_create(
        this->Ref(), std::move(call_creds), &config_, target,
        overridden_target_name.has_value() ? overridden_target_name->c_str()
                                           : nullptr,
        factory_with_cache);
    tsi_ssl_client_handshaker_factory_unref(factory_with_cache);
  } else {
    // Create security connector without session cache
    if (client_handshaker_initialization_status_ != GRPC_SECURITY_OK) {
      return nullptr;
    }
    security_connector = grpc_ssl_channel_security_connector_create(
        this->Ref(), std::move(call_creds), &config_, target,
        overridden_target_name.has_value() ? overridden_target_name->c_str()
                                           : nullptr,
        client_handshaker_factory_);
  }

  if (security_connector == nullptr) {
    return security_connector;
  }
  // Set HTTPS scheme for the channel
  *args = args->Set(GRPC_ARG_HTTP2_SCHEME, "https");
  return security_connector;
}

// Returns the type name for SSL credentials
grpc_core::UniqueTypeName grpc_ssl_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Ssl");
  return kFactory.Create();
}

// Builds SSL configuration from provided parameters
void grpc_ssl_credentials::build_config(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const grpc_ssl_verify_peer_options* verify_options) {
  config_.pem_root_certs = gpr_strdup(pem_root_certs);
  if (pem_key_cert_pair != nullptr) {
    CHECK_NE(pem_key_cert_pair->private_key, nullptr);
    CHECK_NE(pem_key_cert_pair->cert_chain, nullptr);
    config_.pem_key_cert_pair = static_cast<tsi_ssl_pem_key_cert_pair*>(
        gpr_zalloc(sizeof(tsi_ssl_pem_key_cert_pair)));
    config_.pem_key_cert_pair->cert_chain =
        gpr_strdup(pem_key_cert_pair->cert_chain);
    config_.pem_key_cert_pair->private_key =
        gpr_strdup(pem_key_cert_pair->private_key);
  } else {
    config_.pem_key_cert_pair = nullptr;
  }
  if (verify_options != nullptr) {
    memcpy(&config_.verify_options, verify_options,
           sizeof(verify_peer_options));
  } else {
    memset(&config_.verify_options, 0, sizeof(verify_peer_options));
  }
}

// Sets minimum TLS version for SSL credentials
void grpc_ssl_credentials::set_min_tls_version(
    grpc_tls_version min_tls_version) {
  config_.min_tls_version = min_tls_version;
}

// Sets maximum TLS version for SSL credentials
void grpc_ssl_credentials::set_max_tls_version(
    grpc_tls_version max_tls_version) {
  config_.max_tls_version = max_tls_version;
}

// Initializes client handshaker factory with SSL configuration
grpc_security_status grpc_ssl_credentials::InitializeClientHandshakerFactory(
    const grpc_ssl_config* config, const char* pem_root_certs,
    const tsi_ssl_root_certs_store* root_store,
    tsi_ssl_session_cache* ssl_session_cache,
    tsi_ssl_client_handshaker_factory** handshaker_factory) {
  // Return if factory already exists and no session cache is provided
  if (client_handshaker_factory_ != nullptr && ssl_session_cache == nullptr) {
    return GRPC_SECURITY_OK;
  }

  bool has_key_cert_pair = config->pem_key_cert_pair != nullptr &&
                           config->pem_key_cert_pair->private_key != nullptr &&
                           config->pem_key_cert_pair->cert_chain != nullptr;
  tsi_ssl_client_handshaker_options options;
  if (pem_root_certs == nullptr) {
    LOG(ERROR) << "Handshaker factory creation failed. pem_root_certs cannot "
                  "be nullptr";
    return GRPC_SECURITY_ERROR;
  }
  options.pem_root_certs = pem_root_certs;
  options.root_store = root_store;
  options.alpn_protocols =
      grpc_fill_alpn_protocol_strings(&options.num_alpn_protocols);
  if (has_key_cert_pair) {
    options.pem_key_cert_pair = config->pem_key_cert_pair;
  }
  options.cipher_suites = grpc_get_ssl_cipher_suites();
  options.session_cache = ssl_session_cache;
  options.min_tls_version = grpc_get_tsi_tls_version(config->min_tls_version);
  options.max_tls_version = grpc_get_tsi_tls_version(config->max_tls_version);
  
  // Create SSL client handshaker factory
  const tsi_result result =
      tsi_create_ssl_client_handshaker_factory_with_options(&options,
                                                            handshaker_factory);
  gpr_free(options.alpn_protocols);
  if (result != TSI_OK) {
    LOG(ERROR) << "Handshaker factory creation failed with "
               << tsi_result_to_string(result);
    return GRPC_SECURITY_ERROR;
  }
  return GRPC_SECURITY_OK;
}

// Creates SSL channel credentials
grpc_channel_credentials* grpc_ssl_credentials_create(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const verify_peer_options* verify_options, void* reserved) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_ssl_credentials_create(pem_root_certs=" << pem_root_certs
      << ", pem_key_cert_pair=" << pem_key_cert_pair
      << ", verify_options=" << verify_options << ", reserved=" << reserved
      << ")";
  CHECK_EQ(reserved, nullptr);

  return new grpc_ssl_credentials(
      pem_root_certs, pem_key_cert_pair,
      reinterpret_cast<const grpc_ssl_verify_peer_options*>(verify_options));
}

// Creates SSL channel credentials with extended options
grpc_channel_credentials* grpc_ssl_credentials_create_ex(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pair,
    const grpc_ssl_verify_peer_options* verify_options, void* reserved) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_ssl_credentials_create(pem_root_certs=" << pem_root_certs
      << ", pem_key_cert_pair=" << pem_key_cert_pair
      << ", verify_options=" << verify_options << ", reserved=" << reserved
      << ")";
  CHECK_EQ(reserved, nullptr);

  return new grpc_ssl_credentials(pem_root_certs, pem_key_cert_pair,
                                  verify_options);
}

// Structure for SSL server credentials options
struct grpc_ssl_server_credentials_options {
  grpc_ssl_client_certificate_request_type client_certificate_request;
  grpc_ssl_server_certificate_config* certificate_config;
  grpc_ssl_server_certificate_config_fetcher* certificate_config_fetcher;
};

// Constructor for SSL server credentials
grpc_ssl_server_credentials::grpc_ssl_server_credentials(
    const grpc_ssl_server_credentials_options& options) {
  if (options.certificate_config_fetcher != nullptr) {
    // Use certificate config fetcher if provided
    config_.client_certificate_request = options.client_certificate_request;
    certificate_config_fetcher_ = *options.certificate_config_fetcher;
  } else {
    // Otherwise build config from provided certificate config
    build_config(options.certificate_config->pem_root_certs,
                 options.certificate_config->pem_key_cert_pairs,
                 options.certificate_config->num_key_cert_pairs,
                 options.client_certificate_request);
  }
}

// Destructor for SSL server credentials
grpc_ssl_server_credentials::~grpc_ssl_server_credentials() {
  grpc_tsi_ssl_pem_key_cert_pairs_destroy(config_.pem_key_cert_pairs,
                                          config_.num_key_cert_pairs);
  gpr_free(config_.pem_root_certs);
}

// Creates security connector for SSL server credentials
grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_ssl_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& args) {
  return grpc_ssl_server_security_connector_create(this->Ref(), args);
}

// Returns the type name for SSL server credentials
grpc_core::UniqueTypeName grpc_ssl_server_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Ssl");
  return kFactory.Create();
}

// Converts gRPC cert pairs to TSI cert pairs
tsi_ssl_pem_key_cert_pair* grpc_convert_grpc_to_tsi_cert_pairs(
    const grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs) {
  tsi_ssl_pem_key_cert_pair* tsi_pairs = nullptr;
  if (num_key_cert_pairs > 0) {
    CHECK_NE(pem_key_cert_pairs, nullptr);
    tsi_pairs = static_cast<tsi_ssl_pem_key_cert_pair*>(
        gpr_zalloc(num_key_cert_pairs * sizeof(tsi_ssl_pem_key_cert_pair)));
  }
  for (size_t i = 0; i < num_key_cert_pairs; i++) {
    CHECK_NE(pem_key_cert_pairs[i].private_key, nullptr);
    CHECK_NE(pem_key_cert_pairs[i].cert_chain, nullptr);
    tsi_pairs[i].cert_chain = gpr_strdup(pem_key_cert_pairs[i].cert_chain);
    tsi_pairs[i].private_key = gpr_strdup(pem_key_cert_pairs[i].private_key);
  }
  return tsi_pairs;
}

// Builds SSL server configuration from provided parameters
void grpc_ssl_server_credentials::build_config(
    const char* pem_root_certs, grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs,
    grpc_ssl_client_certificate_request_type client_certificate_request) {
  config_.client_certificate_request = client_certificate_request;
  config_.pem_root_certs = gpr_strdup(pem_root_certs);
  config_.pem_key_cert_pairs = grpc_convert_grpc_to_tsi_cert_pairs(
      pem_key_cert_pairs, num_key_cert_pairs);
  config_.num_key_cert_pairs = num_key_cert_pairs;
}

// Sets minimum TLS version for SSL server credentials
void grpc_ssl_server_credentials::set_min_tls_version(
    grpc_tls_version min_tls_version) {
  config_.min_tls_version = min_tls_version;
}

// Sets maximum TLS version for SSL server credentials
void grpc_ssl_server_credentials::set_max_tls_version(
    grpc_tls_version max_tls_version) {
  config_.max_tls_version = max_tls_version;
}

// Creates SSL server certificate configuration
grpc_ssl_server_certificate_config* grpc_ssl_server_certificate_config_create(
    const char* pem_root_certs,
    const grpc_ssl_pem_key_cert_pair* pem_key_cert_pairs,
    size_t num_key_cert_pairs) {
  grpc_ssl_server_certificate_config* config =
      static_cast<grpc_ssl_server_certificate_config*>(
          gpr_zalloc(sizeof(grpc_ssl_server_certificate_config)));
  config->pem_root_certs = gpr_strdup(pem_root_certs);
  if (num_key_cert_pairs > 0) {
    CHECK_NE(pem_key_cert_pairs, nullptr);
    config->pem_key_cert_pairs = static_cast<grpc_ssl_pem_key_cert_pair*>(
        gpr_zalloc(num_key_cert_pairs * sizeof(grpc_ssl_pem_key_cert_pair)));
  }
  config->num_key_cert_pairs = num_key_cert_pairs;
  for (size_t i = 0; i < num_key_cert_pairs; i++) {
    CHECK_NE(pem_key_cert_pairs[i].private_key, nullptr);
    CHECK_NE(pem_key_cert_pairs[i].cert_chain, nullptr);
    config->pem_key_cert_pairs[i].cert_chain =
        gpr_strdup(pem_key_cert_pairs[i].cert_chain);
    config->pem_key_cert_pairs[i].private_key =
        gpr_strdup(pem_key_cert_pairs[i].private_key);
  }
  return config;
}

// Destroys SSL server certificate configuration
void grpc_ssl_server_certificate_config_destroy(
    grpc_ssl_server_certificate_config* config) {
  if (config == nullptr) return;
  for (size_t i = 0; i < config->num_key_cert_pairs; i++) {
    gpr_free(const_cast<char*>(config->pem_key_cert_pairs[i].private_key));
    gpr_free(const_cast<char*>(config->pem_key_cert_pairs[i].cert_