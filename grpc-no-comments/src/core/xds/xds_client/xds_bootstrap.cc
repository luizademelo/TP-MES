
// Copyright 2019 gRPC authors.

#include "src/core/xds/xds_client/xds_bootstrap.h"

#include <grpc/support/port_platform.h>

#include <optional>

#include "src/core/util/env.h"
#include "src/core/util/string.h"

namespace grpc_core {

bool XdsFederationEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_FEDERATION");
  if (!value.has_value()) return true;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

bool XdsDataErrorHandlingEnabled() {
  auto value = GetEnv("GRPC_EXPERIMENTAL_XDS_DATA_ERROR_HANDLING");
  if (!value.has_value()) return false;
  bool parsed_value;
  bool parse_succeeded = gpr_parse_bool_value(value->c_str(), &parsed_value);
  return parse_succeeded && parsed_value;
}

}
