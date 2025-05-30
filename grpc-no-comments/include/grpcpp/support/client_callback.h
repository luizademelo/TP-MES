
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_SUPPORT_CLIENT_CALLBACK_H
#define GRPCPP_SUPPORT_CLIENT_CALLBACK_H

#include <grpc/grpc.h>
#include <grpc/impl/call.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/callback_common.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

#include <atomic>
#include <functional>

#include "absl/log/absl_check.h"

namespace grpc {
class Channel;
class ClientContext;

namespace internal {
class RpcMethod;

template <class InputMessage, class OutputMessage,
          class BaseInputMessage = InputMessage,
          class BaseOutputMessage = OutputMessage>
void CallbackUnaryCall(grpc::ChannelInterface* channel,
                       const grpc::internal::RpcMethod& method,
                       grpc::ClientContext* context,
                       const InputMessage* request, OutputMessage* result,
                       std::function<void(grpc::Status)> on_completion) {
  static_assert(std::is_base_of<BaseInputMessage, InputMessage>::value,
                "Invalid input message specification");
  static_assert(std::is_base_of<BaseOutputMessage, OutputMessage>::value,
                "Invalid output message specification");
  CallbackUnaryCallImpl<BaseInputMessage, BaseOutputMessage> x(
      channel, method, context, request, result, on_completion);
}

template <class InputMessage, class OutputMessage>
class CallbackUnaryCallImpl {
 public:
  CallbackUnaryCallImpl(grpc::ChannelInterface* channel,
                        const grpc::internal::RpcMethod& method,
                        grpc::ClientContext* context,
                        const InputMessage* request, OutputMessage* result,
                        std::function<void(grpc::Status)> on_completion) {
    grpc::CompletionQueue* cq = channel->CallbackCQ();
    ABSL_CHECK_NE(cq, nullptr);
    grpc::internal::Call call(channel->CreateCall(method, context, cq));

    using FullCallOpSet = grpc::internal::CallOpSet<
        grpc::internal::CallOpSendInitialMetadata,
        grpc::internal::CallOpSendMessage,
        grpc::internal::CallOpRecvInitialMetadata,
        grpc::internal::CallOpRecvMessage<OutputMessage>,
        grpc::internal::CallOpClientSendClose,
        grpc::internal::CallOpClientRecvStatus>;

    struct OpSetAndTag {
      FullCallOpSet opset;
      grpc::internal::CallbackWithStatusTag tag;
    };
    const size_t alloc_sz = sizeof(OpSetAndTag);
    auto* const alloced =
        static_cast<OpSetAndTag*>(grpc_call_arena_alloc(call.call(), alloc_sz));
    auto* ops = new (&alloced->opset) FullCallOpSet;
    auto* tag = new (&alloced->tag)
        grpc::internal::CallbackWithStatusTag(call.call(), on_completion, ops);

    grpc::Status s = ops->SendMessagePtr(request);
    if (!s.ok()) {
      tag->force_run(s);
      return;
    }
    ops->SendInitialMetadata(&context->send_initial_metadata_,
                             context->initial_metadata_flags());
    ops->RecvInitialMetadata(context);
    ops->RecvMessage(result);
    ops->AllowNoMessage();
    ops->ClientSendClose();
    ops->ClientRecvStatus(context, tag->status_ptr());
    ops->set_core_cq_tag(tag);
    call.PerformOps(ops);
  }
};

class ClientReactor {
 public:
  virtual ~ClientReactor() = default;

  virtual void OnDone(const grpc::Status& ) = 0;

  virtual bool InternalTrailersOnly(const grpc_call* call) const;
};

}

template <class Request, class Response>
class ClientBidiReactor;
template <class Response>
class ClientReadReactor;
template <class Request>
class ClientWriteReactor;
class ClientUnaryReactor;

// NOTE: The streaming objects are not actually implemented in the public API.

template <class Request, class Response>
class ClientCallbackReaderWriter {
 public:
  virtual ~ClientCallbackReaderWriter() {}
  virtual void StartCall() = 0;
  virtual void Write(const Request* req, grpc::WriteOptions options) = 0;
  virtual void WritesDone() = 0;
  virtual void Read(Response* resp) = 0;
  virtual void AddHold(int holds) = 0;
  virtual void RemoveHold() = 0;

