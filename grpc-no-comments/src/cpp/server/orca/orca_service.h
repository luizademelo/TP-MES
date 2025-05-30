
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_ORCA_ORCA_SERVICE_H
#define GRPC_SRC_CPP_SERVER_ORCA_ORCA_SERVICE_H

#include <grpc/event_engine/event_engine.h>
#include <grpcpp/ext/orca_service.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/status.h>

#include <atomic>
#include <memory>
#include <optional>

#include "absl/base/thread_annotations.h"
#include "absl/strings/string_view.h"
#include "src/core/util/ref_counted.h"

namespace grpc {
namespace experimental {

class OrcaService::Reactor
    : public ServerWriteReactor<ByteBuffer>,
      public grpc_core::RefCounted<OrcaService::Reactor> {
 public:
  explicit Reactor(OrcaService* service, absl::string_view peer,
                   const ByteBuffer* request_buffer,
                   std::shared_ptr<OrcaService::ReactorHook> hook);

  void OnWriteDone(bool ok) override;

  void OnCancel() override;

  void OnDone() override;

 private:
  void FinishRpc(grpc::Status status);

  void SendResponse();

  bool MaybeScheduleTimer();

  bool MaybeCancelTimer();

  void OnTimer();

  OrcaService* service_;

  grpc::internal::Mutex timer_mu_;
  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      timer_handle_ ABSL_GUARDED_BY(&timer_mu_);
  bool cancelled_ ABSL_GUARDED_BY(&timer_mu_) = false;

  grpc_event_engine::experimental::EventEngine::Duration report_interval_;
  ByteBuffer response_;
  std::shared_ptr<ReactorHook> hook_;
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> engine_;
};

}
}

#endif
