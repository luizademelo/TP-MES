// Copyright 2024 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_EXTENSIBLE_H
#define GRPC_EVENT_ENGINE_EXTENSIBLE_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"

namespace grpc_event_engine {
namespace experimental {

class Extensible {
 public:

  virtual void* QueryExtension(absl::string_view ) { return nullptr; }

 protected:
  ~Extensible() = default;
};

}
}

#endif
