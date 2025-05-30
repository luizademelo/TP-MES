
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_IMPL_RPC_SERVICE_METHOD_H
#define GRPCPP_IMPL_RPC_SERVICE_METHOD_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/config.h>
#include <grpcpp/support/status.h>

#include <climits>
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "absl/log/absl_check.h"
#include "absl/log/absl_log.h"

namespace grpc {
class ServerContextBase;
namespace internal {

class MethodHandler {
 public:
  virtual ~MethodHandler() {}
  struct HandlerParameter {

    HandlerParameter(Call* c, grpc::ServerContextBase* context, void* req,
                     Status req_status, void* handler_data,
                     std::function<void()> requester)
        : call(c),
          server_context(context),
          request(req),
          status(req_status),
          internal_data(handler_data),
          call_requester(std::move(requester)) {}
    ~HandlerParameter() {}
    Call* const call;
    grpc::ServerContextBase* const server_context;
    void* const request;
    const Status status;
    void* const internal_data;
    const std::function<void()> call_requester;
  };
  virtual void RunHandler(const HandlerParameter& param) = 0;

  virtual void* Deserialize(grpc_call* , grpc_byte_buffer* req,
                            Status* , void** ) {
    ABSL_CHECK_EQ(req, nullptr);
    return nullptr;
  }
};

class RpcServiceMethod : public RpcMethod {
 public:

  RpcServiceMethod(const char* name, RpcMethod::RpcType type,
                   MethodHandler* handler)
      : RpcMethod(name, type),
        server_tag_(nullptr),
        api_type_(ApiType::SYNC),
        handler_(handler) {}

  enum class ApiType {
    SYNC,
    ASYNC,
    RAW,
    CALL_BACK,
    RAW_CALL_BACK,
  };

  void set_server_tag(void* tag) { server_tag_ = tag; }
  void* server_tag() const { return server_tag_; }

  MethodHandler* handler() const { return handler_.get(); }
  ApiType api_type() const { return api_type_; }
  void SetHandler(MethodHandler* handler) { handler_.reset(handler); }
  void SetServerApiType(RpcServiceMethod::ApiType type) {
    if ((api_type_ == ApiType::SYNC) &&
        (type == ApiType::ASYNC || type == ApiType::RAW)) {

      handler_.reset();
    } else if (api_type_ != ApiType::SYNC) {

      ABSL_LOG(INFO)
          << "You are marking method " << name() << " as '"
          << TypeToString(api_type_)
          << "', even though it was previously marked '" << TypeToString(type)
          << "'. This behavior will overwrite the original behavior. If "
             "you expected this then ignore this message.";
    }
    api_type_ = type;
  }

 private:
  void* server_tag_;
  ApiType api_type_;
  std::unique_ptr<MethodHandler> handler_;

  const char* TypeToString(RpcServiceMethod::ApiType type) {
    switch (type) {
      case ApiType::SYNC:
        return "sync";
      case ApiType::ASYNC:
        return "async";
      case ApiType::RAW:
        return "raw";
      case ApiType::CALL_BACK:
        return "callback";
      case ApiType::RAW_CALL_BACK:
        return "raw_callback";
      default:
        GPR_UNREACHABLE_CODE(return "unknown");
    }
  }
};
}

}

#endif
