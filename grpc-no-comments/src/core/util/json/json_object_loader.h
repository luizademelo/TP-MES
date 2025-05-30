// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_OBJECT_LOADER_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_OBJECT_LOADER_H

#include <grpc/support/port_platform.h>

#include <cstdint>
#include <cstring>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/meta/type_traits.h"
#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "src/core/util/json/json.h"
#include "src/core/util/json/json_args.h"
#include "src/core/util/no_destruct.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"
#include "src/core/util/validation_errors.h"

//       // Note: Field names must be string constants; they are not copied.

namespace grpc_core {

namespace json_detail {

class LoaderInterface {
 public:

  virtual void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                        ValidationErrors* errors) const = 0;

 protected:
  ~LoaderInterface() = default;
};

class LoadScalar : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadScalar() = default;

 private:

  virtual bool IsNumber() const = 0;

  virtual void LoadInto(const std::string& json, void* dst,
                        ValidationErrors* errors) const = 0;
};

class LoadString : public LoadScalar {
 protected:
  ~LoadString() = default;

 private:
  bool IsNumber() const override;
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override;
};

class LoadDuration : public LoadScalar {
 protected:
  ~LoadDuration() = default;

 private:
  bool IsNumber() const override;
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override;
};

class LoadNumber : public LoadScalar {
 protected:
  ~LoadNumber() = default;

 private:
  bool IsNumber() const override;
};

template <typename T>
class TypedLoadSignedNumber : public LoadNumber {
 protected:
  ~TypedLoadSignedNumber() = default;

 private:
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override {
    if (!absl::SimpleAtoi(value, static_cast<T*>(dst))) {
      errors->AddError("failed to parse number");
    }
  }
};

template <typename T>
class TypedLoadUnsignedNumber : public LoadNumber {
 protected:
  ~TypedLoadUnsignedNumber() = default;

 private:
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override {
    if (!absl::SimpleAtoi(value, static_cast<T*>(dst))) {
      errors->AddError("failed to parse non-negative number");
    }
  }
};

class LoadFloat : public LoadNumber {
 protected:
  ~LoadFloat() = default;

 private:
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override {
    if (!absl::SimpleAtof(value, static_cast<float*>(dst))) {
      errors->AddError("failed to parse floating-point number");
    }
  }
};

class LoadDouble : public LoadNumber {
 protected:
  ~LoadDouble() = default;

 private:
  void LoadInto(const std::string& value, void* dst,
                ValidationErrors* errors) const override {
    if (!absl::SimpleAtod(value, static_cast<double*>(dst))) {
      errors->AddError("failed to parse floating-point number");
    }
  }
};

class LoadBool : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& , void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadBool() = default;
};

class LoadUnprocessedJsonObject : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& , void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadUnprocessedJsonObject() = default;
};

class LoadUnprocessedJsonArray : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& , void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadUnprocessedJsonArray() = default;
};

class LoadVector : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadVector() = default;

 private:
  virtual void* EmplaceBack(void* dst) const = 0;
  virtual const LoaderInterface* ElementLoader() const = 0;
};

class LoadMap : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadMap() = default;

 private:
  virtual void* Insert(const std::string& name, void* dst) const = 0;
  virtual const LoaderInterface* ElementLoader() const = 0;
};

class LoadWrapped : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override;

 protected:
  ~LoadWrapped() = default;

 private:
  virtual void* Emplace(void* dst) const = 0;
  virtual void Reset(void* dst) const = 0;
  virtual const LoaderInterface* ElementLoader() const = 0;
};

template <typename T>
const LoaderInterface* LoaderForType();

template <typename T>
class AutoLoader final : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override {
    T::JsonLoader(args)->LoadInto(json, args, dst, errors);
  }

 private:
  ~AutoLoader() = default;
};

