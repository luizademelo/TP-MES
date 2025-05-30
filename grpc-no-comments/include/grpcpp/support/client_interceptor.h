
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_SUPPORT_CLIENT_INTERCEPTOR_H
#define GRPCPP_SUPPORT_CLIENT_INTERCEPTOR_H

#include <grpcpp/impl/rpc_method.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/string_ref.h>

#include <memory>
#include <vector>

#include "absl/log/absl_check.h"

namespace grpc {

class Channel;
class ClientContext;

namespace internal {
class InterceptorBatchMethodsImpl;
}

namespace experimental {
class ClientRpcInfo;

class ClientInterceptorFactoryInterface {
 public:
  virtual ~ClientInterceptorFactoryInterface() {}

  virtual Interceptor* CreateClientInterceptor(ClientRpcInfo* info) = 0;
};
}

namespace internal {
extern experimental::ClientInterceptorFactoryInterface*
    g_global_client_interceptor_factory;

extern experimental::ClientInterceptorFactoryInterface*
    g_global_client_stats_interceptor_factory;
}

namespace experimental {
class ClientRpcInfo {
 public:

  enum class Type {
    UNARY,
    CLIENT_STREAMING,
    SERVER_STREAMING,
    BIDI_STREAMING,
    UNKNOWN
  };

  ~ClientRpcInfo() {}

  ClientRpcInfo(const ClientRpcInfo&) = delete;
  ClientRpcInfo(ClientRpcInfo&&) = default;

  const char* method() const { return method_; }

  const char* suffix_for_stats() const { return suffix_for_stats_; }

  ChannelInterface* channel() { return channel_; }

  grpc::ClientContext* client_context() { return ctx_; }

  Type type() const { return type_; }

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

  ClientRpcInfo() = default;

  ClientRpcInfo(grpc::ClientContext* ctx, internal::RpcMethod::RpcType type,
                const char* method, const char* suffix_for_stats,
                grpc::ChannelInterface* channel)
      : ctx_(ctx),
        type_(static_cast<Type>(type)),
        method_(method),
        suffix_for_stats_(suffix_for_stats),
        channel_(channel) {}

  ClientRpcInfo& operator=(ClientRpcInfo&&) = default;

  void RunInterceptor(
      experimental::InterceptorBatchMethods* interceptor_methods, size_t pos) {
    ABSL_CHECK_LT(pos, interceptors_.size());
    interceptors_[pos]->Intercept(interceptor_methods);
  }

  void RegisterInterceptors(
      const std::vector<std::unique_ptr<
          experimental::ClientInterceptorFactoryInterface>>& creators,
      size_t interceptor_pos) {

    size_t num_interceptors =
        creators.size() +
        (internal::g_global_client_stats_interceptor_factory != nullptr) +
        (internal::g_global_client_interceptor_factory != nullptr);
    if (interceptor_pos > num_interceptors) {

      return;
    }
    if (internal::g_global_client_stats_interceptor_factory != nullptr) {
      interceptors_.push_back(std::unique_ptr<experimental::Interceptor>(
          internal::g_global_client_stats_interceptor_factory
              ->CreateClientInterceptor(this)));
      --interceptor_pos;
    }
    // NOTE: The following is not a range-based for loop because it will only

    for (auto it = creators.begin() + interceptor_pos; it != creators.end();
         ++it) {
      auto* interceptor = (*it)->CreateClientInterceptor(this);
      if (interceptor != nullptr) {
        interceptors_.push_back(
            std::unique_ptr<experimental::Interceptor>(interceptor));
      }
    }
    if (internal::g_global_client_interceptor_factory != nullptr) {
      interceptors_.push_back(std::unique_ptr<experimental::Interceptor>(
          internal::g_global_client_interceptor_factory
              ->CreateClientInterceptor(this)));
    }
  }

  grpc::ClientContext* ctx_ = nullptr;

  Type type_{Type::UNKNOWN};
  const char* method_ = nullptr;
  const char* suffix_for_stats_ = nullptr;
  grpc::ChannelInterface* channel_ = nullptr;
  std::vector<std::unique_ptr<experimental::Interceptor>> interceptors_;
  bool hijacked_ = false;
  size_t hijacked_interceptor_ = 0;

  friend class internal::InterceptorBatchMethodsImpl;
  friend class grpc::ClientContext;
};

void RegisterGlobalClientInterceptorFactory(
    ClientInterceptorFactoryInterface* factory);

void TestOnlyResetGlobalClientInterceptorFactory();

}
}

#endif
