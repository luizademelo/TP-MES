
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_UTIL_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_UTIL_H

#include <grpc/support/port_platform.h>

#include <algorithm>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/json/json.h"
#include "src/core/util/time.h"

namespace grpc_core {

bool ParseDurationFromJson(const Json& field, Duration* duration);

template <typename NumericType>
bool ExtractJsonNumber(const Json& json, absl::string_view field_name,
                       NumericType* output,
                       std::vector<grpc_error_handle>* error_list) {
  static_assert(std::is_integral<NumericType>::value, "Integral required");
  if (json.type() != Json::Type::kNumber &&
      json.type() != Json::Type::kString) {
    error_list->push_back(GRPC_ERROR_CREATE(absl::StrCat(
        "field:", field_name, " error:type should be NUMBER or STRING")));
    return false;
  }
  if (!absl::SimpleAtoi(json.string(), output)) {
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name, " error:failed to parse.")));
    return false;
  }
  return true;
}

bool ExtractJsonBool(const Json& json, absl::string_view field_name,
                     bool* output, std::vector<grpc_error_handle>* error_list);

template <typename OutputType>
bool ExtractJsonString(const Json& json, absl::string_view field_name,
                       OutputType* output,
                       std::vector<grpc_error_handle>* error_list) {
  if (json.type() != Json::Type::kString) {
    *output = "";
    error_list->push_back(GRPC_ERROR_CREATE(
        absl::StrCat("field:", field_name, " error:type should be STRING")));
    return false;
  }
  *output = json.string();
  return true;
}

bool ExtractJsonArray(const Json& json, absl::string_view field_name,
                      const Json::Array** output,
                      std::vector<grpc_error_handle>* error_list);

bool ExtractJsonObject(const Json& json, absl::string_view field_name,
                       const Json::Object** output,
                       std::vector<grpc_error_handle>* error_list);

template <typename NumericType>
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            NumericType* output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonNumber(json, field_name, output, error_list);
}
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            bool* output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonBool(json, field_name, output, error_list);
}
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            std::string* output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonString(json, field_name, output, error_list);
}
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            absl::string_view* output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonString(json, field_name, output, error_list);
}
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            const Json::Array** output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonArray(json, field_name, output, error_list);
}
inline bool ExtractJsonType(const Json& json, absl::string_view field_name,
                            const Json::Object** output,
                            std::vector<grpc_error_handle>* error_list) {
  return ExtractJsonObject(json, field_name, output, error_list);
}

template <typename T>
bool ParseJsonObjectField(const Json::Object& object,
                          absl::string_view field_name, T* output,
                          std::vector<grpc_error_handle>* error_list,
                          bool required = true) {

  auto it = object.find(std::string(field_name));
  if (it == object.end()) {
    if (required) {
      error_list->push_back(GRPC_ERROR_CREATE(
          absl::StrCat("field:", field_name, " error:does not exist.")));
    }
    return false;
  }
  auto& child_object_json = it->second;
  return ExtractJsonType(child_object_json, field_name, output, error_list);
}

bool ParseJsonObjectFieldAsDuration(const Json::Object& object,
                                    absl::string_view field_name,
                                    Duration* output,
                                    std::vector<grpc_error_handle>* error_list,
                                    bool required = true);

}

#endif
