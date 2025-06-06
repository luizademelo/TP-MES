
// Copyright 2020 gRPC authors.

#include <grpcpp/ext/admin_services.h>
#include <grpcpp/ext/csm_observability.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "absl/algorithm/container.h"
#include "absl/flags/flag.h"
#include "absl/log/check.h"
#include "absl/log/log.h"
#include "absl/strings/str_split.h"
#include "opentelemetry/exporters/prometheus/exporter_factory.h"
#include "opentelemetry/exporters/prometheus/exporter_options.h"
#include "opentelemetry/sdk/metrics/meter_provider.h"
#include "src/core/call/status_util.h"
#include "src/core/util/env.h"
#include "src/proto/grpc/testing/empty.pb.h"
#include "src/proto/grpc/testing/messages.pb.h"
#include "src/proto/grpc/testing/test.grpc.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/interop/rpc_behavior_lb_policy.h"
#include "test/cpp/interop/xds_stats_watcher.h"
#include "test/cpp/util/test_config.h"

ABSL_FLAG(bool, fail_on_failed_rpc, false,
          "Fail client if any RPCs fail after first successful RPC.");
ABSL_FLAG(int32_t, num_channels, 1, "Number of channels.");
ABSL_FLAG(bool, print_response, false, "Write RPC response to stdout.");
ABSL_FLAG(int32_t, qps, 1, "Qps per channel.");

ABSL_FLAG(int32_t, rpc_timeout_sec, 30, "Per RPC timeout seconds.");
ABSL_FLAG(std::string, server, "localhost:50051", "Address of server.");
ABSL_FLAG(int32_t, stats_port, 50052,
          "Port to expose peer distribution stats service.");
ABSL_FLAG(std::string, rpc, "UnaryCall",
          "a comma separated list of rpc methods.");
ABSL_FLAG(int32_t, request_payload_size, 0,
          "Set the SimpleRequest.payload.body to a string of repeated 0 (zero) "
          "ASCII characters of the given size in bytes.");
ABSL_FLAG(int32_t, response_payload_size, 0,
          "Ask the server to respond with SimpleResponse.payload.body of the "
          "given length (may not be implemented on the server).");
ABSL_FLAG(std::string, metadata, "", "metadata to send with the RPC.");
ABSL_FLAG(std::string, expect_status, "OK",
          "RPC status for the test RPC to be considered successful");
ABSL_FLAG(
    bool, secure_mode, false,
    "If true, XdsCredentials are used, InsecureChannelCredentials otherwise");
ABSL_FLAG(bool, enable_csm_observability, false,
          "Whether to enable CSM Observability");
ABSL_FLAG(bool, log_rpc_start_and_end, false,
          "Whether to log when RPCs start and end.");

using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::testing::AsyncClientCallResult;
using grpc::testing::ClientConfigureRequest;
using grpc::testing::ClientConfigureResponse;
using grpc::testing::Empty;
using grpc::testing::LoadBalancerAccumulatedStatsRequest;
using grpc::testing::LoadBalancerAccumulatedStatsResponse;
using grpc::testing::LoadBalancerStatsRequest;
using grpc::testing::LoadBalancerStatsResponse;
using grpc::testing::LoadBalancerStatsService;
using grpc::testing::SimpleRequest;
using grpc::testing::SimpleResponse;
using grpc::testing::StatsWatchers;
using grpc::testing::TestService;
using grpc::testing::XdsStatsWatcher;
using grpc::testing::XdsUpdateClientConfigureService;

struct AsyncClientCall {
  ClientContext context;
  std::unique_ptr<ClientAsyncResponseReader<Empty>> empty_response_reader;
  std::unique_ptr<ClientAsyncResponseReader<SimpleResponse>>
      simple_response_reader;

  AsyncClientCallResult result;
};

std::atomic<bool> one_rpc_succeeded(false);

struct RpcConfig {
  ClientConfigureRequest::RpcType type;
  std::vector<std::pair<std::string, std::string>> metadata;
  int timeout_sec = 0;
  std::string request_payload;
  int request_payload_size = 0;
  int response_payload_size = 0;
};
struct RpcConfigurationsQueue {

  std::deque<std::vector<RpcConfig>> rpc_configs_queue;

  std::mutex mu_rpc_configs_queue;
};

class TestClient {
 public:
  TestClient(const std::shared_ptr<Channel>& channel,
             StatsWatchers* stats_watchers)
      : stub_(TestService::NewStub(channel)), stats_watchers_(stats_watchers) {}

