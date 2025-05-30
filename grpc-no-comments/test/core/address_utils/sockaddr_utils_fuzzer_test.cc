
// Copyright 2022 gRPC authors.

#include <stdint.h>
#include <string.h>

#include <string>
#include <vector>

#include "absl/log/check.h"
#include "absl/status/statusor.h"
#include "fuzztest/fuzztest.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/iomgr/resolve_address.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/uri.h"

using fuzztest::Arbitrary;
using fuzztest::VectorOf;

void CheckUriIsParseable(std::vector<uint8_t> buffer) {
  grpc_resolved_address address;
  memset(&address, 0, sizeof(address));
  memcpy(address.addr, buffer.data(), buffer.size());
  address.len = buffer.size();
  absl::StatusOr<std::string> uri = grpc_sockaddr_to_uri(&address);
  if (!uri.ok()) return;
  absl::StatusOr<grpc_core::URI> parsed_uri =
      grpc_core::URI::Parse(uri.value());
  CHECK_OK(parsed_uri);
}
FUZZ_TEST(MyTestSuite, CheckUriIsParseable)
    .WithDomains(VectorOf(Arbitrary<uint8_t>())
                     .WithMaxSize(GRPC_MAX_SOCKADDR_SIZE)
                     .WithMinSize(1));
