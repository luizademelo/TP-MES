// Copyright 2025 gRPC authors.

#include <grpc/event_engine/event_engine.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/event_engine/tcp_socket_utils.h"
#include "src/core/util/uri.h"

using fuzztest::Arbitrary;
using fuzztest::VectorOf;
using grpc_event_engine::experimental::EventEngine;
using grpc_event_engine::experimental::ResolvedAddressToURI;

void CheckUriIsParseable(std::vector<uint8_t> buffer) {
  EventEngine::ResolvedAddress address(
      reinterpret_cast<sockaddr*>(buffer.data()), buffer.size());
  absl::StatusOr<std::string> uri = ResolvedAddressToURI(address);
  if (!uri.ok()) return;
  absl::StatusOr<grpc_core::URI> parsed_uri =
      grpc_core::URI::Parse(uri.value());
  CHECK_OK(parsed_uri);
}

FUZZ_TEST(ResolvedAddress, CheckUriIsParseable)
    .WithDomains(VectorOf(Arbitrary<uint8_t>())
                     .WithMaxSize(EventEngine::ResolvedAddress::MAX_SIZE_BYTES)
                     .WithMinSize(1));
