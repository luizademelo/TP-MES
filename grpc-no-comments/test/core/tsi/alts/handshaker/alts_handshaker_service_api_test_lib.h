
// Copyright 2018 gRPC authors.

#ifndef GRPC_TEST_CORE_TSI_ALTS_HANDSHAKER_ALTS_HANDSHAKER_SERVICE_API_TEST_LIB_H
#define GRPC_TEST_CORE_TSI_ALTS_HANDSHAKER_ALTS_HANDSHAKER_SERVICE_API_TEST_LIB_H

#include "src/core/tsi/alts/handshaker/transport_security_common_api.h"
#include "src/proto/grpc/gcp/handshaker.upb.h"

bool grpc_gcp_handshaker_resp_set_peer_rpc_versions(
    grpc_gcp_HandshakerResp* resp, upb_Arena* arena, uint32_t max_major,
    uint32_t max_minor, uint32_t min_major, uint32_t min_minor);

grpc_gcp_HandshakerReq* grpc_gcp_handshaker_req_decode(grpc_slice slice,
                                                       upb_Arena* arena);

bool grpc_gcp_handshaker_resp_equals(const grpc_gcp_HandshakerResp* l_resp,
                                     const grpc_gcp_HandshakerResp* r_resp);

bool grpc_gcp_handshaker_resp_result_equals(
    const grpc_gcp_HandshakerResult* l_result,
    const grpc_gcp_HandshakerResult* r_result);

bool grpc_gcp_handshaker_resp_status_equals(
    const grpc_gcp_HandshakerStatus* l_status,
    const grpc_gcp_HandshakerStatus* r_status);

#endif
