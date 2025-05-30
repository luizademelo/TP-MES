
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_METADATA_H

#include <memory>
#include <string>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class XdsMetadataValue {
 public:
  virtual ~XdsMetadataValue() = default;

  virtual absl::string_view type() const = 0;

  bool operator==(const XdsMetadataValue& other) const {
    return type() == other.type() && Equals(other);
  }
  bool operator!=(const XdsMetadataValue& other) const {
    return !(*this == other);
  }

  virtual std::string ToString() const = 0;

 private:

  virtual bool Equals(const XdsMetadataValue& other) const = 0;
};

class XdsMetadataMap {
 public:
  void Insert(absl::string_view key, std::unique_ptr<XdsMetadataValue> value);

  const XdsMetadataValue* Find(absl::string_view key) const;

  template <typename T>
  const T* FindType(absl::string_view key) const {
    auto it = map_.find(key);
    if (it == map_.end()) return nullptr;
    if (it->second->type() != T::Type()) return nullptr;
    return DownCast<const T*>(it->second.get());
  }

  bool empty() const { return map_.empty(); }
  size_t size() const { return map_.size(); }

  bool operator==(const XdsMetadataMap& other) const;

  std::string ToString() const;

 private:
  absl::flat_hash_map<std::string, std::unique_ptr<XdsMetadataValue>> map_;
};

class XdsStructMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsStructMetadataValue(Json json) : json_(std::move(json)) {}

  static absl::string_view Type() { return "google.protobuf.Struct"; }

  absl::string_view type() const override { return Type(); }

  const Json& json() const { return json_; }

  std::string ToString() const override {
    return absl::StrCat(type(), "{", JsonDump(json_), "}");
  }

 private:
  bool Equals(const XdsMetadataValue& other) const override {
    return json_ == DownCast<const XdsStructMetadataValue&>(other).json_;
  }

  Json json_;
};

class XdsGcpAuthnAudienceMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsGcpAuthnAudienceMetadataValue(absl::string_view url)
      : url_(url) {}

  static absl::string_view Type() {
    return "envoy.extensions.filters.http.gcp_authn.v3.Audience";
  }

  absl::string_view type() const override { return Type(); }

  const std::string& url() const { return url_; }

  std::string ToString() const override {
    return absl::StrCat(type(), "{url=\"", url_, "\"}");
  }

 private:
  bool Equals(const XdsMetadataValue& other) const override {
    return url_ ==
           DownCast<const XdsGcpAuthnAudienceMetadataValue&>(other).url_;
  }

  std::string url_;
};

class XdsAddressMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsAddressMetadataValue(std::string address)
      : address_(std::move(address)) {}

  static absl::string_view Type() { return "envoy.config.core.v3.Address"; }

  absl::string_view type() const override { return Type(); }

  const std::string& address() const { return address_; }

  std::string ToString() const override {
    return absl::StrCat(type(), "{address=\"", address_, "\"}");
  }

 private:
  bool Equals(const XdsMetadataValue& other) const override {
    return address_ == DownCast<const XdsAddressMetadataValue&>(other).address_;
  }

  std::string address_;
};

}

#endif
