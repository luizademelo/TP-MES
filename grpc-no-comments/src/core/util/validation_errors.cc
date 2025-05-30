// Copyright 2020 gRPC authors.

#include "src/core/util/validation_errors.h"

#include <grpc/support/port_platform.h>
#include <inttypes.h>

#include <utility>

#include "absl/log/log.h"
#include "absl/status/status.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/strings/strip.h"

namespace grpc_core {

void ValidationErrors::PushField(absl::string_view ext) {

  if (fields_.empty()) absl::ConsumePrefix(&ext, ".");
  fields_.emplace_back(std::string(ext));
}

void ValidationErrors::PopField() { fields_.pop_back(); }

void ValidationErrors::AddError(absl::string_view error) {
  auto key = absl::StrJoin(fields_, "");
  if (field_errors_[key].size() >= max_error_count_) {
    VLOG(2) << "Ignoring validation error: too many errors found ("
            << max_error_count_ << ")";
    return;
  }
  field_errors_[key].emplace_back(error);
}

bool ValidationErrors::FieldHasErrors() const {
  return field_errors_.find(absl::StrJoin(fields_, "")) != field_errors_.end();
}

absl::Status ValidationErrors::status(absl::StatusCode code,
                                      absl::string_view prefix) const {
  if (field_errors_.empty()) return absl::OkStatus();
  return absl::Status(code, message(prefix));
}

std::string ValidationErrors::message(absl::string_view prefix) const {
  if (field_errors_.empty()) return "";
  std::vector<std::string> errors;
  for (const auto& [field, field_errors] : field_errors_) {
    if (field_errors.size() > 1) {
      errors.emplace_back(absl::StrCat("field:", field, " errors:[",
                                       absl::StrJoin(field_errors, "; "), "]"));
    } else {
      errors.emplace_back(
          absl::StrCat("field:", field, " error:", field_errors[0]));
    }
  }
  return absl::StrCat(prefix, ": [", absl::StrJoin(errors, "; "), "]");
}

}
