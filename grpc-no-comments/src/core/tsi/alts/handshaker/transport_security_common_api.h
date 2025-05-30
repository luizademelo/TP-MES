
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_TRANSPORT_SECURITY_COMMON_API_H
#define GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_TRANSPORT_SECURITY_COMMON_API_H

#include <grpc/slice.h>
#include <grpc/slice_buffer.h>
#include <grpc/support/alloc.h>
#include <grpc/support/port_platform.h>

#include "src/core/util/crash.h"
#include "src/proto/grpc/gcp/transport_security_common.upb.h"

typedef struct _grpc_gcp_RpcProtocolVersions_Version {
  uint32_t major;
  uint32_t minor;
} grpc_gcp_rpc_protocol_versions_version;

typedef struct _grpc_gcp_RpcProtocolVersions {
  grpc_gcp_rpc_protocol_versions_version max_rpc_version;
  grpc_gcp_rpc_protocol_versions_version min_rpc_version;
} grpc_gcp_rpc_protocol_versions;

bool grpc_gcp_rpc_protocol_versions_set_max(
    grpc_gcp_rpc_protocol_versions* versions, uint32_t max_major,
    uint32_t max_minor);

bool grpc_gcp_rpc_protocol_versions_set_min(
    grpc_gcp_rpc_protocol_versions* versions, uint32_t min_major,
    uint32_t min_minor);

bool grpc_gcp_rpc_protocol_versions_encode(
    const grpc_gcp_rpc_protocol_versions* versions, grpc_slice* slice);

bool grpc_gcp_rpc_protocol_versions_encode(
    const grpc_gcp_RpcProtocolVersions* versions, upb_Arena* arena,
    grpc_slice* slice);

bool grpc_gcp_rpc_protocol_versions_decode(
    const grpc_slice& slice, grpc_gcp_rpc_protocol_versions* versions);

void grpc_gcp_rpc_protocol_versions_assign_from_upb(
    grpc_gcp_rpc_protocol_versions* versions,
    const grpc_gcp_RpcProtocolVersions* value);

void grpc_gcp_RpcProtocolVersions_assign_from_struct(
    grpc_gcp_RpcProtocolVersions* versions, upb_Arena* arena,
    const grpc_gcp_rpc_protocol_versions* value);

bool grpc_gcp_rpc_protocol_versions_copy(
    const grpc_gcp_rpc_protocol_versions* src,
    grpc_gcp_rpc_protocol_versions* dst);

bool grpc_gcp_rpc_protocol_versions_check(
    const grpc_gcp_rpc_protocol_versions* local_versions,
    const grpc_gcp_rpc_protocol_versions* peer_versions,
    grpc_gcp_rpc_protocol_versions_version* highest_common_version);

namespace grpc_core {
namespace internal {

int grpc_gcp_rpc_protocol_version_compare(
    const grpc_gcp_rpc_protocol_versions_version* v1,
    const grpc_gcp_rpc_protocol_versions_version* v2);

}
}

#endif
