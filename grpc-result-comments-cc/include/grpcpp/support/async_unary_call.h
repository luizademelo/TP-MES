Here's the commented version of the code:

```c++
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

// Forward declaration of ClientAsyncResponseReader
template <class R>
class ClientAsyncResponseReader;

// Interface for asynchronous client-side unary RPC operations
template <class R>
class ClientAsyncResponseReaderInterface {
 public:
  virtual ~ClientAsyncResponseReaderInterface() {}

  // Starts the RPC call
  virtual void StartCall() = 0;

  // Reads initial metadata from server (optional)
  virtual void ReadInitialMetadata(void* tag) = 0;

  // Completes the RPC and gets the response message and status
  virtual void Finish(R* msg, grpc::Status* status, void* tag) = 0;
};

namespace internal {

// Helper class for creating and setting up ClientAsyncResponseReader objects
class ClientAsyncResponseReaderHelper {
 public:
  // Creates a new ClientAsyncResponseReader instance and sets up the RPC call
  template <class R, class W, class BaseR = R, class BaseW = W>
  static ClientAsyncResponseReader<R>* Create(
      grpc::ChannelInterface* channel, grpc::CompletionQueue* cq,
      const grpc::internal::RpcMethod& method, grpc::ClientContext* context,
      const W& request)  {
    // Create the underlying gRPC call
    grpc::internal::Call call = channel->CreateCall(method, context, cq);
    // Allocate and construct the ClientAsyncResponseReader in the call arena
    ClientAsyncResponseReader<R>* result = new (grpc_call_arena_alloc(
        call.call(), sizeof(ClientAsyncResponseReader<R>)))
        ClientAsyncResponseReader<R>(call, context);
    // Set up the request with proper type handling
    SetupRequest<BaseR, BaseW>(
        call.call(), &result->single_buf_, &result->read_initial_metadata_,
        &result->finish_, static_cast<const BaseW&>(request));

    return result;
  }

  // Sets up the request operations for the async call
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
    // Define the operation set for the initial request
    using SingleBufType =
        grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                                  grpc::internal::CallOpSendMessage,
                                  grpc::internal::CallOpClientSendClose,
                                  grpc::internal::CallOpRecvInitialMetadata,
                                  grpc::internal::CallOpRecvMessage<R>,
                                  grpc::internal::CallOpClientRecvStatus>;
    // Allocate the operation set in the call arena
    SingleBufType* single_buf =
        new (grpc_call_arena_alloc(call, sizeof(SingleBufType))) SingleBufType;
    *single_buf_ptr = single_buf;

    // Set up the request message and close client sending
    ABSL_CHECK(single_buf->SendMessage(request).ok());
    single_buf->ClientSendClose();

    // Set up the function for reading initial metadata
    *read_initial_metadata =
        [](ClientContext* context, internal::Call* call,
           internal::CallOpSendInitialMetadata* single_buf_view, void* tag) {
          auto* single_buf = static_cast<SingleBufType*>(single_buf_view);
          single_buf->set_output_tag(tag);
          single_buf->RecvInitialMetadata(context);
          call->PerformOps(single_buf);
        };

    // Set up the function for finishing the call
    *finish = [](ClientContext* context, internal::Call* call,
                 bool initial_metadata_read,
                 internal::CallOpSendInitialMetadata* single_buf_view,
                 internal::CallOpSetInterface** finish_buf_ptr, void* msg,
                 Status* status, void* tag) {
      if (initial_metadata_read) {
        // If initial metadata was already read, use a simpler operation set
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
        // If initial metadata wasn't read, use the full operation set
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

  // Starts the actual RPC call
  static void StartCall(grpc::ClientContext* context,
                        grpc::internal::CallOpSendInitialMetadata* single_buf) {
    single_buf->SendInitialMetadata(&context->send_initial_metadata_,
                                    context->initial_metadata_flags());
  }
};

// Factory class for creating ClientAsyncResponseReader instances
template <class R>
class ClientAsyncResponseReaderFactory {
 public:
  // Creates a new ClientAsyncResponseReader, optionally starting the call
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

}  // namespace internal

// Implementation of ClientAsyncResponseReaderInterface for unary RPCs
template <class R>
class ClientAsyncResponseReader final
    : public ClientAsyncResponseReaderInterface<R> {
 public:
  // Custom delete operators to ensure proper memory management
  static void operator delete(void* , std::size_t size) {
    ABSL_CHECK_EQ(size, sizeof(ClientAsyncResponseReader));
  }

  static void operator delete(void*, void*) { ABSL_CHECK(false); }

  // Starts the RPC call
  void StartCall() override {
    ABSL_DCHECK(!started_);
    started_ = true;
    internal::ClientAsyncResponseReaderHelper::StartCall(context_, single_buf_);
  }

  // Reads initial metadata from the server
  void ReadInitialMetadata(void* tag) override {
    ABSL_DCHECK(started_);
    ABSL_DCHECK(!context_->initial_metadata_received_);
    read_initial_metadata_(context_, &call_, single_buf_, tag);
    initial_metadata_read_ = true;
  }

  // Completes the RPC and gets the response
  void Finish(R* msg, grpc::Status* status, void* tag) override {
    ABSL_DCHECK(started_);
    finish_(context_, &call_, initial_metadata_read_, single_buf_, &finish_buf_,
            static_cast<void*>(msg), status, tag);
  }

 private:
  friend class internal::ClientAsyncResponseReaderHelper;
  grpc::ClientContext* const context_;  // Client context for the call
  grpc::internal::Call call_;           // The underlying gRPC call
  bool started_ = false;                // Whether the call has started
  bool initial_metadata_read_ = false;  // Whether initial metadata was read

  // Private constructor - only to be called by helper class
  ClientAsyncResponseReader(grpc::internal::Call call,
                            grpc::ClientContext* context)
      : context_(context), call_(call) {}

  // Custom new operators for arena allocation
  static void* operator new(std::size_t size);
  static void* operator new(std::size_t , void* p) { return p; }

  // Operation buffers and handlers
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

// Server-side handler for asynchronous unary RPC responses
template <class W>
class ServerAsyncResponseWriter final
    : public grpc::internal::ServerAsyncStreamingInterface {
 public:
  explicit ServerAsyncResponseWriter(grpc::ServerContext* ctx)
      : call_(nullptr, nullptr, nullptr), ctx_(ctx) {}

  // Sends initial metadata to the client
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

  // Completes the RPC with a response message and status
  // Note: if status has a non-OK code, then msg will not be sent
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

  // Completes the RPC with an error status (no message sent)
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
  // Binds the call to this writer
  void BindCall(grpc::internal::Call* call) override { call_ = *call; }

  grpc::internal::Call call_;  // The underlying gRPC call
  grpc::ServerContext* ctx_;   // Server context for the call
  // Operation buffers
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
      meta_buf_;
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      finish_buf_;
};

}  // namespace grpc

// Specializations of std::default_delete to prevent deletion of these objects
// (they are managed by gRPC's arena allocator)
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

#endif  // GRPCPP_SUPPORT_ASYNC_UNARY_CALL_H
```

The comments explain:
1. The purpose of each class and its role in the async unary call process
2. The functionality of each method
3. Important implementation details
4. Memory management considerations
5. The flow of operations for both client and server sides
6. Special cases and error handling

The comments are placed to be helpful for future maintainers while not being overly verbose or explaining obvious things. They focus on the "why" and "how" rather than just repeating what the code does.