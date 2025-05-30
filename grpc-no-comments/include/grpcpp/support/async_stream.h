
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_ASYNC_STREAM_H
#define GRPCPP_SUPPORT_ASYNC_STREAM_H

#include <grpc/grpc.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "absl/log/absl_check.h"

namespace grpc {

namespace internal {

class ClientAsyncStreamingInterface {
 public:
  virtual ~ClientAsyncStreamingInterface() {}

  virtual void StartCall(void* tag) = 0;

  virtual void ReadInitialMetadata(void* tag) = 0;

  virtual void Finish(grpc::Status* status, void* tag) = 0;
};

template <class R>
class AsyncReaderInterface {
 public:
  virtual ~AsyncReaderInterface() {}

  virtual void Read(R* msg, void* tag) = 0;
};

template <class W>
class AsyncWriterInterface {
 public:
  virtual ~AsyncWriterInterface() {}

  virtual void Write(const W& msg, void* tag) = 0;

  virtual void Write(const W& msg, grpc::WriteOptions options, void* tag) = 0;

  void WriteLast(const W& msg, grpc::WriteOptions options, void* tag) {
    Write(msg, options.set_last_message(), tag);
  }
};

}

template <class R>
class ClientAsyncReaderInterface
    : public internal::ClientAsyncStreamingInterface,
      public internal::AsyncReaderInterface<R> {};

namespace internal {
template <class R>
class ClientAsyncReaderFactory {
 public:

  template <class W>
  static ClientAsyncReader<R>* Create(grpc::ChannelInterface* channel,
                                      grpc::CompletionQueue* cq,
                                      const grpc::internal::RpcMethod& method,
                                      grpc::ClientContext* context,
                                      const W& request, bool start, void* tag) {
    grpc::internal::Call call = channel->CreateCall(method, context, cq);
    return new (
        grpc_call_arena_alloc(call.call(), sizeof(ClientAsyncReader<R>)))
        ClientAsyncReader<R>(call, context, request, start, tag);
  }
};
}

template <class R>
class ClientAsyncReader final : public ClientAsyncReaderInterface<R> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientAsyncReader));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall(void* tag) override {
    ABSL_CHECK(!started_);
    started_ = true;
    StartCallInternal(tag);
  }

  void ReadInitialMetadata(void* tag) override {
    ABSL_CHECK(started_);
    ABSL_CHECK(!context_->initial_metadata_received_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.RecvInitialMetadata(context_);
    call_.PerformOps(&meta_ops_);
  }

  void Read(R* msg, void* tag) override {
    ABSL_CHECK(started_);
    read_ops_.set_output_tag(tag);
    if (!context_->initial_metadata_received_) {
      read_ops_.RecvInitialMetadata(context_);
    }
    read_ops_.RecvMessage(msg);
    call_.PerformOps(&read_ops_);
  }

  void Finish(grpc::Status* status, void* tag) override {
    ABSL_CHECK(started_);
    finish_ops_.set_output_tag(tag);
    if (!context_->initial_metadata_received_) {
      finish_ops_.RecvInitialMetadata(context_);
    }
    finish_ops_.ClientRecvStatus(context_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  friend class internal::ClientAsyncReaderFactory<R>;
  template <class W>
  ClientAsyncReader(grpc::internal::Call call, grpc::ClientContext* context,
                    const W& request, bool start, void* tag)
      : context_(context), call_(call), started_(start) {

    ABSL_CHECK(init_ops_.SendMessage(request).ok());
    init_ops_.ClientSendClose();
    if (start) {
      StartCallInternal(tag);
    } else {
      ABSL_CHECK(tag == nullptr);
    }
  }

  void StartCallInternal(void* tag) {
    init_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                  context_->initial_metadata_flags());
    init_ops_.set_output_tag(tag);
    call_.PerformOps(&init_ops_);
  }

  grpc::ClientContext* context_;
  grpc::internal::Call call_;
  bool started_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose>
      init_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpRecvMessage<R>>
      read_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
};

template <class W>
class ClientAsyncWriterInterface
    : public internal::ClientAsyncStreamingInterface,
      public internal::AsyncWriterInterface<W> {
 public:

  virtual void WritesDone(void* tag) = 0;
};

namespace internal {
template <class W>
class ClientAsyncWriterFactory {
 public:

  template <class R>
  static ClientAsyncWriter<W>* Create(grpc::ChannelInterface* channel,
                                      grpc::CompletionQueue* cq,
                                      const grpc::internal::RpcMethod& method,
                                      grpc::ClientContext* context, R* response,
                                      bool start, void* tag) {
    grpc::internal::Call call = channel->CreateCall(method, context, cq);
    return new (
        grpc_call_arena_alloc(call.call(), sizeof(ClientAsyncWriter<W>)))
        ClientAsyncWriter<W>(call, context, response, start, tag);
  }
};
}

template <class W>
class ClientAsyncWriter final : public ClientAsyncWriterInterface<W> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientAsyncWriter));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall(void* tag) override {
    ABSL_CHECK(!started_);
    started_ = true;
    StartCallInternal(tag);
  }

  void ReadInitialMetadata(void* tag) override {
    ABSL_CHECK(started_);
    ABSL_CHECK(!context_->initial_metadata_received_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.RecvInitialMetadata(context_);
    call_.PerformOps(&meta_ops_);
  }

  void Write(const W& msg, void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);

    ABSL_CHECK(write_ops_.SendMessage(msg).ok());
    call_.PerformOps(&write_ops_);
  }

  void Write(const W& msg, grpc::WriteOptions options, void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);
    if (options.is_last_message()) {
      options.set_buffer_hint();
      write_ops_.ClientSendClose();
    }

    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    call_.PerformOps(&write_ops_);
  }

  void WritesDone(void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);
    write_ops_.ClientSendClose();
    call_.PerformOps(&write_ops_);
  }

  void Finish(grpc::Status* status, void* tag) override {
    ABSL_CHECK(started_);
    finish_ops_.set_output_tag(tag);
    if (!context_->initial_metadata_received_) {
      finish_ops_.RecvInitialMetadata(context_);
    }
    finish_ops_.ClientRecvStatus(context_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  friend class internal::ClientAsyncWriterFactory<W>;
  template <class R>
  ClientAsyncWriter(grpc::internal::Call call, grpc::ClientContext* context,
                    R* response, bool start, void* tag)
      : context_(context), call_(call), started_(start) {
    finish_ops_.RecvMessage(response);
    finish_ops_.AllowNoMessage();
    if (start) {
      StartCallInternal(tag);
    } else {
      ABSL_CHECK(tag == nullptr);
    }
  }

  void StartCallInternal(void* tag) {
    write_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                   context_->initial_metadata_flags());

    if (!context_->initial_metadata_corked_) {
      write_ops_.set_output_tag(tag);
      call_.PerformOps(&write_ops_);
    }
  }

  grpc::ClientContext* context_;
  grpc::internal::Call call_;
  bool started_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose>
      write_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpGenericRecvMessage,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
};

