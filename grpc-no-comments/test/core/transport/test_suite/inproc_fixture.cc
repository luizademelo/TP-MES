// Copyright 2023 gRPC authors.

#include "src/core/config/core_configuration.h"
#include "src/core/ext/transport/inproc/inproc_transport.h"
#include "test/core/transport/test_suite/transport_test.h"

namespace grpc_core {

TRANSPORT_FIXTURE(Inproc) {
  auto transports =
      MakeInProcessTransportPair(CoreConfiguration::Get()
                                     .channel_args_preconditioning()
                                     .PreconditionChannelArgs(nullptr));
  return {std::move(transports.first), std::move(transports.second)};
}

}
