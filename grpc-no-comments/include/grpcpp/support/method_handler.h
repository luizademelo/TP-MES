
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

template <class ResponseType>
void UnaryRunHandlerHelper(const MethodHandler::HandlerParameter& param,
                           ResponseType* rsp, grpc::Status& status) {
  ABSL_CHECK(!param.server_context->sent_initial_metadata_);
  grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                            grpc::internal::CallOpSendMessage,
                            grpc::internal::CallOpServerSendStatus>
      ops;
  ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                          param.server_context->initial_metadata_flags());
  if (param.server_context->compression_level_set()) {
    ops.set_compression_level(param.server_context->compression_level());
  }
  if (status.ok()) {
    status = ops.SendMessagePtr(rsp);
  }
  ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
  param.call->PerformOps(&ops);
  param.call->cq()->Pluck(&ops);
}

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
  request->~RequestType();
  return nullptr;
}

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

  void RunHandler(const HandlerParameter& param) final {
    ResponseType rsp;
    grpc::Status status = param.status;
    if (status.ok()) {
      status = CatchingFunctionHandler([this, &param, &rsp] {
        return func_(service_,
                     static_cast<grpc::ServerContext*>(param.server_context),
                     static_cast<RequestType*>(param.request), &rsp);
      });
      static_cast<RequestType*>(param.request)->~RequestType();
    }
    UnaryRunHandlerHelper(param, static_cast<BaseResponseType*>(&rsp), status);
  }

  void* Deserialize(grpc_call* call, grpc_byte_buffer* req,
                    grpc::Status* status, void** ) final {
    auto* request =
        new (grpc_call_arena_alloc(call, sizeof(RequestType))) RequestType;
    return UnaryDeserializeHelper(req, status,
                                  static_cast<BaseRequestType*>(request));
  }

 private:

  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             const RequestType*, ResponseType*)>
      func_;

  ServiceType* service_;
};

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
    ServerReader<RequestType> reader(
        param.call, static_cast<grpc::ServerContext*>(param.server_context));
    ResponseType rsp;
    grpc::Status status =
        CatchingFunctionHandler([this, &param, &reader, &rsp] {
          return func_(service_,
                       static_cast<grpc::ServerContext*>(param.server_context),
                       &reader, &rsp);
        });

    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpSendMessage,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
    }
    if (status.ok()) {
      status = ops.SendMessagePtr(&rsp);
    }
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    param.call->PerformOps(&ops);
    param.call->cq()->Pluck(&ops);
  }

 private:
  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             ServerReader<RequestType>*, ResponseType*)>
      func_;
  ServiceType* service_;
};

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
      ServerWriter<ResponseType> writer(
          param.call, static_cast<grpc::ServerContext*>(param.server_context));
      status = CatchingFunctionHandler([this, &param, &writer] {
        return func_(service_,
                     static_cast<grpc::ServerContext*>(param.server_context),
                     static_cast<RequestType*>(param.request), &writer);
      });
      static_cast<RequestType*>(param.request)->~RequestType();
    }

    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
    }
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    param.call->PerformOps(&ops);
    if (param.server_context->has_pending_ops_) {
      param.call->cq()->Pluck(&param.server_context->pending_ops_);
    }
    param.call->cq()->Pluck(&ops);
  }

  void* Deserialize(grpc_call* call, grpc_byte_buffer* req,
                    grpc::Status* status, void** ) final {
    grpc::ByteBuffer buf;
    buf.set_buffer(req);
    auto* request =
        new (grpc_call_arena_alloc(call, sizeof(RequestType))) RequestType();
    *status =
        grpc::SerializationTraits<RequestType>::Deserialize(&buf, request);
    buf.Release();
    if (status->ok()) {
      return request;
    }
    request->~RequestType();
    return nullptr;
  }

 private:
  std::function<grpc::Status(ServiceType*, grpc::ServerContext*,
                             const RequestType*, ServerWriter<ResponseType>*)>
      func_;
  ServiceType* service_;
};

template <class Streamer, bool WriteNeeded>
class TemplatedBidiStreamingHandler : public grpc::internal::MethodHandler {
 public:
  explicit TemplatedBidiStreamingHandler(
      std::function<grpc::Status(grpc::ServerContext*, Streamer*)> func)
      : func_(func), write_needed_(WriteNeeded) {}

  void RunHandler(const HandlerParameter& param) final {
    Streamer stream(param.call,
                    static_cast<grpc::ServerContext*>(param.server_context));
    grpc::Status status = CatchingFunctionHandler([this, &param, &stream] {
      return func_(static_cast<grpc::ServerContext*>(param.server_context),
                   &stream);
    });

    grpc::internal::CallOpSet<grpc::internal::CallOpSendInitialMetadata,
                              grpc::internal::CallOpServerSendStatus>
        ops;
    if (!param.server_context->sent_initial_metadata_) {
      ops.SendInitialMetadata(&param.server_context->initial_metadata_,
                              param.server_context->initial_metadata_flags());
      if (param.server_context->compression_level_set()) {
        ops.set_compression_level(param.server_context->compression_level());
      }
      if (write_needed_ && status.ok()) {

        status = grpc::Status(grpc::StatusCode::INTERNAL,
                              "Service did not provide response message");
      }
    }
    ops.ServerSendStatus(&param.server_context->trailing_metadata_, status);
    param.call->PerformOps(&ops);
    if (param.server_context->has_pending_ops_) {
      param.call->cq()->Pluck(&param.server_context->pending_ops_);
    }
    param.call->cq()->Pluck(&ops);
  }

 private:
  std::function<grpc::Status(grpc::ServerContext*, Streamer*)> func_;
  const bool write_needed_;
};

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

template <grpc::StatusCode code>
class ErrorMethodHandler : public grpc::internal::MethodHandler {
 public:
  explicit ErrorMethodHandler(const std::string& message) : message_(message) {}

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

    if (req != nullptr) {
      grpc_byte_buffer_destroy(req);
    }
    return nullptr;
  }

 private:
  const std::string message_;
};

typedef ErrorMethodHandler<grpc::StatusCode::UNIMPLEMENTED>
    UnknownMethodHandler;
typedef ErrorMethodHandler<grpc::StatusCode::RESOURCE_EXHAUSTED>
    ResourceExhaustedHandler;

}
}

#endif
