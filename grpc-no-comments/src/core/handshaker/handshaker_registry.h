
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_REGISTRY_H
#define GRPC_SRC_CORE_HANDSHAKER_HANDSHAKER_REGISTRY_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <vector>

#include "src/core/handshaker/handshaker_factory.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"

namespace grpc_core {

typedef enum {
  HANDSHAKER_CLIENT = 0,
  HANDSHAKER_SERVER,
  NUM_HANDSHAKER_TYPES,
} HandshakerType;

class HandshakerRegistry {
 public:
  class Builder {
   public:

    void RegisterHandshakerFactory(HandshakerType handshaker_type,
                                   std::unique_ptr<HandshakerFactory> factory);

    HandshakerRegistry Build();

   private:
    std::vector<std::unique_ptr<HandshakerFactory>>
        factories_[NUM_HANDSHAKER_TYPES];
  };

  void AddHandshakers(HandshakerType handshaker_type, const ChannelArgs& args,
                      grpc_pollset_set* interested_parties,
                      HandshakeManager* handshake_mgr) const;

 private:
  HandshakerRegistry() = default;

  std::vector<std::unique_ptr<HandshakerFactory>>
      factories_[NUM_HANDSHAKER_TYPES];
};

}

#endif
