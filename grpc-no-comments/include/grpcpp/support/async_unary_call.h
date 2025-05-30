
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_ASYNC_UNARY_CALL_H
#define GRPCPP_SUPPORT_ASYNC_UNARY_CALL_H

#include <grpc/grpc.h>
#include <grpcpp/client_context.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/call_op_set_interface.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>

#include "absl/log/absl_check.h"

namespace grpc {

template <class R>
class ClientAsyncResponseReader;

template <class R>
class ClientAsyncResponseReaderInterface {
 public:
  virtual ~ClientAsyncResponseReaderInterface() {}

  virtual void StartCall() = 0;

  virtual void ReadInitialMetadata(void* tag) = 0;

  virtual void Finish(R* msg, grpc::Status* status, void* tag) = 0;
};

namespace internal {

class ClientAsyncResponseReaderHelper {
 public:

  template <class R, class W, class BaseR = R, class BaseW = W>
  static ClientAsyncResponseReader<R>* Create(
      grpc::ChannelInterface* channel, grpc::CompletionQueue* cq,
      const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
      const W& request)  {
    grpc::internal::Call call = channel->CreateCall(method, context, cq);
    ClientAsyncResponseReader<R>* result = new (grpc_call_arena_alloc(
        call.call(), sizeof(ClientAsyncResponseReader<R>)))
        ClientAsyncResponseReader<R>(call, context);
    SetupRequest<BaseR, BaseW>(
        call.call(), &result->single_buf_, &result->read_initial_metadata_,
        &result->finish_, static_cast<const BaseW&>(request));

    return result;
  }

  template <class R, class W>
  static void SetupRequest(
      grpc_call* call,
      grpc::internal::CallOpSendInitialMetadata** single_buf_ptr,
      std::function<void(ClientContext*, internal::Call*,
                         internal::CallOpSendInitialMetadata*, void*)>*
          read_initial_metadata,
      std::function<
          void(ClientContext*, internal::Call*, bool initial_metadata_read,
               internal::CallOpSendInitialMetadata*,
               internal::CallOpSetInterface**, void*, Status*, void*)>* finish,
      const W& request) {
    using SingleBufType =
        grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                                  grpc::internal::CallOpSendMessage,
                                  grpc::internal::CallOpClientSendClose,
                                  grpc::internal::CallOpRecvInitialMetadata,
                                  grpc::internal::CallOpRecvMessage<R>,
                                  grpc::internal::CallOpClientRecvStatus>;
    SingleBufType* single_buf =
        new (grpc_call_arena_alloc(call, sizeof(SingleBufType))) SingleBufType;
    *single_buf_ptr = single_buf;

    ABSL_CHECK(single_buf->SendMessage(request).ok());
    single_buf->ClientSendClose();

    *read_initial_metadata =
        [](ClientContext* context, internal::Call* call,
           internal::CallOpSendInitialMetadata* single_buf_view, void* tag) {
          auto* single_buf = static_cast<SingleBufType*>(single_buf_view);
          single_buf->set_output_tag(tag);
          single_buf->RecvInitialMetadata(context);
          call->PerformOps(single_buf);
        };

    *finish = [](ClientContext* context, internal::Call* call,
                 bool initial_metadata_read,
                 internal::CallOpSendInitialMetadata* single_buf_view,
                 internal::CallOpSetInterface** finish_buf_ptr, void* msg,
                 Status* status, void* tag) {
      if (initial_metadata_read) {
        using FinishBufType =
            grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<R>,
                                      grpc::internal::CallOpClientRecvStatus>;
        FinishBufType* finish_buf =
            new (grpc_call_arena_alloc(call->call(), sizeof(FinishBufType)))
                FinishBufType;
        *finish_buf_ptr = finish_buf;
        finish_buf->set_output_tag(tag);
        finish_buf->RecvMessage(static_cast<R*>(msg));
        finish_buf->AllowNoMessage();
        finish_buf->ClientRecvStatus(context, status);
        call->PerformOps(finish_buf);
      } else {
        auto* single_buf = static_cast<SingleBufType*>(single_buf_view);
        single_buf->set_output_tag(tag);
        single_buf->RecvInitialMetadata(context);
        single_buf->RecvMessage(static_cast<R*>(msg));
        single_buf->AllowNoMessage();
        single_buf->ClientRecvStatus(context, status);
        call->PerformOps(single_buf);
      }
    };
  }

