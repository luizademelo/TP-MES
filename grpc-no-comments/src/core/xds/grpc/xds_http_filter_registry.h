
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_FILTER_REGISTRY_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_FILTER_REGISTRY_H

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/interception_chain.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsHttpRouterFilter final : public XdsHttpFilterImpl {
 public:
  absl::string_view ConfigProtoName() const override;
  absl::string_view OverrideConfigProtoName() const override;
  void PopulateSymtab(upb_DefPool* symtab) const override;
  std::optional<FilterConfig> GenerateFilterConfig(
      absl::string_view ,
      const XdsResourceType::DecodeContext& context, XdsExtension extension,
      ValidationErrors* errors) const override;
  std::optional<FilterConfig> GenerateFilterConfigOverride(
      absl::string_view ,
      const XdsResourceType::DecodeContext& context, XdsExtension extension,
      ValidationErrors* errors) const override;
  void AddFilter(InterceptionChainBuilder& ) const override {}
  const grpc_channel_filter* channel_filter() const override { return nullptr; }
  absl::StatusOr<ServiceConfigJsonEntry> GenerateMethodConfig(
      const FilterConfig& ,
      const FilterConfig* ) const override {

    return absl::UnimplementedError("router filter should never be called");
  }
  absl::StatusOr<ServiceConfigJsonEntry> GenerateServiceConfig(
      const FilterConfig& ) const override {

    return absl::UnimplementedError("router filter should never be called");
  }
  bool IsSupportedOnClients() const override { return true; }
  bool IsSupportedOnServers() const override { return true; }
  bool IsTerminalFilter() const override { return true; }
};

class XdsHttpFilterRegistry final {
 public:
  explicit XdsHttpFilterRegistry(bool register_builtins = true);

  XdsHttpFilterRegistry(const XdsHttpFilterRegistry&) = delete;
  XdsHttpFilterRegistry& operator=(const XdsHttpFilterRegistry&) = delete;

  XdsHttpFilterRegistry(XdsHttpFilterRegistry&& other) noexcept
      : owning_list_(std::move(other.owning_list_)),
        registry_map_(std::move(other.registry_map_)) {}
  XdsHttpFilterRegistry& operator=(XdsHttpFilterRegistry&& other) noexcept {
    owning_list_ = std::move(other.owning_list_);
    registry_map_ = std::move(other.registry_map_);
    return *this;
  }

  void RegisterFilter(std::unique_ptr<XdsHttpFilterImpl> filter);

  const XdsHttpFilterImpl* GetFilterForType(
      absl::string_view proto_type_name) const;

  void PopulateSymtab(upb_DefPool* symtab) const;

 private:
  std::vector<std::unique_ptr<XdsHttpFilterImpl>> owning_list_;
  std::map<absl::string_view, XdsHttpFilterImpl*> registry_map_;
};

}

#endif
