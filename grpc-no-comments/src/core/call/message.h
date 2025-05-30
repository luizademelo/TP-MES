// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_CALL_MESSAGE_H
#define GRPC_SRC_CORE_CALL_MESSAGE_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice_buffer.h"

#define GRPC_WRITE_INTERNAL_COMPRESS (0x80000000u)

#define GRPC_WRITE_INTERNAL_TEST_ONLY_WAS_COMPRESSED (0x40000000u)

#define GRPC_WRITE_INTERNAL_USED_MASK \
  (GRPC_WRITE_INTERNAL_COMPRESS | GRPC_WRITE_INTERNAL_TEST_ONLY_WAS_COMPRESSED)

namespace grpc_core {

class Message {
 public:
  Message() = default;
  ~Message() = default;
  Message(SliceBuffer payload, uint32_t flags)
      : payload_(std::move(payload)), flags_(flags) {}
  Message(const Message&) = delete;
  Message& operator=(const Message&) = delete;

  uint32_t flags() const { return flags_; }
  uint32_t& mutable_flags() { return flags_; }
  SliceBuffer* payload() { return &payload_; }
  const SliceBuffer* payload() const { return &payload_; }

  Arena::PoolPtr<Message> Clone() const {
    return Arena::MakePooled<Message>(payload_.Copy(), flags_);
  }

  std::string DebugString() const;

  template <typename Sink>
  friend void AbslStringify(Sink& sink, const Message& message) {
    sink.Append(message.DebugString());
  }

 private:
  SliceBuffer payload_;
  uint32_t flags_ = 0;
};

using MessageHandle = Arena::PoolPtr<Message>;

}

#endif
