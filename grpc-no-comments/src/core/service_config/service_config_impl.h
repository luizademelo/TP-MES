
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_IMPL_H
#define GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_IMPL_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/service_config/service_config.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/json/json.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/validation_errors.h"

namespace grpc_core {

class ServiceConfigImpl final : public ServiceConfig {
 public:

  static absl::StatusOr<RefCountedPtr<ServiceConfig>> Create(
      const ChannelArgs& args, absl::string_view json_string);

  static RefCountedPtr<ServiceConfig> Create(const ChannelArgs& args,
                                             const Json& json,
                                             absl::string_view json_string,
                                             ValidationErrors* errors);
  static RefCountedPtr<ServiceConfig> Create(const ChannelArgs& args,
                                             const Json& json,
                                             ValidationErrors* errors);

  ~ServiceConfigImpl() override;

  absl::string_view json_string() const override { return json_string_; }

  ServiceConfigParser::ParsedConfig* GetGlobalParsedConfig(
      size_t index) override {
    DCHECK(index < parsed_global_configs_.size());
    return parsed_global_configs_[index].get();
  }

  const ServiceConfigParser::ParsedConfigVector* GetMethodParsedConfigVector(
      const grpc_slice& path) const override;

 private:
  std::string json_string_;
  Json json_;

  ServiceConfigParser::ParsedConfigVector parsed_global_configs_;

  std::unordered_map<grpc_slice, const ServiceConfigParser::ParsedConfigVector*,
                     SliceHash>
      parsed_method_configs_map_;

  const ServiceConfigParser::ParsedConfigVector* default_method_config_vector_ =
      nullptr;

  std::vector<ServiceConfigParser::ParsedConfigVector>
      parsed_method_config_vectors_storage_;
};

}

#endif
