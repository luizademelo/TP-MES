
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_QPS_REPORT_H
#define GRPC_TEST_CPP_QPS_REPORT_H

#include <grpcpp/channel.h>
#include <grpcpp/support/config.h>

#include <memory>
#include <set>
#include <vector>

#include "src/proto/grpc/testing/report_qps_scenario_service.grpc.pb.h"
#include "test/cpp/qps/driver.h"

namespace grpc {
namespace testing {

class Reporter {
 public:

  explicit Reporter(const string& name) : name_(name) {}

  virtual ~Reporter() {}

  string name() const { return name_; }

  virtual void ReportQPS(const ScenarioResult& result) = 0;

  virtual void ReportQPSPerCore(const ScenarioResult& result) = 0;

  virtual void ReportLatency(const ScenarioResult& result) = 0;

  virtual void ReportTimes(const ScenarioResult& result) = 0;

  virtual void ReportCpuUsage(const ScenarioResult& result) = 0;

  virtual void ReportPollCount(const ScenarioResult& result) = 0;

  virtual void ReportQueriesPerCpuSec(const ScenarioResult& result) = 0;

 private:
  const string name_;
};

class CompositeReporter : public Reporter {
 public:
  CompositeReporter() : Reporter("CompositeReporter") {}

  void add(std::unique_ptr<Reporter> reporter);

  void ReportQPS(const ScenarioResult& result) override;
  void ReportQPSPerCore(const ScenarioResult& result) override;
  void ReportLatency(const ScenarioResult& result) override;
  void ReportTimes(const ScenarioResult& result) override;
  void ReportCpuUsage(const ScenarioResult& result) override;
  void ReportPollCount(const ScenarioResult& result) override;
  void ReportQueriesPerCpuSec(const ScenarioResult& result) override;

 private:
  std::vector<std::unique_ptr<Reporter> > reporters_;
};

class GprLogReporter : public Reporter {
 public:
  explicit GprLogReporter(const string& name) : Reporter(name) {}

 private:
  void ReportQPS(const ScenarioResult& result) override;
  void ReportQPSPerCore(const ScenarioResult& result) override;
  void ReportLatency(const ScenarioResult& result) override;
  void ReportTimes(const ScenarioResult& result) override;
  void ReportCpuUsage(const ScenarioResult& result) override;
  void ReportPollCount(const ScenarioResult& result) override;
  void ReportQueriesPerCpuSec(const ScenarioResult& result) override;
};

class JsonReporter : public Reporter {
 public:
  JsonReporter(const string& name, const string& report_file)
      : Reporter(name), report_file_(report_file) {}

 private:
  void ReportQPS(const ScenarioResult& result) override;
  void ReportQPSPerCore(const ScenarioResult& result) override;
  void ReportLatency(const ScenarioResult& result) override;
  void ReportTimes(const ScenarioResult& result) override;
  void ReportCpuUsage(const ScenarioResult& result) override;
  void ReportPollCount(const ScenarioResult& result) override;
  void ReportQueriesPerCpuSec(const ScenarioResult& result) override;

  const string report_file_;
};

class RpcReporter : public Reporter {
 public:
  RpcReporter(const string& name, const std::shared_ptr<grpc::Channel>& channel)
      : Reporter(name), stub_(ReportQpsScenarioService::NewStub(channel)) {}

 private:
  void ReportQPS(const ScenarioResult& result) override;
  void ReportQPSPerCore(const ScenarioResult& result) override;
  void ReportLatency(const ScenarioResult& result) override;
  void ReportTimes(const ScenarioResult& result) override;
  void ReportCpuUsage(const ScenarioResult& result) override;
  void ReportPollCount(const ScenarioResult& result) override;
  void ReportQueriesPerCpuSec(const ScenarioResult& result) override;

  std::unique_ptr<ReportQpsScenarioService::Stub> stub_;
};

}
}

#endif
