// Copyright 2024 gRPC authors.

#include "src/core/util/dump_args.h"

#include "absl/log/check.h"
#include "absl/strings/ascii.h"
#include "absl/strings/string_view.h"

namespace grpc_core {
namespace dump_args_detail {

void DumpArgs::Stringify(CustomSink& sink) const {

  std::vector<absl::string_view> keys;
  int depth = 0;
  const char* start = arg_string_;
  for (const char* p = arg_string_; *p; ++p) {
    if (*p == '(') {
      ++depth;
    } else if (*p == ')') {
      --depth;
    } else if (*p == ',' && depth == 0) {
      keys.push_back(absl::string_view(start, p - start));
      start = p + 1;
    }
  }
  keys.push_back(start);
  CHECK_EQ(keys.size(), arg_dumpers_.size());
  for (size_t i = 0; i < keys.size(); i++) {
    if (i != 0) sink.Append(", ");
    sink.Append(absl::StripAsciiWhitespace(keys[i]));
    sink.Append(" = ");
    arg_dumpers_[i](sink);
  }
}

}
}
