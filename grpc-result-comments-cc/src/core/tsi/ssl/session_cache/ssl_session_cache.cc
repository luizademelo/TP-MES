Here's the commented version of the code:

```c++
// Copyright 2018 gRPC authors.

#include "src/core/tsi/ssl/session_cache/ssl_session_cache.h"

#include <grpc/support/port_platform.h>
#include <grpc/support/string_util.h>

#include "absl/log/check.h"
#include "absl/log/log.h"
#include "src/core/lib/slice/slice_internal.h"
#include "src/core/tsi/ssl/session_cache/ssl_session.h"
#include "src/core/util/crash.h"
#include "src/core/util/sync.h"

namespace tsi {

// Node class represents an entry in the LRU cache
class SslSessionLRUCache::Node {
 public:
  // Constructor: creates a new node with given key and SSL session
  Node(const std::string& key, SslSessionPtr session) : key_(key) {
    SetSession(std::move(session));
  }

  // Delete copy constructor and assignment operator
  Node(const Node&) = delete;
  Node& operator=(const Node&) = delete;

  // Returns the key associated with this node
  const std::string& key() const { return key_; }

  // Returns a copy of the cached SSL session
  SslSessionPtr CopySession() const { return session_->CopySession(); }

  // Updates the SSL session stored in this node
  void SetSession(SslSessionPtr session) {
    session_ = SslCachedSession::Create(std::move(session));
  }

 private:
  friend class SslSessionLRUCache;

  std::string key_;  // The key used to identify this session
  std::unique_ptr<SslCachedSession> session_;  // The cached SSL session

  // Pointers for maintaining the doubly-linked list structure
  Node* next_ = nullptr;
  Node* prev_ = nullptr;
};

// Constructor: creates an LRU cache with specified capacity
SslSessionLRUCache::SslSessionLRUCache(size_t capacity) : capacity_(capacity) {
  if (capacity == 0) {
    LOG(ERROR) << "SslSessionLRUCache capacity is zero. SSL sessions cannot be "
                  "resumed.";
  }
}

// Destructor: cleans up all nodes in the cache
SslSessionLRUCache::~SslSessionLRUCache() {
  Node* node = use_order_list_head_;
  while (node) {
    Node* next = node->next_;
    delete node;
    node = next;
  }
}

// Returns the current number of entries in the cache
size_t SslSessionLRUCache::Size() {
  grpc_core::MutexLock lock(&lock_);
  return use_order_list_size_;
}

// Internal method to find a node by key and update its position in LRU order
// Must be called with lock held
SslSessionLRUCache::Node* SslSessionLRUCache::FindLocked(
    const std::string& key) {
  auto it = entry_by_key_.find(key);
  if (it == entry_by_key_.end()) {
    return nullptr;
  }
  Node* node = it->second;

  // Move the found node to the front (most recently used position)
  Remove(node);
  PushFront(node);
  AssertInvariants();
  return node;
}

// Adds or updates an SSL session in the cache
void SslSessionLRUCache::Put(const char* key, SslSessionPtr session) {
  if (session == nullptr) {
    LOG(ERROR) << "Attempted to put null SSL session in session cache.";
    return;
  }
  grpc_core::MutexLock lock(&lock_);
  Node* node = FindLocked(key);
  if (node != nullptr) {
    // Update existing session
    node->SetSession(std::move(session));
    return;
  }
  // Create new node and add to cache
  node = new Node(key, std::move(session));
  PushFront(node);
  entry_by_key_.emplace(key, node);
  AssertInvariants();
  
  // If cache exceeds capacity, remove least recently used item
  if (use_order_list_size_ > capacity_) {
    CHECK(use_order_list_tail_);
    node = use_order_list_tail_;
    Remove(node);

    entry_by_key_.erase(node->key());
    delete node;
    AssertInvariants();
  }
}

// Retrieves an SSL session from the cache
SslSessionPtr SslSessionLRUCache::Get(const char* key) {
  grpc_core::MutexLock lock(&lock_);

  Node* node = FindLocked(key);
  if (node == nullptr) {
    return nullptr;
  }
  return node->CopySession();
}

// Internal method to remove a node from the linked list
// Must be called with lock held
void SslSessionLRUCache::Remove(SslSessionLRUCache::Node* node) {
  if (node->prev_ == nullptr) {
    use_order_list_head_ = node->next_;
  } else {
    node->prev_->next_ = node->next_;
  }
  if (node->next_ == nullptr) {
    use_order_list_tail_ = node->prev_;
  } else {
    node->next_->prev_ = node->prev_;
  }
  CHECK_GE(use_order_list_size_, 1u);
  use_order_list_size_--;
}

// Internal method to add a node to the front of the linked list (MRU position)
// Must be called with lock held
void SslSessionLRUCache::PushFront(SslSessionLRUCache::Node* node) {
  if (use_order_list_head_ == nullptr) {
    // First node in empty list
    use_order_list_head_ = node;
    use_order_list_tail_ = node;
    node->next_ = nullptr;
    node->prev_ = nullptr;
  } else {
    // Add to front of non-empty list
    node->next_ = use_order_list_head_;
    node->next_->prev_ = node;
    use_order_list_head_ = node;
    node->prev_ = nullptr;
  }
  use_order_list_size_++;
}

// Debug method to verify cache invariants
#ifndef NDEBUG
void SslSessionLRUCache::AssertInvariants() {
  size_t size = 0;
  Node* prev = nullptr;
  Node* current = use_order_list_head_;
  while (current != nullptr) {
    size++;
    CHECK(current->prev_ == prev);
    auto it = entry_by_key_.find(current->key());
    CHECK(it != entry_by_key_.end());
    CHECK(it->second == current);
    prev = current;
    current = current->next_;
  }
  CHECK(prev == use_order_list_tail_);
  CHECK(size == use_order_list_size_);
  CHECK(entry_by_key_.size() == use_order_list_size_);
}
#else
// Empty implementation for release builds
void SslSessionLRUCache::AssertInvariants() {}
#endif

}  // namespace tsi
```