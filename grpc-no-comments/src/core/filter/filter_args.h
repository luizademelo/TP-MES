// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_FILTER_FILTER_ARGS_H
#define GRPC_SRC_CORE_FILTER_FILTER_ARGS_H

#include "src/core/filter/blackboard.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/util/match.h"

namespace grpc_core {

class FilterArgs {
 public:
  FilterArgs() : FilterArgs(nullptr, nullptr, nullptr) {}
  FilterArgs(grpc_channel_stack* channel_stack,
             grpc_channel_element* channel_element,
             size_t (*channel_stack_filter_instance_number)(
                 grpc_channel_stack*, grpc_channel_element*),
             const Blackboard* old_blackboard = nullptr,
             Blackboard* new_blackboard = nullptr)
      : impl_(ChannelStackBased{channel_stack, channel_element,
                                channel_stack_filter_instance_number}),
        old_blackboard_(old_blackboard),
        new_blackboard_(new_blackboard) {}

  FilterArgs(size_t instance_id, const Blackboard* old_blackboard = nullptr,
             Blackboard* new_blackboard = nullptr)
      : impl_(V3Based{instance_id}),
        old_blackboard_(old_blackboard),
        new_blackboard_(new_blackboard) {}

  ABSL_DEPRECATED("Direct access to channel stack is deprecated")
  grpc_channel_stack* channel_stack() const {
    return std::get<ChannelStackBased>(impl_).channel_stack;
  }

  size_t instance_id() const {
    return Match(
        impl_,
        [](const ChannelStackBased& cs) {
          return cs.channel_stack_filter_instance_number(cs.channel_stack,
                                                         cs.channel_element);
        },
        [](const V3Based& v3) { return v3.instance_id; });
  }

  template <typename T>
  RefCountedPtr<T> GetOrCreateState(
      const std::string& key,
      absl::FunctionRef<RefCountedPtr<T>()> create_func) {
    RefCountedPtr<T> state;
    if (old_blackboard_ != nullptr) state = old_blackboard_->Get<T>(key);
    if (state == nullptr) state = create_func();
    if (new_blackboard_ != nullptr) new_blackboard_->Set(key, state);
    return state;
  }

 private:
  friend class ChannelFilter;

  struct ChannelStackBased {
    grpc_channel_stack* channel_stack;
    grpc_channel_element* channel_element;
    size_t (*channel_stack_filter_instance_number)(grpc_channel_stack*,
                                                   grpc_channel_element*);
  };

  struct V3Based {
    size_t instance_id;
  };

  using Impl = std::variant<ChannelStackBased, V3Based>;
  Impl impl_;

  const Blackboard* old_blackboard_ = nullptr;
  Blackboard* new_blackboard_ = nullptr;
};

}

#endif
