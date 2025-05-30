
// Copyright 2021 gRPC authors.

#ifndef GRPC_SRC_CPP_SERVER_CSDS_CSDS_H
#define GRPC_SRC_CPP_SERVER_CSDS_CSDS_H

#include <grpc/support/port_platform.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>

#include "src/proto/grpc/testing/xds/v3/csds.grpc.pb.h"

namespace grpc {
namespace xds {
namespace experimental {

class ClientStatusDiscoveryService final
    : public envoy::service::status::v3::ClientStatusDiscoveryService::Service {
 public:

  Status StreamClientStatus(
      ServerContext* ,
      ServerReaderWriter<envoy::service::status::v3::ClientStatusResponse,
                         envoy::service::status::v3::ClientStatusRequest>*
          stream) override;

  Status FetchClientStatus(
      ServerContext* ,
      const envoy::service::status::v3::ClientStatusRequest* ,
      envoy::service::status::v3::ClientStatusResponse* response) override;
};

}
}
}

#endif
