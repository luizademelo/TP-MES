
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpc/support/alloc.h>
#include <grpc/support/time.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/benchmark_service.grpc.pb.h"
#include "test/cpp/qps/client.h"
#include "test/cpp/qps/interarrival.h"
#include "test/cpp/qps/usage_timer.h"

namespace grpc {
namespace testing {

static std::unique_ptr<BenchmarkService::Stub> BenchmarkStubCreator(
    const std::shared_ptr<Channel>& ch) {
  return BenchmarkService::NewStub(ch);
}

class SynchronousClient
    : public ClientImpl<BenchmarkService::Stub, SimpleRequest> {
 public:
  explicit SynchronousClient(const ClientConfig& config)
      : ClientImpl<BenchmarkService::Stub, SimpleRequest>(
            config, BenchmarkStubCreator) {
    num_threads_ =
        config.outstanding_rpcs_per_channel() * config.client_channels();
    responses_.resize(num_threads_);
    SetupLoadTest(config, num_threads_);
  }

  ~SynchronousClient() override {}

  virtual bool InitThreadFuncImpl(size_t thread_idx) = 0;
  virtual bool ThreadFuncImpl(HistogramEntry* entry, size_t thread_idx) = 0;

  void ThreadFunc(size_t thread_idx, Thread* t) override {
    if (!InitThreadFuncImpl(thread_idx)) {
      return;
    }
    for (;;) {

      HistogramEntry entry;
      const bool thread_still_ok = ThreadFuncImpl(&entry, thread_idx);
      t->UpdateHistogram(&entry);
      if (!thread_still_ok || ThreadCompleted()) {
        return;
      }
    }
  }

 protected:

  bool WaitToIssue(int thread_idx) {
    if (!closed_loop_) {
      const gpr_timespec next_issue_time = NextIssueTime(thread_idx);

      while (true) {
        const gpr_timespec one_sec_delay =
            gpr_time_add(gpr_now(GPR_CLOCK_MONOTONIC),
                         gpr_time_from_seconds(1, GPR_TIMESPAN));
        if (gpr_time_cmp(next_issue_time, one_sec_delay) <= 0) {
          gpr_sleep_until(next_issue_time);
          return true;
        } else {
          gpr_sleep_until(one_sec_delay);
          if (gpr_atm_acq_load(&thread_pool_done_) != gpr_atm{0}) {
            return false;
          }
        }
      }
    }
    return true;
  }

  size_t num_threads_;
  std::vector<SimpleResponse> responses_;
};

class SynchronousUnaryClient final : public SynchronousClient {
 public:
  explicit SynchronousUnaryClient(const ClientConfig& config)
      : SynchronousClient(config) {
    StartThreads(num_threads_);
  }
  ~SynchronousUnaryClient() override {}

  bool InitThreadFuncImpl(size_t ) override { return true; }

  bool ThreadFuncImpl(HistogramEntry* entry, size_t thread_idx) override {
    if (!WaitToIssue(thread_idx)) {
      return true;
    }
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    double start = UsageTimer::Now();
    grpc::ClientContext context;
    grpc::Status s =
        stub->UnaryCall(&context, request_, &responses_[thread_idx]);
    if (s.ok()) {
      entry->set_value((UsageTimer::Now() - start) * 1e9);
    }
    entry->set_status(s.error_code());
    return true;
  }

 private:
  void DestroyMultithreading() final { EndThreads(); }
};

template <class StreamType>
class SynchronousStreamingClient : public SynchronousClient {
 public:
  explicit SynchronousStreamingClient(const ClientConfig& config)
      : SynchronousClient(config),
        context_(num_threads_),
        stream_(num_threads_),
        stream_mu_(num_threads_),
        shutdown_(num_threads_),
        messages_per_stream_(config.messages_per_stream()),
        messages_issued_(num_threads_) {
    StartThreads(num_threads_);
  }
  ~SynchronousStreamingClient() override {
    CleanupAllStreams([this](size_t thread_idx) {

      stream_[thread_idx]->Finish().IgnoreError();
    });
  }

