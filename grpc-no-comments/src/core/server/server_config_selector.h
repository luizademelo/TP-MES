
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVER_SERVER_CONFIG_SELECTOR_H
#define GRPC_SRC_CORE_SERVER_SERVER_CONFIG_SELECTOR_H

#include <grpc/support/port_platform.h>

#include <memory>

#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/dual_ref_counted.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/useful.h"

namespace grpc_core {

class ServerConfigSelector : public RefCounted<ServerConfigSelector> {
 public:

  struct CallConfig {
    const ServiceConfigParser::ParsedConfigVector* method_configs = nullptr;
    RefCountedPtr<ServiceConfig> service_config;
  };

  ~ServerConfigSelector() override = default;

  virtual absl::StatusOr<CallConfig> GetCallConfig(
      grpc_metadata_batch* metadata) = 0;
};

class ServerConfigSelectorProvider
    : public DualRefCounted<ServerConfigSelectorProvider> {
 public:
  class ServerConfigSelectorWatcher {
   public:
    virtual ~ServerConfigSelectorWatcher() = default;
    virtual void OnServerConfigSelectorUpdate(
        absl::StatusOr<RefCountedPtr<ServerConfigSelector>> update) = 0;
  };

  ~ServerConfigSelectorProvider() override = default;

  virtual absl::StatusOr<RefCountedPtr<ServerConfigSelector>> Watch(
      std::unique_ptr<ServerConfigSelectorWatcher> watcher) = 0;
  virtual void CancelWatch() = 0;

  static absl::string_view ChannelArgName() {
    return "grpc.internal.server_config_selector_provider";
  }
  static int ChannelArgsCompare(const ServerConfigSelectorProvider* a,
                                const ServerConfigSelectorProvider* b) {
    return QsortCompare(a, b);
  }
};

}

#endif
