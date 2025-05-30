
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_TSI_HANDSHAKER_H
#define GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_TSI_HANDSHAKER_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/credentials/transport/alts/grpc_alts_credentials_options.h"
#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/tsi/alts/handshaker/alts_handshaker_client.h"
#include "src/core/tsi/transport_security.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/proto/grpc/gcp/altscontext.upb.h"
#include "src/proto/grpc/gcp/handshaker.upb.h"

#define TSI_ALTS_SERVICE_ACCOUNT_PEER_PROPERTY "service_account"
#define TSI_ALTS_CERTIFICATE_TYPE "ALTS"
#define TSI_ALTS_RPC_VERSIONS "rpc_versions"
#define TSI_ALTS_CONTEXT "alts_context"
#define TSI_ALTS_NEGOTIATED_TRANSPORT_PROTOCOL \
  "alts_negotiated_transport_protocol"

inline const size_t kTsiAltsMinNumOfPeerProperties = 5;

const size_t kTsiAltsMinFrameSize = 16 * 1024;
const size_t kTsiAltsMaxFrameSize = 1024 * 1024;

typedef struct alts_tsi_handshaker alts_tsi_handshaker;

tsi_result alts_tsi_handshaker_create(
    const grpc_alts_credentials_options* options, const char* target_name,
    const char* handshaker_service_url, bool is_client,
    grpc_pollset_set* interested_parties, tsi_handshaker** self,
    size_t user_specified_max_frame_size,
    std::optional<std::string> preferred_transport_protocols);

tsi_result alts_tsi_handshaker_result_create(grpc_gcp_HandshakerResp* resp,
                                             bool is_client,
                                             tsi_handshaker_result** result);

void alts_tsi_handshaker_result_set_unused_bytes(tsi_handshaker_result* result,
                                                 grpc_slice* recv_bytes,
                                                 size_t bytes_consumed);

bool alts_tsi_handshaker_has_shutdown(alts_tsi_handshaker* handshaker);

#endif
