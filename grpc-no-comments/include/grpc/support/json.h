
// Copyright 2015 gRPC authors.

#ifndef GRPC_SUPPORT_JSON_H
#define GRPC_SUPPORT_JSON_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "absl/strings/str_cat.h"

namespace grpc_core {
namespace experimental {

class Json {
 public:

  enum class Type {
    kNull,
    kBoolean,
    kNumber,

    kString,
    kObject,
    kArray,
  };

  using Object = std::map<std::string, Json>;
  using Array = std::vector<Json>;

  static Json FromBool(bool b) {
    Json json;
    json.value_ = b;
    return json;
  }

  static Json FromNumber(const std::string& str) {
    Json json;
    json.value_ = NumberValue{str};
    return json;
  }
  static Json FromNumber(const char* str) {
    Json json;
    json.value_ = NumberValue{std::string(str)};
    return json;
  }
  static Json FromNumber(std::string&& str) {
    Json json;
    json.value_ = NumberValue{std::move(str)};
    return json;
  }
  template <typename T>
  static std::enable_if_t<std::is_arithmetic_v<T>, Json> FromNumber(T value) {
    Json json;
    json.value_ = NumberValue{absl::StrCat(value)};
    return json;
  }

  static Json FromString(const std::string& str) {
    Json json;
    json.value_ = str;
    return json;
  }
  static Json FromString(const char* str) {
    Json json;
    json.value_ = std::string(str);
    return json;
  }
  static Json FromString(std::string&& str) {
    Json json;
    json.value_ = std::move(str);
    return json;
  }

  static Json FromObject(const Object& object) {
    Json json;
    json.value_ = object;
    return json;
  }
  static Json FromObject(Object&& object) {
    Json json;
    json.value_ = std::move(object);
    return json;
  }

  static Json FromArray(const Array& array) {
    Json json;
    json.value_ = array;
    return json;
  }
  static Json FromArray(Array&& array) {
    Json json;
    json.value_ = std::move(array);
    return json;
  }

  Json() = default;

  Json(const Json& other) = default;
  Json& operator=(const Json& other) = default;

  Json(Json&& other) noexcept : value_(std::move(other.value_)) {
    other.value_ = std::monostate();
  }
  Json& operator=(Json&& other) noexcept {
    value_ = std::move(other.value_);
    other.value_ = std::monostate();
    return *this;
  }

  Type type() const {
    struct ValueFunctor {
      Json::Type operator()(const std::monostate&) { return Type::kNull; }
      Json::Type operator()(bool) { return Type::kBoolean; }
      Json::Type operator()(const NumberValue&) { return Type::kNumber; }
      Json::Type operator()(const std::string&) { return Type::kString; }
      Json::Type operator()(const Object&) { return Type::kObject; }
      Json::Type operator()(const Array&) { return Type::kArray; }
    };
    return std::visit(ValueFunctor(), value_);
  }

  bool boolean() const { return std::get<bool>(value_); }

  const std::string& string() const {
    const NumberValue* num = std::get_if<NumberValue>(&value_);
    if (num != nullptr) return num->value;
    return std::get<std::string>(value_);
  }

  const Object& object() const { return std::get<Object>(value_); }

  const Array& array() const { return std::get<Array>(value_); }

  bool operator==(const Json& other) const { return value_ == other.value_; }
  bool operator!=(const Json& other) const { return !(*this == other); }

 private:
  struct NumberValue {
    std::string value;

    bool operator==(const NumberValue& other) const {
      return value == other.value;
    }
  };
  using Value = std::variant<std::monostate,
                             bool,
                             NumberValue,
                             std::string,
                             Object,
                             Array>;

  explicit Json(Value value) : value_(std::move(value)) {}

  Value value_;
};

}
}

#endif