 protected:
  void BindReactor(ClientBidiReactor<Request, Response>* reactor) {
    reactor->BindStream(this);
  }
};

template <class Response>
class ClientCallbackReader {
 public:
  virtual ~ClientCallbackReader() {}
  virtual void StartCall() = 0;
  virtual void Read(Response* resp) = 0;
  virtual void AddHold(int holds) = 0;
  virtual void RemoveHold() = 0;

 protected:
  void BindReactor(ClientReadReactor<Response>* reactor) {
    reactor->BindReader(this);
  }
};

template <class Request>
class ClientCallbackWriter {
 public:
  virtual ~ClientCallbackWriter() {}
  virtual void StartCall() = 0;
  void Write(const Request* req) { Write(req, grpc::WriteOptions()); }
  virtual void Write(const Request* req, grpc::WriteOptions options) = 0;
  void WriteLast(const Request* req, grpc::WriteOptions options) {
    Write(req, options.set_last_message());
  }
  virtual void WritesDone() = 0;

  virtual void AddHold(int holds) = 0;
  virtual void RemoveHold() = 0;

 protected:
  void BindReactor(ClientWriteReactor<Request>* reactor) {
    reactor->BindWriter(this);
  }
};

class ClientCallbackUnary {
 public:
  virtual ~ClientCallbackUnary() {}
  virtual void StartCall() = 0;

 protected:
  void BindReactor(ClientUnaryReactor* reactor);
};

template <class Request, class Response>
class ClientBidiReactor : public internal::ClientReactor {
 public:

  void StartCall() { stream_->StartCall(); }

  void StartRead(Response* resp) { stream_->Read(resp); }

  void StartWrite(const Request* req) { StartWrite(req, grpc::WriteOptions()); }

  void StartWrite(const Request* req, grpc::WriteOptions options) {
    stream_->Write(req, options);
  }

  void StartWriteLast(const Request* req, grpc::WriteOptions options) {
    StartWrite(req, options.set_last_message());
  }

  void StartWritesDone() { stream_->WritesDone(); }

  void AddHold() { AddMultipleHolds(1); }
  void AddMultipleHolds(int holds) {
    ABSL_DCHECK_GT(holds, 0);
    stream_->AddHold(holds);
  }
  void RemoveHold() { stream_->RemoveHold(); }

  void OnDone(const grpc::Status& ) override {}

  virtual void OnReadInitialMetadataDone(bool ) {}

  virtual void OnReadDone(bool ) {}

  virtual void OnWriteDone(bool ) {}

  virtual void OnWritesDoneDone(bool ) {}

 private:
  friend class ClientCallbackReaderWriter<Request, Response>;
  void BindStream(ClientCallbackReaderWriter<Request, Response>* stream) {
    stream_ = stream;
  }
  ClientCallbackReaderWriter<Request, Response>* stream_;
};

template <class Response>
class ClientReadReactor : public internal::ClientReactor {
 public:
  void StartCall() { reader_->StartCall(); }
  void StartRead(Response* resp) { reader_->Read(resp); }

  void AddHold() { AddMultipleHolds(1); }
  void AddMultipleHolds(int holds) {
    ABSL_DCHECK_GT(holds, 0);
    reader_->AddHold(holds);
  }
  void RemoveHold() { reader_->RemoveHold(); }

  void OnDone(const grpc::Status& ) override {}
  virtual void OnReadInitialMetadataDone(bool ) {}
  virtual void OnReadDone(bool ) {}

 private:
  friend class ClientCallbackReader<Response>;
  void BindReader(ClientCallbackReader<Response>* reader) { reader_ = reader; }
  ClientCallbackReader<Response>* reader_;
};

template <class Request>
class ClientWriteReactor : public internal::ClientReactor {
 public:
  void StartCall() { writer_->StartCall(); }
  void StartWrite(const Request* req) { StartWrite(req, grpc::WriteOptions()); }
  void StartWrite(const Request* req, grpc::WriteOptions options) {
    writer_->Write(req, options);
  }
  void StartWriteLast(const Request* req, grpc::WriteOptions options) {
    StartWrite(req, options.set_last_message());
  }
  void StartWritesDone() { writer_->WritesDone(); }

