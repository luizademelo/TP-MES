
// Copyright 2018 gRPC authors.

#ifndef GRPCPP_GENERIC_ASYNC_GENERIC_SERVICE_H
#define GRPCPP_GENERIC_ASYNC_GENERIC_SERVICE_H

#include <grpc/support/port_platform.h>
#include <grpcpp/generic/callback_generic_service.h>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/byte_buffer.h>

struct grpc_server;

namespace grpc {

typedef ServerAsyncReaderWriter<ByteBuffer, ByteBuffer>
    GenericServerAsyncReaderWriter;
typedef ServerAsyncResponseWriter<ByteBuffer> GenericServerAsyncResponseWriter;
typedef ServerAsyncReader<ByteBuffer, ByteBuffer> GenericServerAsyncReader;
typedef ServerAsyncWriter<ByteBuffer> GenericServerAsyncWriter;

class GenericServerContext final : public ServerContext {
 public:
  const std::string& method() const { return method_; }
  const std::string& host() const { return host_; }

 private:
  friend class ServerInterface;

  std::string method_;
  std::string host_;
};

class AsyncGenericService final {
 public:
  AsyncGenericService() : server_(nullptr) {}

  void RequestCall(GenericServerContext* ctx,
                   GenericServerAsyncReaderWriter* reader_writer,
                   grpc::CompletionQueue* call_cq,
                   grpc::ServerCompletionQueue* notification_cq, void* tag);

 private:
  friend class grpc::Server;
  grpc::Server* server_;
};

}

#endif
