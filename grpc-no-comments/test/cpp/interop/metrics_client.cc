
// Copyright 2015 gRPC authors.

#include <grpcpp/grpcpp.h>

#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "src/core/util/crash.h"
#include "src/proto/grpc/testing/metrics.grpc.pb.h"
#include "src/proto/grpc/testing/metrics.pb.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/util/metrics_server.h"
#include "test/cpp/util/test_config.h"

int kDeadlineSecs = 10;

ABSL_FLAG(std::string, metrics_server_address, "localhost:8081",
          "The metrics server addresses in the format <hostname>:<port>");

ABSL_FLAG(int32_t, deadline_secs, kDeadlineSecs,
          "The deadline (in seconds) for RCP call");
ABSL_FLAG(bool, total_only, false,
          "If true, this prints only the total value of all gauges");

using grpc::testing::EmptyMessage;
using grpc::testing::GaugeResponse;
using grpc::testing::MetricsService;

bool PrintMetrics(std::unique_ptr<MetricsService::Stub> stub, bool total_only,
                  int deadline_secs) {
  grpc::ClientContext context;
  EmptyMessage message;

  std::chrono::system_clock::time_point deadline =
      std::chrono::system_clock::now() + std::chrono::seconds(deadline_secs);

  context.set_deadline(deadline);

  std::unique_ptr<grpc::ClientReader<GaugeResponse>> reader(
      stub->GetAllGauges(&context, message));

  GaugeResponse gauge_response;
  long overall_qps = 0;
  while (reader->Read(&gauge_response)) {
    if (gauge_response.value_case() == GaugeResponse::kLongValue) {
      if (!total_only) {
        std::cout << gauge_response.name() << ": "
                  << gauge_response.long_value() << std::endl;
      }
      overall_qps += gauge_response.long_value();
    } else {
      std::cout << "Gauge '" << gauge_response.name() << "' is not long valued"
                << std::endl;
    }
  }

  std::cout << overall_qps << std::endl;

  const grpc::Status status = reader->Finish();
  if (!status.ok()) {
    std::cout << "Error in getting metrics from the client" << std::endl;
  }

  return status.ok();
}

int main(int argc, char** argv) {
  grpc::testing::InitTest(&argc, &argv, true);

  grpc_disable_all_absl_logs();

  std::shared_ptr<grpc::Channel> channel(
      grpc::CreateChannel(absl::GetFlag(FLAGS_metrics_server_address),
                          grpc::InsecureChannelCredentials()));

  if (!PrintMetrics(MetricsService::NewStub(channel),
                    absl::GetFlag(FLAGS_total_only),
                    absl::GetFlag(FLAGS_deadline_secs))) {
    return 1;
  }

  return 0;
}
