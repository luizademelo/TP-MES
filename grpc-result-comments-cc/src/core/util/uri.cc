Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

// Includes necessary headers for URI parsing and manipulation
#include "src/core/util/uri.h"

#include <ctype.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <utility>

// ABSL headers for logging, status handling, and string manipulation
#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/ascii.h"
#include "absl/strings/escaping.h"
#include "absl/strings/match.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_join.h"
#include "absl/strings/str_split.h"
#include "absl/strings/strip.h"

namespace grpc_core {

namespace {

// Helper functions to check character types according to URI RFC 3986

// Checks if a character is a sub-delimiter as per RFC 3986
bool IsSubDelimChar(char c) {
  switch (c) {
    case '!':
    case '$':
    case '&':
    case '\'':
    case '(':
    case ')':
    case '*':
    case '+':
    case ',':
    case ';':
    case '=':
      return true;
  }
  return false;
}

// Checks if a character is unreserved as per RFC 3986
bool IsUnreservedChar(char c) {
  if (absl::ascii_isalnum(c)) return true;
  switch (c) {
    case '-':
    case '.':
    case '_':
    case '~':
      return true;
  }
  return false;
}

// Checks if a character is valid in a URI scheme
bool IsSchemeChar(char c) {
  if (absl::ascii_isalnum(c)) return true;
  switch (c) {
    case '+':
    case '-':
    case '.':
      return true;
  }
  return false;
}

// Checks if a character is valid in the authority component of a URI
bool IsAuthorityChar(char c) {
  if (IsUnreservedChar(c)) return true;
  if (IsSubDelimChar(c)) return true;
  switch (c) {
    case ':':
    case '[':
    case ']':
    case '@':
      return true;
  }
  return false;
}

// Checks if a character is valid in the userinfo component of a URI
bool IsUserInfoChar(char c) {
  if (IsUnreservedChar(c)) return true;
  if (IsSubDelimChar(c)) return true;
  if (c == ':') return true;
  return false;
}

// Checks if a character is valid in the host:port component of a URI
bool IsHostPortChar(char c) {
  if (IsUnreservedChar(c)) return true;
  if (IsSubDelimChar(c)) return true;
  switch (c) {
    case ':':
    case '[':
    case ']':
      return true;
  }
  return false;
}

// Checks if a character is valid in a path segment (pchar)
bool IsPChar(char c) {
  if (IsUnreservedChar(c)) return true;
  if (IsSubDelimChar(c)) return true;
  switch (c) {
    case ':':
    case '@':
      return true;
  }
  return false;
}

// Checks if a character is valid in a path
bool IsPathChar(char c) { return IsPChar(c) || c == '/'; }

// Checks if a character is valid in a query or fragment
bool IsQueryOrFragmentChar(char c) {
  return IsPChar(c) || c == '/' || c == '?';
}

// Checks if a character is valid in a query key or value
bool IsQueryKeyOrValueChar(char c) {
  return c != '&' && c != '=' && IsQueryOrFragmentChar(c);
}

// Percent-encodes a string according to the given character validation function
std::string PercentEncode(absl::string_view str,
                          std::function<bool(char)> is_allowed_char) {
  std::string out;
  for (char c : str) {
    if (!is_allowed_char(c)) {
      // Convert disallowed characters to %-encoded form
      std::string hex = absl::BytesToHexString(absl::string_view(&c, 1));
      CHECK_EQ(hex.size(), 2u);

      absl::AsciiStrToUpper(&hex);
      out.push_back('%');
      out.append(hex);
    } else {
      out.push_back(c);
    }
  }
  return out;
}

// Validates if a string contains only valid query/fragment characters
bool IsQueryOrFragmentString(absl::string_view str) {
  for (char c : str) {
    if (!IsQueryOrFragmentChar(c) && c != '%') return false;
  }
  return true;
}

// Creates an error status for invalid URI parsing
absl::Status MakeInvalidURIStatus(absl::string_view part_name,
                                  absl::string_view uri,
                                  absl::string_view extra) {
  return absl::InvalidArgumentError(absl::StrFormat(
      "Could not parse '%s' from uri '%s'. %s", part_name, uri, extra));
}

}  // namespace

// Percent-encodes a string for the authority component of a URI
std::string URI::PercentEncodeAuthority(absl::string_view str) {
  return PercentEncode(str, IsAuthorityChar);
}

// Percent-encodes a string for the path component of a URI
std::string URI::PercentEncodePath(absl::string_view str) {
  return PercentEncode(str, IsPathChar);
}

// Percent-decodes a string (converts %XX sequences back to characters)
std::string URI::PercentDecode(absl::string_view str) {
  if (str.empty() || !absl::StrContains(str, "%")) {
    return std::string(str);
  }
  std::string out;
  std::string unescaped;
  out.reserve(str.size());
  for (size_t i = 0; i < str.length(); i++) {
    unescaped = "";
    if (str[i] == '%' && i + 3 <= str.length() &&
        absl::CUnescape(absl::StrCat("\\x", str.substr(i + 1, 2)),
                        &unescaped) &&
        unescaped.length() == 1) {
      out += unescaped[0];
      i += 2;
    } else {
      out += str[i];
    }
  }
  return out;
}

// Returns the authority portion of the URI (user_info@host_port or just host_port)
std::string URI::authority() const {
  if (!user_info_.empty()) {
    return absl::StrCat(user_info_, "@", host_port_);
  }
  return host_port_;
}

// Parses a URI string into its components
absl::StatusOr<URI> URI::Parse(absl::string_view uri_text) {
  absl::string_view remaining = uri_text;

  // Extract scheme
  size_t offset = remaining.find(':');
  if (offset == remaining.npos || offset == 0) {
    return MakeInvalidURIStatus("scheme", uri_text, "Scheme not found.");
  }
  std::string scheme(remaining.substr(0, offset));
  if (scheme.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                               "0123456789+-.") != std::string::npos) {
    return MakeInvalidURIStatus("scheme", uri_text,
                                "Scheme contains invalid characters.");
  }
  if (!isalpha(scheme[0])) {
    return MakeInvalidURIStatus(
        "scheme", uri_text,
        "Scheme must begin with an alpha character [A-Za-z].");
  }
  remaining.remove_prefix(offset + 1);

