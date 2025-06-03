Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/cpp/server/load_reporter/load_reporter_async_service_impl.h"

#include <google/protobuf/repeated_ptr_field.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>
#include <grpcpp/support/status.h>
#include <inttypes.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/cpp/server/load_reporter/constants.h"

namespace grpc {
namespace load_reporter {

// Executes the handler function when the tag is called from the completion queue
void LoadReporterAsyncServiceImpl::CallableTag::Run(bool ok) {
  CHECK(handler_function_ != nullptr);
  CHECK_NE(handler_, nullptr);
  handler_function_(std::move(handler_), ok);
}

// Constructor for the async load reporter service implementation
// Initializes the completion queue, starts the worker thread, and sets up the load reporter
LoadReporterAsyncServiceImpl::LoadReporterAsyncServiceImpl(
    std::unique_ptr<ServerCompletionQueue> cq)
    : cq_(std::move(cq)) {
  // Create and start the worker thread for load reporting
  thread_ =
      std::make_unique<grpc_core::Thread>("server_load_reporting", Work, this);
  
  // Platform-specific CPU stats provider initialization
  std::unique_ptr<CpuStatsProvider> cpu_stats_provider = nullptr;
#if defined(GPR_LINUX) || defined(GPR_WINDOWS) || defined(GPR_APPLE)
  cpu_stats_provider = std::make_unique<CpuStatsProviderDefaultImpl>();
#endif
  
  // Create the load reporter with specified parameters
  load_reporter_ = std::make_unique<LoadReporter>(
      kFeedbackSampleWindowSeconds,
      std::unique_ptr<CensusViewProvider>(new CensusViewProviderDefaultImpl()),
      std::move(cpu_stats_provider));
}

// Destructor for the async load reporter service implementation
// Performs cleanup including shutting down the completion queue and joining the worker thread
LoadReporterAsyncServiceImpl::~LoadReporterAsyncServiceImpl() {
  shutdown_ = true;
  {
    grpc_core::MutexLock lock(&cq_shutdown_mu_);
    cq_->Shutdown();
  }
  if (next_fetch_and_sample_alarm_ != nullptr) {
    next_fetch_and_sample_alarm_->Cancel();
  }
  thread_->Join();
}

// Schedules the next fetch-and-sample operation after the specified interval
void LoadReporterAsyncServiceImpl::ScheduleNextFetchAndSample() {
  // Calculate next execution time
  auto next_fetch_and_sample_time =
      gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                   gpr_time_from_millis(kFetchAndSampleIntervalSeconds * 1000,
                                        GPR_TIMESPAN));
  {
    grpc_core::MutexLock lock(&cq_shutdown_mu_);
    if (shutdown_) return;

    // Set up alarm for next execution
    next_fetch_and_sample_alarm_ = std::make_unique<Alarm>();
    next_fetch_and_sample_alarm_->Set(cq_.get(), next_fetch_and_sample_time,
                                      this);
  }
  VLOG(2) << "[LRS " << this << "] Next fetch-and-sample scheduled.";
}

// Performs the fetch-and-sample operation and schedules the next one
void LoadReporterAsyncServiceImpl::FetchAndSample(bool ok) {
  if (!ok) {
    LOG(INFO) << "[LRS " << this << "] Fetch-and-sample is stopped.";
    return;
  }
  VLOG(2) << "[LRS " << this << "] Starting a fetch-and-sample...";
  load_reporter_->FetchAndSample();
  ScheduleNextFetchAndSample();
}

// Main worker thread function that handles load reporting operations
void LoadReporterAsyncServiceImpl::Work(void* arg) {
  LoadReporterAsyncServiceImpl* service =
      static_cast<LoadReporterAsyncServiceImpl*>(arg);
  // Start initial fetch-and-sample
  service->FetchAndSample(true);

  // Small delay before starting the report handler
  gpr_sleep_until(gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                               gpr_time_from_seconds(1, GPR_TIMESPAN)));
  
  // Create and start the initial report load handler
  ReportLoadHandler::CreateAndStart(service->cq_.get(), service,
                                    service->load_reporter_.get());
  
