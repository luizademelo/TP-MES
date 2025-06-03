Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

// Service configuration implementation for gRPC
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

// Represents a method configuration in the service config
struct MethodConfig {
  // Represents a method name in the configuration
  struct Name {
    std::optional<std::string> service;  // Optional service name
    std::optional<std::string> method;   // Optional method name

    // JSON loader for Name structure
    static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
      static const auto* loader = JsonObjectLoader<Name>()
                                      .OptionalField("service", &Name::service)
                                      .OptionalField("method", &Name::method)
                                      .Finish();
      return loader;
    }

    // Post-load validation for Name structure
    void JsonPostLoad(const Json&, const JsonArgs&, ValidationErrors* errors) {
      // Validate that method name isn't specified without service name
      if (!service.has_value() && method.has_value()) {
        errors->AddError("method name populated without service name");
      }
    }

    // Returns the path string for this method name (e.g., "/service/method")
    std::string Path() const {
      if (!service.has_value() || service->empty()) return "";
      return absl::StrCat("/", *service, "/",
                          method.has_value() ? *method : "");
    }
  };

  std::vector<Name> names;  // List of method names this config applies to

  // JSON loader for MethodConfig structure
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader = JsonObjectLoader<MethodConfig>()
                                    .OptionalField("name", &MethodConfig::names)
                                    .Finish();
    return loader;
  }
};

}  // namespace

// Creates a ServiceConfig from a JSON string
absl::StatusOr<RefCountedPtr<ServiceConfig>> ServiceConfigImpl::Create(
    const ChannelArgs& args, absl::string_view json_string) {
  // Parse the JSON string
  auto json = JsonParse(json_string);
  if (!json.ok()) return json.status();
  
  // Validate and create the service config
  ValidationErrors errors;
  auto service_config = Create(args, *json, json_string, &errors);
  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument,
                         "errors validating service config");
  }
  return service_config;
}

// Creates a ServiceConfig from a parsed JSON object
RefCountedPtr<ServiceConfig> ServiceConfigImpl::Create(
    const ChannelArgs& args, const Json& json, ValidationErrors* errors) {
  return Create(args, json, JsonDump(json), errors);
}

// Internal implementation of ServiceConfig creation
RefCountedPtr<ServiceConfig> ServiceConfigImpl::Create(
    const ChannelArgs& args, const Json& json, absl::string_view json_string,
    ValidationErrors* errors) {
  // Validate JSON is an object
  if (json.type() != Json::Type::kObject) {
    errors->AddError("is not an object");
    return nullptr;
  }
  
  // Create the service config instance
  auto service_config = MakeRefCounted<ServiceConfigImpl>();
  service_config->json_string_ = std::string(json_string);

  // Parse global parameters from the config
  service_config->parsed_global_configs_ =
      CoreConfiguration::Get().service_config_parser().ParseGlobalParameters(
          args, json, errors);

  // Parse method-specific configurations
  auto method_configs = LoadJsonObjectField<std::vector<Json::Object>>(
      json.object(), JsonArgs(), "methodConfig", errors,
      false);
  if (method_configs.has_value()) {
    // Reserve space for method configs
    service_config->parsed_method_config_vectors_storage_.reserve(
        method_configs->size());
    
    // Process each method config
    for (size_t i = 0; i < method_configs->size(); ++i) {
      const Json method_config_json =
          Json::FromObject(std::move((*method_configs)[i]));
      ValidationErrors::ScopedField field(
          errors, absl::StrCat(".methodConfig[", i, "]"));

      // Parse per-method parameters
      auto parsed_configs =
          CoreConfiguration::Get()
              .service_config_parser()
              .ParsePerMethodParameters(args, method_config_json, errors);

      // Store parsed configs
      service_config->parsed_method_config_vectors_storage_.push_back(
          std::move(parsed_configs));
      const ServiceConfigParser::ParsedConfigVector* vector_ptr =
          &service_config->parsed_method_config_vectors_storage_.back();

      // Load method config details
      auto method_config =
          LoadFromJson<MethodConfig>(method_config_json, JsonArgs(), errors);
      
      // Process each method name in the config
      for (size_t j = 0; j < method_config.names.size(); ++j) {
        ValidationErrors::ScopedField field(errors,
                                            absl::StrCat(".name[", j, "]"));
        std::string path = method_config.names[j].Path();
        
        // Handle default config (empty path)
        if (path.empty()) {
          if (service_config->default_method_config_vector_ != nullptr) {
            errors->AddError("duplicate default method config");
          }
          service_config->default_method_config_vector_ = vector_ptr;
        } else {
          // Handle specific method paths
          grpc_slice key = grpc_slice_from_cpp_string(std::move(path));

          auto& value = service_config->parsed_method_configs_map_[key];
          if (value != nullptr) {
            // Error if duplicate path found
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

// Destructor - cleans up allocated slices
ServiceConfigImpl::~ServiceConfigImpl() {
  for (auto& p : parsed_method_configs_map_) {
    CSliceUnref(p.first);
  }
}

// Gets the parsed config vector for a given method path
const ServiceConfigParser::ParsedConfigVector*
ServiceConfigImpl::GetMethodParsedConfigVector(const grpc_slice& path) const {
  // If no method-specific configs, return default
  if (parsed_method_configs_map_.empty()) {
    return default_method_config_vector_;
  }

  // Look for exact path match
  auto it = parsed_method_configs_map_.find(path);
  if (it != parsed_method_configs_map_.end()) return it->second;

  // Try wildcard matching (service/*)
  UniquePtr<char> path_str(grpc_slice_to_c_string(path));
  char* sep = strrchr(path_str.get(), '/');
  if (sep == nullptr) return nullptr;
  sep[1] = '\0';
  grpc_slice wildcard_path = grpc_slice_from_static_string(path_str.get());
  it = parsed_method_configs_map_.find(wildcard_path);
  if (it != parsed_method_configs_map_.end()) return it->second;

  // Fall back to default config
  return default_method_config_vector_;
}

}  // namespace grpc_core
```