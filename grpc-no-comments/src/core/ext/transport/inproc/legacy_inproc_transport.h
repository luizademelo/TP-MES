// Copyright 2017 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_INPROC_LEGACY_INPROC_TRANSPORT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_INPROC_LEGACY_INPROC_TRANSPORT_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "src/core/lib/debug/trace.h"

grpc_channel* grpc_legacy_inproc_channel_create(grpc_server* server,
                                                const grpc_channel_args* args,
                                                void* reserved);

#endif
