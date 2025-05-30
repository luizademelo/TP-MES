// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_CONTROL_ENDPOINT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_LEGACY_CONTROL_ENDPOINT_H

#include "absl/cleanup/cleanup.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace chaotic_good_legacy {

class ControlEndpoint {
 private:
  class Buffer : public RefCounted<Buffer> {
   public:

    auto Queue(SliceBuffer&& buffer) {
      return [buffer = std::move(buffer), this]() mutable -> Poll<Empty> {
        Waker waker;
        auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
        MutexLock lock(&mu_);
        if (queued_output_.Length() != 0 &&
            queued_output_.Length() + buffer.Length() > MaxQueued()) {
          GRPC_TRACE_LOG(chaotic_good, INFO)
              << "CHAOTIC_GOOD: Delay control write"
              << " write_length=" << buffer.Length()
              << " already_buffered=" << queued_output_.Length()
              << " queue=" << this;
          write_waker_ = GetContext<Activity>()->MakeNonOwningWaker();
          return Pending{};
        }
        GRPC_TRACE_LOG(chaotic_good, INFO)
            << "CHAOTIC_GOOD: Queue control write " << buffer.Length()
            << " bytes on " << this;
        waker = std::move(flush_waker_);
        queued_output_.Append(buffer);
        return Empty{};
      };
    }

    auto Pull();

   private:
    size_t MaxQueued() const { return 1024 * 1024; }

    Mutex mu_;
    Waker write_waker_ ABSL_GUARDED_BY(mu_);
    Waker flush_waker_ ABSL_GUARDED_BY(mu_);
    SliceBuffer queued_output_ ABSL_GUARDED_BY(mu_);
  };

 public:
  ControlEndpoint(PromiseEndpoint endpoint,
                  grpc_event_engine::experimental::EventEngine* event_engine);

  auto Write(SliceBuffer&& bytes) { return buffer_->Queue(std::move(bytes)); }

  auto ReadSlice(size_t length) {
    return AddErrorPrefix("CONTROL_CHANNEL: ", endpoint_->ReadSlice(length));
  }
  auto Read(size_t length) {
    return AddErrorPrefix("CONTROL_CHANNEL: ", endpoint_->Read(length));
  }
  auto GetPeerAddress() const { return endpoint_->GetPeerAddress(); }
  auto GetLocalAddress() const { return endpoint_->GetLocalAddress(); }

 private:
  std::shared_ptr<PromiseEndpoint> endpoint_;
  RefCountedPtr<Party> write_party_;
  RefCountedPtr<Buffer> buffer_ = MakeRefCounted<Buffer>();
};

}
}

#endif