  void AddHold() { AddMultipleHolds(1); }
  void AddMultipleHolds(int holds) {
    ABSL_DCHECK_GT(holds, 0);
    writer_->AddHold(holds);
  }
  void RemoveHold() { writer_->RemoveHold(); }

  void OnDone(const grpc::Status& ) override {}
  virtual void OnReadInitialMetadataDone(bool ) {}
  virtual void OnWriteDone(bool ) {}
  virtual void OnWritesDoneDone(bool ) {}

 private:
  friend class ClientCallbackWriter<Request>;
  void BindWriter(ClientCallbackWriter<Request>* writer) { writer_ = writer; }

  ClientCallbackWriter<Request>* writer_;
};

class ClientUnaryReactor : public internal::ClientReactor {
 public:
  void StartCall() { call_->StartCall(); }
  void OnDone(const grpc::Status& ) override {}
  virtual void OnReadInitialMetadataDone(bool ) {}

 private:
  friend class ClientCallbackUnary;
  void BindCall(ClientCallbackUnary* call) { call_ = call; }
  ClientCallbackUnary* call_;
};

inline void ClientCallbackUnary::BindReactor(ClientUnaryReactor* reactor) {
  reactor->BindCall(this);
}

namespace internal {

template <class Request, class Response>
class ClientCallbackReaderWriterFactory;
template <class Response>
class ClientCallbackReaderFactory;
template <class Request>
class ClientCallbackWriterFactory;

template <class Request, class Response>
class ClientCallbackReaderWriterImpl
    : public ClientCallbackReaderWriter<Request, Response> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientCallbackReaderWriterImpl));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall() ABSL_LOCKS_EXCLUDED(start_mu_) override {

    if (!start_corked_) {
      start_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                     context_->initial_metadata_flags());
    }

    call_.PerformOps(&start_ops_);

    {
      grpc::internal::MutexLock lock(&start_mu_);

      if (backlog_.read_ops) {
        call_.PerformOps(&read_ops_);
      }
      if (backlog_.write_ops) {
        call_.PerformOps(&write_ops_);
      }
      if (backlog_.writes_done_ops) {
        call_.PerformOps(&writes_done_ops_);
      }
      call_.PerformOps(&finish_ops_);

      started_.store(true, std::memory_order_release);
    }

    this->MaybeFinish(false);
  }

  void Read(Response* msg) override {
    read_ops_.RecvMessage(msg);
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);
    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.read_ops = true;
        return;
      }
    }
    call_.PerformOps(&read_ops_);
  }

  void Write(const Request* msg, grpc::WriteOptions options)
      ABSL_LOCKS_EXCLUDED(start_mu_) override {
    if (options.is_last_message()) {
      options.set_buffer_hint();
      write_ops_.ClientSendClose();
    }

    ABSL_CHECK(write_ops_.SendMessagePtr(msg, options).ok());
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);
    if (GPR_UNLIKELY(corked_write_needed_)) {
      write_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                     context_->initial_metadata_flags());
      corked_write_needed_ = false;
    }

    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.write_ops = true;
        return;
      }
    }
    call_.PerformOps(&write_ops_);
  }
  void WritesDone() ABSL_LOCKS_EXCLUDED(start_mu_) override {
    writes_done_ops_.ClientSendClose();
    writes_done_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnWritesDoneDone(ok);
          MaybeFinish(true);
        },
        &writes_done_ops_, false);
    writes_done_ops_.set_core_cq_tag(&writes_done_tag_);
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);
    if (GPR_UNLIKELY(corked_write_needed_)) {
      writes_done_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                           context_->initial_metadata_flags());
      corked_write_needed_ = false;
    }
    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.writes_done_ops = true;
        return;
      }
    }
    call_.PerformOps(&writes_done_ops_);
  }

  void AddHold(int holds) override {
    callbacks_outstanding_.fetch_add(holds, std::memory_order_relaxed);
  }
  void RemoveHold() override { MaybeFinish(false); }

 private:
  friend class ClientCallbackReaderWriterFactory<Request, Response>;

  ClientCallbackReaderWriterImpl(grpc::internal::Call call,
                                 grpc::ClientContext* context,
                                 ClientBidiReactor<Request, Response>* reactor)
      : context_(context),
        call_(call),
        reactor_(reactor),
        start_corked_(context_->initial_metadata_corked_),
        corked_write_needed_(start_corked_) {
    this->BindReactor(reactor);

    start_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadInitialMetadataDone(
              ok && !reactor_->InternalTrailersOnly(call_.call()));
          MaybeFinish(true);
        },
        &start_ops_, false);
    start_ops_.RecvInitialMetadata(context_);
    start_ops_.set_core_cq_tag(&start_tag_);

    write_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnWriteDone(ok);
          MaybeFinish(true);
        },
        &write_ops_, false);
    write_ops_.set_core_cq_tag(&write_tag_);

    read_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadDone(ok);
          MaybeFinish(true);
        },
        &read_ops_, false);
    read_ops_.set_core_cq_tag(&read_tag_);

    finish_tag_.Set(
        call_.call(),
        [this](bool ) { MaybeFinish(true); },
        &finish_ops_,
        false);
    finish_ops_.ClientRecvStatus(context_, &finish_status_);
    finish_ops_.set_core_cq_tag(&finish_tag_);
  }

  void MaybeFinish(bool from_reaction) {
    if (GPR_UNLIKELY(callbacks_outstanding_.fetch_sub(
                         1, std::memory_order_acq_rel) == 1)) {
      grpc::Status s = std::move(finish_status_);
      auto* reactor = reactor_;
      auto* call = call_.call();
      this->~ClientCallbackReaderWriterImpl();
      if (GPR_LIKELY(from_reaction)) {
        grpc_call_unref(call);
        reactor->OnDone(s);
      } else {
        grpc_call_run_in_event_engine(
            call, [reactor, s = std::move(s)]() { reactor->OnDone(s); });
        grpc_call_unref(call);
      }
    }
  }

  grpc::ClientContext* const context_;
  grpc::internal::Call call_;
  ClientBidiReactor<Request, Response>* const reactor_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpRecvInitialMetadata>
      start_ops_;
  grpc::internal::CallbackWithSuccessTag start_tag_;
  const bool start_corked_;
  bool corked_write_needed_;

  grpc::internal::CallOpSet<grpc::internal::CallOpClientRecvStatus> finish_ops_;
  grpc::internal::CallbackWithSuccessTag finish_tag_;
  grpc::Status finish_status_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose>
      write_ops_;
  grpc::internal::CallbackWithSuccessTag write_tag_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpClientSendClose>
      writes_done_ops_;
  grpc::internal::CallbackWithSuccessTag writes_done_tag_;

  grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<Response>>
      read_ops_;
  grpc::internal::CallbackWithSuccessTag read_tag_;

  struct StartCallBacklog {
    bool write_ops = false;
    bool writes_done_ops = false;
    bool read_ops = false;
  };
  StartCallBacklog backlog_ ABSL_GUARDED_BY(start_mu_);

  std::atomic<intptr_t> callbacks_outstanding_{3};
  std::atomic_bool started_{false};
  grpc::internal::Mutex start_mu_;
};

