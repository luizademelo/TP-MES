
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SYNC_STREAM_H
#define GRPCPP_SUPPORT_SYNC_STREAM_H

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

class ClientStreamingInterface {
 public:
  virtual ~ClientStreamingInterface() {}

  virtual grpc::Status Finish() = 0;
};

class ServerStreamingInterface {
 public:
  virtual ~ServerStreamingInterface() {}

  virtual void SendInitialMetadata() = 0;
};

template <class R>
class ReaderInterface {
 public:
  virtual ~ReaderInterface() {}

  virtual bool NextMessageSize(uint32_t* sz) = 0;

  virtual bool Read(R* msg) = 0;
};

template <class W>
class WriterInterface {
 public:
  virtual ~WriterInterface() {}

  virtual bool Write(const W& msg, grpc::WriteOptions options) = 0;

  inline bool Write(const W& msg) { return Write(msg, grpc::WriteOptions()); }

  void WriteLast(const W& msg, grpc::WriteOptions options) {
    Write(msg, options.set_last_message());
  }
};

}

template <class R>
class ClientReaderInterface : public internal::ClientStreamingInterface,
                              public internal::ReaderInterface<R> {
 public:

  virtual void WaitForInitialMetadata() = 0;
};

namespace internal {
template <class R>
class ClientReaderFactory {
 public:
  template <class W>
  static ClientReader<R>* Create(grpc::ChannelInterface* channel,
                                 const grpc::internal::RpcMethod& method,
                                 grpc::ClientContext* context,
                                 const W& request) {
    return new ClientReader<R>(channel, method, context, request);
  }
};
}

template <class R>
class ClientReader final : public ClientReaderInterface<R> {
 public:

