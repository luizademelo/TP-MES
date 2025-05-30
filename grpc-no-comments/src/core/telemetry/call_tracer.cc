
// Copyright 2023 gRPC authors.

#include "src/core/telemetry/call_tracer.h"

#include <grpc/support/port_platform.h>

#include <memory>
#include <utility>
#include <vector>

#include "absl/log/check.h"
#include "src/core/lib/promise/context.h"
#include "src/core/telemetry/tcp_tracer.h"

namespace grpc_core {

CallTracerInterface::TransportByteSize&
CallTracerInterface::TransportByteSize::operator+=(
    const CallTracerInterface::TransportByteSize& other) {
  framing_bytes += other.framing_bytes;
  data_bytes += other.data_bytes;
  header_bytes += other.header_bytes;
  return *this;
}

namespace {

ServerCallTracerFactory* g_server_call_tracer_factory_ = nullptr;

const char* kServerCallTracerFactoryChannelArgName =
    "grpc.experimental.server_call_tracer_factory";

}

ServerCallTracerFactory* ServerCallTracerFactory::Get(
    const ChannelArgs& channel_args) {
  ServerCallTracerFactory* factory =
      channel_args.GetObject<ServerCallTracerFactory>();
  if (factory == nullptr) {
    factory = g_server_call_tracer_factory_;
  }
  if (factory && factory->IsServerTraced(channel_args)) {
    return factory;
  }
  return nullptr;
}

void ServerCallTracerFactory::RegisterGlobal(ServerCallTracerFactory* factory) {
  g_server_call_tracer_factory_ = factory;
}

void ServerCallTracerFactory::TestOnlyReset() {
  delete g_server_call_tracer_factory_;
  g_server_call_tracer_factory_ = nullptr;
}

absl::string_view ServerCallTracerFactory::ChannelArgName() {
  return kServerCallTracerFactoryChannelArgName;
}

class DelegatingClientCallTracer : public ClientCallTracer {
 public:
  class DelegatingClientCallAttemptTracer
      : public ClientCallTracer::CallAttemptTracer {
   public:
    explicit DelegatingClientCallAttemptTracer(
        std::vector<CallAttemptTracer*> tracers)
        : tracers_(std::move(tracers)) {
      DCHECK(!tracers_.empty());
    }
    ~DelegatingClientCallAttemptTracer() override {}
    void RecordSendInitialMetadata(
        grpc_metadata_batch* send_initial_metadata) override {
      for (auto* tracer : tracers_) {
        tracer->RecordSendInitialMetadata(send_initial_metadata);
      }
    }
    void RecordSendTrailingMetadata(
        grpc_metadata_batch* send_trailing_metadata) override {
      for (auto* tracer : tracers_) {
        tracer->RecordSendTrailingMetadata(send_trailing_metadata);
      }
    }
    void RecordSendMessage(const Message& send_message) override {
      for (auto* tracer : tracers_) {
        tracer->RecordSendMessage(send_message);
      }
    }
    void RecordSendCompressedMessage(
        const Message& send_compressed_message) override {
      for (auto* tracer : tracers_) {
        tracer->RecordSendCompressedMessage(send_compressed_message);
      }
    }
    void RecordReceivedInitialMetadata(
        grpc_metadata_batch* recv_initial_metadata) override {
      for (auto* tracer : tracers_) {
        tracer->RecordReceivedInitialMetadata(recv_initial_metadata);
      }
    }
    void RecordReceivedMessage(const Message& recv_message) override {
      for (auto* tracer : tracers_) {
        tracer->RecordReceivedMessage(recv_message);
      }
    }
    void RecordReceivedDecompressedMessage(
        const Message& recv_decompressed_message) override {
      for (auto* tracer : tracers_) {
        tracer->RecordReceivedDecompressedMessage(recv_decompressed_message);
      }
    }
    void RecordCancel(grpc_error_handle cancel_error) override {
      for (auto* tracer : tracers_) {
        tracer->RecordCancel(cancel_error);
      }
    }
    void RecordReceivedTrailingMetadata(
        absl::Status status, grpc_metadata_batch* recv_trailing_metadata,
        const grpc_transport_stream_stats* transport_stream_stats) override {
      for (auto* tracer : tracers_) {
        tracer->RecordReceivedTrailingMetadata(status, recv_trailing_metadata,
                                               transport_stream_stats);
      }
    }
    void RecordEnd() override {
      for (auto* tracer : tracers_) {
        tracer->RecordEnd();
      }
    }
    void RecordIncomingBytes(
        const TransportByteSize& transport_byte_size) override {
      for (auto* tracer : tracers_) {
        tracer->RecordIncomingBytes(transport_byte_size);
      }
    }
    void RecordOutgoingBytes(
        const TransportByteSize& transport_byte_size) override {
      for (auto* tracer : tracers_) {
        tracer->RecordOutgoingBytes(transport_byte_size);
      }
    }
    void RecordAnnotation(absl::string_view annotation) override {
      for (auto* tracer : tracers_) {
        tracer->RecordAnnotation(annotation);
      }
    }
    void RecordAnnotation(const Annotation& annotation) override {
      for (auto* tracer : tracers_) {
        tracer->RecordAnnotation(annotation);
      }
    }
    std::shared_ptr<TcpCallTracer> StartNewTcpTrace() override {
      return nullptr;
    }
    void SetOptionalLabel(OptionalLabelKey key,
                          RefCountedStringValue value) override {
      for (auto* tracer : tracers_) {
        tracer->SetOptionalLabel(key, value);
      }
    }
    std::string TraceId() override { return tracers_[0]->TraceId(); }
    std::string SpanId() override { return tracers_[0]->SpanId(); }
    bool IsSampled() override { return tracers_[0]->IsSampled(); }
    bool IsDelegatingTracer() override { return true; }

   private:

    std::vector<CallAttemptTracer*> tracers_;
  };
  explicit DelegatingClientCallTracer(ClientCallTracer* tracer)
      : tracers_{tracer} {}
  ~DelegatingClientCallTracer() override {}
  CallAttemptTracer* StartNewAttempt(bool is_transparent_retry) override {
    std::vector<CallAttemptTracer*> attempt_tracers;
    attempt_tracers.reserve(tracers_.size());
    for (auto* tracer : tracers_) {
      auto* attempt_tracer = tracer->StartNewAttempt(is_transparent_retry);
      DCHECK_NE(attempt_tracer, nullptr);
      attempt_tracers.push_back(attempt_tracer);
    }
    return GetContext<Arena>()->ManagedNew<DelegatingClientCallAttemptTracer>(
        std::move(attempt_tracers));
  }