template <class Request, class Response>
class ClientCallbackReaderWriterFactory {
 public:
  static void Create(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context,
                     ClientBidiReactor<Request, Response>* reactor) {
    grpc::internal::Call call =
        channel->CreateCall(method, context, channel->CallbackCQ());

    grpc_call_ref(call.call());
    new (grpc_call_arena_alloc(
        call.call(), sizeof(ClientCallbackReaderWriterImpl<Request, Response>)))
        ClientCallbackReaderWriterImpl<Request, Response>(call, context,
                                                          reactor);
  }
};

template <class Response>
class ClientCallbackReaderImpl : public ClientCallbackReader<Response> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientCallbackReaderImpl));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall() override {

    start_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadInitialMetadataDone(
              ok && !reactor_->InternalTrailersOnly(call_.call()));
          MaybeFinish(true);
        },
        &start_ops_, false);
    start_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                   context_->initial_metadata_flags());
    start_ops_.RecvInitialMetadata(context_);
    start_ops_.set_core_cq_tag(&start_tag_);
    call_.PerformOps(&start_ops_);

    read_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadDone(ok);
          MaybeFinish(true);
        },
        &read_ops_, false);
    read_ops_.set_core_cq_tag(&read_tag_);

    {
      grpc::internal::MutexLock lock(&start_mu_);
      if (backlog_.read_ops) {
        call_.PerformOps(&read_ops_);
      }
      started_.store(true, std::memory_order_release);
    }

    finish_tag_.Set(
        call_.call(),
        [this](bool ) { MaybeFinish(true); },
        &finish_ops_, false);
    finish_ops_.ClientRecvStatus(context_, &finish_status_);
    finish_ops_.set_core_cq_tag(&finish_tag_);
    call_.PerformOps(&finish_ops_);
  }

  void Read(Response* msg) override {
    read_ops_.RecvMessage(msg);
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);
    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.read_ops = true;
        return;
      }
    }
    call_.PerformOps(&read_ops_);
  }

  void AddHold(int holds) override {
    callbacks_outstanding_.fetch_add(holds, std::memory_order_relaxed);
  }
  void RemoveHold() override { MaybeFinish(false); }

 private:
  friend class ClientCallbackReaderFactory<Response>;

  template <class Request>
  ClientCallbackReaderImpl(grpc::internal::Call call,
                           grpc::ClientContext* context, Request* request,
                           ClientReadReactor<Response>* reactor)
      : context_(context), call_(call), reactor_(reactor) {
    this->BindReactor(reactor);

    ABSL_CHECK(start_ops_.SendMessagePtr(request).ok());
    start_ops_.ClientSendClose();
  }

  void MaybeFinish(bool from_reaction) {
    if (GPR_UNLIKELY(callbacks_outstanding_.fetch_sub(
                         1, std::memory_order_acq_rel) == 1)) {
      grpc::Status s = std::move(finish_status_);
      auto* reactor = reactor_;
      auto* call = call_.call();
      this->~ClientCallbackReaderImpl();
      if (GPR_LIKELY(from_reaction)) {
        grpc_call_unref(call);
        reactor->OnDone(s);
      } else {
        grpc_call_run_in_event_engine(
            call, [reactor, s = std::move(s)]() { reactor->OnDone(s); });
        grpc_call_unref(call);
      }
    }
  }

  grpc::ClientContext* const context_;
  grpc::internal::Call call_;
  ClientReadReactor<Response>* const reactor_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose,
                            grpc::internal::CallOpRecvInitialMetadata>
      start_ops_;
  grpc::internal::CallbackWithSuccessTag start_tag_;

  grpc::internal::CallOpSet<grpc::internal::CallOpClientRecvStatus> finish_ops_;
  grpc::internal::CallbackWithSuccessTag finish_tag_;
  grpc::Status finish_status_;

  grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<Response>>
      read_ops_;
  grpc::internal::CallbackWithSuccessTag read_tag_;

  struct StartCallBacklog {
    bool read_ops = false;
  };
  StartCallBacklog backlog_ ABSL_GUARDED_BY(start_mu_);

  std::atomic<intptr_t> callbacks_outstanding_{2};
  std::atomic_bool started_{false};
  grpc::internal::Mutex start_mu_;
};

