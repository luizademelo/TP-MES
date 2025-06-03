Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_HEALTH_DEFAULT_HEALTH_CHECK_SERVICE_H
#define GRPC_SRC_CPP_SERVER_HEALTH_DEFAULT_HEALTH_CHECK_SERVICE_H

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/status.h>
#include <stddef.h>

#include <map>
#include <memory>
#include <string>

#include "absl/base/thread_annotations.h"
#include "src/core/util/ref_counted.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc {

// Default implementation of HealthCheckServiceInterface that maintains
// serving status for gRPC services and implements health checking protocol.
class DefaultHealthCheckService final : public HealthCheckServiceInterface {
 public:
  // Possible serving statuses for a service
  enum ServingStatus { NOT_FOUND, SERVING, NOT_SERVING };

  // Implementation of the health check service that handles RPC requests
  class HealthCheckServiceImpl : public Service {
   public:
    // Reactor class for handling Watch RPCs that streams health status updates
    class WatchReactor : public ServerWriteReactor<ByteBuffer>,
                         public grpc_core::RefCounted<WatchReactor> {
     public:
      WatchReactor(HealthCheckServiceImpl* service, const ByteBuffer* request);

      // Send a health status update to the client
      void SendHealth(ServingStatus status);

      // Overridden ServerWriteReactor methods
      void OnWriteDone(bool ok) override;  // Called when a write completes
      void OnCancel() override;            // Called when client cancels RPC
      void OnDone() override;              // Called when RPC is done

     private:
      // Send health status while holding the mutex
      void SendHealthLocked(ServingStatus status)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

      // Finish the RPC with given status if not already finished
      void MaybeFinishLocked(Status status) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

      HealthCheckServiceImpl* service_;  // Parent service implementation
      std::string service_name_;         // Service being watched
      ByteBuffer response_;              // Response buffer for health status

      grpc::internal::Mutex mu_;
      bool write_pending_ ABSL_GUARDED_BY(mu_) = false;  // Write in progress flag
      ServingStatus pending_status_ ABSL_GUARDED_BY(mu_) = NOT_FOUND;  // Next status to send
      bool finish_called_ ABSL_GUARDED_BY(mu_) = false;  // Finish called flag
    };

    explicit HealthCheckServiceImpl(DefaultHealthCheckService* database);
    ~HealthCheckServiceImpl() override;

   private:
    // Handler for Check RPC requests (unary)
    static ServerUnaryReactor* HandleCheckRequest(
        DefaultHealthCheckService* database, CallbackServerContext* context,
        const ByteBuffer* request, ByteBuffer* response);

    // Helper methods for request/response encoding/decoding
    static bool DecodeRequest(const ByteBuffer& request,
                              std::string* service_name);
    static bool EncodeResponse(ServingStatus status, ByteBuffer* response);

    DefaultHealthCheckService* database_;  // Backing data storage

    grpc::internal::Mutex mu_;
    grpc::internal::CondVar shutdown_condition_;  // Signals when shutdown complete
    bool shutdown_ ABSL_GUARDED_BY(mu_) = false;  // Shutdown flag
    size_t num_watches_ ABSL_GUARDED_BY(mu_) = 0;  // Active watch count
  };

  DefaultHealthCheckService();

  // HealthCheckServiceInterface overrides
  void SetServingStatus(const std::string& service_name, bool serving) override;
  void SetServingStatus(bool serving) override;  // Sets status for all services
  void Shutdown() override;  // Shuts down the health check service

  // Gets current serving status for a service
  ServingStatus GetServingStatus(const std::string& service_name) const;

  // Gets the health check service implementation
  HealthCheckServiceImpl* GetHealthCheckService();

 private:
  // Internal class storing service health data and watchers
  class ServiceData {
   public:
    void SetServingStatus(ServingStatus status);
    ServingStatus GetServingStatus() const { return status_; }
    // Adds a watcher for this service
    void AddWatch(
        grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher);
    // Removes a watcher for this service
    void RemoveWatch(HealthCheckServiceImpl::WatchReactor* watcher);
    // Checks if this service data is unused (no watchers and default status)
    bool Unused() const { return watchers_.empty() && status_ == NOT_FOUND; }

   private:
    ServingStatus status_ = NOT_FOUND;  // Current health status
    // Map of active watchers for this service
    std::map<HealthCheckServiceImpl::WatchReactor*,
             grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor>>
        watchers_;
  };

  // Registers a new watcher for a service
  void RegisterWatch(
      const std::string& service_name,
      grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher);

  // Unregisters a watcher for a service
  void UnregisterWatch(const std::string& service_name,
                       HealthCheckServiceImpl::WatchReactor* watcher);

  mutable grpc::internal::Mutex mu_;
  bool shutdown_ ABSL_GUARDED_BY(&mu_) = false;  // Service shutdown flag
  // Map of service names to their health data
  std::map<std::string, ServiceData> services_map_ ABSL_GUARDED_BY(&mu_);
  std::unique_ptr<HealthCheckServiceImpl> impl_;  // Service implementation
};

}

#endif
```

The comments added explain:
1. The overall purpose of each class and its role in the health checking system
2. The meaning of key enums and status values
3. The purpose of each method and member variable
4. Thread safety annotations and locking requirements
5. The flow of data between components
6. The relationship between the main service and its implementation classes

The comments are designed to help future developers understand:
- How the health check protocol is implemented
- How service status tracking works
- How watch streams are managed
- The threading model and synchronization points
- The lifecycle of health check requests