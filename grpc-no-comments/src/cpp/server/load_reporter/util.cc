
// Copyright 2018 gRPC authors.

#include <grpc/load_reporting.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/ext/server_load_reporting.h>
#include <grpcpp/server_context.h>
#include <string.h>

#include <cmath>
#include <string>

#include "absl/log/log.h"

namespace grpc {
namespace load_reporter {
namespace experimental {

void AddLoadReportingCost(grpc::ServerContext* ctx,
                          const std::string& cost_name, double cost_value) {
  if (std::isnormal(cost_value)) {
    std::string buf;
    buf.resize(sizeof(cost_value) + cost_name.size());
    memcpy(&(*buf.begin()), &cost_value, sizeof(cost_value));
    memcpy(&(*buf.begin()) + sizeof(cost_value), cost_name.data(),
           cost_name.size());
    ctx->AddTrailingMetadata(GRPC_LB_COST_MD_KEY, buf);
  } else {
    LOG(ERROR) << "Call metric value is not normal.";
  }
}

}
}
}
