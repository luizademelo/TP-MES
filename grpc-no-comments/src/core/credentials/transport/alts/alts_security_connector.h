
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_ALTS_SECURITY_CONNECTOR_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_ALTS_SECURITY_CONNECTOR_H
#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "src/core/credentials/transport/security_connector.h"
#include "src/core/tsi/alts/handshaker/transport_security_common_api.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/ref_counted_ptr.h"

#define GRPC_ALTS_TRANSPORT_SECURITY_TYPE "alts"

grpc_core::RefCountedPtr<grpc_channel_security_connector>
grpc_alts_channel_security_connector_create(
    grpc_core::RefCountedPtr<grpc_channel_credentials> channel_creds,
    grpc_core::RefCountedPtr<grpc_call_credentials> request_metadata_creds,
    const char* target_name);

grpc_core::RefCountedPtr<grpc_server_security_connector>
grpc_alts_server_security_connector_create(
    grpc_core::RefCountedPtr<grpc_server_credentials> server_creds);

void grpc_alts_set_rpc_protocol_versions(
    grpc_gcp_rpc_protocol_versions* rpc_versions);

namespace grpc_core {
namespace internal {

RefCountedPtr<grpc_auth_context> grpc_alts_auth_context_from_tsi_peer(
    const tsi_peer* peer);

}
}

#endif
