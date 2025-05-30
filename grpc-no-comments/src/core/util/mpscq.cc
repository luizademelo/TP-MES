
// Copyright 2016 gRPC authors.

#include "src/core/util/mpscq.h"

#include <grpc/support/port_platform.h>

namespace grpc_core {

bool MultiProducerSingleConsumerQueue::Push(Node* node) {
  node->next.store(nullptr, std::memory_order_relaxed);
  Node* prev = head_.exchange(node, std::memory_order_acq_rel);
  prev->next.store(node, std::memory_order_release);
  return prev == &stub_;
}

MultiProducerSingleConsumerQueue::Node*
MultiProducerSingleConsumerQueue::Pop() {
  bool empty;
  return PopAndCheckEnd(&empty);
}

MultiProducerSingleConsumerQueue::Node*
MultiProducerSingleConsumerQueue::PopAndCheckEnd(bool* empty) {
  Node* tail = tail_;
  Node* next = tail_->next.load(std::memory_order_acquire);
  if (tail == &stub_) {

    if (next == nullptr) {
      *empty = true;
      return nullptr;
    }
    tail_ = next;
    tail = next;
    next = tail->next.load(std::memory_order_acquire);
  }
  if (next != nullptr) {
    *empty = false;
    tail_ = next;
    return tail;
  }
  Node* head = head_.load(std::memory_order_acquire);
  if (tail != head) {
    *empty = false;

    return nullptr;
  }
  Push(&stub_);
  next = tail->next.load(std::memory_order_acquire);
  if (next != nullptr) {
    *empty = false;
    tail_ = next;
    return tail;
  }

  *empty = false;
  return nullptr;
}

bool LockedMultiProducerSingleConsumerQueue::Push(Node* node) {
  return queue_.Push(node);
}

LockedMultiProducerSingleConsumerQueue::Node*
LockedMultiProducerSingleConsumerQueue::TryPop() {
  if (mu_.TryLock()) {
    Node* node = queue_.Pop();
    mu_.Unlock();
    return node;
  }
  return nullptr;
}

LockedMultiProducerSingleConsumerQueue::Node*
LockedMultiProducerSingleConsumerQueue::Pop() {
  MutexLock lock(&mu_);
  bool empty = false;
  Node* node;
  do {
    node = queue_.PopAndCheckEnd(&empty);
  } while (node == nullptr && !empty);
  return node;
}

}
