
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_GRPC_ALTS_CREDENTIALS_OPTIONS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_ALTS_GRPC_ALTS_CREDENTIALS_OPTIONS_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include "src/core/tsi/alts/handshaker/transport_security_common_api.h"

typedef struct grpc_alts_credentials_options_vtable {
  grpc_alts_credentials_options* (*copy)(
      const grpc_alts_credentials_options* options);
  void (*destruct)(grpc_alts_credentials_options* options);
} grpc_alts_credentials_options_vtable;

struct grpc_alts_credentials_options {
  const struct grpc_alts_credentials_options_vtable* vtable;
  grpc_gcp_rpc_protocol_versions rpc_versions;
};

typedef struct target_service_account {
  struct target_service_account* next;
  char* data;
} target_service_account;

typedef struct grpc_alts_credentials_client_options {
  grpc_alts_credentials_options base;
  target_service_account* target_account_list_head;
} grpc_alts_credentials_client_options;

typedef struct grpc_alts_credentials_server_options {
  grpc_alts_credentials_options base;
} grpc_alts_credentials_server_options;

grpc_alts_credentials_options* grpc_alts_credentials_options_copy(
    const grpc_alts_credentials_options* options);

#endif