template <>
class AutoLoader<std::string> final : public LoadString {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<Duration> final : public LoadDuration {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<int32_t> final : public TypedLoadSignedNumber<int32_t> {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<int64_t> final : public TypedLoadSignedNumber<int64_t> {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<uint32_t> final : public TypedLoadUnsignedNumber<uint32_t> {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<uint64_t> final : public TypedLoadUnsignedNumber<uint64_t> {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<float> final : public LoadFloat {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<double> final : public LoadDouble {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<bool> final : public LoadBool {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<Json::Object> final : public LoadUnprocessedJsonObject {
 private:
  ~AutoLoader() = default;
};
template <>
class AutoLoader<Json::Array> final : public LoadUnprocessedJsonArray {
 private:
  ~AutoLoader() = default;
};

template <typename T>
class AutoLoader<std::vector<T>> final : public LoadVector {
 private:
  ~AutoLoader() = default;
  void* EmplaceBack(void* dst) const final {
    auto* vec = static_cast<std::vector<T>*>(dst);
    vec->emplace_back();
    return &vec->back();
  }
  const LoaderInterface* ElementLoader() const final {
    return LoaderForType<T>();
  }
};

template <>
class AutoLoader<std::vector<bool>> final : public LoaderInterface {
 public:
  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override;

 private:
  ~AutoLoader() = default;
};

template <typename T, typename C>
class AutoLoader<std::map<std::string, T, C>> final : public LoadMap {
 private:
  void* Insert(const std::string& name, void* dst) const final {
    return &static_cast<std::map<std::string, T, C>*>(dst)
                ->emplace(name, T())
                .first->second;
  };
  const LoaderInterface* ElementLoader() const final {
    return LoaderForType<T>();
  }

  ~AutoLoader() = default;
};

template <typename T>
class AutoLoader<std::optional<T>> final : public LoadWrapped {
 public:
  void* Emplace(void* dst) const final {
    return &static_cast<std::optional<T>*>(dst)->emplace();
  }
  void Reset(void* dst) const final {
    static_cast<std::optional<T>*>(dst)->reset();
  }
  const LoaderInterface* ElementLoader() const final {
    return LoaderForType<T>();
  }

 private:
  ~AutoLoader() = default;
};

template <typename T>
class AutoLoader<std::unique_ptr<T>> final : public LoadWrapped {
 public:
  void* Emplace(void* dst) const final {
    auto& p = *static_cast<std::unique_ptr<T>*>(dst);
    p = std::make_unique<T>();
    return p.get();
  }
  void Reset(void* dst) const final {
    static_cast<std::unique_ptr<T>*>(dst)->reset();
  }
  const LoaderInterface* ElementLoader() const final {
    return LoaderForType<T>();
  }

 private:
  ~AutoLoader() = default;
};

template <typename T>
class AutoLoader<RefCountedPtr<T>> final : public LoadWrapped {
 public:
  void* Emplace(void* dst) const final {
    auto& p = *static_cast<RefCountedPtr<T>*>(dst);
    p = MakeRefCounted<T>();
    return p.get();
  }
  void Reset(void* dst) const final {
    static_cast<RefCountedPtr<T>*>(dst)->reset();
  }
  const LoaderInterface* ElementLoader() const final {
    return LoaderForType<T>();
  }

 private:
  ~AutoLoader() = default;
};

template <typename T>
const LoaderInterface* LoaderForType() {
  return NoDestructSingleton<AutoLoader<T>>::Get();
}

struct Element {
  Element() = default;
  template <typename A, typename B>
  Element(const char* name, bool optional, B A::* p,
          const LoaderInterface* loader, const char* enable_key)
      : loader(loader),
        member_offset(static_cast<uint16_t>(
            reinterpret_cast<uintptr_t>(&(static_cast<A*>(nullptr)->*p)))),
        optional(optional),
        name(name),
        enable_key(enable_key) {}

  const LoaderInterface* loader;

  uint16_t member_offset;

  bool optional;

  const char* name;

  const char* enable_key;
};

template <typename T, size_t kSize>
class Vec {
 public:
  Vec(const Vec<T, kSize - 1>& other, const T& new_value) {
    for (size_t i = 0; i < other.size(); i++) values_[i] = other.data()[i];
    values_[kSize - 1] = new_value;
  }

  const T* data() const { return values_; }
  size_t size() const { return kSize; }

 private:
  T values_[kSize];
};

template <typename T>
class Vec<T, 0> {
 public:
  const T* data() const { return nullptr; }
  size_t size() const { return 0; }
};

bool LoadObject(const Json& json, const JsonArgs& args, const Element* elements,
                size_t num_elements, void* dst, ValidationErrors* errors);

template <typename T, size_t kElemCount, typename Hidden = void>
class FinishedJsonObjectLoader final : public LoaderInterface {
 public:
  explicit FinishedJsonObjectLoader(const Vec<Element, kElemCount>& elements)
      : elements_(elements) {}

  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override {
    LoadObject(json, args, elements_.data(), elements_.size(), dst, errors);
  }

