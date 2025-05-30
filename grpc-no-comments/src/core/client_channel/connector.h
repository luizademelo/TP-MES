
// Copyright 2015 gRPC authors.

#ifndef GRPC_SRC_CORE_CLIENT_CHANNEL_CONNECTOR_H
#define GRPC_SRC_CORE_CLIENT_CHANNEL_CONNECTOR_H

#include <grpc/support/port_platform.h>

#include "src/core/channelz/channelz.h"
#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/iomgr/closure.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/iomgr/iomgr_fwd.h"
#include "src/core/lib/iomgr/resolved_address.h"
#include "src/core/lib/transport/transport.h"
#include "src/core/util/orphanable.h"
#include "src/core/util/ref_counted_ptr.h"
#include "src/core/util/time.h"

namespace grpc_core {

class SubchannelConnector : public InternallyRefCounted<SubchannelConnector> {
 public:
  struct Args {

    grpc_resolved_address* address;

    grpc_pollset_set* interested_parties;

    Timestamp deadline;

    ChannelArgs channel_args;
  };

  struct Result {

    Transport* transport = nullptr;

    ChannelArgs channel_args;

    void Reset() {
      if (transport != nullptr) {
        transport->Orphan();
        transport = nullptr;
      }
      channel_args = ChannelArgs();
    }
  };

  virtual void Connect(const Args& args, Result* result,
                       grpc_closure* notify) = 0;

  virtual void Shutdown(grpc_error_handle error) = 0;

  void Orphan() override {
    Shutdown(GRPC_ERROR_CREATE("Subchannel disconnected"));
    Unref();
  }
};

}

#endif
