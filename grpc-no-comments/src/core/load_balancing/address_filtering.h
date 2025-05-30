
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_LOAD_BALANCING_ADDRESS_FILTERING_H
#define GRPC_SRC_CORE_LOAD_BALANCING_ADDRESS_FILTERING_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/resolver/endpoint_addresses.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_string.h"

namespace grpc_core {

class HierarchicalPathArg final : public RefCounted<HierarchicalPathArg> {
 public:
  explicit HierarchicalPathArg(std::vector<RefCountedStringValue> path)
      : path_(std::move(path)) {}

  static absl::string_view ChannelArgName();
  static int ChannelArgsCompare(const HierarchicalPathArg* a,
                                const HierarchicalPathArg* b);

  const std::vector<RefCountedStringValue>& path() const { return path_; }

 private:
  std::vector<RefCountedStringValue> path_;
};

using HierarchicalAddressMap =
    std::map<RefCountedStringValue, std::shared_ptr<EndpointAddressesIterator>,
             RefCountedStringValueLessThan>;

absl::StatusOr<HierarchicalAddressMap> MakeHierarchicalAddressMap(
    absl::StatusOr<std::shared_ptr<EndpointAddressesIterator>> addresses);

}

#endif
