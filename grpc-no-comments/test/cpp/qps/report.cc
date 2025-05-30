
// Copyright 2015 gRPC authors.

#include "test/cpp/qps/report.h"

#include <grpcpp/client_context.h>

#include <fstream>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/report_qps_scenario_service.grpc.pb.h"
#include "test/cpp/qps/driver.h"
#include "test/cpp/qps/parse_json.h"
#include "test/cpp/qps/stats.h"

namespace grpc {
namespace testing {

void CompositeReporter::add(std::unique_ptr<Reporter> reporter) {
  reporters_.emplace_back(std::move(reporter));
}

void CompositeReporter::ReportQPS(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportQPS(result);
  }
}

void CompositeReporter::ReportQPSPerCore(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportQPSPerCore(result);
  }
}

void CompositeReporter::ReportLatency(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportLatency(result);
  }
}

void CompositeReporter::ReportTimes(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportTimes(result);
  }
}

void CompositeReporter::ReportCpuUsage(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportCpuUsage(result);
  }
}

void CompositeReporter::ReportPollCount(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportPollCount(result);
  }
}

void CompositeReporter::ReportQueriesPerCpuSec(const ScenarioResult& result) {
  for (size_t i = 0; i < reporters_.size(); ++i) {
    reporters_[i]->ReportQueriesPerCpuSec(result);
  }
}

void GprLogReporter::ReportQPS(const ScenarioResult& result) {
  LOG(INFO) << "QPS: " << result.summary().qps();
  if (result.summary().failed_requests_per_second() > 0) {
    LOG(INFO) << "failed requests/second: "
              << result.summary().failed_requests_per_second();
    LOG(INFO) << "successful requests/second: "
              << result.summary().successful_requests_per_second();
  }
}

void GprLogReporter::ReportQPSPerCore(const ScenarioResult& result) {
  LOG(INFO) << "QPS: " << result.summary().qps() << " ("
            << result.summary().qps_per_server_core() << "/server core)";
}

void GprLogReporter::ReportLatency(const ScenarioResult& result) {
  LOG(INFO) << "Latencies (50/90/95/99/99.9%-ile): "
            << result.summary().latency_50() / 1000 << "/"
            << result.summary().latency_90() / 1000 << "/"
            << result.summary().latency_95() / 1000 << "/"
            << result.summary().latency_99() / 1000 << "/"
            << result.summary().latency_999() / 1000 << " us";
}

void GprLogReporter::ReportTimes(const ScenarioResult& result) {
  LOG(INFO) << "Server system time: " << result.summary().server_system_time();
  LOG(INFO) << "Server user time:   " << result.summary().server_user_time();
  LOG(INFO) << "Client system time: " << result.summary().client_system_time();
  LOG(INFO) << "Client user time:   " << result.summary().client_user_time();
}

void GprLogReporter::ReportCpuUsage(const ScenarioResult& result) {
  LOG(INFO) << "Server CPU usage: " << result.summary().server_cpu_usage();
}

void GprLogReporter::ReportPollCount(const ScenarioResult& result) {
  LOG(INFO) << "Client Polls per Request: "
            << result.summary().client_polls_per_request();
  LOG(INFO) << "Server Polls per Request: "
            << result.summary().server_polls_per_request();
}

void GprLogReporter::ReportQueriesPerCpuSec(const ScenarioResult& result) {
  LOG(INFO) << "Server Queries/CPU-sec: "
            << result.summary().server_queries_per_cpu_sec();
  LOG(INFO) << "Client Queries/CPU-sec: "
            << result.summary().client_queries_per_cpu_sec();
}

void JsonReporter::ReportQPS(const ScenarioResult& result) {
  std::string json_string =
      SerializeJson(result, "type.googleapis.com/grpc.testing.ScenarioResult");
  std::ofstream output_file(report_file_);
  output_file << json_string;
  output_file.close();
}

void JsonReporter::ReportQPSPerCore(const ScenarioResult& ) {

}

void JsonReporter::ReportLatency(const ScenarioResult& ) {

}

void JsonReporter::ReportTimes(const ScenarioResult& ) {

}

void JsonReporter::ReportCpuUsage(const ScenarioResult& ) {

}

void JsonReporter::ReportPollCount(const ScenarioResult& ) {

}

void JsonReporter::ReportQueriesPerCpuSec(const ScenarioResult& ) {

}

void RpcReporter::ReportQPS(const ScenarioResult& result) {
  grpc::ClientContext context;
  grpc::Status status;
  Void phony;

  LOG(INFO) << "RPC reporter sending scenario result to server";
  status = stub_->ReportScenario(&context, result, &phony);

  if (status.ok()) {
    LOG(INFO) << "RpcReporter report RPC success!";
  } else {
    LOG(ERROR) << "RpcReporter report RPC: code: " << status.error_code()
               << ". message: " << status.error_message();
  }
}

void RpcReporter::ReportQPSPerCore(const ScenarioResult& ) {

}

void RpcReporter::ReportLatency(const ScenarioResult& ) {

}

void RpcReporter::ReportTimes(const ScenarioResult& ) {

}

void RpcReporter::ReportCpuUsage(const ScenarioResult& ) {

}

void RpcReporter::ReportPollCount(const ScenarioResult& ) {

}

void RpcReporter::ReportQueriesPerCpuSec(const ScenarioResult& ) {

}

}
}
