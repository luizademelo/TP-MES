// Copyright 2022 gRPC authors.

#ifndef GRPC_EVENT_ENGINE_INTERNAL_WRITE_EVENT_H
#define GRPC_EVENT_ENGINE_INTERNAL_WRITE_EVENT_H

namespace grpc_event_engine::experimental::internal {

enum class WriteEvent {
  kSendMsg,
  kScheduled,
  kSent,
  kAcked,
  kClosed,
  kCount
};

}

#endif
