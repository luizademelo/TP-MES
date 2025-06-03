Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/cpp/server/health/default_health_check_service.h"

#include <grpc/slice.h>
#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/support/slice.h>
#include <stdint.h>

#include <memory>
#include <utility>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/proto/grpc/health/v1/health.upb.h"
#include "upb/base/string_view.h"
#include "upb/mem/arena.hpp"

// Maximum allowed length for service names in health check requests
#define MAX_SERVICE_NAME_LENGTH 200

namespace grpc {

// Constructor initializes the default service (empty name) with SERVING status
DefaultHealthCheckService::DefaultHealthCheckService() {
  services_map_[""].SetServingStatus(SERVING);
}

// Sets the serving status for a specific service
// If the service is shutdown, forces status to NOT_SERVING
void DefaultHealthCheckService::SetServingStatus(
    const std::string& service_name, bool serving) {
  grpc::internal::MutexLock lock(&mu_);
  if (shutdown_) {
    serving = false;
  }
  services_map_[service_name].SetServingStatus(serving ? SERVING : NOT_SERVING);
}

// Sets the serving status for all registered services
void DefaultHealthCheckService::SetServingStatus(bool serving) {
  const ServingStatus status = serving ? SERVING : NOT_SERVING;
  grpc::internal::MutexLock lock(&mu_);
  if (shutdown_) return;
  for (auto& p : services_map_) {
    ServiceData& service_data = p.second;
    service_data.SetServingStatus(status);
  }
}

// Shuts down the health check service, marking all services as NOT_SERVING
void DefaultHealthCheckService::Shutdown() {
  grpc::internal::MutexLock lock(&mu_);
  if (shutdown_) return;
  shutdown_ = true;
  for (auto& p : services_map_) {
    ServiceData& service_data = p.second;
    service_data.SetServingStatus(NOT_SERVING);
  }
}

// Returns the serving status for a given service
// Returns NOT_FOUND if service doesn't exist
DefaultHealthCheckService::ServingStatus
DefaultHealthCheckService::GetServingStatus(
    const std::string& service_name) const {
  grpc::internal::MutexLock lock(&mu_);
  auto it = services_map_.find(service_name);
  if (it == services_map_.end()) return NOT_FOUND;
  const ServiceData& service_data = it->second;
  return service_data.GetServingStatus();
}

// Registers a watcher for a service's health status
// Immediately sends current health status to the watcher
void DefaultHealthCheckService::RegisterWatch(
    const std::string& service_name,
    grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher) {
  grpc::internal::MutexLock lock(&mu_);
  ServiceData& service_data = services_map_[service_name];
  watcher->SendHealth(service_data.GetServingStatus());
  service_data.AddWatch(std::move(watcher));
}

// Unregisters a watcher for a service's health status
// Removes the service entry if no watchers remain
void DefaultHealthCheckService::UnregisterWatch(
    const std::string& service_name,
    HealthCheckServiceImpl::WatchReactor* watcher) {
  grpc::internal::MutexLock lock(&mu_);
  auto it = services_map_.find(service_name);
  if (it == services_map_.end()) return;
  ServiceData& service_data = it->second;
  service_data.RemoveWatch(watcher);
  if (service_data.Unused()) services_map_.erase(it);
}

// Creates and returns the health check service implementation
DefaultHealthCheckService::HealthCheckServiceImpl*
DefaultHealthCheckService::GetHealthCheckService() {
  CHECK(impl_ == nullptr);
  impl_ = std::make_unique<HealthCheckServiceImpl>(this);
  return impl_.get();
}

// Sets the serving status for a service and notifies all watchers
void DefaultHealthCheckService::ServiceData::SetServingStatus(
    ServingStatus status) {
  status_ = status;
  for (const auto& p : watchers_) {
    p.first->SendHealth(status);
  }
}

// Adds a watcher for this service's health status
void DefaultHealthCheckService::ServiceData::AddWatch(
    grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher) {
  watchers_[watcher.get()] = std::move(watcher);
}

// Removes a watcher for this service's health status
void DefaultHealthCheckService::ServiceData::RemoveWatch(
    HealthCheckServiceImpl::WatchReactor* watcher) {
  watchers_.erase(watcher);
}

namespace {
// gRPC method names for health check service
const char kHealthCheckMethodName[] = "/grpc.health.v1.Health/Check";
const char kHealthWatchMethodName[] = "/grpc.health.v1.Health/Watch";
}

// HealthCheckServiceImpl constructor
// Registers the health check and watch methods with their handlers
DefaultHealthCheckService::HealthCheckServiceImpl::HealthCheckServiceImpl(
    DefaultHealthCheckService* database)
    : database_(database) {
  // Add health check method (unary RPC)
  AddMethod(new internal::RpcServiceMethod(
      kHealthCheckMethodName, internal::RpcMethod::NORMAL_RPC, nullptr));
  MarkMethodCallback(
      0, new internal::CallbackUnaryHandler<ByteBuffer, ByteBuffer>(
             [database](CallbackServerContext* context,
                        const ByteBuffer* request, ByteBuffer* response) {
               return HandleCheckRequest(database, context, request, response);
             }));

  // Add health watch method (server streaming RPC)
  AddMethod(new internal::RpcServiceMethod(
      kHealthWatchMethodName, internal::RpcMethod::SERVER_STREAMING, nullptr));
  MarkMethodCallback(
      1, new internal::CallbackServerStreamingHandler<ByteBuffer, ByteBuffer>(
             [this](CallbackServerContext* , const ByteBuffer* request) {
               return new WatchReactor(this, request);
             }));
}

// HealthCheckServiceImpl destructor
// Waits for all active watches to complete during shutdown
DefaultHealthCheckService::HealthCheckServiceImpl::~HealthCheckServiceImpl() {
  grpc::internal::MutexLock lock(&mu_);
  shutdown_ = true;
  while (num_watches_ > 0) {
    shutdown_condition_.Wait(&mu_);
  }
}

// Handles health check requests (unary RPC)
ServerUnaryReactor*
DefaultHealthCheckService::HealthCheckServiceImpl::HandleCheckRequest(
    DefaultHealthCheckService* database, CallbackServerContext* context,
    const ByteBuffer* request, ByteBuffer* response) {
  auto* reactor = context->DefaultReactor();
  std::string service_name;
  if (!DecodeRequest(*request, &service_name)) {
    reactor->Finish(
        Status(StatusCode::INVALID_ARGUMENT, "could not parse request"));
    return reactor;
  }
  ServingStatus serving_status = database->GetServingStatus(service_name);
  if (serving_status == NOT_FOUND) {
    reactor->Finish(Status(StatusCode::NOT_FOUND, "service name unknown"));
    return reactor;
  }
  if (!EncodeResponse(serving_status, response)) {
    reactor->Finish(Status(StatusCode::INTERNAL, "could not encode response"));
    return reactor;
  }
  reactor->Finish(Status::OK);
  return reactor;
}

// Decodes a health check request from ByteBuffer to service name
bool DefaultHealthCheckService::HealthCheckServiceImpl::DecodeRequest(
    const ByteBuffer& request, std::string* service_name) {
  Slice slice;
  if (!request.DumpToSingleSlice(&slice).ok()) return false;
  uint8_t* request_bytes = nullptr;
  size_t request_size = 0;
  request_bytes = const_cast<uint8_t*>(slice.begin());
  request_size = slice.size();
  upb::Arena arena;
  grpc_health_v1_HealthCheckRequest* request_struct =
      grpc_health_v1_HealthCheckRequest_parse(
          reinterpret_cast<char*>(request_bytes), request_size, arena.ptr());
  if (request_struct == nullptr) {
    return false;
  }
  upb_StringView service =
      grpc_health_v1_HealthCheckRequest_service(request_struct);
  if (service.size > MAX_SERVICE_NAME_LENGTH) {
    return false;
  }
  service_name->assign(service.data, service.size);
  return true;
}

// Encodes a health check response from status to ByteBuffer
bool DefaultHealthCheckService::HealthCheckServiceImpl::EncodeResponse(
    ServingStatus status, ByteBuffer* response) {
  upb::Arena arena;
  grpc_health_v1_HealthCheckResponse* response_struct =
      grpc_health_v1_HealthCheckResponse_new(arena.ptr());
  grpc_health_v1_HealthCheckResponse_set_status(
      response_struct,
      status == NOT_FOUND ? grpc_health_v1_HealthCheckResponse_SERVICE_UNKNOWN
      : status == SERVING ? grpc_health_v1_HealthCheckResponse_SERVING
                          : grpc_health_v1_HealthCheckResponse_NOT_SERVING);
  size_t buf_length;
  char* buf = grpc_health_v1_HealthCheckResponse_serialize(
      response_struct, arena.ptr(), &buf_length);
  if (buf == nullptr) {
    return false;
  }
  grpc_slice response_slice = grpc_slice_from_copied_buffer(buf, buf_length);
  Slice encoded_response(response_slice, Slice::STEAL_REF);
  ByteBuffer response_buffer(&encoded_response, 1);
  response->Swap(&response_buffer);
  return true;
}

// WatchReactor constructor - handles server streaming health watch requests
DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::WatchReactor(
    HealthCheckServiceImpl* service, const ByteBuffer* request)
    : service_(service) {
  {
    grpc::internal::MutexLock lock(&service_->mu_);
    ++service_->num_watches_;
  }
  bool success = DecodeRequest(*request, &service_name_);
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_ << "\": watch call started";
  if (!success) {
    MaybeFinishLocked(Status(StatusCode::INTERNAL, "could not parse request"));
    return;
  }

  service_->database_->RegisterWatch(service_name_, Ref());
}

// Sends health status update to the client
// Queues updates if a write is already in progress
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::
    SendHealth(ServingStatus status) {
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_ << "\": SendHealth() for ServingStatus " << status;
  grpc::internal::MutexLock lock(&mu_);

  if (write_pending_) {
    VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
            << service_name_ << "\": queuing write";
    pending_status_ = status;
    return;
  }

  SendHealthLocked(status);
}

// Internal method to send health status to client
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::
    SendHealthLocked(ServingStatus status) {
  if (finish_called_) return;

  {
    grpc::internal::MutexLock lock(&service_->mu_);
    if (service_->shutdown_) {
      MaybeFinishLocked(
          Status(StatusCode::CANCELLED, "not writing due to shutdown"));
      return;
    }
  }

  bool success = EncodeResponse(status, &response_);
  if (!success) {
    MaybeFinishLocked(
        Status(StatusCode::INTERNAL, "could not encode response"));
    return;
  }
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_ << "\": starting write for ServingStatus " << status;
  write_pending_ = true;
  StartWrite(&response_);
}

// Callback when a write operation completes
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::
    OnWriteDone(bool ok) {
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_ << "\": OnWriteDone(): ok=" << ok;
  response_.Clear();
  grpc::internal::MutexLock lock(&mu_);
  if (!ok) {
    MaybeFinishLocked(Status(StatusCode::CANCELLED, "OnWriteDone() ok=false"));
    return;
  }
  write_pending_ = false;

  if (pending_status_ != NOT_FOUND) {
    auto status = pending_status_;
    pending_status_ = NOT_FOUND;
    SendHealthLocked(status);
  }
}

// Callback when the watch is cancelled by client
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::
    OnCancel() {
  grpc::internal::MutexLock lock(&mu_);
  MaybeFinishLocked(Status(StatusCode::UNKNOWN, "OnCancel()"));
}

// Callback when the watch is done (cleanup)
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::OnDone() {
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_ << "\": OnDone()";
  service_->database_->UnregisterWatch(service_name_, this);
  {
    grpc::internal::MutexLock lock(&service_->mu_);
    if (--service_->num_watches_ == 0 && service_->shutdown_) {
      service_->shutdown_condition_.Signal();
    }
  }

  Unref();
}

// Safely finishes the watch if not already finished
void DefaultHealthCheckService::HealthCheckServiceImpl::WatchReactor::
    MaybeFinishLocked(Status status) {
  VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
          << service_name_
          << "\": MaybeFinishLocked() with code=" << status.error_code()
          << " msg=" << status.error_message();
  if (!finish_called_) {
    VLOG(2) << "[HCS " << service_ << "] watcher " << this << " \""
            << service_name_ << "\": actually calling Finish()";
    finish_called_ = true;
    Finish(status);
  }
}

}
```