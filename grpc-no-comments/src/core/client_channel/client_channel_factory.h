
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_FACTORY_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CLIENT_CHANNEL_FACTORY_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/client_channel/subchannel.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class ClientChannelFactory {
 public:
  struct RawPointerChannelArgTag {};

  virtual ~ClientChannelFactory() = default;

  virtual RefCountedPtr<Subchannel> CreateSubchannel(
      const grpc_resolved_address& address, const ChannelArgs& args) = 0;

  static absl::string_view ChannelArgName();
};

}

#endif
