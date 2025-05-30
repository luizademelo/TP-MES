
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_CFSTREAM_H
#define GRPC_SRC_CORE_LIB_IOMGR_ENDPOINT_CFSTREAM_H

#include <grpc/support/port_platform.h>

#ifdef GRPC_CFSTREAM

#import <CoreFoundation/CoreFoundation.h>

#include "src/core/lib/debug/trace.h"
#include "src/core/lib/iomgr/cfstream_handle.h"
#include "src/core/lib/iomgr/endpoint.h"

grpc_endpoint* grpc_cfstream_endpoint_create(CFReadStreamRef read_stream,
                                             CFWriteStreamRef write_stream,
                                             const char* peer_string,
                                             CFStreamHandle* stream_sync);

#endif

#endif
