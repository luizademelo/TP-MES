
// Copyright 2015 gRPC authors.

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <signal.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <sstream>

#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/core/test_util/reconnect_server.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(int32_t, control_port, 0, "Server port for controlling the server.");
ABSL_FLAG(int32_t, retry_port, 0,
          "Server port for raw tcp connections. All incoming "
          "connections will be closed immediately.");

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::testing::Empty;
using grpc::testing::ReconnectInfo;
using grpc::testing::ReconnectParams;
using grpc::testing::ReconnectService;

static bool got_sigint = false;

class ReconnectServiceImpl : public ReconnectService::Service {
 public:
  explicit ReconnectServiceImpl(int retry_port)
      : retry_port_(retry_port),
        serving_(false),
        server_started_(false),
        shutdown_(false) {
    reconnect_server_init(&tcp_server_);
  }

  ~ReconnectServiceImpl() override {
    if (server_started_) {
      reconnect_server_destroy(&tcp_server_);
    }
  }

  void Poll(int seconds) { reconnect_server_poll(&tcp_server_, seconds); }

  Status Start(ServerContext* , const ReconnectParams* request,
               Empty* ) override {
    bool start_server = true;
    std::unique_lock<std::mutex> lock(mu_);
    while (serving_ && !shutdown_) {
      cv_.wait(lock);
    }
    if (shutdown_) {
      return Status(grpc::StatusCode::UNAVAILABLE, "shutting down");
    }
    serving_ = true;
    if (server_started_) {
      start_server = false;
    } else {
      tcp_server_.max_reconnect_backoff_ms =
          request->max_reconnect_backoff_ms();
      server_started_ = true;
    }
    lock.unlock();

    if (start_server) {
      reconnect_server_start(&tcp_server_, retry_port_);
    } else {
      reconnect_server_clear_timestamps(&tcp_server_);
    }
    return Status::OK;
  }

  Status Stop(ServerContext* , const Empty* ,
              ReconnectInfo* response) override {

    Verify(response);
    reconnect_server_clear_timestamps(&tcp_server_);
    std::lock_guard<std::mutex> lock(mu_);
    serving_ = false;
    cv_.notify_one();
    return Status::OK;
  }

  void Verify(ReconnectInfo* response) {
    double expected_backoff = 1000.0;
    const double kTransmissionDelay = 100.0;
    const double kBackoffMultiplier = 1.6;
    const double kJitterFactor = 0.2;
    const int kMaxBackoffMs = tcp_server_.max_reconnect_backoff_ms
                                  ? tcp_server_.max_reconnect_backoff_ms
                                  : 120 * 1000;
    bool passed = true;
    for (timestamp_list* cur = tcp_server_.head; cur && cur->next;
         cur = cur->next) {
      double backoff = gpr_time_to_millis(
          gpr_time_sub(cur->next->timestamp, cur->timestamp));
      double min_backoff = expected_backoff * (1 - kJitterFactor);
      double max_backoff = expected_backoff * (1 + kJitterFactor);
      if (backoff < min_backoff - kTransmissionDelay ||
          backoff > max_backoff + kTransmissionDelay) {
        passed = false;
      }
      response->add_backoff_ms(static_cast<int32_t>(backoff));
      expected_backoff *= kBackoffMultiplier;
      expected_backoff =
          expected_backoff > kMaxBackoffMs ? kMaxBackoffMs : expected_backoff;
    }
    response->set_passed(passed);
  }

  void Shutdown() {
    std::lock_guard<std::mutex> lock(mu_);
    shutdown_ = true;
    cv_.notify_all();
  }

 private:
  int retry_port_;
  reconnect_server tcp_server_;
  bool serving_;
  bool server_started_;
  bool shutdown_;
  std::mutex mu_;
  std::condition_variable cv_;
};

void RunServer() {
  std::ostringstream server_address;
  server_address << "0.0.0.0:" << absl::GetFlag(FLAGS_control_port);
  ReconnectServiceImpl service(absl::GetFlag(FLAGS_retry_port));

  ServerBuilder builder;
  builder.RegisterService(&service);
  builder.AddListeningPort(server_address.str(),
                           grpc::InsecureServerCredentials());
  std::unique_ptr<Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_address.str();
  while (!got_sigint) {
    service.Poll(5);
  }
  service.Shutdown();
}

static void sigint_handler(int ) { got_sigint = true; }

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);
  signal(SIGINT, sigint_handler);

  CHECK_NE(absl::GetFlag(FLAGS_control_port), 0);
  CHECK_NE(absl::GetFlag(FLAGS_retry_port), 0);
  RunServer();

  return 0;
}
