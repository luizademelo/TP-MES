
// Copyright 2024 gRPC authors.

#ifndef GRPCPP_GENERIC_CALLBACK_GENERIC_SERVICE_H
#define GRPCPP_GENERIC_CALLBACK_GENERIC_SERVICE_H

#include <grpc/support/port_platform.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/support/byte_buffer.h>
#include <grpcpp/support/server_callback.h>

struct grpc_server;

namespace grpc {

using ServerGenericBidiReactor = ServerBidiReactor<ByteBuffer, ByteBuffer>;

class GenericCallbackServerContext final : public grpc::CallbackServerContext {
 public:
  const std::string& method() const { return method_; }
  const std::string& host() const { return host_; }

 private:
  friend class grpc::Server;

  std::string method_;
  std::string host_;
};

class CallbackGenericService {
 public:
  CallbackGenericService() {}
  virtual ~CallbackGenericService() {}

  virtual ServerGenericBidiReactor* CreateReactor(
      GenericCallbackServerContext* ) {
    class Reactor : public ServerGenericBidiReactor {
     public:
      Reactor() { this->Finish(Status(StatusCode::UNIMPLEMENTED, "")); }
      void OnDone() override { delete this; }
    };
    return new Reactor;
  }

 private:
  friend class grpc::Server;

  internal::CallbackBidiHandler<ByteBuffer, ByteBuffer>* Handler() {
    return new internal::CallbackBidiHandler<ByteBuffer, ByteBuffer>(
        [this](grpc::CallbackServerContext* ctx) {
          return CreateReactor(static_cast<GenericCallbackServerContext*>(ctx));
        });
  }

  grpc::Server* server_{nullptr};
};

}

#endif