  static void StartCall(grpc::ClientContext* context,
                        grpc::internal::CallOpSendInitialMetadata* single_buf) {
    single_buf->SendInitialMetadata(&context->send_initial_metadata_,
                                    context->initial_metadata_flags());
  }
};

template <class R>
class ClientAsyncResponseReaderFactory {
 public:
  template <class W>
  static ClientAsyncResponseReader<R>* Create(
      grpc::ChannelInterface* channel, grpc::CompletionQueue* cq,
      const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
      const W& request, bool start) {
    auto* result = ClientAsyncResponseReaderHelper::Create<R>(
        channel, cq, method, context, request);
    if (start) {
      result->StartCall();
    }
    return result;
  }
};

}

template <class R>
class ClientAsyncResponseReader final
    : public ClientAsyncResponseReaderInterface<R> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientAsyncResponseReader));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall() override {
    ABSL_DCHECK(!started_);
    started_ = true;
    internal::ClientAsyncResponseReaderHelper::StartCall(context_, single_buf_);
  }

  void ReadInitialMetadata(void* tag) override {
    ABSL_DCHECK(started_);
    ABSL_DCHECK(!context_->initial_metadata_received_);
    read_initial_metadata_(context_, &call_, single_buf_, tag);
    initial_metadata_read_ = true;
  }

  void Finish(R* msg, grpc::Status* status, void* tag) override {
    ABSL_DCHECK(started_);
    finish_(context_, &call_, initial_metadata_read_, single_buf_, &finish_buf_,
            static_cast<void*>(msg), status, tag);
  }

 private:
  friend class internal::ClientAsyncResponseReaderHelper;
  grpc::ClientContext* const context_;
  grpc::internal::Call call_;
  bool started_ = false;
  bool initial_metadata_read_ = false;

  ClientAsyncResponseReader(grpc::internal::Call call,
                            grpc::ClientContext* context)
      : context_(context), call_(call) {}

  static void* operator new(std::size_t size);
  static void* operator new(std::size_t , void* p) { return p; }

  internal::CallOpSendInitialMetadata* single_buf_;
  internal::CallOpSetInterface* finish_buf_ = nullptr;
  std::function<void(ClientContext*, internal::Call*,
                     internal::CallOpSendInitialMetadata*, void*)>
      read_initial_metadata_;
  std::function<void(ClientContext*, internal::Call*,
                     bool initial_metadata_read,
                     internal::CallOpSendInitialMetadata*,
                     internal::CallOpSetInterface**, void*, Status*, void*)>
      finish_;
};

template <class W>
class ServerAsyncResponseWriter final
    : public grpc::internal::ServerAsyncStreamingInterface {
 public:
  explicit ServerAsyncResponseWriter(grpc::ServerContext* ctx)
      : call_(nullptr, nullptr, nullptr), ctx_(ctx) {}

  void SendInitialMetadata(void* tag) override {
    ABSL_CHECK(!ctx_->sent_initial_metadata_);

    meta_buf_.set_output_tag(tag);
    meta_buf_.SendInitialMetadata(&ctx_->initial_metadata_,
                                  ctx_->initial_metadata_flags());
    if (ctx_->compression_level_set()) {
      meta_buf_.set_compression_level(ctx_->compression_level());
    }
    ctx_->sent_initial_metadata_ = true;
    call_.PerformOps(&meta_buf_);
  }

  /// Note: if \a status has a non-OK code, then \a msg will not be sent,

  void Finish(const W& msg, const grpc::Status& status, void* tag) {
    finish_buf_.set_output_tag(tag);
    finish_buf_.set_core_cq_tag(&finish_buf_);
    if (!ctx_->sent_initial_metadata_) {
      finish_buf_.SendInitialMetadata(&ctx_->initial_metadata_,
                                      ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        finish_buf_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }

    if (status.ok()) {
      finish_buf_.ServerSendStatus(&ctx_->trailing_metadata_,
                                   finish_buf_.SendMessage(msg));
    } else {
      finish_buf_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    }
    call_.PerformOps(&finish_buf_);
  }

  void FinishWithError(const grpc::Status& status, void* tag) {
    ABSL_CHECK(!status.ok());
    finish_buf_.set_output_tag(tag);
    if (!ctx_->sent_initial_metadata_) {
      finish_buf_.SendInitialMetadata(&ctx_->initial_metadata_,
                                      ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        finish_buf_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
    }
    finish_buf_.ServerSendStatus(&ctx_->trailing_metadata_, status);
    call_.PerformOps(&finish_buf_);
  }

 private:
  void BindCall(grpc::internal::Call* call) override { call_ = *call; }

  grpc::internal::Call call_;
  grpc::ServerContext* ctx_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
      meta_buf_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      finish_buf_;
};

}

namespace std {
template <class R>
class default_delete<grpc::ClientAsyncResponseReader<R>> {
 public:
  void operator()(void* ) {}
};
template <class R>
class default_delete<grpc::ClientAsyncResponseReaderInterface<R>> {
 public:
  void operator()(void* ) {}
};
}

#endif
