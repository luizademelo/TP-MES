
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_SUPPORT_SERVER_CALLBACK_H
#define GRPCPP_SUPPORT_SERVER_CALLBACK_H

#include <grpc/impl/call.h>
#include <grpcpp/impl/call.h>
#include <grpcpp/impl/call_op_set.h>
#include <grpcpp/impl/sync.h>
#include <grpcpp/support/callback_common.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/status.h>

#include <atomic>
#include <functional>
#include <type_traits>

#include "absl/functional/any_invocable.h"

namespace grpc {

namespace internal {

template <class Request, class Response>
class CallbackUnaryHandler;
template <class Request, class Response>
class CallbackClientStreamingHandler;
template <class Request, class Response>
class CallbackServerStreamingHandler;
template <class Request, class Response>
class CallbackBidiHandler;

class ServerReactor {
 public:
  virtual ~ServerReactor() = default;
  virtual void OnDone() = 0;
  virtual void OnCancel() = 0;

  virtual bool InternalInlineable() { return false; }

 private:
  template <class Request, class Response>
  friend class CallbackUnaryHandler;
  template <class Request, class Response>
  friend class CallbackClientStreamingHandler;
  template <class Request, class Response>
  friend class CallbackServerStreamingHandler;
  template <class Request, class Response>
  friend class CallbackBidiHandler;
};

class ServerCallbackCall {
 public:
  virtual ~ServerCallbackCall() {}

  void MaybeDone() {
    if (GPR_UNLIKELY(Unref() == 1)) {
      ScheduleOnDone(reactor()->InternalInlineable());
    }
  }

  void MaybeDone(bool inline_ondone) {
    if (GPR_UNLIKELY(Unref() == 1)) {
      ScheduleOnDone(inline_ondone);
    }
  }

  void MaybeCallOnCancel(ServerReactor* reactor) {
    if (GPR_UNLIKELY(UnblockCancellation())) {
      CallOnCancel(reactor);
    }
  }

  void MaybeCallOnCancel() {
    if (GPR_UNLIKELY(UnblockCancellation())) {
      CallOnCancel(reactor());
    }
  }

 protected:

  void Ref() { callbacks_outstanding_.fetch_add(1, std::memory_order_relaxed); }

 private:
  virtual ServerReactor* reactor() = 0;

  virtual grpc_call* call() = 0;

  virtual void RunAsync(absl::AnyInvocable<void()> cb) {
    grpc_call_run_in_event_engine(call(), std::move(cb));
  }

  virtual void CallOnDone() = 0;

  void ScheduleOnDone(bool inline_ondone);

  void CallOnCancel(ServerReactor* reactor);

  bool UnblockCancellation() {
    return on_cancel_conditions_remaining_.fetch_sub(
               1, std::memory_order_acq_rel) == 1;
  }

  int Unref() {
    return callbacks_outstanding_.fetch_sub(1, std::memory_order_acq_rel);
  }

  std::atomic_int on_cancel_conditions_remaining_{2};
  std::atomic_int callbacks_outstanding_{
      3};
};

template <class Request, class Response>
class DefaultMessageHolder : public MessageHolder<Request, Response> {
 public:
  DefaultMessageHolder() {
    this->set_request(&request_obj_);
    this->set_response(&response_obj_);
  }
  void Release() override {

    this->~DefaultMessageHolder<Request, Response>();
  }

 private:
  Request request_obj_;
  Response response_obj_;
};

}

class ServerUnaryReactor;
template <class Request>
class ServerReadReactor;
template <class Response>
class ServerWriteReactor;
template <class Request, class Response>
class ServerBidiReactor;

// NOTE: The actual call/stream object classes are provided as API only to

class ServerCallbackUnary : public internal::ServerCallbackCall {
 public:
  ~ServerCallbackUnary() override {}
  virtual void Finish(grpc::Status s) = 0;
  virtual void SendInitialMetadata() = 0;

 protected:

  template <class Reactor>
  void BindReactor(Reactor* reactor) {
    reactor->InternalBindCall(this);
  }
};

template <class Request>
class ServerCallbackReader : public internal::ServerCallbackCall {
 public:
  ~ServerCallbackReader() override {}
  virtual void Finish(grpc::Status s) = 0;
  virtual void SendInitialMetadata() = 0;
  virtual void Read(Request* msg) = 0;

