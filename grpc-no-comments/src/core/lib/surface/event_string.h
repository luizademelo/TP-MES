
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_SURFACE_EVENT_STRING_H
#define GRPC_SRC_CORE_LIB_SURFACE_EVENT_STRING_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <string>

std::string grpc_event_string(grpc_event* ev);

#endif
