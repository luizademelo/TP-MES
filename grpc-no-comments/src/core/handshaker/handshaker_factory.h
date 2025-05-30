
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_FACTORY_H
#define GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_FACTORY_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"

namespace grpc_core {

class HandshakeManager;

class HandshakerFactory {
 public:

  enum class HandshakerPriority : int {

    kPreTCPConnectHandshakers,

    kTCPConnectHandshakers,

    kHTTPConnectHandshakers,

    kReadAheadSecurityHandshakers,

    kSecurityHandshakers,

    kTemporaryHackDoNotUseEndpointWrappingHandshakers,
  };

  virtual void AddHandshakers(const ChannelArgs& args,
                              grpc_pollset_set* interested_parties,
                              HandshakeManager* handshake_mgr) = 0;

  virtual HandshakerPriority Priority() = 0;
  virtual ~HandshakerFactory() = default;
};

}

#endif
