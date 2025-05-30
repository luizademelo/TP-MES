
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_SPECIFIER_PLUGIN_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_CLUSTER_SPECIFIER_PLUGIN_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "upb/mem/arena.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsClusterSpecifierPluginImpl {
 public:
  virtual ~XdsClusterSpecifierPluginImpl() = default;

  virtual absl::string_view ConfigProtoName() const = 0;

  virtual void PopulateSymtab(upb_DefPool* symtab) const = 0;

  virtual Json GenerateLoadBalancingPolicyConfig(
      XdsExtension extension, upb_Arena* arena, upb_DefPool* symtab,
      ValidationErrors* errors) const = 0;
};

class XdsRouteLookupClusterSpecifierPlugin final
    : public XdsClusterSpecifierPluginImpl {
  absl::string_view ConfigProtoName() const override;

  void PopulateSymtab(upb_DefPool* symtab) const override;

  Json GenerateLoadBalancingPolicyConfig(
      XdsExtension extension, upb_Arena* arena, upb_DefPool* symtab,
      ValidationErrors* errors) const override;
};

class XdsClusterSpecifierPluginRegistry final {
 public:
  XdsClusterSpecifierPluginRegistry();

  XdsClusterSpecifierPluginRegistry(const XdsClusterSpecifierPluginRegistry&) =
      delete;
  XdsClusterSpecifierPluginRegistry& operator=(
      const XdsClusterSpecifierPluginRegistry&) = delete;

  XdsClusterSpecifierPluginRegistry(
      XdsClusterSpecifierPluginRegistry&& other) noexcept
      : registry_(std::move(other.registry_)) {}
  XdsClusterSpecifierPluginRegistry& operator=(
      XdsClusterSpecifierPluginRegistry&& other) noexcept {
    registry_ = std::move(other.registry_);
    return *this;
  }

  void RegisterPlugin(std::unique_ptr<XdsClusterSpecifierPluginImpl> plugin);

  void PopulateSymtab(upb_DefPool* symtab) const;

  const XdsClusterSpecifierPluginImpl* GetPluginForType(
      absl::string_view config_proto_type_name) const;

 private:
  std::map<absl::string_view, std::unique_ptr<XdsClusterSpecifierPluginImpl>>
      registry_;
};

}

#endif
