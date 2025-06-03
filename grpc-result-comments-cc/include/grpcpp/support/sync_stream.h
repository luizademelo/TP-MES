Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SYNC_STREAM_H
#define GRPCPP_SUPPORT_SYNC_STREAM_H

// Include necessary headers for gRPC functionality
#include <grpcpp/client_context.h>
#include <grpcpp/completion_queue.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "absl/log/absl_check.h"

namespace grpc {

namespace internal {

// Interface for client-side streaming operations
class ClientStreamingInterface {
 public:
  virtual ~ClientStreamingInterface() {}

  // Finalizes the client streaming call and returns the status
  virtual grpc::Status Finish() = 0;
};

// Interface for server-side streaming operations
class ServerStreamingInterface {
 public:
  virtual ~ServerStreamingInterface() {}

  // Sends initial metadata to the client
  virtual void SendInitialMetadata() = 0;
};

// Interface for reading messages from a stream
template <class R>
class ReaderInterface {
 public:
  virtual ~ReaderInterface() {}

  // Gets the size of the next message
  virtual bool NextMessageSize(uint32_t* sz) = 0;

  // Reads a message from the stream
  virtual bool Read(R* msg) = 0;
};

// Interface for writing messages to a stream
template <class W>
class WriterInterface {
 public:
  virtual ~WriterInterface() {}

  // Writes a message to the stream with options
  virtual bool Write(const W& msg, grpc::WriteOptions options) = 0;

  // Writes a message to the stream with default options
  inline bool Write(const W& msg) { return Write(msg, grpc::WriteOptions()); }

  // Writes the last message to the stream with options
  void WriteLast(const W& msg, grpc::WriteOptions options) {
    Write(msg, options.set_last_message());
  }
};

}  // namespace internal

// Interface for client-side stream reading
template <class R>
class ClientReaderInterface : public internal::ClientStreamingInterface,
                              public internal::ReaderInterface<R> {
 public:
  // Waits for the server to send initial metadata
  virtual void WaitForInitialMetadata() = 0;
};

namespace internal {
// Factory for creating ClientReader instances
template <class R>
class ClientReaderFactory {
 public:
  // Creates a new ClientReader instance
  template <class W>
  static ClientReader<R>* Create(grpc::ChannelInterface* channel,
                                 const grpc::internal::RpcMethod& method,
                                 grpc::ClientContext* context,
                                 const W& request) {
    return new ClientReader<R>(channel, method, context, request);
  }
};
}  // namespace internal

// Implementation of client-side stream reading
template <class R>
class ClientReader final : public ClientReaderInterface<R> {
 public:
  // Waits for initial metadata from the server
  void WaitForInitialMetadata() override {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  // Gets the size of the next message
  bool NextMessageSize(uint32_t* sz) override {
    int result = call_.max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

  // Reads a message from the stream
  bool Read(R* msg) override {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                              grpc::internal::CallOpRecvMessage<R>>
        ops;
    if (!context_->initial_metadata_received_) {
      ops.RecvInitialMetadata(context_);
    }
    ops.RecvMessage(msg);
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops) && ops.got_message;
  }

  // Finishes the client streaming call
  grpc::Status Finish() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                              grpc::internal::CallOpClientRecvStatus>
        ops;
    if (!context_->initial_metadata_received_) {
      ops.RecvInitialMetadata(context_);
    }
    grpc::Status status;
    ops.ClientRecvStatus(context_, &status);
    call_.PerformOps(&ops);
    ABSL_CHECK(cq_.Pluck(&ops));
    return status;
  }

 private:
  friend class internal::ClientReaderFactory<R>;
  grpc::ClientContext* context_;
  grpc::CompletionQueue cq_;
  grpc::internal::Call call_;

  // Constructor for ClientReader
  template <class W>
  ClientReader(grpc::ChannelInterface* channel,
               const grpc::internal::RpcMethod& method,
               grpc::ClientContext* context, const W& request)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
    // Set up and perform initial call operations
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpClientSendClose>
        ops;
    ops.SendInitialMetadata(&context->send_initial_metadata_,
                            context->initial_metadata_flags());

