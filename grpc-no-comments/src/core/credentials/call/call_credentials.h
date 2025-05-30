
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_CALL_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_CALL_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc.h>
#include <grpc/grpc_security.h>
#include <grpc/grpc_security_constants.h>
#include <grpc/impl/grpc_types.h>
#include <grpc/support/port_platform.h>

#include <string>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/transport/auth_context.h"
#include "src/core/util/crash.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"

typedef enum {
  GRPC_CREDENTIALS_OK = 0,
  GRPC_CREDENTIALS_ERROR
} grpc_credentials_status;

#define GRPC_AUTHORIZATION_METADATA_KEY "authorization"
#define GRPC_IAM_AUTHORIZATION_TOKEN_METADATA_KEY \
  "x-goog-iam-authorization-token"
#define GRPC_IAM_AUTHORITY_SELECTOR_METADATA_KEY "x-goog-iam-authority-selector"

#define GRPC_SECURE_TOKEN_REFRESH_THRESHOLD_SECS 60

#define GRPC_COMPUTE_ENGINE_METADATA_HOST "metadata.google.internal."
#define GRPC_COMPUTE_ENGINE_METADATA_TOKEN_PATH \
  "/computeMetadata/v1/instance/service-accounts/default/token"

#define GRPC_GOOGLE_OAUTH2_SERVICE_HOST "oauth2.googleapis.com"
#define GRPC_GOOGLE_OAUTH2_SERVICE_TOKEN_PATH "/token"

#define GRPC_SERVICE_ACCOUNT_POST_BODY_PREFIX                         \
  "grant_type=urn%3Aietf%3Aparams%3Aoauth%3Agrant-type%3Ajwt-bearer&" \
  "assertion="

#define GRPC_REFRESH_TOKEN_POST_BODY_FORMAT_STRING \
  "client_id=%s&client_secret=%s&refresh_token=%s&grant_type=refresh_token"

std::string grpc_get_well_known_google_credentials_file_path(void);

std::string grpc_get_well_known_google_credentials_file_path_impl(void);

typedef std::string (*grpc_well_known_credentials_path_getter)(void);
void grpc_override_well_known_credentials_path_getter(
    grpc_well_known_credentials_path_getter getter);

namespace grpc_core {
using CredentialsMetadataArray = std::vector<std::pair<Slice, Slice>>;
}

struct grpc_call_credentials
    : public grpc_core::DualRefCounted<grpc_call_credentials> {
 public:

  struct GetRequestMetadataArgs {
    grpc_core::RefCountedPtr<grpc_channel_security_connector>
        security_connector;
    grpc_core::RefCountedPtr<grpc_auth_context> auth_context;
  };

  explicit grpc_call_credentials(
      grpc_security_level min_security_level = GRPC_PRIVACY_AND_INTEGRITY)
      : min_security_level_(min_security_level) {}

  ~grpc_call_credentials() override = default;

  virtual grpc_core::ArenaPromise<
      absl::StatusOr<grpc_core::ClientMetadataHandle>>
  GetRequestMetadata(grpc_core::ClientMetadataHandle initial_metadata,
                     const GetRequestMetadataArgs* args) = 0;

  virtual grpc_security_level min_security_level() const {
    return min_security_level_;
  }

  int cmp(const grpc_call_credentials* other) const {
    CHECK_NE(other, nullptr);
    int r = type().Compare(other->type());
    if (r != 0) return r;
    return cmp_impl(other);
  }

  virtual std::string debug_string() {
    return "grpc_call_credentials did not provide debug string";
  }

  virtual grpc_core::UniqueTypeName type() const = 0;

 private:

  virtual int cmp_impl(const grpc_call_credentials* other) const = 0;

  const grpc_security_level min_security_level_;
};

#endif
