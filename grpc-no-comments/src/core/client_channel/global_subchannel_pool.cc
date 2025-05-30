
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/global_subchannel_pool.h"

#include <grpc/support/port_platform.h>

#include <utility>

#include "src/core/client_channel/subchannel.h"

namespace grpc_core {

RefCountedPtr<LegacyGlobalSubchannelPool>
LegacyGlobalSubchannelPool::instance() {
  static LegacyGlobalSubchannelPool* p = new LegacyGlobalSubchannelPool();
  return p->RefAsSubclass<LegacyGlobalSubchannelPool>();
}

RefCountedPtr<Subchannel> LegacyGlobalSubchannelPool::RegisterSubchannel(
    const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) {
  MutexLock lock(&mu_);
  auto it = subchannel_map_.find(key);
  if (it != subchannel_map_.end()) {
    RefCountedPtr<Subchannel> existing = it->second->RefIfNonZero();
    if (existing != nullptr) return existing;
  }
  subchannel_map_[key] = constructed.get();
  return constructed;
}

void LegacyGlobalSubchannelPool::UnregisterSubchannel(const SubchannelKey& key,
                                                      Subchannel* subchannel) {
  MutexLock lock(&mu_);
  auto it = subchannel_map_.find(key);

  if (it != subchannel_map_.end() && it->second == subchannel) {
    subchannel_map_.erase(it);
  }
}

RefCountedPtr<Subchannel> LegacyGlobalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  MutexLock lock(&mu_);
  auto it = subchannel_map_.find(key);
  if (it == subchannel_map_.end()) return nullptr;
  return it->second->RefIfNonZero();
}

RefCountedPtr<GlobalSubchannelPool> GlobalSubchannelPool::instance() {
  static GlobalSubchannelPool* p = new GlobalSubchannelPool();
  return p->RefAsSubclass<GlobalSubchannelPool>();
}

RefCountedPtr<Subchannel> GlobalSubchannelPool::RegisterSubchannel(
    const SubchannelKey& key, RefCountedPtr<Subchannel> constructed) {
  auto shard_index = ShardIndex(key);
  auto& write_shard = write_shards_[shard_index];
  auto& read_shard = read_shards_[shard_index];
  SubchannelMap old_map1;
  SubchannelMap old_map2;
  MutexLock lock(&write_shard.mu);
  auto* existing = write_shard.map.Lookup(key);
  if (existing != nullptr) return (*existing)->RefIfNonZero();
  old_map1 = std::exchange(write_shard.map,
                           write_shard.map.Add(key, constructed->WeakRef()));
  MutexLock lock_read(&read_shard.mu);
  old_map2 = std::exchange(read_shard.map, write_shard.map);
  return constructed;
}

void GlobalSubchannelPool::UnregisterSubchannel(const SubchannelKey& key,
                                                Subchannel* subchannel) {
  auto shard_index = ShardIndex(key);
  auto& write_shard = write_shards_[shard_index];
  auto& read_shard = read_shards_[shard_index];
  SubchannelMap old_map1;
  SubchannelMap old_map2;
  MutexLock lock(&write_shard.mu);
  auto* existing = write_shard.map.Lookup(key);

  if (existing == nullptr || existing->get() != subchannel) return;
  old_map1 = std::exchange(write_shard.map, write_shard.map.Remove(key));
  MutexLock lock_read(&read_shard.mu);
  old_map2 = std::exchange(read_shard.map, write_shard.map);
}

RefCountedPtr<Subchannel> GlobalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  auto shard_index = ShardIndex(key);
  auto& read_shard = read_shards_[shard_index];
  read_shard.mu.Lock();
  auto map = read_shard.map;
  read_shard.mu.Unlock();
  auto* subchannel = map.Lookup(key);
  if (subchannel == nullptr) return nullptr;
  return (*subchannel)->RefIfNonZero();
}

size_t GlobalSubchannelPool::ShardIndex(const SubchannelKey& key) {
  absl::string_view addr(key.address().addr, key.address().len);
  return absl::HashOf(addr) % kShards;
}

GlobalSubchannelPool::GlobalSubchannelPool() = default;

GlobalSubchannelPool::~GlobalSubchannelPool() = default;

}
