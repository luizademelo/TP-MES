
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_CLIENT_CHTTP2_CONNECTOR_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHTTP2_CLIENT_CHTTP2_CONNECTOR_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/support/port_platform.h>

#include <optional>

#include "absl/base/thread_annotations.h"
#include "src/core/client_channel/connector.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/endpoint.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class Chttp2Connector : public SubchannelConnector {
 public:
  void Connect(const Args& args, Result* result, grpc_closure* notify) override;
  void Shutdown(grpc_error_handle error) override;

 private:
  void OnHandshakeDone(absl::StatusOr<HandshakerArgs*> result);
  static void OnReceiveSettings(void* arg, grpc_error_handle error);
  void OnTimeout() ABSL_LOCKS_EXCLUDED(mu_);

  void MaybeNotify(grpc_error_handle error);

  Mutex mu_;
  Args args_;
  Result* result_ = nullptr;
  grpc_closure* notify_ = nullptr;
  bool shutdown_ = false;
  grpc_closure on_receive_settings_;
  std::optional<grpc_event_engine::experimental::EventEngine::TaskHandle>
      timer_handle_ ABSL_GUARDED_BY(mu_);

  grpc_event_engine::experimental::EventEngine* event_engine_
      ABSL_GUARDED_BY(mu_);
  std::optional<grpc_error_handle> notify_error_;
  RefCountedPtr<HandshakeManager> handshake_mgr_;
};

absl::StatusOr<grpc_channel*> CreateHttp2Channel(std::string target,
                                                 const ChannelArgs& args);

}

#endif
