
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_URI_H
#define GRPC_SRC_CORE_UTIL_URI_H

#include <grpc/support/port_platform.h>

#include <map>
#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

class URI {
 public:
  struct QueryParam {
    std::string key;
    std::string value;
    bool operator==(const QueryParam& other) const {
      return key == other.key && value == other.value;
    }
    bool operator<(const QueryParam& other) const {
      int c = key.compare(other.key);
      if (c != 0) return c < 0;
      return value < other.value;
    }
  };

  static absl::StatusOr<URI> Parse(absl::string_view uri_text);

  static absl::StatusOr<URI> Create(
      std::string scheme, std::string user_info, std::string host_port,
      std::string path, std::vector<QueryParam> query_parameter_pairs,
      std::string fragment);

  URI() = default;

  URI(const URI& other);
  URI& operator=(const URI& other);

  URI(URI&&) = default;
  URI& operator=(URI&&) = default;

  static std::string PercentEncodeAuthority(absl::string_view str);
  static std::string PercentEncodePath(absl::string_view str);

  static std::string PercentDecode(absl::string_view str);

  const std::string& scheme() const { return scheme_; }
  std::string authority() const;
  const std::string& user_info() const { return user_info_; }
  const std::string& host_port() const { return host_port_; }
  const std::string& path() const { return path_; }

  const std::map<absl::string_view, absl::string_view>& query_parameter_map()
      const {
    return query_parameter_map_;
  }

  const std::vector<QueryParam>& query_parameter_pairs() const {
    return query_parameter_pairs_;
  }
  const std::string& fragment() const { return fragment_; }

  std::string ToString() const;

  std::string EncodedPathAndQueryParams() const;

  bool operator==(const URI& other) const {
    return scheme_ == other.scheme_ && user_info_ == other.user_info_ &&
           host_port_ == other.host_port_ && path_ == other.path_ &&
           query_parameter_pairs_ == other.query_parameter_pairs_ &&
           fragment_ == other.fragment_;
  }

 private:
  URI(std::string scheme, std::string user_info, std::string host_port,
      std::string path, std::vector<QueryParam> query_parameter_pairs,
      std::string fragment);

  std::string scheme_;
  std::string user_info_;
  std::string host_port_;
  std::string path_;
  std::map<absl::string_view, absl::string_view> query_parameter_map_;
  std::vector<QueryParam> query_parameter_pairs_;
  std::string fragment_;
};
}

#endif
