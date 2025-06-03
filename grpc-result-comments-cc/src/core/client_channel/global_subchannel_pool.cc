Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/client_channel/global_subchannel_pool.h"
#include <grpc/support/port_platform.h>
#include <utility>
#include "src/core/client_channel/subchannel.h"

namespace grpc_core {

// Returns a singleton instance of LegacyGlobalSubchannelPool.
// Uses Meyer's singleton pattern with a static local variable for thread safety.
RefCountedPtr<LegacyGlobalSubchannelPool>
LegacyGlobalSubchannelPool::instance() {
  static LegacyGlobalSubchannelPool* p = new LegacyGlobalSubchannelPool();
  return p->RefAsSubclass<LegacyGlobalSubchannelPool>();
}

// Registers a subchannel with the pool using the given key.
// If a subchannel with the same key already exists and is active (non-zero ref count),
// returns the existing subchannel. Otherwise, adds the new subchannel to the pool.
// Thread-safe: protected by mutex.
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

// Unregisters a subchannel from the pool if it matches the given key and subchannel pointer.
// Thread-safe: protected by mutex.
void LegacyGlobalSubchannelPool::UnregisterSubchannel(const SubchannelKey& key,
                                                      Subchannel* subchannel) {
  MutexLock lock(&mu_);
  auto it = subchannel_map_.find(key);
  if (it != subchannel_map_.end() && it->second == subchannel) {
    subchannel_map_.erase(it);
  }
}

// Finds and returns an active subchannel (if exists) for the given key.
// Returns nullptr if no active subchannel is found.
// Thread-safe: protected by mutex.
RefCountedPtr<Subchannel> LegacyGlobalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  MutexLock lock(&mu_);
  auto it = subchannel_map_.find(key);
  if (it == subchannel_map_.end()) return nullptr;
  return it->second->RefIfNonZero();
}

// Returns a singleton instance of GlobalSubchannelPool.
// Uses Meyer's singleton pattern with a static local variable for thread safety.
RefCountedPtr<GlobalSubchannelPool> GlobalSubchannelPool::instance() {
  static GlobalSubchannelPool* p = new GlobalSubchannelPool();
  return p->RefAsSubclass<GlobalSubchannelPool>();
}

// Registers a subchannel with the pool using the given key.
// Uses sharding for better concurrency performance.
// If a subchannel with the same key already exists and is active, returns the existing one.
// Otherwise, adds the new subchannel to both write and read shards.
// Thread-safe: protected by per-shard mutexes.
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
  
  // Atomically update write shard and maintain old map for cleanup
  old_map1 = std::exchange(write_shard.map,
                           write_shard.map.Add(key, constructed->WeakRef()));
  
  // Synchronize read shard with write shard
  MutexLock lock_read(&read_shard.mu);
  old_map2 = std::exchange(read_shard.map, write_shard.map);
  
  return constructed;
}

// Unregisters a subchannel from the pool if it matches the given key and subchannel pointer.
// Uses sharding for better concurrency performance.
// Thread-safe: protected by per-shard mutexes.
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
  
  // Atomically update write shard and maintain old map for cleanup
  old_map1 = std::exchange(write_shard.map, write_shard.map.Remove(key));
  
  // Synchronize read shard with write shard
  MutexLock lock_read(&read_shard.mu);
  old_map2 = std::exchange(read_shard.map, write_shard.map);
}

// Finds and returns an active subchannel (if exists) for the given key.
// Uses sharding for better concurrency performance.
// Returns nullptr if no active subchannel is found.
// Thread-safe: protected by per-shard mutexes.
RefCountedPtr<Subchannel> GlobalSubchannelPool::FindSubchannel(
    const SubchannelKey& key) {
  auto shard_index = ShardIndex(key);
  auto& read_shard = read_shards_[shard_index];
  
  // Lock only briefly to get a snapshot of the map
  read_shard.mu.Lock();
  auto map = read_shard.map;
  read_shard.mu.Unlock();
  
  auto* subchannel = map.Lookup(key);
  if (subchannel == nullptr) return nullptr;
  return (*subchannel)->RefIfNonZero();
}

// Computes which shard a given key should be assigned to.
// Uses consistent hashing of the address part of the key.
size_t GlobalSubchannelPool::ShardIndex(const SubchannelKey& key) {
  absl::string_view addr(key.address().addr, key.address().len);
  return absl::HashOf(addr) % kShards;
}

// Default constructor
GlobalSubchannelPool::GlobalSubchannelPool() = default;

// Default destructor
GlobalSubchannelPool::~GlobalSubchannelPool() = default;

}
```

Key aspects covered in the comments:
1. Singleton pattern usage for instance management
2. Thread safety mechanisms (mutex locks)
3. Sharding strategy for concurrent access
4. Reference counting behavior
5. Map operations and atomic updates
6. Purpose of each method
7. Return value explanations
8. Edge case handling

The comments explain both the high-level design (like sharding for concurrency) and implementation details (like the use of std::exchange for atomic map updates).