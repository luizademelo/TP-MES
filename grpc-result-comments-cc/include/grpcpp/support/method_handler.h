Here's the commented version of the code:

```c++
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_METHOD_HANDLER_H
#define GRPCPP_SUPPORT_METHOD_HANDLER_H

#include <grpc/byte_buffer.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/sync_stream.h>

#include "absl/log/absl_check.h"

namespace grpc {

namespace internal {

// Wraps a callable handler function with exception handling when exceptions are enabled
// Returns UNKNOWN status if an exception occurs, otherwise returns the handler's status
template <class Callable>
::grpc::Status CatchingFunctionHandler(Callable&& handler) {
#if GRPC_ALLOW_EXCEPTIONS
  try {
    return handler();
  } catch (...) {
    return grpc::Status(grpc::StatusCode::UNKNOWN,
                        "Unexpected error in RPC handling");
  }
#else
  return handler();
#endif
}

// Helper function for unary RPCs that handles sending response and status
// Sets up and performs the necessary gRPC operations for a unary response
template <class ResponseType>
void UnaryRunHandlerHelper(const MethodHandler::HandlerParameter& param,
                           ResponseType* rsp, grpc::Status& status) {
  ABSL_CHECK(!param.server_context->sent_initial_metadata_);
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      ops;
  // Set up initial metadata
  ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                          param.server_context->initial_metadata_flags());
  // Apply compression if set
  if (param.server_context->compression_level_set()) {
    ops.set_compression_level(param.server_context->compression_level());
  }
  // Send message if status is OK
  if (status.ok()) {
    status = ops.SendMessagePtr(rsp);
  }
  // Send final status to client
  ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
  // Perform the operations and wait for completion
  param.call->PerformOps(&ops);
  param.call->cq()->Pluck(&ops);
}

// Helper function for deserializing unary request messages
// Returns deserialized request object or nullptr if deserialization fails
template <class RequestType>
void* UnaryDeserializeHelper(grpc_byte_buffer* req, grpc::Status* status,
                             RequestType* request) {
  grpc::ByteBuffer buf;
  buf.set_buffer(req);
  *status = grpc::SerializationTraits<RequestType>::Deserialize(
      &buf, static_cast<RequestType*>(request));
  buf.Release();
  if (status->ok()) {
    return request;
  }
  // Clean up if deserialization failed
  request->~RequestType();
  return nullptr;
}

// Handler for unary RPC methods
template <class ServiceType, class RequestType, class ResponseType,
          class BaseRequestType = RequestType,
          class BaseResponseType = ResponseType>
class RpcMethodHandler : public grpc::internal::MethodHandler {
 public:
  RpcMethodHandler(
      std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                                 const RequestType*, ResponseType*)>
          func,
      ServiceType* service)
      : func_(func), service_(service) {}

  // Main handler method for unary RPCs
  void RunHandler(const HandlerParameter& param) final {
    ResponseType rsp;
    grpc::Status status = param.status;
    if (status.ok()) {
      // Execute the handler function with exception protection
      status = CatchingFunctionHandler([this, &param, &rsp] {
        return func_(service_,
                     static_cast<grpc::ServerContext*>(param.server_context),
                     static_cast<RequestType*>(param.request), &rsp);
      });
      // Clean up request object
      static_cast<RequestType*>(param.request)->~RequestType();
    }
    // Send response to client
    UnaryRunHandlerHelper(param, static_cast<BaseResponseType*>(&rsp), status);
  }

  // Deserializes the incoming request
  void* Deserialize(grpc_call* call, grpc_byte_buffer* req,
                    grpc::Status* status, void** ) final {
    // Allocate request object in call arena
    auto* request =
        new (grpc_call_arena_alloc(call, sizeof(RequestType))) RequestType;
    return UnaryDeserializeHelper(req, status,
                                  static_cast<BaseRequestType*>(request));
  }

 private:
  // The service method implementation
  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             const RequestType*, ResponseType*)>
      func_;

  // The service instance
  ServiceType* service_;
};

// Handler for client streaming RPCs (client sends stream, server sends single response)
template <class ServiceType, class RequestType, class ResponseType>
class ClientStreamingHandler : public grpc::internal::MethodHandler {
 public:
  ClientStreamingHandler(
      std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                                 ServerReader<RequestType>*, ResponseType*)>
          func,
      ServiceType* service)
      : func_(func), service_(service) {}

  void RunHandler(const HandlerParameter& param) final {
    // Create reader for client stream
    ServerReader<RequestType> reader(
        param.call, static_cast<grpc::ServerContext*>(param.server_context));
    ResponseType rsp;
    // Execute handler with exception protection
    grpc::Status status =
        CatchingFunctionHandler([this, &param, &reader, &rsp] {
          return func_(service_,
                       static_cast<grpc::ServerContext*>(param.server_context),
                       &reader, &rsp);
        });

    // Set up operations for sending response
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    // Send initial metadata if not already sent
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
    }
    // Send response message if status is OK
    if (status.ok()) {
      status = ops.SendMessagePtr(&rsp);
    }
    // Send final status to client
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    // Perform operations and wait for completion
    param.call->PerformOps(&ops);
    param.call->cq()->Pluck(&ops);
  }

 private:
  // The service method implementation
  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             ServerReader<RequestType>*, ResponseType*)>
      func_;
  // The service instance
  ServiceType* service_;
};

// Handler for server streaming RPCs (client sends single request, server sends stream)
template <class ServiceType, class RequestType, class ResponseType>
class ServerStreamingHandler : public grpc::internal::MethodHandler {
 public:
  ServerStreamingHandler(std::function<grpc::Status(
                             ServiceType*, grpc::ServerContext*,
                             const RequestType*, ServerWriter<ResponseType>*)>
                             func,
                         ServiceType* service)
      : func_(func), service_(service) {}

  void RunHandler(const HandlerParameter& param) final {
    grpc::Status status = param.status;
    if (status.ok()) {
      // Create writer for server stream
      ServerWriter<ResponseType> writer(
          param.call, static_cast<grpc::ServerContext*>(param.server_context));
      // Execute handler with exception protection
      status = CatchingFunctionHandler([this, &param, &writer] {
        return func_(service_,
                     static_cast<grpc::ServerContext*>(param.server_context),
                     static_cast<RequestType*>(param.request), &writer);
      });
      // Clean up request object
      static_cast<RequestType*>(param.request)->~RequestType();
    }

    // Set up operations for sending status
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    // Send initial metadata if not already sent
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
    }
    // Send final status to client
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    // Perform operations and wait for completion
    param.call->PerformOps(&ops);
    if (param.server_context->has_pending_ops_) {
      param.call->cq()->Pluck(&param.server_context->pending_ops_);
    }
    param.call->cq()->Pluck(&ops);
  }

  // Deserializes the incoming request
  void* Deserialize(grpc_call* call, grpc_byte_buffer* req,
                    grpc::Status* status, void** ) final {
    grpc::ByteBuffer buf;
    buf.set_buffer(req);
    // Allocate request object in call arena
    auto* request =
        new (grpc_call_arena_alloc(call, sizeof(RequestType))) RequestType();
    *status =
        grpc::SerializationTraits<RequestType>::Deserialize(&buf, request);
    buf.Release();
    if (status->ok()) {
      return request;
    }
    // Clean up if deserialization failed
    request->~RequestType();
    return nullptr;
  }

 private:
  // The service method implementation
  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             const RequestType*, ServerWriter<ResponseType>*)>
      func_;
  // The service instance
  ServiceType* service_;
};

// Base template for bidirectional streaming handlers
template <class Streamer, bool WriteNeeded>
class TemplatedBidiStreamingHandler : public grpc::internal::MethodHandler {
 public:
  explicit TemplatedBidiStreamingHandler(
      std::function<grpc::Status(grpc::ServerContext*, Streamer*)> func)
      : func_(func), write_needed_(WriteNeeded) {}

  void RunHandler(const HandlerParameter& param) final {
    // Create streamer for bidirectional communication
    Streamer stream(param.call,
                    static_cast<grpc::ServerContext*>(param.server_context));
    // Execute handler with exception protection
    grpc::Status status = CatchingFunctionHandler([this, &param, &stream] {
      return func_(static_cast<grpc::ServerContext*>(param.server_context),
                   &stream);
    });

    // Set up operations for sending status
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    // Send initial metadata if not already sent
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
      // Check if response was required but not provided
      if (write_needed_ && status.ok()) {
        status = grpc::Status(grpc::StatusCode::INTERNAL,
                              "Service did not provide response message");
      }
    }
    // Send final status to client
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    // Perform operations and wait for completion
    param.call->PerformOps(&ops);
    if (param.server_context->has_pending_ops_) {
      param.call->cq()->Pluck(&param.server_context->pending_ops_);
    }
    param.call->cq()->Pluck(&ops);
  }

 private:
  // The service method implementation
  std::function<grpc::Status(grpc::ServerContext*, Streamer*)> func_;
  // Flag indicating whether a response write is required
  const bool write_needed_;
};

// Handler for bidirectional streaming RPCs
template <class ServiceType, class RequestType, class ResponseType>
class BidiStreamingHandler
    : public TemplatedBidiStreamingHandler<
          ServerReaderWriter<ResponseType, RequestType>, false> {
 public:
  BidiStreamingHandler(std::function<grpc::Status(
                           ServiceType*, grpc::ServerContext*,
                           ServerReaderWriter<ResponseType, RequestType>*)>
                           func,
                       ServiceType* service)
      : TemplatedBidiStreamingHandler<
            ServerReaderWriter<ResponseType, RequestType>, false>(
            [func, service](
                grpc::ServerContext* ctx,
                ServerReaderWriter<ResponseType, RequestType>* streamer) {
              return func(service, ctx, streamer);
            }) {}
};

// Handler for streamed unary RPCs (client sends stream, server sends single response)
template <class RequestType, class ResponseType>
class StreamedUnaryHandler
    : public TemplatedBidiStreamingHandler<
          ServerUnaryStreamer<RequestType, ResponseType>, true> {
 public:
  explicit StreamedUnaryHandler(
      std::function<
          grpc::Status(grpc::ServerContext*,
                       ServerUnaryStreamer<RequestType, ResponseType>*)>
          func)
      : TemplatedBidiStreamingHandler<
            ServerUnaryStreamer<RequestType, ResponseType>, true>(
            std::move(func)) {}
};

// Handler for split streaming RPCs (separate reader and writer)
template <class RequestType, class ResponseType>
class SplitServerStreamingHandler
    : public TemplatedBidiStreamingHandler<
          ServerSplitStreamer<RequestType, ResponseType>, false> {
 public:
  explicit SplitServerStreamingHandler(
      std::function<
          grpc::Status(grpc::ServerContext*,
                       ServerSplitStreamer<RequestType, ResponseType>*)>
          func)
      : TemplatedBidiStreamingHandler<
            ServerSplitStreamer<RequestType, ResponseType>, false>(
            std::move(func)) {}
};

// Handler for returning error responses with specific status code
template <grpc::StatusCode code>
class ErrorMethodHandler : public grpc::internal::MethodHandler {
 public:
  explicit ErrorMethodHandler(const std::string& message) : message_(message) {}

  // Helper method to fill operations with error response
  template <class T>
  static void FillOps(grpc::ServerContextBase* context,
                      const std::string& message, T* ops) {
    grpc::Status status(code, message);
    if (!context->sent_initial_metadata_) {
      ops->SendInitialMetadata(&context->initial_metadata_,
                               context->initial_metadata_flags());
      if (context->compression_level_set()) {
        ops->set_compression_level(context->compression_level());
      }
      context->sent_initial_metadata_ = true;
    }
    ops->ServerSendStatus(&context->trailing_metadata_, status);
  }

  void RunHandler(const HandlerParameter& param) final {
    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    FillOps(param.server_context, message_, &ops);
    param.call->PerformOps(&ops);
    param.call->cq()->Pluck(&ops);
  }

  void* Deserialize(grpc_call* , grpc_byte_buffer* req,
                    grpc::Status* , void** ) final {
    // Clean up request buffer if present (no deserialization for error handlers)
    if (req != nullptr) {
      grpc_byte_buffer_destroy(req);
    }
    return nullptr;
  }

 private:
  const std::string message_;
};

// Specific error handlers
typedef ErrorMethodHandler<grpc::StatusCode::UNIMPLEMENTED>
    UnknownMethodHandler;  // For unimplemented methods
typedef ErrorMethodHandler<grpc::StatusCode::RESOURCE_EXHAUSTED>
    ResourceExhaustedHandler;  // For resource exhausted errors

}
}

#endif
```