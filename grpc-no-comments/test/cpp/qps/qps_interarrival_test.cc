
// Copyright 2015 gRPC authors.

#include <chrono>
#include <iostream>

#include "test/core/test_util/histogram.h"
#include "test/core/test_util/test_config.h"
#include "test/cpp/qps/interarrival.h"
#include "test/cpp/util/test_config.h"

using grpc::testing::InterarrivalTimer;
using grpc::testing::RandomDistInterface;

static void RunTest(RandomDistInterface&& r, int threads,
                    const std::string& title) {
  InterarrivalTimer timer;
  timer.init(r, threads);
  grpc_histogram* h(grpc_histogram_create(0.01, 60e9));

  for (int i = 0; i < 10000000; i++) {
    for (int j = 0; j < threads; j++) {
      grpc_histogram_add(h, timer.next(j));
    }
  }

  std::cout << title << " Distribution" << std::endl;
  std::cout << "Value, Percentile" << std::endl;
  for (double pct = 0.0; pct < 100.0; pct += 1.0) {
    std::cout << grpc_histogram_percentile(h, pct) << "," << pct << std::endl;
  }

  grpc_histogram_destroy(h);
}

using grpc::testing::ExpDist;

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(&argc, argv);
  grpc::testing::InitTest(&argc, &argv, true);

  RunTest(ExpDist(10.0), 5, std::string("Exponential(10)"));
  return 0;
}
