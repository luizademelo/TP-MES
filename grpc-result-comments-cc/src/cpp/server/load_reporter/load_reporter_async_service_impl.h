Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTER_ASYNC_SERVICE_IMPL_H
#define GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTER_ASYNC_SERVICE_IMPL_H

#include <grpc/support/port_platform.h>
#include <grpcpp/alarm.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/interceptor.h>
#include <stdint.h>

#include <atomic>
#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "absl/log/check.h"
#include "src/core/util/sync.h"
#include "src/core/util/thd.h"
#include "src/cpp/server/load_reporter/load_reporter.h"
#include "src/proto/grpc/lb/v1/load_reporter.grpc.pb.h"

namespace grpc {
namespace load_reporter {

// Implementation of the asynchronous LoadReporter service.
// This class handles load reporting requests from clients asynchronously.
class LoadReporterAsyncServiceImpl
    : public grpc::lb::v1::LoadReporter::AsyncService {
 public:
  // Constructor that takes ownership of a ServerCompletionQueue.
  explicit LoadReporterAsyncServiceImpl(
      std::unique_ptr<ServerCompletionQueue> cq);
  ~LoadReporterAsyncServiceImpl() override;

  // Starts the worker thread for handling load reporting.
  void StartThread();

  // Disable copy constructor and assignment operator.
  LoadReporterAsyncServiceImpl(const LoadReporterAsyncServiceImpl&) = delete;
  LoadReporterAsyncServiceImpl& operator=(const LoadReporterAsyncServiceImpl&) =
      delete;

 private:
  // Forward declaration of the handler class for ReportLoad RPCs.
  class ReportLoadHandler;

  // Tag that can be called back from the completion queue.
  // Used to associate callbacks with specific handler instances.
  class CallableTag {
   public:
    // Function type for handler callbacks.
    using HandlerFunction =
        std::function<void(std::shared_ptr<ReportLoadHandler>, bool)>;

    CallableTag() {}

    // Creates a CallableTag with the given handler function and handler instance.
    CallableTag(HandlerFunction func,
                std::shared_ptr<ReportLoadHandler> handler)
        : handler_function_(std::move(func)), handler_(std::move(handler)) {
      CHECK(handler_function_ != nullptr);
      CHECK_NE(handler_, nullptr);
    }

    // Executes the associated handler function.
    void Run(bool ok);

    // Releases ownership of the handler instance.
    std::shared_ptr<ReportLoadHandler> ReleaseHandler() {
      return std::move(handler_);
    }

   private:
    HandlerFunction handler_function_ = nullptr;
    std::shared_ptr<ReportLoadHandler> handler_;
  };

  // Handler class for individual ReportLoad RPC calls.
  class ReportLoadHandler {
   public:
    // Factory method to create and start a new handler.
    static void CreateAndStart(ServerCompletionQueue* cq,
                               LoadReporterAsyncServiceImpl* service,
                               LoadReporter* load_reporter);

    // Constructor for the handler.
    ReportLoadHandler(ServerCompletionQueue* cq,
                      LoadReporterAsyncServiceImpl* service,
                      LoadReporter* load_reporter);

   private:
    // Callback when the initial request is delivered.
    void OnRequestDelivered(std::shared_ptr<ReportLoadHandler> self, bool ok);

    // Callback when a read operation completes.
    void OnReadDone(std::shared_ptr<ReportLoadHandler> self, bool ok);

    // Sends a load report to the client.
    void SendReport(std::shared_ptr<ReportLoadHandler> self, bool ok);
    
    // Schedules the next load report to be sent.
    void ScheduleNextReport(std::shared_ptr<ReportLoadHandler> self, bool ok);

    // Callback when the finish operation completes.
    void OnFinishDone(std::shared_ptr<ReportLoadHandler> self, bool ok);

    // Callback when the RPC is done.
    void OnDoneNotified(std::shared_ptr<ReportLoadHandler> self, bool ok);

    // Shuts down the handler with the given reason.
    void Shutdown(std::shared_ptr<ReportLoadHandler> self, const char* reason);

    // Client identification and load reporting parameters
    std::string lb_id_;
    std::string load_balanced_hostname_;
    std::string load_key_;
    uint64_t load_report_interval_ms_;

    // gRPC server context for this RPC
    ServerContext ctx_;
    // The load report request from the client
    grpc::lb::v1::LoadReportRequest request_;

    // Completion queue and service references
    ServerCompletionQueue* cq_;
    LoadReporterAsyncServiceImpl* service_;
    LoadReporter* load_reporter_;
    // The bidirectional stream for load reports
    ServerAsyncReaderWriter<grpc::lb::v1::LoadReportResponse,
                            grpc::lb::v1::LoadReportRequest>
        stream_;

    // State machine for the RPC call
    enum CallStatus {
      WAITING_FOR_DELIVERY,    // Waiting for initial request delivery
      DELIVERED,               // Initial request delivered
      INITIAL_REQUEST_RECEIVED, // Initial request received from client
      INITIAL_RESPONSE_SENT,    // Initial response sent to client
      FINISH_CALLED             // RPC finished
    } call_status_;
    
    // State flags
    bool shutdown_{false};      // Whether shutdown has been initiated
    bool done_notified_{false}; // Whether done notification was received
    bool is_cancelled_{false};  // Whether the call was cancelled

    // Callable tags for various operations
    CallableTag on_done_notified_;
    CallableTag on_finish_done_;
    CallableTag next_inbound_;
    CallableTag next_outbound_;
    
    // Alarm for scheduling the next report
    std::unique_ptr<Alarm> next_report_alarm_;
  };

  // Static worker thread function.
  static void Work(void* arg);

  // Schedules the next fetch and sample operation.
  void ScheduleNextFetchAndSample();

  // Performs the fetch and sample operation for load reporting.
  void FetchAndSample(bool ok);

  // The completion queue for async operations
  std::unique_ptr<ServerCompletionQueue> cq_;

  // Mutex for protecting completion queue shutdown
  grpc_core::Mutex cq_shutdown_mu_;
  // Atomic flag indicating shutdown state
  std::atomic_bool shutdown_{false};
  // Worker thread for handling RPCs
  std::unique_ptr<grpc_core::Thread> thread_;
  // The load reporter instance
  std::unique_ptr<LoadReporter> load_reporter_;
  // Alarm for scheduling the next fetch and sample
  std::unique_ptr<Alarm> next_fetch_and_sample_alarm_;
};

}  // namespace load_reporter
}  // namespace grpc

#endif  // GRPC_SRC_CPP_SERVER_LOAD_REPORTER_LOAD_REPORTER_ASYNC_SERVICE_IMPL_H
```

The comments explain:
1. The overall purpose of the class and its components
2. The role of each method and member variable
3. The state machine used for handling RPC calls
4. The asynchronous operation flow
5. Important implementation details
6. Thread safety considerations

The comments are designed to help future developers understand:
- How the load reporting service works
- The lifecycle of RPC handling
- The asynchronous operation flow
- The purpose of each component
- Important implementation details