// Copyright 2024 The gRPC Authors

#include "absl/strings/string_view.h"

namespace grpc_core {

namespace {
bool IsGlob(absl::string_view trace_glob) {
  return std::any_of(trace_glob.begin(), trace_glob.end(),
                     [](const char c) { return c == '?' || c == '*'; });
}
}

bool GlobMatch(absl::string_view name, absl::string_view pattern) {
  if (!IsGlob(pattern)) return name == pattern;
  size_t name_idx = 0;
  size_t trace_idx = 0;

  size_t name_next_idx = name_idx;
  size_t trace_next_idx = trace_idx;

  while (trace_idx < pattern.length() || name_idx < name.length()) {
    if (trace_idx < pattern.length()) {
      switch (pattern.at(trace_idx)) {
        case '?':
          if (name_idx < name.length()) {
            ++trace_idx;
            ++name_idx;
            continue;
          }
          break;
        case '*':
          trace_next_idx = trace_idx;
          name_next_idx = name_idx + 1;
          ++trace_idx;
          continue;
        default:
          if (name_idx < name.length() &&
              name.at(name_idx) == pattern.at(trace_idx)) {
            ++trace_idx;
            ++name_idx;
            continue;
          }
          break;
      }
    }

    if (name_next_idx > 0 && name_next_idx <= name.length()) {
      trace_idx = trace_next_idx;
      name_idx = name_next_idx;
      continue;
    }
    return false;
  }
  return true;
}

}
