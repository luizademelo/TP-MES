
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_LOCAL_TRANSPORT_SECURITY_H
#define GRPC_SRC_CORE_TSI_LOCAL_TRANSPORT_SECURITY_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/transport_security.h"
#include "src/core/tsi/transport_security_interface.h"

#define TSI_LOCAL_NUM_OF_PEER_PROPERTIES 1
#define TSI_LOCAL_PROCESS_ID_PEER_PROPERTY "process_id"

tsi_result tsi_local_handshaker_create(tsi_handshaker** self);

#endif
