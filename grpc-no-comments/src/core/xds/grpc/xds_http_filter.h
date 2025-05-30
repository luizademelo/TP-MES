
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_FILTER_H
#define GRPC_SRC_CORE_XDS_GRPC_XDS_HTTP_FILTER_H

#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/call/interception_chain.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/validation_errors.h"
#include "src/core/xds/grpc/xds_common_types.h"
#include "src/core/xds/xds_client/xds_resource_type.h"
#include "upb/reflection/def.h"

namespace grpc_core {

class XdsHttpFilterImpl {
 public:
  struct FilterConfig {
    absl::string_view config_proto_type_name;
    Json config;

    bool operator==(const FilterConfig& other) const {
      return config_proto_type_name == other.config_proto_type_name &&
             config == other.config;
    }
    std::string ToString() const {
      return absl::StrCat("{config_proto_type_name=", config_proto_type_name,
                          " config=", JsonDump(config), "}");
    }
  };

  struct ServiceConfigJsonEntry {

    std::string service_config_field_name;

    std::string element;
  };

  virtual ~XdsHttpFilterImpl() = default;

  virtual absl::string_view ConfigProtoName() const = 0;

  virtual absl::string_view OverrideConfigProtoName() const = 0;

  virtual void PopulateSymtab(upb_DefPool* symtab) const = 0;

  virtual std::optional<FilterConfig> GenerateFilterConfig(
      absl::string_view instance_name,
      const XdsResourceType::DecodeContext& context, XdsExtension extension,
      ValidationErrors* errors) const = 0;

  virtual std::optional<FilterConfig> GenerateFilterConfigOverride(
      absl::string_view instance_name,
      const XdsResourceType::DecodeContext& context, XdsExtension extension,
      ValidationErrors* errors) const = 0;

  virtual void AddFilter(InterceptionChainBuilder& builder) const = 0;

  virtual const grpc_channel_filter* channel_filter() const = 0;

  virtual ChannelArgs ModifyChannelArgs(const ChannelArgs& args) const {
    return args;
  }

  virtual absl::StatusOr<ServiceConfigJsonEntry> GenerateMethodConfig(
      const FilterConfig& hcm_filter_config,
      const FilterConfig* filter_config_override) const = 0;

  virtual absl::StatusOr<ServiceConfigJsonEntry> GenerateServiceConfig(
      const FilterConfig& hcm_filter_config) const = 0;

  virtual bool IsSupportedOnClients() const = 0;

  virtual bool IsSupportedOnServers() const = 0;

  virtual bool IsTerminalFilter() const { return false; }
};

}

#endif
