
// Copyright 2015-2016 gRPC authors.

#include "src/core/credentials/call/composite/composite_call_credentials.h"

#include <cstring>
#include <memory>
#include <vector>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/lib/promise/try_seq.h"
#include "src/core/util/ref_counted_ptr.h"

grpc_core::ArenaPromise<absl::StatusOr<grpc_core::ClientMetadataHandle>>
grpc_composite_call_credentials::GetRequestMetadata(
    grpc_core::ClientMetadataHandle initial_metadata,
    const grpc_call_credentials::GetRequestMetadataArgs* args) {
  auto self = Ref();
  return TrySeqIter(
      inner_.begin(), inner_.end(), std::move(initial_metadata),
      [self, args](const grpc_core::RefCountedPtr<grpc_call_credentials>& creds,
                   grpc_core::ClientMetadataHandle initial_metadata) {
        return creds->GetRequestMetadata(std::move(initial_metadata), args);
      });
}

grpc_core::UniqueTypeName grpc_composite_call_credentials::Type() {
  static grpc_core::UniqueTypeName::Factory kFactory("Composite");
  return kFactory.Create();
}

std::string grpc_composite_call_credentials::debug_string() {
  std::vector<std::string> outputs;
  for (auto& inner_cred : inner_) {
    outputs.emplace_back(inner_cred->debug_string());
  }
  return absl::StrCat("CompositeCallCredentials{", absl::StrJoin(outputs, ","),
                      "}");
}

static size_t get_creds_array_size(const grpc_call_credentials* creds,
                                   bool is_composite) {
  return is_composite
             ? static_cast<const grpc_composite_call_credentials*>(creds)
                   ->inner()
                   .size()
             : 1;
}

void grpc_composite_call_credentials::push_to_inner(
    grpc_core::RefCountedPtr<grpc_call_credentials> creds, bool is_composite) {
  if (!is_composite) {
    inner_.push_back(std::move(creds));
    return;
  }
  auto composite_creds =
      static_cast<grpc_composite_call_credentials*>(creds.get());
  for (size_t i = 0; i < composite_creds->inner().size(); ++i) {
    inner_.push_back(composite_creds->inner_[i]);
  }
}

grpc_composite_call_credentials::grpc_composite_call_credentials(
    grpc_core::RefCountedPtr<grpc_call_credentials> creds1,
    grpc_core::RefCountedPtr<grpc_call_credentials> creds2) {
  const bool creds1_is_composite =
      creds1->type() == grpc_composite_call_credentials::Type();
  const bool creds2_is_composite =
      creds2->type() == grpc_composite_call_credentials::Type();
  const size_t size = get_creds_array_size(creds1.get(), creds1_is_composite) +
                      get_creds_array_size(creds2.get(), creds2_is_composite);
  inner_.reserve(size);
  push_to_inner(std::move(creds1), creds1_is_composite);
  push_to_inner(std::move(creds2), creds2_is_composite);
  min_security_level_ = GRPC_SECURITY_NONE;
  for (size_t i = 0; i < inner_.size(); ++i) {
    if (static_cast<int>(min_security_level_) <
        static_cast<int>(inner_[i]->min_security_level())) {
      min_security_level_ = inner_[i]->min_security_level();
    }
  }
}

grpc_call_credentials* grpc_composite_call_credentials_create(
    grpc_call_credentials* creds1, grpc_call_credentials* creds2,
    void* reserved) {
  GRPC_TRACE_LOG(api, INFO)
      << "grpc_composite_call_credentials_create(creds1=" << creds1
      << ", creds2=" << creds2 << ", reserved=" << reserved << ")";
  CHECK_EQ(reserved, nullptr);
  CHECK_NE(creds1, nullptr);
  CHECK_NE(creds2, nullptr);
  return grpc_core::MakeRefCounted<grpc_composite_call_credentials>(
             creds1->Ref(), creds2->Ref())
      .release();
}
