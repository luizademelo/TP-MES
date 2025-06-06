// Copyright 2024 gRPC authors.

#include "src/core/client_channel/lb_metadata.h"

#include "absl/log/log.h"

namespace grpc_core {

namespace {

class Encoder {
 public:
  void Encode(const Slice& key, const Slice& value) {
    out_.emplace_back(std::string(key.as_string_view()),
                      std::string(value.as_string_view()));
  }

  template <class Which>
  void Encode(Which, const typename Which::ValueType& value) {
    auto value_slice = Which::Encode(value);
    out_.emplace_back(std::string(Which::key()),
                      std::string(value_slice.as_string_view()));
  }

  void Encode(GrpcTimeoutMetadata,
              const typename GrpcTimeoutMetadata::ValueType&) {}
  void Encode(HttpPathMetadata, const Slice&) {}
  void Encode(HttpMethodMetadata,
              const typename HttpMethodMetadata::ValueType&) {}

  std::vector<std::pair<std::string, std::string>> Take() {
    return std::move(out_);
  }

 private:
  std::vector<std::pair<std::string, std::string>> out_;
};

}

std::optional<absl::string_view> LbMetadata::Lookup(absl::string_view key,
                                                    std::string* buffer) const {
  if (batch_ == nullptr) return std::nullopt;
  return batch_->GetStringValue(key, buffer);
}

std::vector<std::pair<std::string, std::string>>
LbMetadata::TestOnlyCopyToVector() const {
  if (batch_ == nullptr) return {};
  Encoder encoder;
  batch_->Encode(&encoder);
  return encoder.Take();
}

void MetadataMutationHandler::Apply(
    LoadBalancingPolicy::MetadataMutations& metadata_mutations,
    grpc_metadata_batch* metadata) {
  for (auto& [key, value_slice] : metadata_mutations.metadata_) {
    Slice& value = grpc_event_engine::experimental::internal::SliceCast<Slice>(
        value_slice);

    metadata->Remove(key);

    if (key == GrpcLbClientStatsMetadata::key()) {
      metadata->Set(
          GrpcLbClientStatsMetadata(),
          const_cast<GrpcLbClientStats*>(
              reinterpret_cast<const GrpcLbClientStats*>(value.data())));
      continue;
    }
    metadata->Append(key, std::move(value),
                     [key = key](absl::string_view error, const Slice& value) {
                       LOG(ERROR) << error << " key:" << key
                                  << " value:" << value.as_string_view();
                     });
  }
}

void MaybeOverrideAuthority(
    grpc_event_engine::experimental::Slice authority_override,
    grpc_metadata_batch* metadata) {

  if (authority_override.empty()) return;

  if (metadata->get_pointer(HttpAuthorityMetadata()) != nullptr) return;

  Slice& authority =
      grpc_event_engine::experimental::internal::SliceCast<Slice>(
          authority_override);
  metadata->Set(HttpAuthorityMetadata(), std::move(authority));
}

}
