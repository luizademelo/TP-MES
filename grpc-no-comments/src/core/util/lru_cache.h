
// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_LRU_CACHE_H
#define GRPC_SRC_CORE_UTIL_LRU_CACHE_H

#include <list>
#include <optional>
#include <tuple>
#include <utility>

#include "absl/container/flat_hash_map.h"
#include "absl/functional/any_invocable.h"
#include "absl/log/check.h"

namespace grpc_core {

template <typename Key, typename Value>
class LruCache {
 public:
  explicit LruCache(size_t max_size) : max_size_(max_size) {
    CHECK_GT(max_size, 0UL);
  }

  std::optional<Value> Get(Key key);

  Value GetOrInsert(Key key, absl::AnyInvocable<Value(const Key&)> create);

  void SetMaxSize(size_t max_size);

 private:
  struct CacheEntry {
    Value value;
    typename std::list<Key>::iterator lru_iterator;

    explicit CacheEntry(Value v) : value(std::move(v)) {}
  };

  void RemoveOldestEntry();

  size_t max_size_;
  absl::flat_hash_map<Key, CacheEntry> cache_;
  std::list<Key> lru_list_;
};

template <typename Key, typename Value>
std::optional<Value> LruCache<Key, Value>::Get(Key key) {
  auto it = cache_.find(key);
  if (it == cache_.end()) return std::nullopt;

  auto new_lru_it = lru_list_.insert(lru_list_.end(), *it->second.lru_iterator);
  lru_list_.erase(it->second.lru_iterator);
  it->second.lru_iterator = new_lru_it;
  return it->second.value;
}

template <typename Key, typename Value>
Value LruCache<Key, Value>::GetOrInsert(
    Key key, absl::AnyInvocable<Value(const Key&)> create) {
  auto value = Get(key);
  if (value.has_value()) return std::move(*value);

  if (cache_.size() == max_size_) RemoveOldestEntry();

  auto it = cache_
                .emplace(std::piecewise_construct, std::forward_as_tuple(key),
                         std::forward_as_tuple(create(key)))
                .first;
  it->second.lru_iterator = lru_list_.insert(lru_list_.end(), std::move(key));
  return it->second.value;
}

template <typename Key, typename Value>
void LruCache<Key, Value>::SetMaxSize(size_t max_size) {
  max_size_ = max_size;
  while (cache_.size() > max_size_) {
    RemoveOldestEntry();
  }
}

template <typename Key, typename Value>
void LruCache<Key, Value>::RemoveOldestEntry() {
  auto lru_it = lru_list_.begin();
  CHECK(lru_it != lru_list_.end());
  auto cache_it = cache_.find(*lru_it);
  CHECK(cache_it != cache_.end());
  cache_.erase(cache_it);
  lru_list_.pop_front();
}

}

#endif