  // Extract authority (user_info and host_port)
  std::string user_info;
  std::string host_port;
  if (absl::ConsumePrefix(&remaining, "//")) {
    offset = remaining.find_first_of("/?#");
    absl::string_view encoded_authority = (remaining.substr(0, offset));

    absl::string_view encoded_user_info;
    absl::string_view encoded_host_port;
    size_t at_pos = encoded_authority.rfind('@');
    if (at_pos == absl::string_view::npos) {
      encoded_host_port = encoded_authority;
    } else {
      encoded_user_info = encoded_authority.substr(0, at_pos);
      encoded_host_port = encoded_authority.substr(at_pos + 1);
    }
    user_info = PercentDecode(encoded_user_info);
    host_port = PercentDecode(encoded_host_port);
    if (offset == remaining.npos) {
      remaining = "";
    } else {
      remaining.remove_prefix(offset);
    }
  }

  // Extract path
  std::string path;
  if (!remaining.empty()) {
    offset = remaining.find_first_of("?#");
    path = PercentDecode(remaining.substr(0, offset));
    if (offset == remaining.npos) {
      remaining = "";
    } else {
      remaining.remove_prefix(offset);
    }
  }

  // Extract query parameters
  std::vector<QueryParam> query_param_pairs;
  if (absl::ConsumePrefix(&remaining, "?")) {
    offset = remaining.find('#');
    absl::string_view tmp_query = remaining.substr(0, offset);
    if (tmp_query.empty()) {
      return MakeInvalidURIStatus("query", uri_text, "Invalid query string.");
    }
    if (!IsQueryOrFragmentString(tmp_query)) {
      return MakeInvalidURIStatus("query string", uri_text,
                                  "Query string contains invalid characters.");
    }
    for (absl::string_view query_param : absl::StrSplit(tmp_query, '&')) {
      const std::pair<absl::string_view, absl::string_view> possible_kv =
          absl::StrSplit(query_param, absl::MaxSplits('=', 1));
      auto& [key, value] = possible_kv;
      if (key.empty()) continue;
      query_param_pairs.push_back({PercentDecode(key), PercentDecode(value)});
    }
    if (offset == remaining.npos) {
      remaining = "";
    } else {
      remaining.remove_prefix(offset);
    }
  }

  // Extract fragment
  std::string fragment;
  if (absl::ConsumePrefix(&remaining, "#")) {
    if (!IsQueryOrFragmentString(remaining)) {
      return MakeInvalidURIStatus("fragment", uri_text,
                                  "Fragment contains invalid characters.");
    }
    fragment = PercentDecode(remaining);
  }

