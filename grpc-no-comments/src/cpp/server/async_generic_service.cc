
// Copyright 2015 gRPC authors.

#include <grpcpp/completion_queue.h>
#include <grpcpp/generic/async_generic_service.h>
#include <grpcpp/server.h>

namespace grpc {

void AsyncGenericService::RequestCall(
    GenericServerContext* ctx, GenericServerAsyncReaderWriter* reader_writer,
    grpc::CompletionQueue* call_cq,
    grpc::ServerCompletionQueue* notification_cq, void* tag) {
  server_->RequestAsyncGenericCall(ctx, reader_writer, call_cq, notification_cq,
                                   tag);
}

}
