
// Copyright 2022 gRPC authors.

#include "src/core/xds/grpc/xds_cluster_specifier_plugin.h"

#include <grpc/support/json.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <map>
#include <utility>
#include <variant>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_reader.h"
#include "src/proto/grpc/lookup/v1/rls_config.upb.h"
#include "src/proto/grpc/lookup/v1/rls_config.upbdefs.h"
#include "upb/base/status.hpp"
#include "upb/json/encode.h"
#include "upb/mem/arena.hpp"

namespace grpc_core {

absl::string_view XdsRouteLookupClusterSpecifierPlugin::ConfigProtoName()
    const {
  return "grpc.lookup.v1.RouteLookupClusterSpecifier";
}

void XdsRouteLookupClusterSpecifierPlugin::PopulateSymtab(
    upb_DefPool* symtab) const {
  grpc_lookup_v1_RouteLookupConfig_getmsgdef(symtab);
}

Json XdsRouteLookupClusterSpecifierPlugin::GenerateLoadBalancingPolicyConfig(
    XdsExtension extension, upb_Arena* arena, upb_DefPool* symtab,
    ValidationErrors* errors) const {
  absl::string_view* serialized_plugin_config =
      std::get_if<absl::string_view>(&extension.value);
  if (serialized_plugin_config == nullptr) {
    errors->AddError("could not parse plugin config");
    return {};
  }
  const auto* specifier = grpc_lookup_v1_RouteLookupClusterSpecifier_parse(
      serialized_plugin_config->data(), serialized_plugin_config->size(),
      arena);
  if (specifier == nullptr) {
    errors->AddError("could not parse plugin config");
    return {};
  }
  const auto* plugin_config = reinterpret_cast<const upb_Message*>(
      grpc_lookup_v1_RouteLookupClusterSpecifier_route_lookup_config(
          specifier));
  if (plugin_config == nullptr) {
    ValidationErrors::ScopedField field(errors, ".route_lookup_config");
    errors->AddError("field not present");
    return {};
  }
  upb::Status status;
  const upb_MessageDef* msg_type =
      grpc_lookup_v1_RouteLookupConfig_getmsgdef(symtab);
  size_t json_size = upb_JsonEncode(plugin_config, msg_type, symtab, 0, nullptr,
                                    0, status.ptr());
  if (json_size == static_cast<size_t>(-1)) {
    errors->AddError(absl::StrCat("failed to dump proto to JSON: ",
                                  upb_Status_ErrorMessage(status.ptr())));
    return {};
  }
  void* buf = upb_Arena_Malloc(arena, json_size + 1);
  upb_JsonEncode(plugin_config, msg_type, symtab, 0,
                 reinterpret_cast<char*>(buf), json_size + 1, status.ptr());
  auto json = JsonParse(reinterpret_cast<char*>(buf));
  CHECK(json.ok());
  return Json::FromArray({Json::FromObject(
      {{"rls_experimental",
        Json::FromObject({
            {"routeLookupConfig", std::move(*json)},
            {"childPolicy",
             Json::FromArray({
                 Json::FromObject({{"cds_experimental",
                                    Json::FromObject({
                                        {"isDynamic", Json::FromBool(true)},
                                    })}}),
             })},
            {"childPolicyConfigTargetFieldName", Json::FromString("cluster")},
        })}})});
}

XdsClusterSpecifierPluginRegistry::XdsClusterSpecifierPluginRegistry() {
  RegisterPlugin(std::make_unique<XdsRouteLookupClusterSpecifierPlugin>());
}

void XdsClusterSpecifierPluginRegistry::RegisterPlugin(
    std::unique_ptr<XdsClusterSpecifierPluginImpl> plugin) {
  absl::string_view name = plugin->ConfigProtoName();
  registry_[name] = std::move(plugin);
}

const XdsClusterSpecifierPluginImpl*
XdsClusterSpecifierPluginRegistry::GetPluginForType(
    absl::string_view config_proto_type_name) const {
  auto it = registry_.find(config_proto_type_name);
  if (it == registry_.end()) return nullptr;
  return it->second.get();
}

void XdsClusterSpecifierPluginRegistry::PopulateSymtab(
    upb_DefPool* symtab) const {
  for (const auto& [_, plugin] : registry_) {
    plugin->PopulateSymtab(symtab);
  }
}

}