  void RecordAnnotation(absl::string_view annotation) override {
    for (auto* tracer : tracers_) {
      tracer->RecordAnnotation(annotation);
    }
  }
  void RecordAnnotation(const Annotation& annotation) override {
    for (auto* tracer : tracers_) {
      tracer->RecordAnnotation(annotation);
    }
  }
  std::string TraceId() override { return tracers_[0]->TraceId(); }
  std::string SpanId() override { return tracers_[0]->SpanId(); }
  bool IsSampled() override { return tracers_[0]->IsSampled(); }
  bool IsDelegatingTracer() override { return true; }

  void AddTracer(ClientCallTracer* tracer) { tracers_.push_back(tracer); }

 private:
  std::vector<ClientCallTracer*> tracers_;
};

class DelegatingServerCallTracer : public ServerCallTracer {
 public:
  explicit DelegatingServerCallTracer(ServerCallTracer* tracer)
      : tracers_{tracer} {}
  ~DelegatingServerCallTracer() override {}
  void RecordSendInitialMetadata(
      grpc_metadata_batch* send_initial_metadata) override {
    for (auto* tracer : tracers_) {
      tracer->RecordSendInitialMetadata(send_initial_metadata);
    }
  }
  void RecordSendTrailingMetadata(
      grpc_metadata_batch* send_trailing_metadata) override {
    for (auto* tracer : tracers_) {
      tracer->RecordSendTrailingMetadata(send_trailing_metadata);
    }
  }
  void RecordSendMessage(const Message& send_message) override {
    for (auto* tracer : tracers_) {
      tracer->RecordSendMessage(send_message);
    }
  }
  void RecordSendCompressedMessage(
      const Message& send_compressed_message) override {
    for (auto* tracer : tracers_) {
      tracer->RecordSendCompressedMessage(send_compressed_message);
    }
  }
  void RecordReceivedInitialMetadata(
      grpc_metadata_batch* recv_initial_metadata) override {
    for (auto* tracer : tracers_) {
      tracer->RecordReceivedInitialMetadata(recv_initial_metadata);
    }
  }
  void RecordReceivedMessage(const Message& recv_message) override {
    for (auto* tracer : tracers_) {
      tracer->RecordReceivedMessage(recv_message);
    }
  }
  void RecordReceivedDecompressedMessage(
      const Message& recv_decompressed_message) override {
    for (auto* tracer : tracers_) {
      tracer->RecordReceivedDecompressedMessage(recv_decompressed_message);
    }
  }
  void RecordCancel(grpc_error_handle cancel_error) override {
    for (auto* tracer : tracers_) {
      tracer->RecordCancel(cancel_error);
    }
  }
  void RecordReceivedTrailingMetadata(
      grpc_metadata_batch* recv_trailing_metadata) override {
    for (auto* tracer : tracers_) {
      tracer->RecordReceivedTrailingMetadata(recv_trailing_metadata);
    }
  }
  void RecordEnd(const grpc_call_final_info* final_info) override {
    for (auto* tracer : tracers_) {
      tracer->RecordEnd(final_info);
    }
  }
  void RecordIncomingBytes(
      const TransportByteSize& transport_byte_size) override {
    for (auto* tracer : tracers_) {
      tracer->RecordIncomingBytes(transport_byte_size);
    }
  }
  void RecordOutgoingBytes(
      const TransportByteSize& transport_byte_size) override {
    for (auto* tracer : tracers_) {
      tracer->RecordOutgoingBytes(transport_byte_size);
    }
  }
  void RecordAnnotation(absl::string_view annotation) override {
    for (auto* tracer : tracers_) {
      tracer->RecordAnnotation(annotation);
    }
  }
  void RecordAnnotation(const Annotation& annotation) override {
    for (auto* tracer : tracers_) {
      tracer->RecordAnnotation(annotation);
    }
  }
  std::shared_ptr<TcpCallTracer> StartNewTcpTrace() override { return nullptr; }
  std::string TraceId() override { return tracers_[0]->TraceId(); }
  std::string SpanId() override { return tracers_[0]->SpanId(); }
  bool IsSampled() override { return tracers_[0]->IsSampled(); }
  bool IsDelegatingTracer() override { return true; }

