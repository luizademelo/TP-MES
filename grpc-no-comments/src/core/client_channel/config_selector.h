
// Copyright 2020 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CONFIG_SELECTOR_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CONFIG_SELECTOR_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <string.h>

#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/interception_chain.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/client_channel/client_channel_internal.h"
#include "src/core/lib/channel/channel_fwd.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice.h"
#include "src/core/service_config/service_config.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/unique_type_name.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_CONFIG_SELECTOR "grpc.internal.config_selector"

namespace grpc_core {

class ConfigSelector : public RefCounted<ConfigSelector> {
 public:
  ~ConfigSelector() override = default;

  virtual UniqueTypeName name() const = 0;

  static bool Equals(const ConfigSelector* cs1, const ConfigSelector* cs2) {
    if (cs1 == nullptr) return cs2 == nullptr;
    if (cs2 == nullptr) return false;
    if (cs1->name() != cs2->name()) return false;
    return cs1->Equals(cs2);
  }

  virtual void AddFilters(InterceptionChainBuilder& ) {}

  virtual std::vector<const grpc_channel_filter*> GetFilters() { return {}; }

  struct GetCallConfigArgs {
    grpc_metadata_batch* initial_metadata;
    Arena* arena;
    ClientChannelServiceConfigCallData* service_config_call_data;
  };
  virtual absl::Status GetCallConfig(GetCallConfigArgs args) = 0;

  static absl::string_view ChannelArgName() { return GRPC_ARG_CONFIG_SELECTOR; }
  static int ChannelArgsCompare(const ConfigSelector* a,
                                const ConfigSelector* b) {
    return QsortCompare(a, b);
  }

 private:

  virtual bool Equals(const ConfigSelector* other) const = 0;
};

class DefaultConfigSelector final : public ConfigSelector {
 public:
  explicit DefaultConfigSelector(RefCountedPtr<ServiceConfig> service_config)
      : service_config_(std::move(service_config)) {

    DCHECK(service_config_ != nullptr);
  }

  UniqueTypeName name() const override {
    static UniqueTypeName::Factory kFactory("default");
    return kFactory.Create();
  }

  absl::Status GetCallConfig(GetCallConfigArgs args) override {
    Slice* path = args.initial_metadata->get_pointer(HttpPathMetadata());
    CHECK_NE(path, nullptr);
    auto* parsed_method_configs =
        service_config_->GetMethodParsedConfigVector(path->c_slice());
    args.service_config_call_data->SetServiceConfig(service_config_,
                                                    parsed_method_configs);
    return absl::OkStatus();
  }

  bool Equals(const ConfigSelector* ) const override { return true; }

 private:
  RefCountedPtr<ServiceConfig> service_config_;
};

}

#endif
