
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JWT_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_JWT_JWT_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>
#include <grpc/support/time.h>
#include <stdint.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/str_format.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/credentials/call/jwt/json_token.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

class grpc_service_account_jwt_access_credentials
    : public grpc_call_credentials {
 public:
  grpc_service_account_jwt_access_credentials(grpc_auth_json_key key,
                                              gpr_timespec token_lifetime);
  ~grpc_service_account_jwt_access_credentials() override;

  void Orphaned() override {}

  grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
  GetRequestMetadata(grpc_core::ClientMetadataHandle initial_metadata,
                     const GetRequestMetadataArgs* args) override;

  const gpr_timespec& jwt_lifetime() const { return jwt_lifetime_; }
  const grpc_auth_json_key& key() const { return key_; }

  std::string debug_string() override {
    return absl::StrFormat(
        "JWTAccessCredentials{ExpirationTime:%s}",
        absl::FormatTime(absl::FromUnixMicros(
            static_cast<int64_t>(gpr_timespec_to_micros(jwt_lifetime_)))));
  };

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

 private:
  int cmp_impl(const grpc_call_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_call_credentials*>(this), other);
  }

  gpr_mu cache_mu_;
  struct Cache {
    grpc_core::Slice jwt_value;
    std::string service_url;
    gpr_timespec jwt_expiration;
  };
  std::optional<Cache> cached_;

  grpc_auth_json_key key_;
  gpr_timespec jwt_lifetime_;
};

grpc_core::RefCountedPtr<grpc_call_credentials>
grpc_service_account_jwt_access_credentials_create_from_auth_json_key(
    grpc_auth_json_key key, gpr_timespec token_lifetime);

namespace grpc_core {

absl::StatusOr<std::string> RemoveServiceNameFromJwtUri(absl::string_view uri);

}

#endif
