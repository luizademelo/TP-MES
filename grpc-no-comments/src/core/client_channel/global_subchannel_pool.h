
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_GLOBAL_SUBCHANNEL_POOL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_GLOBAL_SUBCHANNEL_POOL_H

#include <grpc/support/port_platform.h>

#include <map>

#include "absl/base/thread_annotations.h"
#include "src/core/client_channel/subchannel_pool_interface.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class LegacyGlobalSubchannelPool final : public SubchannelPoolInterface {
 public:

  static RefCountedPtr<LegacyGlobalSubchannelPool> instance();

  RefCountedPtr<Subchannel> RegisterSubchannel(
      const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) override
      ABSL_LOCKS_EXCLUDED(mu_);
  void UnregisterSubchannel(const SubchannelKey& key,
                            Subchannel* subchannel) override
      ABSL_LOCKS_EXCLUDED(mu_);
  RefCountedPtr<Subchannel> FindSubchannel(const SubchannelKey& key) override
      ABSL_LOCKS_EXCLUDED(mu_);

 private:
  LegacyGlobalSubchannelPool() {}
  ~LegacyGlobalSubchannelPool() override {}

  std::map<SubchannelKey, Subchannel*> subchannel_map_ ABSL_GUARDED_BY(mu_);

  Mutex mu_;
};

class GlobalSubchannelPool final : public SubchannelPoolInterface {
 public:

  static RefCountedPtr<GlobalSubchannelPool> instance();

  RefCountedPtr<Subchannel> RegisterSubchannel(
      const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) override;
  void UnregisterSubchannel(const SubchannelKey& key,
                            Subchannel* subchannel) override;
  RefCountedPtr<Subchannel> FindSubchannel(const SubchannelKey& key) override;

 private:
  GlobalSubchannelPool();
  ~GlobalSubchannelPool() override;

  static const size_t kShards = 127;

  using SubchannelMap = AVL<SubchannelKey, WeakRefCountedPtr<Subchannel>>;
  struct LockedMap {
    Mutex mu;
    SubchannelMap map ABSL_GUARDED_BY(mu);
  };
  using ShardedMap = std::array<LockedMap, kShards>;

  static size_t ShardIndex(const SubchannelKey& key);

  ShardedMap write_shards_;
  ShardedMap read_shards_;
};

}

#endif