 protected:
  std::vector<grpc::ClientContext> context_;
  std::vector<std::unique_ptr<StreamType>> stream_;

  std::vector<std::mutex> stream_mu_;

  struct Bool {
    bool val;
    Bool() : val(false) {}
  };
  std::vector<Bool> shutdown_;
  const int messages_per_stream_;
  std::vector<int> messages_issued_;

  void FinishStream(HistogramEntry* entry, size_t thread_idx) {
    Status s = stream_[thread_idx]->Finish();

    entry->set_status(s.error_code());
    if (!s.ok()) {
      std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
      if (!shutdown_[thread_idx].val) {
        LOG(ERROR) << "Stream " << thread_idx << " received an error "
                   << s.error_message();
      }
    }

    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    context_[thread_idx].~ClientContext();
    new (&context_[thread_idx]) ClientContext();
  }

  void CleanupAllStreams(const std::function<void(size_t)>& cleaner) {
    std::vector<std::thread> cleanup_threads;
    for (size_t i = 0; i < num_threads_; i++) {
      cleanup_threads.emplace_back([this, i, cleaner] {
        std::lock_guard<std::mutex> l(stream_mu_[i]);
        shutdown_[i].val = true;
        if (stream_[i]) {
          cleaner(i);
        }
      });
    }
    for (auto& th : cleanup_threads) {
      th.join();
    }
  }

 private:
  void DestroyMultithreading() final {
    CleanupAllStreams(
        [this](size_t thread_idx) { context_[thread_idx].TryCancel(); });
    EndThreads();
  }
};

class SynchronousStreamingPingPongClient final
    : public SynchronousStreamingClient<
          grpc::ClientReaderWriter<SimpleRequest, SimpleResponse>> {
 public:
  explicit SynchronousStreamingPingPongClient(const ClientConfig& config)
      : SynchronousStreamingClient(config) {}
  ~SynchronousStreamingPingPongClient() override {
    CleanupAllStreams(
        [this](size_t thread_idx) { stream_[thread_idx]->WritesDone(); });
  }

 private:
  bool InitThreadFuncImpl(size_t thread_idx) override {
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] = stub->StreamingCall(&context_[thread_idx]);
    } else {
      return false;
    }
    messages_issued_[thread_idx] = 0;
    return true;
  }

  bool ThreadFuncImpl(HistogramEntry* entry, size_t thread_idx) override {
    if (!WaitToIssue(thread_idx)) {
      return true;
    }
    double start = UsageTimer::Now();
    if (stream_[thread_idx]->Write(request_) &&
        stream_[thread_idx]->Read(&responses_[thread_idx])) {
      entry->set_value((UsageTimer::Now() - start) * 1e9);

      if ((messages_per_stream_ != 0) &&
          (++messages_issued_[thread_idx] < messages_per_stream_)) {
        return true;
      } else if (messages_per_stream_ == 0) {
        return true;
      } else {

      }
    }
    stream_[thread_idx]->WritesDone();
    FinishStream(entry, thread_idx);
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] = stub->StreamingCall(&context_[thread_idx]);
    } else {
      stream_[thread_idx].reset();
      return false;
    }
    messages_issued_[thread_idx] = 0;
    return true;
  }
};