  // Main event loop for processing completion queue events
  void* tag;
  bool ok;
  while (true) {
    if (!service->cq_->Next(&tag, &ok)) {
      // Break if shutdown was requested
      CHECK(service->shutdown_);
      break;
    }
    if (tag == service) {
      // Handle fetch-and-sample events
      service->FetchAndSample(ok);
    } else {
      // Handle other callable tags
      auto* next_step = static_cast<CallableTag*>(tag);
      next_step->Run(ok);
    }
  }
}

// Starts the worker thread
void LoadReporterAsyncServiceImpl::StartThread() { thread_->Start(); }

// Creates and starts a new ReportLoadHandler instance
void LoadReporterAsyncServiceImpl::ReportLoadHandler::CreateAndStart(
    ServerCompletionQueue* cq, LoadReporterAsyncServiceImpl* service,
    LoadReporter* load_reporter) {
  // Create new handler instance
  std::shared_ptr<ReportLoadHandler> handler =
      std::make_shared<ReportLoadHandler>(cq, service, load_reporter);
  ReportLoadHandler* p = handler.get();
  
  {
    grpc_core::MutexLock lock(&service->cq_shutdown_mu_);
    if (service->shutdown_) return;
    
    // Set up callbacks for async operations
    p->on_done_notified_ =
        CallableTag(std::bind(&ReportLoadHandler::OnDoneNotified, p,
                              std::placeholders::_1, std::placeholders::_2),
                    handler);
    p->next_inbound_ =
        CallableTag(std::bind(&ReportLoadHandler::OnRequestDelivered, p,
                              std::placeholders::_1, std::placeholders::_2),
                    std::move(handler));
    
    // Register for notification when call is done
    p->ctx_.AsyncNotifyWhenDone(&p->on_done_notified_);
    
    // Start the async request for load reporting
    service->RequestReportLoad(&p->ctx_, &p->stream_, cq, cq,
                               &p->next_inbound_);
  }
}

// Constructor for ReportLoadHandler
LoadReporterAsyncServiceImpl::ReportLoadHandler::ReportLoadHandler(
    ServerCompletionQueue* cq, LoadReporterAsyncServiceImpl* service,
    LoadReporter* load_reporter)
    : cq_(cq),
      service_(service),
      load_reporter_(load_reporter),
      stream_(&ctx_),
      call_status_(WAITING_FOR_DELIVERY) {}

// Callback when a request is delivered to the handler
void LoadReporterAsyncServiceImpl::ReportLoadHandler::OnRequestDelivered(
    std::shared_ptr<ReportLoadHandler> self, bool ok) {
  if (ok) {
    call_status_ = DELIVERED;
  } else {
    // Clean up if delivery failed
    CHECK_NE(on_done_notified_.ReleaseHandler(), nullptr);
  }
  
  // Shutdown if request failed or service is shutting down
  if (!ok || shutdown_) {
    Shutdown(std::move(self), "OnRequestDelivered");
    return;
  }

  // Create a new handler for the next request
  CreateAndStart(cq_, service_, load_reporter_);
  
  {
    grpc_core::ReleasableMutexLock lock(&service_->cq_shutdown_mu_);
    if (service_->shutdown_) {
      lock.Release();
      Shutdown(std::move(self), "OnRequestDelivered");
      return;
    }
    
    // Set up callback for reading the request
    next_inbound_ =
        CallableTag(std::bind(&ReportLoadHandler::OnReadDone, this,
                              std::placeholders::_1, std::placeholders::_2),
                    std::move(self));
    stream_.Read(&request_, &next_inbound_);
  }

  // Generate LB ID for this request and log
  lb_id_ = load_reporter_->GenerateLbId();
  LOG(INFO) << "[LRS " << service_
            << "] Call request delivered (lb_id_: " << lb_id_
            << ", handler: " << this
            << "). Start reading the initial request...";
}

