
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_CHANNEL_CREDS_REGISTRY_H
#define GRPC_SRC_CORE_CREDENTIALS_TRANSPORT_CHANNEL_CREDS_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <type_traits>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"

struct grpc_channel_credentials;

namespace grpc_core {

class ChannelCredsConfig : public RefCounted<ChannelCredsConfig> {
 public:
  virtual absl::string_view type() const = 0;

  virtual bool Equals(const ChannelCredsConfig& other) const = 0;

  virtual std::string ToString() const = 0;
};

template <typename T = grpc_channel_credentials>
class ChannelCredsFactory final {
 public:
  virtual ~ChannelCredsFactory() {}
  virtual absl::string_view type() const = delete;
  virtual RefCountedPtr<ChannelCredsConfig> ParseConfig(
      const Json& config, const JsonArgs& args,
      ValidationErrors* errors) const = delete;
  virtual RefCountedPtr<T> CreateChannelCreds(
      RefCountedPtr<ChannelCredsConfig> config) const = delete;
};

template <>
class ChannelCredsFactory<grpc_channel_credentials> {
 public:
  virtual ~ChannelCredsFactory() {}
  virtual absl::string_view type() const = 0;
  virtual RefCountedPtr<ChannelCredsConfig> ParseConfig(
      const Json& config, const JsonArgs& args,
      ValidationErrors* errors) const = 0;
  virtual RefCountedPtr<grpc_channel_credentials> CreateChannelCreds(
      RefCountedPtr<ChannelCredsConfig> config) const = 0;
};

template <typename T = grpc_channel_credentials>
class ChannelCredsRegistry {
 private:
  using FactoryMap =
      std::map<absl::string_view, std::unique_ptr<ChannelCredsFactory<T>>>;

 public:
  static_assert(std::is_base_of<grpc_channel_credentials, T>::value,
                "ChannelCredsRegistry must be instantiated with "
                "grpc_channel_credentials.");

  class Builder {
   public:
    void RegisterChannelCredsFactory(
        std::unique_ptr<ChannelCredsFactory<T>> factory) {
      absl::string_view type = factory->type();
      factories_[type] = std::move(factory);
    }
    ChannelCredsRegistry Build() {
      return ChannelCredsRegistry<T>(std::move(factories_));
    }

   private:
    FactoryMap factories_;
  };

  bool IsSupported(absl::string_view type) const {
    return factories_.find(type) != factories_.end();
  }

  RefCountedPtr<ChannelCredsConfig> ParseConfig(
      absl::string_view type, const Json& config, const JsonArgs& args,
      ValidationErrors* errors) const {
    const auto it = factories_.find(type);
    if (it == factories_.cend()) return nullptr;
    return it->second->ParseConfig(config, args, errors);
  }

  RefCountedPtr<T> CreateChannelCreds(
      RefCountedPtr<ChannelCredsConfig> config) const {
    if (config == nullptr) return nullptr;
    const auto it = factories_.find(config->type());
    if (it == factories_.cend()) return nullptr;
    return it->second->CreateChannelCreds(std::move(config));
  }

 private:
  explicit ChannelCredsRegistry(FactoryMap factories)
      : factories_(std::move(factories)) {}

  FactoryMap factories_;
};

}

#endif
