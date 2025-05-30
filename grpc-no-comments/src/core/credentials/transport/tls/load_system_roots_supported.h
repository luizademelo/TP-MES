
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_LOAD_SYSTEM_ROOTS_SUPPORTED_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_LOAD_SYSTEM_ROOTS_SUPPORTED_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>

#if defined(GPR_LINUX) || defined(GPR_FREEBSD) || defined(GPR_APPLE)

namespace grpc_core {

grpc_slice CreateRootCertsBundle(const char* certs_directory);

void GetAbsoluteFilePath(const char* valid_file_dir,
                         const char* file_entry_name, char* path_buffer);

}

#endif
#endif
