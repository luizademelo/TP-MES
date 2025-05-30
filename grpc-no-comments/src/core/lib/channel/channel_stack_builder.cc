
// Copyright 2016 gRPC authors.

#include "src/core/lib/channel/channel_stack_builder.h"

#include <grpc/support/port_platform.h>

#include <algorithm>

#include "src/core/lib/channel/channel_args.h"

namespace grpc_core {

ChannelStackBuilder::ChannelStackBuilder(const char* name,
                                         grpc_channel_stack_type type,
                                         const ChannelArgs& channel_args)
    : name_(name), type_(type), args_(channel_args) {}

ChannelStackBuilder& ChannelStackBuilder::SetTarget(const char* target) {
  if (target == nullptr) {
    target_ = unknown_target();
  } else {
    target_ = target;
  }
  return *this;
}

void ChannelStackBuilder::PrependFilter(const grpc_channel_filter* filter) {
  stack_.insert(stack_.begin(), filter);
}

void ChannelStackBuilder::AppendFilter(const grpc_channel_filter* filter) {
  stack_.push_back(filter);
}

}
