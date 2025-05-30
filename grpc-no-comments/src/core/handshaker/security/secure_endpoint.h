
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_SECURITY_SECURE_ENDPOINT_H
#define GRPC_SRC_CORE_HANDSHAKER_SECURITY_SECURE_ENDPOINT_H

#include <grpc/grpc.h>
#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/util/orphanable.h"

#define GRPC_ARG_DECRYPTION_OFFLOAD_THRESHOLD \
  "grpc.secure_endpoint.decryption_offload_threshold"
#define GRPC_ARG_ENCRYPTION_OFFLOAD_THRESHOLD \
  "grpc.secure_endpoint.encryption_offload_threshold"
#define GRPC_ARG_ENCRYPTION_OFFLOAD_MAX_BUFFERED_WRITES \
  "grpc.secure_endpoint.encryption_offload_max_buffered_writes"

grpc_core::OrphanablePtr<grpc_endpoint> grpc_secure_endpoint_create(
    struct tsi_frame_protector* protector,
    struct tsi_zero_copy_grpc_protector* zero_copy_protector,
    grpc_core::OrphanablePtr<grpc_endpoint> to_wrap,
    grpc_slice* leftover_slices, size_t leftover_nslices,
    const grpc_core::ChannelArgs& channel_args);

grpc_core::OrphanablePtr<grpc_endpoint> grpc_legacy_secure_endpoint_create(
    struct tsi_frame_protector* protector,
    struct tsi_zero_copy_grpc_protector* zero_copy_protector,
    grpc_core::OrphanablePtr<grpc_endpoint> to_wrap,
    grpc_slice* leftover_slices, const grpc_channel_args* channel_args,
    size_t leftover_nslices);

#endif
