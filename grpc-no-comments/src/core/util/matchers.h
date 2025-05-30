// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_MATCHERS_H
#define GRPC_SRC_CORE_UTIL_MATCHERS_H

#include <grpc/support/port_platform.h>
#include <stdint.h>

#include <memory>
#include <optional>
#include <string>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "re2/re2.h"

namespace grpc_core {

class StringMatcher {
 public:
  enum class Type {
    kExact,
    kPrefix,
    kSuffix,
    kSafeRegex,
    kContains,
  };

  // Note: case_sensitive is ignored for type kSafeRegex.
  static absl::StatusOr<StringMatcher> Create(Type type,
                                              absl::string_view matcher,
                                              bool case_sensitive = true);

  StringMatcher() = default;
  StringMatcher(const StringMatcher& other);
  StringMatcher& operator=(const StringMatcher& other);
  StringMatcher(StringMatcher&& other) noexcept;
  StringMatcher& operator=(StringMatcher&& other) noexcept;
  bool operator==(const StringMatcher& other) const;

  bool Match(absl::string_view value) const;

  std::string ToString() const;

  Type type() const { return type_; }

  const std::string& string_matcher() const { return string_matcher_; }

  RE2* regex_matcher() const { return regex_matcher_.get(); }

  bool case_sensitive() const { return case_sensitive_; }

 private:
  StringMatcher(Type type, absl::string_view matcher, bool case_sensitive);
  explicit StringMatcher(std::unique_ptr<RE2> regex_matcher);

  Type type_ = Type::kExact;
  std::string string_matcher_;
  std::unique_ptr<RE2> regex_matcher_;
  bool case_sensitive_ = true;
};

class HeaderMatcher {
 public:
  enum class Type {
    kExact,
    kPrefix,
    kSuffix,
    kSafeRegex,
    kContains,
    kRange,
    kPresent,
  };

  static_assert(static_cast<StringMatcher::Type>(Type::kExact) ==
                StringMatcher::Type::kExact);
  static_assert(static_cast<StringMatcher::Type>(Type::kPrefix) ==
                StringMatcher::Type::kPrefix);
  static_assert(static_cast<StringMatcher::Type>(Type::kSuffix) ==
                StringMatcher::Type::kSuffix);
  static_assert(static_cast<StringMatcher::Type>(Type::kSafeRegex) ==
                StringMatcher::Type::kSafeRegex);
  static_assert(static_cast<StringMatcher::Type>(Type::kContains) ==
                StringMatcher::Type::kContains);

  static absl::StatusOr<HeaderMatcher> Create(absl::string_view name, Type type,
                                              absl::string_view matcher,
                                              int64_t range_start = 0,
                                              int64_t range_end = 0,
                                              bool present_match = false,
                                              bool invert_match = false,
                                              bool case_sensitive = true);

  static HeaderMatcher CreateFromStringMatcher(absl::string_view name,
                                               StringMatcher matcher,
                                               bool invert_match);

  HeaderMatcher() = default;
  HeaderMatcher(const HeaderMatcher& other);
  HeaderMatcher& operator=(const HeaderMatcher& other);
  HeaderMatcher(HeaderMatcher&& other) noexcept;
  HeaderMatcher& operator=(HeaderMatcher&& other) noexcept;
  bool operator==(const HeaderMatcher& other) const;

  const std::string& name() const { return name_; }

  Type type() const { return type_; }

  const std::string& string_matcher() const {
    return matcher_.string_matcher();
  }

  RE2* regex_matcher() const { return matcher_.regex_matcher(); }

  bool Match(const std::optional<absl::string_view>& value) const;

  std::string ToString() const;

 private:

  HeaderMatcher(absl::string_view name, Type type, StringMatcher matcher,
                bool invert_match);

  HeaderMatcher(absl::string_view name, int64_t range_start, int64_t range_end,
                bool invert_match);

  HeaderMatcher(absl::string_view name, bool present_match, bool invert_match);

  std::string name_;
  Type type_ = Type::kExact;
  StringMatcher matcher_;
  int64_t range_start_;
  int64_t range_end_;
  bool present_match_;
  bool invert_match_ = false;
};

}

#endif