    ABSL_CHECK(ops.SendMessagePtr(&request).ok());
    ops.ClientSendClose();
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }
};

// Interface for client-side stream writing
template <class W>
class ClientWriterInterface : public internal::ClientStreamingInterface,
                              public internal::WriterInterface<W> {
 public:
  // Indicates that no more writes will be made to the stream
  virtual bool WritesDone() = 0;
};

namespace internal {
// Factory for creating ClientWriter instances
template <class W>
class ClientWriterFactory {
 public:
  // Creates a new ClientWriter instance
  template <class R>
  static ClientWriter<W>* Create(grpc::ChannelInterface* channel,
                                 const grpc::internal::RpcMethod& method,
                                 grpc::ClientContext* context, R* response) {
    return new ClientWriter<W>(channel, method, context, response);
  }
};
}  // namespace internal

// Implementation of client-side stream writing
template <class W>
class ClientWriter : public ClientWriterInterface<W> {
 public:
  // Waits for initial metadata from the server
  void WaitForInitialMetadata() {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  using internal::WriterInterface<W>::Write;
  // Writes a message to the stream with options
  bool Write(const W& msg, grpc::WriteOptions options) override {
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpClientSendClose>
        ops;

    if (options.is_last_message()) {
      options.set_buffer_hint();
      ops.ClientSendClose();
    }
    if (context_->initial_metadata_corked_) {
      ops.SendInitialMetadata(&context_->send_initial_metadata_,
                              context_->initial_metadata_flags());
      context_->set_initial_metadata_corked(false);
    }
    if (!ops.SendMessagePtr(&msg, options).ok()) {
      return false;
    }

    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

  // Indicates that no more writes will be made to the stream
  bool WritesDone() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpClientSendClose> ops;
    ops.ClientSendClose();
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

  // Finishes the client streaming call
  grpc::Status Finish() override {
    grpc::Status status;
    if (!context_->initial_metadata_received_) {
      finish_ops_.RecvInitialMetadata(context_);
    }
    finish_ops_.ClientRecvStatus(context_, &status);
    call_.PerformOps(&finish_ops_);
    ABSL_CHECK(cq_.Pluck(&finish_ops_));
    return status;
  }

 private:
  friend class internal::ClientWriterFactory<W>;

  // Constructor for ClientWriter
  template <class R>
  ClientWriter(grpc::ChannelInterface* channel,
               const grpc::internal::RpcMethod& method,
               grpc::ClientContext* context, R* response)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
    // Set up finish operations
    finish_ops_.RecvMessage(response);
    finish_ops_.AllowNoMessage();

    // Send initial metadata if not corked
    if (!context_->initial_metadata_corked_) {
      grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata> ops;
      ops.SendInitialMetadata(&context->send_initial_metadata_,
                              context->initial_metadata_flags());
      call_.PerformOps(&ops);
      cq_.Pluck(&ops);
    }
  }

  grpc::ClientContext* context_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpGenericRecvMessage,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
  grpc::CompletionQueue cq_;
  grpc::internal::Call call_;
};

// Interface for bidirectional client-side streaming
template <class W, class R>
class ClientReaderWriterInterface : public internal::ClientStreamingInterface,
                                    public internal::WriterInterface<W>,
                                    public internal::ReaderInterface<R> {
 public:
  // Waits for the server to send initial metadata
  virtual void WaitForInitialMetadata() = 0;

  // Indicates that no more writes will be made to the stream
  virtual bool WritesDone() = 0;
};

namespace internal {
// Factory for creating ClientReaderWriter instances
template <class W, class R>
class ClientReaderWriterFactory {
 public:
  // Creates a new ClientReaderWriter instance
  static ClientReaderWriter<W, R>* Create(
      grpc::ChannelInterface* channel, const grpc::internal::RpcMethod& method,
      grpc::ClientContext* context) {
    return new ClientReaderWriter<W, R>(channel, method, context);
  }
};
}  // namespace internal

// Implementation of bidirectional client-side streaming
template <class W, class R>
class ClientReaderWriter final : public ClientReaderWriterInterface<W, R> {
 public:
  // Waits for initial metadata from the server
  void WaitForInitialMetadata() override {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  // Gets the size of the next message
  bool NextMessageSize(uint32_t* sz) override {
    int result = call_.max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

  // Reads a message from the stream
  bool Read(R* msg) override {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                              grpc::internal::CallOpRecvMessage<R>>
        ops;
    if (!context_->initial_metadata_received_) {
      ops.RecvInitialMetadata(context_);
    }
    ops.RecvMessage(msg);
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops) && ops.got_message;
  }

  using internal::WriterInterface<W>::Write;
  // Writes a message to the stream with options
  bool Write(const W& msg, grpc::WriteOptions options) override {
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpClientSendClose>
        ops;

    if (options.is_last_message()) {
      options.set_buffer_hint();
      ops.ClientSendClose();
    }
    if (context_->initial_metadata_corked_) {
      ops.SendInitialMetadata(&context_->send_initial_metadata_,
                              context_->initial_metadata_flags());
      context_->set_initial_metadata_corked(false);
    }
    if (!ops.SendMessagePtr(&msg, options).ok()) {
      return false;
    }

    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

  // Indicates that no more writes will be made to the stream
  bool WritesDone() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpClientSendClose> ops;
    ops.ClientSendClose();
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

  // Finishes the client streaming call
  grpc::Status Finish() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                              grpc::internal::CallOpClientRecvStatus>
        ops;
    if (!context_->initial_metadata_received_) {
      ops.RecvInitialMetadata(context_);
    }
    grpc::Status status;
    ops.ClientRecvStatus(context_, &status);
    call_.PerformOps(&ops);
    ABSL_CHECK(cq_.Pluck(&ops));
    return status;
  }

 private:
  friend class internal::ClientReaderWriterFactory<W, R>;

  grpc::ClientContext* context_;
  grpc::CompletionQueue cq_;
  grpc::internal::Call call_;

  // Constructor for ClientReaderWriter
  ClientReaderWriter(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
    // Send initial metadata if not corked
    if (!context_->initial_metadata_corked_) {
      grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata> ops;
      ops.SendInitialMetadata(&context->send_initial_metadata_,
                              context->initial_metadata_flags());
      call_.PerformOps(&ops);
      cq_.Pluck(&ops);
    }
  }
};

// Interface for server-side stream reading
template <class R>
class ServerReaderInterface : public internal::ServerStreamingInterface,
                              public internal::ReaderInterface<R> {};

// Implementation of server-side stream reading
template <class R>
class ServerReader final : public ServerReaderInterface<R> {
 public:
  // Sends initial metadata to the client
  void SendInitialMetadata() override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata> ops;
    ops.SendInitialMetadata(&ctx_->initial_metadata_,
                            ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      ops.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_->PerformOps(&ops);
    call_->cq()->Pluck(&ops);
  }

  // Gets the size of the next message
  bool NextMessageSize(uint32_t* sz) override {
    int result = call_->max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

  // Reads a message from the stream
  bool Read(R* msg) override {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<R>> ops;
    ops.RecvMessage(msg);
    call_->PerformOps(&ops);
    bool ok = call_->cq()->Pluck(&ops) && ops.got_message;
    if (!ok) {
      ctx_->MaybeMarkCancelledOnRead();
    }
    return ok;
  }

 private:
  grpc::internal::Call* const call_;
  ServerContext* const ctx_;

  template <class ServiceType, class RequestType, class ResponseType>
  friend class internal::ClientStreamingHandler;

  // Constructor for ServerReader
  ServerReader(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : call_(call), ctx_(ctx) {}
};

// Interface for server-side stream writing
template <class W>
class ServerWriterInterface : public internal::ServerStreamingInterface,
                              public internal::WriterInterface<W> {};

// Implementation of server-side stream writing
template <class W>
class ServerWriter final : public ServerWriterInterface<W> {
 public:
  // Sends initial metadata to the client
  void SendInitialMetadata() override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata> ops;
    ops.SendInitialMetadata(&ctx_->initial_metadata_,
                            ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      ops.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_->PerformOps