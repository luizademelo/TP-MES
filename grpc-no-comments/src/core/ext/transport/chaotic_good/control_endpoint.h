// Copyright 2024 gRPC authors.

#ifndef GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CONTROL_ENDPOINT_H
#define GRPC_SRC_CORE_EXT_TRANSPORT_CHAOTIC_GOOD_CONTROL_ENDPOINT_H

#include "absl/cleanup/cleanup.h"
#include "src/core/ext/transport/chaotic_good/tcp_ztrace_collector.h"
#include "src/core/ext/transport/chaotic_good/transport_context.h"
#include "src/core/lib/promise/party.h"
#include "src/core/lib/transport/promise_endpoint.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/sync.h"

namespace grpc_core {
namespace chaotic_good {

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

    void ForceQueue(SliceBuffer&& buffer) {
      Waker waker;
      auto cleanup = absl::MakeCleanup([&waker]() { waker.Wakeup(); });
      MutexLock lock(&mu_);
      GRPC_TRACE_LOG(chaotic_good, INFO)
          << "CHAOTIC_GOOD: Force queue control write " << buffer.Length()
          << " bytes on " << this;
      waker = std::move(flush_waker_);
      queued_output_.Append(buffer);
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
  ControlEndpoint(PromiseEndpoint endpoint, RefCountedPtr<TransportContext> ctx,
                  std::shared_ptr<TcpZTraceCollector> ztrace_collector);

  auto Write(SliceBuffer&& bytes) { return buffer_->Queue(std::move(bytes)); }

  auto ReadSlice(size_t length) {
    return AddErrorPrefix(
        "CONTROL_CHANNEL: ",
        GRPC_LATENT_SEE_PROMISE("CtlEndpointReadHdr",
                                endpoint_->ReadSlice(length)));
  }
  auto Read(size_t length) {
    return AddErrorPrefix(
        "CONTROL_CHANNEL: ",
        GRPC_LATENT_SEE_PROMISE("CtlEndpointRead", endpoint_->Read(length)));
  }
  auto GetPeerAddress() const { return endpoint_->GetPeerAddress(); }
  auto GetLocalAddress() const { return endpoint_->GetLocalAddress(); }

  std::shared_ptr<grpc_event_engine::experimental::EventEngine::Endpoint>
  GetEventEngineEndpoint() const {
    return endpoint_->GetEventEngineEndpoint();
  }

  auto SecureFrameWriterCallback() {
    return [buffer = buffer_](SliceBuffer* data) {
      SliceBuffer output;
      CHECK_LT(data->Length(), std::numeric_limits<uint32_t>::max());
      const uint32_t length = data->Length();
      TcpFrameHeader hdr{{FrameType::kTcpSecurityFrame, 0, length}};
      hdr.Serialize(output.AddTiny(TcpFrameHeader::kFrameHeaderSize));
      output.TakeAndAppend(*data);
      buffer->ForceQueue(std::move(output));
    };
  }

 private:
  std::shared_ptr<PromiseEndpoint> endpoint_;
  RefCountedPtr<Party> write_party_;
  RefCountedPtr<Buffer> buffer_ = MakeRefCounted<Buffer>();
  RefCountedPtr<TransportContext> ctx_;
  std::shared_ptr<TcpZTraceCollector> ztrace_collector_;
};

}
}

#endif
