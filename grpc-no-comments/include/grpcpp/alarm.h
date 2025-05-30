
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_ALARM_H
#define GRPCPP_ALARM_H

#include <grpc/event_engine/event_engine.h>
#include <grpc/grpc.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/completion_queue_tag.h>
#include <grpcpp/impl/grpc_library.h>
#include <grpcpp/support/time.h>

#include <functional>

namespace grpc {

class Alarm : private grpc::internal::GrpcLibrary {
 public:

  Alarm();

  ~Alarm() override;

  template <typename T>
  Alarm(grpc::CompletionQueue* cq, const T& deadline, void* tag) : Alarm() {
    SetInternal(cq, grpc::TimePoint<T>(deadline).raw_time(), tag);
  }

  template <typename T>
  void Set(grpc::CompletionQueue* cq, const T& deadline, void* tag) {
    SetInternal(cq, grpc::TimePoint<T>(deadline).raw_time(), tag);
  }

  Alarm(const Alarm&) = delete;
  Alarm& operator=(const Alarm&) = delete;

  Alarm(Alarm&& rhs) noexcept : alarm_(rhs.alarm_) { rhs.alarm_ = nullptr; }
  Alarm& operator=(Alarm&& rhs) noexcept {
    std::swap(alarm_, rhs.alarm_);
    return *this;
  }

  void Cancel();

  template <typename T>
  void Set(const T& deadline, std::function<void(bool)> f) {
    SetInternal(grpc::TimePoint<T>(deadline).raw_time(), std::move(f));
  }

 private:
  void SetInternal(grpc::CompletionQueue* cq, gpr_timespec deadline, void* tag);
  void SetInternal(gpr_timespec deadline, std::function<void(bool)> f);

  grpc::internal::CompletionQueueTag* alarm_;
};

}

#endif
