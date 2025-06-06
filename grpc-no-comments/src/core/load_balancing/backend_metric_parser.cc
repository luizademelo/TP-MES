
// Copyright 2019 gRPC authors.

#include "src/core/load_balancing/backend_metric_parser.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include <map>

#include "absl/strings/string_view.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"
#include "upb/message/map.h"
#include "xds/data/orca/v3/orca_load_report.upb.h"

namespace grpc_core {

namespace {

std::map<absl::string_view, double> ParseMap(
    xds_data_orca_v3_OrcaLoadReport* msg,
    bool (*upb_next_func)(const xds_data_orca_v3_OrcaLoadReport* msg,
                          upb_StringView* key, double* val, size_t* iter),
    BackendMetricAllocatorInterface* allocator) {
  std::map<absl::string_view, double> result;
  size_t i = kUpb_Map_Begin;
  upb_StringView key_view;
  double value;
  while (upb_next_func(msg, &key_view, &value, &i)) {
    char* key = allocator->AllocateString(key_view.size);
    memcpy(key, key_view.data, key_view.size);
    result[absl::string_view(key, key_view.size)] = value;
  }
  return result;
}

}

const BackendMetricData* ParseBackendMetricData(
    absl::string_view serialized_load_report,
    BackendMetricAllocatorInterface* allocator) {
  upb::Arena upb_arena;
  xds_data_orca_v3_OrcaLoadReport* msg = xds_data_orca_v3_OrcaLoadReport_parse(
      serialized_load_report.data(), serialized_load_report.size(),
      upb_arena.ptr());
  if (msg == nullptr) return nullptr;
  BackendMetricData* backend_metric_data =
      allocator->AllocateBackendMetricData();
  backend_metric_data->cpu_utilization =
      xds_data_orca_v3_OrcaLoadReport_cpu_utilization(msg);
  backend_metric_data->mem_utilization =
      xds_data_orca_v3_OrcaLoadReport_mem_utilization(msg);
  backend_metric_data->application_utilization =
      xds_data_orca_v3_OrcaLoadReport_application_utilization(msg);
  backend_metric_data->qps =
      xds_data_orca_v3_OrcaLoadReport_rps_fractional(msg);
  backend_metric_data->eps = xds_data_orca_v3_OrcaLoadReport_eps(msg);
  backend_metric_data->request_cost = ParseMap(
      msg, xds_data_orca_v3_OrcaLoadReport_request_cost_next, allocator);
  backend_metric_data->utilization = ParseMap(
      msg, xds_data_orca_v3_OrcaLoadReport_utilization_next, allocator);
  backend_metric_data->named_metrics = ParseMap(
      msg, xds_data_orca_v3_OrcaLoadReport_named_metrics_next, allocator);
  return backend_metric_data;
}

}
