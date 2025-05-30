
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/cpu.h>
#include <grpcpp/alarm.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>

#include <list>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "absl/log/log.h"
#include "absl/memory/memory.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/benchmark_service.grpc.pb.h"
#include "test/cpp/qps/client.h"
#include "test/cpp/qps/usage_timer.h"

namespace grpc {
namespace testing {

struct CallbackClientRpcContext {
  explicit CallbackClientRpcContext(BenchmarkService::Stub* stub)
      : alarm_(nullptr), stub_(stub) {}

  ~CallbackClientRpcContext() {}

  SimpleResponse response_;
  ClientContext context_;
  std::unique_ptr<Alarm> alarm_;
  BenchmarkService::Stub* stub_;
};

static std::unique_ptr<BenchmarkService::Stub> BenchmarkStubCreator(
    const std::shared_ptr<Channel>& ch) {
  return BenchmarkService::NewStub(ch);
}

class CallbackClient
    : public ClientImpl<BenchmarkService::Stub, SimpleRequest> {
 public:
  explicit CallbackClient(const ClientConfig& config)
      : ClientImpl<BenchmarkService::Stub, SimpleRequest>(
            config, BenchmarkStubCreator) {
    num_threads_ = NumThreads(config);
    rpcs_done_ = 0;

    SetupLoadTest(config, 1);
    total_outstanding_rpcs_ =
        config.client_channels() * config.outstanding_rpcs_per_channel();
  }

  ~CallbackClient() override {}

  void NotifyMainThreadOfThreadCompletion() {
    std::lock_guard<std::mutex> l(shutdown_mu_);
    rpcs_done_++;
    if (rpcs_done_ == total_outstanding_rpcs_) {
      shutdown_cv_.notify_one();
    }
  }

  gpr_timespec NextRPCIssueTime() {
    std::lock_guard<std::mutex> l(next_issue_time_mu_);
    return Client::NextIssueTime(0);
  }

 protected:
  size_t num_threads_;
  size_t total_outstanding_rpcs_;

  std::mutex shutdown_mu_;
  std::condition_variable shutdown_cv_;

  size_t rpcs_done_;

  std::vector<std::unique_ptr<CallbackClientRpcContext>> ctx_;

  virtual void InitThreadFuncImpl(size_t thread_idx) = 0;
  virtual bool ThreadFuncImpl(Thread* t, size_t thread_idx) = 0;

  void ThreadFunc(size_t thread_idx, Thread* t) override {
    InitThreadFuncImpl(thread_idx);
    ThreadFuncImpl(t, thread_idx);
  }

 private:
  std::mutex next_issue_time_mu_;

  int NumThreads(const ClientConfig& config) {
    int num_threads = config.async_client_threads();
    if (num_threads <= 0) {
      num_threads = cores_;
      LOG(INFO) << "Sizing callback client to " << num_threads << " threads";
    }
    return num_threads;
  }

  void DestroyMultithreading() final {
    std::unique_lock<std::mutex> l(shutdown_mu_);
    while (rpcs_done_ != total_outstanding_rpcs_) {
      shutdown_cv_.wait(l);
    }
    EndThreads();
  }
};

class CallbackUnaryClient final : public CallbackClient {
 public:
  explicit CallbackUnaryClient(const ClientConfig& config)
      : CallbackClient(config) {
    for (int ch = 0; ch < config.client_channels(); ch++) {
      for (int i = 0; i < config.outstanding_rpcs_per_channel(); i++) {
        ctx_.emplace_back(
            new CallbackClientRpcContext(channels_[ch].get_stub()));
      }
    }
    StartThreads(num_threads_);
  }
  ~CallbackUnaryClient() override {}

 protected:
  bool ThreadFuncImpl(Thread* t, size_t thread_idx) override {
    for (size_t vector_idx = thread_idx; vector_idx < total_outstanding_rpcs_;
         vector_idx += num_threads_) {
      ScheduleRpc(t, vector_idx);
    }
    return true;
  }

  void InitThreadFuncImpl(size_t ) override {}

 private:
  void ScheduleRpc(Thread* t, size_t vector_idx) {
    if (!closed_loop_) {
      gpr_timespec next_issue_time = NextRPCIssueTime();

      if (ctx_[vector_idx]->alarm_ == nullptr) {
        ctx_[vector_idx]->alarm_ = std::make_unique<Alarm>();
      }
      ctx_[vector_idx]->alarm_->Set(next_issue_time,
                                    [this, t, vector_idx](bool ) {
                                      IssueUnaryCallbackRpc(t, vector_idx);
                                    });
    } else {
      IssueUnaryCallbackRpc(t, vector_idx);
    }
  }

  void IssueUnaryCallbackRpc(Thread* t, size_t vector_idx) {
    double start = UsageTimer::Now();
    ctx_[vector_idx]->stub_->async()->UnaryCall(
        (&ctx_[vector_idx]->context_), &request_, &ctx_[vector_idx]->response_,
        [this, t, start, vector_idx](grpc::Status s) {

          HistogramEntry entry;
          if (s.ok()) {
            entry.set_value((UsageTimer::Now() - start) * 1e9);
          }
          entry.set_status(s.error_code());
          t->UpdateHistogram(&entry);

          if (ThreadCompleted() || !s.ok()) {

            NotifyMainThreadOfThreadCompletion();
          } else {

            ctx_[vector_idx] = std::make_unique<CallbackClientRpcContext>(
                ctx_[vector_idx]->stub_);

            ScheduleRpc(t, vector_idx);
          }
        });
  }
};

class CallbackStreamingClient : public CallbackClient {
 public:
  explicit CallbackStreamingClient(const ClientConfig& config)
      : CallbackClient(config),
        messages_per_stream_(config.messages_per_stream()) {
    for (int ch = 0; ch < config.client_channels(); ch++) {
      for (int i = 0; i < config.outstanding_rpcs_per_channel(); i++) {
        ctx_.emplace_back(
            new CallbackClientRpcContext(channels_[ch].get_stub()));
      }
    }
    StartThreads(num_threads_);
  }
  ~CallbackStreamingClient() override {}

