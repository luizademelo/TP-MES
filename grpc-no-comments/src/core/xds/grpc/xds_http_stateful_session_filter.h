
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_STATEFUL_SESSION_FILTER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_STATEFUL_SESSION_FILTER_H

#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/grpc/xds_http_filter.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsHttpStatefulSessionFilter final : public XdsHttpFilterImpl {
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
  void AddFilter(InterceptionChainBuilder& builder) const override;
  const grpc_channel_filter* channel_filter() const override;
  ChannelArgs ModifyChannelArgs(const ChannelArgs& args) const override;
  absl::StatusOr<ServiceConfigJsonEntry> GenerateMethodConfig(
      const FilterConfig& hcm_filter_config,
      const FilterConfig* filter_config_override) const override;
  absl::StatusOr<ServiceConfigJsonEntry> GenerateServiceConfig(
      const FilterConfig& hcm_filter_config) const override;
  bool IsSupportedOnClients() const override { return true; }
  bool IsSupportedOnServers() const override { return false; }
};

}

#endif
