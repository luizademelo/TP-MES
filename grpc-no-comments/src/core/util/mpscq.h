
// Copyright 2016 gRPC authors.

#ifndef GRPC_SRC_CORE_UTIL_MPSCQ_H
#define GRPC_SRC_CORE_UTIL_MPSCQ_H

#include <grpc/support/port_platform.h>

#include <atomic>

#include "absl/log/check.h"
#include "src/core/util/sync.h"

namespace grpc_core {

class MultiProducerSingleConsumerQueue {
 public:

  struct Node {
    std::atomic<Node*> next{nullptr};
  };

  MultiProducerSingleConsumerQueue() : head_{&stub_}, tail_(&stub_) {}
  ~MultiProducerSingleConsumerQueue() {
    CHECK(head_.load(std::memory_order_relaxed) == &stub_);
    CHECK(tail_ == &stub_);
  }

  bool Push(Node* node);

  Node* Pop();

  Node* PopAndCheckEnd(bool* empty);

 private:

  union {
    char padding_[GPR_CACHELINE_SIZE];
    std::atomic<Node*> head_{nullptr};
  };
  Node* tail_;
  Node stub_;
};

class LockedMultiProducerSingleConsumerQueue {
 public:
  typedef MultiProducerSingleConsumerQueue::Node Node;

  bool Push(Node* node);

  Node* TryPop();

  Node* Pop();

 private:
  MultiProducerSingleConsumerQueue queue_;
  Mutex mu_;
};

}

#endif
