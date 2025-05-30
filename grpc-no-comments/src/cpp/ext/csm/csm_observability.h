
// Copyright 2023 gRPC authors.

#ifndef GRPC_SRC_CPP_EXT_CSM_CSM_OBSERVABILITY_H
#define GRPC_SRC_CPP_EXT_CSM_CSM_OBSERVABILITY_H

#include <grpc/support/port_platform.h>

#include "absl/strings/string_view.h"
#include "src/core/lib/channel/channel_args.h"

namespace grpc {
namespace internal {

bool CsmChannelTargetSelector(absl::string_view target);

bool CsmServerSelector(const grpc_core::ChannelArgs& args);

}
}

#endif
