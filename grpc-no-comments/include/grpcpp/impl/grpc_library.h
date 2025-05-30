
// Copyright 2015 gRPC authors.

#ifndef GRPCPP_IMPL_GRPC_LIBRARY_H
#define GRPCPP_IMPL_GRPC_LIBRARY_H

#include <grpc/grpc.h>
#include <grpcpp/impl/codegen/config.h>

#include <iostream>

namespace grpc {

namespace internal {

class GrpcLibrary {
 public:
  explicit GrpcLibrary(bool call_grpc_init = true) : grpc_init_called_(false) {
    if (call_grpc_init) {
      grpc_init();
      grpc_init_called_ = true;
    }
  }
  virtual ~GrpcLibrary() {
    if (grpc_init_called_) {
      grpc_shutdown();
    }
  }

 private:
  bool grpc_init_called_;
};

}
}

#endif
