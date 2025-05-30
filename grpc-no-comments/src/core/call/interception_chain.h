// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_INTERCEPTION_CHAIN_H
#define GRPC_SRC_CORE_CALL_INTERCEPTION_CHAIN_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <vector>

#include "src/core/call/call_destination.h"
#include "src/core/call/call_filters.h"
#include "src/core/call/call_spine.h"
#include "src/core/call/metadata.h"
#include "src/core/util/ref_counted.h"

namespace grpc_core {

class Blackboard;
class InterceptionChainBuilder;

class HijackedCall final {
 public:
  HijackedCall(ClientMetadataHandle metadata,
               RefCountedPtr<UnstartedCallDestination> destination,
               CallHandler call_handler)
      : metadata_(std::move(metadata)),
        destination_(std::move(destination)),
        call_handler_(std::move(call_handler)) {}

  CallInitiator MakeCall();

  CallInitiator MakeLastCall() {
    return MakeCallWithMetadata(std::move(metadata_));
  }

  CallHandler& original_call_handler() { return call_handler_; }

  ClientMetadata& client_metadata() { return *metadata_; }

 private:
  CallInitiator MakeCallWithMetadata(ClientMetadataHandle metadata);

  ClientMetadataHandle metadata_;
  RefCountedPtr<UnstartedCallDestination> destination_;
  CallHandler call_handler_;
};

class Interceptor : public UnstartedCallDestination {
 public:
  using UnstartedCallDestination::UnstartedCallDestination;

  void StartCall(UnstartedCallHandler unstarted_call_handler) final {
    unstarted_call_handler.AddCallStack(filter_stack_);
    InterceptCall(std::move(unstarted_call_handler));
  }

 protected:
  virtual void InterceptCall(UnstartedCallHandler unstarted_call_handler) = 0;

  auto Hijack(UnstartedCallHandler unstarted_call_handler) {
    auto call_handler = unstarted_call_handler.StartCall();
    return Map(call_handler.PullClientInitialMetadata(),
               [call_handler, destination = wrapped_destination_](
                   ValueOrFailure<ClientMetadataHandle> metadata) mutable
                   -> ValueOrFailure<HijackedCall> {
                 if (!metadata.ok()) return Failure{};
                 return HijackedCall(std::move(metadata.value()),
                                     std::move(destination),
                                     std::move(call_handler));
               });
  }

  CallInitiator MakeChildCall(ClientMetadataHandle metadata,
                              RefCountedPtr<Arena> arena);

  CallHandler Consume(UnstartedCallHandler unstarted_call_handler) {
    return unstarted_call_handler.StartCall();
  }

  void PassThrough(UnstartedCallHandler unstarted_call_handler) {
    wrapped_destination_->StartCall(std::move(unstarted_call_handler));
  }

 private:
  friend class InterceptionChainBuilder;

  RefCountedPtr<UnstartedCallDestination> wrapped_destination_;
  RefCountedPtr<CallFilters::Stack> filter_stack_;
};

class InterceptionChainBuilder final {
 public:

  using FinalDestination = std::variant<RefCountedPtr<UnstartedCallDestination>,
                                        RefCountedPtr<CallDestination>>;

  explicit InterceptionChainBuilder(ChannelArgs args,
                                    const Blackboard* old_blackboard = nullptr,
                                    Blackboard* new_blackboard = nullptr)
      : args_(std::move(args)),
        old_blackboard_(old_blackboard),
        new_blackboard_(new_blackboard) {}

  template <typename T>
  absl::enable_if_t<sizeof(typename T::Call) != 0, InterceptionChainBuilder&>
  Add() {
    if (!status_.ok()) return *this;
    auto filter = T::Create(args_, {FilterInstanceId(FilterTypeId<T>()),
                                    old_blackboard_, new_blackboard_});
    if (!filter.ok()) {
      status_ = filter.status();
      return *this;
    }
    auto& sb = stack_builder();
    sb.Add(filter.value().get());
    sb.AddOwnedObject(std::move(filter.value()));
    return *this;
  };

  template <typename T>
  absl::enable_if_t<std::is_base_of<Interceptor, T>::value,
                    InterceptionChainBuilder&>
  Add() {
    AddInterceptor(T::Create(args_, {FilterInstanceId(FilterTypeId<T>()),
                                     old_blackboard_, new_blackboard_}));
    return *this;
  };

  template <typename F>
  InterceptionChainBuilder& AddOnClientInitialMetadata(F f) {
    stack_builder().AddOnClientInitialMetadata(std::move(f));
    return *this;
  }

  template <typename F>
  InterceptionChainBuilder& AddOnServerTrailingMetadata(F f) {
    stack_builder().AddOnServerTrailingMetadata(std::move(f));
    return *this;
  }

  template <typename F>
  InterceptionChainBuilder& AddOnServerTrailingMetadataForEachInterceptor(F f) {
    AddOnServerTrailingMetadata(f);
    on_new_interception_tail_.emplace_back([f](InterceptionChainBuilder* b) {
      b->AddOnServerTrailingMetadata(f);
    });
    return *this;
  }

  void Fail(absl::Status status) {
    CHECK(!status.ok()) << status;
    if (status_.ok()) status_ = std::move(status);
  }

  absl::StatusOr<RefCountedPtr<UnstartedCallDestination>> Build(
      FinalDestination final_destination);

  const ChannelArgs& channel_args() const { return args_; }

 private:
  CallFilters::StackBuilder& stack_builder() {
    if (!stack_builder_.has_value()) {
      stack_builder_.emplace();
      for (auto& f : on_new_interception_tail_) f(this);
    }
    return *stack_builder_;
  }

  RefCountedPtr<CallFilters::Stack> MakeFilterStack() {
    auto stack = stack_builder().Build();
    stack_builder_.reset();
    return stack;
  }

  template <typename T>
  static size_t FilterTypeId() {
    static const size_t id =
        next_filter_id_.fetch_add(1, std::memory_order_relaxed);
    return id;
  }

  size_t FilterInstanceId(size_t filter_type) {
    return filter_type_counts_[filter_type]++;
  }

  void AddInterceptor(absl::StatusOr<RefCountedPtr<Interceptor>> interceptor);

  ChannelArgs args_;
  std::optional<CallFilters::StackBuilder> stack_builder_;
  RefCountedPtr<Interceptor> top_interceptor_;
  std::vector<absl::AnyInvocable<void(InterceptionChainBuilder*)>>
      on_new_interception_tail_;
  absl::Status status_;
  std::map<size_t, size_t> filter_type_counts_;
  static std::atomic<size_t> next_filter_id_;
  const Blackboard* old_blackboard_ = nullptr;
  Blackboard* new_blackboard_ = nullptr;
};

}

#endif
