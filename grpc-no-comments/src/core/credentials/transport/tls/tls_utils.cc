
// Copyright 2020 gRPC authors.

#include "src/core/credentials/transport/tls/tls_utils.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>

#include "absl/log/log.h"
#include "absl/strings/ascii.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"

namespace grpc_core {

bool VerifySubjectAlternativeName(absl::string_view subject_alternative_name,
                                  const std::string& matcher) {
  if (subject_alternative_name.empty() ||
      absl::StartsWith(subject_alternative_name, ".")) {

    return false;
  }
  if (matcher.empty() || absl::StartsWith(matcher, ".")) {

    return false;
  }

  std::string normalized_san =
      absl::EndsWith(subject_alternative_name, ".")
          ? std::string(subject_alternative_name)
          : absl::StrCat(subject_alternative_name, ".");
  std::string normalized_matcher =
      absl::EndsWith(matcher, ".") ? matcher : absl::StrCat(matcher, ".");
  absl::AsciiStrToLower(&normalized_san);
  absl::AsciiStrToLower(&normalized_matcher);
  if (!absl::StrContains(normalized_san, "*")) {
    return normalized_san == normalized_matcher;
  }

  if (!absl::StartsWith(normalized_san, "*.")) {

    return false;
  }
  if (normalized_san == "*.") {

    return false;
  }
  absl::string_view suffix = absl::string_view(normalized_san).substr(1);
  if (absl::StrContains(suffix, "*")) {

    return false;
  }
  if (!absl::EndsWith(normalized_matcher, suffix)) return false;
  size_t suffix_start_index = normalized_matcher.length() - suffix.length();

  return suffix_start_index <= 0  ||
         normalized_matcher.find_last_of('.', suffix_start_index - 1) ==
             std::string::npos;
}

absl::string_view GetAuthPropertyValue(grpc_auth_context* context,
                                       const char* property_name) {
  grpc_auth_property_iterator it =
      grpc_auth_context_find_properties_by_name(context, property_name);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  if (prop == nullptr) {
    VLOG(2) << "No value found for " << property_name << " property.";
    return "";
  }
  if (grpc_auth_property_iterator_next(&it) != nullptr) {
    VLOG(2) << "Multiple values found for " << property_name << " property.";
    return "";
  }
  return absl::string_view(prop->value, prop->value_length);
}

std::vector<absl::string_view> GetAuthPropertyArray(grpc_auth_context* context,
                                                    const char* property_name) {
  std::vector<absl::string_view> values;
  grpc_auth_property_iterator it =
      grpc_auth_context_find_properties_by_name(context, property_name);
  const grpc_auth_property* prop = grpc_auth_property_iterator_next(&it);
  while (prop != nullptr) {
    values.emplace_back(prop->value, prop->value_length);
    prop = grpc_auth_property_iterator_next(&it);
  }
  if (values.empty()) {
    VLOG(2) << "No value found for " << property_name << " property.";
  }
  return values;
}

}