  void AsyncUnaryCall(const RpcConfig& config) {
    SimpleResponse response;
    int saved_request_id;
    {
      std::lock_guard<std::mutex> lock(stats_watchers_->mu);
      saved_request_id = ++stats_watchers_->global_request_id;
      ++stats_watchers_
            ->global_request_id_by_type[ClientConfigureRequest::UNARY_CALL];
    }
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() +
        std::chrono::seconds(config.timeout_sec != 0
                                 ? config.timeout_sec
                                 : absl::GetFlag(FLAGS_rpc_timeout_sec));
    AsyncClientCall* call = new AsyncClientCall;
    if (absl::GetFlag(FLAGS_log_rpc_start_and_end)) {
      LOG(INFO) << "starting async unary call " << static_cast<void*>(call);
    }
    for (const auto& data : config.metadata) {
      call->context.AddMetadata(data.first, data.second);
    }
    SimpleRequest request;
    request.set_response_size(config.response_payload_size);
    if (config.request_payload_size > 0) {
      request.mutable_payload()->set_body(config.request_payload.c_str(),
                                          config.request_payload_size);
    }
    call->context.set_deadline(deadline);
    call->result.saved_request_id = saved_request_id;
    call->result.rpc_type = ClientConfigureRequest::UNARY_CALL;
    call->simple_response_reader =
        stub_->PrepareAsyncUnaryCall(&call->context, request, &cq_);
    call->simple_response_reader->StartCall();
    call->simple_response_reader->Finish(&call->result.simple_response,
                                         &call->result.status, call);
  }

  void AsyncEmptyCall(const RpcConfig& config) {
    Empty response;
    int saved_request_id;
    {
      std::lock_guard<std::mutex> lock(stats_watchers_->mu);
      saved_request_id = ++stats_watchers_->global_request_id;
      ++stats_watchers_
            ->global_request_id_by_type[ClientConfigureRequest::EMPTY_CALL];
    }
    std::chrono::system_clock::time_point deadline =
        std::chrono::system_clock::now() +
        std::chrono::seconds(config.timeout_sec != 0
                                 ? config.timeout_sec
                                 : absl::GetFlag(FLAGS_rpc_timeout_sec));
    AsyncClientCall* call = new AsyncClientCall;
    if (absl::GetFlag(FLAGS_log_rpc_start_and_end)) {
      LOG(INFO) << "starting async empty call " << static_cast<void*>(call);
    }
    for (const auto& data : config.metadata) {
      call->context.AddMetadata(data.first, data.second);
    }
    call->context.set_deadline(deadline);
    call->result.saved_request_id = saved_request_id;
    call->result.rpc_type = ClientConfigureRequest::EMPTY_CALL;
    call->empty_response_reader = stub_->PrepareAsyncEmptyCall(
        &call->context, Empty::default_instance(), &cq_);
    call->empty_response_reader->StartCall();
    call->empty_response_reader->Finish(&call->result.empty_response,
                                        &call->result.status, call);
  }

  void AsyncCompleteRpc() {
    void* got_tag;
    bool ok = false;
    while (cq_.Next(&got_tag, &ok)) {
      AsyncClientCall* call = static_cast<AsyncClientCall*>(got_tag);
      CHECK(ok);
      if (absl::GetFlag(FLAGS_log_rpc_start_and_end)) {
        LOG(INFO) << "completed async call " << static_cast<void*>(call);
      }
      {
        std::lock_guard<std::mutex> lock(stats_watchers_->mu);
        auto server_initial_metadata = call->context.GetServerInitialMetadata();
        auto metadata_hostname =
            call->context.GetServerInitialMetadata().find("hostname");
        std::string hostname =
            metadata_hostname != call->context.GetServerInitialMetadata().end()
                ? std::string(metadata_hostname->second.data(),
                              metadata_hostname->second.length())
                : call->result.simple_response.hostname();
        for (auto watcher : stats_watchers_->watchers) {
          watcher->RpcCompleted(call->result, hostname,
                                call->context.GetServerInitialMetadata(),
                                call->context.GetServerTrailingMetadata());
        }
      }

      if (!RpcStatusCheckSuccess(call)) {
        if (absl::GetFlag(FLAGS_print_response) ||
            absl::GetFlag(FLAGS_fail_on_failed_rpc)) {
          std::cout << "RPC failed: " << call->result.status.error_code()
                    << ": " << call->result.status.error_message() << std::endl;
        }
        if (absl::GetFlag(FLAGS_fail_on_failed_rpc) &&
            one_rpc_succeeded.load()) {
          abort();
        }
      } else {
        if (absl::GetFlag(FLAGS_print_response)) {
          auto metadata_hostname =
              call->context.GetServerInitialMetadata().find("hostname");
          std::string hostname =
              metadata_hostname !=
                      call->context.GetServerInitialMetadata().end()
                  ? std::string(metadata_hostname->second.data(),
                                metadata_hostname->second.length())
                  : call->result.simple_response.hostname();
          std::cout << "Greeting: Hello world, this is " << hostname
                    << ", from " << call->context.peer() << std::endl;
        }
        one_rpc_succeeded = true;
      }

      delete call;
    }
  }