  void AddTracer(ServerCallTracer* tracer) { tracers_.push_back(tracer); }

 private:

  std::vector<ServerCallTracer*> tracers_;
};

void AddClientCallTracerToContext(Arena* arena, ClientCallTracer* tracer) {
  if (arena->GetContext<CallTracerAnnotationInterface>() == nullptr) {

    arena->SetContext<CallTracerAnnotationInterface>(tracer);
  } else {

    auto* orig_tracer = DownCast<ClientCallTracer*>(
        arena->GetContext<CallTracerAnnotationInterface>());
    if (orig_tracer->IsDelegatingTracer()) {

      DownCast<DelegatingClientCallTracer*>(orig_tracer)->AddTracer(tracer);
    } else {

      auto* delegating_tracer =
          GetContext<Arena>()->ManagedNew<DelegatingClientCallTracer>(
              orig_tracer);
      arena->SetContext<CallTracerAnnotationInterface>(delegating_tracer);
      delegating_tracer->AddTracer(tracer);
    }
  }
}

void AddServerCallTracerToContext(Arena* arena, ServerCallTracer* tracer) {
  DCHECK_EQ(arena->GetContext<CallTracerInterface>(),
            arena->GetContext<CallTracerAnnotationInterface>());
  if (arena->GetContext<CallTracerAnnotationInterface>() == nullptr) {

    arena->SetContext<CallTracerAnnotationInterface>(tracer);
    arena->SetContext<CallTracerInterface>(tracer);
  } else {

    auto* orig_tracer = DownCast<ServerCallTracer*>(
        arena->GetContext<CallTracerAnnotationInterface>());
    if (orig_tracer->IsDelegatingTracer()) {

      DownCast<DelegatingServerCallTracer*>(orig_tracer)->AddTracer(tracer);
    } else {

      auto* delegating_tracer =
          GetContext<Arena>()->ManagedNew<DelegatingServerCallTracer>(
              orig_tracer);
      arena->SetContext<CallTracerAnnotationInterface>(delegating_tracer);
      arena->SetContext<CallTracerInterface>(delegating_tracer);
      delegating_tracer->AddTracer(tracer);
    }
  }
}

}
