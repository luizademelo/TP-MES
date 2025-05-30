
// Copyright 2016 gRPC authors.

#include <grpc/grpc.h>
#include <stdint.h>
#include <string.h>

#include <utility>

#include "absl/log/check.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/slice/percent_encoding.h"
#include "src/core/lib/slice/slice.h"

using fuzztest::Arbitrary;
using fuzztest::ElementOf;
using fuzztest::VectorOf;

namespace grpc_core {
namespace {

void RoundTrips(std::vector<uint8_t> buffer, PercentEncodingType type) {
  auto input = Slice::FromCopiedBuffer(
      reinterpret_cast<const char*>(buffer.data()), buffer.size());
  auto output = PercentEncodeSlice(input.Ref(), type);
  auto permissive_decoded_output =
      PermissivePercentDecodeSlice(std::move(output));

  CHECK(input == permissive_decoded_output);
}
FUZZ_TEST(MyTestSuite, RoundTrips)
    .WithDomains(VectorOf(Arbitrary<uint8_t>()),
                 ElementOf({PercentEncodingType::URL,
                            PercentEncodingType::Compatible}));

void DecodeDoesntCrash(std::vector<uint8_t> buffer) {
  PermissivePercentDecodeSlice(Slice::FromCopiedBuffer(
      reinterpret_cast<const char*>(buffer.data()), buffer.size()));
}
FUZZ_TEST(MyTestSuite, DecodeDoesntCrash)
    .WithDomains(VectorOf(Arbitrary<uint8_t>()));

}
}