template <class Response>
class ClientCallbackReaderFactory {
 public:
  template <class Request>
  static void Create(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context, const Request* request,
                     ClientReadReactor<Response>* reactor) {
    grpc::internal::Call call =
        channel->CreateCall(method, context, channel->CallbackCQ());

    grpc_call_ref(call.call());
    new (grpc_call_arena_alloc(call.call(),
                               sizeof(ClientCallbackReaderImpl<Response>)))
        ClientCallbackReaderImpl<Response>(call, context, request, reactor);
  }
};

template <class Request>
class ClientCallbackWriterImpl : public ClientCallbackWriter<Request> {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientCallbackWriterImpl));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall() ABSL_LOCKS_EXCLUDED(start_mu_) override {

    if (!start_corked_) {
      start_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                     context_->initial_metadata_flags());
    }
    call_.PerformOps(&start_ops_);

    {
      grpc::internal::MutexLock lock(&start_mu_);

      if (backlog_.write_ops) {
        call_.PerformOps(&write_ops_);
      }
      if (backlog_.writes_done_ops) {
        call_.PerformOps(&writes_done_ops_);
      }
      call_.PerformOps(&finish_ops_);

      started_.store(true, std::memory_order_release);
    }

    this->MaybeFinish(false);
  }

  void Write(const Request* msg, grpc::WriteOptions options)
      ABSL_LOCKS_EXCLUDED(start_mu_) override {
    if (GPR_UNLIKELY(options.is_last_message())) {
      options.set_buffer_hint();
      write_ops_.ClientSendClose();
    }

    ABSL_CHECK(write_ops_.SendMessagePtr(msg, options).ok());
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);

    if (GPR_UNLIKELY(corked_write_needed_)) {
      write_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                     context_->initial_metadata_flags());
      corked_write_needed_ = false;
    }

    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.write_ops = true;
        return;
      }
    }
    call_.PerformOps(&write_ops_);
  }

  void WritesDone() ABSL_LOCKS_EXCLUDED(start_mu_) override {
    writes_done_ops_.ClientSendClose();
    writes_done_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnWritesDoneDone(ok);
          MaybeFinish(true);
        },
        &writes_done_ops_, false);
    writes_done_ops_.set_core_cq_tag(&writes_done_tag_);
    callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed);

    if (GPR_UNLIKELY(corked_write_needed_)) {
      writes_done_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                           context_->initial_metadata_flags());
      corked_write_needed_ = false;
    }

    if (GPR_UNLIKELY(!started_.load(std::memory_order_acquire))) {
      grpc::internal::MutexLock lock(&start_mu_);
      if (GPR_LIKELY(!started_.load(std::memory_order_relaxed))) {
        backlog_.writes_done_ops = true;
        return;
      }
    }
    call_.PerformOps(&writes_done_ops_);
  }

  void AddHold(int holds) override {
    callbacks_outstanding_.fetch_add(holds, std::memory_order_relaxed);
  }
  void RemoveHold() override { MaybeFinish(false); }

 private:
  friend class ClientCallbackWriterFactory<Request>;

  template <class Response>
  ClientCallbackWriterImpl(grpc::internal::Call call,
                           grpc::ClientContext* context, Response* response,
                           ClientWriteReactor<Request>* reactor)
      : context_(context),
        call_(call),
        reactor_(reactor),
        start_corked_(context_->initial_metadata_corked_),
        corked_write_needed_(start_corked_) {
    this->BindReactor(reactor);

    start_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadInitialMetadataDone(
              ok && !reactor_->InternalTrailersOnly(call_.call()));
          MaybeFinish(true);
        },
        &start_ops_, false);
    start_ops_.RecvInitialMetadata(context_);
    start_ops_.set_core_cq_tag(&start_tag_);

    write_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnWriteDone(ok);
          MaybeFinish(true);
        },
        &write_ops_, false);
    write_ops_.set_core_cq_tag(&write_tag_);

    finish_ops_.RecvMessage(response);
    finish_ops_.AllowNoMessage();
    finish_tag_.Set(
        call_.call(),
        [this](bool ) { MaybeFinish(true); },
        &finish_ops_,
        false);
    finish_ops_.ClientRecvStatus(context_, &finish_status_);
    finish_ops_.set_core_cq_tag(&finish_tag_);
  }

  void MaybeFinish(bool from_reaction) {
    if (GPR_UNLIKELY(callbacks_outstanding_.fetch_sub(
                         1, std::memory_order_acq_rel) == 1)) {
      grpc::Status s = std::move(finish_status_);
      auto* reactor = reactor_;
      auto* call = call_.call();
      this->~ClientCallbackWriterImpl();
      if (GPR_LIKELY(from_reaction)) {
        grpc_call_unref(call);
        reactor->OnDone(s);
      } else {
        grpc_call_run_in_event_engine(
            call, [reactor, s = std::move(s)]() { reactor->OnDone(s); });
        grpc_call_unref(call);
      }
    }
  }

  grpc::ClientContext* const context_;
  grpc::internal::Call call_;
  ClientWriteReactor<Request>* const reactor_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpRecvInitialMetadata>
      start_ops_;
  grpc::internal::CallbackWithSuccessTag start_tag_;
  const bool start_corked_;
  bool corked_write_needed_;

  grpc::internal::CallOpSet<grpc::internal::CallOpGenericRecvMessage,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
  grpc::internal::CallbackWithSuccessTag finish_tag_;
  grpc::Status finish_status_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose>
      write_ops_;
  grpc::internal::CallbackWithSuccessTag write_tag_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpClientSendClose>
      writes_done_ops_;
  grpc::internal::CallbackWithSuccessTag writes_done_tag_;

  struct StartCallBacklog {
    bool write_ops = false;
    bool writes_done_ops = false;
  };
  StartCallBacklog backlog_ ABSL_GUARDED_BY(start_mu_);

  std::atomic<intptr_t> callbacks_outstanding_{3};
  std::atomic_bool started_{false};
  grpc::internal::Mutex start_mu_;
};

