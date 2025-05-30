
// Copyright 2015 gRPC authors.

#ifndef GRPC_TEST_CPP_UTIL_METRICS_SERVER_H
#define GRPC_TEST_CPP_UTIL_METRICS_SERVER_H

#include <grpcpp/server.h>

#include <map>
#include <mutex>

#include "src/proto/grpc/testing/metrics.grpc.pb.h"
#include "src/proto/grpc/testing/metrics.pb.h"

//    server->Wait(); // Note: This is blocking.

namespace grpc {
namespace testing {

class QpsGauge {
 public:
  QpsGauge();

  void Reset();

  void Incr();

  long Get();

 private:
  gpr_timespec start_time_;
  long num_queries_;
  std::mutex num_queries_mu_;
};

class MetricsServiceImpl final : public MetricsService::Service {
 public:
  grpc::Status GetAllGauges(ServerContext* context, const EmptyMessage* request,
                            ServerWriter<GaugeResponse>* writer) override;

  grpc::Status GetGauge(ServerContext* context, const GaugeRequest* request,
                        GaugeResponse* response) override;

  // NOTE: CreateQpsGauge can be called anytime (i.e before or after calling

  std::shared_ptr<QpsGauge> CreateQpsGauge(const std::string& name,
                                           bool* already_present);

  std::unique_ptr<grpc::Server> StartServer(int port);

 private:
  std::map<string, std::shared_ptr<QpsGauge>> qps_gauges_;
  std::mutex mu_;
};

}
}

#endif
