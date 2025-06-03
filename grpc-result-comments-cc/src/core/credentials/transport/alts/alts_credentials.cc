Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

// Include necessary headers for ALTS credentials implementation
#include "src/core/credentials/transport/alts/alts_credentials.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>

#include <utility>

#include "src/core/credentials/transport/alts/alts_security_connector.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/credentials/transport/alts/grpc_alts_credentials_options.h"

// Default URL for ALTS handshaker service in GCP environment
#define GRPC_ALTS_HANDSHAKER_SERVICE_URL "dns:///metadata.google.internal.:8080"

// Constructor for ALTS channel credentials
// options: ALTS credentials options containing security configurations
// handshaker_service_url: URL for the ALTS handshaker service (nullptr uses default)
grpc_alts_credentials::grpc_alts_credentials(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url)
    : options_(grpc_alts_credentials_options_copy(options)),
      handshaker_service_url_(handshaker_service_url == nullptr
                                  ? gpr_strdup(GRPC_ALTS_HANDSHAKER_SERVICE_URL)
                                  : gpr_strdup(handshaker_service_url)) {
  // Set RPC protocol versions in the options
  grpc_alts_set_rpc_protocol_versions(&options_->rpc_versions);
}

// Destructor for ALTS channel credentials
grpc_alts_credentials::~grpc_alts_credentials() {
  grpc_alts_credentials_options_destroy(options_);
  gpr_free(handshaker_service_url_);
}

// Creates a security connector for ALTS channel credentials
// call_creds: Call credentials to associate with the connector
// target_name: Target name for the secure connection
// Returns: A new ALTS channel security connector
grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_alts_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target_name, grpc_core::ChannelArgs* ) {
  return grpc_alts_channel_security_connector_create(
      this->Ref(), std::move(call_creds), target_name);
}

// Returns the unique type name for ALTS credentials
grpc_core::UniqueTypeName grpc_alts_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Alts");
  return kFactory.Create();
}

// Constructor for ALTS server credentials
// options: ALTS credentials options containing security configurations
// handshaker_service_url: URL for the ALTS handshaker service (nullptr uses default)
grpc_alts_server_credentials::grpc_alts_server_credentials(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url)
    : options_(grpc_alts_credentials_options_copy(options)),
      handshaker_service_url_(handshaker_service_url == nullptr
                                  ? gpr_strdup(GRPC_ALTS_HANDSHAKER_SERVICE_URL)
                                  : gpr_strdup(handshaker_service_url)) {
  // Set RPC protocol versions in the options
  grpc_alts_set_rpc_protocol_versions(&options_->rpc_versions);
}

// Creates a security connector for ALTS server credentials
// Returns: A new ALTS server security connector
grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_alts_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& ) {
  return grpc_alts_server_security_connector_create(this->Ref());
}

// Destructor for ALTS server credentials
grpc_alts_server_credentials::~grpc_alts_server_credentials() {
  grpc_alts_credentials_options_destroy(options_);
  gpr_free(handshaker_service_url_);
}

// Returns the unique type name for ALTS server credentials
grpc_core::UniqueTypeName grpc_alts_server_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Alts");
  return kFactory.Create();
}

// Creates customized ALTS channel credentials
// options: ALTS credentials options
// handshaker_service_url: Custom handshaker service URL
// enable_untrusted_alts: Whether to allow ALTS on non-GCP environments
// Returns: New ALTS channel credentials or nullptr if not on GCP and untrusted ALTS disabled
grpc_channel_credentials* grpc_alts_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts) {
  if (!enable_untrusted_alts && !grpc_alts_is_running_on_gcp()) {
    return nullptr;
  }
  return new grpc_alts_credentials(options, handshaker_service_url);
}

// Creates customized ALTS server credentials
// options: ALTS credentials options
// handshaker_service_url: Custom handshaker service URL
// enable_untrusted_alts: Whether to allow ALTS on non-GCP environments
// Returns: New ALTS server credentials or nullptr if not on GCP and untrusted ALTS disabled
grpc_server_credentials* grpc_alts_server_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts) {
  if (!enable_untrusted_alts && !grpc_alts_is_running_on_gcp()) {
    return nullptr;
  }
  return new grpc_alts_server_credentials(options, handshaker_service_url);
}

// Creates ALTS channel credentials with default settings
// options: ALTS credentials options
// Returns: New ALTS channel credentials (only works in GCP environment)
grpc_channel_credentials* grpc_alts_credentials_create(
    const grpc_alts_credentials_options* options) {
  return grpc_alts_credentials_create_customized(
      options, GRPC_ALTS_HANDSHAKER_SERVICE_URL, false);
}

// Creates ALTS server credentials with default settings
// options: ALTS credentials options
// Returns: New ALTS server credentials (only works in GCP environment)
grpc_server_credentials* grpc_alts_server_credentials_create(
    const grpc_alts_credentials_options* options) {
  return grpc_alts_server_credentials_create_customized(
      options, GRPC_ALTS_HANDSHAKER_SERVICE_URL, false);
}
```