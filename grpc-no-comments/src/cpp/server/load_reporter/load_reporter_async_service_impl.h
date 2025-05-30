
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

class LoadReporterAsyncServiceImpl
    : public grpc::lb::v1::LoadReporter::AsyncService {
 public:
  explicit LoadReporterAsyncServiceImpl(
      std::unique_ptr<ServerCompletionQueue> cq);
  ~LoadReporterAsyncServiceImpl() override;

  void StartThread();

  LoadReporterAsyncServiceImpl(const LoadReporterAsyncServiceImpl&) = delete;
  LoadReporterAsyncServiceImpl& operator=(const LoadReporterAsyncServiceImpl&) =
      delete;

 private:
  class ReportLoadHandler;

  class CallableTag {
   public:
    using HandlerFunction =
        std::function<void(std::shared_ptr<ReportLoadHandler>, bool)>;

    CallableTag() {}

    CallableTag(HandlerFunction func,
                std::shared_ptr<ReportLoadHandler> handler)
        : handler_function_(std::move(func)), handler_(std::move(handler)) {
      CHECK(handler_function_ != nullptr);
      CHECK_NE(handler_, nullptr);
    }

    void Run(bool ok);

    std::shared_ptr<ReportLoadHandler> ReleaseHandler() {
      return std::move(handler_);
    }

   private:
    HandlerFunction handler_function_ = nullptr;
    std::shared_ptr<ReportLoadHandler> handler_;
  };

  class ReportLoadHandler {
   public:

    static void CreateAndStart(ServerCompletionQueue* cq,
                               LoadReporterAsyncServiceImpl* service,
                               LoadReporter* load_reporter);

    ReportLoadHandler(ServerCompletionQueue* cq,
                      LoadReporterAsyncServiceImpl* service,
                      LoadReporter* load_reporter);

   private:

    void OnRequestDelivered(std::shared_ptr<ReportLoadHandler> self, bool ok);

    void OnReadDone(std::shared_ptr<ReportLoadHandler> self, bool ok);

    void SendReport(std::shared_ptr<ReportLoadHandler> self, bool ok);
    void ScheduleNextReport(std::shared_ptr<ReportLoadHandler> self, bool ok);

    void OnFinishDone(std::shared_ptr<ReportLoadHandler> self, bool ok);

    void OnDoneNotified(std::shared_ptr<ReportLoadHandler> self, bool ok);

    void Shutdown(std::shared_ptr<ReportLoadHandler> self, const char* reason);

    std::string lb_id_;
    std::string load_balanced_hostname_;
    std::string load_key_;
    uint64_t load_report_interval_ms_;

    ServerContext ctx_;
    grpc::lb::v1::LoadReportRequest request_;

    ServerCompletionQueue* cq_;
    LoadReporterAsyncServiceImpl* service_;
    LoadReporter* load_reporter_;
    ServerAsyncReaderWriter<grpc::lb::v1::LoadReportResponse,
                            grpc::lb::v1::LoadReportRequest>
        stream_;

    enum CallStatus {
      WAITING_FOR_DELIVERY,
      DELIVERED,
      INITIAL_REQUEST_RECEIVED,
      INITIAL_RESPONSE_SENT,
      FINISH_CALLED
    } call_status_;
    bool shutdown_{false};
    bool done_notified_{false};
    bool is_cancelled_{false};
    CallableTag on_done_notified_;
    CallableTag on_finish_done_;
    CallableTag next_inbound_;
    CallableTag next_outbound_;
    std::unique_ptr<Alarm> next_report_alarm_;
  };

  static void Work(void* arg);

  void ScheduleNextFetchAndSample();

  void FetchAndSample(bool ok);

  std::unique_ptr<ServerCompletionQueue> cq_;

  grpc_core::Mutex cq_shutdown_mu_;
  std::atomic_bool shutdown_{false};
  std::unique_ptr<grpc_core::Thread> thread_;
  std::unique_ptr<LoadReporter> load_reporter_;
  std::unique_ptr<Alarm> next_fetch_and_sample_alarm_;
};

}
}

#endif
