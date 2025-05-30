// Copyright 2016 gRPC authors.

#ifndef GRPC_TEST_CPP_END2END_CONNECTION_ATTEMPT_INJECTOR_H
#define GRPC_TEST_CPP_END2END_CONNECTION_ATTEMPT_INJECTOR_H

#include <memory>

#include "src/core/lib/event_engine/channel_args_endpoint_config.h"
#include "src/core/lib/iomgr/tcp_client.h"
#include "src/core/util/time.h"

namespace grpc {
namespace testing {

// Note: This must be "final" to avoid tsan problems in both the ctor

class ConnectionAttemptInjector final {
 private:

  class QueuedAttempt;

  grpc_core::Mutex mu_;

 public:
  class Hold {
   public:

    Hold(ConnectionAttemptInjector* injector, int port,
         bool intercept_completion);

    void Wait();

    void Resume();

    void Fail(grpc_error_handle error);

    void WaitForCompletion();

    bool IsStarted();

   private:
    friend class ConnectionAttemptInjector;

    static void OnComplete(void* arg, grpc_error_handle error);

    ConnectionAttemptInjector* injector_;
    const int port_;
    const bool intercept_completion_;
    std::unique_ptr<QueuedAttempt> queued_attempt_
        ABSL_GUARDED_BY(&ConnectionAttemptInjector::mu_);
    grpc_core::CondVar start_cv_;
    grpc_closure on_complete_;
    grpc_closure* original_on_complete_;
    grpc_core::CondVar complete_cv_;
  };

  static void Init();

  ConnectionAttemptInjector();
  ~ConnectionAttemptInjector();

  std::unique_ptr<Hold> AddHold(int port, bool intercept_completion = false);

  void SetDelay(grpc_core::Duration delay);

 private:
  static grpc_tcp_client_vtable kDelayedConnectVTable;

  class QueuedAttempt {
   public:
    QueuedAttempt(grpc_closure* closure, grpc_endpoint** ep,
                  grpc_pollset_set* interested_parties,
                  const grpc_event_engine::experimental::EndpointConfig& config,
                  const grpc_resolved_address* addr,
                  grpc_core::Timestamp deadline);
    ~QueuedAttempt();

    void Resume();

    void Fail(grpc_error_handle error);

   private:
    grpc_closure* closure_;
    grpc_endpoint** endpoint_;
    grpc_pollset_set* interested_parties_;
    grpc_event_engine::experimental::ChannelArgsEndpointConfig config_;
    grpc_resolved_address address_;
    grpc_core::Timestamp deadline_;
  };

  class InjectedDelay {
   public:
    virtual ~InjectedDelay() = default;

    InjectedDelay(grpc_core::Duration duration, grpc_closure* closure,
                  grpc_endpoint** ep, grpc_pollset_set* interested_parties,
                  const grpc_event_engine::experimental::EndpointConfig& config,
                  const grpc_resolved_address* addr,
                  grpc_core::Timestamp deadline);

   private:
    void TimerCallback();

    QueuedAttempt attempt_;
  };

  void HandleConnection(
      grpc_closure* closure, grpc_endpoint** ep,
      grpc_pollset_set* interested_parties,
      const grpc_event_engine::experimental::EndpointConfig& config,
      const grpc_resolved_address* addr, grpc_core::Timestamp deadline);

  static void AttemptConnection(
      grpc_closure* closure, grpc_endpoint** ep,
      grpc_pollset_set* interested_parties,
      const grpc_event_engine::experimental::EndpointConfig& config,
      const grpc_resolved_address* addr, grpc_core::Timestamp deadline);

  static int64_t TcpConnect(
      grpc_closure* closure, grpc_endpoint** ep,
      grpc_pollset_set* interested_parties,
      const grpc_event_engine::experimental::EndpointConfig& config,
      const grpc_resolved_address* addr, grpc_core::Timestamp deadline);
  static bool TcpConnectCancel(int64_t connection_handle);

  std::vector<Hold*> holds_ ABSL_GUARDED_BY(&mu_);
  std::optional<grpc_core::Duration> delay_ ABSL_GUARDED_BY(&mu_);
};

}
}

#endif
