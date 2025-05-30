
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_INSECURE_INSECURE_SECURITY_CONNECTOR_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_INSECURE_INSECURE_SECURITY_CONNECTOR_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

extern const char kInsecureTransportSecurityType[];

RefCountedPtr<grpc_auth_context> TestOnlyMakeInsecureAuthContext();

class InsecureChannelSecurityConnector
    : public grpc_channel_security_connector {
 public:
  InsecureChannelSecurityConnector(
      RefCountedPtr<grpc_channel_credentials> channel_creds,
      RefCountedPtr<grpc_call_credentials> request_metadata_creds)
      : grpc_channel_security_connector("", std::move(channel_creds),
                                        std::move(request_metadata_creds)) {}

  ArenaPromise<absl::Status> CheckCallHost(
      absl::string_view host, grpc_auth_context* auth_context) override;

  void add_handshakers(const ChannelArgs& args,
                       grpc_pollset_set* ,
                       HandshakeManager* handshake_manager) override;

  void check_peer(tsi_peer peer, grpc_endpoint* ep, const ChannelArgs& ,
                  RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override;

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  int cmp(const grpc_security_connector* other_sc) const override;
};

class InsecureServerSecurityConnector : public grpc_server_security_connector {
 public:
  explicit InsecureServerSecurityConnector(
      RefCountedPtr<grpc_server_credentials> server_creds)
      : grpc_server_security_connector("" ,
                                       std::move(server_creds)) {}

  void add_handshakers(const ChannelArgs& args,
                       grpc_pollset_set* ,
                       HandshakeManager* handshake_manager) override;

  void check_peer(tsi_peer peer, grpc_endpoint* ep, const ChannelArgs& ,
                  RefCountedPtr<grpc_auth_context>* auth_context,
                  grpc_closure* on_peer_checked) override;

  void cancel_check_peer(grpc_closure* ,
                         grpc_error_handle ) override {}

  int cmp(const grpc_security_connector* other) const override;
};

}

#endif
