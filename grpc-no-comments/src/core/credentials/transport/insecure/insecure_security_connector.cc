
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/insecure/insecure_security_connector.h"

#include <grpc/grpc_security_constants.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/log/check.h"
#include "src/core/handshaker/security/security_handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/lib/promise/promise.h"
#include "src/core/transport/auth_context.h"
#include "src/core/tsi/local_transport_security.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

const char kInsecureTransportSecurityType[] = "insecure";

namespace {

RefCountedPtr<grpc_auth_context> MakeAuthContext() {
  auto ctx = MakeRefCounted<grpc_auth_context>(nullptr);
  grpc_auth_context_add_cstring_property(
      ctx.get(), GRPC_TRANSPORT_SECURITY_TYPE_PROPERTY_NAME,
      kInsecureTransportSecurityType);
  const char* security_level = tsi_security_level_to_string(TSI_SECURITY_NONE);
  grpc_auth_context_add_property(ctx.get(),
                                 GRPC_TRANSPORT_SECURITY_LEVEL_PROPERTY_NAME,
                                 security_level, strlen(security_level));
  return ctx;
}

}

RefCountedPtr<grpc_auth_context> TestOnlyMakeInsecureAuthContext() {
  return MakeAuthContext();
}

ArenaPromise<absl::Status> InsecureChannelSecurityConnector::CheckCallHost(
    absl::string_view, grpc_auth_context*) {
  return ImmediateOkStatus();
}

void InsecureChannelSecurityConnector::add_handshakers(
    const ChannelArgs& args, grpc_pollset_set* ,
    HandshakeManager* handshake_manager) {
  tsi_handshaker* handshaker = nullptr;

  CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
  handshake_manager->Add(SecurityHandshakerCreate(handshaker, this, args));
}

void InsecureChannelSecurityConnector::check_peer(
    tsi_peer peer, grpc_endpoint* , const ChannelArgs& ,
    RefCountedPtr<grpc_auth_context>* auth_context,
    grpc_closure* on_peer_checked) {
  *auth_context = MakeAuthContext();
  tsi_peer_destruct(&peer);
  ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, absl::OkStatus());
}

int InsecureChannelSecurityConnector::cmp(
    const grpc_security_connector* other_sc) const {
  return channel_security_connector_cmp(
      static_cast<const grpc_channel_security_connector*>(other_sc));
}

void InsecureServerSecurityConnector::add_handshakers(
    const ChannelArgs& args, grpc_pollset_set* ,
    HandshakeManager* handshake_manager) {
  tsi_handshaker* handshaker = nullptr;

  CHECK(tsi_local_handshaker_create(&handshaker) == TSI_OK);
  handshake_manager->Add(SecurityHandshakerCreate(handshaker, this, args));
}

void InsecureServerSecurityConnector::check_peer(
    tsi_peer peer, grpc_endpoint* , const ChannelArgs& ,
    RefCountedPtr<grpc_auth_context>* auth_context,
    grpc_closure* on_peer_checked) {
  *auth_context = MakeAuthContext();
  tsi_peer_destruct(&peer);
  ExecCtx::Run(DEBUG_LOCATION, on_peer_checked, absl::OkStatus());
}

int InsecureServerSecurityConnector::cmp(
    const grpc_security_connector* other) const {
  return server_security_connector_cmp(
      static_cast<const grpc_server_security_connector*>(other));
}

}
