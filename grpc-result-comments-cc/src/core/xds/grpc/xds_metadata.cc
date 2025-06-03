Here's the commented version of the code:

```c++
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

// Inserts a key-value pair into the metadata map.
// Parameters:
//   key: The key under which to store the value
//   value: Unique pointer to the metadata value to store
// Requirements:
//   - value must not be null (CHECKed)
//   - key must not already exist in the map (CHECKed)
// Note: The method takes ownership of the value through the unique_ptr
void XdsMetadataMap::Insert(absl::string_view key,
                            std::unique_ptr<XdsMetadataValue> value) {
  CHECK(value != nullptr);
  CHECK(map_.emplace(key, std::move(value)).second) << "duplicate key: " << key;
}

// Finds and returns a metadata value by key.
// Parameters:
//   key: The key to look up in the map
// Returns:
//   - Pointer to the found value if key exists
//   - nullptr if key is not found
// Note: The returned pointer is non-owning and remains valid as long as the map exists
const XdsMetadataValue* XdsMetadataMap::Find(absl::string_view key) const {
  auto it = map_.find(key);
  if (it == map_.end()) return nullptr;
  return it->second.get();
}

// Equality comparison operator for XdsMetadataMap.
// Two maps are considered equal if:
//   1. They have the same size
//   2. For each key-value pair in this map:
//      - The key exists in the other map
//      - The corresponding values compare equal (using XdsMetadataValue::operator==)
bool XdsMetadataMap::operator==(const XdsMetadataMap& other) const {
  if (map_.size() != other.map_.size()) return false;
  for (const auto& [key, value] : map_) {
    auto it = other.map_.find(key);
    if (it == other.map_.end()) return false;
    if (*value != *it->second) return false;
  }
  return true;
}

// Converts the metadata map to a human-readable string representation.
// The format is: "{key1=value1, key2=value2, ...}"
// The entries are sorted alphabetically by key for consistent output.
// Returns:
//   String representation of the metadata map
std::string XdsMetadataMap::ToString() const {
  std::vector<std::string> entries;
  for (const auto& [key, value] : map_) {
    entries.push_back(absl::StrCat(key, "=", value->ToString()));
  }
  std::sort(entries.begin(), entries.end());
  return absl::StrCat("{", absl::StrJoin(entries, ", "), "}");
}

}  // namespace grpc_core
```

The comments provide:
1. Description of each method's purpose
2. Parameter explanations
3. Return value explanations
4. Important notes about ownership and pointer validity
5. Behavior details and requirements
6. Format explanations for string output
7. Equality comparison criteria

The comments are placed directly above each method they describe and follow a consistent style that explains both what the code does and why it does it that way.