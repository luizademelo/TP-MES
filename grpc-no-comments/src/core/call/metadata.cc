// Copyright 2024 gRPC authors.

#include "src/core/call/metadata.h"

#include <grpc/support/port_platform.h>

#include "src/core/call/metadata_batch.h"
#include "src/core/lib/transport/error_utils.h"

namespace grpc_core {

ServerMetadataHandle ServerMetadataFromStatus(const absl::Status& status) {
  auto hdl = Arena::MakePooledForOverwrite<ServerMetadata>();
  grpc_status_code code;
  std::string message;
  grpc_error_get_status(status, Timestamp::InfFuture(), &code, &message,
                        nullptr, nullptr);
  hdl->Set(GrpcStatusMetadata(), code);
  if (!status.ok()) {
    hdl->Set(GrpcMessageMetadata(), Slice::FromCopiedString(message));
  }
  return hdl;
}

ServerMetadataHandle CancelledServerMetadataFromStatus(
    const absl::Status& status) {
  auto hdl = ServerMetadataFromStatus(status);
  hdl->Set(GrpcCallWasCancelled(), true);
  return hdl;
}

ServerMetadataHandle ServerMetadataFromStatus(grpc_status_code code,
                                              absl::string_view message) {
  auto hdl = Arena::MakePooledForOverwrite<ServerMetadata>();
  hdl->Set(GrpcStatusMetadata(), code);
  hdl->Set(GrpcMessageMetadata(), Slice::FromCopiedString(message));
  return hdl;
}

ServerMetadataHandle CancelledServerMetadataFromStatus(
    grpc_status_code code, absl::string_view message) {
  auto hdl = Arena::MakePooledForOverwrite<ServerMetadata>();
  hdl->Set(GrpcStatusMetadata(), code);
  hdl->Set(GrpcMessageMetadata(), Slice::FromCopiedString(message));
  hdl->Set(GrpcCallWasCancelled(), true);
  return hdl;
}

}
