
// Copyright 2015 gRPC authors.

#include "test/cpp/util/metrics_server.h"

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "absl/log/log.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/metrics.grpc.pb.h"
#include "src/proto/grpc/testing/metrics.pb.h"

namespace grpc {
namespace testing {

QpsGauge::QpsGauge()
    : start_time_(gpr_now(GPR_CLOCK_REALTIME)), num_queries_(0) {}

void QpsGauge::Reset() {
  std::lock_guard<std::mutex> lock(num_queries_mu_);
  num_queries_ = 0;
  start_time_ = gpr_now(GPR_CLOCK_REALTIME);
}

void QpsGauge::Incr() {
  std::lock_guard<std::mutex> lock(num_queries_mu_);
  num_queries_++;
}

long QpsGauge::Get() {
  std::lock_guard<std::mutex> lock(num_queries_mu_);
  gpr_timespec time_diff =
      gpr_time_sub(gpr_now(GPR_CLOCK_REALTIME), start_time_);
  long duration_secs = time_diff.tv_sec > 0 ? time_diff.tv_sec : 1;
  return num_queries_ / duration_secs;
}

grpc::Status MetricsServiceImpl::GetAllGauges(
    ServerContext* , const EmptyMessage* ,
    ServerWriter<GaugeResponse>* writer) {
  VLOG(2) << "GetAllGauges called";

  std::lock_guard<std::mutex> lock(mu_);
  for (auto it = qps_gauges_.begin(); it != qps_gauges_.end(); it++) {
    GaugeResponse resp;
    resp.set_name(it->first);
    resp.set_long_value(it->second->Get());
    writer->Write(resp);
  }

  return Status::OK;
}

grpc::Status MetricsServiceImpl::GetGauge(ServerContext* ,
                                          const GaugeRequest* request,
                                          GaugeResponse* response) {
  std::lock_guard<std::mutex> lock(mu_);

  const auto it = qps_gauges_.find(request->name());
  if (it != qps_gauges_.end()) {
    response->set_name(it->first);
    response->set_long_value(it->second->Get());
  }

  return Status::OK;
}

std::shared_ptr<QpsGauge> MetricsServiceImpl::CreateQpsGauge(
    const std::string& name, bool* already_present) {
  std::lock_guard<std::mutex> lock(mu_);

  std::shared_ptr<QpsGauge> qps_gauge(new QpsGauge());
  const auto p = qps_gauges_.insert(std::pair(name, qps_gauge));

  *already_present = !p.second;
  return p.first->second;
}

std::unique_ptr<grpc::Server> MetricsServiceImpl::StartServer(int port) {
  LOG(INFO) << "Building metrics server..";

  const std::string address = "0.0.0.0:" + std::to_string(port);

  ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(this);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Metrics server " << address
            << " started. Ready to receive requests..";

  return server;
}

}
}
