
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_THREAD_POOL_INTERFACE_H
#define GRPC_SRC_CPP_SERVER_THREAD_POOL_INTERFACE_H

#include <functional>

namespace grpc {

class ThreadPoolInterface {
 public:
  virtual ~ThreadPoolInterface() {}

  virtual void Add(const std::function<void()>& callback) = 0;
};

typedef ThreadPoolInterface* (*CreateThreadPoolFunc)(void);
void SetCreateThreadPool(CreateThreadPoolFunc func);

ThreadPoolInterface* CreateDefaultThreadPool();

}

#endif
