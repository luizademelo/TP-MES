
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_FRAME_PROTECTOR_H
#define GRPC_SRC_CORE_TSI_ALTS_FRAME_PROTECTOR_ALTS_FRAME_PROTECTOR_H

#include <grpc/support/port_platform.h>
#include <stdbool.h>

#include "src/core/tsi/transport_security_interface.h"

typedef struct alts_frame_protector alts_frame_protector;

/// TODO: Add a parameter to the interface to support the use of

tsi_result alts_create_frame_protector(const uint8_t* key, size_t key_size,
                                       bool is_client, bool is_rekey,
                                       size_t* max_protected_frame_size,
                                       tsi_frame_protector** self);

#endif
