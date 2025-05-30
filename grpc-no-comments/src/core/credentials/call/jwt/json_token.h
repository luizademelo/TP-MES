
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JSON_TOKEN_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JSON_TOKEN_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <openssl/crypto.h>

#include "src/core/util/json/json.h"

#define GRPC_JWT_OAUTH2_AUDIENCE "https://oauth2.googleapis.com/token"

struct grpc_auth_json_key {
  const char* type;
  char* private_key_id;
  char* client_id;
  char* client_email;
#if OPENSSL_VERSION_NUMBER < 0x30000000L
  RSA* private_key;
#else
  EVP_PKEY* private_key;
#endif
};

int grpc_auth_json_key_is_valid(const grpc_auth_json_key* json_key);

grpc_auth_json_key grpc_auth_json_key_create_from_string(
    const char* json_string);

grpc_auth_json_key grpc_auth_json_key_create_from_json(
    const grpc_core::Json& json);

void grpc_auth_json_key_destruct(grpc_auth_json_key* json_key);

char* grpc_jwt_encode_and_sign(const grpc_auth_json_key* json_key,
                               const char* audience,
                               gpr_timespec token_lifetime, const char* scope);

typedef char* (*grpc_jwt_encode_and_sign_override)(
    const grpc_auth_json_key* json_key, const char* audience,
    gpr_timespec token_lifetime, const char* scope);

void grpc_jwt_encode_and_sign_set_override(
    grpc_jwt_encode_and_sign_override func);

#endif
