
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_OAUTH2_OAUTH2_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_OAUTH2_OAUTH2_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>

#include <atomic>
#include <optional>
#include <string>
#include <utility>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/call/token_fetcher/token_fetcher_credentials.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/promise/activity.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/http_client/httpcli.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/uri.h"
#include "src/core/util/useful.h"

#define GRPC_STS_POST_MINIMAL_BODY_FORMAT_STRING                               \
  "grant_type=urn:ietf:params:oauth:grant-type:token-exchange&subject_token=%" \
  "s&subject_token_type=%s"

struct grpc_auth_refresh_token {
  const char* type;
  char* client_id;
  char* client_secret;
  char* refresh_token;
};

int grpc_auth_refresh_token_is_valid(
    const grpc_auth_refresh_token* refresh_token);

grpc_auth_refresh_token grpc_auth_refresh_token_create_from_string(
    const char* json_string);

grpc_auth_refresh_token grpc_auth_refresh_token_create_from_json(
    const grpc_core::Json& json);

void grpc_auth_refresh_token_destruct(grpc_auth_refresh_token* refresh_token);

namespace grpc_core {

class Oauth2TokenFetcherCredentials : public TokenFetcherCredentials {
 public:
  std::string debug_string() override;

  UniqueTypeName type() const override;

  OrphanablePtr<FetchRequest> FetchToken(
      Timestamp deadline,
      absl::AnyInvocable<
          void(absl::StatusOr<RefCountedPtr<TokenFetcherCredentials::Token>>)>
          on_done) final;

  virtual OrphanablePtr<HttpRequest> StartHttpRequest(
      grpc_polling_entity* pollent, Timestamp deadline,
      grpc_http_response* response, grpc_closure* on_complete) = 0;

 private:
  class HttpFetchRequest;

  int cmp_impl(const grpc_call_credentials* other) const override {

    return QsortCompare(static_cast<const grpc_call_credentials*>(this), other);
  }
};

}

class grpc_google_refresh_token_credentials final
    : public grpc_core::Oauth2TokenFetcherCredentials {
 public:
  explicit grpc_google_refresh_token_credentials(
      grpc_auth_refresh_token refresh_token);
  ~grpc_google_refresh_token_credentials() override;

  const grpc_auth_refresh_token& refresh_token() const {
    return refresh_token_;
  }

  std::string debug_string() override;

  grpc_core::UniqueTypeName type() const override;

 private:
  grpc_core::OrphanablePtr<grpc_core::HttpRequest> StartHttpRequest(
      grpc_polling_entity* pollent, grpc_core::Timestamp deadline,
      grpc_http_response* response, grpc_closure* on_complete) override;

  grpc_auth_refresh_token refresh_token_;
};

class grpc_access_token_credentials final : public grpc_call_credentials {
 public:
  explicit grpc_access_token_credentials(const char* access_token);

  void Orphaned() override {}

  grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
  GetRequestMetadata(grpc_core::ClientMetadataHandle initial_metadata,
                     const GetRequestMetadataArgs* args) override;

  std::string debug_string() override;

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

 private:
  int cmp_impl(const grpc_call_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_call_credentials*>(this), other);
  }

  const grpc_core::Slice access_token_value_;
};

grpc_core::RefCountedPtr<grpc_call_credentials>
grpc_refresh_token_credentials_create_from_auth_refresh_token(
    grpc_auth_refresh_token token);

grpc_credentials_status
grpc_oauth2_token_fetcher_credentials_parse_server_response_body(
    absl::string_view body, std::optional<grpc_core::Slice>* token_value,
    grpc_core::Duration* token_lifetime);

grpc_credentials_status
grpc_oauth2_token_fetcher_credentials_parse_server_response(
    const struct grpc_http_response* response,
    std::optional<grpc_core::Slice>* token_value,
    grpc_core::Duration* token_lifetime);

namespace grpc_core {

absl::StatusOr<URI> ValidateStsCredentialsOptions(
    const grpc_sts_credentials_options* options);
}

#endif
