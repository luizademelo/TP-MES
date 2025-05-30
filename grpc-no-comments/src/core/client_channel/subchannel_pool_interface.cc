
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/subchannel_pool_interface.h"

#include <grpc/support/port_platform.h>
#include <string.h>

#include "absl/status/status.h"
#include "absl/status/statusor.h"
#include "absl/strings/str_cat.h"
#include "src/core/lib/address_utils/sockaddr_utils.h"
#include "src/core/lib/channel/channel_args.h"

#define GRPC_ARG_SUBCHANNEL_POOL "grpc.internal.subchannel_pool"

#define GRPC_ARG_SUBCHANNEL_KEY_TEST_ONLY_ID "grpc.subchannel_key_test_only_id"

namespace grpc_core {

SubchannelKey::SubchannelKey(const grpc_resolved_address& address,
                             const ChannelArgs& args)
    : address_(address), args_(args) {}

int SubchannelKey::Compare(const SubchannelKey& other) const {
  if (address_.len < other.address_.len) return -1;
  if (address_.len > other.address_.len) return 1;
  int r = memcmp(address_.addr, other.address_.addr, address_.len);
  if (r != 0) return r;
  return QsortCompare(args_, other.args_);
}

std::string SubchannelKey::ToString() const {
  auto addr_uri = grpc_sockaddr_to_uri(&address_);
  return absl::StrCat(
      "{address=",
      addr_uri.ok() ? addr_uri.value() : addr_uri.status().ToString(),
      ", args=", args_.ToString(), "}");
}

absl::string_view SubchannelPoolInterface::ChannelArgName() {
  return GRPC_ARG_SUBCHANNEL_POOL;
}

}
