
// Copyright 2020 gRPC authors.

#include "src/core/util/json/json_util.h"

#include <grpc/support/port_platform.h>

#include "src/core/util/json/json_args.h"
#include "src/core/util/json/json_object_loader.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

bool ParseDurationFromJson(const Json& field, Duration* duration) {
  ValidationErrors errors;
  static_cast<json_detail::LoaderInterface*>(
      NoDestructSingleton<json_detail::AutoLoader<Duration>>::Get())
      ->LoadInto(field, JsonArgs(), duration, &errors);
  return errors.ok();
}

bool ExtractJsonBool(const Json& json, absl::string_view field_name,
                     bool* output, std::vector<grpc_error_handle>* error_list) {
  if (json.type() != Json::Type::kBoolean) {
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name, " error:type should be BOOLEAN")));
    return false;
  }
  *output = json.boolean();
  return true;
}

bool ExtractJsonArray(const Json& json, absl::string_view field_name,
                      const Json::Array** output,
                      std::vector<grpc_error_handle>* error_list) {
  if (json.type() != Json::Type::kArray) {
    *output = nullptr;
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name, " error:type should be ARRAY")));
    return false;
  }
  *output = &json.array();
  return true;
}

bool ExtractJsonObject(const Json& json, absl::string_view field_name,
                       const Json::Object** output,
                       std::vector<grpc_error_handle>* error_list) {
  if (json.type() != Json::Type::kObject) {
    *output = nullptr;
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name, " error:type should be OBJECT")));
    return false;
  }
  *output = &json.object();
  return true;
}

bool ParseJsonObjectFieldAsDuration(const Json::Object& object,
                                    absl::string_view field_name,
                                    Duration* output,
                                    std::vector<grpc_error_handle>* error_list,
                                    bool required) {

  auto it = object.find(std::string(field_name));
  if (it == object.end()) {
    if (required) {
      error_list->push_back(GRPC_ERROR_CREATE(
          absl::StrCat("field:", field_name, " error:does not exist.")));
    }
    return false;
  }
  if (!ParseDurationFromJson(it->second, output)) {
    *output = Duration::NegativeInfinity();
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name,
                     " error:type should be STRING of the form given by "
                     "google.proto.Duration.")));
    return false;
  }
  return true;
}

}
