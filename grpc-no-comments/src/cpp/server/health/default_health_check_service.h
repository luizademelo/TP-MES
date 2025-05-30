
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

class DefaultHealthCheckService final : public HealthCheckServiceInterface {
 public:
  enum ServingStatus { NOT_FOUND, SERVING, NOT_SERVING };

  class HealthCheckServiceImpl : public Service {
   public:

    class WatchReactor : public ServerWriteReactor<ByteBuffer>,
                         public grpc_core::RefCounted<WatchReactor> {
     public:
      WatchReactor(HealthCheckServiceImpl* service, const ByteBuffer* request);

      void SendHealth(ServingStatus status);

      void OnWriteDone(bool ok) override;
      void OnCancel() override;
      void OnDone() override;

     private:
      void SendHealthLocked(ServingStatus status)
          ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

      void MaybeFinishLocked(Status status) ABSL_EXCLUSIVE_LOCKS_REQUIRED(&mu_);

      HealthCheckServiceImpl* service_;
      std::string service_name_;
      ByteBuffer response_;

      grpc::internal::Mutex mu_;
      bool write_pending_ ABSL_GUARDED_BY(mu_) = false;
      ServingStatus pending_status_ ABSL_GUARDED_BY(mu_) = NOT_FOUND;
      bool finish_called_ ABSL_GUARDED_BY(mu_) = false;
    };

    explicit HealthCheckServiceImpl(DefaultHealthCheckService* database);

    ~HealthCheckServiceImpl() override;

   private:

    static ServerUnaryReactor* HandleCheckRequest(
        DefaultHealthCheckService* database, CallbackServerContext* context,
        const ByteBuffer* request, ByteBuffer* response);

    static bool DecodeRequest(const ByteBuffer& request,
                              std::string* service_name);
    static bool EncodeResponse(ServingStatus status, ByteBuffer* response);

    DefaultHealthCheckService* database_;

    grpc::internal::Mutex mu_;
    grpc::internal::CondVar shutdown_condition_;
    bool shutdown_ ABSL_GUARDED_BY(mu_) = false;
    size_t num_watches_ ABSL_GUARDED_BY(mu_) = 0;
  };

  DefaultHealthCheckService();

  void SetServingStatus(const std::string& service_name, bool serving) override;
  void SetServingStatus(bool serving) override;

  void Shutdown() override;

  ServingStatus GetServingStatus(const std::string& service_name) const;

  HealthCheckServiceImpl* GetHealthCheckService();

 private:

  class ServiceData {
   public:
    void SetServingStatus(ServingStatus status);
    ServingStatus GetServingStatus() const { return status_; }
    void AddWatch(
        grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher);
    void RemoveWatch(HealthCheckServiceImpl::WatchReactor* watcher);
    bool Unused() const { return watchers_.empty() && status_ == NOT_FOUND; }

   private:
    ServingStatus status_ = NOT_FOUND;
    std::map<HealthCheckServiceImpl::WatchReactor*,
             grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor>>
        watchers_;
  };

  void RegisterWatch(
      const std::string& service_name,
      grpc_core::RefCountedPtr<HealthCheckServiceImpl::WatchReactor> watcher);

  void UnregisterWatch(const std::string& service_name,
                       HealthCheckServiceImpl::WatchReactor* watcher);

  mutable grpc::internal::Mutex mu_;
  bool shutdown_ ABSL_GUARDED_BY(&mu_) = false;
  std::map<std::string, ServiceData> services_map_ ABSL_GUARDED_BY(&mu_);
  std::unique_ptr<HealthCheckServiceImpl> impl_;
};

}

#endif