 private:
  GPR_NO_UNIQUE_ADDRESS Vec<Element, kElemCount> elements_;
};

template <typename T, size_t kElemCount>
class FinishedJsonObjectLoader<T, kElemCount,
                               absl::void_t<decltype(&T::JsonPostLoad)>>
    final : public LoaderInterface {
 public:
  explicit FinishedJsonObjectLoader(const Vec<Element, kElemCount>& elements)
      : elements_(elements) {}

  void LoadInto(const Json& json, const JsonArgs& args, void* dst,
                ValidationErrors* errors) const override {

    if (LoadObject(json, args, elements_.data(), elements_.size(), dst,
                   errors)) {
      static_cast<T*>(dst)->JsonPostLoad(json, args, errors);
    }
  }

 private:
  GPR_NO_UNIQUE_ADDRESS Vec<Element, kElemCount> elements_;
};

template <typename T, size_t kElemCount = 0>
class JsonObjectLoader final {
 public:
  JsonObjectLoader() {
    static_assert(kElemCount == 0,
                  "Only initial loader step can have kElemCount==0.");
  }

  FinishedJsonObjectLoader<T, kElemCount>* Finish() const {
    return new FinishedJsonObjectLoader<T, kElemCount>(elements_);
  }

  template <typename U>
  JsonObjectLoader<T, kElemCount + 1> Field(
      const char* name, U T::* p, const char* enable_key = nullptr) const {
    return Field(name, false, p, enable_key);
  }

  template <typename U>
  JsonObjectLoader<T, kElemCount + 1> OptionalField(
      const char* name, U T::* p, const char* enable_key = nullptr) const {
    return Field(name, true, p, enable_key);
  }

  JsonObjectLoader(const Vec<Element, kElemCount - 1>& elements,
                   Element new_element)
      : elements_(elements, new_element) {}

 private:
  template <typename U>
  JsonObjectLoader<T, kElemCount + 1> Field(const char* name, bool optional,
                                            U T::* p,
                                            const char* enable_key) const {
    return JsonObjectLoader<T, kElemCount + 1>(
        elements_, Element(name, optional, p, LoaderForType<U>(), enable_key));
  }

  GPR_NO_UNIQUE_ADDRESS Vec<Element, kElemCount> elements_;
};

const Json* GetJsonObjectField(const Json::Object& json,
                               absl::string_view field,
                               ValidationErrors* errors, bool required);

}

template <typename T>
using JsonObjectLoader = json_detail::JsonObjectLoader<T>;

using JsonLoaderInterface = json_detail::LoaderInterface;

template <typename T>
absl::StatusOr<T> LoadFromJson(
    const Json& json, const JsonArgs& args = JsonArgs(),
    absl::string_view error_prefix = "errors validating JSON") {
  ValidationErrors errors;
  T result{};
  json_detail::LoaderForType<T>()->LoadInto(json, args, &result, &errors);
  if (!errors.ok()) {
    return errors.status(absl::StatusCode::kInvalidArgument, error_prefix);
  }
  return std::move(result);
}

template <typename T>
T LoadFromJson(const Json& json, const JsonArgs& args,
               ValidationErrors* errors) {
  T result{};
  json_detail::LoaderForType<T>()->LoadInto(json, args, &result, errors);
  return result;
}

template <typename T>
std::optional<T> LoadJsonObjectField(const Json::Object& json,
                                     const JsonArgs& args,
                                     absl::string_view field,
                                     ValidationErrors* errors,
                                     bool required = true) {
  ValidationErrors::ScopedField error_field(errors, absl::StrCat(".", field));
  const Json* field_json =
      json_detail::GetJsonObjectField(json, field, errors, required);
  if (field_json == nullptr) return std::nullopt;
  T result{};
  size_t starting_error_size = errors->size();
  json_detail::LoaderForType<T>()->LoadInto(*field_json, args, &result, errors);
  if (errors->size() > starting_error_size) return std::nullopt;
  return std::move(result);
}

}

#endif
