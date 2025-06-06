
// Copyright 2015 gRPC authors.

#include <grpc/credentials.h>
#include <grpc/slice.h>
#include <grpc/support/alloc.h>
#include <stdio.h>
#include <string.h>

#include "src/core/credentials/call/jwt/jwt_credentials.h"
#include "src/core/util/crash.h"
#include "test/core/test_util/cmdline.h"
#include "test/core/test_util/tls_utils.h"

void create_jwt(const char* json_key_file_path, const char* service_url,
                const char* scope) {
  grpc_auth_json_key key;
  char* jwt;
  std::string json_key_data =
      grpc_core::testing::GetFileContents(json_key_file_path);
  key = grpc_auth_json_key_create_from_string(json_key_data.c_str());
  if (!grpc_auth_json_key_is_valid(&key)) {
    fprintf(stderr, "Could not parse json key.\n");
    fflush(stderr);
    exit(1);
  }
  jwt = grpc_jwt_encode_and_sign(
      &key, service_url == nullptr ? GRPC_JWT_OAUTH2_AUDIENCE : service_url,
      grpc_max_auth_token_lifetime(), scope);
  grpc_auth_json_key_destruct(&key);
  if (jwt == nullptr) {
    fprintf(stderr, "Could not create JWT.\n");
    fflush(stderr);
    exit(1);
  }
  fprintf(stdout, "%s\n", jwt);
  gpr_free(jwt);
}

int main(int argc, char** argv) {
  const char* scope = nullptr;
  const char* json_key_file_path = nullptr;
  const char* service_url = nullptr;
  grpc_init();
  gpr_cmdline* cl = gpr_cmdline_create("create_jwt");
  gpr_cmdline_add_string(cl, "json_key", "File path of the json key.",
                         &json_key_file_path);
  gpr_cmdline_add_string(cl, "scope",
                         "OPTIONAL Space delimited permissions. Mutually "
                         "exclusive with service_url",
                         &scope);
  gpr_cmdline_add_string(cl, "service_url",
                         "OPTIONAL service URL. Mutually exclusive with scope.",
                         &service_url);
  gpr_cmdline_parse(cl, argc, argv);

  if (json_key_file_path == nullptr) {
    fprintf(stderr, "Missing --json_key option.\n");
    fflush(stderr);
    exit(1);
  }
  if (scope != nullptr) {
    if (service_url != nullptr) {
      fprintf(stderr,
              "Options --scope and --service_url are mutually exclusive.\n");
      fflush(stderr);
      exit(1);
    }
  } else if (service_url == nullptr) {
    fprintf(stderr, "Need one of --service_url or --scope options.\n");
    fflush(stderr);
    exit(1);
  }

  create_jwt(json_key_file_path, service_url, scope);

  gpr_cmdline_destroy(cl);
  grpc_shutdown();
  return 0;
}
