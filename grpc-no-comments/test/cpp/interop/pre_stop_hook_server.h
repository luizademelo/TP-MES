
// Copyright 2023 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_PRE_STOP_HOOK_SERVER_H
#define GRPC_TEST_CPP_INTEROP_PRE_STOP_HOOK_SERVER_H

#include <grpc/support/port_platform.h>
#include <grpcpp/server.h>

#include "src/core/util/sync.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"

namespace grpc {
namespace testing {

class HookServiceImpl final : public HookService::CallbackService {
 public:
  ServerUnaryReactor* Hook(CallbackServerContext* context,
                           const Empty* ,
                           Empty* ) override;

  ServerUnaryReactor* SetReturnStatus(CallbackServerContext* context,
                                      const SetReturnStatusRequest* request,
                                      Empty* ) override;

  ServerUnaryReactor* ClearReturnStatus(CallbackServerContext* context,
                                        const Empty* request,
                                        Empty* ) override;

  void AddReturnStatus(const Status& status);

  bool TestOnlyExpectRequests(size_t expected_requests_count,
                              const absl::Duration& timeout);

  void Stop();

 private:
  void MatchRequestsAndStatuses() ABSL_EXCLUSIVE_LOCKS_REQUIRED(mu_);

  grpc_core::Mutex mu_;
  grpc_core::CondVar request_var_ ABSL_GUARDED_BY(&mu_);
  std::vector<ServerUnaryReactor*> pending_requests_ ABSL_GUARDED_BY(&mu_);
  std::vector<Status> pending_statuses_ ABSL_GUARDED_BY(&mu_);
  std::optional<Status> respond_all_status_ ABSL_GUARDED_BY(&mu_);
};

class PreStopHookServer;

class PreStopHookServerManager {
 public:
  Status Start(int port, size_t timeout_s);
  Status Stop();
  void Return(StatusCode code, absl::string_view description);

  bool TestOnlyExpectRequests(
      size_t expected_requests_count,
      const absl::Duration& timeout = absl::Seconds(15));

 private:

  struct PreStopHookServerDeleter {
    void operator()(PreStopHookServer* server);
  };

  std::unique_ptr<PreStopHookServer, PreStopHookServerDeleter> server_;
};

}
}
#endif
