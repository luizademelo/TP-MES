
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CORE_CREDENTIALS_CALL_OAUTH2_OAUTH2_UTILS_H
#define GRPC_TEST_CORE_CREDENTIALS_CALL_OAUTH2_OAUTH2_UTILS_H

#include "src/core/credentials/call/call_credentials.h"

char* grpc_test_fetch_oauth2_token_with_credentials(
    grpc_call_credentials* creds);

#endif
