
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_LOCAL_SUBCHANNEL_POOL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_LOCAL_SUBCHANNEL_POOL_H

#include <grpc/support/port_platform.h>

#include <map>

#include "src/core/client_channel/subchannel_pool_interface.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

class LocalSubchannelPool final : public SubchannelPoolInterface {
 public:
  LocalSubchannelPool() {}
  ~LocalSubchannelPool() override {}

  RefCountedPtr<Subchannel> RegisterSubchannel(
      const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) override;
  void UnregisterSubchannel(const SubchannelKey& key,
                            Subchannel* subchannel) override;
  RefCountedPtr<Subchannel> FindSubchannel(const SubchannelKey& key) override;

 private:

  std::map<SubchannelKey, Subchannel*> subchannel_map_;
};

}

#endif
