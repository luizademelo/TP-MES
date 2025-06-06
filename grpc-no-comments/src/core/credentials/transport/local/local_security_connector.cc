
// Copyright 2018 gRPC authors.

#include "src/core/credentials/transport/local/local_security_connector.h"

#include <grpc/grpc.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>
#include <string.h>

#include <optional>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/match.h"
#include "absl/strings/string_view.h"
#include "src/core/client_channel/client_channel_filter.h"
#include "src/core/credentials/transport/local/local_credentials.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/address_utils/parse_address.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/experiments/experiments.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/iomgr/sockaddr.h"
#include "src/core/lib/iomgr/socket_utils.h"
#include "src/core/lib/iomgr/unix_sockets_posix.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/local_transport_security.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/uri.h"

#define GRPC_UDS_URI_PATTERN "unix:"
#define GRPC_ABSTRACT_UDS_URI_PATTERN "unix-abstract:"
#define GRPC_LOCAL_TRANSPORT_SECURITY_TYPE "local"

namespace {

grpc_core::RefCountedPtr<grpc_auth_context> local_auth_context_create(
    const tsi_peer* peer) {

  grpc_core::RefCountedPtr<grpc_auth_context> ctx =
      grpc_core::MakeRefCounted<grpc_auth_context>(nullptr);
  grpc_auth_context_add_cstring_property(
      ctx.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
      GRPC_LOCAL_TRANSPORT_SECURITY_TYPE);
  CHECK(grpc_auth_context_set_peer_identity_property_name(
            ctx.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME) == 1);
  CHECK_EQ(peer->property_count, 1u);
  const tsi_peer_property* prop = &peer->properties[0];
  CHECK_NE(prop, nullptr);
  CHECK_EQ(strcmp(prop->name, TSI_SECURITY_LEVEL_PEER_PROPERTY), 0);
  grpc_auth_context_add_property(ctx.get(),
                                 GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME,
                                 prop->value.data, prop->value.length);
  return ctx;
}

void local_check_peer(tsi_peer peer, grpc_endpoint* ep,
                      grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                      grpc_closure* on_peer_checked,
                      grpc_local_connect_type type) {
  grpc_resolved_address resolved_addr;
  bool is_endpoint_local = false;
  absl::string_view local_addr = grpc_endpoint_get_local_address(ep);
  absl::StatusOr<grpc_core::URI> uri = grpc_core::URI::Parse(local_addr);
  if (!uri.ok() || !grpc_parse_uri(*uri, &resolved_addr)) {
    LOG(ERROR) << "Could not parse endpoint address: " << local_addr;
  } else {
    grpc_resolved_address addr_normalized;
    grpc_resolved_address* addr =
        grpc_sockaddr_is_v4mapped(&resolved_addr, &addr_normalized)
            ? &addr_normalized
            : &resolved_addr;
    grpc_sockaddr* sock_addr = reinterpret_cast<grpc_sockaddr*>(&addr->addr);

    if (type == UDS && grpc_is_unix_socket(addr)) {
      is_endpoint_local = true;

    } else if (type == LOCAL_TCP && sock_addr->sa_family == GRPC_AF_INET) {
      const grpc_sockaddr_in* addr4 =
          reinterpret_cast<const grpc_sockaddr_in*>(sock_addr);
      if (grpc_htonl(addr4->sin_addr.s_addr) == INADDR_LOOPBACK) {
        is_endpoint_local = true;
      }

    } else if (type == LOCAL_TCP && sock_addr->sa_family == GRPC_AF_INET6) {
      const grpc_sockaddr_in6* addr6 =
          reinterpret_cast<const grpc_sockaddr_in6*>(addr);
      if (memcmp(&addr6->sin6_addr, &in6addr_loopback,
                 sizeof(in6addr_loopback)) == 0) {
        is_endpoint_local = true;
      }
    }
  }
  grpc_error_handle error;
  if (!is_endpoint_local) {
    error =
        GRPC_ERROR_CREATE("Endpoint is neither UDS or TCP loopback address.");
    grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
    return;
  }

  size_t new_property_count = peer.property_count + 1;
  tsi_peer_property* new_properties = static_cast<tsi_peer_property*>(
      gpr_zalloc(sizeof(*new_properties) * new_property_count));
  for (size_t i = 0; i < peer.property_count; i++) {
    new_properties[i] = peer.properties[i];
  }
  if (peer.properties != nullptr) gpr_free(peer.properties);
  peer.properties = new_properties;

  const char* security_level;
  if (grpc_core::IsLocalConnectorSecureEnabled()) {
    security_level = tsi_security_level_to_string(
        type == UDS ? TSI_PRIVACY_AND_INTEGRITY : TSI_SECURITY_NONE);
  } else {
    security_level = tsi_security_level_to_string(TSI_PRIVACY_AND_INTEGRITY);
  }
  tsi_result result = tsi_construct_string_peer_property_from_cstring(
      TSI_SECURITY_LEVEL_PEER_PROPERTY, security_level,
      &peer.properties[peer.property_count]);
  if (result != TSI_OK) return;
  peer.property_count++;

  *auth_context = local_auth_context_create(&peer);
  tsi_peer_destruct(&peer);
  error = *auth_context != nullptr
              ? absl::OkStatus()
              : GRPC_ERROR_CREATE("Could not create local auth context");
  grpc_core::ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, error);
}

