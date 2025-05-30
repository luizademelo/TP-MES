
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_SERVER_INTERCEPTOR_H
#define GRPCPP_SUPPORT_SERVER_INTERCEPTOR_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/string_ref.h>

#include <atomic>
#include <vector>

#include "absl/log/absl_check.h"

namespace grpc {
class ServerContextBase;
namespace internal {
class InterceptorBatchMethodsImpl;
}

namespace experimental {
class ServerRpcInfo;

class ServerInterceptorFactoryInterface {
 public:
  virtual ~ServerInterceptorFactoryInterface() {}

  virtual Interceptor* CreateServerInterceptor(ServerRpcInfo* info) = 0;
};

class ServerRpcInfo {
 public:

  enum class Type { UNARY, CLIENT_STREAMING, SERVER_STREAMING, BIDI_STREAMING };

  ~ServerRpcInfo() {}

  ServerRpcInfo(const ServerRpcInfo&) = delete;
  ServerRpcInfo& operator=(const ServerRpcInfo&) = delete;
  ServerRpcInfo(ServerRpcInfo&&) = delete;
  ServerRpcInfo& operator=(ServerRpcInfo&&) = delete;

  const char* method() const { return method_; }

  Type type() const { return type_; }

  ServerContextBase* server_context() { return ctx_; }

 private:
  static_assert(Type::UNARY ==
                    static_cast<Type>(internal::RpcMethod::NORMAL_RPC),
                "violated expectation about Type enum");
  static_assert(Type::CLIENT_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::CLIENT_STREAMING),
                "violated expectation about Type enum");
  static_assert(Type::SERVER_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::SERVER_STREAMING),
                "violated expectation about Type enum");
  static_assert(Type::BIDI_STREAMING ==
                    static_cast<Type>(internal::RpcMethod::BIDI_STREAMING),
                "violated expectation about Type enum");

  ServerRpcInfo(ServerContextBase* ctx, const char* method,
                internal::RpcMethod::RpcType type)
      : ctx_(ctx), method_(method), type_(static_cast<Type>(type)) {}

  void RunInterceptor(
      experimental::InterceptorBatchMethods* interceptor_methods, size_t pos) {
    ABSL_CHECK_LT(pos, interceptors_.size());
    interceptors_[pos]->Intercept(interceptor_methods);
  }

  void RegisterInterceptors(
      const std::vector<
          std::unique_ptr<experimental::ServerInterceptorFactoryInterface>>&
          creators) {
    for (const auto& creator : creators) {
      auto* interceptor = creator->CreateServerInterceptor(this);
      if (interceptor != nullptr) {
        interceptors_.push_back(
            std::unique_ptr<experimental::Interceptor>(interceptor));
      }
    }
  }

  void Ref() { ref_.fetch_add(1, std::memory_order_relaxed); }
  void Unref() {
    if (GPR_UNLIKELY(ref_.fetch_sub(1, std::memory_order_acq_rel) == 1)) {
      delete this;
    }
  }

  ServerContextBase* ctx_ = nullptr;
  const char* method_ = nullptr;
  const Type type_;
  std::atomic<intptr_t> ref_{1};
  std::vector<std::unique_ptr<experimental::Interceptor>> interceptors_;

  friend class internal::InterceptorBatchMethodsImpl;
  friend class grpc::ServerContextBase;
};

}
}

#endif
