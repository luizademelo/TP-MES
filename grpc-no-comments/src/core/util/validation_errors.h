// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_VALIDATION_ERRORS_H
#define GRPC_SRC_CORE_UTIL_VALIDATION_ERRORS_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"

namespace grpc_core {

class ValidationErrors {
 public:

  static constexpr size_t kMaxErrorCount = 20;

  class ScopedField {
   public:
    ScopedField(ValidationErrors* errors, absl::string_view field_name)
        : errors_(errors) {
      errors_->PushField(field_name);
    }

    ScopedField(const ScopedField& other) = delete;
    ScopedField& operator=(const ScopedField& other) = delete;

    ScopedField(ScopedField&& other) noexcept
        : errors_(std::exchange(other.errors_, nullptr)) {}
    ScopedField& operator=(ScopedField&& other) noexcept {
      if (errors_ != nullptr) errors_->PopField();
      errors_ = std::exchange(other.errors_, nullptr);
      return *this;
    }

    ~ScopedField() {
      if (errors_ != nullptr) errors_->PopField();
    }

   private:
    ValidationErrors* errors_;
  };

  ValidationErrors() : ValidationErrors(kMaxErrorCount) {}

  explicit ValidationErrors(size_t max_error_count)
      : max_error_count_(max_error_count) {}

  void AddError(absl::string_view error) GPR_ATTRIBUTE_NOINLINE;

  bool FieldHasErrors() const GPR_ATTRIBUTE_NOINLINE;

  absl::Status status(absl::StatusCode code, absl::string_view prefix) const;

  std::string message(absl::string_view prefix) const;

  bool ok() const { return field_errors_.empty(); }

  size_t size() const { return field_errors_.size(); }

 private:

  void PushField(absl::string_view ext) GPR_ATTRIBUTE_NOINLINE;

  void PopField() GPR_ATTRIBUTE_NOINLINE;

  std::map<std::string , std::vector<std::string>> field_errors_;

  std::vector<std::string> fields_;

  size_t max_error_count_;
};

}

#endif
