
// Copyright 2017 gRPC authors.

#ifndef GRPC_TEST_CPP_MICROBENCHMARKS_HELPERS_H
#define GRPC_TEST_CPP_MICROBENCHMARKS_HELPERS_H

#include <benchmark/benchmark.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/impl/grpc_library.h>

#include <sstream>
#include <vector>

#include "src/core/telemetry/stats.h"
#include "src/core/telemetry/stats_data.h"

class LibraryInitializer {
 public:
  LibraryInitializer();
  ~LibraryInitializer();

  static LibraryInitializer& get();

 private:
  grpc::internal::GrpcLibrary init_lib_;
};

#endif