 private:
  static bool RpcStatusCheckSuccess(AsyncClientCall* call) {

    grpc_status_code code;
    CHECK(grpc_status_code_from_string(
        absl::GetFlag(FLAGS_expect_status).c_str(), &code));
    return code ==
           static_cast<grpc_status_code>(call->result.status.error_code());
  }

  std::unique_ptr<TestService::Stub> stub_;
  StatsWatchers* stats_watchers_;
  CompletionQueue cq_;
};

class LoadBalancerStatsServiceImpl : public LoadBalancerStatsService::Service {
 public:
  explicit LoadBalancerStatsServiceImpl(StatsWatchers* stats_watchers)
      : stats_watchers_(stats_watchers) {}

  Status GetClientStats(ServerContext* ,
                        const LoadBalancerStatsRequest* request,
                        LoadBalancerStatsResponse* response) override {
    int start_id;
    int end_id;
    std::unique_ptr<XdsStatsWatcher> watcher;
    {
      std::lock_guard<std::mutex> lock(stats_watchers_->mu);
      start_id = stats_watchers_->global_request_id + 1;
      end_id = start_id + request->num_rpcs();
      watcher = std::make_unique<XdsStatsWatcher>(
          start_id, end_id,
          std::vector<std::string>(request->metadata_keys().begin(),
                                   request->metadata_keys().end()));
      stats_watchers_->watchers.insert(watcher.get());
    }
    *response = watcher->WaitForRpcStatsResponse(request->timeout_sec());
    {
      std::lock_guard<std::mutex> lock(stats_watchers_->mu);
      stats_watchers_->watchers.erase(watcher.get());
    }
    return Status::OK;
  }

  Status GetClientAccumulatedStats(
      ServerContext* ,
      const LoadBalancerAccumulatedStatsRequest* ,
      LoadBalancerAccumulatedStatsResponse* response) override {
    std::lock_guard<std::mutex> lock(stats_watchers_->mu);
    stats_watchers_->global_watcher->GetCurrentRpcStats(response,
                                                        stats_watchers_);
    return Status::OK;
  }

 private:
  StatsWatchers* stats_watchers_;
};

class XdsUpdateClientConfigureServiceImpl
    : public XdsUpdateClientConfigureService::Service {
 public:
  explicit XdsUpdateClientConfigureServiceImpl(
      RpcConfigurationsQueue* rpc_configs_queue)
      : rpc_configs_queue_(rpc_configs_queue) {}

  Status Configure(ServerContext* ,
                   const ClientConfigureRequest* request,
                   ClientConfigureResponse* ) override {
    std::map<int, std::vector<std::pair<std::string, std::string>>>
        metadata_map;
    for (const auto& data : request->metadata()) {
      metadata_map[data.type()].push_back({data.key(), data.value()});
    }
    std::vector<RpcConfig> configs;
    int request_payload_size = absl::GetFlag(FLAGS_request_payload_size);
    int response_payload_size = absl::GetFlag(FLAGS_response_payload_size);
    CHECK_GE(request_payload_size, 0);
    CHECK_GE(response_payload_size, 0);
    for (const auto& rpc : request->types()) {
      RpcConfig config;
      config.timeout_sec = request->timeout_sec();
      config.type = static_cast<ClientConfigureRequest::RpcType>(rpc);
      auto metadata_iter = metadata_map.find(rpc);
      if (metadata_iter != metadata_map.end()) {
        config.metadata = metadata_iter->second;
      }
      if (request_payload_size > 0 &&
          config.type == ClientConfigureRequest::EMPTY_CALL) {
        LOG(ERROR) << "request_payload_size should not be set for EMPTY_CALL";
      }
      if (response_payload_size > 0 &&
          config.type == ClientConfigureRequest::EMPTY_CALL) {
        LOG(ERROR) << "response_payload_size should not be set for EMPTY_CALL";
      }
      config.request_payload_size = request_payload_size;
      std::string payload(config.request_payload_size, '0');
      config.request_payload = payload;
      config.response_payload_size = response_payload_size;
      configs.push_back(std::move(config));
    }
    {
      std::lock_guard<std::mutex> lock(
          rpc_configs_queue_->mu_rpc_configs_queue);
      rpc_configs_queue_->rpc_configs_queue.emplace_back(std::move(configs));
    }
    return Status::OK;
  }

 private:
  RpcConfigurationsQueue* rpc_configs_queue_;
};

