
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/local_subchannel_pool.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "absl/log/check.h"
#include "src/core/client_channel/subchannel.h"

namespace grpc_core {

RefCountedPtr<Subchannel> LocalSubchannelPool::RegisterSubchannel(
    const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) {
  auto it = subchannel_map_.find(key);

  CHECK(it == subchannel_map_.end());
  subchannel_map_[key] = constructed.get();
  return constructed;
}

void LocalSubchannelPool::UnregisterSubchannel(const SubchannelKey& key,
                                               Subchannel* subchannel) {
  auto it = subchannel_map_.find(key);

  CHECK(it != subchannel_map_.end());
  CHECK(it->second == subchannel);
  subchannel_map_.erase(it);
}

RefCountedPtr<Subchannel> LocalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  auto it = subchannel_map_.find(key);
  if (it == subchannel_map_.end()) return nullptr;
  return it->second->Ref();
}

}
