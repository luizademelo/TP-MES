Here's the commented version of the code:

```c++
// Copyright 2019 gRPC authors.

#ifndef GRPCPP_IMPL_SERVER_CALLBACK_HANDLERS_H
#define GRPCPP_IMPL_SERVER_CALLBACK_HANDLERS_H

#include <grpc/grpc.h>
#include <grpc/impl/call.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/support/status.h>

#include "absl/log/absl_check.h"

namespace grpc {
namespace internal {

// Handler for unary RPC calls (single request, single response)
template <class RequestType, class ResponseType>
class CallbackUnaryHandler : public grpc::internal::MethodHandler {
 public:
  // Constructor that takes a function to get the reactor for this call
  explicit CallbackUnaryHandler(
      std::function<ServerUnaryReactor*(grpc::CallbackServerContext*,
                                        const RequestType*, ResponseType*)>
          get_reactor)
      : get_reactor_(std::move(get_reactor)) {}

  // Sets the message allocator for request/response messages
  void SetMessageAllocator(
      MessageAllocator<RequestType, ResponseType>* allocator) {
    allocator_ = allocator;
  }

  // Main handler method called when a request comes in
  void RunHandler(const HandlerParameter& param) final {
    // Increment call reference count
    grpc_call_ref(param.call->call());
    
    // Get message allocator state from internal data
    auto* allocator_state =
        static_cast<MessageHolder<RequestType, ResponseType>*>(
            param.internal_data);

    // Create server callback implementation in call arena
    auto* call = new (grpc_call_arena_alloc(param.call->call(),
                                            sizeof(ServerCallbackUnaryImpl)))
        ServerCallbackUnaryImpl(
            static_cast<grpc::CallbackServerContext*>(param.server_context),
            param.call, allocator_state, param.call_requester);
    
    // Begin completion operation for this call
    param.server_context->BeginCompletionOp(
        param.call, [call](bool) { call->MaybeDone(); }, call);

    // Get the reactor for this call (if status is OK)
    ServerUnaryReactor* reactor = nullptr;
    if (param.status.ok()) {
      reactor = grpc::internal::CatchingReactorGetter<ServerUnaryReactor>(
          get_reactor_,
          static_cast<grpc::CallbackServerContext*>(param.server_context),
          call->request(), call->response());
    }

    // If no reactor was created (or error occurred), use unimplemented reactor
    if (reactor == nullptr) {
      reactor = new (grpc_call_arena_alloc(param.call->call(),
                                           sizeof(UnimplementedUnaryReactor)))
          UnimplementedUnaryReactor(
              grpc::Status(grpc::StatusCode::UNIMPLEMENTED, ""));
    }

    // Setup the reactor for this call
    call->SetupReactor(reactor);
  }

  // Deserialize the incoming request
  void* Deserialize(grpc_call* call, grpc_byte_buffer* req,
                    grpc::Status* status, void** handler_data) final {
    grpc::ByteBuffer buf;
    buf.set_buffer(req);
    RequestType* request = nullptr;
    MessageHolder<RequestType, ResponseType>* allocator_state;
    
    // Allocate message holder using custom allocator if available
    if (allocator_ != nullptr) {
      allocator_state = allocator_->AllocateMessages();
    } else {
      allocator_state = new (grpc_call_arena_alloc(
          call, sizeof(DefaultMessageHolder<RequestType, ResponseType>)))
          DefaultMessageHolder<RequestType, ResponseType>();
    }
    
    *handler_data = allocator_state;
    request = allocator_state->request();
    
    // Deserialize the request
    *status =
        grpc::SerializationTraits<RequestType>::Deserialize(&buf, request);
    buf.Release();
    
    // Return request if deserialization succeeded
    if (status->ok()) {
      return request;
    }
    return nullptr;
  }

 private:
  // Function to get the reactor for this call
  std::function<ServerUnaryReactor*(grpc::CallbackServerContext*,
                                    const RequestType*, ResponseType*)>
      get_reactor_;
  // Message allocator for request/response messages
  MessageAllocator<RequestType, ResponseType>* allocator_ = nullptr;

  // Implementation of ServerCallbackUnary interface
  class ServerCallbackUnaryImpl : public ServerCallbackUnary {
   public:
    // Finish the call with given status
    void Finish(grpc::Status s) override {
      // Set up finish operation callback
      finish_tag_.Set(
          call_.call(),
          [this](bool) {
            this->MaybeDone(
                reactor_.load(std::memory_order_relaxed)->InternalInlineable());
          },
          &finish_ops_, true);
      finish_ops_.set_core_cq_tag(&finish_tag_);

      // Send initial metadata if not already sent
      if (!ctx_->sent_initial_metadata_) {
        finish_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                        ctx_->initial_metadata_flags());
        if (ctx_->compression_level_set()) {
          finish_ops_.set_compression_level(ctx_->compression_level());
        }
        ctx_->sent_initial_metadata_ = true;
      }

      // Send response if status is OK, otherwise just send status
      if (s.ok()) {
        finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_,
                                     finish_ops_.SendMessagePtr(response()));
      } else {
        finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, s);
      }
      finish_ops_.set_core_cq_tag(&finish_tag_);
      call_.PerformOps(&finish_ops_);
    }

    // Send initial metadata
    void SendInitialMetadata() override {
      ABSL_CHECK(!ctx_->sent_initial_metadata_);
      this->Ref();

      // Set up metadata operation callback
      meta_tag_.Set(
          call_.call(),
          [this](bool ok) {
            ServerUnaryReactor* reactor =
                reactor_.load(std::memory_order_relaxed);
            reactor->OnSendInitialMetadataDone(ok);
            this->MaybeDone(true);
          },
          &meta_ops_, false);
      meta_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                    ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        meta_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
      meta_ops_.set_core_cq_tag(&meta_tag_);
      call_.PerformOps(&meta_ops_);
    }

   private:
    friend class CallbackUnaryHandler<RequestType, ResponseType>;

    // Constructor
    ServerCallbackUnaryImpl(
        grpc::CallbackServerContext* ctx, grpc::internal::Call* call,
        MessageHolder<RequestType, ResponseType>* allocator_state,
        std::function<void()> call_requester)
        : ctx_(ctx),
          call_(*call),
          allocator_state_(allocator_state),
          call_requester_(std::move(call_requester)) {
      ctx_->set_message_allocator_state(allocator_state);
    }

    // Get underlying gRPC call
    grpc_call* call() override { return call_.call(); }

    // Setup the reactor for this call
    void SetupReactor(ServerUnaryReactor* reactor) {
      reactor_.store(reactor, std::memory_order_relaxed);
      this->BindReactor(reactor);
      this->MaybeCallOnCancel(reactor);
      this->MaybeDone(reactor->InternalInlineable());
    }

    // Get request message
    const RequestType* request() { return allocator_state_->request(); }
    // Get response message
    ResponseType* response() { return allocator_state_->response(); }

    // Called when call is done
    void CallOnDone() override {
      reactor_.load(std::memory_order_relaxed)->OnDone();
      grpc_call* call = call_.call();
      auto call_requester = std::move(call_requester_);
      allocator_state_->Release();
      if (ctx_->context_allocator() != nullptr) {
        ctx_->context_allocator()->Release(ctx_);
      }
      this->~ServerCallbackUnaryImpl();
      grpc_call_unref(call);
      call_requester();
    }

    // Get the reactor for this call
    ServerReactor* reactor() override {
      return reactor_.load(std::memory_order_relaxed);
    }

    // Operations for sending metadata
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
        meta_ops_;
    grpc::internal::CallbackWithSuccessTag meta_tag_;
    
    // Operations for finishing the call
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpServerSendStatus>
        finish_ops_;
    grpc::internal::CallbackWithSuccessTag finish_tag_;

    // Context for this call
    grpc::CallbackServerContext* const ctx_;
    // Underlying gRPC call
    grpc::internal::Call call_;
    // Message allocator state
    MessageHolder<RequestType, ResponseType>* const allocator_state_;
    // Function to request new calls
    std::function<void()> call_requester_;

    // Reactor for this call
    std::atomic<ServerUnaryReactor*> reactor_;

    // Counter for outstanding callbacks
    std::atomic<intptr_t> callbacks_outstanding_{3};
  };
};

// Handler for client streaming RPC calls (stream of requests, single response)
template <class RequestType, class ResponseType>
class CallbackClientStreamingHandler : public grpc::internal::MethodHandler {
 public:
  // Constructor that takes a function to get the reactor for this call
  explicit CallbackClientStreamingHandler(
      std::function<ServerReadReactor<RequestType>*(
          grpc::CallbackServerContext*, ResponseType*)>
          get_reactor)
      : get_reactor_(std::move(get_reactor)) {}
  
  // Main handler method called when a request comes in
  void RunHandler(const HandlerParameter& param) final {
    // Increment call reference count
    grpc_call_ref(param.call->call());

    // Create server callback reader implementation in call arena
    auto* reader = new (grpc_call_arena_alloc(param.call->call(),
                                              sizeof(ServerCallbackReaderImpl)))
        ServerCallbackReaderImpl(
            static_cast<grpc::CallbackServerContext*>(param.server_context),
            param.call, param.call_requester);

    // Begin completion operation for this call
    param.server_context->BeginCompletionOp(
        param.call,
        [reader](bool) { reader->MaybeDone(false); },
        reader);

    // Get the reactor for this call (if status is OK)
    ServerReadReactor<RequestType>* reactor = nullptr;
    if (param.status.ok()) {
      reactor =
          grpc::internal::CatchingReactorGetter<ServerReadReactor<RequestType>>(
              get_reactor_,
              static_cast<grpc::CallbackServerContext*>(param.server_context),
              reader->response());
    }

    // If no reactor was created (or error occurred), use unimplemented reactor
    if (reactor == nullptr) {
      reactor = new (grpc_call_arena_alloc(
          param.call->call(), sizeof(UnimplementedReadReactor<RequestType>)))
          UnimplementedReadReactor<RequestType>(
              grpc::Status(grpc::StatusCode::UNIMPLEMENTED, ""));
    }

    // Setup the reactor for this call
    reader->SetupReactor(reactor);
  }

 private:
  // Function to get the reactor for this call
  std::function<ServerReadReactor<RequestType>*(grpc::CallbackServerContext*,
                                                ResponseType*)>
      get_reactor_;

  // Implementation of ServerCallbackReader interface
  class ServerCallbackReaderImpl : public ServerCallbackReader<RequestType> {
   public:
    // Finish the call with given status
    void Finish(grpc::Status s) override {
      // Set up finish operation callback
      finish_tag_.Set(
          call_.call(),
          [this](bool) {
            this->MaybeDone(false);
          },
          &finish_ops_, true);
      
      // Send initial metadata if not already sent
      if (!ctx_->sent_initial_metadata_) {
        finish_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                        ctx_->initial_metadata_flags());
        if (ctx_->compression_level_set()) {
          finish_ops_.set_compression_level(ctx_->compression_level());
        }
        ctx_->sent_initial_metadata_ = true;
      }

      // Send response if status is OK, otherwise just send status
      if (s.ok()) {
        finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_,
                                     finish_ops_.SendMessagePtr(&resp_));
      } else {
        finish_ops_.ServerSendStatus(&ctx_->trailing_metadata_, s);
      }
      finish_ops_.set_core_cq_tag(&finish_tag_);
      call_.PerformOps(&finish_ops_);
    }

    // Send initial metadata
    void SendInitialMetadata() override {
      ABSL_CHECK(!ctx_->sent_initial_metadata_);
      this->Ref();

      // Set up metadata operation callback
      meta_tag_.Set(
          call_.call(),
          [this](bool ok) {
            ServerReadReactor<RequestType>* reactor =
                reactor_.load(std::memory_order_relaxed);
            reactor->OnSendInitialMetadataDone(ok);
            this->MaybeDone(true);
          },
          &meta_ops_, false);
      meta_ops_.SendInitialMetadata(&ctx_->initial_metadata_,
                                    ctx_->initial_metadata_flags());
      if (ctx_->compression_level_set()) {
        meta_ops_.set_compression_level(ctx_->compression_level());
      }
      ctx_->sent_initial_metadata_ = true;
      meta_ops_.set_core_cq_tag(&meta_tag_);
      call_.PerformOps(&meta_ops_);
    }

    // Read a request message from the stream
    void Read(RequestType* req) override {
      this->Ref();
      read_ops_.RecvMessage(req);
      call_.PerformOps(&read_ops_);
    }

   private:
    friend class CallbackClientStreamingHandler<RequestType, ResponseType>;

    // Constructor
    ServerCallbackReaderImpl(grpc::CallbackServerContext* ctx,
                             grpc::internal::Call* call,
                             std::function<void()> call_requester)
        : ctx_(ctx), call_(*call), call_requester_(std::move(call_requester)) {}

    // Get underlying gRPC call
    grpc_call* call() override { return call_.call(); }

    // Setup the reactor for this call
    void SetupReactor(ServerReadReactor<RequestType>* reactor) {
      reactor_.store(reactor, std::memory_order_relaxed);

      // Set up read operation callback
      read_tag_.Set(
          call_.call(),
          [this, reactor](bool ok) {
            if (GPR_UNLIKELY(!ok)) {
              ctx_->MaybeMarkCancelledOnRead();
            }
            reactor->OnReadDone(ok);
            this->MaybeDone(true);
          },
          &read_ops_, false);
      read_ops_.set_core_cq_tag(&read_tag_);
      this->BindReactor(reactor);
      this->MaybeCallOnCancel(reactor);

      this->MaybeDone(false);
    }

    // Destructor
    ~ServerCallbackReaderImpl() {}

    // Get response message
    ResponseType* response() { return &resp_; }

    // Called when call is done
    void CallOnDone() override {
      reactor_.load(std::memory_order_relaxed)->OnDone();
      grpc_call* call = call_.call();
      auto call_requester = std::move(call_requester_);
      if (ctx_->context_allocator() != nullptr) {
        ctx_->context_allocator()->Release(ctx_);
      }
      this->~ServerCallbackReaderImpl();
      grpc_call_unref(call);
      call_requester();
    }

    // Get the reactor for this call
    ServerReactor* reactor() override {
      return reactor_.load(std::memory_order_relaxed);
    }

    // Operations for sending metadata
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata>
        meta_ops_;
    grpc::internal::CallbackWithSuccessTag meta_tag_;
    
    // Operations for finishing the call
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpServerSendStatus>
        finish_ops_;
    grpc::internal::CallbackWithSuccessTag finish_tag_;
    
    // Operations for reading messages
    grpc::internal::CallOpSet<grpc::internal::CallOpRecvMessage<RequestType>>
        read_ops_;
    grpc::internal::CallbackWithSuccessTag read_tag_;

    // Context for this call
    grpc::CallbackServerContext* const ctx_;
    // Underlying gRPC call
    grpc::internal::Call call_;
    // Response message
    ResponseType resp_;
    // Function to request new calls
    std::function<void()> call_requester_;

    // Reactor for this call
    std::atomic<ServerReadReactor<RequestType>*> reactor_;

    // Counter for outstanding callbacks
    std::atomic<intptr_t> callbacks_outstanding_{3};
  };
};

// Handler for server streaming RPC calls (single request, stream of responses)
template <class RequestType, class ResponseType>
class CallbackServerStreamingHandler : public grpc::internal::MethodHandler {
 public:
  // Constructor that takes a function to get the reactor for this call
  explicit CallbackServerStreamingHandler(
      std::function<ServerWriteRe