void RunTestLoop(std::chrono::duration<double> duration_per_query,
                 StatsWatchers* stats_watchers,
                 RpcConfigurationsQueue* rpc_configs_queue) {
  grpc::ChannelArguments channel_args;
  channel_args.SetInt(GRPC_ARG_ENABLE_RETRIES, 1);
  TestClient client(
      grpc::CreateCustomChannel(
          absl::GetFlag(FLAGS_server),
          absl::GetFlag(FLAGS_secure_mode)
              ? grpc::XdsCredentials(grpc::InsecureChannelCredentials())
              : grpc::InsecureChannelCredentials(),
          channel_args),
      stats_watchers);
  std::chrono::time_point<std::chrono::system_clock> start =
      std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed;

  std::thread thread = std::thread(&TestClient::AsyncCompleteRpc, &client);

  std::vector<RpcConfig> configs;
  while (true) {
    {
      std::lock_guard<std::mutex> lock(rpc_configs_queue->mu_rpc_configs_queue);
      if (!rpc_configs_queue->rpc_configs_queue.empty()) {
        configs = std::move(rpc_configs_queue->rpc_configs_queue.front());
        rpc_configs_queue->rpc_configs_queue.pop_front();
      }
    }

    elapsed = std::chrono::system_clock::now() - start;
    if (elapsed > duration_per_query) {
      start = std::chrono::system_clock::now();
      for (const auto& config : configs) {
        if (config.type == ClientConfigureRequest::EMPTY_CALL) {
          client.AsyncEmptyCall(config);
        } else if (config.type == ClientConfigureRequest::UNARY_CALL) {
          client.AsyncUnaryCall(config);
        } else {
          CHECK(0);
        }
      }
    }
  }
  GPR_UNREACHABLE_CODE(thread.join());
}

grpc::CsmObservability EnableCsmObservability() {
  VLOG(2) << "Registering Prometheus exporter";
  opentelemetry::exporter::metrics::PrometheusExporterOptions opts;

  opts.url = "0.0.0.0:9464";
  opts.without_otel_scope = false;
  auto prometheus_exporter =
      opentelemetry::exporter::metrics::PrometheusExporterFactory::Create(opts);
  auto meter_provider =
      std::make_shared<opentelemetry::sdk::metrics::MeterProvider>();
  meter_provider->AddMetricReader(std::move(prometheus_exporter));
  auto observability = grpc::CsmObservabilityBuilder()
                           .SetMeterProvider(std::move(meter_provider))
                           .BuildAndRegister();
  assert(observability.ok());
  return *std::move(observability);
}

void RunServer(const int port, StatsWatchers* stats_watchers,
               RpcConfigurationsQueue* rpc_configs_queue) {
  CHECK_NE(port, 0);
  std::ostringstream server_address;
  server_address << "0.0.0.0:" << port;

  LoadBalancerStatsServiceImpl stats_service(stats_watchers);
  XdsUpdateClientConfigureServiceImpl client_config_service(rpc_configs_queue);

  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  builder.RegisterService(&stats_service);
  builder.RegisterService(&client_config_service);
  grpc::AddAdminServices(&builder);
  builder.AddListeningPort(server_address.str(),
                           grpc::InsecureServerCredentials());
  std::unique_ptr<Server> server(builder.BuildAndStart());
  VLOG(2) << "Server listening on " << server_address.str();

  server->Wait();
}