  void WaitForInitialMetadata() override {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  bool NextMessageSize(uint32_t* sz) override {
    int result = call_.max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

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

  template <class W>
  ClientReader(grpc::ChannelInterface* channel,
               const grpc::internal::RpcMethod& method,
               grpc::ClientContext* context, const W& request)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
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

template <class W>
class ClientWriterInterface : public internal::ClientStreamingInterface,
                              public internal::WriterInterface<W> {
 public:

  virtual bool WritesDone() = 0;
};

namespace internal {
template <class W>
class ClientWriterFactory {
 public:
  template <class R>
  static ClientWriter<W>* Create(grpc::ChannelInterface* channel,
                                 const grpc::internal::RpcMethod& method,
                                 grpc::ClientContext* context, R* response) {
    return new ClientWriter<W>(channel, method, context, response);
  }
};
}

template <class W>
class ClientWriter : public ClientWriterInterface<W> {
 public:

  void WaitForInitialMetadata() {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  using internal::WriterInterface<W>::Write;
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

  bool WritesDone() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpClientSendClose> ops;
    ops.ClientSendClose();
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

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

  template <class R>
  ClientWriter(grpc::ChannelInterface* channel,
               const grpc::internal::RpcMethod& method,
               grpc::ClientContext* context, R* response)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
    finish_ops_.RecvMessage(response);
    finish_ops_.AllowNoMessage();

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

template <class W, class R>
class ClientReaderWriterInterface : public internal::ClientStreamingInterface,
                                    public internal::WriterInterface<W>,
                                    public internal::ReaderInterface<R> {
 public:

  virtual void WaitForInitialMetadata() = 0;

  virtual bool WritesDone() = 0;
};

namespace internal {
template <class W, class R>
class ClientReaderWriterFactory {
 public:
  static ClientReaderWriter<W, R>* Create(
      grpc::ChannelInterface* channel, const grpc::internal::RpcMethod& method,
      grpc::ClientContext* context) {
    return new ClientReaderWriter<W, R>(channel, method, context);
  }
};
}

template <class W, class R>
class ClientReaderWriter final : public ClientReaderWriterInterface<W, R> {
 public:

  void WaitForInitialMetadata() override {
    ABSL_CHECK(!context_->initial_metadata_received_);

    grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata> ops;
    ops.RecvInitialMetadata(context_);
    call_.PerformOps(&ops);
    cq_.Pluck(&ops);
  }

  bool NextMessageSize(uint32_t* sz) override {
    int result = call_.max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

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

  bool WritesDone() override {
    grpc::internal::CallOpSet<grpc::internal::CallOpClientSendClose> ops;
    ops.ClientSendClose();
    call_.PerformOps(&ops);
    return cq_.Pluck(&ops);
  }

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

  ClientReaderWriter(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context)
      : context_(context),
        cq_(grpc_completion_queue_attributes{
            GRPC_CQ_CURRENT_VERSION, GRPC_CQ_PLUCK, GRPC_CQ_DEFAULT_POLLING,
            nullptr}),
        call_(channel->CreateCall(method, context, &cq_)) {
    if (!context_->initial_metadata_corked_) {
      grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata> ops;
      ops.SendInitialMetadata(&context->send_initial_metadata_,
                              context->initial_metadata_flags());
      call_.PerformOps(&ops);
      cq_.Pluck(&ops);
    }
  }
};

template <class R>
class ServerReaderInterface : public internal::ServerStreamingInterface,
                              public internal::ReaderInterface<R> {};

template <class R>
class ServerReader final : public ServerReaderInterface<R> {
 public:

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

  bool NextMessageSize(uint32_t* sz) override {
    int result = call_->max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

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

  ServerReader(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : call_(call), ctx_(ctx) {}
};

template <class W>
class ServerWriterInterface : public internal::ServerStreamingInterface,
                              public internal::WriterInterface<W> {};

template <class W>
class ServerWriter final : public ServerWriterInterface<W> {
 public:

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

  using internal::WriterInterface<W>::Write;
  bool Write(const W& msg, grpc::WriteOptions options) override {
    if (options.is_last_message()) {
      options.set_buffer_hint();
    }

    if (!ctx_->pending_ops_.SendMessagePtr(&msg, options).ok()) {
      return false;
    }
    if (!ctx_->sent_initial_metadata_) {
      ctx_->pending_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                             ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        ctx_->pending_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
    call_->PerformOps(&ctx_->pending_ops_);

    if (options.is_last_message()) {
      ctx_->has_pending_ops_ = true;
      return true;
    }
    ctx_->has_pending_ops_ = false;
    return call_->cq()->Pluck(&ctx_->pending_ops_);
  }

 private:
  grpc::internal::Call* const call_;
  grpc::ServerContext* const ctx_;

  template <class ServiceType, class RequestType, class ResponseType>
  friend class internal::ServerStreamingHandler;

  ServerWriter(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : call_(call), ctx_(ctx) {}
};

template <class W, class R>
class ServerReaderWriterInterface : public internal::ServerStreamingInterface,
                                    public internal::WriterInterface<W>,
                                    public internal::ReaderInterface<R> {};

namespace internal {
template <class W, class R>
class ServerReaderWriterBody final {
 public:
  ServerReaderWriterBody(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : call_(call), ctx_(ctx) {}

  void SendInitialMetadata() {
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

  bool NextMessageSize(uint32_t* sz) {
    int result = call_->max_receive_message_size();
    *sz = (result > 0) ? result : UINT32_MAX;
    return true;
  }

  bool Read(R* msg) {
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<R>> ops;
    ops.RecvMessage(msg);
    call_->PerformOps(&ops);
    bool ok = call_->cq()->Pluck(&ops) && ops.got_message;
    if (!ok) {
      ctx_->MaybeMarkCancelledOnRead();
    }
    return ok;
  }

  bool Write(const W& msg, grpc::WriteOptions options) {
    if (options.is_last_message()) {
      options.set_buffer_hint();
    }
    if (!ctx_->pending_ops_.SendMessagePtr(&msg, options).ok()) {
      return false;
    }
    if (!ctx_->sent_initial_metadata_) {
      ctx_->pending_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                             ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        ctx_->pending_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
    call_->PerformOps(&ctx_->pending_ops_);

    if (options.is_last_message()) {
      ctx_->has_pending_ops_ = true;
      return true;
    }
    ctx_->has_pending_ops_ = false;
    return call_->cq()->Pluck(&ctx_->pending_ops_);
  }

 private:
  grpc::internal::Call* const call_;
  grpc::ServerContext* const ctx_;
};

}

template <class W, class R>
class ServerReaderWriter final : public ServerReaderWriterInterface<W, R> {
 public:

  void SendInitialMetadata() override { body_.SendInitialMetadata(); }

  bool NextMessageSize(uint32_t* sz) override {
    return body_.NextMessageSize(sz);
  }

  bool Read(R* msg) override { return body_.Read(msg); }

  using internal::WriterInterface<W>::Write;
  bool Write(const W& msg, grpc::WriteOptions options) override {
    return body_.Write(msg, options);
  }

 private:
  internal::ServerReaderWriterBody<W, R> body_;

  friend class internal::TemplatedBidiStreamingHandler<ServerReaderWriter<W, R>,
                                                       false>;
  ServerReaderWriter(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : body_(call, ctx) {}
};

template <class RequestType, class ResponseType>
class ServerUnaryStreamer final
    : public ServerReaderWriterInterface<ResponseType, RequestType> {
 public:

  void SendInitialMetadata() override { body_.SendInitialMetadata(); }

  bool NextMessageSize(uint32_t* sz) override {
    return body_.NextMessageSize(sz);
  }

  bool Read(RequestType* request) override {
    if (read_done_) {
      return false;
    }
    read_done_ = true;
    return body_.Read(request);
  }

  using internal::WriterInterface<ResponseType>::Write;
  bool Write(const ResponseType& response,
             grpc::WriteOptions options) override {
    if (write_done_ || !read_done_) {
      return false;
    }
    write_done_ = true;
    return body_.Write(response, options);
  }

 private:
  internal::ServerReaderWriterBody<ResponseType, RequestType> body_;
  bool read_done_;
  bool write_done_;

  friend class internal::TemplatedBidiStreamingHandler<
      ServerUnaryStreamer<RequestType, ResponseType>, true>;
  ServerUnaryStreamer(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : body_(call, ctx), read_done_(false), write_done_(false) {}
};

template <class RequestType, class ResponseType>
class ServerSplitStreamer final
    : public ServerReaderWriterInterface<ResponseType, RequestType> {
 public:

  void SendInitialMetadata() override { body_.SendInitialMetadata(); }

  bool NextMessageSize(uint32_t* sz) override {
    return body_.NextMessageSize(sz);
  }

  bool Read(RequestType* request) override {
    if (read_done_) {
      return false;
    }
    read_done_ = true;
    return body_.Read(request);
  }

  using internal::WriterInterface<ResponseType>::Write;
  bool Write(const ResponseType& response,
             grpc::WriteOptions options) override {
    return read_done_ && body_.Write(response, options);
  }

 private:
  internal::ServerReaderWriterBody<ResponseType, RequestType> body_;
  bool read_done_;

  friend class internal::TemplatedBidiStreamingHandler<
      ServerSplitStreamer<RequestType, ResponseType>, false>;
  ServerSplitStreamer(grpc::internal::Call* call, grpc::ServerContext* ctx)
      : body_(call, ctx), read_done_(false) {}
};

}

#endif
