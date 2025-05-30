
// Copyright 2016 gRPC authors.

#ifndef GRPCPP_IMPL_SERVER_INITIALIZER_H
#define GRPCPP_IMPL_SERVER_INITIALIZER_H

#include <grpcpp/server.h>

#include <memory>
#include <vector>

namespace grpc {
class Server;
class Service;

class ServerInitializer {
 public:
  explicit ServerInitializer(grpc::Server* server) : server_(server) {}

  bool RegisterService(std::shared_ptr<grpc::Service> service) {
    if (!server_->RegisterService(nullptr, service.get())) {
      return false;
    }
    default_services_.push_back(service);
    return true;
  }

  const std::vector<std::string>* GetServiceList() {
    return &server_->services_;
  }

 private:
  grpc::Server* server_;
  std::vector<std::shared_ptr<grpc::Service> > default_services_;
};

}

#endif
