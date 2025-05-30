// Copyright 2023 gRPC authors.

#ifndef SAMPLER_MAIN_H
#define SAMPLER_MAIN_H

#include <cstdint>
#include <string>

namespace grpc_observability {

class ProbabilitySampler final {
 public:
  static ProbabilitySampler& Get();

  bool ShouldSample(const std::string& trace_id);

  void SetThreshold(double probability);

 private:
  ProbabilitySampler() = default;

  uint64_t threshold_;
};

}

#endif