class grpc_local_channel_security_connector final
    : public grpc_channel_security_connector {
 public:
  grpc_local_channel_security_connector(
      grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
      grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
      const char* target_name)
      : grpc_channel_security_connector({}, std::move(channel_creds),
                                        std::move(request_metadata_creds)),
        target_name_(gpr_strdup(target_name)) {}

  ~grpc_local_channel_security_connector() override { gpr_free(target_name_); }

  void add_handshakers(
      const grpc_core::ChannelArgs& args,
      grpc_pollset_set* ,
      grpc_core::HandshakeManager* handshake_manager) override {
    tsi_handshaker* handshaker = nullptr;
    CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
    handshake_manager->Add(
        grpc_core::SecurityHandshakerCreate(handshaker, this, args));
  }

  int cmp(const grpc_security_connector* other_sc) const override {
    auto* other =
        reinterpret_cast<const grpc_local_channel_security_connector*>(
            other_sc);
    int c = channel_security_connector_cmp(other);
    if (c != 0) return c;
    return strcmp(target_name_, other->target_name_);
  }

  void check_peer(tsi_peer peer, grpc_endpoint* ep,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    grpc_local_credentials* creds =
        reinterpret_cast<grpc_local_credentials*>(mutable_channel_creds());
    local_check_peer(peer, ep, auth_context, on_peer_checked,
                     creds->connect_type());
  }

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  grpc_core::ArenaPromise<absl::Status> CheckCallHost(
      absl::string_view host, grpc_auth_context*) override {
    if (host.empty() || host != target_name_) {
      return grpc_core::Immediate(absl::UnauthenticatedError(
          "local call host does not match target name"));
    }
    return grpc_core::ImmediateOkStatus();
  }

  const char* target_name() const { return target_name_; }

 private:
  char* target_name_;
};

class grpc_local_server_security_connector final
    : public grpc_server_security_connector {
 public:
  explicit grpc_local_server_security_connector(
      grpc_core::RefCountedPtr<grpc_server_credentials> server_creds)
      : grpc_server_security_connector({}, std::move(server_creds)) {}
  ~grpc_local_server_security_connector() override = default;

  void add_handshakers(
      const grpc_core::ChannelArgs& args,
      grpc_pollset_set* ,
      grpc_core::HandshakeManager* handshake_manager) override {
    tsi_handshaker* handshaker = nullptr;
    CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
    handshake_manager->Add(
        grpc_core::SecurityHandshakerCreate(handshaker, this, args));
  }

  void check_peer(tsi_peer peer, grpc_endpoint* ep,
                  const grpc_core::ChannelArgs& ,
                  grpc_core::RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override {
    grpc_local_server_credentials* creds =
        static_cast<grpc_local_server_credentials*>(mutable_server_creds());
    local_check_peer(peer, ep, auth_context, on_peer_checked,
                     creds->connect_type());
  }

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  int cmp(const grpc_security_connector* other) const override {
    return server_security_connector_cmp(
        static_cast<const grpc_server_security_connector*>(other));
  }
};
}

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_local_channel_security_connector_create(
    grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const grpc_core::ChannelArgs& args, const char* target_name) {
  if (channel_creds == nullptr || target_name == nullptr) {
    LOG(ERROR) << "Invalid arguments to "
                  "grpc_local_channel_security_connector_create()";
    return nullptr;
  }

  grpc_local_credentials* creds =
      static_cast<grpc_local_credentials*>(channel_creds.get());
  absl::string_view server_uri_str =
      args.GetString(GRPC_ARG_SERVER_URI).value_or("");
  if (creds->connect_type() == UDS &&
      !absl::StartsWith(server_uri_str, GRPC_UDS_URI_PATTERN) &&
      !absl::StartsWith(server_uri_str, GRPC_ABSTRACT_UDS_URI_PATTERN)) {
    LOG(ERROR) << "Invalid UDS target name to "
                  "grpc_local_channel_security_connector_create()";
    return nullptr;
  }
  return grpc_core::MakeRefCounted<grpc_local_channel_security_connector>(
      channel_creds, request_metadata_creds, target_name);
}

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_local_server_security_connector_create(
    grpc_core::RefCountedPtr<grpc_server_credentials> server_creds) {
  if (server_creds == nullptr) {
    LOG(ERROR)
        << "Invalid arguments to grpc_local_server_security_connector_create()";
    return nullptr;
  }
  return grpc_core::MakeRefCounted<grpc_local_server_security_connector>(
      std::move(server_creds));
}
