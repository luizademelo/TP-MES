// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_BUILDER_H
#define GRPC_SRC_CORE_LIB_CHANNEL_CHANNEL_STACK_BUILDER_H

#include <grpc/support/port_platform.h>

#include <string>
#include <vector>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/surface/channel_stack_type.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class ChannelStackBuilder {
 public:

  ChannelStackBuilder(const char* name, grpc_channel_stack_type type,
                      const ChannelArgs& channel_args);

  const char* name() const { return name_; }

  ChannelStackBuilder& SetTarget(const char* target);

  absl::string_view target() const { return target_; }

  const ChannelArgs& channel_args() const { return args_; }

  std::vector<const grpc_channel_filter*>* mutable_stack() { return &stack_; }

  const std::vector<const grpc_channel_filter*>& stack() const {
    return stack_;
  }

  grpc_channel_stack_type channel_stack_type() const { return type_; }

  void PrependFilter(const grpc_channel_filter* filter);

  void AppendFilter(const grpc_channel_filter* filter);

  virtual absl::StatusOr<RefCountedPtr<grpc_channel_stack>> Build() = 0;

 protected:
  ~ChannelStackBuilder() = default;

 private:
  static std::string unknown_target() { return "unknown"; }

  const char* const name_;

  const grpc_channel_stack_type type_;

  std::string target_{unknown_target()};

  ChannelArgs args_;

  std::vector<const grpc_channel_filter*> stack_;
};

}

#endif
