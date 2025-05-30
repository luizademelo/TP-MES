
// Copyright 2016 gRPC authors.

#include "src/core/resolver/fake/fake_resolver.h"

#include <grpc/support/port_platform.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "absl/log/check.h"
#include "absl/strings/string_view.h"
#include "src/core/config/core_configuration.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"
#include "src/core/util/useful.h"
#include "src/core/util/work_serializer.h"

namespace grpc_core {

class FakeResolver final : public Resolver {
 public:
  explicit FakeResolver(ResolverArgs args);

  void StartLocked() override;

  void RequestReresolutionLocked() override;

 private:
  friend class FakeResolverResponseGenerator;

  void ShutdownLocked() override;

  void MaybeSendResultLocked();

  std::shared_ptr<WorkSerializer> work_serializer_;
  std::unique_ptr<ResultHandler> result_handler_;
  ChannelArgs channel_args_;
  RefCountedPtr<FakeResolverResponseGenerator> response_generator_;

  std::optional<Result> next_result_;

  bool started_ = false;

  bool shutdown_ = false;
};

FakeResolver::FakeResolver(ResolverArgs args)
    : work_serializer_(std::move(args.work_serializer)),
      result_handler_(std::move(args.result_handler)),
      channel_args_(

          args.args.Remove(GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR)),
      response_generator_(
          args.args.GetObjectRef<FakeResolverResponseGenerator>()) {
  if (response_generator_ != nullptr) {
    response_generator_->SetFakeResolver(RefAsSubclass<FakeResolver>());
  }
}

void FakeResolver::StartLocked() {
  started_ = true;
  MaybeSendResultLocked();
}

void FakeResolver::RequestReresolutionLocked() {

  CHECK(response_generator_ != nullptr);
  response_generator_->ReresolutionRequested();
}

void FakeResolver::ShutdownLocked() {
  shutdown_ = true;
  if (response_generator_ != nullptr) {
    response_generator_->SetFakeResolver(nullptr);
    response_generator_.reset();
  }
}

void FakeResolver::MaybeSendResultLocked() {
  if (!started_ || shutdown_) return;
  if (next_result_.has_value()) {

    next_result_->args = next_result_->args.UnionWith(channel_args_);
    result_handler_->ReportResult(std::move(*next_result_));
    next_result_.reset();
  }
}

FakeResolverResponseGenerator::FakeResolverResponseGenerator() {}

FakeResolverResponseGenerator::~FakeResolverResponseGenerator() {}

void FakeResolverResponseGenerator::SetResponseAndNotify(
    Resolver::Result result, Notification* notify_when_set) {
  RefCountedPtr<FakeResolver> resolver;
  {
    MutexLock lock(&mu_);
    if (resolver_ == nullptr) {
      result_ = std::move(result);
      if (notify_when_set != nullptr) notify_when_set->Notify();
      return;
    }
    resolver = resolver_;
  }
  SendResultToResolver(std::move(resolver), std::move(result), notify_when_set);
}

void FakeResolverResponseGenerator::SetFakeResolver(
    RefCountedPtr<FakeResolver> resolver) {
  Resolver::Result result;
  {
    MutexLock lock(&mu_);
    resolver_ = resolver;
    if (resolver_set_cv_ != nullptr) resolver_set_cv_->SignalAll();
    if (resolver == nullptr) return;
    if (!result_.has_value()) return;
    result = std::move(*result_);
    result_.reset();
  }
  SendResultToResolver(std::move(resolver), std::move(result), nullptr);
}

void FakeResolverResponseGenerator::SendResultToResolver(
    RefCountedPtr<FakeResolver> resolver, Resolver::Result result,
    Notification* notify_when_set) {
  auto* resolver_ptr = resolver.get();
  resolver_ptr->work_serializer_->Run([resolver = std::move(resolver),
                                       result = std::move(result),
                                       notify_when_set]() mutable {
    if (!resolver->shutdown_) {
      resolver->next_result_ = std::move(result);
      resolver->MaybeSendResultLocked();
    }
    if (notify_when_set != nullptr) notify_when_set->Notify();
  });
}

bool FakeResolverResponseGenerator::WaitForResolverSet(absl::Duration timeout) {
  MutexLock lock(&mu_);
  if (resolver_ == nullptr) {
    CondVar condition;
    resolver_set_cv_ = &condition;
    condition.WaitWithTimeout(&mu_, timeout);
    resolver_set_cv_ = nullptr;
  }
  return resolver_ != nullptr;
}

bool FakeResolverResponseGenerator::WaitForReresolutionRequest(
    absl::Duration timeout) {
  MutexLock lock(&reresolution_mu_);
  if (!reresolution_requested_) {
    CondVar condition;
    reresolution_cv_ = &condition;
    condition.WaitWithTimeout(&reresolution_mu_, timeout);
    reresolution_cv_ = nullptr;
  }
  return std::exchange(reresolution_requested_, false);
}

void FakeResolverResponseGenerator::ReresolutionRequested() {
  MutexLock lock(&reresolution_mu_);
  reresolution_requested_ = true;
  if (reresolution_cv_ != nullptr) reresolution_cv_->SignalAll();
}

namespace {

void* ResponseGeneratorChannelArgCopy(void* p) {
  auto* generator = static_cast<FakeResolverResponseGenerator*>(p);
  generator->Ref().release();
  return p;
}

void ResponseGeneratorChannelArgDestroy(void* p) {
  auto* generator = static_cast<FakeResolverResponseGenerator*>(p);
  generator->Unref();
}

int ResponseGeneratorChannelArgCmp(void* a, void* b) {
  return QsortCompare(a, b);
}

}

const grpc_arg_pointer_vtable
    FakeResolverResponseGenerator::kChannelArgPointerVtable = {
        ResponseGeneratorChannelArgCopy, ResponseGeneratorChannelArgDestroy,
        ResponseGeneratorChannelArgCmp};

namespace {

class FakeResolverFactory final : public ResolverFactory {
 public:
  absl::string_view scheme() const override { return "fake"; }

  bool IsValidUri(const URI& ) const override { return true; }

  OrphanablePtr<Resolver> CreateResolver(ResolverArgs args) const override {
    return MakeOrphanable<FakeResolver>(std::move(args));
  }
};

}

void RegisterFakeResolver(CoreConfiguration::Builder* builder) {
  builder->resolver_registry()->RegisterResolverFactory(
      std::make_unique<FakeResolverFactory>());
}

}

void grpc_resolver_fake_shutdown() {}
