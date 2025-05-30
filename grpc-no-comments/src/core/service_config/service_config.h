
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_H
#define GRPC_SRC_CORE_SERVICE_CONFIG_SERVICE_CONFIG_H

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/strings/string_view.h"
#include "src/core/service_config/service_config_parser.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/useful.h"

#define GRPC_ARG_SERVICE_CONFIG_OBJ "grpc.internal.service_config_obj"

namespace grpc_core {

class ServiceConfig : public RefCounted<ServiceConfig> {
 public:
  static absl::string_view ChannelArgName() {
    return GRPC_ARG_SERVICE_CONFIG_OBJ;
  }
  static int ChannelArgsCompare(const ServiceConfig* a,
                                const ServiceConfig* b) {
    return QsortCompare(a, b);
  }

  virtual absl::string_view json_string() const = 0;

  virtual ServiceConfigParser::ParsedConfig* GetGlobalParsedConfig(
      size_t index) = 0;

  virtual const ServiceConfigParser::ParsedConfigVector*
  GetMethodParsedConfigVector(const grpc_slice& path) const = 0;
};

}

#endif
