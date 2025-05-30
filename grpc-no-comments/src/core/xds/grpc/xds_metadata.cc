
// Copyright 2024 gRPC authors.

#include "src/core/xds/grpc/xds_metadata.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

void XdsMetadataMap::Insert(absl::string_view key,
                            std::unique_ptr<XdsMetadataValue> value) {
  CHECK(value != nullptr);
  CHECK(map_.emplace(key, std::move(value)).second) << "duplicate key: " << key;
}

const XdsMetadataValue* XdsMetadataMap::Find(absl::string_view key) const {
  auto it = map_.find(key);
  if (it == map_.end()) return nullptr;
  return it->second.get();
}

bool XdsMetadataMap::operator==(const XdsMetadataMap& other) const {
  if (map_.size() != other.map_.size()) return false;
  for (const auto& [key, value] : map_) {
    auto it = other.map_.find(key);
    if (it == other.map_.end()) return false;
    if (*value != *it->second) return false;
  }
  return true;
}

std::string XdsMetadataMap::ToString() const {
  std::vector<std::string> entries;
  for (const auto& [key, value] : map_) {
    entries.push_back(absl::StrCat(key, "=", value->ToString()));
  }
  std::sort(entries.begin(), entries.end());
  return absl::StrCat("{", absl::StrJoin(entries, ", "), "}");
}

}
