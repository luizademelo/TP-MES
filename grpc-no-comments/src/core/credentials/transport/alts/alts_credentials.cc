
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/alts/alts_credentials.h"

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>

#include <utility>

#include "src/core/credentials/transport/alts/alts_security_connector.h"
#include "src/core/credentials/transport/alts/check_gcp_environment.h"
#include "src/core/credentials/transport/alts/grpc_alts_credentials_options.h"

#define GRPC_ALTS_HANDSHAKER_SERVICE_URL "dns:///metadata.google.internal.:8080"

grpc_alts_credentials::grpc_alts_credentials(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url)
    : options_(grpc_alts_credentials_options_copy(options)),
      handshaker_service_url_(handshaker_service_url == nullptr
                                  ? gpr_strdup(GRPC_ALTS_HANDSHAKER_SERVICE_URL)
                                  : gpr_strdup(handshaker_service_url)) {
  grpc_alts_set_rpc_protocol_versions(&options_->rpc_versions);
}

grpc_alts_credentials::~grpc_alts_credentials() {
  grpc_alts_credentials_options_destroy(options_);
  gpr_free(handshaker_service_url_);
}

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_alts_credentials::create_security_connector(
    grpc_core::RefCountedPtr<grpc_call_credentials> call_creds,
    const char* target_name, grpc_core::ChannelArgs* ) {
  return grpc_alts_channel_security_connector_create(
      this->Ref(), std::move(call_creds), target_name);
}

grpc_core::UniqueTypeName grpc_alts_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Alts");
  return kFactory.Create();
}

grpc_alts_server_credentials::grpc_alts_server_credentials(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url)
    : options_(grpc_alts_credentials_options_copy(options)),
      handshaker_service_url_(handshaker_service_url == nullptr
                                  ? gpr_strdup(GRPC_ALTS_HANDSHAKER_SERVICE_URL)
                                  : gpr_strdup(handshaker_service_url)) {
  grpc_alts_set_rpc_protocol_versions(&options_->rpc_versions);
}

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_alts_server_credentials::create_security_connector(
    const grpc_core::ChannelArgs& ) {
  return grpc_alts_server_security_connector_create(this->Ref());
}

grpc_alts_server_credentials::~grpc_alts_server_credentials() {
  grpc_alts_credentials_options_destroy(options_);
  gpr_free(handshaker_service_url_);
}

grpc_core::UniqueTypeName grpc_alts_server_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Alts");
  return kFactory.Create();
}

grpc_channel_credentials* grpc_alts_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts) {
  if (!enable_untrusted_alts && !grpc_alts_is_running_on_gcp()) {
    return nullptr;
  }
  return new grpc_alts_credentials(options, handshaker_service_url);
}

grpc_server_credentials* grpc_alts_server_credentials_create_customized(
    const grpc_alts_credentials_options* options,
    const char* handshaker_service_url, bool enable_untrusted_alts) {
  if (!enable_untrusted_alts && !grpc_alts_is_running_on_gcp()) {
    return nullptr;
  }
  return new grpc_alts_server_credentials(options, handshaker_service_url);
}

grpc_channel_credentials* grpc_alts_credentials_create(
    const grpc_alts_credentials_options* options) {
  return grpc_alts_credentials_create_customized(
      options, GRPC_ALTS_HANDSHAKER_SERVICE_URL, false);
}

grpc_server_credentials* grpc_alts_server_credentials_create(
    const grpc_alts_credentials_options* options) {
  return grpc_alts_server_credentials_create_customized(
      options, GRPC_ALTS_HANDSHAKER_SERVICE_URL, false);
}
