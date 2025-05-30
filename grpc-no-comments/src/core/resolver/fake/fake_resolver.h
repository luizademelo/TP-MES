
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_FAKE_FAKE_RESOLVER_H
#define GRPC_SRC_CORE_RESOLVER_FAKE_FAKE_RESOLVER_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include <optional>
#include <utility>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "src/core/resolver/resolver.h"
#include "src/core/util/notification.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR \
  "grpc.fake_resolver.response_generator"

namespace grpc_core {

class FakeResolver;

class FakeResolverResponseGenerator final
    : public RefCounted<FakeResolverResponseGenerator> {
 public:
  static const grpc_arg_pointer_vtable kChannelArgPointerVtable;

  FakeResolverResponseGenerator();
  ~FakeResolverResponseGenerator() override;

  void SetResponseAndNotify(Resolver::Result result,
                            Notification* notify_when_set);

  void SetResponseAsync(Resolver::Result result) {
    SetResponseAndNotify(std::move(result), nullptr);
  }

  void SetResponseSynchronously(Resolver::Result result) {
    Notification n;
    SetResponseAndNotify(std::move(result), &n);
    n.WaitForNotification();
  }

  bool WaitForReresolutionRequest(absl::Duration timeout);

  bool WaitForResolverSet(absl::Duration timeout);

  static absl::string_view ChannelArgName() {
    return GRPC_ARG_FAKE_RESOLVER_RESPONSE_GENERATOR;
  }

  static int ChannelArgsCompare(const FakeResolverResponseGenerator* a,
                                const FakeResolverResponseGenerator* b) {
    return QsortCompare(a, b);
  }

 private:
  friend class FakeResolver;

  void SetFakeResolver(RefCountedPtr<FakeResolver> resolver);

  void ReresolutionRequested();

  static void SendResultToResolver(RefCountedPtr<FakeResolver> resolver,
                                   Resolver::Result result,
                                   Notification* notify_when_set);

  Mutex mu_;
  CondVar* resolver_set_cv_ ABSL_GUARDED_BY(mu_) = nullptr;
  RefCountedPtr<FakeResolver> resolver_ ABSL_GUARDED_BY(mu_);

  std::optional<Resolver::Result> result_ ABSL_GUARDED_BY(mu_);

  Mutex reresolution_mu_;
  CondVar* reresolution_cv_ ABSL_GUARDED_BY(reresolution_mu_) = nullptr;
  bool reresolution_requested_ ABSL_GUARDED_BY(reresolution_mu_) = false;
};

}

#endif
