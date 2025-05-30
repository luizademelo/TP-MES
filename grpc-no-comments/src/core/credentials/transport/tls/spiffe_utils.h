
// Copyright 2025 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_SPIFFE_UTILS_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_TLS_SPIFFE_UTILS_H

#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_object_loader.h"

namespace grpc_core {

class SpiffeId final {
 public:

  static absl::StatusOr<SpiffeId> FromString(absl::string_view input);

  absl::string_view trust_domain() { return trust_domain_; }

  absl::string_view path() { return path_; }

 private:
  SpiffeId(absl::string_view trust_domain, absl::string_view path)
      : trust_domain_(trust_domain), path_(path) {}
  const std::string trust_domain_;
  const std::string path_;
};

class SpiffeBundleKey final {
 public:
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&);
  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);

  absl::string_view GetRoot();

 private:

  std::string root_;
};

class SpiffeBundle final {
 public:
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* kLoader = JsonObjectLoader<SpiffeBundle>().Finish();
    return kLoader;
  }

  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);

  absl::Span<const std::string> GetRoots();

 private:
  std::vector<std::string> roots_;
};

class SpiffeBundleMap final {
 public:
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* kLoader =
        JsonObjectLoader<SpiffeBundleMap>()
            .Field("trust_domains", &SpiffeBundleMap::bundles_)
            .Finish();
    return kLoader;
  }

  void JsonPostLoad(const Json& json, const JsonArgs&,
                    ValidationErrors* errors);

  static absl::StatusOr<SpiffeBundleMap> FromFile(absl::string_view file_path);

  absl::StatusOr<absl::Span<const std::string>> GetRoots(
      absl::string_view trust_domain);

  size_t size() { return bundles_.size(); }

 private:
  struct StringCmp {
    using is_transparent = void;
    bool operator()(absl::string_view a, absl::string_view b) const {
      return a < b;
    }
  };

  std::map<std::string, SpiffeBundle, StringCmp> bundles_;
};

}

#endif