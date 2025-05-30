
// Copyright 2024 gRPC authors.

#include "src/core/credentials/call/gcp_service_account_identity/gcp_service_account_identity_credentials.h"

#include <grpc/support/time.h>

#include "absl/functional/any_invocable.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/escaping.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_split.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata.h"
#include "src/core/credentials/transport/transport_credentials.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/transport/status_conversion.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/status_helper.h"
#include "src/core/util/uri.h"

namespace grpc_core {

class JwtTokenFetcherCallCredentials::HttpFetchRequest final
    : public TokenFetcherCredentials::FetchRequest {
 public:
  HttpFetchRequest(
      JwtTokenFetcherCallCredentials* creds, Timestamp deadline,
      absl::AnyInvocable<
          void(absl::StatusOr<RefCountedPtr<TokenFetcherCredentials::Token>>)>
          on_done)
      : on_done_(std::move(on_done)) {
    GRPC_CLOSURE_INIT(&on_http_response_, OnHttpResponse, this, nullptr);
    Ref().release();
    http_request_ = creds->StartHttpRequest(creds->pollent(), deadline,
                                            &response_, &on_http_response_);
  }

  ~HttpFetchRequest() override { grpc_http_response_destroy(&response_); }

  void Orphan() override {
    http_request_.reset();
    Unref();
  }

 private:
  static void OnHttpResponse(void* arg, grpc_error_handle error) {
    RefCountedPtr<HttpFetchRequest> self(static_cast<HttpFetchRequest*>(arg));
    if (!error.ok()) {

      self->on_done_(absl::UnavailableError(StatusToString(error)));
      return;
    }
    if (self->response_.status != 200) {
      grpc_status_code status_code =
          grpc_http2_status_to_grpc_status(self->response_.status);
      if (status_code != GRPC_STATUS_UNAVAILABLE) {
        status_code = GRPC_STATUS_UNAUTHENTICATED;
      }
      self->on_done_(absl::Status(static_cast<absl::StatusCode>(status_code),
                                  absl::StrCat("JWT fetch failed with status ",
                                               self->response_.status)));
      return;
    }
    absl::string_view body(self->response_.body, self->response_.body_length);

    std::vector<absl::string_view> parts = absl::StrSplit(body, '.');
    if (parts.size() != 3) {
      self->on_done_(absl::UnauthenticatedError("error parsing JWT token"));
      return;
    }

    std::string payload;
    if (!absl::WebSafeBase64Unescape(parts[1], &payload)) {
      self->on_done_(absl::UnauthenticatedError("error parsing JWT token"));
      return;
    }

    auto json = JsonParse(payload);
    if (!json.ok()) {
      self->on_done_(absl::UnauthenticatedError("error parsing JWT token"));
      return;
    }

    struct ParsedPayload {
      uint64_t exp = 0;

      static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
        static const auto kJsonLoader = JsonObjectLoader<ParsedPayload>()
                                            .Field("exp", &ParsedPayload::exp)
                                            .Finish();
        return kJsonLoader;
      }
    };
    auto parsed_payload = LoadFromJson<ParsedPayload>(*json, JsonArgs(), "");
    if (!parsed_payload.ok()) {
      self->on_done_(absl::UnauthenticatedError("error parsing JWT token"));
      return;
    }
    gpr_timespec ts = gpr_time_0(GPR_CLOCK_REALTIME);
    ts.tv_sec = parsed_payload->exp;
    Timestamp expiration_time = Timestamp::FromTimespecRoundDown(ts);

    self->on_done_(MakeRefCounted<Token>(
        Slice::FromCopiedString(absl::StrCat("Bearer ", body)),
        expiration_time));
  }

  OrphanablePtr<HttpRequest> http_request_;
  grpc_closure on_http_response_;
  grpc_http_response response_;
  absl::AnyInvocable<void(
      absl::StatusOr<RefCountedPtr<TokenFetcherCredentials::Token>>)>
      on_done_;
};

OrphanablePtr<TokenFetcherCredentials::FetchRequest>
JwtTokenFetcherCallCredentials::FetchToken(
    Timestamp deadline,
    absl::AnyInvocable<
        void(absl::StatusOr<RefCountedPtr<TokenFetcherCredentials::Token>>)>
        on_done) {
  return MakeOrphanable<HttpFetchRequest>(this, deadline, std::move(on_done));
}

std::string GcpServiceAccountIdentityCallCredentials::debug_string() {
  return absl::StrCat("GcpServiceAccountIdentityCallCredentials(", audience_,
                      ")");
}

UniqueTypeName GcpServiceAccountIdentityCallCredentials::Type() {
  static UniqueTypeName::Factory kFactory("GcpServiceAccountIdentity");
  return kFactory.Create();
}

OrphanablePtr<HttpRequest>
GcpServiceAccountIdentityCallCredentials::StartHttpRequest(
    grpc_polling_entity* pollent, Timestamp deadline,
    grpc_http_response* response, grpc_closure* on_complete) {
  grpc_http_header header = {const_cast<char*>("Metadata-Flavor"),
                             const_cast<char*>("Google")};
  grpc_http_request request;
  memset(&request, 0, sizeof(grpc_http_request));
  request.hdr_count = 1;
  request.hdrs = &header;

  auto uri = URI::Create(
      "http", "", "metadata.google.internal.",
      "/computeMetadata/v1/instance/service-accounts/default/identity",
      {{"audience", audience_}}, "");
  CHECK_OK(uri);
  auto http_request =
      HttpRequest::Get(std::move(*uri), nullptr, pollent, &request,
                       deadline, on_complete, response,
                       RefCountedPtr<grpc_channel_credentials>(
                           grpc_insecure_credentials_create()));
  http_request->Start();
  return http_request;
}

}
