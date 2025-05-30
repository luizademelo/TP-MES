
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_RESOLVER_REGISTRY_H
#define GRPC_SRC_CORE_RESOLVER_RESOLVER_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/resolver.h"
#include "src/core/resolver/resolver_factory.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"

namespace grpc_core {

class ResolverRegistry final {
 private:

  struct State {
    std::map<absl::string_view, std::unique_ptr<ResolverFactory>> factories;
    std::string default_prefix;
  };

 public:

  class Builder final {
   public:
    Builder();

    void SetDefaultPrefix(std::string default_prefix);

    void RegisterResolverFactory(std::unique_ptr<ResolverFactory> factory);

    bool HasResolverFactory(absl::string_view scheme) const;

    void Reset();

    ResolverRegistry Build();

   private:
    ResolverRegistry::State state_;
  };

  ResolverRegistry(const ResolverRegistry&) = delete;
  ResolverRegistry& operator=(const ResolverRegistry&) = delete;
  ResolverRegistry(ResolverRegistry&&) noexcept;
  ResolverRegistry& operator=(ResolverRegistry&&) noexcept;

  bool IsValidTarget(absl::string_view target) const;

  OrphanablePtr<Resolver> CreateResolver(
      absl::string_view target, const ChannelArgs& args,
      grpc_pollset_set* pollset_set,
      std::shared_ptr<WorkSerializer> work_serializer,
      std::unique_ptr<Resolver::ResultHandler> result_handler) const;

  std::string GetDefaultAuthority(absl::string_view target) const;

  std::string AddDefaultPrefixIfNeeded(absl::string_view target) const;

  ResolverFactory* LookupResolverFactory(absl::string_view scheme) const;

 private:
  explicit ResolverRegistry(State state) : state_(std::move(state)) {}

  ResolverFactory* FindResolverFactory(absl::string_view target, URI* uri,
                                       std::string* canonical_target) const;

  State state_;
};

}

#endif
