// Copyright 2024 The gRPC Authors

#ifndef GRPC_SRC_CORE_LIB_TRANSPORT_TRANSPORT_FRAMING_ENDPOINT_EXTENSION_H
#define GRPC_SRC_CORE_LIB_TRANSPORT_TRANSPORT_FRAMING_ENDPOINT_EXTENSION_H

#include <grpc/support/port_platform.h>

#include "absl/functional/any_invocable.h"
#include "absl/strings/string_view.h"
#include "src/core/lib/slice/slice_buffer.h"

namespace grpc_core {

class TransportFramingEndpointExtension {
 public:
  virtual ~TransportFramingEndpointExtension() = default;
  static absl::string_view EndpointExtensionName() {
    return "io.grpc.transport.extension.transport_framing_endpoint_"
           "extension";
  }

  virtual void SetSendFrameCallback(
      absl::AnyInvocable<void(SliceBuffer* data)> cb) = 0;

  virtual void ReceiveFrame(SliceBuffer data) = 0;
};

}

#endif
