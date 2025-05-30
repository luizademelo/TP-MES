
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_TSI_UTILS_H
#define GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_TSI_UTILS_H

#include <grpc/byte_buffer.h>
#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/transport_security_interface.h"
#include "src/proto/grpc/gcp/handshaker.upb.h"

tsi_result alts_tsi_utils_convert_to_tsi_result(grpc_status_code code);

grpc_gcp_HandshakerResp* alts_tsi_utils_deserialize_response(
    grpc_byte_buffer* resp_buffer, upb_Arena* arena);

#endif
