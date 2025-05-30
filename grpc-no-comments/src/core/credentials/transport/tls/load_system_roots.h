
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_LOAD_SYSTEM_ROOTS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_LOAD_SYSTEM_ROOTS_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

namespace grpc_core {

grpc_slice LoadSystemRootCerts();

}

#endif