template <class W, class R>
class ClientAsyncReaderWriterInterface
    : public internal::ClientAsyncStreamingInterface,
      public internal::AsyncWriterInterface<W>,
      public internal::AsyncReaderInterface<R> {
 public:

  virtual void WritesDone(void* tag) = 0;
};

namespace internal {
template <class W, class R>
class ClientAsyncReaderWriterFactory {
 public:

  static ClientAsyncReaderWriter<W, R>* Create(
      grpc::ChannelInterface* channel, grpc::CompletionQueue* cq,
      const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
      bool start, void* tag) {
    grpc::internal::Call call = channel->CreateCall(method, context, cq);

    return new (grpc_call_arena_alloc(call.call(),
                                      sizeof(ClientAsyncReaderWriter<W, R>)))
        ClientAsyncReaderWriter<W, R>(call, context, start, tag);
  }
};
}

template <class W, class R>
class ClientAsyncReaderWriter final
    : public ClientAsyncReaderWriterInterface<W, R> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientAsyncReaderWriter));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall(void* tag) override {
    ABSL_CHECK(!started_);
    started_ = true;
    StartCallInternal(tag);
  }

  void ReadInitialMetadata(void* tag) override {
    ABSL_CHECK(started_);
    ABSL_CHECK(!context_->initial_metadata_received_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.RecvInitialMetadata(context_);
    call_.PerformOps(&meta_ops_);
  }

  void Read(R* msg, void* tag) override {
    ABSL_CHECK(started_);
    read_ops_.set_output_tag(tag);
    if (!context_->initial_metadata_received_) {
      read_ops_.RecvInitialMetadata(context_);
    }
    read_ops_.RecvMessage(msg);
    call_.PerformOps(&read_ops_);
  }

  void Write(const W& msg, void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);

    ABSL_CHECK(write_ops_.SendMessage(msg).ok());
    call_.PerformOps(&write_ops_);
  }

  void Write(const W& msg, grpc::WriteOptions options, void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);
    if (options.is_last_message()) {
      options.set_buffer_hint();
      write_ops_.ClientSendClose();
    }

    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    call_.PerformOps(&write_ops_);
  }

  void WritesDone(void* tag) override {
    ABSL_CHECK(started_);
    write_ops_.set_output_tag(tag);
    write_ops_.ClientSendClose();
    call_.PerformOps(&write_ops_);
  }

  void Finish(grpc::Status* status, void* tag) override {
    ABSL_CHECK(started_);
    finish_ops_.set_output_tag(tag);
    if (!context_->initial_metadata_received_) {
      finish_ops_.RecvInitialMetadata(context_);
    }
    finish_ops_.ClientRecvStatus(context_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  friend class internal::ClientAsyncReaderWriterFactory<W, R>;
  ClientAsyncReaderWriter(grpc::internal::Call call,
                          grpc::ClientContext* context, bool start, void* tag)
      : context_(context), call_(call), started_(start) {
    if (start) {
      StartCallInternal(tag);
    } else {
      ABSL_CHECK(tag == nullptr);
    }
  }

  void StartCallInternal(void* tag) {
    write_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                   context_->initial_metadata_flags());

    if (!context_->initial_metadata_corked_) {
      write_ops_.set_output_tag(tag);
      call_.PerformOps(&write_ops_);
    }
  }

  grpc::ClientContext* context_;
  grpc::internal::Call call_;
  bool started_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpRecvMessage<R>>
      read_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose>
      write_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvInitialMetadata,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
};

