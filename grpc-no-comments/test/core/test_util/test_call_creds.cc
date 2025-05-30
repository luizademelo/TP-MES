
// Copyright 2016 gRPC authors.

#include "test/core/test_util/test_call_creds.h"

#include <stdlib.h>

#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/promise/promise.h"

grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
grpc_md_only_test_credentials::GetRequestMetadata(
    grpc_core::ClientMetadataHandle initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs*) {
  initial_metadata->Append(
      key_.as_string_view(), value_.Ref(),
      [](absl::string_view, const grpc_core::Slice&) { abort(); });
  return grpc_core::Immediate(std::move(initial_metadata));
}

grpc_core::UniqueTypeName grpc_md_only_test_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("MdOnlyTest");
  return kFactory.Create();
}

grpc_call_credentials* grpc_md_only_test_credentials_create(
    const char* md_key, const char* md_value) {
  return new grpc_md_only_test_credentials(md_key, md_value);
}
