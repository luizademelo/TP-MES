
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_RESOLVER_RESOLVER_FACTORY_H
#define GRPC_SRC_CORE_RESOLVER_RESOLVER_FACTORY_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <string>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/resolver/resolver.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/uri.h"

namespace grpc_core {

class WorkSerializer;

struct ResolverArgs {

  URI uri;

  ChannelArgs args;

  grpc_pollset_set* pollset_set = nullptr;

  std::shared_ptr<WorkSerializer> work_serializer;

  std::unique_ptr<Resolver::ResultHandler> result_handler;
};

class ResolverFactory {
 public:
  virtual ~ResolverFactory() {}

  virtual absl::string_view scheme() const = 0;

  virtual bool IsValidUri(const URI& uri) const = 0;

  virtual OrphanablePtr<Resolver> CreateResolver(ResolverArgs args) const = 0;

  virtual std::string GetDefaultAuthority(const URI& uri) const {
    return URI::PercentEncodeAuthority(absl::StripPrefix(uri.path(), "/"));
  }
};

}

#endif