  void AddHistogramEntry(double start, bool ok, Thread* thread_ptr) {

    HistogramEntry entry;
    if (ok) {
      entry.set_value((UsageTimer::Now() - start) * 1e9);
    }
    thread_ptr->UpdateHistogram(&entry);
  }

  int messages_per_stream() { return messages_per_stream_; }

 protected:
  const int messages_per_stream_;
};

class CallbackStreamingPingPongClient : public CallbackStreamingClient {
 public:
  explicit CallbackStreamingPingPongClient(const ClientConfig& config)
      : CallbackStreamingClient(config) {}
  ~CallbackStreamingPingPongClient() override {}
};

class CallbackStreamingPingPongReactor final
    : public grpc::ClientBidiReactor<SimpleRequest, SimpleResponse> {
 public:
  CallbackStreamingPingPongReactor(
      CallbackStreamingPingPongClient* client,
      std::unique_ptr<CallbackClientRpcContext> ctx)
      : client_(client), ctx_(std::move(ctx)), messages_issued_(0) {}

  void StartNewRpc() {
    ctx_->stub_->async()->StreamingCall(&(ctx_->context_), this);
    write_time_ = UsageTimer::Now();
    StartWrite(client_->request());
    writes_done_started_.clear();
    StartCall();
  }

  void OnWriteDone(bool ok) override {
    if (!ok) {
      LOG(ERROR) << "Error writing RPC";
    }
    if ((!ok || client_->ThreadCompleted()) &&
        !writes_done_started_.test_and_set()) {
      StartWritesDone();
    }
    StartRead(&ctx_->response_);
  }

  void OnReadDone(bool ok) override {
    client_->AddHistogramEntry(write_time_, ok, thread_ptr_);

    if (client_->ThreadCompleted() || !ok ||
        (client_->messages_per_stream() != 0 &&
         ++messages_issued_ >= client_->messages_per_stream())) {
      if (!ok) {
        LOG(ERROR) << "Error reading RPC";
      }
      if (!writes_done_started_.test_and_set()) {
        StartWritesDone();
      }
      return;
    }
    if (!client_->IsClosedLoop()) {
      gpr_timespec next_issue_time = client_->NextRPCIssueTime();

      ctx_->alarm_->Set(next_issue_time, [this](bool ) {
        write_time_ = UsageTimer::Now();
        StartWrite(client_->request());
      });
    } else {
      write_time_ = UsageTimer::Now();
      StartWrite(client_->request());
    }
  }

  void OnDone(const Status& s) override {
    if (client_->ThreadCompleted() || !s.ok()) {
      client_->NotifyMainThreadOfThreadCompletion();
      return;
    }
    ctx_ = std::make_unique<CallbackClientRpcContext>(ctx_->stub_);
    ScheduleRpc();
  }

  void ScheduleRpc() {
    if (!client_->IsClosedLoop()) {
      gpr_timespec next_issue_time = client_->NextRPCIssueTime();

      if (ctx_->alarm_ == nullptr) {
        ctx_->alarm_ = std::make_unique<Alarm>();
      }
      ctx_->alarm_->Set(next_issue_time,
                        [this](bool ) { StartNewRpc(); });
    } else {
      StartNewRpc();
    }
  }

  void set_thread_ptr(Client::Thread* ptr) { thread_ptr_ = ptr; }

  CallbackStreamingPingPongClient* client_;
  std::unique_ptr<CallbackClientRpcContext> ctx_;
  std::atomic_flag writes_done_started_;
  Client::Thread* thread_ptr_;
  double write_time_;
  int messages_issued_;
};

class CallbackStreamingPingPongClientImpl final
    : public CallbackStreamingPingPongClient {
 public:
  explicit CallbackStreamingPingPongClientImpl(const ClientConfig& config)
      : CallbackStreamingPingPongClient(config) {
    for (size_t i = 0; i < total_outstanding_rpcs_; i++) {
      reactor_.emplace_back(
          new CallbackStreamingPingPongReactor(this, std::move(ctx_[i])));
    }
  }
  ~CallbackStreamingPingPongClientImpl() override {}

  bool ThreadFuncImpl(Client::Thread* t, size_t thread_idx) override {
    for (size_t vector_idx = thread_idx; vector_idx < total_outstanding_rpcs_;
         vector_idx += num_threads_) {
      reactor_[vector_idx]->set_thread_ptr(t);
      reactor_[vector_idx]->ScheduleRpc();
    }
    return true;
  }

  void InitThreadFuncImpl(size_t ) override {}

 private:
  std::vector<std::unique_ptr<CallbackStreamingPingPongReactor>> reactor_;
};

std::unique_ptr<Client> CreateCallbackClient(const ClientConfig& config) {
  switch (config.rpc_type()) {
    case UNARY:
      return std::unique_ptr<Client>(new CallbackUnaryClient(config));
    case STREAMING:
      return std::unique_ptr<Client>(
          new CallbackStreamingPingPongClientImpl(config));
    case STREAMING_FROM_CLIENT:
    case STREAMING_FROM_SERVER:
    case STREAMING_BOTH_WAYS:
      grpc_core::Crash(
          "STREAMING_FROM_* scenarios are not supported by the callback "
          "API");
    default:
      grpc_core::Crash(absl::StrCat("Unknown RPC type: ", config.rpc_type()));
  }
}

}
}
