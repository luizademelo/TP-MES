
// Copyright 2022 gRPC authors.

#ifndef GRPC_TEST_CPP_INTEROP_ISTIO_ECHO_SERVER_LIB_H
#define GRPC_TEST_CPP_INTEROP_ISTIO_ECHO_SERVER_LIB_H

#include "src/proto/grpc/testing/istio_echo.grpc.pb.h"

namespace grpc {
namespace testing {

class EchoTestServiceImpl : public proto::EchoTestService::Service {
 public:
  EchoTestServiceImpl(std::string hostname, std::string service_version,
                      std::string forwarding_address);

  grpc::Status Echo(grpc::ServerContext* context,
                    const proto::EchoRequest* request,
                    proto::EchoResponse* response) override;

  grpc::Status ForwardEcho(grpc::ServerContext* ,
                           const proto::ForwardEchoRequest* request,
                           proto::ForwardEchoResponse* response) override;

 private:
  std::string hostname_;
  std::string service_version_;
  std::string forwarding_address_;
  std::unique_ptr<proto::EchoTestService::Stub> forwarding_stub_;

};

}
}

#endif
