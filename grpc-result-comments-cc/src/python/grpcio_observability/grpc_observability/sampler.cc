Here's the commented version of the code:

```c++
// Copyright 2023 gRPC authors.

#include "sampler.h"

#include <cmath>
#include <cstdint>

#include "absl/strings/escaping.h"

namespace grpc_observability {

namespace {

// Calculates a sampling threshold based on given probability
// Args:
//   probability: sampling probability between 0.0 and 1.0
// Returns:
//   - 0 if probability <= 0.0
//   - UINT64_MAX if probability >= 1.0
//   - Otherwise, returns a 64-bit threshold value calculated by:
//       1. Multiplying UINT32_MAX with the probability
//       2. Splitting the product into high and low 32-bit parts
//       3. Combining them into a 64-bit threshold
uint64_t CalculateThreshold(double probability) {
  if (probability <= 0.0) return 0;
  if (probability >= 1.0) return UINT64_MAX;

  const double product = UINT32_MAX * probability;
  double hi_bits, lo_bits = ldexp(modf(product, &hi_bits), 32) + product;
  return (static_cast<uint64_t>(hi_bits) << 32) +
         static_cast<uint64_t>(lo_bits);
}

// Converts a trace ID string into a 64-bit threshold value
// Args:
//   trace_id: hexadecimal string representing the trace ID
// Returns:
//   64-bit value formed by:
//     1. Converting hex string to bytes
//     2. Taking first 8 bytes
//     3. Combining them into a 64-bit integer (little-endian)
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

// Returns the singleton instance of ProbabilitySampler
// Note: Uses Meyer's singleton pattern for thread-safe initialization
ProbabilitySampler& ProbabilitySampler::Get() {
  static ProbabilitySampler* sampler = new ProbabilitySampler;
  return *sampler;
}

// Sets the sampling threshold based on given probability
// Args:
//   probability: sampling probability between 0.0 and 1.0
void ProbabilitySampler::SetThreshold(double probability) {
  uint64_t threshold = CalculateThreshold(probability);
  threshold_ = threshold;
}

// Determines whether a trace should be sampled based on its ID
// Args:
//   trace_id: hexadecimal string representing the trace ID
// Returns:
//   false if:
//     - threshold is 0 (sampling disabled)
//     - trace_id is too short (<32 chars)
//   true if the calculated trace ID value <= current threshold
bool ProbabilitySampler::ShouldSample(const std::string& trace_id) {
  if (threshold_ == 0 || trace_id.length() < 32) return false;

  return CalculateThresholdFromBuffer(trace_id) <= threshold_;
}

}
```