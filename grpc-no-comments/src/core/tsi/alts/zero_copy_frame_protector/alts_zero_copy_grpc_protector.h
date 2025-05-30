
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_ZERO_COPY_GRPC_PROTECTOR_H
#define GRPC_SRC_CORE_TSI_ALTS_ZERO_COPY_FRAME_PROTECTOR_ALTS_ZERO_COPY_GRPC_PROTECTOR_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/tsi/alts/crypt/gsec.h"
#include "src/core/tsi/transport_security_interface.h"

tsi_result alts_zero_copy_grpc_protector_create(
    const grpc_core::GsecKeyFactoryInterface& key_factory, bool is_client,
    bool is_integrity_only, bool enable_extra_copy,
    size_t* max_protected_frame_size, tsi_zero_copy_grpc_protector** protector);

#endif
