
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_GCP_SERVICE_ACCOUNT_IDENTITY_GCP_SERVICE_ACCOUNT_IDENTITY_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_GCP_SERVICE_ACCOUNT_IDENTITY_GCP_SERVICE_ACCOUNT_IDENTITY_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>

#include <string>
#include <utility>

#include "src/core/call/metadata.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/call/token_fetcher/token_fetcher_credentials.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/polling_entity.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/util/http_client/httpcli.h"
#include "src/core/util/http_client/parser.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

class JwtTokenFetcherCallCredentials : public TokenFetcherCredentials {
 public:
  OrphanablePtr<FetchRequest> FetchToken(
      Timestamp deadline,
      absl::AnyInvocable<
          void(absl::StatusOr<RefCountedPtr<TokenFetcherCredentials::Token>>)>
          on_done) final;

 private:
  class HttpFetchRequest;

  virtual OrphanablePtr<HttpRequest> StartHttpRequest(
      grpc_polling_entity* pollent, Timestamp deadline,
      grpc_http_response* response, grpc_closure* on_complete) = 0;
};

class GcpServiceAccountIdentityCallCredentials
    : public JwtTokenFetcherCallCredentials {
 public:
  explicit GcpServiceAccountIdentityCallCredentials(absl::string_view audience)
      : audience_(audience) {}

  std::string debug_string() override;

  static UniqueTypeName Type();

  UniqueTypeName type() const override { return Type(); }

  absl::string_view audience() const { return audience_; }

 private:
  OrphanablePtr<HttpRequest> StartHttpRequest(
      grpc_polling_entity* pollent, Timestamp deadline,
      grpc_http_response* response, grpc_closure* on_complete) override;

  int cmp_impl(const grpc_call_credentials* other) const override {

    return QsortCompare(static_cast<const grpc_call_credentials*>(this), other);
  }

  std::string audience_;
};

}

#endif
