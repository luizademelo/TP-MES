
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_EV_APPLE_H
#define GRPC_SRC_CORE_LIB_IOMGR_EV_APPLE_H

#include <grpc/support/port_platform.h>

#ifdef GRPC_APPLE_EV

#include <CoreFoundation/CoreFoundation.h>

#include "src/core/lib/iomgr/pollset.h"
#include "src/core/lib/iomgr/pollset_set.h"

void grpc_apple_register_read_stream(CFReadStreamRef read_stream,
                                     dispatch_queue_t dispatch_queue);

void grpc_apple_register_write_stream(CFWriteStreamRef write_stream,
                                      dispatch_queue_t dispatch_queue);

extern grpc_pollset_vtable grpc_apple_pollset_vtable;

extern grpc_pollset_set_vtable grpc_apple_pollset_set_vtable;

#endif

#endif