  // Return constructed URI object
  return URI(std::move(scheme), std::move(user_info), std::move(host_port),
             std::move(path), std::move(query_param_pairs),
             std::move(fragment));
}

// Creates a URI object with validation
absl::StatusOr<URI> URI::Create(std::string scheme, std::string user_info,
                                std::string host_port, std::string path,
                                std::vector<QueryParam> query_parameter_pairs,
                                std::string fragment) {
  // Validate URI components
  if (!host_port.empty() && !path.empty() && path[0] != '/') {
    return absl::InvalidArgumentError(
        "if host_port is present, path must start with a '/'");
  }
  if (!user_info.empty() && host_port.empty()) {
    return absl::InvalidArgumentError(
        "if user_info is present, host_port must be present");
  }
  return URI(std::move(scheme), std::move(user_info), std::move(host_port),
             std::move(path), std::move(query_parameter_pairs),
             std::move(fragment));
}

// URI constructor
URI::URI(std::string scheme, std::string user_info, std::string host_port,
         std::string path, std::vector<QueryParam> query_parameter_pairs,
         std::string fragment)
    : scheme_(std::move(scheme)),
      user_info_(std::move(user_info)),
      host_port_(std::move(host_port)),
      path_(std::move(path)),
      query_parameter_pairs_(std::move(query_parameter_pairs)),
      fragment_(std::move(fragment)) {
  // Normalize scheme to lowercase
  absl::AsciiStrToLower(&scheme_);
  // Build query parameter map
  for (const auto& kv : query_parameter_pairs_) {
    query_parameter_map_[kv.key] = kv.value;
  }
}

// URI copy constructor
URI::URI(const URI& other)
    : scheme_(other.scheme_),
      user_info_(other.user_info_),
      host_port_(other.host_port_),
      path_(other.path_),
      query_parameter_pairs_(other.query_parameter_pairs_),
      fragment_(other.fragment_) {
  // Rebuild query parameter map
  for (const auto& kv : query_parameter_pairs_) {
    query_parameter_map_[kv.key] = kv.value;
  }
}

// URI assignment operator
URI& URI::operator=(const URI& other) {
  if (this == &other) {
    return *this;
  }
  scheme_ = other.scheme_;
  user_info_ = other.user_info_;
  host_port_ = other.host_port_;
  path_ = other.path_;
  query_parameter_pairs_ = other.query_parameter_pairs_;
  fragment_ = other.fragment_;
  // Rebuild query parameter map
  for (const auto& kv : query_parameter_pairs_) {
    query_parameter_map_[kv.key] = kv.value;
  }
  return *this;
}

namespace {

// Helper struct for formatting query parameters in ToString()
struct QueryParameterFormatter {
  void operator()(std::string* out, const URI::QueryParam& query_param) const {
    out->append(
        absl::StrCat(PercentEncode(query_param.key, IsQueryKeyOrValueChar), "=",
                     PercentEncode(query_param.value, IsQueryKeyOrValueChar)));
  }
};

}  // namespace

// Converts the URI to its string representation
std::string URI::ToString() const {
  std::vector<std::string> parts = {PercentEncode(scheme_, IsSchemeChar), ":"};

  // Handle authority portion
  if (!host_port_.empty() || absl::StartsWith(path_, "//")) {
    parts.emplace_back("//");
    if (!user_info_.empty()) {
      parts.emplace_back(PercentEncode(user_info_, IsUserInfoChar));
      parts.emplace_back("@");
    }
    parts.emplace_back(PercentEncode(host_port_, IsHostPortChar));
  }
  // Add path and query
  parts.emplace_back(EncodedPathAndQueryParams());
  // Add fragment if present
  if (!fragment_.empty()) {
    parts.push_back("#");
    parts.push_back(PercentEncode(fragment_, IsQueryOrFragmentChar));
  }
  return absl::StrJoin(parts, "");
}

// Returns the encoded path and query parameters as a string
std::string URI::EncodedPathAndQueryParams() const {
  std::vector<std::string> parts;
  if (!path_.empty()) {
    parts.emplace_back(PercentEncode(path_, IsPathChar));
  }
  if (!query_parameter_pairs_.empty()) {
    parts.push_back("?");
    parts.push_back(
        absl::StrJoin(query_parameter_pairs_, "&", QueryParameterFormatter()));
  }
  return absl::StrJoin(parts, "");
}

}  // namespace grpc_core
```