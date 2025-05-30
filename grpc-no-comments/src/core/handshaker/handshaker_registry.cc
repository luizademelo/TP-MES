
// Copyright 2016 gRPC authors.

#include "src/core/handshaker/handshaker_registry.h"

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include <algorithm>
#include <utility>

namespace grpc_core {

void HandshakerRegistry::Builder::RegisterHandshakerFactory(
    HandshakerType handshaker_type,
    std::unique_ptr<HandshakerFactory> factory) {
  auto& vec = factories_[handshaker_type];
  auto where = vec.empty() ? vec.begin() : vec.end();
  for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
    if (factory->Priority() < iter->get()->Priority()) {
      where = iter;
      break;
    }
  }
  vec.insert(where, std::move(factory));
}

HandshakerRegistry HandshakerRegistry::Builder::Build() {
  HandshakerRegistry out;
  for (size_t i = 0; i < NUM_HANDSHAKER_TYPES; i++) {
    out.factories_[i] = std::move(factories_[i]);
  }
  return out;
}

void HandshakerRegistry::AddHandshakers(HandshakerType handshaker_type,
                                        const ChannelArgs& args,
                                        grpc_pollset_set* interested_parties,
                                        HandshakeManager* handshake_mgr) const {
  for (const auto& factory : factories_[handshaker_type]) {
    factory->AddHandshakers(args, interested_parties, handshake_mgr);
  }
}

}
