
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_CALL_IAM_IAM_CREDENTIALS_H
#define GRPC_SRC_CORE_CREDENTIALS_CALL_IAM_IAM_CREDENTIALS_H

#include <grpc/credentials.h>
#include <grpc/grpc_security.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "src/core/credentials/call/call_credentials.h"
#include "src/core/lib/promise/arena_promise.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

class grpc_google_iam_credentials : public grpc_call_credentials {
 public:
  grpc_google_iam_credentials(const char* token,
                              const char* authority_selector);

  void Orphaned() override {}

  grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
  GetRequestMetadata(grpc_core::ClientMetadataHandle initial_metadata,
                     const GetRequestMetadataArgs* args) override;

  std::string debug_string() override { return debug_string_; }

  static grpc_core::UniqueTypeName Type();

  grpc_core::UniqueTypeName type() const override { return Type(); }

 private:
  int cmp_impl(const grpc_call_credentials* other) const override {

    return grpc_core::QsortCompare(
        static_cast<const grpc_call_credentials*>(this), other);
  }

  const std::optional<grpc_core::Slice> token_;
  const grpc_core::Slice authority_selector_;
  const std::string debug_string_;
};

#endif
