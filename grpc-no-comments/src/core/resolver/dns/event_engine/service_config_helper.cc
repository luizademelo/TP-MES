// Copyright 2023 The gRPC Authors

#include "src/core/resolver/dns/event_engine/service_config_helper.h"

#include <grpc/support/port_platform.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/util/gethostname.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/json/json_reader.h"
#include "src/core/util/json/json_writer.h"
#include "src/core/util/status_helper.h"

namespace grpc_core {

namespace {

struct ServiceConfigChoice {
  std::vector<std::string> client_language;
  int percentage = -1;
  std::vector<std::string> client_hostname;
  Json::Object service_config;

  static const JsonLoaderInterface* JsonLoader(const JsonArgs&) {
    static const auto* loader =
        JsonObjectLoader<ServiceConfigChoice>()
            .OptionalField("clientLanguage",
                           &ServiceConfigChoice::client_language)
            .OptionalField("percentage", &ServiceConfigChoice::percentage)
            .OptionalField("clientHostname",
                           &ServiceConfigChoice::client_hostname)
            .Field("serviceConfig", &ServiceConfigChoice::service_config)
            .Finish();
    return loader;
  }
};

bool vector_contains(const std::vector<std::string>& v,
                     const std::string& value) {
  return std::find(v.begin(), v.end(), value) != v.end();
}

}

absl::StatusOr<std::string> ChooseServiceConfig(
    absl::string_view service_config_json) {
  auto json = JsonParse(service_config_json);
  GRPC_RETURN_IF_ERROR(json.status());
  auto choices = LoadFromJson<std::vector<ServiceConfigChoice>>(*json);
  GRPC_RETURN_IF_ERROR(choices.status());
  for (const ServiceConfigChoice& choice : *choices) {

    if (!choice.client_language.empty() &&
        !vector_contains(choice.client_language, "c++")) {
      continue;
    }

    if (!choice.client_hostname.empty()) {
      const char* hostname = grpc_gethostname();
      if (!vector_contains(choice.client_hostname, hostname)) {
        continue;
      }
    }

    if (choice.percentage != -1) {
      int random_pct = rand() % 100;
      if (random_pct > choice.percentage || choice.percentage == 0) {
        continue;
      }
    }
    return JsonDump(Json::FromObject(choice.service_config));
  }

  return "";
}

}