template <class Request>
class ClientCallbackWriterFactory {
 public:
  template <class Response>
  static void Create(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context, Response* response,
                     ClientWriteReactor<Request>* reactor) {
    grpc::internal::Call call =
        channel->CreateCall(method, context, channel->CallbackCQ());

    grpc_call_ref(call.call());
    new (grpc_call_arena_alloc(call.call(),
                               sizeof(ClientCallbackWriterImpl<Request>)))
        ClientCallbackWriterImpl<Request>(call, context, response, reactor);
  }
};

class ClientCallbackUnaryImpl final : public ClientCallbackUnary {
 public:

  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientCallbackUnaryImpl));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  void StartCall() override {

    start_tag_.Set(
        call_.call(),
        [this](bool ok) {
          reactor_->OnReadInitialMetadataDone(
              ok && !reactor_->InternalTrailersOnly(call_.call()));
          MaybeFinish();
        },
        &start_ops_, false);
    start_ops_.SendInitialMetadata(&context_->send_initial_metadata_,
                                   context_->initial_metadata_flags());
    start_ops_.RecvInitialMetadata(context_);
    start_ops_.set_core_cq_tag(&start_tag_);
    call_.PerformOps(&start_ops_);

    finish_tag_.Set(
        call_.call(), [this](bool ) { MaybeFinish(); }, &finish_ops_,
        false);
    finish_ops_.ClientRecvStatus(context_, &finish_status_);
    finish_ops_.set_core_cq_tag(&finish_tag_);
    call_.PerformOps(&finish_ops_);
  }

 private:
  friend class ClientCallbackUnaryFactory;

  template <class Request, class Response>
  ClientCallbackUnaryImpl(grpc::internal::Call call,
                          grpc::ClientContext* context, Request* request,
                          Response* response, ClientUnaryReactor* reactor)
      : context_(context), call_(call), reactor_(reactor) {
    this->BindReactor(reactor);

    ABSL_CHECK(start_ops_.SendMessagePtr(request).ok());
    start_ops_.ClientSendClose();
    finish_ops_.RecvMessage(response);
    finish_ops_.AllowNoMessage();
  }

  void MaybeFinish() {
    if (GPR_UNLIKELY(callbacks_outstanding_.fetch_sub(
                         1, std::memory_order_acq_rel) == 1)) {
      grpc::Status s = std::move(finish_status_);
      auto* reactor = reactor_;
      auto* call = call_.call();
      this->~ClientCallbackUnaryImpl();
      grpc_call_unref(call);
      reactor->OnDone(s);
    }
  }

  grpc::ClientContext* const context_;
  grpc::internal::Call call_;
  ClientUnaryReactor* const reactor_;

  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpClientSendClose,
                            grpc::internal::CallOpRecvInitialMetadata>
      start_ops_;
  grpc::internal::CallbackWithSuccessTag start_tag_;

  grpc::internal::CallOpSet<grpc::internal::CallOpGenericRecvMessage,
                            grpc::internal::CallOpClientRecvStatus>
      finish_ops_;
  grpc::internal::CallbackWithSuccessTag finish_tag_;
  grpc::Status finish_status_;

  std::atomic<intptr_t> callbacks_outstanding_{2};
};

class ClientCallbackUnaryFactory {
 public:
  template <class Request, class Response, class BaseRequest = Request,
            class BaseResponse = Response>
  static void Create(grpc::ChannelInterface* channel,
                     const grpc::internal::RpcMethod& method,
                     grpc::ClientContext* context, const Request* request,
                     Response* response, ClientUnaryReactor* reactor) {
    grpc::internal::Call call =
        channel->CreateCall(method, context, channel->CallbackCQ());

    grpc_call_ref(call.call());

    new (grpc_call_arena_alloc(call.call(), sizeof(ClientCallbackUnaryImpl)))
        ClientCallbackUnaryImpl(call, context,
                                static_cast<const BaseRequest*>(request),
                                static_cast<BaseResponse*>(response), reactor);
  }
};

}
}

#endif
