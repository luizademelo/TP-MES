
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/alts/alts_security_connector.h"

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/channel_arg_names.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <algorithm>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/alts/alts_credentials.h"
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
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/alts/handshaker/alts_tsi_handshaker.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

void grpc_alts_set_rpc_protocol_versions(
    grpc_gcp_rpc_protocol_versions* rpc_versions) {
  grpc_gcp_rpc_protocol_versions_set_max(rpc_versions,
                                         GRPC_PROTOCOL_VERSION_MAX_MAJOR,
                                         GRPC_PROTOCOL_VERSION_MAX_MINOR);
  grpc_gcp_rpc_protocol_versions_set_min(rpc_versions,
                                         GRPC_PROTOCOL_VERSION_MIN_MAJOR,
                                         GRPC_PROTOCOL_VERSION_MIN_MINOR);
}

namespace {

void alts_check_peer(tsi_peer peer,
                     grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                     grpc_closure* on_peer_checked) {
  *auth_context =
      grpc_core::internal::grpc_alts_auth_context_from_tsi_peer(&peer);
  tsi_peer_destruct(&peer);
  grpc_error_handle error =
      *auth_context != nullptr
          ? absl::OkStatus()
          : GRPC_ERROR_CREATE("Could not get ALTS auth context from TSI peer");
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
}

class grpc_alts_channel_security_connector final
    : public grpc_channel_security_connector {
 public:
  grpc_alts_channel_security_connector(
      grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
      grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* target_name)
      : grpc_channel_security_connector(GRPC_SSL_URL_SCHEME,
                                        std::move(channel_creds),
                                        std::move(request_metadata_creds)),
        target_name_(gpr_strdup(target_name)) {}

  ~grpc_alts_channel_security_connector() override { gpr_free(target_name_); }

  void add_handshakers(
      const grpc_core::ChannelArgs& args, grpc_pollset_set* interested_parties,
      grpc_core::HandshakeManager* handshake_manager) override {
    tsi_handshaker* handshaker = nullptr;
    const grpc_alts_credentials* creds =
        static_cast<const grpc_alts_credentials*>(channel_creds());
    const size_t user_specified_max_frame_size =
        std::max(0, args.GetInt(GRPC_ARG_TSI_MAX_FRAME_SIZE).value_or(0));
    CHECK(alts_tsi_handshaker_create(
              creds->options(), target_name_, creds->handshaker_service_url(),
              true, interested_parties, &handshaker,
              user_specified_max_frame_size,
              args.GetOwnedString(GRPC_ARG_TRANSPORT_PROTOCOLS)) == TSI_OK);
    handshake_manager->Add(
        grpc_core::SecurityHandshakerCreate(handshaker, this, args));
  }

  void check_peer(tsi_peer peer, grpc_endpoint* ,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    alts_check_peer(peer, auth_context, on_peer_checked);
  }

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  int cmp(const grpc_security_connector* other_sc) const override {
    auto* other =
        reinterpret_cast<const grpc_alts_channel_security_connector*>(other_sc);
    int c = channel_security_connector_cmp(other);
    if (c != 0) return c;
    return strcmp(target_name_, other->target_name_);
  }

  grpc_core::ArenaPromise<absl::Status> CheckCallHost(
      absl::string_view, grpc_auth_context*) override {
    return grpc_core::ImmediateOkStatus();
  }

 private:
  char* target_name_;
};

class grpc_alts_server_security_connector final
    : public grpc_server_security_connector {
 public:
  explicit grpc_alts_server_security_connector(
      grpc_core::RefCountedPtr<grpc_server_credentials> server_creds)
      : grpc_server_security_connector(GRPC_SSL_URL_SCHEME,
                                       std::move(server_creds)) {}

  ~grpc_alts_server_security_connector() override = default;

  void add_handshakers(
      const grpc_core::ChannelArgs& args, grpc_pollset_set* interested_parties,
      grpc_core::HandshakeManager* handshake_manager) override {
    tsi_handshaker* handshaker = nullptr;
    const grpc_alts_server_credentials* creds =
        static_cast<const grpc_alts_server_credentials*>(server_creds());
    size_t user_specified_max_frame_size =
        std::max(0, args.GetInt(GRPC_ARG_TSI_MAX_FRAME_SIZE).value_or(0));
    CHECK(alts_tsi_handshaker_create(
              creds->options(), nullptr, creds->handshaker_service_url(), false,
              interested_parties, &handshaker, user_specified_max_frame_size,
              args.GetOwnedString(GRPC_ARG_TRANSPORT_PROTOCOLS)) == TSI_OK);
    handshake_manager->Add(
        grpc_core::SecurityHandshakerCreate(handshaker, this, args));
  }

  void check_peer(tsi_peer peer, grpc_endpoint* ,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    alts_check_peer(peer, auth_context, on_peer_checked);
  }

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  int cmp(const grpc_security_connector* other) const override {
    return server_security_connector_cmp(
        static_cast<const grpc_server_security_connector*>(other));
  }
};
}

