Here's the commented version of the code:

```c++
// Copyright 2022 gRPC authors.

#include "src/cpp/server/orca/orca_service.h"

#include <grpc/event_engine/event_engine.h>
#include <grpcpp/ext/orca_service.h>
#include <grpcpp/ext/server_metric_recorder.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/slice.h>
#include <grpcpp/support/status.h>
#include <stddef.h>

#include <map>
#include <memory>
#include <optional>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/string_view.h"
#include "absl/time/time.h"
#include "google/protobuf/duration.upb.h"
#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/core/lib/iomgr/exec_ctx.h"
#include "src/core/load_balancing/backend_metric_data.h"
#include "src/core/util/debug_location.h"
#include "src/core/util/time.h"
#include "src/cpp/server/backend_metric_recorder.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"
#include "xds/data/orca/v3/orca_load_report.upb.h"
#include "xds/service/orca/v3/orca.upb.h"

namespace grpc {
namespace experimental {

// Reactor class implementation for handling ORCA (Open Request Cost Aggregation) service streams
OrcaService::Reactor::Reactor(OrcaService* service, absl::string_view peer,
                              const ByteBuffer* request_buffer,
                              std::shared_ptr<ReactorHook> hook)
    : service_(service),
      hook_(std::move(hook)),
      engine_(grpc_event_engine::experimental::GetDefaultEventEngine()) {

  // Extract the request data from the ByteBuffer
  Slice slice;
  grpc::Status status = request_buffer->DumpToSingleSlice(&slice);
  if (!status.ok()) {
    LOG_EVERY_N_SEC(WARNING, 1)
        << "OrcaService failed to extract request from peer: " << peer
        << " error:" << status.error_message();
    FinishRpc(Status(StatusCode::INTERNAL, status.error_message()));
    return;
  }

  // Parse the ORCA load report request using upb (micro protobuf)
  upb::Arena arena;
  xds_service_orca_v3_OrcaLoadReportRequest* request =
      xds_service_orca_v3_OrcaLoadReportRequest_parse(
          reinterpret_cast<const char*>(slice.begin()), slice.size(),
          arena.ptr());
  if (request == nullptr) {
    LOG_EVERY_N_SEC(WARNING, 1)
        << "OrcaService failed to parse request proto from peer: " << peer;
    FinishRpc(Status(StatusCode::INTERNAL, "could not parse request proto"));
    return;
  }

  // Process the report interval from the request
  const auto* duration_proto =
      xds_service_orca_v3_OrcaLoadReportRequest_report_interval(request);
  grpc_core::Duration report_interval;
  if (duration_proto != nullptr) {
    report_interval = grpc_core::Duration::FromSecondsAndNanoseconds(
        google_protobuf_Duration_seconds(duration_proto),
        google_protobuf_Duration_nanos(duration_proto));
  }
  
  // Ensure the report interval is not smaller than the minimum configured duration
  auto min_interval = grpc_core::Duration::Milliseconds(
      service_->min_report_duration_ / absl::Milliseconds(1));
  report_interval_ = std::max(report_interval, min_interval);

  // Send the initial response
  SendResponse();
}

// Callback for when a write operation completes
void OrcaService::Reactor::OnWriteDone(bool ok) {
  if (!ok) {
    FinishRpc(Status(StatusCode::UNKNOWN, "write failed"));
    return;
  }
  // Clear the response buffer and schedule the next report if needed
  response_.Clear();
  if (!MaybeScheduleTimer()) {
    FinishRpc(Status(StatusCode::UNKNOWN, "call cancelled by client"));
  }
}

// Callback for when the call is cancelled by the client
void OrcaService::Reactor::OnCancel() {
  if (MaybeCancelTimer()) {
    FinishRpc(Status(StatusCode::UNKNOWN, "call cancelled by client"));
  }
}

// Callback for when the RPC is done (cleanup)
void OrcaService::Reactor::OnDone() {
  Unref(DEBUG_LOCATION, "OnDone");
}

// Helper method to finish the RPC with the given status
void OrcaService::Reactor::FinishRpc(grpc::Status status) {
  if (hook_ != nullptr) {
    hook_->OnFinish(status);
  }
  Finish(status);
}

// Sends the current metrics response to the client
void OrcaService::Reactor::SendResponse() {
  Slice response_slice = service_->GetOrCreateSerializedResponse();
  ByteBuffer response_buffer(&response_slice, 1);
  response_.Swap(&response_buffer);
  if (hook_ != nullptr) {
    hook_->OnStartWrite(&response_);
  }
  StartWrite(&response_);
}

// Schedules the next metrics report if the call hasn't been cancelled
bool OrcaService::Reactor::MaybeScheduleTimer() {
  grpc::internal::MutexLock lock(&timer_mu_);
  if (cancelled_) return false;
  timer_handle_ = engine_->RunAfter(
      report_interval_,
      [self = Ref(DEBUG_LOCATION, "Orca Service")] { self->OnTimer(); });
  return true;
}

// Attempts to cancel any pending timer
bool OrcaService::Reactor::MaybeCancelTimer() {
  grpc::internal::MutexLock lock(&timer_mu_);
  cancelled_ = true;
  if (timer_handle_.has_value() && engine_->Cancel(*timer_handle_)) {
    timer_handle_.reset();
    return true;
  }
  return false;
}

// Callback for when the report timer fires
void OrcaService::Reactor::OnTimer() {
  grpc_core::ExecCtx exec_ctx;
  grpc::internal::MutexLock lock(&timer_mu_);
  timer_handle_.reset();
  SendResponse();
}

// OrcaService constructor
OrcaService::OrcaService(ServerMetricRecorder* const server_metric_recorder,
                         Options options)
    : server_metric_recorder_(server_metric_recorder),
      min_report_duration_(options.min_report_duration) {
  CHECK_NE(server_metric_recorder_, nullptr);
  // Register the ORCA service method
  AddMethod(new internal::RpcServiceMethod(
      "/xds.service.orca.v3.OpenRcaService/StreamCoreMetrics",
      internal::RpcMethod::SERVER_STREAMING, nullptr));
  // Set up the callback handler for the streaming method
  MarkMethodCallback(
      0, new internal::CallbackServerStreamingHandler<ByteBuffer, ByteBuffer>(
             [this](CallbackServerContext* ctx, const ByteBuffer* request) {
               return new Reactor(this, ctx->peer(), request, nullptr);
             }));
}

// Gets or creates a serialized metrics response
Slice OrcaService::GetOrCreateSerializedResponse() {
  grpc::internal::MutexLock lock(&mu_);
  // Get the latest metrics if they've changed
  std::shared_ptr<const ServerMetricRecorder::BackendMetricDataState> result =
      server_metric_recorder_->GetMetricsIfChanged();
  if (!response_slice_seq_.has_value() ||
      *response_slice_seq_ != result->sequence_number) {
    const auto& data = result->data;
    upb::Arena arena;
    // Create a new ORCA load report message
    xds_data_orca_v3_OrcaLoadReport* response =
        xds_data_orca_v3_OrcaLoadReport_new(arena.ptr());
    
    // Populate the response with available metrics
    if (data.cpu_utilization != -1) {
      xds_data_orca_v3_OrcaLoadReport_set_cpu_utilization(response,
                                                          data.cpu_utilization);
    }
    if (data.mem_utilization != -1) {
      xds_data_orca_v3_OrcaLoadReport_set_mem_utilization(response,
                                                          data.mem_utilization);
    }
    if (data.application_utilization != -1) {
      xds_data_orca_v3_OrcaLoadReport_set_application_utilization(
          response, data.application_utilization);
    }
    if (data.qps != -1) {
      xds_data_orca_v3_OrcaLoadReport_set_rps_fractional(response, data.qps);
    }
    if (data.eps != -1) {
      xds_data_orca_v3_OrcaLoadReport_set_eps(response, data.eps);
    }
    // Add utilization metrics for named resources
    for (const auto& u : data.utilization) {
      xds_data_orca_v3_OrcaLoadReport_utilization_set(
          response,
          upb_StringView_FromDataAndSize(u.first.data(), u.first.size()),
          u.second, arena.ptr());
    }
    // Serialize the response
    size_t buf_length;
    char* buf = xds_data_orca_v3_OrcaLoadReport_serialize(response, arena.ptr(),
                                                          &buf_length);
    response_slice_.emplace(buf, buf_length);
    response_slice_seq_ = result->sequence_number;
  }
  return Slice(*response_slice_);
}

}  // namespace experimental
}  // namespace grpc
```