 protected:
  void BindReactor(ServerReadReactor<Request>* reactor) {
    reactor->InternalBindReader(this);
  }
};

template <class Response>
class ServerCallbackWriter : public internal::ServerCallbackCall {
 public:
  ~ServerCallbackWriter() override {}

  virtual void Finish(grpc::Status s) = 0;
  virtual void SendInitialMetadata() = 0;
  virtual void Write(const Response* msg, grpc::WriteOptions options) = 0;
  virtual void WriteAndFinish(const Response* msg, grpc::WriteOptions options,
                              grpc::Status s) = 0;

 protected:
  void BindReactor(ServerWriteReactor<Response>* reactor) {
    reactor->InternalBindWriter(this);
  }
};

template <class Request, class Response>
class ServerCallbackReaderWriter : public internal::ServerCallbackCall {
 public:
  ~ServerCallbackReaderWriter() override {}

  virtual void Finish(grpc::Status s) = 0;
  virtual void SendInitialMetadata() = 0;
  virtual void Read(Request* msg) = 0;
  virtual void Write(const Response* msg, grpc::WriteOptions options) = 0;
  virtual void WriteAndFinish(const Response* msg, grpc::WriteOptions options,
                              grpc::Status s) = 0;

 protected:
  void BindReactor(ServerBidiReactor<Request, Response>* reactor) {
    reactor->InternalBindStream(this);
  }
};

template <class Request, class Response>
class ServerBidiReactor : public internal::ServerReactor {
 public:
  // NOTE: Initializing stream_ as a constructor initializer rather than a

  ServerBidiReactor() : stream_(nullptr) {}
  ~ServerBidiReactor() override = default;

  void StartSendInitialMetadata() ABSL_LOCKS_EXCLUDED(stream_mu_) {
    ServerCallbackReaderWriter<Request, Response>* stream =
        stream_.load(std::memory_order_acquire);
    if (stream == nullptr) {
      grpc::internal::MutexLock l(&stream_mu_);
      stream = stream_.load(std::memory_order_relaxed);
      if (stream == nullptr) {
        backlog_.send_initial_metadata_wanted = true;
        return;
      }
    }
    stream->SendInitialMetadata();
  }

  void StartRead(Request* req) ABSL_LOCKS_EXCLUDED(stream_mu_) {
    ServerCallbackReaderWriter<Request, Response>* stream =
        stream_.load(std::memory_order_acquire);
    if (stream == nullptr) {
      grpc::internal::MutexLock l(&stream_mu_);
      stream = stream_.load(std::memory_order_relaxed);
      if (stream == nullptr) {
        backlog_.read_wanted = req;
        return;
      }
    }
    stream->Read(req);
  }

  void StartWrite(const Response* resp) {
    StartWrite(resp, grpc::WriteOptions());
  }

  void StartWrite(const Response* resp, grpc::WriteOptions options)
      ABSL_LOCKS_EXCLUDED(stream_mu_) {
    ServerCallbackReaderWriter<Request, Response>* stream =
        stream_.load(std::memory_order_acquire);
    if (stream == nullptr) {
      grpc::internal::MutexLock l(&stream_mu_);
      stream = stream_.load(std::memory_order_relaxed);
      if (stream == nullptr) {
        backlog_.write_wanted = resp;
        backlog_.write_options_wanted = options;
        return;
      }
    }
    stream->Write(resp, options);
  }