namespace grpc_core {
namespace internal {
RefCountedPtr<grpc_auth_context> grpc_alts_auth_context_from_tsi_peer(
    const tsi_peer* peer) {
  if (peer == nullptr) {
    LOG(ERROR) << "Invalid arguments to grpc_alts_auth_context_from_tsi_peer()";
    return nullptr;
  }

  const tsi_peer_property* cert_type_prop =
      tsi_peer_get_property_by_name(peer, TSI_CERTIFICATE_TYPE_PEER_PROPERTY);
  if (cert_type_prop == nullptr ||
      strncmp(cert_type_prop->value.data, TSI_ALTS_CERTIFICATE_TYPE,
              cert_type_prop->value.length) != 0) {
    LOG(ERROR) << "Invalid or missing certificate type property.";
    return nullptr;
  }

  const tsi_peer_property* security_level_prop =
      tsi_peer_get_property_by_name(peer, TSI_SECURITY_LEVEL_PEER_PROPERTY);
  if (security_level_prop == nullptr) {
    LOG(ERROR) << "Missing security level property.";
    return nullptr;
  }

  const tsi_peer_property* rpc_versions_prop =
      tsi_peer_get_property_by_name(peer, TSI_ALTS_RPC_VERSIONS);
  if (rpc_versions_prop == nullptr) {
    LOG(ERROR) << "Missing rpc protocol versions property.";
    return nullptr;
  }
  grpc_gcp_rpc_protocol_versions local_versions, peer_versions;
  grpc_alts_set_rpc_protocol_versions(&local_versions);
  grpc_slice slice = grpc_slice_from_copied_buffer(
      rpc_versions_prop->value.data, rpc_versions_prop->value.length);
  bool decode_result =
      grpc_gcp_rpc_protocol_versions_decode(slice, &peer_versions);
  CSliceUnref(slice);
  if (!decode_result) {
    LOG(ERROR) << "Invalid peer rpc protocol versions.";
    return nullptr;
  }

  bool check_result = grpc_gcp_rpc_protocol_versions_check(
      &local_versions, &peer_versions, nullptr);
  if (!check_result) {
    LOG(ERROR) << "Mismatch of local and peer rpc protocol versions.";
    return nullptr;
  }

  const tsi_peer_property* alts_context_prop =
      tsi_peer_get_property_by_name(peer, TSI_ALTS_CONTEXT);
  if (alts_context_prop == nullptr) {
    LOG(ERROR) << "Missing alts context property.";
    return nullptr;
  }

  auto ctx = MakeRefCounted<grpc_auth_context>(nullptr);
  grpc_auth_context_add_cstring_property(
      ctx.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
      GRPC_ALTS_TRANSPORT_SECURITY_TYPE);
  size_t i = 0;
  for (i = 0; i < peer->property_count; i++) {
    const tsi_peer_property* tsi_prop = &peer->properties[i];

    if (strcmp(tsi_prop->name, TSI_ALTS_SERVICE_ACCOUNT_PEER_PROPERTY) == 0) {
      grpc_auth_context_add_property(
          ctx.get(), TSI_ALTS_SERVICE_ACCOUNT_PEER_PROPERTY,
          tsi_prop->value.data, tsi_prop->value.length);
      CHECK(grpc_auth_context_set_peer_identity_property_name(
                ctx.get(), TSI_ALTS_SERVICE_ACCOUNT_PEER_PROPERTY) == 1);
    }

    if (strcmp(tsi_prop->name, TSI_ALTS_CONTEXT) == 0) {
      grpc_auth_context_add_property(ctx.get(), TSI_ALTS_CONTEXT,
                                     tsi_prop->value.data,
                                     tsi_prop->value.length);
    }

    if (strcmp(tsi_prop->name, TSI_SECURITY_LEVEL_PEER_PROPERTY) == 0) {
      grpc_auth_context_add_property(
          ctx.get(), GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME,
          tsi_prop->value.data, tsi_prop->value.length);
    }
  }
  if (!grpc_auth_context_peer_is_authenticated(ctx.get())) {
    LOG(ERROR) << "Invalid unauthenticated peer.";
    ctx.reset(DEBUG_LOCATION, "test");
    return nullptr;
  }
  return ctx;
}

}
}

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_alts_channel_security_connector_create(
    grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* target_name) {
  if (channel_creds == nullptr || target_name == nullptr) {
    LOG(ERROR)
        << "Invalid arguments to grpc_alts_channel_security_connector_create()";
    return nullptr;
  }
  return grpc_core::MakeRefCounted<grpc_alts_channel_security_connector>(
      std::move(channel_creds), std::move(request_metadata_creds), target_name);
}

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_alts_server_security_connector_create(
    grpc_core::RefCountedPtr<grpc_server_credentials> server_creds) {
  if (server_creds == nullptr) {
    LOG(ERROR)
        << "Invalid arguments to grpc_alts_server_security_connector_create()";
    return nullptr;
  }
  return grpc_core::MakeRefCounted<grpc_alts_server_security_connector>(
      std::move(server_creds));
}
