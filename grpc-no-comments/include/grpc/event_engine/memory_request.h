// Copyright 2021 The gRPC Authors

#ifndef GRPC_EVENT_ENGINE_MEMORY_REQUEST_H
#define GRPC_EVENT_ENGINE_MEMORY_REQUEST_H

#include <grpc/support/port_platform.h>
#include <stddef.h>

#include "absl/strings/string_view.h"

namespace grpc_event_engine {
namespace experimental {

class MemoryRequest {
 public:

  MemoryRequest(size_t n) : min_(n), max_(n) {}

  MemoryRequest(size_t min, size_t max) : min_(min), max_(max) {}

  static constexpr size_t max_allowed_size() { return 1024 * 1024 * 1024; }

  MemoryRequest Increase(size_t amount) const {
    return MemoryRequest(min_ + amount, max_ + amount);
  }

  size_t min() const { return min_; }
  size_t max() const { return max_; }

  bool operator==(const MemoryRequest& other) const {
    return min_ == other.min_ && max_ == other.max_;
  }
  bool operator!=(const MemoryRequest& other) const {
    return !(*this == other);
  }

  template <typename Sink>
  friend void AbslStringify(Sink& s, const MemoryRequest& r) {
    if (r.min_ == r.max_) {
      s.Append(std::to_string(r.min_));
    } else {
      s.Append(std::to_string(r.min_));
      s.Append("..");
      s.Append(std::to_string(r.max_));
    }
  }

 private:
  size_t min_;
  size_t max_;
};

}
}

#endif
