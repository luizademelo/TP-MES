
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_DYNAMIC_THREAD_POOL_H
#define GRPC_SRC_CPP_SERVER_DYNAMIC_THREAD_POOL_H

#include <grpc/event_engine/event_engine.h>

#include <functional>
#include <memory>

#include "src/core/lib/event_engine/default_event_engine.h"
#include "src/cpp/server/thread_pool_interface.h"

namespace grpc {

class DynamicThreadPool final : public ThreadPoolInterface {
 public:
  void Add(const std::function<void()>& callback) override {
    event_engine_->Run(callback);
  }

 private:
  std::shared_ptr<grpc_event_engine::experimental::EventEngine> event_engine_ =
      grpc_event_engine::experimental::GetDefaultEventEngine();
};

}

#endif
