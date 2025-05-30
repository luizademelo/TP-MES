// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_LB_METADATA_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_LB_METADATA_H

#include <grpc/event_engine/slice.h>

#include <optional>
#include <string>
#include <vector>

#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/load_balancing/lb_policy.h"

namespace grpc_core {

class LbMetadata : public LoadBalancingPolicy::MetadataInterface {
 public:
  explicit LbMetadata(grpc_metadata_batch* batch) : batch_(batch) {}

  std::optional<absl::string_view> Lookup(absl::string_view key,
                                          std::string* buffer) const override;

  std::vector<std::pair<std::string, std::string>> TestOnlyCopyToVector() const;

 private:
  grpc_metadata_batch* batch_;
};

class MetadataMutationHandler {
 public:
  static void Apply(LoadBalancingPolicy::MetadataMutations& metadata_mutations,
                    grpc_metadata_batch* metadata);
};

void MaybeOverrideAuthority(
    grpc_event_engine::experimental::Slice authority_override,
    grpc_metadata_batch* metadata);

}

#endif
