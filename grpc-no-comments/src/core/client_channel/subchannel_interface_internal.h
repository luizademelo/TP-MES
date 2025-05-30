
// Copyright 2022 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_INTERFACE_INTERNAL_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_SUBCHANNEL_INTERFACE_INTERNAL_H

#include <grpc/support/port_platform.h>

#include "src/core/client_channel/subchannel.h"
#include "src/core/load_balancing/subchannel_interface.h"
#include "src/core/util/unique_type_name.h"

namespace grpc_core {

class InternalSubchannelDataWatcherInterface
    : public SubchannelInterface::DataWatcherInterface {
 public:
  virtual UniqueTypeName type() const = 0;

  virtual void SetSubchannel(Subchannel* subchannel) = 0;
};

}

#endif
