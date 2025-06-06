
// Copyright 2022 gRPC authors.

#include "src/core/service_config/service_config_impl.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include <optional>
#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/memory.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

namespace {

struct MethodConfig {
  struct Name {
    std::optional<std::string> service;
    std::optional<std::string> method;

    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<Name>()
                                      .OptionalField("service", &Name::service)
                                      .OptionalField("method", &Name::method)
                                      .Finish();
      return loader;
    }

    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {
      if (!service.has_value() && method.has_value()) {
        errors->AddError("method name populated without service name");
      }
    }

    std::string Path() const {
      if (!service.has_value() || service->empty()) return "";
      return absl::StrCat("/", *service, "/",
                          method.has_value() ? *method : "");
    }
  };

  std::vector<Name> names;

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader = JsonObjectLoader<MethodConfig>()
                                    .OptionalField("name", &MethodConfig::names)
                                    .Finish();
    return loader;
  }
};

}

absl::StatusOr<RefCountedPtr<ServiceConfig>> ServiceConfigImpl::Create(
    const ChannelArgs& args, absl::string_view json_string) {
  auto json = JsonParse(json_string);
  if (!json.ok()) return json.status();
  ValidationErrors errors;
  auto service_config = Create(args, *json, json_string, &errors);
  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument,
                         "errors validating service config");
  }
  return service_config;
}

RefCountedPtr<ServiceConfig> ServiceConfigImpl::Create(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {
  return Create(args, json, JsonDump(json), errors);
}

RefCountedPtr<ServiceConfig> ServiceConfigImpl::Create(
    const ChannelArgs& args, const Json& json, absl::string_view json_string,
    ValidationErrors* errors) {
  if (json.type() != Json::Type::kObject) {
    errors->AddError("is not an object");
    return nullptr;
  }
  auto service_config = MakeRefCounted<ServiceConfigImpl>();
  service_config->json_string_ = std::string(json_string);

  service_config->parsed_global_configs_ =
      CoreConfiguration::Get().service_config_parser().ParseGlobalParameters(
          args, json, errors);

  auto method_configs = LoadJsonObjectField<std::vector<Json::Object>>(
      json.object(), JsonArgs(), "methodConfig", errors,
      false);
  if (method_configs.has_value()) {
    service_config->parsed_method_config_vectors_storage_.reserve(
        method_configs->size());
    for (size_t i = 0; i < method_configs->size(); ++i) {
      const Json method_config_json =
          Json::FromObject(std::move((*method_configs)[i]));
      ValidationErrors::ScopedField field(
          errors, absl::StrCat(".methodConfig[", i, "]"));

      auto parsed_configs =
          CoreConfiguration::Get()
              .service_config_parser()
              .ParsePerMethodParameters(args, method_config_json, errors);

      service_config->parsed_method_config_vectors_storage_.push_back(
          std::move(parsed_configs));
      const ServiceConfigParser::ParsedConfigVector* vector_ptr =
          &service_config->parsed_method_config_vectors_storage_.back();

      auto method_config =
          LoadFromJson<MethodConfig>(method_config_json, JsonArgs(), errors);
      for (size_t j = 0; j < method_config.names.size(); ++j) {
        ValidationErrors::ScopedField field(errors,
                                            absl::StrCat(".name[", j, "]"));
        std::string path = method_config.names[j].Path();
        if (path.empty()) {
          if (service_config->default_method_config_vector_ != nullptr) {
            errors->AddError("duplicate default method config");
          }
          service_config->default_method_config_vector_ = vector_ptr;
        } else {
          grpc_slice key = grpc_slice_from_cpp_string(std::move(path));

          auto& value = service_config->parsed_method_configs_map_[key];
          if (value != nullptr) {
            errors->AddError(absl::StrCat("multiple method configs for path ",
                                          StringViewFromSlice(key)));

            CSliceUnref(key);
          } else {
            value = vector_ptr;
          }
        }
      }
    }
  }
  return service_config;
}

ServiceConfigImpl::~ServiceConfigImpl() {
  for (auto& p : parsed_method_configs_map_) {
    CSliceUnref(p.first);
  }
}

const ServiceConfigParser::ParsedConfigVector*
ServiceConfigImpl::GetMethodParsedConfigVector(const grpc_slice& path) const {
  if (parsed_method_configs_map_.empty()) {
    return default_method_config_vector_;
  }

  auto it = parsed_method_configs_map_.find(path);
  if (it != parsed_method_configs_map_.end()) return it->second;

  UniquePtr<char> path_str(grpc_slice_to_c_string(path));
  char* sep = strrchr(path_str.get(), '/');
  if (sep == nullptr) return nullptr;
  sep[1] = '\0';
  grpc_slice wildcard_path = grpc_slice_from_static_string(path_str.get());
  it = parsed_method_configs_map_.find(wildcard_path);
  if (it != parsed_method_configs_map_.end()) return it->second;

  return default_method_config_vector_;
}

}
