// Copyright 2024 gRPC authors.

#include "src/core/call/interception_chain.h"

#include <grpc/support/port_platform.h>

#include <cstddef>

#include "src/core/call/call_destination.h"
#include "src/core/call/call_filters.h"
#include "src/core/call/call_spine.h"
#include "src/core/call/metadata.h"
#include "src/core/lib/debug/trace.h"
#include "src/core/util/match.h"

namespace grpc_core {

std::atomic<size_t> InterceptionChainBuilder::next_filter_id_{0};

CallInitiator HijackedCall::MakeCall() {
  auto metadata = Arena::MakePooledForOverwrite<ClientMetadata>();
  *metadata = metadata_->Copy();
  return MakeCallWithMetadata(std::move(metadata));
}

CallInitiator HijackedCall::MakeCallWithMetadata(
    ClientMetadataHandle metadata) {
  auto call = MakeCallPair(std::move(metadata), call_handler_.arena()->Ref());
  destination_->StartCall(std::move(call.handler));
  return std::move(call.initiator);
}

CallInitiator Interceptor::MakeChildCall(ClientMetadataHandle metadata,
                                         RefCountedPtr<Arena> arena) {
  auto call = MakeCallPair(std::move(metadata), arena);
  wrapped_destination_->StartCall(std::move(call.handler));
  return std::move(call.initiator);
}

namespace {
class CallStarter final : public UnstartedCallDestination {
 public:
  CallStarter(RefCountedPtr<CallFilters::Stack> stack,
              RefCountedPtr<CallDestination> destination)
      : stack_(std::move(stack)), destination_(std::move(destination)) {}

  void Orphaned() override {
    stack_.reset();
    destination_.reset();
  }

  void StartCall(UnstartedCallHandler unstarted_call_handler) override {
    unstarted_call_handler.AddCallStack(stack_);
    destination_->HandleCall(unstarted_call_handler.StartCall());
  }

 private:
  RefCountedPtr<CallFilters::Stack> stack_;
  RefCountedPtr<CallDestination> destination_;
};

class TerminalInterceptor final : public UnstartedCallDestination {
 public:
  explicit TerminalInterceptor(
      RefCountedPtr<CallFilters::Stack> stack,
      RefCountedPtr<UnstartedCallDestination> destination)
      : stack_(std::move(stack)), destination_(std::move(destination)) {}

  void Orphaned() override {
    stack_.reset();
    destination_.reset();
  }

  void StartCall(UnstartedCallHandler unstarted_call_handler) override {
    unstarted_call_handler.AddCallStack(stack_);
    destination_->StartCall(unstarted_call_handler);
  }

 private:
  RefCountedPtr<CallFilters::Stack> stack_;
  RefCountedPtr<UnstartedCallDestination> destination_;
};
}

void InterceptionChainBuilder::AddInterceptor(
    absl::StatusOr<RefCountedPtr<Interceptor>> interceptor) {
  if (!status_.ok()) return;
  if (!interceptor.ok()) {
    status_ = interceptor.status();
    return;
  }
  (*interceptor)->filter_stack_ = MakeFilterStack();
  if (top_interceptor_ == nullptr) {
    top_interceptor_ = std::move(*interceptor);
  } else {
    Interceptor* previous = top_interceptor_.get();
    while (previous->wrapped_destination_ != nullptr) {
      previous = DownCast<Interceptor*>(previous->wrapped_destination_.get());
    }
    previous->wrapped_destination_ = std::move(*interceptor);
  }
}

absl::StatusOr<RefCountedPtr<UnstartedCallDestination>>
InterceptionChainBuilder::Build(FinalDestination final_destination) {
  if (!status_.ok()) return status_;

  RefCountedPtr<UnstartedCallDestination> terminator = Match(
      final_destination,
      [this](RefCountedPtr<UnstartedCallDestination> final_destination)
          -> RefCountedPtr<UnstartedCallDestination> {
        if (stack_builder_.has_value()) {
          return MakeRefCounted<TerminalInterceptor>(MakeFilterStack(),
                                                     final_destination);
        }
        return final_destination;
      },
      [this](RefCountedPtr<CallDestination> final_destination)
          -> RefCountedPtr<UnstartedCallDestination> {
        return MakeRefCounted<CallStarter>(MakeFilterStack(),
                                           std::move(final_destination));
      });

  if (top_interceptor_ == nullptr) {
    return std::move(terminator);
  }
  Interceptor* previous = top_interceptor_.get();
  while (previous->wrapped_destination_ != nullptr) {
    previous = DownCast<Interceptor*>(previous->wrapped_destination_.get());
  }
  previous->wrapped_destination_ = std::move(terminator);
  return std::move(top_interceptor_);
}

}