// Callback when a read operation completes
void LoadReporterAsyncServiceImpl::ReportLoadHandler::OnReadDone(
    std::shared_ptr<ReportLoadHandler> self, bool ok) {
  if (!ok || shutdown_) {
    if (!ok && call_status_ < INITIAL_REQUEST_RECEIVED) {
      LOG(INFO) << "[LRS " << service_
                << "] Failed reading the initial request from the stream "
                   "(lb_id_: "
                << lb_id_ << ", handler: " << this
                << ", done_notified: " << done_notified_
                << ", is_cancelled: " << is_cancelled_ << ").";
    }
    Shutdown(std::move(self), "OnReadDone");
    return;
  }

  // Process initial request
  if (call_status_ < INITIAL_REQUEST_RECEIVED) {
    if (!request_.has_initial_request()) {
      Shutdown(std::move(self), "OnReadDone+initial_request_not_found");
    } else {
      call_status_ = INITIAL_REQUEST_RECEIVED;
      const auto& initial_request = request_.initial_request();
      load_balanced_hostname_ = initial_request.load_balanced_hostname();
      load_key_ = initial_request.load_key();
      
      // Notify load reporter about new stream
      load_reporter_->ReportStreamCreated(load_balanced_hostname_, lb_id_,
                                          load_key_);
      
      // Calculate report interval
      const auto& load_report_interval = initial_request.load_report_interval();
      load_report_interval_ms_ =
          static_cast<unsigned long>((load_report_interval.seconds() * 1000) +
                                     (load_report_interval.nanos() / 1000);
      
      LOG(INFO) << "[LRS " << service_
                << "] Initial request received. Start load reporting (load "
                   "balanced host: "
                << load_balanced_hostname_
                << ", interval: " << load_report_interval_ms_
                << " ms, lb_id_: " << lb_id_ << ", handler: " << this << ")...";
      
      // Send initial report
      SendReport(self, true);

      {
        grpc_core::ReleasableMutexLock lock(&service_->cq_shutdown_mu_);
        if (service_->shutdown_) {
          lock.Release();
          Shutdown(std::move(self), "OnReadDone");
          return;
        }
        
        // Set up for next read
        next_inbound_ =
            CallableTag(std::bind(&ReportLoadHandler::OnReadDone, this,
                                  std::placeholders::_1, std::placeholders::_2),
                        std::move(self));
        stream_.Read(&request_, &next_inbound_);
      }
    }
  } else {
    // Unexpected additional request
    LOG(ERROR) << "[LRS " << service_
               << "] Another request received (lb_id_: " << lb_id_
               << ", handler: " << this << ").";
    Shutdown(std::move(self), "OnReadDone+second_request");
  }
}

// Schedules the next load report to be sent
void LoadReporterAsyncServiceImpl::ReportLoadHandler::ScheduleNextReport(
    std::shared_ptr<ReportLoadHandler> self, bool ok) {
  if (!ok || shutdown_) {
    Shutdown(std::move(self), "ScheduleNextReport");
    return;
  }
  
  // Calculate next report time
  auto next_report_time = gpr_time_add(
      gpr_now(GPR_CLOCK_MONOTONIC),
      gpr_time_from_millis(load_report_interval_ms_, GPR_TIMESPAN));
  
  {
    grpc_core::ReleasableMutexLock lock(&service_->cq_shutdown_mu_);
    if (service_->shutdown_) {
      lock.Release();
      Shutdown(std::move(self), "ScheduleNextReport");
      return;
    }
    
    // Set up callback for next report
    next_outbound_ =
        CallableTag(std::bind(&ReportLoadHandler::SendReport, this,
                              std::placeholders::_1, std::placeholders::_2),
                    std::move(self));

    // Set alarm for next report
    next_report_alarm_ = std::make_unique<Alarm>();
    next_report_alarm_->Set(cq_, next_report_time, &next_outbound_);
  }
  VLOG(2) << "[LRS " << service_
          << "] Next load report scheduled (lb_id_: " << lb_id_
          << ", handler: " << this << ").";
}

// Sends a load report to the client
void LoadReporterAsyncServiceImpl::ReportLoadHandler::SendReport(
    std::shared_ptr<ReportLoadHandler> self, bool ok) {
  if (!ok || shutdown_) {
    Shutdown(std::move(self), "SendReport");
    return;
  }
  
  // Prepare the load report response
  grpc::lb::v1::LoadReportResponse response;
  auto loads = load_reporter_->GenerateLoads(load_balanced_hostname_, lb_id_);
  response.mutable_load()->Swap(&loads);
  auto feedback = load_reporter_->GenerateLoadBalancingFeedback();
  response.mutable_load_balancing_feedback()->Swap(&feedback);
  
  // Add initial response data if this is the first report
  if (call_status_ < INITIAL_RESPONSE_SENT) {
    auto initial_response = response.mutable_initial_response();
    initial_response->set_load_balancer_id(lb_id_);
    initial_response->set_implementation_id(
        grpc::lb::v1::InitialLoadReportResponse::CPP);
    initial_response->set_server_version(kVersion);
    call_status_ = INITIAL_RESPONSE_SENT;
  }
  
  {
    grpc_core::ReleasableMutexLock lock(&service_->cq_shutdown_mu_);
    if (service_->shutdown_) {
      lock.Release();
      Shutdown(std::move(self), "SendReport");
      return;
    }
    
    // Set up callback for after write completes
    next_outbound_ =
        CallableTag(std::bind(&ReportLoadHandler::ScheduleNextReport, this,
                              std::placeholders::_1, std::placeholders::_2),
                    std::move(self));
    
    // Send the report
    stream_.Write(response, &next_outbound_);
    LOG(INFO) << "[LRS " << service_
              << "] Sending load report (lb_id_: " << lb_id_
              << ", handler: " << this
              << ", loads count: " << response.load().size() << ")...";
  }
}

// Callback when the RPC is notified as done
void LoadReporterAsyncServiceImpl::ReportLoadHandler::OnDoneNotified(
    std::shared_ptr<ReportLoadHandler> self, bool ok) {
  CHECK(ok);
  done_notified_ = true;
  if (ctx_.IsCancelled()) {
    is_cancelled_ = true;
  }
  LOG(INFO) << "[LRS " << service_
            << "] Load reporting call is notified done (handler: " << this
            << ", is_cancelled: " << is_cancelled_ << ").";
  Shutdown(std::move(self), "OnDoneNotified");
}

// Shuts down the handler and cleans up resources
void LoadReporterAsyncServiceImpl::ReportLoadHandler::Shutdown(
    std::shared_ptr<ReportLoadHandler> self, const char* reason) {
  if (!shutdown_) {
    LOG(INFO) << "[LRS " << service_
              << "] Shutting down the handler (lb_id_: " << lb_id_
              << ", handler: " << this << ", reason: " << reason << ").";
    shutdown_ = true;
    
    // Clean up resources if we received an initial request
    if (call_status_ >= INITIAL_REQUEST_RECEIVED) {
      load_reporter_->ReportStreamClosed(load_balanced_hostname_, lb_id_);
      next_report_alarm_->Cancel();
    }
  }

  // Finish the call if needed
  if (call_status_ >= DELIVERED && call_status_ < FINISH_CALLED) {
    grpc_core::MutexLock lock(&service_->cq_shutdown_mu_);
    if (!service_->shutdown_) {
      on_finish_done_ =
          CallableTag(std::bind(&ReportLoadHandler::OnFinishDone, this,
                                std::placeholders::_1, std::placeholders::_2),
                      std::move(self));

      stream_.Finish(Status::CANCELLED, &on_finish_done_);
      call_status_ = FINISH_CALLED;
    }
  }
}

// Callback when finishing the call completes
void LoadReporterAsyncServiceImpl::ReportLoadHandler::OnFinishDone(
    std::shared_ptr<ReportLoadHandler> , bool ok) {
  if (ok) {
    LOG(INFO) << "[LRS " << service_
              << "] Load reporting finished (lb_id_: " << lb_id_
              << ", handler: " << this << ").";
  }
}

}
}
```