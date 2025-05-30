
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_HANDSHAKER_SECURITY_SECURITY_HANDSHAKER_H
#define GRPC_SRC_CORE_HANDSHAKER_SECURITY_SECURITY_HANDSHAKER_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>

#include "absl/status/statusor.h"
#include "src/core/config/core_configuration.h"
#include "src/core/credentials/transport/security_connector.h"
#include "src/core/handshaker/handshaker.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/tsi/transport_security_interface.h"
#include "src/core/util/ref_counted_ptr.h"

namespace grpc_core {

RefCountedPtr<Handshaker> SecurityHandshakerCreate(
    absl::StatusOr<tsi_handshaker*> handshaker,
    grpc_security_connector* connector, const ChannelArgs& args);

void SecurityRegisterHandshakerFactories(CoreConfiguration::Builder*);

}

#endif
