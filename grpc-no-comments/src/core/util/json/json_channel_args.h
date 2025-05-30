// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_JSON_JSON_CHANNEL_ARGS_H
#define GRPC_SRC_CORE_UTIL_JSON_JSON_CHANNEL_ARGS_H

#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/util/json/json_args.h"

namespace grpc_core {

class JsonChannelArgs : public JsonArgs {
 public:
  explicit JsonChannelArgs(const ChannelArgs& args) : args_(args) {}

  bool IsEnabled(absl::string_view key) const override {
    return args_.GetBool(key).value_or(false);
  }

 private:
  ChannelArgs args_;
};

}

#endif
