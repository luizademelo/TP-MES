// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_LIB_EVENT_ENGINE_FORKABLE_H
#define GRPC_SRC_CORE_LIB_EVENT_ENGINE_FORKABLE_H

#include <grpc/support/port_platform.h>

#include <memory>
#include <vector>

#include "src/core/lib/debug/trace.h"

namespace grpc_event_engine::experimental {

class Forkable {
 public:
  virtual ~Forkable() = default;
  virtual void PrepareFork() = 0;
  virtual void PostforkParent() = 0;
  virtual void PostforkChild() = 0;
};

class ObjectGroupForkHandler {
 public:

  void RegisterForkable(std::shared_ptr<Forkable> forkable,
                        GRPC_UNUSED void (*prepare)(void),
                        GRPC_UNUSED void (*parent)(void),
                        GRPC_UNUSED void (*child)(void));

  void Prefork();
  void PostforkParent();
  void PostforkChild();

 private:
  GRPC_UNUSED bool registered_ = false;
  bool is_forking_ = false;
  std::vector<std::weak_ptr<Forkable> > forkables_;
};

}

#endif
