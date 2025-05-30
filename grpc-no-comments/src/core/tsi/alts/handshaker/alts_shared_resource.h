
// Copyright 2018 gRPC authors.

#ifndef GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_SHARED_RESOURCE_H
#define GRPC_SRC_CORE_TSI_ALTS_HANDSHAKER_ALTS_SHARED_RESOURCE_H

#include <grpc/grpc.h>
#include <grpc/support/port_platform.h>
#include <grpc/support/sync.h>

#include "src/core/lib/iomgr/pollset_set.h"
#include "src/core/lib/surface/completion_queue.h"
#include "src/core/util/thd.h"

typedef struct alts_shared_resource_dedicated {
  grpc_core::Thread thread;
  grpc_completion_queue* cq;
  grpc_pollset_set* interested_parties;
  grpc_cq_completion storage;
  gpr_mu mu;
  grpc_channel* channel;
} alts_shared_resource_dedicated;

alts_shared_resource_dedicated* grpc_alts_get_shared_resource_dedicated(void);

void grpc_alts_shared_resource_dedicated_shutdown();

void grpc_alts_shared_resource_dedicated_init();

void grpc_alts_shared_resource_dedicated_start(
    const char* handshaker_service_url);

#endif
