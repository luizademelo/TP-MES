Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/xds/grpc/xds_endpoint.h"

#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"

namespace grpc_core {

// Converts a Locality object to its string representation.
// The string includes the locality name, load balancing weight, and all endpoints.
std::string XdsEndpointResource::Priority::Locality::ToString() const {
  std::vector<std::string> endpoint_strings;
  for (const EndpointAddresses& endpoint : endpoints) {
    endpoint_strings.emplace_back(endpoint.ToString());
  }
  return absl::StrCat("{name=", name->human_readable_string().as_string_view(),
                      ", lb_weight=", lb_weight, ", endpoints=[",
                      absl::StrJoin(endpoint_strings, ", "), "]}");
}

// Compares two Priority objects for equality by checking:
// 1. If they have the same number of localities
// 2. If each locality (in order) has the same name and content
bool XdsEndpointResource::Priority::operator==(const Priority& other) const {
  if (localities.size() != other.localities.size()) return false;
  auto it1 = localities.begin();
  auto it2 = other.localities.begin();
  while (it1 != localities.end()) {
    if (*it1->first != *it2->first) return false;
    if (it1->second != it2->second) return false;
    ++it1;
    ++it2;
  }
  return true;
}

// Converts a Priority object to its string representation.
// The string includes all localities in the priority.
std::string XdsEndpointResource::Priority::ToString() const {
  std::vector<std::string> locality_strings;
  locality_strings.reserve(localities.size());
  for (const auto& [_, locality] : localities) {
    locality_strings.emplace_back(locality.ToString());
  }
  return absl::StrCat("[", absl::StrJoin(locality_strings, ", "), "]");
}

// Determines whether a request should be dropped based on configured drop rates.
// Returns true and sets the category_name if a drop should occur.
// Thread-safe: uses mutex to protect random number generation.
bool XdsEndpointResource::DropConfig::ShouldDrop(
    const std::string** category_name) {
  for (const auto& drop_category : drop_category_list_) {
    // Generate random number in a thread-safe manner
    const uint32_t random = [&]() {
      MutexLock lock(&mu_);
      return absl::Uniform<uint32_t>(bit_gen_, 0, 1000000);
    }();
    // Check if random number falls in the drop range for this category
    if (random < drop_category.parts_per_million) {
      *category_name = &drop_category.name;
      return true;
    }
  }
  return false;
}

// Converts a DropConfig object to its string representation.
// The string includes all drop categories and their ppm rates, plus drop_all flag.
std::string XdsEndpointResource::DropConfig::ToString() const {
  std::vector<std::string> category_strings;
  for (const DropCategory& category : drop_category_list_) {
    category_strings.emplace_back(
        absl::StrCat(category.name, "=", category.parts_per_million));
  }
  return absl::StrCat("{[", absl::StrJoin(category_strings, ", "),
                      "], drop_all=", drop_all_, "}");
}

// Converts an XdsEndpointResource to its string representation.
// The string includes all priorities and the drop configuration.
std::string XdsEndpointResource::ToString() const {
  std::vector<std::string> priority_strings;
  for (size_t i = 0; i < priorities.size(); ++i) {
    const Priority& priority = priorities[i];
    priority_strings.emplace_back(
        absl::StrCat("priority ", i, ": ", priority.ToString()));
  }
  return absl::StrCat(
      "priorities=[", absl::StrJoin(priority_strings, ", "), "], drop_config=",
      drop_config == nullptr ? "<null>" : drop_config->ToString());
}

}  // namespace grpc_core
```

The comments added:
1. Explain the purpose of each method
2. Describe the logic and key operations
3. Note thread-safety considerations where relevant
4. Clarify the string format for ToString() methods
5. Explain comparison logic for operator==
6. Document the drop decision algorithm in ShouldDrop()

The comments are concise yet comprehensive, providing enough information for maintenance while not being overly verbose. They follow the style of explaining what the code does rather than just repeating what the code says.