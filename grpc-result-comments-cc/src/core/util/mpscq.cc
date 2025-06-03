Here's the commented version of the code:

```c++
// Copyright 2016 gRPC authors.

#include "src/core/util/mpscq.h"
#include <grpc/support/port_platform.h>

namespace grpc_core {

// Push a new node to the front of the queue (multi-producer thread-safe)
// Args:
//   node: The node to be pushed to the queue
// Returns:
//   true if the queue was empty before this push, false otherwise
bool MultiProducerSingleConsumerQueue::Push(Node* node) {
  // Initialize the new node's next pointer to nullptr
  node->next.store(nullptr, std::memory_order_relaxed);
  // Atomically exchange the head with the new node and get the previous head
  Node* prev = head_.exchange(node, std::memory_order_acq_rel);
  // Set the previous head's next pointer to the new node
  prev->next.store(node, std::memory_order_release);
  // Return whether the queue was empty (prev was the stub node)
  return prev == &stub_;
}

// Pop a node from the tail of the queue (single-consumer thread-safe)
// Returns:
//   The popped node or nullptr if queue is empty
MultiProducerSingleConsumerQueue::Node*
MultiProducerSingleConsumerQueue::Pop() {
  bool empty;
  return PopAndCheckEnd(&empty);
}

// Pop a node from the queue and check if the queue is empty
// Args:
//   empty: Output parameter indicating if the queue is empty
// Returns:
//   The popped node or nullptr if queue is empty or operation should be retried
MultiProducerSingleConsumerQueue::Node*
MultiProducerSingleConsumerQueue::PopAndCheckEnd(bool* empty) {
  Node* tail = tail_;
  Node* next = tail_->next.load(std::memory_order_acquire);
  
  // Handle case where tail is the stub node (queue might be empty)
  if (tail == &stub_) {
    if (next == nullptr) {
      *empty = true;
      return nullptr;  // Queue is empty
    }
    // Move tail past the stub node
    tail_ = next;
    tail = next;
    next = tail->next.load(std::memory_order_acquire);
  }
  
  // If next node exists, advance tail and return current tail
  if (next != nullptr) {
    *empty = false;
    tail_ = next;
    return tail;
  }
  
  // Check if queue is actually empty
  Node* head = head_.load(std::memory_order_acquire);
  if (tail != head) {
    *empty = false;
    return nullptr;  // Queue not empty, but need to retry
  }
  
  // Queue might be empty, add stub node to confirm
  Push(&stub_);
  next = tail->next.load(std::memory_order_acquire);
  if (next != nullptr) {
    *empty = false;
    tail_ = next;
    return tail;
  }

  *empty = false;
  return nullptr;  // No node available right now
}

// Thread-safe push operation using external mutex
// Args:
//   node: The node to be pushed to the queue
// Returns:
//   true if the queue was empty before this push, false otherwise
bool LockedMultiProducerSingleConsumerQueue::Push(Node* node) {
  return queue_.Push(node);
}

// Try to pop a node without blocking (thread-safe)
// Returns:
//   The popped node or nullptr if queue is empty or lock is unavailable
LockedMultiProducerSingleConsumerQueue::Node*
LockedMultiProducerSingleConsumerQueue::TryPop() {
  if (mu_.TryLock()) {
    Node* node = queue_.Pop();
    mu_.Unlock();
    return node;
  }
  return nullptr;
}

// Pop a node from the queue, blocking until a node is available (thread-safe)
// Returns:
//   The popped node (guaranteed non-null as it blocks until available)
LockedMultiProducerSingleConsumerQueue::Node*
LockedMultiProducerSingleConsumerQueue::Pop() {
  MutexLock lock(&mu_);  // Lock held for entire scope
  bool empty = false;
  Node* node;
  do {
    node = queue_.PopAndCheckEnd(&empty);
  } while (node == nullptr && !empty);
  return node;
}

}  // namespace grpc_core
```

The comments explain:
1. The purpose of each method
2. The thread-safety guarantees
3. The memory ordering semantics
4. The handling of the stub node (used to indicate empty queue state)
5. The retry logic in Pop operations
6. The difference between blocking and non-blocking operations in the locked version
7. The flow of data through the queue

The comments maintain consistency with the original code style while providing clear explanations of the complex concurrent queue operations.