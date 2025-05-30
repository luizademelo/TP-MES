
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_JSON_UTIL_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_JSON_UTIL_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/iomgr/error.h"
#include "src/core/util/json/json.h"

#define GRPC_AUTH_JSON_TYPE_INVALID "invalid"
#define GRPC_AUTH_JSON_TYPE_SERVICE_ACCOUNT "service_account"
#define GRPC_AUTH_JSON_TYPE_AUTHORIZED_USER "authorized_user"
#define GRPC_AUTH_JSON_TYPE_EXTERNAL_ACCOUNT "external_account"

const char* grpc_json_get_string_property(const grpc_core::Json& json,
                                          const char* prop_name,
                                          grpc_error_handle* error);

bool grpc_copy_json_string_property(const grpc_core::Json& json,
                                    const char* prop_name, char** copied_value);

#endif