  void StartWriteAndFinish(const Response* resp, grpc::WriteOptions options,
                           grpc::Status s) ABSL_LOCKS_EXCLUDED(stream_mu_) {
    ServerCallbackReaderWriter<Request, Response>* stream =
        stream_.load(std::memory_order_acquire);
    if (stream == nullptr) {
      grpc::internal::MutexLock l(&stream_mu_);
      stream = stream_.load(std::memory_order_relaxed);
      if (stream == nullptr) {
        backlog_.write_and_finish_wanted = true;
        backlog_.write_wanted = resp;
        backlog_.write_options_wanted = options;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    stream->WriteAndFinish(resp, options, std::move(s));
  }

  void StartWriteLast(const Response* resp, grpc::WriteOptions options) {
    StartWrite(resp, options.set_last_message());
  }

  void Finish(grpc::Status s) ABSL_LOCKS_EXCLUDED(stream_mu_) {
    ServerCallbackReaderWriter<Request, Response>* stream =
        stream_.load(std::memory_order_acquire);
    if (stream == nullptr) {
      grpc::internal::MutexLock l(&stream_mu_);
      stream = stream_.load(std::memory_order_relaxed);
      if (stream == nullptr) {
        backlog_.finish_wanted = true;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    stream->Finish(std::move(s));
  }

  virtual void OnSendInitialMetadataDone(bool ) {}

  virtual void OnReadDone(bool ) {}

  virtual void OnWriteDone(bool ) {}

  void OnDone() override = 0;

  void OnCancel() override {}

 private:
  friend class ServerCallbackReaderWriter<Request, Response>;

  virtual void InternalBindStream(
      ServerCallbackReaderWriter<Request, Response>* stream) {
    grpc::internal::MutexLock l(&stream_mu_);

    if (GPR_UNLIKELY(backlog_.send_initial_metadata_wanted)) {
      stream->SendInitialMetadata();
    }
    if (GPR_UNLIKELY(backlog_.read_wanted != nullptr)) {
      stream->Read(backlog_.read_wanted);
    }
    if (GPR_UNLIKELY(backlog_.write_and_finish_wanted)) {
      stream->WriteAndFinish(backlog_.write_wanted,
                             std::move(backlog_.write_options_wanted),
                             std::move(backlog_.status_wanted));
    } else {
      if (GPR_UNLIKELY(backlog_.write_wanted != nullptr)) {
        stream->Write(backlog_.write_wanted,
                      std::move(backlog_.write_options_wanted));
      }
      if (GPR_UNLIKELY(backlog_.finish_wanted)) {
        stream->Finish(std::move(backlog_.status_wanted));
      }
    }

    stream_.store(stream, std::memory_order_release);
  }

  grpc::internal::Mutex stream_mu_;

  std::atomic<ServerCallbackReaderWriter<Request, Response>*> stream_{nullptr};
  struct PreBindBacklog {
    bool send_initial_metadata_wanted = false;
    bool write_and_finish_wanted = false;
    bool finish_wanted = false;
    Request* read_wanted = nullptr;
    const Response* write_wanted = nullptr;
    grpc::WriteOptions write_options_wanted;
    grpc::Status status_wanted;
  };
  PreBindBacklog backlog_ ABSL_GUARDED_BY(stream_mu_);
};

template <class Request>
class ServerReadReactor : public internal::ServerReactor {
 public:
  ServerReadReactor() : reader_(nullptr) {}
  ~ServerReadReactor() override = default;

  void StartSendInitialMetadata() ABSL_LOCKS_EXCLUDED(reader_mu_) {
    ServerCallbackReader<Request>* reader =
        reader_.load(std::memory_order_acquire);
    if (reader == nullptr) {
      grpc::internal::MutexLock l(&reader_mu_);
      reader = reader_.load(std::memory_order_relaxed);
      if (reader == nullptr) {
        backlog_.send_initial_metadata_wanted = true;
        return;
      }
    }
    reader->SendInitialMetadata();
  }
  void StartRead(Request* req) ABSL_LOCKS_EXCLUDED(reader_mu_) {
    ServerCallbackReader<Request>* reader =
        reader_.load(std::memory_order_acquire);
    if (reader == nullptr) {
      grpc::internal::MutexLock l(&reader_mu_);
      reader = reader_.load(std::memory_order_relaxed);
      if (reader == nullptr) {
        backlog_.read_wanted = req;
        return;
      }
    }
    reader->Read(req);
  }
  void Finish(grpc::Status s) ABSL_LOCKS_EXCLUDED(reader_mu_) {
    ServerCallbackReader<Request>* reader =
        reader_.load(std::memory_order_acquire);
    if (reader == nullptr) {
      grpc::internal::MutexLock l(&reader_mu_);
      reader = reader_.load(std::memory_order_relaxed);
      if (reader == nullptr) {
        backlog_.finish_wanted = true;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    reader->Finish(std::move(s));
  }

  virtual void OnSendInitialMetadataDone(bool ) {}
  virtual void OnReadDone(bool ) {}
  void OnDone() override = 0;
  void OnCancel() override {}

 private:
  friend class ServerCallbackReader<Request>;

  virtual void InternalBindReader(ServerCallbackReader<Request>* reader)
      ABSL_LOCKS_EXCLUDED(reader_mu_) {
    grpc::internal::MutexLock l(&reader_mu_);

    if (GPR_UNLIKELY(backlog_.send_initial_metadata_wanted)) {
      reader->SendInitialMetadata();
    }
    if (GPR_UNLIKELY(backlog_.read_wanted != nullptr)) {
      reader->Read(backlog_.read_wanted);
    }
    if (GPR_UNLIKELY(backlog_.finish_wanted)) {
      reader->Finish(std::move(backlog_.status_wanted));
    }

    reader_.store(reader, std::memory_order_release);
  }

  grpc::internal::Mutex reader_mu_;
  std::atomic<ServerCallbackReader<Request>*> reader_{nullptr};
  struct PreBindBacklog {
    bool send_initial_metadata_wanted = false;
    bool finish_wanted = false;
    Request* read_wanted = nullptr;
    grpc::Status status_wanted;
  };
  PreBindBacklog backlog_ ABSL_GUARDED_BY(reader_mu_);
};

template <class Response>
class ServerWriteReactor : public internal::ServerReactor {
 public:
  ServerWriteReactor() : writer_(nullptr) {}
  ~ServerWriteReactor() override = default;

  void StartSendInitialMetadata() ABSL_LOCKS_EXCLUDED(writer_mu_) {
    ServerCallbackWriter<Response>* writer =
        writer_.load(std::memory_order_acquire);
    if (writer == nullptr) {
      grpc::internal::MutexLock l(&writer_mu_);
      writer = writer_.load(std::memory_order_relaxed);
      if (writer == nullptr) {
        backlog_.send_initial_metadata_wanted = true;
        return;
      }
    }
    writer->SendInitialMetadata();
  }
  void StartWrite(const Response* resp) {
    StartWrite(resp, grpc::WriteOptions());
  }
  void StartWrite(const Response* resp, grpc::WriteOptions options)
      ABSL_LOCKS_EXCLUDED(writer_mu_) {
    ServerCallbackWriter<Response>* writer =
        writer_.load(std::memory_order_acquire);
    if (writer == nullptr) {
      grpc::internal::MutexLock l(&writer_mu_);
      writer = writer_.load(std::memory_order_relaxed);
      if (writer == nullptr) {
        backlog_.write_wanted = resp;
        backlog_.write_options_wanted = options;
        return;
      }
    }
    writer->Write(resp, options);
  }
  void StartWriteAndFinish(const Response* resp, grpc::WriteOptions options,
                           grpc::Status s) ABSL_LOCKS_EXCLUDED(writer_mu_) {
    ServerCallbackWriter<Response>* writer =
        writer_.load(std::memory_order_acquire);
    if (writer == nullptr) {
      grpc::internal::MutexLock l(&writer_mu_);
      writer = writer_.load(std::memory_order_relaxed);
      if (writer == nullptr) {
        backlog_.write_and_finish_wanted = true;
        backlog_.write_wanted = resp;
        backlog_.write_options_wanted = options;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    writer->WriteAndFinish(resp, options, std::move(s));
  }
  void StartWriteLast(const Response* resp, grpc::WriteOptions options) {
    StartWrite(resp, options.set_last_message());
  }
  void Finish(grpc::Status s) ABSL_LOCKS_EXCLUDED(writer_mu_) {
    ServerCallbackWriter<Response>* writer =
        writer_.load(std::memory_order_acquire);
    if (writer == nullptr) {
      grpc::internal::MutexLock l(&writer_mu_);
      writer = writer_.load(std::memory_order_relaxed);
      if (writer == nullptr) {
        backlog_.finish_wanted = true;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    writer->Finish(std::move(s));
  }

  virtual void OnSendInitialMetadataDone(bool ) {}
  virtual void OnWriteDone(bool ) {}
  void OnDone() override = 0;
  void OnCancel() override {}

 private:
  friend class ServerCallbackWriter<Response>;

  virtual void InternalBindWriter(ServerCallbackWriter<Response>* writer)
      ABSL_LOCKS_EXCLUDED(writer_mu_) {
    grpc::internal::MutexLock l(&writer_mu_);

    if (GPR_UNLIKELY(backlog_.send_initial_metadata_wanted)) {
      writer->SendInitialMetadata();
    }
    if (GPR_UNLIKELY(backlog_.write_and_finish_wanted)) {
      writer->WriteAndFinish(backlog_.write_wanted,
                             std::move(backlog_.write_options_wanted),
                             std::move(backlog_.status_wanted));
    } else {
      if (GPR_UNLIKELY(backlog_.write_wanted != nullptr)) {
        writer->Write(backlog_.write_wanted,
                      std::move(backlog_.write_options_wanted));
      }
      if (GPR_UNLIKELY(backlog_.finish_wanted)) {
        writer->Finish(std::move(backlog_.status_wanted));
      }
    }

    writer_.store(writer, std::memory_order_release);
  }

  grpc::internal::Mutex writer_mu_;
  std::atomic<ServerCallbackWriter<Response>*> writer_{nullptr};
  struct PreBindBacklog {
    bool send_initial_metadata_wanted = false;
    bool write_and_finish_wanted = false;
    bool finish_wanted = false;
    const Response* write_wanted = nullptr;
    grpc::WriteOptions write_options_wanted;
    grpc::Status status_wanted;
  };
  PreBindBacklog backlog_ ABSL_GUARDED_BY(writer_mu_);
};

class ServerUnaryReactor : public internal::ServerReactor {
 public:
  ServerUnaryReactor() : call_(nullptr) {}
  ~ServerUnaryReactor() override = default;

  void StartSendInitialMetadata() ABSL_LOCKS_EXCLUDED(call_mu_) {
    ServerCallbackUnary* call = call_.load(std::memory_order_acquire);
    if (call == nullptr) {
      grpc::internal::MutexLock l(&call_mu_);
      call = call_.load(std::memory_order_relaxed);
      if (call == nullptr) {
        backlog_.send_initial_metadata_wanted = true;
        return;
      }
    }
    call->SendInitialMetadata();
  }

  void Finish(grpc::Status s) ABSL_LOCKS_EXCLUDED(call_mu_) {
    ServerCallbackUnary* call = call_.load(std::memory_order_acquire);
    if (call == nullptr) {
      grpc::internal::MutexLock l(&call_mu_);
      call = call_.load(std::memory_order_relaxed);
      if (call == nullptr) {
        backlog_.finish_wanted = true;
        backlog_.status_wanted = std::move(s);
        return;
      }
    }
    call->Finish(std::move(s));
  }

  virtual void OnSendInitialMetadataDone(bool ) {}
  void OnDone() override = 0;
  void OnCancel() override {}

 private:
  friend class ServerCallbackUnary;

  virtual void InternalBindCall(ServerCallbackUnary* call)
      ABSL_LOCKS_EXCLUDED(call_mu_) {
    grpc::internal::MutexLock l(&call_mu_);

    if (GPR_UNLIKELY(backlog_.send_initial_metadata_wanted)) {
      call->SendInitialMetadata();
    }
    if (GPR_UNLIKELY(backlog_.finish_wanted)) {
      call->Finish(std::move(backlog_.status_wanted));
    }

    call_.store(call, std::memory_order_release);
  }

  grpc::internal::Mutex call_mu_;
  std::atomic<ServerCallbackUnary*> call_{nullptr};
  struct PreBindBacklog {
    bool send_initial_metadata_wanted = false;
    bool finish_wanted = false;
    grpc::Status status_wanted;
  };
  PreBindBacklog backlog_ ABSL_GUARDED_BY(call_mu_);
};

namespace internal {

template <class Base>
class FinishOnlyReactor : public Base {
 public:
  explicit FinishOnlyReactor(grpc::Status s) { this->Finish(std::move(s)); }
  void OnDone() override { this->~FinishOnlyReactor(); }
};

using UnimplementedUnaryReactor = FinishOnlyReactor<ServerUnaryReactor>;
template <class Request>
using UnimplementedReadReactor = FinishOnlyReactor<ServerReadReactor<Request>>;
template <class Response>
using UnimplementedWriteReactor =
    FinishOnlyReactor<ServerWriteReactor<Response>>;
template <class Request, class Response>
using UnimplementedBidiReactor =
    FinishOnlyReactor<ServerBidiReactor<Request, Response>>;

}

namespace experimental {

template <class Request, class Response>
using ServerBidiReactor = ::grpc::ServerBidiReactor<Request, Response>;

}

}

#endif
