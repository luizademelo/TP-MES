Here's the commented version of the code:

```c++
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

// Abstract base class representing a value in xDS metadata.
// Provides common interface for all metadata value types.
class XdsMetadataValue {
 public:
  virtual ~XdsMetadataValue() = default;

  // Returns the type identifier of the metadata value
  virtual absl::string_view type() const = 0;

  // Comparison operators that check both type and value equality
  bool operator==(const XdsMetadataValue& other) const {
    return type() == other.type() && Equals(other);
  }
  bool operator!=(const XdsMetadataValue& other) const {
    return !(*this == other);
  }

  // Returns a string representation of the metadata value
  virtual std::string ToString() const = 0;

 private:
  // Internal method for value equality comparison to be implemented by subclasses
  virtual bool Equals(const XdsMetadataValue& other) const = 0;
};

// A map container for xDS metadata that stores key-value pairs where
// values are polymorphic XdsMetadataValue objects.
class XdsMetadataMap {
 public:
  // Inserts a new key-value pair into the metadata map
  void Insert(absl::string_view key, std::unique_ptr<XdsMetadataValue> value);

  // Finds a metadata value by key (returns nullptr if not found)
  const XdsMetadataValue* Find(absl::string_view key) const;

  // Finds a metadata value by key and type (returns nullptr if not found or type mismatch)
  template <typename T>
  const T* FindType(absl::string_view key) const {
    auto it = map_.find(key);
    if (it == map_.end()) return nullptr;
    if (it->second->type() != T::Type()) return nullptr;
    return DownCast<const T*>(it->second.get());
  }

  // Checks if the metadata map is empty
  bool empty() const { return map_.empty(); }
  // Returns the number of elements in the metadata map
  size_t size() const { return map_.size(); }

  // Compares two metadata maps for equality
  bool operator==(const XdsMetadataMap& other) const;

  // Returns a string representation of the entire metadata map
  std::string ToString() const;

 private:
  // Underlying storage using a hash map with string keys and polymorphic values
  absl::flat_hash_map<std::string, std::unique_ptr<XdsMetadataValue>> map_;
};

// Metadata value implementation for Protocol Buffer Struct type
class XdsStructMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsStructMetadataValue(Json json) : json_(std::move(json)) {}

  // Returns the type identifier for Struct metadata values
  static absl::string_view Type() { return "google.protobuf.Struct"; }

  absl::string_view type() const override { return Type(); }

  // Accessor for the underlying JSON data
  const Json& json() const { return json_; }

  // Returns a string representation of the Struct value
  std::string ToString() const override {
    return absl::StrCat(type(), "{", JsonDump(json_), "}");
  }

 private:
  // Compares the JSON content for equality
  bool Equals(const XdsMetadataValue& other) const override {
    return json_ == DownCast<const XdsStructMetadataValue&>(other).json_;
  }

  // The actual JSON data being stored
  Json json_;
};

// Metadata value implementation for GCP Authentication Audience
class XdsGcpAuthnAudienceMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsGcpAuthnAudienceMetadataValue(absl::string_view url)
      : url_(url) {}

  // Returns the type identifier for GCP Authn Audience metadata values
  static absl::string_view Type() {
    return "envoy.extensions.filters.http.gcp_authn.v3.Audience";
  }

  absl::string_view type() const override { return Type(); }

  // Accessor for the URL value
  const std::string& url() const { return url_; }

  // Returns a string representation of the Audience value
  std::string ToString() const override {
    return absl::StrCat(type(), "{url=\"", url_, "\"}");
  }

 private:
  // Compares the URL values for equality
  bool Equals(const XdsMetadataValue& other) const override {
    return url_ ==
           DownCast<const XdsGcpAuthnAudienceMetadataValue&>(other).url_;
  }

  // The URL string being stored
  std::string url_;
};

// Metadata value implementation for Envoy Address type
class XdsAddressMetadataValue : public XdsMetadataValue {
 public:
  explicit XdsAddressMetadataValue(std::string address)
      : address_(std::move(address)) {}

  // Returns the type identifier for Address metadata values
  static absl::string_view Type() { return "envoy.config.core.v3.Address"; }

  absl::string_view type() const override { return Type(); }

  // Accessor for the address value
  const std::string& address() const { return address_; }

  // Returns a string representation of the Address value
  std::string ToString() const override {
    return absl::StrCat(type(), "{address=\"", address_, "\"}");
  }

 private:
  // Compares the address values for equality
  bool Equals(const XdsMetadataValue& other) const override {
    return address_ == DownCast<const XdsAddressMetadataValue&>(other).address_;
  }

  // The address string being stored
  std::string address_;
};

}

#endif
```