void BuildRpcConfigsFromFlags(RpcConfigurationsQueue* rpc_configs_queue) {

  std::vector<std::string> rpc_metadata =
      absl::StrSplit(absl::GetFlag(FLAGS_metadata), ',', absl::SkipEmpty());
  std::map<int, std::vector<std::pair<std::string, std::string>>> metadata_map;
  for (auto& data : rpc_metadata) {
    std::vector<std::string> metadata =
        absl::StrSplit(data, ':', absl::SkipEmpty());
    CHECK_EQ(metadata.size(), 3u);
    if (metadata[0] == "EmptyCall") {
      metadata_map[ClientConfigureRequest::EMPTY_CALL].push_back(
          {metadata[1], metadata[2]});
    } else if (metadata[0] == "UnaryCall") {
      metadata_map[ClientConfigureRequest::UNARY_CALL].push_back(
          {metadata[1], metadata[2]});
    } else {
      CHECK(0);
    }
  }
  std::vector<RpcConfig> configs;
  std::vector<std::string> rpc_methods =
      absl::StrSplit(absl::GetFlag(FLAGS_rpc), ',', absl::SkipEmpty());
  int request_payload_size = absl::GetFlag(FLAGS_request_payload_size);
  int response_payload_size = absl::GetFlag(FLAGS_response_payload_size);
  CHECK_GE(request_payload_size, 0);
  CHECK_GE(response_payload_size, 0);
  for (const std::string& rpc_method : rpc_methods) {
    RpcConfig config;
    if (rpc_method == "EmptyCall") {
      config.type = ClientConfigureRequest::EMPTY_CALL;
    } else if (rpc_method == "UnaryCall") {
      config.type = ClientConfigureRequest::UNARY_CALL;
    } else {
      CHECK(0);
    }
    auto metadata_iter = metadata_map.find(config.type);
    if (metadata_iter != metadata_map.end()) {
      config.metadata = metadata_iter->second;
    }
    if (request_payload_size > 0 &&
        config.type == ClientConfigureRequest::EMPTY_CALL) {
      LOG(ERROR) << "request_payload_size should not be set for EMPTY_CALL";
    }
    if (response_payload_size > 0 &&
        config.type == ClientConfigureRequest::EMPTY_CALL) {
      LOG(ERROR) << "response_payload_size should not be set for EMPTY_CALL";
    }
    config.request_payload_size = request_payload_size;
    std::string payload(config.request_payload_size, '0');
    config.request_payload = payload;
    config.response_payload_size = response_payload_size;
    configs.push_back(std::move(config));
  }
  {
    std::lock_guard<std::mutex> lock(rpc_configs_queue->mu_rpc_configs_queue);
    rpc_configs_queue->rpc_configs_queue.emplace_back(std::move(configs));
  }
}

int main(int argc, char** argv) {
  grpc_core::CoreConfiguration::RegisterEphemeralBuilder(
      grpc::testing::RegisterRpcBehaviorLbPolicy);
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);

  grpc_status_code code;
  CHECK(grpc_status_code_from_string(absl::GetFlag(FLAGS_expect_status).c_str(),
                                     &code));
  StatsWatchers stats_watchers;
  RpcConfigurationsQueue rpc_config_queue;

  {
    std::lock_guard<std::mutex> lock(stats_watchers.mu);
    stats_watchers.global_watcher = new XdsStatsWatcher(0, 0, {});
    stats_watchers.watchers.insert(stats_watchers.global_watcher);
  }

  BuildRpcConfigsFromFlags(&rpc_config_queue);
  grpc::CsmObservability observability;
  if (absl::GetFlag(FLAGS_enable_csm_observability)) {
    observability = EnableCsmObservability();
  }

  std::chrono::duration<double> duration_per_query =
      std::chrono::nanoseconds(std::chrono::seconds(1)) /
      absl::GetFlag(FLAGS_qps);

  std::vector<std::thread> test_threads;
  test_threads.reserve(absl::GetFlag(FLAGS_num_channels));
  for (int i = 0; i < absl::GetFlag(FLAGS_num_channels); i++) {
    test_threads.emplace_back(std::thread(&RunTestLoop, duration_per_query,
                                          &stats_watchers, &rpc_config_queue));
  }

  RunServer(absl::GetFlag(FLAGS_stats_port), &stats_watchers,
            &rpc_config_queue);

  for (auto it = test_threads.begin(); it != test_threads.end(); it++) {
    it->join();
  }

  return 0;
}