template <class W, class R>
class ServerAsyncReaderInterface
    : public grpc::internal::ServerAsyncStreamingInterface,
      public internal::AsyncReaderInterface<R> {
 public:

  virtual void Finish(const W& msg, const grpc::Status& status, void* tag) = 0;

  virtual void FinishWithError(const grpc::Status& status, void* tag) = 0;
};

template <class W, class R>
class ServerAsyncReader final : public ServerAsyncReaderInterface<W, R> {
 public:
  explicit ServerAsyncReader(grpc::ServerContext* ctx)
      : call_(nullptr, nullptr, nullptr), ctx_(ctx) {}

  void SendInitialMetadata(void* tag) override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                  ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      meta_ops_.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_.PerformOps(&meta_ops_);
  }

  void Read(R* msg, void* tag) override {
    read_ops_.set_output_tag(tag);
    read_ops_.RecvMessage(msg);
    call_.PerformOps(&read_ops_);
  }

  /// Note: \a msg is not sent if \a status has a non-OK code.

  void Finish(const W& msg, const grpc::Status& status, void* tag) override {
    finish_ops_.set_output_tag(tag);
    if (!ctx_->sent_initial_metadata_) {
      finish_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                      ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        finish_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }

    if (status.ok()) {
      finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_,
                                   finish_ops_.SendMessage(msg));
    } else {
      finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    }
    call_.PerformOps(&finish_ops_);
  }

  void FinishWithError(const grpc::Status& status, void* tag) override {
    ABSL_CHECK(!status.ok());
    finish_ops_.set_output_tag(tag);
    if (!ctx_->sent_initial_metadata_) {
      finish_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                      ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        finish_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
    finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  void BindCall(grpc::internal::Call* call) override { call_ = *call; }

  grpc::internal::Call call_;
  grpc::ServerContext* ctx_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<R>> read_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      finish_ops_;
};

template <class W>
class ServerAsyncWriterInterface
    : public grpc::internal::ServerAsyncStreamingInterface,
      public internal::AsyncWriterInterface<W> {
 public:

  virtual void Finish(const grpc::Status& status, void* tag) = 0;

  virtual void WriteAndFinish(const W& msg, grpc::WriteOptions options,
                              const grpc::Status& status, void* tag) = 0;
};

template <class W>
class ServerAsyncWriter final : public ServerAsyncWriterInterface<W> {
 public:
  explicit ServerAsyncWriter(grpc::ServerContext* ctx)
      : call_(nullptr, nullptr, nullptr), ctx_(ctx) {}

  void SendInitialMetadata(void* tag) override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                  ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      meta_ops_.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_.PerformOps(&meta_ops_);
  }

  void Write(const W& msg, void* tag) override {
    write_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&write_ops_);

    ABSL_CHECK(write_ops_.SendMessage(msg).ok());
    call_.PerformOps(&write_ops_);
  }

  void Write(const W& msg, grpc::WriteOptions options, void* tag) override {
    write_ops_.set_output_tag(tag);
    if (options.is_last_message()) {
      options.set_buffer_hint();
    }

    EnsureInitialMetadataSent(&write_ops_);

    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    call_.PerformOps(&write_ops_);
  }

  /// Note: \a status must have an OK code.

  void WriteAndFinish(const W& msg, grpc::WriteOptions options,
                      const grpc::Status& status, void* tag) override {
    write_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&write_ops_);
    options.set_buffer_hint();
    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    write_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&write_ops_);
  }

  /// Note: there are no restrictions are the code of

  void Finish(const grpc::Status& status, void* tag) override {
    finish_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&finish_ops_);
    finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  void BindCall(grpc::internal::Call* call) override { call_ = *call; }

  template <class T>
  void EnsureInitialMetadataSent(T* ops) {
    if (!ctx_->sent_initial_metadata_) {
      ops->SendInitialMetadata(&ctx_->initial_metadata_,
                               ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        ops->set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
  }

  grpc::internal::Call call_;
  grpc::ServerContext* ctx_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      write_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpServerSendStatus>
      finish_ops_;
};

template <class W, class R>
class ServerAsyncReaderWriterInterface
    : public grpc::internal::ServerAsyncStreamingInterface,
      public internal::AsyncWriterInterface<W>,
      public internal::AsyncReaderInterface<R> {
 public:

  virtual void Finish(const grpc::Status& status, void* tag) = 0;

  virtual void WriteAndFinish(const W& msg, grpc::WriteOptions options,
                              const grpc::Status& status, void* tag) = 0;
};

template <class W, class R>
class ServerAsyncReaderWriter final
    : public ServerAsyncReaderWriterInterface<W, R> {
 public:
  explicit ServerAsyncReaderWriter(grpc::ServerContext* ctx)
      : call_(nullptr, nullptr, nullptr), ctx_(ctx) {}

  void SendInitialMetadata(void* tag) override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    meta_ops_.set_output_tag(tag);
    meta_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                  ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      meta_ops_.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_.PerformOps(&meta_ops_);
  }

  void Read(R* msg, void* tag) override {
    read_ops_.set_output_tag(tag);
    read_ops_.RecvMessage(msg);
    call_.PerformOps(&read_ops_);
  }

  void Write(const W& msg, void* tag) override {
    write_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&write_ops_);

    ABSL_CHECK(write_ops_.SendMessage(msg).ok());
    call_.PerformOps(&write_ops_);
  }

  void Write(const W& msg, grpc::WriteOptions options, void* tag) override {
    write_ops_.set_output_tag(tag);
    if (options.is_last_message()) {
      options.set_buffer_hint();
    }
    EnsureInitialMetadataSent(&write_ops_);
    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    call_.PerformOps(&write_ops_);
  }

  /// Note: \a status must have an OK code.

  void WriteAndFinish(const W& msg, grpc::WriteOptions options,
                      const grpc::Status& status, void* tag) override {
    write_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&write_ops_);
    options.set_buffer_hint();
    ABSL_CHECK(write_ops_.SendMessage(msg, options).ok());
    write_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&write_ops_);
  }

  /// Note: there are no restrictions are the code of \a status,

  void Finish(const grpc::Status& status, void* tag) override {
    finish_ops_.set_output_tag(tag);
    EnsureInitialMetadataSent(&finish_ops_);

    finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&finish_ops_);
  }

 private:
  friend class grpc::Server;

  void BindCall(grpc::internal::Call* call) override { call_ = *call; }

  template <class T>
  void EnsureInitialMetadataSent(T* ops) {
    if (!ctx_->sent_initial_metadata_) {
      ops->SendInitialMetadata(&ctx_->initial_metadata_,
                               ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        ops->set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
  }

  grpc::internal::Call call_;
  grpc::ServerContext* ctx_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
      meta_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<R>> read_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      write_ops_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpServerSendStatus>
      finish_ops_;
};

}

#endif