class SynchronousStreamingFromClientClient final
    : public SynchronousStreamingClient<grpc::ClientWriter<SimpleRequest>> {
 public:
  explicit SynchronousStreamingFromClientClient(const ClientConfig& config)
      : SynchronousStreamingClient(config), last_issue_(num_threads_) {}
  ~SynchronousStreamingFromClientClient() override {
    CleanupAllStreams(
        [this](size_t thread_idx) { stream_[thread_idx]->WritesDone(); });
  }

 private:
  std::vector<double> last_issue_;

  bool InitThreadFuncImpl(size_t thread_idx) override {
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] = stub->StreamingFromClient(&context_[thread_idx],
                                                      &responses_[thread_idx]);
    } else {
      return false;
    }
    last_issue_[thread_idx] = UsageTimer::Now();
    return true;
  }

  bool ThreadFuncImpl(HistogramEntry* entry, size_t thread_idx) override {

    if (!WaitToIssue(thread_idx)) {
      return true;
    }
    if (stream_[thread_idx]->Write(request_)) {
      double now = UsageTimer::Now();
      entry->set_value((now - last_issue_[thread_idx]) * 1e9);
      last_issue_[thread_idx] = now;
      return true;
    }
    stream_[thread_idx]->WritesDone();
    FinishStream(entry, thread_idx);
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] = stub->StreamingFromClient(&context_[thread_idx],
                                                      &responses_[thread_idx]);
    } else {
      stream_[thread_idx].reset();
      return false;
    }
    return true;
  }
};

class SynchronousStreamingFromServerClient final
    : public SynchronousStreamingClient<grpc::ClientReader<SimpleResponse>> {
 public:
  explicit SynchronousStreamingFromServerClient(const ClientConfig& config)
      : SynchronousStreamingClient(config), last_recv_(num_threads_) {}
  ~SynchronousStreamingFromServerClient() override {}

 private:
  std::vector<double> last_recv_;

  bool InitThreadFuncImpl(size_t thread_idx) override {
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] =
          stub->StreamingFromServer(&context_[thread_idx], request_);
    } else {
      return false;
    }
    last_recv_[thread_idx] = UsageTimer::Now();
    return true;
  }

  bool ThreadFuncImpl(HistogramEntry* entry, size_t thread_idx) override {
    if (stream_[thread_idx]->Read(&responses_[thread_idx])) {
      double now = UsageTimer::Now();
      entry->set_value((now - last_recv_[thread_idx]) * 1e9);
      last_recv_[thread_idx] = now;
      return true;
    }
    FinishStream(entry, thread_idx);
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] =
          stub->StreamingFromServer(&context_[thread_idx], request_);
    } else {
      stream_[thread_idx].reset();
      return false;
    }
    return true;
  }
};

class SynchronousStreamingBothWaysClient final
    : public SynchronousStreamingClient<
          grpc::ClientReaderWriter<SimpleRequest, SimpleResponse>> {
 public:
  explicit SynchronousStreamingBothWaysClient(const ClientConfig& config)
      : SynchronousStreamingClient(config) {}
  ~SynchronousStreamingBothWaysClient() override {
    CleanupAllStreams(
        [this](size_t thread_idx) { stream_[thread_idx]->WritesDone(); });
  }

 private:
  bool InitThreadFuncImpl(size_t thread_idx) override {
    auto* stub = channels_[thread_idx % channels_.size()].get_stub();
    std::lock_guard<std::mutex> l(stream_mu_[thread_idx]);
    if (!shutdown_[thread_idx].val) {
      stream_[thread_idx] = stub->StreamingBothWays(&context_[thread_idx]);
    } else {
      return false;
    }
    return true;
  }

  bool ThreadFuncImpl(HistogramEntry* ,
                      size_t ) override {

    return true;
  }
};

std::unique_ptr<Client> CreateSynchronousClient(const ClientConfig& config) {
  CHECK(!config.use_coalesce_api());
  switch (config.rpc_type()) {
    case UNARY:
      return std::unique_ptr<Client>(new SynchronousUnaryClient(config));
    case STREAMING:
      return std::unique_ptr<Client>(
          new SynchronousStreamingPingPongClient(config));
    case STREAMING_FROM_CLIENT:
      return std::unique_ptr<Client>(
          new SynchronousStreamingFromClientClient(config));
    case STREAMING_FROM_SERVER:
      return std::unique_ptr<Client>(
          new SynchronousStreamingFromServerClient(config));
    case STREAMING_BOTH_WAYS:
      return std::unique_ptr<Client>(
          new SynchronousStreamingBothWaysClient(config));
    default:
      assert(false);
      return nullptr;
  }
}

}
}
