
// Copyright 2021 gRPC authors.

#include "src/cpp/server/csds/csds.h"

#include <grpc/slice.h>
#include <grpc/support/port_platform.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/slice.h>

#include <string>
#include <utility>

#include "absl/status/status.h"
#include "absl/status/statusor.h"

namespace grpc {
namespace xds {
namespace experimental {

using envoy::service::status::v3::ClientStatusRequest;
using envoy::service::status::v3::ClientStatusResponse;

namespace {

absl::StatusOr<ClientStatusResponse> DumpClientStatusResponse() {
  ClientStatusResponse response;
  grpc_slice serialized_client_config = grpc_dump_xds_configs();
  std::string bytes = StringFromCopiedSlice(serialized_client_config);
  grpc_slice_unref(serialized_client_config);
  if (!response.ParseFromString(bytes)) {
    return absl::InternalError("Failed to parse ClientStatusResponse.");
  }
  return response;
}

}

Status ClientStatusDiscoveryService::StreamClientStatus(
    ServerContext* ,
    ServerReaderWriter<ClientStatusResponse, ClientStatusRequest>* stream) {
  ClientStatusRequest request;
  while (stream->Read(&request)) {
    absl::StatusOr<ClientStatusResponse> response = DumpClientStatusResponse();
    if (!response.ok()) {
      if (response.status().code() == absl::StatusCode::kUnavailable) {

        stream->Write(ClientStatusResponse());
        continue;
      }
      return Status(static_cast<StatusCode>(response.status().raw_code()),
                    response.status().ToString());
    }
    stream->Write(*response);
  }
  return Status::OK;
}

Status ClientStatusDiscoveryService::FetchClientStatus(
    ServerContext* , const ClientStatusRequest* ,
    ClientStatusResponse* response) {
  absl::StatusOr<ClientStatusResponse> s = DumpClientStatusResponse();
  if (!s.ok()) {
    if (s.status().code() == absl::StatusCode::kUnavailable) {

      return Status::OK;
    }
    return Status(static_cast<StatusCode>(s.status().raw_code()),
                  s.status().ToString());
  }
  *response = std::move(*s);
  return Status::OK;
}

}
}
}
