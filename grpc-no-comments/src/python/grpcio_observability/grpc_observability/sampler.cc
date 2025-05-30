// Copyright 2023 gRPC authors.

#include "sampler.h"

#include <cmath>
#include <cstdint>

#include "absl/strings/escaping.h"

namespace grpc_observability {

namespace {

uint64_t CalculateThreshold(double probability) {
  if (probability <= 0.0) return 0;
  if (probability >= 1.0) return UINT64_MAX;

  const double product = UINT32_MAX * probability;
  double hi_bits, lo_bits = ldexp(modf(product, &hi_bits), 32) + product;
  return (static_cast<uint64_t>(hi_bits) << 32) +
         static_cast<uint64_t>(lo_bits);
}

uint64_t CalculateThresholdFromBuffer(const std::string& trace_id) {
  const std::string trace_id_bytes = absl::HexStringToBytes(trace_id);
  const uint8_t* buf = reinterpret_cast<const uint8_t*>(trace_id_bytes.c_str());
  uint64_t res = 0;
  for (int i = 0; i < 8; ++i) {
    res |= (static_cast<uint64_t>(buf[i]) << (i * 8));
  }
  return res;
}
}

ProbabilitySampler& ProbabilitySampler::Get() {
  static ProbabilitySampler* sampler = new ProbabilitySampler;
  return *sampler;
}

void ProbabilitySampler::SetThreshold(double probability) {
  uint64_t threshold = CalculateThreshold(probability);
  threshold_ = threshold;
}

bool ProbabilitySampler::ShouldSample(const std::string& trace_id) {
  if (threshold_ == 0 || trace_id.length() < 32) return false;

  return CalculateThresholdFromBuffer(trace_id) <= threshold_;
}

}
