
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CORE_TELEMETRY_CALL_TRACER_H
#define GRPC_SRC_CORE_TELEMETRY_CALL_TRACER_H

#include <grpc/support/port_platform.h>
#include <grpc/support/time.h>

#include <memory>
#include <optional>
#include <string>

#include "absl/status/status.h"
#include "absl/strings/string_view.h"
#include "src/core/call/message.h"
#include "src/core/call/metadata_batch.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/promise/context.h"
#include "src/core/lib/resource_quota/arena.h"
#include "src/core/lib/slice/slice_buffer.h"
#include "src/core/lib/transport/call_final_info.h"
#include "src/core/telemetry/tcp_tracer.h"
#include "src/core/util/ref_counted_string.h"

namespace grpc_core {

class CallTracerAnnotationInterface {
 public:

  enum class AnnotationType {
    kMetadataSizes,
    kHttpTransport,
    kDoNotUse_MustBeLast,
  };

  class Annotation {
   public:
    explicit Annotation(AnnotationType type) : type_(type) {}
    AnnotationType type() const { return type_; }
    virtual std::string ToString() const = 0;
    virtual ~Annotation() = default;

   private:
    const AnnotationType type_;
  };

  virtual ~CallTracerAnnotationInterface() {}

  virtual void RecordAnnotation(absl::string_view annotation) = 0;
  virtual void RecordAnnotation(const Annotation& annotation) = 0;
  virtual std::string TraceId() = 0;
  virtual std::string SpanId() = 0;
  virtual bool IsSampled() = 0;

  virtual bool IsDelegatingTracer() { return false; }
};

class CallTracerInterface : public CallTracerAnnotationInterface {
 public:
  ~CallTracerInterface() override {}

  virtual void RecordSendInitialMetadata(
      grpc_metadata_batch* send_initial_metadata) = 0;
  virtual void RecordSendTrailingMetadata(
      grpc_metadata_batch* send_trailing_metadata) = 0;
  virtual void RecordSendMessage(const Message& send_message) = 0;

  virtual void RecordSendCompressedMessage(
      const Message& send_compressed_message) = 0;

  virtual void RecordReceivedInitialMetadata(
      grpc_metadata_batch* recv_initial_metadata) = 0;
  virtual void RecordReceivedMessage(const Message& recv_message) = 0;

  virtual void RecordReceivedDecompressedMessage(
      const Message& recv_decompressed_message) = 0;
  virtual void RecordCancel(grpc_error_handle cancel_error) = 0;

  struct TransportByteSize {
    uint64_t framing_bytes = 0;
    uint64_t data_bytes = 0;
    uint64_t header_bytes = 0;

    TransportByteSize& operator+=(const TransportByteSize& other);
  };
  virtual void RecordIncomingBytes(
      const TransportByteSize& transport_byte_size) = 0;
  virtual void RecordOutgoingBytes(
      const TransportByteSize& transport_byte_size) = 0;

  virtual std::shared_ptr<TcpCallTracer> StartNewTcpTrace() = 0;
};

class ClientCallTracer : public CallTracerAnnotationInterface {
 public:

  class CallAttemptTracer : public CallTracerInterface {
   public:

    enum class OptionalLabelKey : std::uint8_t {
      kXdsServiceName,
      kXdsServiceNamespace,
      kLocality,
      kSize
    };

    ~CallAttemptTracer() override {}

    virtual void RecordReceivedTrailingMetadata(
        absl::Status status, grpc_metadata_batch* recv_trailing_metadata,

        const grpc_transport_stream_stats* transport_stream_stats) = 0;

    virtual void RecordEnd() = 0;

    virtual void SetOptionalLabel(OptionalLabelKey key,
                                  RefCountedStringValue value) = 0;
  };

  ~ClientCallTracer() override {}

  virtual CallAttemptTracer* StartNewAttempt(bool is_transparent_retry) = 0;
};

class ServerCallTracer : public CallTracerInterface {
 public:
  ~ServerCallTracer() override {}

  virtual void RecordReceivedTrailingMetadata(
      grpc_metadata_batch* recv_trailing_metadata) = 0;

  virtual void RecordEnd(const grpc_call_final_info* final_info) = 0;
};

class ServerCallTracerFactory {
 public:
  struct RawPointerChannelArgTag {};

  virtual ~ServerCallTracerFactory() {}

  virtual ServerCallTracer* CreateNewServerCallTracer(
      Arena* arena, const ChannelArgs& channel_args) = 0;

  virtual bool IsServerTraced(const ChannelArgs& ) { return true; }

  static ServerCallTracerFactory* Get(const ChannelArgs& channel_args);

  static void RegisterGlobal(ServerCallTracerFactory* factory);

  static void TestOnlyReset();

  static absl::string_view ChannelArgName();
};

void AddClientCallTracerToContext(Arena* arena, ClientCallTracer* tracer);

void AddServerCallTracerToContext(Arena* arena, ServerCallTracer* tracer);

template <>
struct ArenaContextType<CallTracerInterface> {
  static void Destroy(CallTracerAnnotationInterface*) {}
};

template <>
struct ArenaContextType<CallTracerAnnotationInterface> {
  static void Destroy(CallTracerAnnotationInterface*) {}
};

template <>
struct ContextSubclass<ClientCallTracer::CallAttemptTracer> {
  using Base = CallTracerInterface;
};

template <>
struct ContextSubclass<ServerCallTracer> {
  using Base = CallTracerInterface;
};

template <>
struct ContextSubclass<ClientCallTracer> {
  using Base = CallTracerAnnotationInterface;
};

}

#endif
