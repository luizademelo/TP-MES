Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#include "src/core/xds/grpc/xds_server_grpc.h"

#include <stdlib.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/util/down_cast.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"

namespace grpc_core {

namespace {
// Constants defining various server feature flags
constexpr absl::string_view kServerFeatureIgnoreResourceDeletion =
    "ignore_resource_deletion";

constexpr absl::string_view kServerFeatureFailOnDataErrors =
    "fail_on_data_errors";

constexpr absl::string_view kServerFeatureResourceTimerIsTransientFailure =
    "resource_timer_is_transient_error";

constexpr absl::string_view kServerFeatureTrustedXdsServer =
    "trusted_xds_server";

}  // namespace

// Returns true if the server should ignore resource deletion notifications
bool GrpcXdsServer::IgnoreResourceDeletion() const {
  return server_features_.find(std::string(
             kServerFeatureIgnoreResourceDeletion)) != server_features_.end();
}

// Returns true if the server should fail on data errors
bool GrpcXdsServer::FailOnDataErrors() const {
  return server_features_.find(std::string(kServerFeatureFailOnDataErrors)) !=
         server_features_.end();
}

// Returns true if resource timer should be treated as transient failure
bool GrpcXdsServer::ResourceTimerIsTransientFailure() const {
  return server_features_.find(
             std::string(kServerFeatureResourceTimerIsTransientFailure)) !=
         server_features_.end();
}

// Returns true if the XDS server is trusted
bool GrpcXdsServer::TrustedXdsServer() const {
  return server_features_.find(std::string(kServerFeatureTrustedXdsServer)) !=
         server_features_.end();
}

// Compares this XDS server with another for equality
bool GrpcXdsServer::Equals(const XdsServer& other) const {
  const auto& o = DownCast<const GrpcXdsServer&>(other);
  return (server_target_->Equals(*o.server_target_) &&
          server_features_ == o.server_features_);
}

// Returns the JSON loader interface for this class
const JsonLoaderInterface* GrpcXdsServer::JsonLoader(const JsonArgs&) {
  static const auto* loader = JsonObjectLoader<GrpcXdsServer>().Finish();
  return loader;
}

namespace {
// Structure representing channel credentials configuration
struct ChannelCreds {
  std::string type;
  Json::Object config;

  // Returns the JSON loader interface for ChannelCreds
  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader =
        JsonObjectLoader<ChannelCreds>()
            .Field("type", &ChannelCreds::type)
            .OptionalField("config", &ChannelCreds::config)
            .Finish();
    return loader;
  }
};

}  // namespace

// Handles post-load processing of JSON configuration
void GrpcXdsServer::JsonPostLoad(const Json& json, const JsonArgs& args,
                                 ValidationErrors* errors) {
  RefCountedPtr<ChannelCredsConfig> channel_creds_config;
  {
    // Load and process channel credentials from JSON
    auto channel_creds_list = LoadJsonObjectField<std::vector<ChannelCreds>>(
        json.object(), args, "channel_creds", errors);
    if (channel_creds_list.has_value()) {
      ValidationErrors::ScopedField field(errors, ".channel_creds");
      for (size_t i = 0; i < channel_creds_list->size(); ++i) {
        ValidationErrors::ScopedField field(errors, absl::StrCat("[", i, "]"));
        auto& creds = (*channel_creds_list)[i];

        // Check if credential type is supported and parse its config
        if (CoreConfiguration::Get().channel_creds_registry().IsSupported(
                creds.type)) {
          ValidationErrors::ScopedField field(errors, ".config");
          auto config =
              CoreConfiguration::Get().channel_creds_registry().ParseConfig(
                  creds.type, Json::FromObject(creds.config), args, errors);
          if (channel_creds_config == nullptr) {
            channel_creds_config = std::move(config);
          }
        }
      }
      if (channel_creds_config == nullptr) {
        errors->AddError("no known creds type found");
      }
    }
  }

  {
    // Load and process server features from JSON
    ValidationErrors::ScopedField field(errors, ".server_features");
    auto it = json.object().find("server_features");
    if (it != json.object().end()) {
      if (it->second.type() != Json::Type::kArray) {
        errors->AddError("is not an array");
      } else {
        const Json::Array& array = it->second.array();
        for (const Json& feature_json : array) {
          // Only add recognized feature flags
          if (feature_json.type() == Json::Type::kString &&
              (feature_json.string() == kServerFeatureIgnoreResourceDeletion ||
               feature_json.string() == kServerFeatureFailOnDataErrors ||
               feature_json.string() ==
                   kServerFeatureResourceTimerIsTransientFailure ||
               feature_json.string() == kServerFeatureTrustedXdsServer)) {
            server_features_.insert(feature_json.string());
          }
        }
      }
    }
  }

  // Load server URI target and create server target object
  std::string server_uri_target = LoadJsonObjectField<std::string>(
                                      json.object(), args, "server_uri", errors)
                                      .value_or("");
  server_target_ = std::make_shared<GrpcXdsServerTarget>(
      std::move(server_uri_target), std::move(channel_creds_config));
}

// Generates a unique key for this XDS server configuration
std::string GrpcXdsServer::Key() const {
  std::vector<std::string> parts;
  parts.push_back("{");
  parts.push_back(absl::StrCat("target=", server_target_->Key()));
  if (!server_features_.empty()) {
    parts.push_back(absl::StrCat("server_features=[",
                                 absl::StrJoin(server_features_, ","), "]"));
  }
  parts.push_back("}");
  return absl::StrJoin(parts, ",");
}

// Generates a unique key for this XDS server target
std::string GrpcXdsServerTarget::Key() const {
  std::vector<std::string> parts;
  parts.push_back("{");
  parts.push_back(absl::StrCat("server_uri=", server_uri_));
  if (channel_creds_config_ != nullptr) {
    parts.push_back(absl::StrCat("creds_type=", channel_creds_config_->type()));
    parts.push_back(
        absl::StrCat("creds_config=", channel_creds_config_->ToString()));
  }
  parts.push_back("}");
  return absl::StrJoin(parts, ",");
}

// Compares this XDS server target with another for equality
bool GrpcXdsServerTarget::Equals(const XdsServerTarget& other) const {
  const auto& o = DownCast<const GrpcXdsServerTarget&>(other);
  return (server_uri_ == o.server_uri_ &&
          channel_creds_config_->type() == o.channel_creds_config_->type() &&
          channel_creds_config_->Equals(*o.channel_creds_config_));
}

}  // namespace grpc_core
```