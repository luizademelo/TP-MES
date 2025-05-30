
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_CALL_CREDS_UTIL_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_CALL_CREDS_UTIL_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <string>

#include "src/core/credentials/call/call_credentials.h"
#include "src/core/lib/transport/transport.h"

namespace grpc_core {

std::string MakeJwtServiceUrl(
    const ClientMetadataHandle& initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args);

grpc_auth_metadata_context MakePluginAuthMetadataContext(
    const ClientMetadataHandle& initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args);

}

#endif
